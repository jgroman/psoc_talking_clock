/*!*****************************************************************************
* \file VDAC_Synth_UAB_param.h
* \version 1.10
*
* \brief 
*   Definitions from Component Parameter
*
********************************************************************************
* \copyright
* (c) 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
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

/* excluding defs in this file with cond and endcond */
/*! @cond */

#if !defined(VDAC_Synth_UAB_PARAM_H)
#define VDAC_Synth_UAB_PARAM_H

#include "VDAC_Synth_UAB_CyUAB_types.h"
#include "VDAC_Synth_UAB_regs.h"
#include "cytypes.h"
#include "cyfitter.h"

#define VDAC_Synth_UAB_Nonzero(x) ( (x) != 0 )

#define VDAC_Synth_UAB_UnmappedIsZero(x)  ((uint32)(((x)==-1)? 0 : (x)))

/*!
* \addtogroup group_init
* @{
*/
/*! Component Parameters set in the component customizer */
#define VDAC_Synth_UAB_PARAM_COMP_MASK        0
#define VDAC_Synth_UAB_PARAM_VDAC_EMPTY_MASK  0

#define VDAC_Synth_UAB_NONZERO_INTR_MASK (VDAC_Synth_UAB_Nonzero( \
    ( 0 |0) ))
#define VDAC_Synth_UAB_DEFAULT_INTR_MASK ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_COMP_MASK)<<VDAC_Synth_UAB_INTR_COMP_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_VDAC_EMPTY_MASK)<<VDAC_Synth_UAB_INTR_VDAC_EMPTY_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_UAB_PWR        0
#define VDAC_Synth_UAB_PARAM_AGND_PTS       0
#define VDAC_Synth_UAB_PARAM_AGND_PWR       0
#define VDAC_Synth_UAB_PARAM_REF_PTS        0
#define VDAC_Synth_UAB_PARAM_REF_PWR        0
#define VDAC_Synth_UAB_PARAM_CMP_DSI_LEVEL  0
#define VDAC_Synth_UAB_PARAM_CMP_EDGE       0
#define VDAC_Synth_UAB_PARAM_CMP_PWR        0
#define VDAC_Synth_UAB_PARAM_OA_PWR         7

#define VDAC_Synth_UAB_PARAM_AGND_TIED      0
#define VDAC_Synth_UAB_PARAM_REF_TIED       0


/*
#define VDAC_Synth_UAB_NONZERO_OA_CTRL (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|0|\
    0||0|0|0|7) ))
*/

/* force inclusion in _initPairs */
#define VDAC_Synth_UAB_NONZERO_OA_CTRL (VDAC_Synth_UAB_Nonzero(1))

/*Shared switches agnd_tied and ref_tied occupy the same bit position, so ommitting from DEFAULT_OA_CTRL -
handled in Init() */
#define VDAC_Synth_UAB_DEFAULT_OA_CTRL ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_UAB_PWR)<<VDAC_Synth_UAB_UAB_PWR_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_AGND_PTS)<<VDAC_Synth_UAB_AGND_PTS_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_AGND_PWR)<<VDAC_Synth_UAB_AGND_PWR_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_REF_PTS)<<VDAC_Synth_UAB_REF_PTS_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_REF_PWR)<<VDAC_Synth_UAB_REF_PWR_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CMP_DSI_LEVEL)<<VDAC_Synth_UAB_CMP_DSI_LEVEL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CMP_EDGE)<<VDAC_Synth_UAB_CMP_EDGE_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CMP_PWR)<<VDAC_Synth_UAB_CMP_PWR_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_OA_PWR)<<VDAC_Synth_UAB_OA_PWR_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_CB_GND       1
#define VDAC_Synth_UAB_PARAM_CC_GND       0
#define VDAC_Synth_UAB_PARAM_FRC_SIGN_BIT 0
#define VDAC_Synth_UAB_PARAM_DAC_MODE_EN  1
#define VDAC_Synth_UAB_PARAM_DAC_MODE     2

#define VDAC_Synth_UAB_NONZERO_CAP_CTRL ( VDAC_Synth_UAB_Nonzero( \
    (1|0|1|2|0) ))
