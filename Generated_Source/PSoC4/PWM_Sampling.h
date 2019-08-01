/*******************************************************************************
* File Name: PWM_Sampling.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the PWM_Sampling
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_PWM_Sampling_H)
#define CY_TCPWM_PWM_Sampling_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} PWM_Sampling_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PWM_Sampling_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define PWM_Sampling_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define PWM_Sampling_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define PWM_Sampling_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define PWM_Sampling_QUAD_ENCODING_MODES            (0lu)
#define PWM_Sampling_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define PWM_Sampling_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PWM_Sampling_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PWM_Sampling_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PWM_Sampling_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PWM_Sampling_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PWM_Sampling_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PWM_Sampling_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PWM_Sampling_TC_RUN_MODE                    (0lu)
#define PWM_Sampling_TC_COUNTER_MODE                (0lu)
#define PWM_Sampling_TC_COMP_CAP_MODE               (2lu)
#define PWM_Sampling_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PWM_Sampling_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PWM_Sampling_TC_COUNT_SIGNAL_MODE           (3lu)
#define PWM_Sampling_TC_START_SIGNAL_MODE           (0lu)
#define PWM_Sampling_TC_STOP_SIGNAL_MODE            (0lu)
#define PWM_Sampling_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM_Sampling_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PWM_Sampling_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PWM_Sampling_TC_START_SIGNAL_PRESENT        (0lu)
#define PWM_Sampling_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PWM_Sampling_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM_Sampling_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define PWM_Sampling_PWM_KILL_EVENT                 (0lu)
#define PWM_Sampling_PWM_STOP_EVENT                 (0lu)
#define PWM_Sampling_PWM_MODE                       (4lu)
#define PWM_Sampling_PWM_OUT_N_INVERT               (0lu)
#define PWM_Sampling_PWM_OUT_INVERT                 (0lu)
#define PWM_Sampling_PWM_ALIGN                      (0lu)
#define PWM_Sampling_PWM_RUN_MODE                   (0lu)
#define PWM_Sampling_PWM_DEAD_TIME_CYCLE            (0lu)
#define PWM_Sampling_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PWM_Sampling_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PWM_Sampling_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PWM_Sampling_PWM_START_SIGNAL_MODE          (0lu)
#define PWM_Sampling_PWM_STOP_SIGNAL_MODE           (0lu)
#define PWM_Sampling_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM_Sampling_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PWM_Sampling_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PWM_Sampling_PWM_START_SIGNAL_PRESENT       (0lu)
#define PWM_Sampling_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PWM_Sampling_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM_Sampling_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PWM_Sampling_TC_PERIOD_VALUE                (65535lu)
#define PWM_Sampling_TC_COMPARE_VALUE               (65535lu)
#define PWM_Sampling_TC_COMPARE_BUF_VALUE           (65535lu)
#define PWM_Sampling_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PWM_Sampling_PWM_PERIOD_VALUE               (125lu)
#define PWM_Sampling_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PWM_Sampling_PWM_PERIOD_SWAP                (0lu)
#define PWM_Sampling_PWM_COMPARE_VALUE              (62lu)
#define PWM_Sampling_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PWM_Sampling_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PWM_Sampling__LEFT 0
#define PWM_Sampling__RIGHT 1
#define PWM_Sampling__CENTER 2
#define PWM_Sampling__ASYMMETRIC 3

#define PWM_Sampling__X1 0
#define PWM_Sampling__X2 1
#define PWM_Sampling__X4 2

#define PWM_Sampling__PWM 4
#define PWM_Sampling__PWM_DT 5
#define PWM_Sampling__PWM_PR 6

#define PWM_Sampling__INVERSE 1
#define PWM_Sampling__DIRECT 0

#define PWM_Sampling__CAPTURE 2
#define PWM_Sampling__COMPARE 0

#define PWM_Sampling__TRIG_LEVEL 3
#define PWM_Sampling__TRIG_RISING 0
#define PWM_Sampling__TRIG_FALLING 1
#define PWM_Sampling__TRIG_BOTH 2

#define PWM_Sampling__INTR_MASK_TC 1
#define PWM_Sampling__INTR_MASK_CC_MATCH 2
#define PWM_Sampling__INTR_MASK_NONE 0
#define PWM_Sampling__INTR_MASK_TC_CC 3

#define PWM_Sampling__UNCONFIG 8
#define PWM_Sampling__TIMER 1
#define PWM_Sampling__QUAD 3
#define PWM_Sampling__PWM_SEL 7

#define PWM_Sampling__COUNT_UP 0
#define PWM_Sampling__COUNT_DOWN 1
#define PWM_Sampling__COUNT_UPDOWN0 2
#define PWM_Sampling__COUNT_UPDOWN1 3


/* Prescaler */
#define PWM_Sampling_PRESCALE_DIVBY1                ((uint32)(0u << PWM_Sampling_PRESCALER_SHIFT))
#define PWM_Sampling_PRESCALE_DIVBY2                ((uint32)(1u << PWM_Sampling_PRESCALER_SHIFT))
#define PWM_Sampling_PRESCALE_DIVBY4                ((uint32)(2u << PWM_Sampling_PRESCALER_SHIFT))
#define PWM_Sampling_PRESCALE_DIVBY8                ((uint32)(3u << PWM_Sampling_PRESCALER_SHIFT))
#define PWM_Sampling_PRESCALE_DIVBY16               ((uint32)(4u << PWM_Sampling_PRESCALER_SHIFT))
#define PWM_Sampling_PRESCALE_DIVBY32               ((uint32)(5u << PWM_Sampling_PRESCALER_SHIFT))
#define PWM_Sampling_PRESCALE_DIVBY64               ((uint32)(6u << PWM_Sampling_PRESCALER_SHIFT))
#define PWM_Sampling_PRESCALE_DIVBY128              ((uint32)(7u << PWM_Sampling_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PWM_Sampling_MODE_TIMER_COMPARE             ((uint32)(PWM_Sampling__COMPARE         <<  \
                                                                  PWM_Sampling_MODE_SHIFT))
