/*******************************************************************************
*  EECS 397
*
*  File name: spi.cpp
*
*  Description: Routines to control the spi driver
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
#include "spi.h"
#include "io_pins.h"

/*******************************************************************************
*  Private Data: Only accessible to code below this point in this file
*******************************************************************************/
SPI wag_spi(SPI_MOSI, SPI_MISO, SPI_SCLK);

/*******************************************************************************
*  Public Function Definitions: Function header comments for these functions
*  are in the header file
*******************************************************************************/

void spi_send(struct spi_cfg spi, int spi_data){
    static int previous_id = SPI_NO_ID;
    spi.spi_nss = 1;
    if(spi.spi_id != previous_id) {
        wag_spi.format(spi.spi_no_bits, spi.spi_mode);
        wag_spi.frequency(spi.spi_freq);
    }
    previous_id = spi.spi_id;
    spi.spi_nss = 0;
    wag_spi.write(spi_data);
    spi.spi_nss = 1;
}
    
    