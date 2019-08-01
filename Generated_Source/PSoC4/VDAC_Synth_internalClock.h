/*******************************************************************************
* File Name: VDAC_Synth_internalClock.h
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

#if !defined(CY_CLOCK_VDAC_Synth_internalClock_H)
#define CY_CLOCK_VDAC_Synth_internalClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void VDAC_Synth_internalClock_StartEx(uint32 alignClkDiv);
#define VDAC_Synth_internalClock_Start() \
    VDAC_Synth_internalClock_StartEx(VDAC_Synth_internalClock__PA_DIV_ID)

#else

void VDAC_Synth_internalClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void VDAC_Synth_internalClock_Stop(void);

void VDAC_Synth_internalClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 VDAC_Synth_internalClock_GetDividerRegister(void);
uint8  VDAC_Synth_internalClock_GetFractionalDividerRegister(void);

#define VDAC_Synth_internalClock_Enable()                         VDAC_Synth_internalClock_Start()
#define VDAC_Synth_internalClock_Disable()                        VDAC_Synth_internalClock_Stop()
#define VDAC_Synth_internalClock_SetDividerRegister(clkDivider, reset)  \
    VDAC_Synth_internalClock_SetFractionalDividerRegister((clkDivider), 0u)
#define VDAC_Synth_internalClock_SetDivider(clkDivider)           VDAC_Synth_internalClock_SetDividerRegister((clkDivider), 1u)
#define VDAC_Synth_internalClock_SetDividerValue(clkDivider)      VDAC_Synth_internalClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define VDAC_Synth_internalClock_DIV_ID     VDAC_Synth_internalClock__DIV_ID

#define VDAC_Synth_internalClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define VDAC_Synth_internalClock_CTRL_REG   (*(reg32 *)VDAC_Synth_internalClock__CTRL_REGISTER)
#define VDAC_Synth_internalClock_DIV_REG    (*(reg32 *)VDAC_Synth_internalClock__DIV_REGISTER)

#define VDAC_Synth_internalClock_CMD_DIV_SHIFT          (0u)
#define VDAC_Synth_internalClock_CMD_PA_DIV_SHIFT       (8u)
#define VDAC_Synth_internalClock_CMD_DISABLE_SHIFT      (30u)
#define VDAC_Synth_internalClock_CMD_ENABLE_SHIFT       (31u)

#define VDAC_Synth_internalClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << VDAC_Synth_internalClock_CMD_DISABLE_SHIFT))
#define VDAC_Synth_internalClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << VDAC_Synth_internalClock_CMD_ENABLE_SHIFT))

#define VDAC_Synth_internalClock_DIV_FRAC_MASK  (0x000000F8u)
#define VDAC_Synth_internalClock_DIV_FRAC_SHIFT (3u)
#define VDAC_Synth_internalClock_DIV_INT_MASK   (0xFFFFFF00u)
#define VDAC_Synth_internalClock_DIV_INT_SHIFT  (8u)

#else 

#define VDAC_Synth_internalClock_DIV_REG        (*(reg32 *)VDAC_Synth_internalClock__REGISTER)
#define VDAC_Synth_internalClock_ENABLE_REG     VDAC_Synth_internalClock_DIV_REG
#define VDAC_Synth_internalClock_DIV_FRAC_MASK  VDAC_Synth_internalClock__FRAC_MASK
#define VDAC_Synth_internalClock_DIV_FRAC_SHIFT (16u)
#define VDAC_Synth_internalClock_DIV_INT_MASK   VDAC_Synth_internalClock__DIVIDER_MASK
#define VDAC_Synth_internalClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_VDAC_Synth_internalClock_H) */

/* [] END OF FILE */