#define PWM_Sampling_MODE_TIMER_CAPTURE             ((uint32)(PWM_Sampling__CAPTURE         <<  \
                                                                  PWM_Sampling_MODE_SHIFT))
#define PWM_Sampling_MODE_QUAD                      ((uint32)(PWM_Sampling__QUAD            <<  \
                                                                  PWM_Sampling_MODE_SHIFT))
#define PWM_Sampling_MODE_PWM                       ((uint32)(PWM_Sampling__PWM             <<  \
                                                                  PWM_Sampling_MODE_SHIFT))
#define PWM_Sampling_MODE_PWM_DT                    ((uint32)(PWM_Sampling__PWM_DT          <<  \
                                                                  PWM_Sampling_MODE_SHIFT))
#define PWM_Sampling_MODE_PWM_PR                    ((uint32)(PWM_Sampling__PWM_PR          <<  \
                                                                  PWM_Sampling_MODE_SHIFT))

/* Quad Modes */
#define PWM_Sampling_MODE_X1                        ((uint32)(PWM_Sampling__X1              <<  \
                                                                  PWM_Sampling_QUAD_MODE_SHIFT))
#define PWM_Sampling_MODE_X2                        ((uint32)(PWM_Sampling__X2              <<  \
                                                                  PWM_Sampling_QUAD_MODE_SHIFT))
#define PWM_Sampling_MODE_X4                        ((uint32)(PWM_Sampling__X4              <<  \
                                                                  PWM_Sampling_QUAD_MODE_SHIFT))

/* Counter modes */
#define PWM_Sampling_COUNT_UP                       ((uint32)(PWM_Sampling__COUNT_UP        <<  \
                                                                  PWM_Sampling_UPDOWN_SHIFT))
#define PWM_Sampling_COUNT_DOWN                     ((uint32)(PWM_Sampling__COUNT_DOWN      <<  \
                                                                  PWM_Sampling_UPDOWN_SHIFT))
