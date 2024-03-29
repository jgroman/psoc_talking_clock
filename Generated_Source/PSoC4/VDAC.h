/***************************************************************************//**
* \file     VDAC.h
* \version  1.10
*
* \brief
* Provides the source code to the API for the VDAC Component.
*
********************************************************************************
* \copyright
* (c) 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#if !defined(CY_VDAC_H)
    #define CY_VDAC_H

/*******************************************************************************
                                  Project Files
*******************************************************************************/
#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/***************************************
*    Variables with External Linkage
***************************************/
/**
* \addtogroup group_globals
* Globals are noted in the descriptions of the functions that use globals.
* They are marked with (R), (W), or (RW) noting whether the variable is read,
* write, or read/write.
* \{
*/

/** Tracks whether block is initialized (1) or not (0). */
extern uint8 VDAC_initVar;

/** \} globals */
    
/**
* \addtogroup group_structures
* \{
*/
/** Low power Mode API Support */
typedef struct
{
    /** Preserves whether block was enabled prior to sleep. 
    bit 0 - enabled state of the UAB
    bit 1 - enabled state of the CTB*/
    uint8   enableState; 
}   VDAC_BACKUP_STRUCT;
#define VDAC_BACKUP_BLOCKENABLED 1u
#define VDAC_BACKUP_OUTPUTDRIVEN 2u
/** \} structures */

/*******************************************************************************
                                  Parameters
The parameters that are set in the customizer are redefined as constants here.
*******************************************************************************/
#define VDAC_PARAM_DacSelect           0 /* DAC Mode (13b 2's comp, 13b sign+mag) */
#define VDAC_PARAM_DacGain             1   /* DAC Gain (1, 2, 4) */
#define VDAC_PARAM_DefaultOutVolts     1.20000004768372 /* Default Output Voltage, floating point */
#define VDAC_PARAM_DefaultOutCode      0 /* The code which corresponds to default voltage */

#define VDAC_PARAM_VrefSource          0 /* From where the Vref signal originates (Internal Vref, External Vref, External Off-chip) */
#define VDAC_PARAM_VrefVolts           1.2 /* Voltage of Vref signal */
#define VDAC_PARAM_VagndSource         0 /* From where the Vagnd signal originates (Internal Vref, External Vref, External Off-chip) */
#define VDAC_PARAM_VagndVolts          1.2 /* Voltage of Vagnd signal */
#define VDAC__SOURCE_INTERNAL 0
#define VDAC__SOURCE_EXTERNAL 1


#define VDAC_PARAM_DacMode             0
#define VDAC__MODE_2CMP 0
#define VDAC__MODE_SGNMAG 1


#define VDAC_PARAM_ExtFeedback         0 /* Whether feedback is used */
#define VDAC_PARAM_ExtModBit           0 /* Whether an external modulator input is used */
#define VDAC_PARAM_ExtStrobe           0 /* Whether an external strobe is used */
#define VDAC_PARAM_UserRefClkRate      250 /* What the desired refresh clock rate is */
#define VDAC_PARAM_UserRefClkRateEn    0 /* Whether user is allowed to modify refresh clock rate */
    
/*******************************************************************************
                                  Range-definition defines
*******************************************************************************/
                                                              /* 2's comp decode, expressed as decimal */
#define VDAC_MAX_13b2SCOMP            ((int32)   4095L)
#define VDAC_MIN_13b2SCOMP            ((int32)  -4096L)
#define VDAC_MAX_13bSGNMAG_12bUNSIGN  ((uint32) 4095UL)
#define VDAC_MIN_13bSGNMAG_12bUNSIGN  ((uint32)    0UL)
#define VDAC_MAX_13bUNSIGNED          ((uint32) 8191UL)
#define VDAC_MIN_13bUNSIGNED          ((uint32)    0UL)    

/*******************************************************************************
                                  Custom UAB Switch defines
*******************************************************************************/
#define VDAC_SW_EXTAGND  (CyUAB_sw_id_enum) CyUAB_SW_ID(VDAC_UAB_SW_STATIC_PTR,((uint32)VDAC_UAB_halfuab__VAGND_SRC), CyUAB_SW_NOX)  /* static: OA+ <-> External routed agnd */ 
#define VDAC_SW_EXTREFA  (CyUAB_sw_id_enum) CyUAB_SW_ID(VDAC_UAB_SW_CA_IN0_PTR,((uint32)((uint32)VDAC_UAB_halfuab__VREF_SRC)*VDAC_UAB_DYNAMIC_FIELD_SIZE), CyUAB_SW_NOX) /* A in <-> External routed vref */  
#define VDAC_SW_EXTREFB  (CyUAB_sw_id_enum) CyUAB_SW_ID(VDAC_UAB_SW_CB_IN0_PTR,((uint32)((uint32)VDAC_UAB_halfuab__VREF_SRC)*VDAC_UAB_DYNAMIC_FIELD_SIZE ), CyUAB_SW_NOX) /* B in <-> External routed vref */

