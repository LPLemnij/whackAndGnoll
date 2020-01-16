/*******************************************************************************
*  EECS 397
*
*  File name: testing.cpp
*
*  Description: Routines for the testing framework
*
*  Notes:
*
*  Author(s): Lemnij, Luca
*
*  Created: 2/23/2019
*  Last Modified: 
*
*  Changes:
*
*******************************************************************************/
#include "mbed.h"
#include "display.h"
#include "io_pins.h"
#include "testing.h"
#include "carriage.h"

/*******************************************************************************
*  Private Constants: Only accessible to code below this point in this file
*******************************************************************************/
#define BAUD_RATE 230400
/*******************************************************************************
*  Private Data: Only accessible to code below this point in this file
*******************************************************************************/
//User button on the nucleo board(blue button)
InterruptIn user_button(BUTTON1);

//Console output though USB
Serial pc(USBTX, USBRX, BAUD_RATE);

//Button was pressed flag
int button_pressed_flag = 0;

//Timer for switch debouncing
Timer debounce;

//Array containing bit values for turning on one led at a time
int test_values[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

//Switching from 0 to 1 turns the laser on and 1 to 0 off
DigitalOut laser_out(LZR_ENABLE);

//Used to read the status of the start button
DigitalIn start_button(UI_START_BUTTON);

//Used to read the status of the jog left button
DigitalIn jog_left_button(UI_JOG_LEFT_BUTTON, PullUp);

//Used to read the status of the jog right button
DigitalIn jog_right_button(UI_JOG_RIGHT_BUTTON, PullUp);

//Used to read the status of the cal button
DigitalIn cal_button(UI_CAL_BUTTON, PullUp);

//Used to read the status of the win button(it is called spare in the io_pins file but is the win button on the board)
DigitalIn win_button(UI_SPARE, PullUp);

//Used to read the status of the home sensor
DigitalIn home_sensor_switch(STP_HOME_SENSOR, PullUp);

//Used to read the station select bit to determine which station we are at
DigitalIn station_select_jumper(UI_STATION_SELECT);

BusOut pt_multiplexor_testing(ANA_MUX_S0, ANA_MUX_S1, ANA_MUX_S2, ANA_MUX_S3);

AnalogIn ptransistor_value_testing(ANA_MUX_OUT);


/*******************************************************************************
*  Private Function Prototypes: These functions may only be called by code
*  below this point in this file
*******************************************************************************/
void wait_until_button_pressed_and_released();
void set_flag();
void reset_flag();

/*******************************************************************************
*  Name: set_flag()
*
*  Description: Sets the button pressed and released flag to 1 after debouncing button 
*  This is used as an interrupt routine.
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

void set_flag() {
    if(debounce.read_ms() > 5) {
        button_pressed_flag = 1;
        debounce.reset();
    }
}

/*******************************************************************************
*  Name: reset_flag()
*
*  Description: Resets the flag value back to 0. Needs to be used at the end of 
*  every test to ensure none are skipped incorrectly.
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
void reset_flag() {
    button_pressed_flag = 0;
}

/*******************************************************************************
*  Name: wait_until_button_pressed()
*
*  Description: Scans the button_pressed_flag and breaks out of the waiting loop
*  once the flag is set and the button has been pressed. 
*  
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
void wait_until_button_pressed_and_released() {
    while(1) {
        wait(1);
        if(button_pressed_flag) {
            break;
        }
    }
}

/*******************************************************************************
*  Public Function Definitions: Function header comments for these functions
*  are in the header file
*******************************************************************************/

void display_welcome() {
    //Start the debounce timer to help interrupts debounce
    debounce.start();
    //Bind the set flag function as an ISR so that the button_pressed flag is set
    //any time someone pushes a button
    user_button.fall(&set_flag);
    pc.printf("Welcome to the WaG test framework\n");
    display_zeros();
    wait_until_button_pressed_and_released();
    reset_flag();
}

void run_display_test() {
    pc.printf("Display test running\n");
    test_mode_on();
    wait_until_button_pressed_and_released();
    test_mode_off();
    display_zeros();
    reset_flag();
}

void run_target_board_LED_test() {
    //Index to keep track of what test value we are writing
    int test_values_index = 0;
    pc.printf("Target board LED test running\n");
    //Only run this test until the button has been pressed and released
    while(!button_pressed_flag) {
        //We want to only write to the fifth digit for testing purposes.
        //We use the modulus operator to make sure the test keeps cycling
        write_int_to_digit(0x0500, test_values[test_values_index % 8]);
        test_values_index++;
        //.1 seconds is 100ms
        wait(.1);
    }
    //Turn the LED's off
    write_int_to_digit(0x0500, 0);
    reset_flag();
}

void run_laser_test() {
    pc.printf("Laser test running\n");
    //Only run this test until the button has been pressed and released
    while(!button_pressed_flag) {
        laser_out = 1;
        //Leave laser on for .5 seconds
        wait(.5);
        laser_out = 0;
        //Leave it off for .5 seconds
        wait(.5);
    }
    reset_flag();
}

void run_phototransistor_test() {
    pc.printf("Phototransistor test running\n");
    //Only run this test until the button has been pressed and released
    while(!button_pressed_flag) {
        for(int i = 0; i < 16; i++) {
            //Selecting the phototransistors in the right order
            pt_multiplexor_testing = i;
            wait(.5);
            i == 15 ? pc.printf("%.2f\n", ptransistor_value_testing.read() * 3.3) : pc.printf("%.2f,", ptransistor_value_testing.read() * 3.3);
        }
    }
    reset_flag();
}   

void run_pushbutton_test() {
    pc.printf("Pushbutton Test Running\n");
    char station;
    if(station_select_jumper.read()) {
        station = 'A';
    } else {
        station = 'B';
    }
    while(!button_pressed_flag) {
        pc.printf("Start Button: %d Jog left: %d, Jog Right: %d, Cal: %d, Win: %d, Home Sensor: %d, Station: %c\n", !start_button.read(), !jog_left_button.read(), !jog_right_button.read(), !cal_button.read(), !win_button.read(), !home_sensor_switch, station);
        wait(.5);
    }
    reset_flag();
}

void run_stepper_test() {
    pc.printf("Stepper test running\n");
    turn_on_laser();
    move_to_home();
    while(!button_pressed_flag) {   
        use_buttons_to_move_carriage();   
    }
    turn_off_laser();
    reset_flag();
}   

void run_calibration_test() {
    pc.printf("Calibration test running\n");
    calibrate();
    wait_until_button_pressed_and_released();
    reset_flag();
}

void illuminate_light(int pos) {
    write_int_to_digit(0x0500, test_values[(pos - 1) % 8]);
}

void delluminate_lights() {
    write_int_to_digit(0x0500, 0);
}
    
void run_repeat_test() {
    laser_out = 1;
    int count = 5;
    if(get_status()) {
        pc.printf("Repeatibility test running\n");
        while(count > 0 && !button_pressed_flag) {
            move_to_home();
            //Read 8th ptransistor which is the closest one
            pt_multiplexor_testing = 7;
            move_to_sensor(8);
            //Print the value of the 8th sensor
            pc.printf("Sensor 8: %0.2f\n", ptransistor_value_testing.read() * 3.3);
            //Read the value of the 1st ptransistor which is the farthest one
            pt_multiplexor_testing = 0; 
            move_to_sensor(1); 
            //Print the value of the first sensor
            pc.printf("Sensor 1: %0.2f\n", ptransistor_value_testing.read() * 3.3);
            move_past_last_sensor();
            move_to_sensor(1);
            //Print the value of the 1st sensor after the carriage moved away
            pc.printf("Sensor 1: %0.2f\n", ptransistor_value_testing.read() * 3.3);
            move_to_sensor(8);
            //Read
            pt_multiplexor_testing = 7;
            //Print the value of the 8th sensor
            pc.printf("Sensor 8: %0.2f\n", ptransistor_value_testing.read() * 3.3);
            count--;
        }
        move_to_home();
        laser_out = 0;
        reset_flag();
    }
}

void run_tests() {
    display_welcome();
    run_display_test();
    run_target_board_LED_test();
    run_laser_test();
    run_phototransistor_test();
    run_pushbutton_test();
    run_stepper_test();
    run_calibration_test();
    run_repeat_test();
}        