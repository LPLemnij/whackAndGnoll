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

/*******************************************************************************
*  Private Constants: Only accessible to code below this point in this file
*******************************************************************************/
#define DRV8806_SPI_NO_BITS 8
#define DRV8806_SPI_MODE 0
#define DRV8806_SPI_FREQ 1000000
#define STP_LEFT STP_CW
#define STP_RIGHT STP_CCW

/*******************************************************************************
*  Private Data: Only accessible to code below this point in this file
*******************************************************************************/
DigitalOut stp_nss(STP_DRV8806_NSS);
extern Serial pc;

struct spi_cfg drv_8806 {
    SPI_DRV8806_ID,
    stp_nss,
    DRV8806_SPI_MODE,
    DRV8806_SPI_FREQ,
    DRV8806_SPI_NO_BITS,
};
    
/*******************************************************************************
*  Public Function Definitions: Function header comments for these functions
*  are in the header file
*******************************************************************************/

void stp_init() {
    spi_send(drv_8806, 0x00);
}

void stp_step(int direction) {
    static int lookup[] = {0x03, 0x06, 0x0c, 0x09};
    static int i = 0; 
    if(direction == STP_CW) {
        if(i == 4) {
            i = 0;
        } else {
            i++;
        }
    } else {
        if(i == -1) {
            i = 3; 
        } else {
            i--;
        }
    }
    spi_send(drv_8806, lookup[i]);
    wait(.0015);
}