/**************************************
*           API Constants
**************************************/
/**
* \addtogroup group_constants
* \{
*/

    /** \addtogroup dacFormat DAC format
     * \brief Constants for the VDAC_SetFormat() function.
     *  \{
     */
    typedef enum
    {
        VDAC_FORMAT_13TWOSCOMP = 0, /** 13bit 2's complement format */
        VDAC_FORMAT_13SIGNMAG  = 1 /** 13bit sign-magnitude format */
    } VDAC_format_enum;
    
    /** \} dacFormat */


    /** \addtogroup sign Sign
     * \brief Constants for the VDAC_SaturateSignMagnitude() function.
     *  \{
     */
    typedef enum
    {
        VDAC_SIGN_POSITIVE = 0, /**< Positive  */
        VDAC_SIGN_NEGATIVE = 1 /**< Negative */
    } VDAC_sign_enum;   
    /** \} sign */

    /** \addtogroup isHWStrobed Strobe mode
     * \brief Constants for the VDAC_SetStrobeMode() function.
     *  \{
     */
    typedef enum
    {
        VDAC_STROBE_CONTINUOUSLY  = 0,/**< Constantly update DAC values  */
        VDAC_STROBE_FROM_TERMINAL = 1 /**< Update DAC values when HW strobe received */
    } VDAC_strobe_mode_enum;  
    /** \} isHWStrobed */

    /** \addtogroup isHiZ Output tristate settings
     * \brief Constants for the VDAC_SetHiZ() function.
     *  \{
     */
    typedef enum
    {
        VDAC_OUTSTATE_DRIVEN = 0, /**< Output is the normal converted input  */
        VDAC_OUTSTATE_HIZ    = 1  /**< Output is tristate */
    } VDAC_output_state_enum;  
    /** \} isHiZ */

    /** \addtogroup rangeFactor Range factor
     * \brief Constants for the VDAC_SetRange() function.
     *  \{
     */
    typedef enum
    {
        VDAC_RANGE_VREF = 31, /**< Deflect around Vagnd by Vref  */
        VDAC_RANGE_2VREF   = 15, /**< Deflect around Vagnd by 2Vref */ 
        VDAC_RANGE_4VREF  =  7  /**< Deflect around Vagnd by 4Vref  */
    } VDAC_range_enum;  
    /** \} rangeFactor */
/** \} group_constants */

/***************************************
* Function Prototypes
***************************************/
/* Register for directly accessing the DAC value, rather than using function. */
#define VDAC_VALUE_PTR VDAC_UAB_CAP_AB_VAL_NXT_PTR
#define VDAC_VALUE_REG VDAC_UAB_CAP_AB_VAL_NXT_REG
#define VDAC_VALUE_DMA_PTR ((void*)VDAC_UAB_CAP_AB_VAL_NXT_PTR)
/**
* \addtogroup group_general
* \{
*/
void VDAC_Start(void);
void VDAC_Stop(void);
void VDAC_SetValue(int32 value);

int32 VDAC_SaturateTwosComp(int32 value);
int32 VDAC_SaturateSignMagnitude(VDAC_sign_enum sign, uint32 magnitude);
int32 VDAC_ConvertUnsigned2TwosComp(uint32 value);
void VDAC_SetFormat(VDAC_format_enum dacFormat);
void VDAC_SetStrobeMode(VDAC_strobe_mode_enum isHWStrobed);
void VDAC_SetHiZ(VDAC_output_state_enum isHiZ);
void VDAC_SetRange(VDAC_range_enum rangeFactor);
void VDAC_Init(void);
void VDAC_Enable(void);
/** \} general */

/**
* \addtogroup group_power
* \{
*/
void VDAC_Sleep(void);
void VDAC_Wakeup(void);
/** \} power */

/* ================= Register definitions for CTB IP Block. ================= */
/* These definitions will be replaced with CyFitter-generated addresses, once
 * they're available.                                                         */
