/*******************************************************************************
*  EECS 397
*
*  File name: display.cpp
*
*  Description: Routines to control the display module
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
#include "display.h"
#include "io_pins.h"
#include "spi.h"

/*******************************************************************************
*  Private Constants: Only accessible to code below this point in this file
*******************************************************************************/
#define DSP_NORM_OP 0x0c01
#define DSP_SCAN_LIMIT 0x0b04
#define DSP_DECODE_MASK 0x090F
#define DSP_MAX_INTENSITY 0x0a0f
#define DSP_TST_ON 0x0f01
#define DSP_TST_OFF 0x0f00
#define VERSION1
#define AS1107_SPI_NO_BITS 16
#define AS1107_SPI_MODE 0
#define AS1107_SPI_FREQ 1000000
//#define VERSION2

/*******************************************************************************
*  Private Data: Only accessible to code below this point in this file
*******************************************************************************/
int digit_arr[] = {0x0400, 0x0300, 0x0200, 0x100};

DigitalOut dsp_nss(DSP_AS1107_NSS);

struct spi_cfg as_1107 {
    SPI_AS1107_ID,
    dsp_nss,
    AS1107_SPI_MODE,
    AS1107_SPI_FREQ,
    AS1107_SPI_NO_BITS,
};

/*******************************************************************************
*  Private Function Prototypes: These functions may only be called by code
*  below this point in this file
*******************************************************************************/
void write_correctly(int code);

/*******************************************************************************
*  Name: Private function write_correctly(int code)
*
*  Description: writes input datat to the 1107
*
*  Inputs:
*  Parameters: code hexadecimal code to be written to the as_1107
*  Globals:
* 
*  Outputs:
*  Parameters:
*  Globals:
*  Returns: void
*
*  Notes:
*
*  Changes:
*
*******************************************************************************/
void write_correctly(int code) {
    spi_send(as_1107, code);
}

/*******************************************************************************
*  Name: Private function write_correctly(int code)
*
*  Description: Turns all elements of an input bcd array to 0
*
*  Inputs:
*  Parameters: bcd_array a pointer to an int array that represents bcd digits
*  Globals:
* 
*  Outputs:
*  Parameters:
*  Globals:
*  Returns: void
*
*  Notes:
*
*  Changes:
*
*******************************************************************************/
void zero_bcd(int *bcd_array) {
    for(int i = 0; i < 4; i++) {
        bcd_array[i] = 0;
    }
}

/*******************************************************************************
*  Public Function Definitions: Function header comments for these functions
*  are in the header file
*******************************************************************************/

void test_mode_on() {
    write_correctly(DSP_TST_ON);
}

void test_mode_off() {
    write_correctly(DSP_TST_OFF);
}

void display_zeros() {
    for(int i = 0; i < 4; i++) {
        write_correctly(digit_arr[i]);
    }
}

void configure_as1107() {
    write_correctly(DSP_NORM_OP);
    write_correctly(DSP_SCAN_LIMIT);
    write_correctly(DSP_DECODE_MASK);
    write_correctly(DSP_MAX_INTENSITY);
}

void dsp_bcd(int *bcd_array) {
    for(int i = 3; i >= 0; i--) {
        write_correctly(digit_arr[i] + bcd_array[i]);
    }
}

void write_int_to_digit(int digit, int number) {
    write_correctly(digit + number);
}

#ifdef VERSION1
void int_to_bcd_array(int num, int *bcd_array) {
    zero_bcd(bcd_array);
    for(int i = 3; num != 0; i--) {
        bcd_array[i] = num % 10;
        num /= 10;
    }
}
#endif

#ifdef VERSION2
void int_to_bcd_array(int num, int *bcd_array) {
    zero_bcd(bcd_array);
    char temp_str[5];
    char c;
    sprintf(temp_str, "%d", num);
    int offset = 4 - strlen(temp_str);
    for(int i = 0; (c = temp_str[i]) != '\0'; i++) {
        bcd_array[offset] = c - 0x30;
        offset++;
    }
}

#endif
