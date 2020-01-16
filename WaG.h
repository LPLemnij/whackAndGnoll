/*******************************************************************************
*
*  EECS 397
*
*  File name: WaG.h
*
*  Description: Header file for WaG module 
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
#ifndef WAG_H
#define WAG_H

/*******************************************************************************
*  Public Function Prototypes: These functions may be called by any code
*  that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Name: play_as_gnoller()
*
*  Description: Allows the current station to play as the gnoller
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
void play_as_gnoller();

/*******************************************************************************
*  Name: play_as_gnoller()
*
*  Description: Allows the current station to play as the whacker
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
void play_as_whacker();

/*******************************************************************************
*  Name: play_WaG()
*
*  Description: Function to play the game as it was designed. In other words, 
*  station A starts as being the gnoller, station B as the whacker and the game
*  continues according to the design document
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
void play_WaG();
#endif