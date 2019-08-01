/*******************************************************************************
* File Name: FRAM_I2C_I2C_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_FRAM_I2C_I2C_SCBCLK_H)
#define CY_CLOCK_FRAM_I2C_I2C_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void FRAM_I2C_I2C_SCBCLK_StartEx(uint32 alignClkDiv);
#define FRAM_I2C_I2C_SCBCLK_Start() \
    FRAM_I2C_I2C_SCBCLK_StartEx(FRAM_I2C_I2C_SCBCLK__PA_DIV_ID)

#else

void FRAM_I2C_I2C_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void FRAM_I2C_I2C_SCBCLK_Stop(void);

void FRAM_I2C_I2C_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 FRAM_I2C_I2C_SCBCLK_GetDividerRegister(void);
uint8  FRAM_I2C_I2C_SCBCLK_GetFractionalDividerRegister(void);

#define FRAM_I2C_I2C_SCBCLK_Enable()                         FRAM_I2C_I2C_SCBCLK_Start()
#define FRAM_I2C_I2C_SCBCLK_Disable()                        FRAM_I2C_I2C_SCBCLK_Stop()
#define FRAM_I2C_I2C_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    FRAM_I2C_I2C_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define FRAM_I2C_I2C_SCBCLK_SetDivider(clkDivider)           FRAM_I2C_I2C_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define FRAM_I2C_I2C_SCBCLK_SetDividerValue(clkDivider)      FRAM_I2C_I2C_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define FRAM_I2C_I2C_SCBCLK_DIV_ID     FRAM_I2C_I2C_SCBCLK__DIV_ID

#define FRAM_I2C_I2C_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define FRAM_I2C_I2C_SCBCLK_CTRL_REG   (*(reg32 *)FRAM_I2C_I2C_SCBCLK__CTRL_REGISTER)
#define FRAM_I2C_I2C_SCBCLK_DIV_REG    (*(reg32 *)FRAM_I2C_I2C_SCBCLK__DIV_REGISTER)

#define FRAM_I2C_I2C_SCBCLK_CMD_DIV_SHIFT          (0u)
#define FRAM_I2C_I2C_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define FRAM_I2C_I2C_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define FRAM_I2C_I2C_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define FRAM_I2C_I2C_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << FRAM_I2C_I2C_SCBCLK_CMD_DISABLE_SHIFT))
#define FRAM_I2C_I2C_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << FRAM_I2C_I2C_SCBCLK_CMD_ENABLE_SHIFT))

#define FRAM_I2C_I2C_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define FRAM_I2C_I2C_SCBCLK_DIV_FRAC_SHIFT (3u)
#define FRAM_I2C_I2C_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define FRAM_I2C_I2C_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define FRAM_I2C_I2C_SCBCLK_DIV_REG        (*(reg32 *)FRAM_I2C_I2C_SCBCLK__REGISTER)
#define FRAM_I2C_I2C_SCBCLK_ENABLE_REG     FRAM_I2C_I2C_SCBCLK_DIV_REG
#define FRAM_I2C_I2C_SCBCLK_DIV_FRAC_MASK  FRAM_I2C_I2C_SCBCLK__FRAC_MASK
#define FRAM_I2C_I2C_SCBCLK_DIV_FRAC_SHIFT (16u)
#define FRAM_I2C_I2C_SCBCLK_DIV_INT_MASK   FRAM_I2C_I2C_SCBCLK__DIVIDER_MASK
#define FRAM_I2C_I2C_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_FRAM_I2C_I2C_SCBCLK_H) */

/* [] END OF FILE */