#define PWM_Sampling_COUNT_UPDOWN0                  ((uint32)(PWM_Sampling__COUNT_UPDOWN0   <<  \
                                                                  PWM_Sampling_UPDOWN_SHIFT))
#define PWM_Sampling_COUNT_UPDOWN1                  ((uint32)(PWM_Sampling__COUNT_UPDOWN1   <<  \
                                                                  PWM_Sampling_UPDOWN_SHIFT))

/* PWM output invert */
#define PWM_Sampling_INVERT_LINE                    ((uint32)(PWM_Sampling__INVERSE         <<  \
                                                                  PWM_Sampling_INV_OUT_SHIFT))
#define PWM_Sampling_INVERT_LINE_N                  ((uint32)(PWM_Sampling__INVERSE         <<  \
                                                                  PWM_Sampling_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PWM_Sampling_TRIG_RISING                    ((uint32)PWM_Sampling__TRIG_RISING)
#define PWM_Sampling_TRIG_FALLING                   ((uint32)PWM_Sampling__TRIG_FALLING)
#define PWM_Sampling_TRIG_BOTH                      ((uint32)PWM_Sampling__TRIG_BOTH)
#define PWM_Sampling_TRIG_LEVEL                     ((uint32)PWM_Sampling__TRIG_LEVEL)

/* Interrupt mask */
#define PWM_Sampling_INTR_MASK_TC                   ((uint32)PWM_Sampling__INTR_MASK_TC)
#define PWM_Sampling_INTR_MASK_CC_MATCH             ((uint32)PWM_Sampling__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PWM_Sampling_CC_MATCH_SET                   (0x00u)
#define PWM_Sampling_CC_MATCH_CLEAR                 (0x01u)
#define PWM_Sampling_CC_MATCH_INVERT                (0x02u)
#define PWM_Sampling_CC_MATCH_NO_CHANGE             (0x03u)
#define PWM_Sampling_OVERLOW_SET                    (0x00u)
#define PWM_Sampling_OVERLOW_CLEAR                  (0x04u)
#define PWM_Sampling_OVERLOW_INVERT                 (0x08u)
#define PWM_Sampling_OVERLOW_NO_CHANGE              (0x0Cu)
#define PWM_Sampling_UNDERFLOW_SET                  (0x00u)
#define PWM_Sampling_UNDERFLOW_CLEAR                (0x10u)
#define PWM_Sampling_UNDERFLOW_INVERT               (0x20u)
#define PWM_Sampling_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PWM_Sampling_PWM_MODE_LEFT                  (PWM_Sampling_CC_MATCH_CLEAR        |   \
                                                         PWM_Sampling_OVERLOW_SET           |   \
                                                         PWM_Sampling_UNDERFLOW_NO_CHANGE)
#define PWM_Sampling_PWM_MODE_RIGHT                 (PWM_Sampling_CC_MATCH_SET          |   \
                                                         PWM_Sampling_OVERLOW_NO_CHANGE     |   \
                                                         PWM_Sampling_UNDERFLOW_CLEAR)
#define PWM_Sampling_PWM_MODE_ASYM                  (PWM_Sampling_CC_MATCH_INVERT       |   \
                                                         PWM_Sampling_OVERLOW_SET           |   \
                                                         PWM_Sampling_UNDERFLOW_CLEAR)

#if (PWM_Sampling_CY_TCPWM_V2)
    #if(PWM_Sampling_CY_TCPWM_4000)
        #define PWM_Sampling_PWM_MODE_CENTER                (PWM_Sampling_CC_MATCH_INVERT       |   \
                                                                 PWM_Sampling_OVERLOW_NO_CHANGE     |   \
                                                                 PWM_Sampling_UNDERFLOW_CLEAR)
    #else
        #define PWM_Sampling_PWM_MODE_CENTER                (PWM_Sampling_CC_MATCH_INVERT       |   \
                                                                 PWM_Sampling_OVERLOW_SET           |   \
                                                                 PWM_Sampling_UNDERFLOW_CLEAR)
    #endif /* (PWM_Sampling_CY_TCPWM_4000) */
