/*******************************************************************************
*
*  EECS 397
*
*  File name: testing.h
*
*  Description: Header file for the testing framework 
*
*  Notes:
*
*  Author(s): Lemnij, Luca
*
*  Created: 3/28/2019
*  Last Modified: 
*
*  Changes:
*
*******************************************************************************/
#ifndef TESTING_H
#define TESTING_H

/*******************************************************************************
*  Public Constants: Accessible by any code that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Public Function Prototypes: These functions may be called by any code
*  that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Name: display_welcome()
*
*  Description: Displays a welcome message and 0000 to the seven segment display
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
void display_welcome();

/*******************************************************************************
*  Name: run_display_test()
*
*  Description: Runs a display test which first indicates to the console that the
*  test is running and then lights all 8 LEDs and all segments on the segment 
*  display(including decimal points). 
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
void run_display_test();

/*******************************************************************************
*  Name: run_traget_board_LED_test()
*
*  Description: Runs a target board LED test which first indicates to the console 
*  that the test is running then cycles through lighting individual LEDs on the 
*  target board until the user button is pushed and released 
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
void run_target_board_LED_test();

/*******************************************************************************
*  Name: run_laser_test()
*
*  Description: Runs a laser test which first indicates to the console that the test
*  is running then cycles through turning the laser on for .5 seconds and turning
*  it off for .5 seconds until the user button is pushed and released.
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
void run_laser_test();

/*******************************************************************************
*  Name: run_phototransistor_test()
*
*  Description: Runs a phototransistor test which first indicates to the console 
*  that the test is running and then reads the values of all phototransistors and 
*  prints all values of the phototransistors to the console(scaled to volts).  
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
void run_phototransistor_test();

/*******************************************************************************
*  Name: run_pushbutton_test()
*
*  Description: Runs a pushbutton test which first indicates to the console that 
*  the test is running and then reads and prints the value of the following buttons: 
*  jog left, jog right, cal, win, and the station select jumper.
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
void run_pushbutton_test();

/*******************************************************************************
*  Name: run_stepper_test()
*
*  Description: Runs a stepper test which first indicates to the console that 
*  the test is running and then allows the tester to move the carriage around 
*  while scanning photo transistors. 
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
void run_stepper_test();

/*******************************************************************************
*  Name: run_calibration_test()
*
*  Description: Runs a calibration test which first indicates to the console that
*  the test is running and then calculates the positions of each photoresistor.
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
void run_calibration_test();

/*******************************************************************************
*  Name: run_repeatability_test()
*
*  Description: Runs a repeatability test
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
void run_repeat_test();

/*******************************************************************************
*  Name: run_tests()
*
*  Description: Runs tbe testing framework of the wag machine
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
void run_tests();

/*******************************************************************************
*  Name: illuminate_light(int pos)
*
*  Description: Illuminate the LED at an input position
*
*  Inputs: int pos position of led to light up
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
void illuminate_light(int pos);

//Turns off indicators CAN'T USE RIGHT NOW BECAUSE OF MBED ERROR L6320W SOMETHING WRONG SERVER SIDE
/*******************************************************************************
*  Name: deluminate_light
*
*  Description: Deluminates the LED at an input position
*
*  Inputs: int pos position of led to turn off
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
void deluminate_lights();
#endif

