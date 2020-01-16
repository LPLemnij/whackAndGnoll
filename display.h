/*******************************************************************************
*
*  EECS 397
*
*  File name: display.h
*
*  Description: Header file for the AS1107 display module 
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
#ifndef DISPLAY_H
#define DISPLAY_H

/*******************************************************************************
*  Public Constants: Accessible by any code that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Public Function Prototypes: These functions may be called by any code
*  that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Name: test_mode_on()
*
*  Description: Puts the as1107 into test mode where all segments are illuminated
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
void test_mode_on();

/*******************************************************************************
*  Name: test_mode_off()
*
*  Description: Takes the as1107 out of test mode
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
void test_mode_off();

/*******************************************************************************
*  Name: configure_as1107()
*
*  Description: Configures the as_1107 in accordance to the display.cpp file
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
void configure_as1107();

/*******************************************************************************
*  Name: display_zeros()
*
*  Description: Displays all 0's on the as1107
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
void display_zeros();

/*******************************************************************************
*  Name: dsp_bcd (int *bcd_array)
*
*  Description: Display the elements of a bcd array to the segment display
*
*  Inputs: 
*  Parameters: int *bcd_array The array from which to read digits from
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
void dsp_bcd(int *bcd_array);

/*******************************************************************************
*  Name: int_to_bcd_array(int num, int *bcd_array)
*
*  Description: Convers an input number to bcd representation
*
*  Inputs: 
*  Parameters: int *bcd_array The array where the bcd representation is written
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
void int_to_bcd_array(int num, int *bcd_array);

/*******************************************************************************
*  Name: void write_int_to_digit
*
*  Description: Writes an input int to the desired digit
*
*  Inputs: 
*  Parameters: int digit The digit number to write to
*              int number The number to be written
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
void write_int_to_digit(int digit, int number);

#endif