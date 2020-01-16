/*******************************************************************************
*
*  EECS 397
*
*  File name: io_pins.h
*
*  Description: Header file for the AS1107 pins 
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
#ifndef IO_PINS_H
#define IO_PINS_H

/*******************************************************************************
*  Public Constants: Accessible by any code that includes this header file
*******************************************************************************/

#define LZR_ENABLE PB_5
#define STP_HOME_SENSOR PE_11
#define STP_DRV8806_NSS PA_15
#define DSP_AS1107_NSS PC_7
#define ANA_MUX_S0 PC_6
#define ANA_MUX_S1 PB_15
#define ANA_MUX_S2 PB_13
#define ANA_MUX_S3 PB_12
#define ANA_MUX_OUT PB_1
#define UI_CAL_BUTTON PG_9
#define UI_START_BUTTON PG_14
#define UI_STATION_SELECT PF_15
#define UI_JOG_LEFT_BUTTON PE_13
#define UI_JOG_RIGHT_BUTTON PF_14
#define UI_SPARE PB_3
#define SPI_SCLK PA_5
#define SPI_MOSI PA_7
#define SPI_MISO PA_6
#define EXP_NSS PA_4

#endif