#define VDAC_Synth_UAB_DEFAULT_CAP_CTRL ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_CB_GND)<<VDAC_Synth_UAB_CB_GND_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CC_GND)<<VDAC_Synth_UAB_CC_GND_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_FRC_SIGN_BIT)<<VDAC_Synth_UAB_FRC_SIGN_BIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_DAC_MODE_EN)<<VDAC_Synth_UAB_DAC_MODE_EN_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_DAC_MODE)<<VDAC_Synth_UAB_DAC_MODE_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_CB_VAL    0
#define VDAC_Synth_UAB_PARAM_CA_VAL    0
#define VDAC_Synth_UAB_PARAM_SIGN_VAL  0
#define VDAC_Synth_UAB_PARAM_CB_64     0
#define VDAC_Synth_UAB_PARAM_CC_VAL    0
#define VDAC_Synth_UAB_PARAM_CF_VAL    31

#define VDAC_Synth_UAB_NONZERO_CAP_ABCF_VAL  (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|0|0|31) ))
#define VDAC_Synth_UAB_DEFAULT_CAP_ABCF_VAL  ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_CB_VAL)<<VDAC_Synth_UAB_CB_VAL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CA_VAL)<<VDAC_Synth_UAB_CA_VAL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SIGN_VAL)<<VDAC_Synth_UAB_SIGN_VAL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CB_64)<<VDAC_Synth_UAB_CB_64_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CC_VAL)<<VDAC_Synth_UAB_CC_VAL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CF_VAL)<<VDAC_Synth_UAB_CF_VAL_SHIFT) \
))

#define VDAC_Synth_UAB_NONZERO_CAP_AB_VAL_NXT (VDAC_Synth_UAB_Nonzero( \
    (0|0|0) ))
#define VDAC_Synth_UAB_DEFAULT_CAP_AB_VAL_NXT  ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_CB_VAL)<<VDAC_Synth_UAB_CB_VAL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CA_VAL)<<VDAC_Synth_UAB_CA_VAL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SIGN_VAL)<<VDAC_Synth_UAB_SIGN_VAL_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_CC_VAL_UPDATE  0
#define VDAC_Synth_UAB_PARAM_CF_VAL_UPDATE  1

#define VDAC_Synth_UAB_NONZERO_CAP_CF_VAL_NXT (VDAC_Synth_UAB_Nonzero( \
    (0|1|0|31) ))
#define VDAC_Synth_UAB_DEFAULT_CAP_CF_VAL_NXT ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_CC_VAL)<<VDAC_Synth_UAB_CC_VAL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CF_VAL)<<VDAC_Synth_UAB_CF_VAL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CC_VAL_UPDATE)<<VDAC_Synth_UAB_CC_VAL_UPDATE_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CF_VAL_UPDATE)<<VDAC_Synth_UAB_CF_VAL_UPDATE_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_GX0        CyUAB_SwIsClosed( 0 )
#define VDAC_Synth_UAB_PARAM_SW_GX1        CyUAB_SwIsClosed( 0 )
#define VDAC_Synth_UAB_PARAM_SW_GX2        CyUAB_SwIsClosed( 0 )
#define VDAC_Synth_UAB_PARAM_SW_GX3        CyUAB_SwIsClosed( 0 )
#define VDAC_Synth_UAB_PARAM_SW_RG         CyUAB_SwIsClosed( 0  )
#define VDAC_Synth_UAB_PARAM_SW_GG         CyUAB_SwIsClosed( 1  )
#define VDAC_Synth_UAB_PARAM_SW_RT         CyUAB_SwIsClosed( 0  )
#define VDAC_Synth_UAB_PARAM_SW_GT         CyUAB_SwIsClosed( 0  )
#define VDAC_Synth_UAB_PARAM_SW_QT         CyUAB_SwIsClosed( 0  )
#define VDAC_Synth_UAB_PARAM_EARLY_PS      1
#define VDAC_Synth_UAB_PARAM_EARLY_PO      1