#else
    #define PWM_Sampling_PWM_MODE_CENTER                (PWM_Sampling_CC_MATCH_INVERT       |   \
                                                             PWM_Sampling_OVERLOW_NO_CHANGE     |   \
                                                             PWM_Sampling_UNDERFLOW_CLEAR)
#endif /* (PWM_Sampling_CY_TCPWM_NEW) */

/* Command operations without condition */
#define PWM_Sampling_CMD_CAPTURE                    (0u)
#define PWM_Sampling_CMD_RELOAD                     (8u)
#define PWM_Sampling_CMD_STOP                       (16u)
#define PWM_Sampling_CMD_START                      (24u)

/* Status */
#define PWM_Sampling_STATUS_DOWN                    (1u)
#define PWM_Sampling_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PWM_Sampling_Init(void);
void   PWM_Sampling_Enable(void);
void   PWM_Sampling_Start(void);
void   PWM_Sampling_Stop(void);

void   PWM_Sampling_SetMode(uint32 mode);
void   PWM_Sampling_SetCounterMode(uint32 counterMode);
void   PWM_Sampling_SetPWMMode(uint32 modeMask);
void   PWM_Sampling_SetQDMode(uint32 qdMode);

void   PWM_Sampling_SetPrescaler(uint32 prescaler);
void   PWM_Sampling_TriggerCommand(uint32 mask, uint32 command);
void   PWM_Sampling_SetOneShot(uint32 oneShotEnable);
uint32 PWM_Sampling_ReadStatus(void);

void   PWM_Sampling_SetPWMSyncKill(uint32 syncKillEnable);
void   PWM_Sampling_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PWM_Sampling_SetPWMDeadTime(uint32 deadTime);
void   PWM_Sampling_SetPWMInvert(uint32 mask);

void   PWM_Sampling_SetInterruptMode(uint32 interruptMask);
uint32 PWM_Sampling_GetInterruptSourceMasked(void);
uint32 PWM_Sampling_GetInterruptSource(void);
void   PWM_Sampling_ClearInterrupt(uint32 interruptMask);
void   PWM_Sampling_SetInterrupt(uint32 interruptMask);

void   PWM_Sampling_WriteCounter(uint32 count);
uint32 PWM_Sampling_ReadCounter(void);

uint32 PWM_Sampling_ReadCapture(void);
uint32 PWM_Sampling_ReadCaptureBuf(void);

void   PWM_Sampling_WritePeriod(uint32 period);
uint32 PWM_Sampling_ReadPeriod(void);
void   PWM_Sampling_WritePeriodBuf(uint32 periodBuf);
uint32 PWM_Sampling_ReadPeriodBuf(void);

void   PWM_Sampling_WriteCompare(uint32 compare);
uint32 PWM_Sampling_ReadCompare(void);
void   PWM_Sampling_WriteCompareBuf(uint32 compareBuf);
uint32 PWM_Sampling_ReadCompareBuf(void);

void   PWM_Sampling_SetPeriodSwap(uint32 swapEnable);
void   PWM_Sampling_SetCompareSwap(uint32 swapEnable);

void   PWM_Sampling_SetCaptureMode(uint32 triggerMode);
void   PWM_Sampling_SetReloadMode(uint32 triggerMode);
void   PWM_Sampling_SetStartMode(uint32 triggerMode);
void   PWM_Sampling_SetStopMode(uint32 triggerMode);
void   PWM_Sampling_SetCountMode(uint32 triggerMode);