#define VDAC_CTB_CTRL_REG                 (* ( reg32 *) 0x40040000 )
#define VDAC_CTB_CTRL_PTR                 (  ( reg32 *) 0x40040000 )
#define VDAC_OA_RES0_CTRL_REG             (* ( reg32 *) 0x40040004 )
#define VDAC_OA_RES0_CTRL_PTR             (  ( reg32 *) 0x40040004 )
#define VDAC_OA0_SW_REG                   (* ( reg32 *) 0x40040080 )
#define VDAC_OA0_SW_PTR                   (  ( reg32 *) 0x40040080 )

/* **************************** CTB_CTRL_REG fields ************************* */
/* ENABLED bitfield -- 1 bits wide -- RW access */
/* - 0: CTB IP disabled (put analog in power down, open all switches)
 * - 1: CTB IP enabled */
#define VDAC_CTB0_CTB_CTRL_ENABLED_MSK                (0x80000000UL)
#define VDAC_CTB0_CTB_CTRL_ENABLED_SHFT               (31U)         
    #define VDAC_CTB0_CTB_CTRL_ENABLED_DISABLED       (0U)
    #define VDAC_CTB0_CTB_CTRL_ENABLED_ENABLED        (1U)

/* **********************CTB0_OA_RES0_CTRL_REG fields *********************** */
/* These defines represent the default customization of the CTB. */
    #define VDAC_CTB0_OA_RES0_CTRL_DEFAULT            ( (VDAC_CTB0_OA_RES0_CTRL_OA0_PWR_MODE_MSK) \
                                                                  | (VDAC_CTB0_OA_RES0_CTRL_OA0_DRIVE_STR_SEL_MSK) \
                                                                  | (VDAC_CTB0_OA_RES0_CTRL_OA0_DSI_BYPASS_MSK) \
                                                                  | (VDAC_CTB0_OA_RES0_CTRL_OA0_PUMP_EN_MSK))

    #define VDAC_CTB0_OA_RES0_CTRL_MSK                ( (VDAC_CTB0_OA_RES0_CTRL_OA0_PWR_MODE_MSK) \
                                                                  | (VDAC_CTB0_OA_RES0_CTRL_OA0_DRIVE_STR_SEL_MSK) \
                                                                  | (VDAC_CTB0_OA_RES0_CTRL_OA0_DSI_BYPASS_MSK) \
                                                                  | (VDAC_CTB0_OA_RES0_CTRL_OA0_PUMP_EN_MSK))
    #define VDAC_CTB0_OA_RES0_CTRL_SHFT               (0x0U)
/* OA0_PWR_MODE bitfield -- 2 bits wide -- RW access */
/* Opamp0 power level: 0=off */
#define VDAC_CTB0_OA_RES0_CTRL_OA0_PWR_MODE_MSK       (0x00000003UL)
#define VDAC_CTB0_OA_RES0_CTRL_OA0_PWR_MODE_SHFT      (0U)          

/* OA0_DRIVE_STR_SEL bitfield -- 1 bits wide -- RW access */
/* Opamp0 output strenght select 0=1x, 1=10x */
#define VDAC_CTB0_OA_RES0_CTRL_OA0_DRIVE_STR_SEL_MSK    (0x00000004UL)
#define VDAC_CTB0_OA_RES0_CTRL_OA0_DRIVE_STR_SEL_SHFT    (2U)          

/* OA0_COMP_EN bitfield -- 1 bits wide -- RW access */
/* Opamp0 comparator enable */
#define VDAC_CTB0_OA_RES0_CTRL_OA0_COMP_EN_MSK        (0x00000010UL)
#define VDAC_CTB0_OA_RES0_CTRL_OA0_COMP_EN_SHFT       (4U)          

/* OA0_HYST_EN bitfield -- 1 bits wide -- RW access */
/* Opamp0 hysteresis enable (10mV) */
#define VDAC_CTB0_OA_RES0_CTRL_OA0_HYST_EN_MSK        (0x00000020UL)
#define VDAC_CTB0_OA_RES0_CTRL_OA0_HYST_EN_SHFT       (5U)          

/* OA0_DSI_BYPASS bitfield -- 1 bits wide -- RW access */
/* Opamp0 bypass comparator output synchronization for DSI (trigger) output:
0=synchronize (level or pulse), 1=bypass (output async) */
#define VDAC_CTB0_OA_RES0_CTRL_OA0_DSI_BYPASS_MSK     (0x00000040UL)
#define VDAC_CTB0_OA_RES0_CTRL_OA0_DSI_BYPASS_SHFT    (6U)          