/*strobe source from cyfitter.h*/
#define VDAC_Synth_UAB_PARAM_STRB_RST_SEL  (VDAC_Synth_UAB_UnmappedIsZero(VDAC_Synth_UAB_halfuab__STRB_RST_SEL))

#define VDAC_Synth_UAB_PARAM_STRB_RST_EN   0


/*if switch parameter references a bad x input, ignored in initialization*/
#define VDAC_Synth_UAB_XIN_OK(xin) ( (0UL==((uint32)(xin))) || (1UL==((uint32)(xin))) || (2UL==((uint32)(xin))) || (3UL==((uint32)(xin))) )
#define VDAC_Synth_UAB_IGNORE_VAL 0UL      
#define VDAC_Synth_UAB_XField(xin,val)  ( VDAC_Synth_UAB_XIN_OK((xin)) ? ((uint32)(val)) : VDAC_Synth_UAB_IGNORE_VAL )

/*
#define VDAC_Synth_UAB_NONZERO_SW_STATIC (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|0|0|1|0|0|0|1|1|0|0) ))
*/

/* force inclusion in _initPairs */
#define VDAC_Synth_UAB_NONZERO_SW_STATIC (VDAC_Synth_UAB_Nonzero(1))

#define VDAC_Synth_UAB_DEFAULT_SW_STATIC ((uint32)(\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X0,VDAC_Synth_UAB_PARAM_SW_GX0<<VDAC_Synth_UAB_StaticVShift(CyUAB_SW_GX0)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X1,VDAC_Synth_UAB_PARAM_SW_GX1<<VDAC_Synth_UAB_StaticVShift(CyUAB_SW_GX1)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X2,VDAC_Synth_UAB_PARAM_SW_GX2<<VDAC_Synth_UAB_StaticVShift(CyUAB_SW_GX2)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X3,VDAC_Synth_UAB_PARAM_SW_GX3<<VDAC_Synth_UAB_StaticVShift(CyUAB_SW_GX3)) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_RG)<<VDAC_Synth_UAB_SW_RG_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_GG)<<VDAC_Synth_UAB_SW_GG_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_RT)<<VDAC_Synth_UAB_SW_RT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_GT)<<VDAC_Synth_UAB_SW_GT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_QT)<<VDAC_Synth_UAB_SW_QT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_EARLY_PS)<<VDAC_Synth_UAB_EARLY_PS_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_EARLY_PO)<<VDAC_Synth_UAB_EARLY_PO_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_STRB_RST_SEL)<<VDAC_Synth_UAB_STRB_RST_SEL_SHIFT) | \
    (((uint32)VDAC_Synth_UAB_PARAM_STRB_RST_EN)<<VDAC_Synth_UAB_STRB_RST_EN_SHIFT) \
))

/*modbitab source from cyfitter.h*/
#define VDAC_Synth_UAB_PARAM_MODBIT0_SRC_SEL   (VDAC_Synth_UAB_UnmappedIsZero(VDAC_Synth_UAB_halfuab__MODBIT0_SEL))
/*modbitc source from cyfitter.h*/
#define VDAC_Synth_UAB_PARAM_MODBIT1_SRC_SEL   (VDAC_Synth_UAB_UnmappedIsZero(VDAC_Synth_UAB_halfuab__MODBIT1_SEL))

/*
#define VDAC_Synth_UAB_NONZERO_SW_MODBIT_SRC (VDAC_Synth_UAB_Nonzero( \
    (0|0) ))
*/
/* force inclusion in _initPairs */
#define VDAC_Synth_UAB_NONZERO_SW_MODBIT_SRC (VDAC_Synth_UAB_Nonzero(1))

#define VDAC_Synth_UAB_DEFAULT_SW_MODBIT_SRC ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_MODBIT0_SRC_SEL)<<VDAC_Synth_UAB_MODBIT0_SRC_SEL_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_MODBIT1_SRC_SEL)<<VDAC_Synth_UAB_MODBIT1_SRC_SEL_SHIFT) \
))


    
#define VDAC_Synth_UAB_PARAM_SW_AX0_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_AX1_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_AX2_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_AX3_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_AP          0
#define VDAC_Synth_UAB_PARAM_SW_AQ          0

