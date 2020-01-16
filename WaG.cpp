/*******************************************************************************
*  EECS 397
*
*  File name: WaG.cpp
*
*  Description: Routines for the WaG gameplay
*
*  Notes:
*
*  Author(s): Lemnij, Luca
*
*  Created: 4/28/2019
*  Last Modified: 
*
*  Changes:
*
*******************************************************************************/
#include "mbed.h"
#include "display.h"
#include "stepper.h"
#include "io_pins.h"
#include "testing.h"
#include "carriage.h"

/*******************************************************************************
*  Private Constants: Only accessible to code below this point in this file
*******************************************************************************/
#define gnoll_lifetime 20
#define station_A 1
#define station_B 0
#define BAUD_RATE 230400
#define CALIBRATED 1
#define NOT_CALIBRATED 0
#define MAX_VOLLEY_COUNT 15

/*******************************************************************************
*  Private Data: Only accessible to code below this point in this file
*******************************************************************************/
//Some code had to be duplicated and renamed due to the way mbed works. That is why
//some variables have the suffix _2 on them. 

//Represents the user button
DigitalIn user_button_2(BUTTON1);

//Represents the start button
DigitalIn start_button_2(UI_START_BUTTON);

//Represents the cal button
DigitalIn cal_button_2(UI_CAL_BUTTON, PullUp);

//Console used to print out messages
Serial pc_2(USBTX, USBRX, BAUD_RATE);

//Used to store which station the software is running on
DigitalIn station(UI_STATION_SELECT);

//Timer for the gnoll lifetime. 
Timer gnoll_timer;

//Timer for the whacker. This is used as a timeout in the play_as_whacker function
Timer whacker_timer;

//Stores whether the station has been calibrated
int cal_status = NOT_CALIBRATED;

//Stores the number of the current match
int match_cnt = 1;

//Stores how many hits have happened 
int hit_count = 0;

//Stores how many misses have happened
int miss_count = 0;

//Stores which volley we are on. MIGHT NOT NEED
int volley_no = 0;

//Stores which volley we are on
int volley_count;

//Stores the sensor that the whacker needs to hit. Used on gnoller to check correctness
int correct_whacker_pos = 0;

//Stores which sensor whacker needs to go to. Used by whacker to know where to go
int pos_to_seek = 0;

//Stores which position the gnoller is at. Used by the whacker
int gnoll_pos;

//Used to display score to the 1107 display module
int bcd_array[4]; 

/*******************************************************************************
*  Private Function Prototypes: These functions may only be called by code
*  below this point in this file
*******************************************************************************/
bool button_is_pressed(DigitalIn *button);
void wait_for_button_to_be_released(DigitalIn* button);
int pick_random_location();
int other_illuminated_sensor();
void set_correct_whacker_pos(int pos);
void set_correct_pos_to_seek();
void update_display();
void retry_or_crash(int pos);

/*******************************************************************************
*  Name: bool button_is_pressed(DigitalIn *button)
*
*  Description: Checks whether an input button has been pressed or not. The cases
*  arise from the fact that the user button is reversed(1 when pressed, 0 when not).
*
*  Inputs:
*  Parameters:
*  Globals: 
*
*  Outputs:
*  Parameters:
*  Globals: 
*  Returns: bool true if a button is pressed, flase if it is not pressed
*  Notes:
*
*  Changes: 
*******************************************************************************/ 
bool button_is_pressed(DigitalIn* button) {
    if(button == &user_button_2) {
        if(*button) {
            return true;
        } else {
            return false;
        }
    } else {
        if(!(*button)) {
            return true;
        } else {
            return false;
        }
    }
}

/*******************************************************************************
*  Name: void wait_for_button_to_be_released(DigitalIn* button);
*
*  Description: Runs an empty loop until the input button has been released. This 
*  effectively means that we are waiting until an input button is released 
*
*  Inputs:
*  Parameters:
*  Globals: 
*
*  Outputs:
*  Parameters:
*  Globals: 
*  Returns: void
*  Notes:
*
*  Changes: 
*******************************************************************************/ 
void wait_for_button_to_be_released(DigitalIn* button) {
    while(button_is_pressed(button)) {
        ;
    }
}

/*******************************************************************************
*  Name: int pick_random_location();
*
*  Description: Used by the gnoller to pick a random location for it to go light up 
*
*  Inputs:
*  Parameters:
*  Globals: 
*
*  Outputs:
*  Parameters:
*  Globals: 
*  Returns: int location to go to
*  Notes:
*
*  Changes: 
*******************************************************************************/ 
int pick_random_location() {
    srand(time(NULL));
    int pos = rand() % 8;
    if(station == station_A) {
        return pos;
    } else {
        return pos + 8;
    }
}

/*******************************************************************************
*  Name: int other_illuminated_sensor();
*
*  Description: Returns the position of the sensor that the other station illuminated
*  or -1 if no sensor is illuminated by either side(this case should never happen).
*
*  Inputs:
*  Parameters:
*  Globals: 
*
*  Outputs:
*  Parameters:
*  Globals: 
*  Returns: int position of sensor other side lit
*  Notes:
*
*  Changes: 
*******************************************************************************/ 
int other_illuminated_sensor() {
    static int start_pos = station == station_A ? 9 : 1;
    static int end_pos = station == station_A ? 16 : 8;
    for(int i = start_pos; i <= end_pos; i++) {
        if(is_lit(i)) {
            return i;
        }
    }
    return -1;
}