/* OA0_DSI_LEVEL bitfield -- 1 bits wide -- RW access */
/* Opamp0 comparator DSI (trigger) out level : 0=pulse, 1=level */
#define VDAC_CTB0_OA_RES0_CTRL_OA0_DSI_LEVEL_MSK      (0x00000080UL)
#define VDAC_CTB0_OA_RES0_CTRL_OA0_DSI_LEVEL_SHFT     (7U)          

/* OA0_COMPINT bitfield -- 2 bits wide -- RW access */
/* Opamp0 comparator edge detect for interrupt and DSI (trigger) */
#define VDAC_CTB0_OA_RES0_CTRL_OA0_COMPINT_MSK        (0x00000300UL)
#define VDAC_CTB0_OA_RES0_CTRL_OA0_COMPINT_SHFT       (8U)          
    /* OA0_COMPINT bitfield enumerated values */
    #define VDAC_OA0_COMPINT_DISABLE                  (0x0)         
    #define VDAC_OA0_COMPINT_RISING                   (0x1)         
    #define VDAC_OA0_COMPINT_FALLING                  (0x2)         
    #define VDAC_OA0_COMPINT_BOTH                     (0x3)         

/* OA0_PUMP_EN bitfield -- 1 bits wide -- RW access */
/* Opamp0 pump enable */
#define VDAC_CTB0_OA_RES0_CTRL_OA0_PUMP_EN_MSK        (0x00000800UL)
#define VDAC_CTB0_OA_RES0_CTRL_OA0_PUMP_EN_SHFT       (11U)         

/* RES0_TAP bitfield -- 4 bits wide -- RW access */
/* PGA gain (resistor tap point): &#xA;0= gain 1.0 (disconnect resistor)&#xA;1=
gain 1.42 &#xA;2= gain 2.0&#xA;3= gain 2.78 &#xA;4= gain 4.0&#xA;5= gain
5.82&#xA;6= gain 8.0&#xA;7= gain 10.67 &#xA;8= gain 16.0&#xA;9= gain
21.33&#xA;10= gain 32.0 */
#define VDAC_CTB0_OA_RES0_CTRL_RES0_TAP_MSK           (0x000f0000UL)
#define VDAC_CTB0_OA_RES0_CTRL_RES0_TAP_SHFT          (16U)         

/* RES0_SWAP bitfield -- 1 bits wide -- RW access */
/* Swap Top and Bottom resistor value */
#define VDAC_CTB0_OA_RES0_CTRL_RES0_SWAP_MSK          (0x00100000UL)
#define VDAC_CTB0_OA_RES0_CTRL_RES0_SWAP_SHFT         (20U)         

/* C0_FB bitfield -- 4 bits wide -- RW access */
/* Feed back Cap value */
#define VDAC_CTB0_OA_RES0_CTRL_C0_FB_MSK              (0x0f000000UL)
#define VDAC_CTB0_OA_RES0_CTRL_C0_FB_SHFT             (24U)         

/* VALID_SEL0 bitfield -- 3 bits wide -- RW access */
/* Select which UAB Valid to use to sample the comparator output. This should
match the UAB analog output connected to this comparator.&#xA;The comparator
output gets sampled at the negative edge of the selected UAB Valid
signal.&#xA;0=UAB0 half 0 Valid output&#xA;1=UAB0 half 1 Valid output&#xA;2=UAB1
half 0 Valid output&#xA;3=UAB1 half 1 Valid output&#xA;4=UAB2 half 0 Valid
output&#xA;5=UAB2 half 1 Valid output&#xA;6=UAB3 half 0 Valid output&#xA;7=UAB3
half 1 Valid output */
#define VDAC_CTB0_OA_RES0_CTRL_VALID_SEL0_MSK         (0x70000000UL)
#define VDAC_CTB0_OA_RES0_CTRL_VALID_SEL0_SHFT        (28U)         

/* VALID_SEL0_EN bitfield -- 1 bits wide -- RW access */
/* Enable UAB Valid selection (UAB mode), otherwise ignore UAB Valid. &#xA;Note
that enabling UAB Valid selection also disables DeepSleep comparator operation.
*/
#define VDAC_CTB0_OA_RES0_CTRL_VALID_SEL0_EN_MSK      (0x80000000UL)
#define VDAC_CTB0_OA_RES0_CTRL_VALID_SEL0_EN_SHFT     (31U)         