#define VDAC_Synth_UAB_NONZERO_SW_CA_IN0 (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|0|0|0) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CA_IN0 ((uint32)(\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X0,VDAC_Synth_UAB_PARAM_SW_AX0_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_AX0_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X1,VDAC_Synth_UAB_PARAM_SW_AX1_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_AX1_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X2,VDAC_Synth_UAB_PARAM_SW_AX2_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_AX2_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X3,VDAC_Synth_UAB_PARAM_SW_AX3_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_AX3_MODBIT)) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_AP)<<VDAC_Synth_UAB_SW_AP_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_AQ)<<VDAC_Synth_UAB_SW_AQ_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_AA         0
#define VDAC_Synth_UAB_PARAM_SW_AR_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_AG_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_AV_MODBIT  10

/*Shared switch AA intentionally ommitted - handled in Init()*/
#define VDAC_Synth_UAB_NONZERO_SW_CA_IN1 (VDAC_Synth_UAB_Nonzero( \
    (0|0|10) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CA_IN1 ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_AR_MODBIT)<<VDAC_Synth_UAB_SW_AR_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_AG_MODBIT)<<VDAC_Synth_UAB_SW_AG_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_AV_MODBIT)<<VDAC_Synth_UAB_SW_AV_MODBIT_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_RA_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_GA_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_VA_MODBIT  0
#define VDAC_Synth_UAB_PARAM_SW_SA         15

#define VDAC_Synth_UAB_NONZERO_SW_CA_TOP (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|15) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CA_TOP ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_RA_MODBIT)<<VDAC_Synth_UAB_SW_RA_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_GA_MODBIT)<<VDAC_Synth_UAB_SW_GA_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_VA_MODBIT)<<VDAC_Synth_UAB_SW_VA_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_SA)<<VDAC_Synth_UAB_SW_SA_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_BX0_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_BX1_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_BX2_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_BX3_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_BP         0
#define VDAC_Synth_UAB_PARAM_SW_BQ         0

#define VDAC_Synth_UAB_NONZERO_SW_CB_IN0 (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|0|0|0) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CB_IN0 ((uint32)(\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X0,VDAC_Synth_UAB_PARAM_SW_BX0_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_BX0_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X1,VDAC_Synth_UAB_PARAM_SW_BX1_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_BX1_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X2,VDAC_Synth_UAB_PARAM_SW_BX2_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_BX2_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X3,VDAC_Synth_UAB_PARAM_SW_BX3_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_BX3_MODBIT)) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_BP)<<VDAC_Synth_UAB_SW_BP_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_BQ)<<VDAC_Synth_UAB_SW_BQ_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_BB        0
#define VDAC_Synth_UAB_PARAM_SW_BR_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_BG_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_BV_MODBIT 10

/*Shared switch BB intentionally ommitted - handled in Init()*/
#define VDAC_Synth_UAB_NONZERO_SW_CB_IN1 (VDAC_Synth_UAB_Nonzero( \
    (0|0|10) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CB_IN1 ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_BR_MODBIT)<<VDAC_Synth_UAB_SW_BR_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_BG_MODBIT)<<VDAC_Synth_UAB_SW_BG_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_BV_MODBIT)<<VDAC_Synth_UAB_SW_BV_MODBIT_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_RB_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_GB_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_VB_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_TB        1
#define VDAC_Synth_UAB_PARAM_SW_SB        15

#define VDAC_Synth_UAB_NONZERO_SW_CB_TOP (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|1|15) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CB_TOP ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_RB_MODBIT)<<VDAC_Synth_UAB_SW_RB_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_GB_MODBIT)<<VDAC_Synth_UAB_SW_GB_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_VB_MODBIT)<<VDAC_Synth_UAB_SW_VB_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_TB)<<VDAC_Synth_UAB_SW_TB_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_SB)<<VDAC_Synth_UAB_SW_SB_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_CX0_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_CX1_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_CX2_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_CX3_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_CP         0
#define VDAC_Synth_UAB_PARAM_SW_CQ         0
    
