/*******************************************************************************
* File Name: FRAM_I2C.h
*
* Version: 1.0
*
* Description:
*  This is header file for F-RAM I2C APIs provided with the dev kit CY15FRAMKIT-001
*  The APIs include initialization of block, write, current read and random read
*  from F-RAM
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#if !defined(FRAM_I2C_H)
#define FRAM_I2C_H

#include <cytypes.h>

// This points to the density selected by the user config
#define FRAM_I2C_i2c_density         1

// Density index
#define i2c_1MBit    (1u)
#define i2c_512KBit  (2u)
#define i2c_256KBit  (3u)
#define i2c_64KBit   (4u)

#define NO_OF_ADDRBYTES  2

// Null pointer
#define NULL_PTR         ((uint8_t*) 0u)

/* Master API returns */
#define FRAM_I2C_MSTR_NO_ERROR          FRAM_I2C_I2C_I2C_MSTR_NO_ERROR         /* Function complete without error                       */
#define FRAM_I2C_MSTR_ERR_ARB_LOST      FRAM_I2C_I2C_I2C_MSTR_ERR_ARB_LOST     /* Master lost arb: INTR_MASTER_I2C_ARB_LOST             */
#define FRAM_I2C_MSTR_ERR_LB_NAK        FRAM_I2C_I2C_I2C_MSTR_ERR_LB_NAK       /* Last Byte Naked: INTR_MASTER_I2C_NACK                 */
#define FRAM_I2C_MSTR_NOT_READY         FRAM_I2C_I2C_I2C_MSTR_NOT_READY        /* Master on the bus or Slave operation is in progress   */
#define FRAM_I2C_MSTR_BUS_BUSY          FRAM_I2C_I2C_I2C_MSTR_BUS_BUSY         /* Bus is busy, process not started                      */
#define FRAM_I2C_MSTR_ERR_ABORT_START   FRAM_I2C_I2C_I2C_MSTR_ERR_ABORT_START  /* Slave was addressed before master begin Start gen     */
#define FRAM_I2C_MSTR_ERR_BUS_ERR       FRAM_I2C_I2C_I2C_MSTR_ERR_BUS_ERR      /* Bus eror has: INTR_MASTER_I2C_BUS_ERROR               */
#define FRAM_I2C_MSTR_ERR               (0xFF)                                         /* Other Errors                                          */

// I2C Communication Timeout at 1000us = 1ms
#define I2C_COM_TIMEOUT  (1000u)

// Masks
#define LSBIT_MASK ((uint8)1)
#define MSB_ADDR_MASK ((uint32)0x010000)    /* upto 1 Mbit */
#define ISB_ADDR_MASK ((uint32)0x00FF00)
#define MSB_ADDR_SHIFTBITS ((uint8)16)
#define ISB_ADDR_SHIFTBITS ((uint8)8)

// A16 Address bit value
#define A16_ADDR_BIT(addr)  ((uint8)((addr & MSB_ADDR_MASK)>>MSB_ADDR_SHIFTBITS) & LSBIT_MASK)

// Second byte in 3-byte address
#define ISB_ADDR_BYTE(addr) ((uint8)((addr & ISB_ADDR_MASK)>>ISB_ADDR_SHIFTBITS))
    
// LSB byte
#define LSB_ADDR_BYTE(addr) ((uint8)(addr))    

// Initialization Function
extern void   FRAM_I2C_Init  ( void );

// I2C Write Function
extern uint32  FRAM_I2C_Write ( uint8, uint32 , uint8* , uint32 );

// I2C Current Read Function
extern uint32  FRAM_I2C_Current_Read  ( uint8, uint8* , uint32 );

// I2C Random Read Function
extern uint32  FRAM_I2C_Random_Read  ( uint8, uint32 , uint8* , uint32 );

#endif // End of FRAM_I2C_H where FRAMI2C is the component name FRAM_I2C
//[] END OF FILE