/* *************************CTB0_OA0_SW_REG fields ************************** */
/* OA0P_A00 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to amuxbusa */
#define VDAC_CTB0_OA0_SW_OA0P_A00_MSK                 (0x00000001UL)
#define VDAC_CTB0_OA0_SW_OA0P_A00_SHFT                (0U)          

/* OA0P_A10 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to pin P1 */
#define VDAC_CTB0_OA0_SW_OA0P_A10_MSK                 (0x00000002UL)
#define VDAC_CTB0_OA0_SW_OA0P_A10_SHFT                (1U)          

/* OA0P_A20 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to pin P0 */
#define VDAC_CTB0_OA0_SW_OA0P_A20_MSK                 (0x00000004UL)
#define VDAC_CTB0_OA0_SW_OA0P_A20_SHFT                (2U)          

/* OA0P_A30 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to ctbbus0 */
#define VDAC_CTB0_OA0_SW_OA0P_A30_MSK                 (0x00000008UL)
#define VDAC_CTB0_OA0_SW_OA0P_A30_SHFT                (3U)          

/* OA0P_A40 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to ctbbus1 */
#define VDAC_CTB0_OA0_SW_OA0P_A40_MSK                 (0x00000010UL)
#define VDAC_CTB0_OA0_SW_OA0P_A40_SHFT                (4U)          

/* OA0P_A50 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to ctbbus2 */
#define VDAC_CTB0_OA0_SW_OA0P_A50_MSK                 (0x00000020UL)
#define VDAC_CTB0_OA0_SW_OA0P_A50_SHFT                (5U)          

/* OA0P_A60 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to ctbbus3 */
#define VDAC_CTB0_OA0_SW_OA0P_A60_MSK                 (0x00000040UL)
#define VDAC_CTB0_OA0_SW_OA0P_A60_SHFT                (6U)          

/* OA0P_A70 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to vref0 */
#define VDAC_CTB0_OA0_SW_OA0P_A70_MSK                 (0x00000080UL)
#define VDAC_CTB0_OA0_SW_OA0P_A70_SHFT                (7U)          

/* OA0P_A80 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to uabin0 */
#define VDAC_CTB0_OA0_SW_OA0P_A80_MSK                 (0x00000100UL)
#define VDAC_CTB0_OA0_SW_OA0P_A80_SHFT                (8U)          

/* OA0P_A90 bitfield -- 1 bits wide -- RW access */
/* Opamp0 positive terminal to uabin1 */
#define VDAC_CTB0_OA0_SW_OA0P_A90_MSK                 (0x00000200UL)
#define VDAC_CTB0_OA0_SW_OA0P_A90_SHFT                (9U)          

/* OA0M_A11 bitfield -- 1 bits wide -- RW access */
/* Opamp0 negative terminal to pin P1 */
#define VDAC_CTB0_OA0_SW_OA0M_A11_MSK                 (0x00000800UL)
#define VDAC_CTB0_OA0_SW_OA0M_A11_SHFT                (11U)         

/* OA0M_A31 bitfield -- 1 bits wide -- RW access */
/* Opamp0 negative terminal to ctbbus0 */
#define VDAC_CTB0_OA0_SW_OA0M_A31_MSK                 (0x00002000UL)
#define VDAC_CTB0_OA0_SW_OA0M_A31_SHFT                (13U)         

/* OA0M_A41 bitfield -- 1 bits wide -- RW access */
/* Opamp0 negative terminal to ctbbus1 */
#define VDAC_CTB0_OA0_SW_OA0M_A41_MSK                 (0x00004000UL)
#define VDAC_CTB0_OA0_SW_OA0M_A41_SHFT                (14U)         

/* OA0M_A51 bitfield -- 1 bits wide -- RW access */
/* Opamp0 negative terminal to ctbbus2 */
#define VDAC_CTB0_OA0_SW_OA0M_A51_MSK                 (0x00008000UL)
#define VDAC_CTB0_OA0_SW_OA0M_A51_SHFT                (15U)         

/* OA0M_A61 bitfield -- 1 bits wide -- RW access */
/* Opamp0 negative terminal to ctbbus3 */
#define VDAC_CTB0_OA0_SW_OA0M_A61_MSK                 (0x00010000UL)
#define VDAC_CTB0_OA0_SW_OA0M_A61_SHFT                (16U)         

/* OA0M_A71 bitfield -- 1 bits wide -- RW access */
/* Opamp0 negative terminal to vref0 */
#define VDAC_CTB0_OA0_SW_OA0M_A71_MSK                 (0x00020000UL)
#define VDAC_CTB0_OA0_SW_OA0M_A71_SHFT                (17U)         