#define VDAC_Synth_UAB_NONZERO_SW_CC_IN0 (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|0|0|0) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CC_IN0 ((uint32)(\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X0,VDAC_Synth_UAB_PARAM_SW_CX0_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_CX0_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X1,VDAC_Synth_UAB_PARAM_SW_CX1_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_CX1_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X2,VDAC_Synth_UAB_PARAM_SW_CX2_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_CX2_MODBIT)) |\
    VDAC_Synth_UAB_XField(VDAC_Synth_UAB_X3,VDAC_Synth_UAB_PARAM_SW_CX3_MODBIT<<VDAC_Synth_UAB_DynamicVShift(CyUAB_SW_CX3_MODBIT)) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_CP)<<VDAC_Synth_UAB_SW_CP_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_CQ)<<VDAC_Synth_UAB_SW_CQ_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_CC        0
#define VDAC_Synth_UAB_PARAM_SW_CR_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_CG_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_CV_MODBIT 0

/*Shared switch CC intentionally ommitted - handled in Init()*/
#define VDAC_Synth_UAB_NONZERO_SW_CC_IN1 (VDAC_Synth_UAB_Nonzero( \
    (0|0|0) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CC_IN1 ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_CR_MODBIT)<<VDAC_Synth_UAB_SW_CR_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_CG_MODBIT)<<VDAC_Synth_UAB_SW_CG_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_CV_MODBIT)<<VDAC_Synth_UAB_SW_CV_MODBIT_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_RC_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_GC_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_VC_MODBIT 0
#define VDAC_Synth_UAB_PARAM_SW_TC        0
#define VDAC_Synth_UAB_PARAM_SW_SC        0
#define VDAC_Synth_UAB_PARAM_SW_ZC        0

#define VDAC_Synth_UAB_NONZERO_SW_CC_TOP (VDAC_Synth_UAB_Nonzero( \
    (0|0|0|0|0|0) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CC_TOP ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_RC_MODBIT)<<VDAC_Synth_UAB_SW_RC_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_GC_MODBIT)<<VDAC_Synth_UAB_SW_GC_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_VC_MODBIT)<<VDAC_Synth_UAB_SW_VC_MODBIT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_TC)<<VDAC_Synth_UAB_SW_TC_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_SC)<<VDAC_Synth_UAB_SW_SC_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_ZC)<<VDAC_Synth_UAB_SW_ZC_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SW_GF 0
#define VDAC_Synth_UAB_PARAM_SW_PF 15
#define VDAC_Synth_UAB_PARAM_SW_PS 1
#define VDAC_Synth_UAB_PARAM_SW_PO 3

#define VDAC_Synth_UAB_NONZERO_SW_CF_BOT (VDAC_Synth_UAB_Nonzero( \
    (0|15|1|3) ))
#define VDAC_Synth_UAB_DEFAULT_SW_CF_BOT ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_GF)<<VDAC_Synth_UAB_SW_GF_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_PF)<<VDAC_Synth_UAB_SW_PF_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_PS)<<VDAC_Synth_UAB_SW_PS_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SW_PO)<<VDAC_Synth_UAB_SW_PO_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_CMP_FF     0
#define VDAC_Synth_UAB_PARAM_VALID_WAVE 3
#define VDAC_Synth_UAB_PARAM_TRIG_OUT   0
#define VDAC_Synth_UAB_PARAM_STROBE_SW  15
#define VDAC_Synth_UAB_PARAM_STROBE_RST 5

#define VDAC_Synth_UAB_NONZERO_SW_OTHER (VDAC_Synth_UAB_Nonzero( \
    (0|3|0|15|5) ))
#define VDAC_Synth_UAB_DEFAULT_SW_OTHER ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_CMP_FF)<<VDAC_Synth_UAB_CMP_FF_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_VALID_WAVE)<<VDAC_Synth_UAB_VALID_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_TRIG_OUT)<<VDAC_Synth_UAB_TRIG_OUT_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_STROBE_SW)<<VDAC_Synth_UAB_STROBE_SW_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_STROBE_RST)<<VDAC_Synth_UAB_STROBE_RST_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_CA_BOOST  1
#define VDAC_Synth_UAB_PARAM_CB_BOOST  1
#define VDAC_Synth_UAB_PARAM_CC_BOOST  0
#define VDAC_Synth_UAB_PARAM_CF_BOOST  1
#define VDAC_Synth_UAB_PARAM_SUM_BOOST 1
#define VDAC_Synth_UAB_PARAM_PUMP_WAVE 1
    