void   PWM_Sampling_SaveConfig(void);
void   PWM_Sampling_RestoreConfig(void);
void   PWM_Sampling_Sleep(void);
void   PWM_Sampling_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PWM_Sampling_BLOCK_CONTROL_REG              (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM_Sampling_BLOCK_CONTROL_PTR              ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM_Sampling_COMMAND_REG                    (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM_Sampling_COMMAND_PTR                    ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM_Sampling_INTRRUPT_CAUSE_REG             (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM_Sampling_INTRRUPT_CAUSE_PTR             ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM_Sampling_CONTROL_REG                    (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__CTRL )
#define PWM_Sampling_CONTROL_PTR                    ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__CTRL )
#define PWM_Sampling_STATUS_REG                     (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__STATUS )
#define PWM_Sampling_STATUS_PTR                     ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__STATUS )
#define PWM_Sampling_COUNTER_REG                    (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__COUNTER )
#define PWM_Sampling_COUNTER_PTR                    ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__COUNTER )
#define PWM_Sampling_COMP_CAP_REG                   (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__CC )
#define PWM_Sampling_COMP_CAP_PTR                   ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__CC )
#define PWM_Sampling_COMP_CAP_BUF_REG               (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM_Sampling_COMP_CAP_BUF_PTR               ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM_Sampling_PERIOD_REG                     (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__PERIOD )
#define PWM_Sampling_PERIOD_PTR                     ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__PERIOD )
#define PWM_Sampling_PERIOD_BUF_REG                 (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM_Sampling_PERIOD_BUF_PTR                 ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM_Sampling_TRIG_CONTROL0_REG              (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM_Sampling_TRIG_CONTROL0_PTR              ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM_Sampling_TRIG_CONTROL1_REG              (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM_Sampling_TRIG_CONTROL1_PTR              ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM_Sampling_TRIG_CONTROL2_REG              (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM_Sampling_TRIG_CONTROL2_PTR              ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM_Sampling_INTERRUPT_REQ_REG              (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__INTR )
#define PWM_Sampling_INTERRUPT_REQ_PTR              ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__INTR )
#define PWM_Sampling_INTERRUPT_SET_REG              (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM_Sampling_INTERRUPT_SET_PTR              ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM_Sampling_INTERRUPT_MASK_REG             (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM_Sampling_INTERRUPT_MASK_PTR             ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM_Sampling_INTERRUPT_MASKED_REG           (*(reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PWM_Sampling_INTERRUPT_MASKED_PTR           ( (reg32 *) PWM_Sampling_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PWM_Sampling_MASK                           ((uint32)PWM_Sampling_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PWM_Sampling_RELOAD_CC_SHIFT                (0u)
#define PWM_Sampling_RELOAD_PERIOD_SHIFT            (1u)
#define PWM_Sampling_PWM_SYNC_KILL_SHIFT            (2u)
#define PWM_Sampling_PWM_STOP_KILL_SHIFT            (3u)
#define PWM_Sampling_PRESCALER_SHIFT                (8u)
#define PWM_Sampling_UPDOWN_SHIFT                   (16u)
#define PWM_Sampling_ONESHOT_SHIFT                  (18u)
#define PWM_Sampling_QUAD_MODE_SHIFT                (20u)
#define PWM_Sampling_INV_OUT_SHIFT                  (20u)
#define PWM_Sampling_INV_COMPL_OUT_SHIFT            (21u)
#define PWM_Sampling_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PWM_Sampling_RELOAD_CC_MASK                 ((uint32)(PWM_Sampling_1BIT_MASK        <<  \
                                                                            PWM_Sampling_RELOAD_CC_SHIFT))
#define PWM_Sampling_RELOAD_PERIOD_MASK             ((uint32)(PWM_Sampling_1BIT_MASK        <<  \
                                                                            PWM_Sampling_RELOAD_PERIOD_SHIFT))
#define PWM_Sampling_PWM_SYNC_KILL_MASK             ((uint32)(PWM_Sampling_1BIT_MASK        <<  \
                                                                            PWM_Sampling_PWM_SYNC_KILL_SHIFT))
#define PWM_Sampling_PWM_STOP_KILL_MASK             ((uint32)(PWM_Sampling_1BIT_MASK        <<  \
                                                                            PWM_Sampling_PWM_STOP_KILL_SHIFT))
#define PWM_Sampling_PRESCALER_MASK                 ((uint32)(PWM_Sampling_8BIT_MASK        <<  \
                                                                            PWM_Sampling_PRESCALER_SHIFT))