/*******************************************************************************
*  Name: void set_correct_whacker_pos(int pos);
*
*  Description: Determines where the whacker needs to go. Sets the correct whacker
*  pos variable using the station. This is used by the gnoller to know whether the
*  whacker has lit the right sensor. 
*
*  Inputs: int pos the position the gnoller is at
*  Parameters:
*  Globals: 
*
*  Outputs:
*  Parameters:
*  Globals: 
*  Returns: void 
*  Notes:
*
*  Changes: 
*******************************************************************************/
void set_correct_whacker_pos(int pos) {
    correct_whacker_pos = station == station_A ? pos + 8 : pos - 8;
}

/*******************************************************************************
*  Name: void set_correct_pos_to_seek()
*
*  Description: Sets the correct position of the senor the whacker needs to go to. 
*  This number is determined by the station
*
*  Inputs: 
*  Parameters:
*  Globals: 
*
*  Outputs:
*  Parameters:
*  Globals: 
*  Returns: void 
*  Notes:
*
*  Changes: 
*******************************************************************************/
void set_correct_pos_to_seek() {
    pos_to_seek = station == station_A ? gnoll_pos - 8 : gnoll_pos + 8;
} 

/*******************************************************************************
*  Name: void update_display();
*
*  Description: SUpdates the display with the correct score. Used only by the gnoller. 
*  Hits go on the left two digits of the display and misses go on the right two digits.
*
*  Inputs: 
*  Parameters:
*  Globals: 
*
*  Outputs:
*  Parameters:
*  Globals: 
*  Returns: void 
*  Notes:
*
*  Changes: 
*******************************************************************************/
void update_display() {
    int score = hit_count * 100 + miss_count;
    int_to_bcd_array(score, bcd_array);
    dsp_bcd(bcd_array);
}

/*******************************************************************************
*  Public Function Definitions: Function header comments for these functions
*  are in the header file
*******************************************************************************/
void play_as_gnoller() {
    int pos;
    while(volley_count < MAX_VOLLEY_COUNT) {
        //Needs to be increased by one due to how the algorithm works
        pos = pick_random_location() + 1;
        set_correct_whacker_pos(pos);
        move_to_sensor(pos);
        turn_on_laser();
        //Need to wait 50 ms before reading in order to ensure that the laser has turned on properly
        wait_ms(50);
        scan_phototransistors(false);
        illuminate_light(pos);
        //Initiating the gnoll timer to start the gnoll lifecycle
        gnoll_timer.reset();
        gnoll_timer.start();
        while(1) {
            scan_phototransistors(false);
            if(other_illuminated_sensor() == correct_whacker_pos) {
                ++hit_count;
                break;
            } else if(other_illuminated_sensor() != correct_whacker_pos && other_illuminated_sensor() != -1) {
                ++miss_count;
                break;
            } else if(gnoll_timer.read() > gnoll_lifetime) {
                ++miss_count;
                break;
            }
        }
        update_display();
        //Server side error for deluminating so I had to do it this way. Would nomrally use deluminate
        write_int_to_digit(0x0500, 0);
        turn_off_laser();
        ++volley_count;
        while(other_illuminated_sensor() != -1) {
            scan_phototransistors(false);
        }
    }
    return;
}

void play_as_whacker() {
    while(volley_count < MAX_VOLLEY_COUNT) {
        scan_phototransistors(false);
        //Keep scanning until the gnoller picks a target
        while((gnoll_pos = other_illuminated_sensor()) == -1) {
            scan_phototransistors(false);
        }
        set_correct_pos_to_seek();
        move_to_sensor(pos_to_seek);
        turn_on_laser();
        wait_ms(50);
        whacker_timer.reset();
        whacker_timer.start();
        illuminate_light(pos_to_seek);
        while(is_lit(gnoll_pos)) {
            scan_phototransistors(false);
        }
        //SERVER SIDE ERROR ON DELUMINATE FUNCTION SO I USED WRITE INT TO DIGIT UNTIL MBED FIXES THIS
        //deluminate_lights();
        write_int_to_digit(0x0500, 0);
        turn_off_laser();
        ++volley_count;
    }
    return;
}

void play_WaG() {
    configure_as1107();
    display_zeros();
    while(1) {
        while(!button_is_pressed(&start_button_2)) {
            if(button_is_pressed(&cal_button_2)) {
                wait_for_button_to_be_released(&cal_button_2);
                calibrate();
                pc_2.printf("calibrated\n");
                cal_status = CALIBRATED;
            }
            if(button_is_pressed(&user_button_2)) {
                wait_for_button_to_be_released(&user_button_2);
                run_tests();
            }
        }
        wait_for_button_to_be_released(&start_button_2);
        if(cal_status == NOT_CALIBRATED) {
            pc_2.printf("Error calibrating. Now Terminating\n");
            break;
        }
        if(match_cnt == 0) {
            hit_count = 0; 
            miss_count = 0; 
            update_display();
            ++match_cnt;
        }
        volley_count = 0;
        if((station == station_A && match_cnt == 1) || (station == station_B && match_cnt == 2)) {
            play_as_gnoller();
        } else {
            play_as_whacker();
        }
        ++match_cnt;
        if(match_cnt == 3) {
            match_cnt = 0;
        }    
    }
}