#define VDAC_Synth_UAB_NONZERO_SW_BOOST_CTRL (VDAC_Synth_UAB_Nonzero( \
    (1|1|0|1|1|1) ))
#define VDAC_Synth_UAB_DEFAULT_SW_BOOST_CTRL ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_CA_BOOST)<<VDAC_Synth_UAB_CA_BOOST_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CB_BOOST)<<VDAC_Synth_UAB_CB_BOOST_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CC_BOOST)<<VDAC_Synth_UAB_CC_BOOST_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_CF_BOOST)<<VDAC_Synth_UAB_CF_BOOST_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SUM_BOOST)<<VDAC_Synth_UAB_SUM_BOOST_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_PUMP_WAVE)<<VDAC_Synth_UAB_PUMP_WAVE_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_STARTUP_DELAY 0
#define VDAC_Synth_UAB_PARAM_ALIGN_MODE    0

#define VDAC_Synth_UAB_NONZERO_STARTUP_DELAY (VDAC_Synth_UAB_Nonzero( \
	(0|0) ))
#define VDAC_Synth_UAB_DEFAULT_STARTUP_DELAY ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_STARTUP_DELAY)<<VDAC_Synth_UAB_STARTUP_DELAY_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_ALIGN_MODE)<<VDAC_Synth_UAB_ALIGN_MODE_SHIFT) \
))

#define VDAC_Synth_UAB_PARAM_SUBSAMPLE 0    
#define VDAC_Synth_UAB_PARAM_SUBSAMPLE_INIT 0    
    
#define VDAC_Synth_UAB_NONZERO_SUBSAMPLE_CTRL (VDAC_Synth_UAB_Nonzero( \
    (0|0) ))
#define VDAC_Synth_UAB_DEFAULT_SUBSAMPLE_CTRL ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_SUBSAMPLE)<<VDAC_Synth_UAB_SUBSAMPLE_SHIFT) |\
    (((uint32)VDAC_Synth_UAB_PARAM_SUBSAMPLE_INIT)<<VDAC_Synth_UAB_SUBSAMPLE_INIT_SHIFT) \
))
    
#define VDAC_Synth_UAB_PARAM_LAST_STEP  3

/*trigger_in source from cyfitter.h*/
#define VDAC_Synth_UAB_PARAM_TRIG_SEL    (VDAC_Synth_UAB_UnmappedIsZero(VDAC_Synth_UAB_halfuab__TRIG_SEL))

#define VDAC_Synth_UAB_PARAM_TRIGGER_EN 0

/*
#define VDAC_Synth_UAB_NONZERO_SRAM_CTRL (VDAC_Synth_UAB_Nonzero( \
    (3|0|0) ))
*/
/* force inclusion in _initPairs */
#define VDAC_Synth_UAB_NONZERO_SRAM_CTRL (VDAC_Synth_UAB_Nonzero(1))    
 
#define VDAC_Synth_UAB_DEFAULT_SRAM_CTRL ((uint32)(\
    (((uint32)VDAC_Synth_UAB_PARAM_LAST_STEP)<<VDAC_Synth_UAB_LAST_STEP_SHIFT) | \
    (((uint32)VDAC_Synth_UAB_PARAM_TRIG_SEL)<<VDAC_Synth_UAB_TRIG_SEL_SHIFT)   | \
    (((uint32)VDAC_Synth_UAB_PARAM_TRIGGER_EN)<<VDAC_Synth_UAB_TRIGGER_EN_SHIFT) \
))
/*There is intentionally no run bit symbol parameter and the run bit is not set as part of the Init() function*/

