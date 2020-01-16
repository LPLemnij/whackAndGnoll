/*******************************************************************************
*
*  EECS 397
*
*  File name: stepper.h
*
*  Description: Header file for the stepper driver 
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
#ifndef STEPPER_H
#define STEPPER_H
#include "mbed.h"

/*******************************************************************************
*  Public Constants: Accessible by any code that includes this header file
*******************************************************************************/
#define STP_CW 0
#define STP_CCW 1

/*******************************************************************************
*  Public Function Prototypes: These functions may be called by any code
*  that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Name: stp_init()
*
*  Description: Initiates the stepper motor 
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
void stp_init();

/*******************************************************************************
*  Name: stp_step(int direction)
*
*  Description: Sends data to the correct spi device
*
*  Inputs:
*  Parameters: int direction specifices which way the stepper should turn
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
void stp_step(int direction);

#endif


