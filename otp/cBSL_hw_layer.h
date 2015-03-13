/* --COPYRIGHT--
 * See LICENCE File
 * --/COPYRIGHT--*/

#ifndef ARRAY_SAFE_H
#define ARRAY_SAFE_H

#include <stdint.h>
#include <msp430.h>
#include "msp430-OTP/otp/cBSL_serial.h"

#define DEBG_INPUT_IN   0x0001

// image status flag is stored in the INFO B area

// Image Status
#define STAT_NONE           0x00EE
#define STAT_DONWLOAD       0x00CC
#define STAT_PENDING_VALID  0xFF88

#define INFO_B_PTR          0x1900
#define IMG_STAT_PTR        0x1900
#define C_INIT00_VECTOR     0x1901
#define BSL_VECTOR          0x1000

#pragma SET_DATA_SECTION(".BSL")
#pragma SET_CODE_SECTION(".BSL")

extern uint16_t g_hooks;
extern ui8_array cBSL_SerialRX;

/**
 * Init System IO
 */
void cBSL_init();

/**
 * Output single char to the uart port
 * @param data byte to output
 */
void cBSL_putch(uint8_t data);

/**
 * Erase Flash Memory
 * @param address pointer into the flash segment to be erased.
 * @param mode    ERASE - for segment erase or
 *                MERAS - for Bank Erase
 *
 * Note: ERASE and MERAS are defind in msp430.h.  The code sequence is from
 * TI MSP430x5xx Family Users Guide section "Initiating Erase From Flash"
 */
inline void cBSL_flash_erase(uint8_t* flash_ptr, uint32_t mode);

/**
 *  Write to Flash
 *  @param data_ptr from
 *  @param flash_ptr to
 *  @param count Quantity of double words to copy
 */
void cBSL_flash_write32(uint32_t* data_ptr,
              uint32_t* flash_ptr,
              unsigned int count);

/**
 * Set the image status
 * @param img_stat New Image Status.
 */
void cBSL_set_info_b(uint16_t value, unsigned int offset);

#pragma SET_DATA_SECTION()
#pragma SET_CODE_SECTION()

#endif
