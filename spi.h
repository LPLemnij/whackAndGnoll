/*******************************************************************************
*
*  EECS 397
*
*  File name: spi.h
*
*  Description: Header file for the spi driver 
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
#ifndef SPI_H
#define SPI_H
#include "mbed.h"

/*******************************************************************************
*  Public Constants: Accessible by any code that includes this header file
*******************************************************************************/
#define SPI_NO_ID 0
#define SPI_AS1107_ID 1107
#define SPI_DRV8806_ID 8806

struct spi_cfg {
    int spi_id; //ID should be unique for each slave type
    DigitalOut spi_nss; //The pin driving the slave select
    int spi_mode; //SPI mode needed by this slave
    int spi_freq; //SPI frequency needed by this slave
    int spi_no_bits; //No. of data bits to be transferred each send to the slave
};

/*******************************************************************************
*  Public Function Prototypes: These functions may be called by any code
*  that includes this header file
*******************************************************************************/

/*******************************************************************************
*  Name: spi_send(struct spi_cfg, int spi_data)
*
*  Description: Sends data to the correct spi device
*
*  Inputs:
*  Parameters: struct spi_cfg struct that contains metadata about correct spi device
*              int spi_data the code to send to the spi device defined in spi_cfg
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
void spi_send(struct spi_cfg, int spi_data);

#endif