#define PWM_Sampling_UPDOWN_MASK                    ((uint32)(PWM_Sampling_2BIT_MASK        <<  \
                                                                            PWM_Sampling_UPDOWN_SHIFT))
#define PWM_Sampling_ONESHOT_MASK                   ((uint32)(PWM_Sampling_1BIT_MASK        <<  \
                                                                            PWM_Sampling_ONESHOT_SHIFT))
#define PWM_Sampling_QUAD_MODE_MASK                 ((uint32)(PWM_Sampling_3BIT_MASK        <<  \
                                                                            PWM_Sampling_QUAD_MODE_SHIFT))
#define PWM_Sampling_INV_OUT_MASK                   ((uint32)(PWM_Sampling_2BIT_MASK        <<  \
                                                                            PWM_Sampling_INV_OUT_SHIFT))
#define PWM_Sampling_MODE_MASK                      ((uint32)(PWM_Sampling_3BIT_MASK        <<  \
                                                                            PWM_Sampling_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PWM_Sampling_CAPTURE_SHIFT                  (0u)
#define PWM_Sampling_COUNT_SHIFT                    (2u)
#define PWM_Sampling_RELOAD_SHIFT                   (4u)
#define PWM_Sampling_STOP_SHIFT                     (6u)
#define PWM_Sampling_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PWM_Sampling_CAPTURE_MASK                   ((uint32)(PWM_Sampling_2BIT_MASK        <<  \
                                                                  PWM_Sampling_CAPTURE_SHIFT))
#define PWM_Sampling_COUNT_MASK                     ((uint32)(PWM_Sampling_2BIT_MASK        <<  \
                                                                  PWM_Sampling_COUNT_SHIFT))
#define PWM_Sampling_RELOAD_MASK                    ((uint32)(PWM_Sampling_2BIT_MASK        <<  \
                                                                  PWM_Sampling_RELOAD_SHIFT))
#define PWM_Sampling_STOP_MASK                      ((uint32)(PWM_Sampling_2BIT_MASK        <<  \
                                                                  PWM_Sampling_STOP_SHIFT))
#define PWM_Sampling_START_MASK                     ((uint32)(PWM_Sampling_2BIT_MASK        <<  \
                                                                  PWM_Sampling_START_SHIFT))

/* MASK */
#define PWM_Sampling_1BIT_MASK                      ((uint32)0x01u)
#define PWM_Sampling_2BIT_MASK                      ((uint32)0x03u)
#define PWM_Sampling_3BIT_MASK                      ((uint32)0x07u)
#define PWM_Sampling_6BIT_MASK                      ((uint32)0x3Fu)
#define PWM_Sampling_8BIT_MASK                      ((uint32)0xFFu)
#define PWM_Sampling_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PWM_Sampling_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PWM_Sampling_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(PWM_Sampling_QUAD_ENCODING_MODES     << PWM_Sampling_QUAD_MODE_SHIFT))       |\
         ((uint32)(PWM_Sampling_CONFIG                  << PWM_Sampling_MODE_SHIFT)))

#define PWM_Sampling_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(PWM_Sampling_PWM_STOP_EVENT          << PWM_Sampling_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(PWM_Sampling_PWM_OUT_INVERT          << PWM_Sampling_INV_OUT_SHIFT))         |\
         ((uint32)(PWM_Sampling_PWM_OUT_N_INVERT        << PWM_Sampling_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(PWM_Sampling_PWM_MODE                << PWM_Sampling_MODE_SHIFT)))

#define PWM_Sampling_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(PWM_Sampling_PWM_RUN_MODE         << PWM_Sampling_ONESHOT_SHIFT))
            
#define PWM_Sampling_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(PWM_Sampling_PWM_ALIGN            << PWM_Sampling_UPDOWN_SHIFT))

#define PWM_Sampling_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(PWM_Sampling_PWM_KILL_EVENT      << PWM_Sampling_PWM_SYNC_KILL_SHIFT))

