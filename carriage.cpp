/*******************************************************************************
*  EECS 397
*
*  File name: stepper.cpp
*
*  Description: Routines to control the stepper module
*
*  Notes:
*
*  Author(s): Lemnij, Luca
*
*  Created: 2/28/2019
*  Last Modified: 
*
*  Changes:
*
*******************************************************************************/
#include "mbed.h"
#include "io_pins.h"
#include "spi.h"
#include "stepper.h"
#include "carriage.h"

/*******************************************************************************
*  Private Constants: Only accessible to code below this point in this file
*******************************************************************************/

#define STP_LEFT STP_CW
#define STP_RIGHT STP_CCW
#define CALIBRATED 1
#define NOT_CALIBRATED 0
#define STP_POSITION_UNKNOWN -1
#define STP_MAXIMUM_POSITION_LIMIT 6296
#define HOME 0

/*******************************************************************************
*  Private Data: Only accessible to code below this point in this file
*******************************************************************************/

DigitalIn home_sensor_flag(STP_HOME_SENSOR, PullUp);
extern Serial pc;

DigitalOut laser(LZR_ENABLE);

DigitalIn station_select(UI_STATION_SELECT);

//Used to read the status of the jog left button
DigitalIn jog_left(UI_JOG_LEFT_BUTTON, PullUp);

//Used to read the status of the jog right button
DigitalIn jog_right(UI_JOG_RIGHT_BUTTON, PullUp);

int start_index;
int end_index;
    
//Get the multiplexor so we can read values
BusOut pt_multiplexor(ANA_MUX_S0, ANA_MUX_S1, ANA_MUX_S2, ANA_MUX_S3);
AnalogIn ptransistor_value(ANA_MUX_OUT);


//Stores the values of each phototransistor
float ptransistor_array[16];

//Stores the positions of each phototransistor as steps away from home
int ptransistor_pos_array[] = {STP_POSITION_UNKNOWN, STP_POSITION_UNKNOWN, STP_POSITION_UNKNOWN, STP_POSITION_UNKNOWN, STP_POSITION_UNKNOWN, STP_POSITION_UNKNOWN, STP_POSITION_UNKNOWN, STP_POSITION_UNKNOWN};

//Stores the current position of the carriage
int carriage_pos;

//Stores whether the WaG is calibrated
bool status = NOT_CALIBRATED;

//Stores the distance to move. Used in the move_to_sensor function
int distance_to_move;
/*******************************************************************************
*  Private Function Prototypes: These functions may only be called by code
*  below this point in this file
*******************************************************************************/

void step_right();
void step_left();

/*******************************************************************************
*  Name: step_right()
*
*  Description: Moves the carriage right one step
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
void step_right() {
    if(home_sensor_flag) {
        stp_step(STP_RIGHT);
        if(carriage_pos != STP_POSITION_UNKNOWN) {
            carriage_pos--;
        }
    }
}

/*******************************************************************************
*  Name: step_left()
*
*  Description: Moves the carriage left one step
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
void step_left() {
    if(carriage_pos != STP_POSITION_UNKNOWN && carriage_pos < STP_MAXIMUM_POSITION_LIMIT) {
        stp_step(STP_LEFT);
        carriage_pos++;
    }
    if(carriage_pos >= STP_MAXIMUM_POSITION_LIMIT) {
        pc.printf("Warning: Distance limit reached. Cannot step left.\n");
    }
}

/*******************************************************************************
*  Public Function Definitions: Function header comments for these functions
*  are in the header file
*******************************************************************************/

void move_to_home() {
    if(!home_sensor_flag) {
        for(int i = 0; i < 100; i++) {
            step_left();
            wait(.001);
        }
    }
    if(!home_sensor_flag) {
        pc.printf("Error: Home sensor still on after moving left\n");
        return;
    }
    while(home_sensor_flag) {
        step_right();
    }
    carriage_pos = HOME;
    pc.printf("Home position found\n");
}

void scan_phototransistors(bool print) {
    //Scanning the appropriate photoresistors
    for(int i = 0; i < 16; i++) {
        //Selecting the phototransistors in the right order
        pt_multiplexor = i;
        wait_us(50);
        ptransistor_array[i] = ptransistor_value.read();
    }
    
    if(print) {
        for(int i = 0; i < 16; i++) {
            pc.printf("%0.2f,", ptransistor_array[i] * 3.3);
        }
    }
}

bool is_lit(int pos) {
    if(ptransistor_array[pos - 1] * 3.3 >= .5) {
        return true;
    } else {
        return false;
    }
}
    
void use_buttons_to_move_carriage() {
    while(jog_right && !jog_left) {
        step_left();
    }
    scan_phototransistors(true);
    while(jog_left && !jog_right) {
        step_right();
    }
}

void calibrate() {
    laser = 1;
    move_to_home();
    //Stores the previous reading of an arbitrary phototransistor in order to find peak brightness
    float last_reading;
    //If station A
    if(station_select.read()) {
        //First photo transistor to be scanned(on the bottom left PT 1)
        start_index = 0;
        //Last photo transistor to be scanned(on the bottom right PT 8)
        end_index = 7;
    } else {
        start_index = 8;
        end_index = 15;
    }
    
    for(int i = end_index; i >= start_index; i--) {
        pt_multiplexor = i;
        wait_us(10);
        while(ptransistor_value.read() >= last_reading - .05) {
            wait_us(10);
            if(ptransistor_value.read() * 3.3 >= 2) {
                last_reading = ptransistor_value.read();
            }
            step_left();
        }
        wait_ms(100);
        ptransistor_pos_array[i % 8] = carriage_pos;
        last_reading = 0;
    }

    laser = 0;
    move_to_home();
    pc.printf("%d, %d, %d, %d, %d, %d, %d, %d\n", ptransistor_pos_array[0],ptransistor_pos_array[1],ptransistor_pos_array[2],ptransistor_pos_array[3],ptransistor_pos_array[4],ptransistor_pos_array[5],ptransistor_pos_array[6],ptransistor_pos_array[7]);
    pc.printf("%d, %d, %d, %d, %d, %d, %d\n", ptransistor_pos_array[1] - ptransistor_pos_array[0], ptransistor_pos_array[2] - ptransistor_pos_array[1], ptransistor_pos_array[3] - ptransistor_pos_array[2], ptransistor_pos_array[4] - ptransistor_pos_array[3], ptransistor_pos_array[5] - ptransistor_pos_array[4], ptransistor_pos_array[6] - ptransistor_pos_array[5], ptransistor_pos_array[7] - ptransistor_pos_array[6]);
    status = CALIBRATED;
}

void move_to_sensor(int sensor) {
     distance_to_move = ptransistor_pos_array[(sensor - 1) % 8] - carriage_pos;
     while(distance_to_move != 0) {
        if(distance_to_move < 0) {
            step_right();
            distance_to_move++;
        } else {
            step_left();
            distance_to_move--;
        }
    }
    wait_ms(100);
}

void move_past_last_sensor() {
    move_to_sensor(1);
    for(int i = 0; i < 100; i++) {
        step_left();
    }
}

bool get_status() {
    return status;
}

int *getPtransistorPosArray() {
    return ptransistor_pos_array;
}

void turn_off_laser() {
    laser = 0;
}

void turn_on_laser() {
    laser = 1;
}
            
        
                
    


    