/*******************************************************************************
* File Name: VDAC_Synth_OUTBUFFER.h
* Version 1.20
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Opamp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_VDAC_Synth_OUTBUFFER_H)
#define CY_OPAMP_VDAC_Synth_OUTBUFFER_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} VDAC_Synth_OUTBUFFER_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void VDAC_Synth_OUTBUFFER_Init(void);
void VDAC_Synth_OUTBUFFER_Enable(void);
void VDAC_Synth_OUTBUFFER_Start(void);
void VDAC_Synth_OUTBUFFER_Stop(void);
void VDAC_Synth_OUTBUFFER_SetPower(uint32 power);
void VDAC_Synth_OUTBUFFER_PumpControl(uint32 onOff);
void VDAC_Synth_OUTBUFFER_Sleep(void);
void VDAC_Synth_OUTBUFFER_Wakeup(void);
void VDAC_Synth_OUTBUFFER_SaveConfig(void);
void VDAC_Synth_OUTBUFFER_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define VDAC_Synth_OUTBUFFER_LOW_POWER      (1u)
#define VDAC_Synth_OUTBUFFER_MED_POWER      (2u)
#define VDAC_Synth_OUTBUFFER_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define VDAC_Synth_OUTBUFFER_PUMP_ON        (1u)
#define VDAC_Synth_OUTBUFFER_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define VDAC_Synth_OUTBUFFER_OUTPUT_CURRENT         (1u)
#define VDAC_Synth_OUTBUFFER_POWER                  (3u)
#define VDAC_Synth_OUTBUFFER_MODE                   (0u)
#define VDAC_Synth_OUTBUFFER_OA_COMP_TRIM_VALUE     (3u)
#define VDAC_Synth_OUTBUFFER_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  VDAC_Synth_OUTBUFFER_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define VDAC_Synth_OUTBUFFER_CTB_CTRL_REG       (*(reg32 *) VDAC_Synth_OUTBUFFER_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define VDAC_Synth_OUTBUFFER_CTB_CTRL_PTR       ( (reg32 *) VDAC_Synth_OUTBUFFER_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define VDAC_Synth_OUTBUFFER_CTB_CTRL_REG       (*(reg32 *) VDAC_Synth_OUTBUFFER_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define VDAC_Synth_OUTBUFFER_CTB_CTRL_PTR       ( (reg32 *) VDAC_Synth_OUTBUFFER_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG    (*(reg32 *) VDAC_Synth_OUTBUFFER_cy_psoc4_abuf__OA_RES_CTRL)
#define VDAC_Synth_OUTBUFFER_OA_RES_CTRL_PTR    ( (reg32 *) VDAC_Synth_OUTBUFFER_cy_psoc4_abuf__OA_RES_CTRL)
#define VDAC_Synth_OUTBUFFER_OA_COMP_TRIM_REG   (*(reg32 *) VDAC_Synth_OUTBUFFER_cy_psoc4_abuf__OA_COMP_TRIM)
#define VDAC_Synth_OUTBUFFER_OA_COMP_TRIM_PTR   ( (reg32 *) VDAC_Synth_OUTBUFFER_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* VDAC_Synth_OUTBUFFER_CTB_CTRL_REG */
#define VDAC_Synth_OUTBUFFER_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define VDAC_Synth_OUTBUFFER_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define VDAC_Synth_OUTBUFFER_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << VDAC_Synth_OUTBUFFER_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define VDAC_Synth_OUTBUFFER_CTB_CTRL_ENABLED               ((uint32) 0x01u << VDAC_Synth_OUTBUFFER_CTB_CTRL_ENABLED_SHIFT)


/* VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG */
#define VDAC_Synth_OUTBUFFER_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define VDAC_Synth_OUTBUFFER_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define VDAC_Synth_OUTBUFFER_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define VDAC_Synth_OUTBUFFER_OA_PWR_MODE                ((uint32) 0x02u << VDAC_Synth_OUTBUFFER_OA_PWR_MODE_SHIFT)
#define VDAC_Synth_OUTBUFFER_OA_PWR_MODE_MASK           ((uint32) 0x03u << VDAC_Synth_OUTBUFFER_OA_PWR_MODE_SHIFT)
#define VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_SHIFT)
#define VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_SHIFT)
#define VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_SHIFT)
#define VDAC_Synth_OUTBUFFER_OA_COMP_EN                 ((uint32) 0x00u << VDAC_Synth_OUTBUFFER_OA_COMP_EN_SHIFT)
#define VDAC_Synth_OUTBUFFER_OA_PUMP_EN                 ((uint32) 0x01u << VDAC_Synth_OUTBUFFER_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define VDAC_Synth_OUTBUFFER_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (VDAC_Synth_OUTBUFFER_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define VDAC_Synth_OUTBUFFER_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_10X) : \
                                                                             (VDAC_Synth_OUTBUFFER_OA_DRIVE_STR_SEL_1X))
#define VDAC_Synth_OUTBUFFER_GET_OA_PWR_MODE(mode)          ((mode) & VDAC_Synth_OUTBUFFER_OA_PWR_MODE_MASK)
#define VDAC_Synth_OUTBUFFER_CHECK_PWR_MODE_OFF             (0u != (VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG & \
                                                                VDAC_Synth_OUTBUFFER_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define VDAC_Synth_OUTBUFFER_CHECK_DEEPSLEEP_SUPPORT        (0u != VDAC_Synth_OUTBUFFER_DEEPSLEEP_SUPPORT) 

#define VDAC_Synth_OUTBUFFER_DEFAULT_CTB_CTRL (VDAC_Synth_OUTBUFFER_GET_DEEPSLEEP_ON(VDAC_Synth_OUTBUFFER_DEEPSLEEP_SUPPORT) | \
                                           VDAC_Synth_OUTBUFFER_CTB_CTRL_ENABLED)

#define VDAC_Synth_OUTBUFFER_DEFAULT_OA_RES_CTRL (VDAC_Synth_OUTBUFFER_OA_COMP_EN | \
                                              VDAC_Synth_OUTBUFFER_GET_OA_DRIVE_STR(VDAC_Synth_OUTBUFFER_OUTPUT_CURRENT))

#define VDAC_Synth_OUTBUFFER_DEFAULT_OA_COMP_TRIM_REG (VDAC_Synth_OUTBUFFER_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define VDAC_Synth_OUTBUFFER_LOWPOWER                   (VDAC_Synth_OUTBUFFER_LOW_POWER)
#define VDAC_Synth_OUTBUFFER_MEDPOWER                   (VDAC_Synth_OUTBUFFER_MED_POWER)
#define VDAC_Synth_OUTBUFFER_HIGHPOWER                  (VDAC_Synth_OUTBUFFER_HIGH_POWER)

/* PUMP ON/OFF defines */
#define VDAC_Synth_OUTBUFFER_PUMPON                     (VDAC_Synth_OUTBUFFER_PUMP_ON)
#define VDAC_Synth_OUTBUFFER_PUMPOFF                    (VDAC_Synth_OUTBUFFER_PUMP_OFF)

#define VDAC_Synth_OUTBUFFER_OA_CTRL                    (VDAC_Synth_OUTBUFFER_CTB_CTRL_REG)
#define VDAC_Synth_OUTBUFFER_OA_RES_CTRL                (VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define VDAC_Synth_OUTBUFFER_OA_CTB_EN_SHIFT            (VDAC_Synth_OUTBUFFER_CTB_CTRL_ENABLED_SHIFT)
#define VDAC_Synth_OUTBUFFER_OA_PUMP_CTRL_SHIFT         (VDAC_Synth_OUTBUFFER_OA_PUMP_EN_SHIFT)
#define VDAC_Synth_OUTBUFFER_OA_PUMP_EN_MASK            (0x800u)
#define VDAC_Synth_OUTBUFFER_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_VDAC_Synth_OUTBUFFER_H */


/* [] END OF FILE */