#define PWM_Sampling_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(PWM_Sampling_PWM_DEAD_TIME_CYCLE  << PWM_Sampling_PRESCALER_SHIFT))

#define PWM_Sampling_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(PWM_Sampling_PWM_PRESCALER        << PWM_Sampling_PRESCALER_SHIFT))

#define PWM_Sampling_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(PWM_Sampling_TC_PRESCALER            << PWM_Sampling_PRESCALER_SHIFT))       |\
         ((uint32)(PWM_Sampling_TC_COUNTER_MODE         << PWM_Sampling_UPDOWN_SHIFT))          |\
         ((uint32)(PWM_Sampling_TC_RUN_MODE             << PWM_Sampling_ONESHOT_SHIFT))         |\
         ((uint32)(PWM_Sampling_TC_COMP_CAP_MODE        << PWM_Sampling_MODE_SHIFT)))
        
#define PWM_Sampling_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(PWM_Sampling_QUAD_PHIA_SIGNAL_MODE   << PWM_Sampling_COUNT_SHIFT))           |\
         ((uint32)(PWM_Sampling_QUAD_INDEX_SIGNAL_MODE  << PWM_Sampling_RELOAD_SHIFT))          |\
         ((uint32)(PWM_Sampling_QUAD_STOP_SIGNAL_MODE   << PWM_Sampling_STOP_SHIFT))            |\
         ((uint32)(PWM_Sampling_QUAD_PHIB_SIGNAL_MODE   << PWM_Sampling_START_SHIFT)))

#define PWM_Sampling_PWM_SIGNALS_MODES                                                              \
        (((uint32)(PWM_Sampling_PWM_SWITCH_SIGNAL_MODE  << PWM_Sampling_CAPTURE_SHIFT))         |\
         ((uint32)(PWM_Sampling_PWM_COUNT_SIGNAL_MODE   << PWM_Sampling_COUNT_SHIFT))           |\
         ((uint32)(PWM_Sampling_PWM_RELOAD_SIGNAL_MODE  << PWM_Sampling_RELOAD_SHIFT))          |\
         ((uint32)(PWM_Sampling_PWM_STOP_SIGNAL_MODE    << PWM_Sampling_STOP_SHIFT))            |\
         ((uint32)(PWM_Sampling_PWM_START_SIGNAL_MODE   << PWM_Sampling_START_SHIFT)))

#define PWM_Sampling_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(PWM_Sampling_TC_CAPTURE_SIGNAL_MODE  << PWM_Sampling_CAPTURE_SHIFT))         |\
         ((uint32)(PWM_Sampling_TC_COUNT_SIGNAL_MODE    << PWM_Sampling_COUNT_SHIFT))           |\
         ((uint32)(PWM_Sampling_TC_RELOAD_SIGNAL_MODE   << PWM_Sampling_RELOAD_SHIFT))          |\
         ((uint32)(PWM_Sampling_TC_STOP_SIGNAL_MODE     << PWM_Sampling_STOP_SHIFT))            |\
         ((uint32)(PWM_Sampling_TC_START_SIGNAL_MODE    << PWM_Sampling_START_SHIFT)))
        
#define PWM_Sampling_TIMER_UPDOWN_CNT_USED                                                          \
                ((PWM_Sampling__COUNT_UPDOWN0 == PWM_Sampling_TC_COUNTER_MODE)                  ||\
                 (PWM_Sampling__COUNT_UPDOWN1 == PWM_Sampling_TC_COUNTER_MODE))

#define PWM_Sampling_PWM_UPDOWN_CNT_USED                                                            \
                ((PWM_Sampling__CENTER == PWM_Sampling_PWM_ALIGN)                               ||\
                 (PWM_Sampling__ASYMMETRIC == PWM_Sampling_PWM_ALIGN))               
        
#define PWM_Sampling_PWM_PR_INIT_VALUE              (1u)
#define PWM_Sampling_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_PWM_Sampling_H */

/* [] END OF FILE */
