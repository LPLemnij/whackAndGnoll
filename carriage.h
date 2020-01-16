/*******************************************************************************
*
*  EECS 397
*
*  File name: carriage.h
*
*  Description: Header file for the laser carriage module 
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
#ifndef CARRIAGE_H
#define CARRIAGE_H

/*******************************************************************************
*  Public Constants: Accessible by any code that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Public Function Prototypes: These functions may be called by any code
*  that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Name: move_to_home()
*
*  Description: Moves the carriage to the home position
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
void move_to_home();

/*******************************************************************************
*  Name: scan_phototransistors_and_turn_on_laser(bool print)
*
*  Description: Scans appropriate photo transistors and turns on the correct laser
*  depending on station
*
*  Inputs: 
*  Parameters: bool print if true it will print the result to the console
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
void scan_phototransistors(bool print);

/*******************************************************************************
*  Name: use_buttons_to_move_carriage()
*
*  Description: Moves the carriage in accordance to the push button pressed. Logic
*  for push buttons is inversed so !jog_right means that the button is actually pressed
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
void use_buttons_to_move_carriage();

/*******************************************************************************
*  Name: calibrate()
*
*  Description: Determines where each photo transistor is relative to the home position
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
void calibrate();

/*******************************************************************************
*  Name: move_to_sensor(int sensor)
*
*  Description: Moves the carriage to an input sensor
*  Inputs: int sensor represents the sensor number on the board
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
void move_to_sensor(int sensor);

/*******************************************************************************
*  Name: move_past_last_sensor(int distance)
*
*  Description: Moves the carriage 100 steps past the furthest sensor to aid in 
*  repeatability test
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
void move_past_last_sensor();

/*******************************************************************************
*  Name: get_status()
*
*  Description: returns whether the game is calibrated or not
*  Parameters: 
*  Globals: 
*
*  Outputs:
*  Parameters:
*  Globals: 
*  Returns: bool status the value of status. true if calibrated, false if not
*  Notes:
*
*  Changes: 
*******************************************************************************/
bool get_status();

//int *getPtransistorPosArray();

//Checks if an input sensor is hit
bool is_lit(int pos);

//Turns off the laser
void turn_off_laser();

//Turns on the laser
void turn_on_laser();
#endif