/* OA0M_A81 bitfield -- 1 bits wide -- RW access */
/* Opamp0 negative terminal to Opamp0 bottom */
#define VDAC_CTB0_OA0_SW_OA0M_A81_MSK                 (0x00040000UL)
#define VDAC_CTB0_OA0_SW_OA0M_A81_SHFT                (18U)         

/* OA0M_A91 bitfield -- 1 bits wide -- RW access */
/* Opamp0 negative terminal to pin P2 */
#define VDAC_CTB0_OA0_SW_OA0M_A91_MSK                 (0x00080000UL)
#define VDAC_CTB0_OA0_SW_OA0M_A91_SHFT                (19U)         

/* OA0O_D31 bitfield -- 1 bits wide -- RW access */
/* Opamp0 output to ctbbus0 */
#define VDAC_CTB0_OA0_SW_OA0O_D31_MSK                 (0x00100000UL)
#define VDAC_CTB0_OA0_SW_OA0O_D31_SHFT                (20U)         

/* OA0O_D51 bitfield -- 1 bits wide -- RW access */
/* Opamp0 output to ctbbus2 */
#define VDAC_CTB0_OA0_SW_OA0O_D51_MSK                 (0x00200000UL)
#define VDAC_CTB0_OA0_SW_OA0O_D51_SHFT                (21U)         

/* OA0O_D71 bitfield -- 1 bits wide -- RW access */
/* Opamp0 output to vref0 */
#define VDAC_CTB0_OA0_SW_OA0O_D71_MSK                 (0x00400000UL)
#define VDAC_CTB0_OA0_SW_OA0O_D71_SHFT                (22U)         

/* OA0O_D81 bitfield -- 1 bits wide -- RW access */
/* Opamp0 output switch to short 1x with 10x drive */
#define VDAC_CTB0_OA0_SW_OA0O_D81_MSK                 (0x00800000UL)
#define VDAC_CTB0_OA0_SW_OA0O_D81_SHFT                (23U)         

/* RES0_R01 bitfield -- 1 bits wide -- RW access */
/* Resistor0 bottom to Pin P1 */
#define VDAC_CTB0_OA0_SW_RES0_R01_MSK                 (0x01000000UL)
#define VDAC_CTB0_OA0_SW_RES0_R01_SHFT                (24U)         

/* RES0_R11 bitfield -- 1 bits wide -- RW access */
/* Resistor0 bottom to Opamp1 output */
#define VDAC_CTB0_OA0_SW_RES0_R11_MSK                 (0x02000000UL)
#define VDAC_CTB0_OA0_SW_RES0_R11_SHFT                (25U)         

/* RES0_R31 bitfield -- 1 bits wide -- RW access */
/* Resistor0 bottom to Opamp0 negative terminal */
#define VDAC_CTB0_OA0_SW_RES0_R31_MSK                 (0x04000000UL)
#define VDAC_CTB0_OA0_SW_RES0_R31_SHFT                (26U)         

/* RES0_R41 bitfield -- 1 bits wide -- RW access */
/* Resistor0 bottom to Opamp1 negative terminal */
#define VDAC_CTB0_OA0_SW_RES0_R41_MSK                 (0x08000000UL)
#define VDAC_CTB0_OA0_SW_RES0_R41_SHFT                (27U)         

/* RES0_R61 bitfield -- 1 bits wide -- RW access */
/* Resistor0 bottom  to VSSA */
#define VDAC_CTB0_OA0_SW_RES0_R61_MSK                 (0x10000000UL)
#define VDAC_CTB0_OA0_SW_RES0_R61_SHFT                (28U)         

/* RES0_R71 bitfield -- 1 bits wide -- RW access */
/* Resistor0 tap to Opamp0 negative terminal */
#define VDAC_CTB0_OA0_SW_RES0_R71_MSK                 (0x20000000UL)
#define VDAC_CTB0_OA0_SW_RES0_R71_SHFT                (29U)         

/* RES0_R81 bitfield -- 1 bits wide -- RW access */
/* Resistor0 tap to Opamp0 positive terminal */
#define VDAC_CTB0_OA0_SW_RES0_R81_MSK                 (0x40000000UL)
#define VDAC_CTB0_OA0_SW_RES0_R81_SHFT                (30U)         
    
#endif /* !defined(CY_VDAC_H) */
/* [] END OF FILE */