#define VDAC_Synth_UAB_PARAM_WAVE_STEP_0  15121
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_1  11778
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_2  3590
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_3  0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_4  0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_5  0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_6  0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_7  0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_8  0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_9  0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_10 0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_11 0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_12 0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_13 0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_14 0
#define VDAC_Synth_UAB_PARAM_WAVE_STEP_15 0

#define VDAC_Synth_UAB_NONZERO_WAVE_0  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_0 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_1  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_1 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_2  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_2 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_3  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_3 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_4  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_4 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_5  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_5 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_6  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_6 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_7  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_7 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_8  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_8 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_9  (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_9 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_10 (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_10 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_11 (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_11 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_12 (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_12 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_13 (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_13 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_14 (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_14 ) )
#define VDAC_Synth_UAB_NONZERO_WAVE_15 (VDAC_Synth_UAB_Nonzero( VDAC_Synth_UAB_PARAM_WAVE_STEP_15 ) )


/*all wave steps up to and including the last non-zero wave step 
    are included in the waveConfig array definition */
/*always include WAVE_STEP_0, since LAST_STEP minimum is 0*/
#define VDAC_Synth_UAB_INC_STEP_0 (VDAC_Synth_UAB_Nonzero(1))

#define VDAC_Synth_UAB_INC_STEP_1  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_1  || \
    VDAC_Synth_UAB_NONZERO_WAVE_2  || VDAC_Synth_UAB_NONZERO_WAVE_3  || \
    VDAC_Synth_UAB_NONZERO_WAVE_4  || VDAC_Synth_UAB_NONZERO_WAVE_5  || \
    VDAC_Synth_UAB_NONZERO_WAVE_6  || VDAC_Synth_UAB_NONZERO_WAVE_7  || \
    VDAC_Synth_UAB_NONZERO_WAVE_8  || VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_2  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_2  || VDAC_Synth_UAB_NONZERO_WAVE_3  || \
    VDAC_Synth_UAB_NONZERO_WAVE_4  || VDAC_Synth_UAB_NONZERO_WAVE_5  || \
    VDAC_Synth_UAB_NONZERO_WAVE_6  || VDAC_Synth_UAB_NONZERO_WAVE_7  || \
    VDAC_Synth_UAB_NONZERO_WAVE_8  || VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_3  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_3  || \
    VDAC_Synth_UAB_NONZERO_WAVE_4  || VDAC_Synth_UAB_NONZERO_WAVE_5  || \
    VDAC_Synth_UAB_NONZERO_WAVE_6  || VDAC_Synth_UAB_NONZERO_WAVE_7  || \
    VDAC_Synth_UAB_NONZERO_WAVE_8  || VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_4  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_4  || VDAC_Synth_UAB_NONZERO_WAVE_5  || \
    VDAC_Synth_UAB_NONZERO_WAVE_6  || VDAC_Synth_UAB_NONZERO_WAVE_7  || \
    VDAC_Synth_UAB_NONZERO_WAVE_8  || VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )

#define VDAC_Synth_UAB_INC_STEP_5  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_5  || \
    VDAC_Synth_UAB_NONZERO_WAVE_6  || VDAC_Synth_UAB_NONZERO_WAVE_7  || \
    VDAC_Synth_UAB_NONZERO_WAVE_8  || VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )

#define VDAC_Synth_UAB_INC_STEP_6  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_6  || VDAC_Synth_UAB_NONZERO_WAVE_7  || \
    VDAC_Synth_UAB_NONZERO_WAVE_8  || VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_7  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_7  || \
    VDAC_Synth_UAB_NONZERO_WAVE_8  || VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_8  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_8  || VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_9  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_9  || \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_10  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_10 || VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_11  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_11 || \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_12  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_12 || VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_13  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_13 || \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_14  ( \
    VDAC_Synth_UAB_NONZERO_WAVE_14 || VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
#define VDAC_Synth_UAB_INC_STEP_15  ( VDAC_Synth_UAB_NONZERO_WAVE_15 )
    
    
/*! @} group_init */

#endif /* #ifndef VDAC_Synth_UAB_PARAM_H */
    
/*! @endcond */

/* [] END OF FILE */
