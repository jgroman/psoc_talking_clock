/*!*****************************************************************************
* \file VDAC_UAB_regs.h
* \version 1.10
*
* \brief 
*   API for Universal Analog Block (UAB)
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
    
#ifndef VDAC_UAB_REGS_H
#define VDAC_UAB_REGS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VDAC_UAB_CyUAB_regs.h"

/*!
* \addtogroup group_general
* @{
*/

/*! Get right-aligned register field; mask parameter is alredy shifted */
#define VDAC_UAB_GET_FIELD(addr,mask,shift)         CyUAB_GET_FIELD((addr),(mask),(shift))
/*! Set register field without modifying other fields; mask parameter is already shifted */
#define VDAC_UAB_SET_FIELD(addr,mask,val,shift)     CyUAB_SET_FIELD((addr),(mask),(val),(shift))
/*! Set multiple register fields with a single register write; mask parameter is already shifted and composite of all fields being written */
#define VDAC_UAB_SET_VARIOUS_FIELDS(addr,mask,val)  CyUAB_SET_VARIOUS_FIELDS((addr), (mask), (val))

/*! number of array elements */
#define VDAC_UAB_ELEMENT_COUNT(x)  (sizeof((x))/sizeof((x)[0]))
/*! @} group_general */
    
    
#define VDAC_UAB_POSITION VDAC_UAB_halfuab__POSITION

#define VDAC_UAB_ISODD  ( (VDAC_UAB_POSITION % 2UL) != 0UL )


#define VDAC_UAB_BAD_XIN 0xabadc0deUL
	
/* x input terminals to VIN mapping selected by Creator P&R */

/* 
Decision tree below assigns unused x inputs to unused vin 
can't use preprocessor undef (MISRA requirement, so using a separate flag variable for each stage
VIN_FLAGS A-D track assigned vin assignments through the decision tree steps
*/

#define VDAC_UAB_VIN0_ASSIGNED  ( (\
        (VDAC_UAB_halfuab__X0==0) || (VDAC_UAB_halfuab__X1==0) || \
        (VDAC_UAB_halfuab__X2==0) || (VDAC_UAB_halfuab__X3==0) ) ? 1 : 0 )
#define VDAC_UAB_VIN1_ASSIGNED  ( (\
        (VDAC_UAB_halfuab__X0==1) || (VDAC_UAB_halfuab__X1==1) || \
        (VDAC_UAB_halfuab__X2==1) || (VDAC_UAB_halfuab__X3==1) ) ? 1 : 0 )
#define VDAC_UAB_VIN2_ASSIGNED  ( (\
        (VDAC_UAB_halfuab__X0==2) || (VDAC_UAB_halfuab__X1==2) || \
        (VDAC_UAB_halfuab__X2==2) || (VDAC_UAB_halfuab__X3==2) ) ? 1 : 0 )
#define VDAC_UAB_VIN3_ASSIGNED  ( (\
        (VDAC_UAB_halfuab__X0==3) || (VDAC_UAB_halfuab__X1==3) || \
        (VDAC_UAB_halfuab__X2==3) || (VDAC_UAB_halfuab__X3==3) ) ? 1 : 0 )


#define VDAC_UAB__X0_FLAGS  ( \
    ( (VDAC_UAB_VIN0_ASSIGNED)    ) | \
    ( (VDAC_UAB_VIN1_ASSIGNED)<<1 ) | \
    ( (VDAC_UAB_VIN2_ASSIGNED)<<2 ) | \
    ( (VDAC_UAB_VIN3_ASSIGNED)<<3 )   \
)
    
/*x0 input assignment*/
#if ( (0<=VDAC_UAB_halfuab__X0) && (VDAC_UAB_halfuab__X0<=3) )
    /*fitter assignment is valid*/
    #define VDAC_UAB_X0         (VDAC_UAB_halfuab__X0)
    #define VDAC_UAB__X1_FLAGS  (VDAC_UAB__X0_FLAGS)
#else
    /*x0 input is unused (==-1), so map to unused vin*/
    #if   (( VDAC_UAB__X0_FLAGS & 0x1 )==0)
        #define VDAC_UAB_X0 (0)
        #define VDAC_UAB__X1_FLAGS (VDAC_UAB__X0_FLAGS|0x1)
    #elif (( VDAC_UAB__X0_FLAGS & 0x2 )==0)
        #define VDAC_UAB_X0 (1)
        #define VDAC_UAB__X1_FLAGS (VDAC_UAB__X0_FLAGS|0x2)
    #elif (( VDAC_UAB__X0_FLAGS & 0x4 )==0)
        #define VDAC_UAB_X0 (2)
        #define VDAC_UAB__X1_FLAGS (VDAC_UAB__X0_FLAGS|0x4)
    #elif (( VDAC_UAB__X0_FLAGS & 0x8 )==0)
        #define VDAC_UAB_X0 (3)
        #define VDAC_UAB__X1_FLAGS (VDAC_UAB__X0_FLAGS|0x8)
    #else
        #error "VDAC_UAB_X0 mapping is bad"
    #endif
#endif

/*x1 input assignment*/
#if ( (0<=VDAC_UAB_halfuab__X1) && (VDAC_UAB_halfuab__X1<=3) )
    /*fitter assignment is valid*/
    #define VDAC_UAB_X1         (VDAC_UAB_halfuab__X1)
    #define VDAC_UAB__X2_FLAGS  (VDAC_UAB__X1_FLAGS)
#else
    /*x1 input is unused (==-1), so map to unused vin*/
    #if   (( VDAC_UAB__X1_FLAGS & 0x1 )==0)
        #define VDAC_UAB_X1 (0)
        #define VDAC_UAB__X2_FLAGS (VDAC_UAB__X1_FLAGS|0x1)
    #elif (( VDAC_UAB__X1_FLAGS & 0x2 )==0)
        #define VDAC_UAB_X1 (1)
        #define VDAC_UAB__X2_FLAGS (VDAC_UAB__X1_FLAGS|0x2)
    #elif (( VDAC_UAB__X1_FLAGS & 0x4 )==0)
        #define VDAC_UAB_X1 (2)
        #define VDAC_UAB__X2_FLAGS (VDAC_UAB__X1_FLAGS|0x4)
    #elif (( VDAC_UAB__X1_FLAGS & 0x8 )==0)
        #define VDAC_UAB_X1 (3)
        #define VDAC_UAB__X2_FLAGS (VDAC_UAB__X1_FLAGS|0x8)
    #else
        #error "VDAC_UAB_X1 mapping is bad"
    #endif
#endif

/*x2 input assignment*/
#if ( (0<=VDAC_UAB_halfuab__X2) && (VDAC_UAB_halfuab__X2<=3) )
    /*fitter assignment is valid*/
    #define VDAC_UAB_X2         (VDAC_UAB_halfuab__X2)
    #define VDAC_UAB__X3_FLAGS  (VDAC_UAB__X2_FLAGS)
#else
    /*x2 input is unused (==-1), so map to unused vin*/
    #if   (( VDAC_UAB__X2_FLAGS & 0x1 )==0)
        #define VDAC_UAB_X2 (0)
        #define VDAC_UAB__X3_FLAGS (VDAC_UAB__X2_FLAGS|0x1)
    #elif (( VDAC_UAB__X2_FLAGS & 0x2 )==0)
        #define VDAC_UAB_X2 (1)
        #define VDAC_UAB__X3_FLAGS (VDAC_UAB__X2_FLAGS|0x2)
    #elif (( VDAC_UAB__X2_FLAGS & 0x4 )==0)
        #define VDAC_UAB_X2 (2)
        #define VDAC_UAB__X3_FLAGS (VDAC_UAB__X2_FLAGS|0x4)
    #elif (( VDAC_UAB__X2_FLAGS & 0x8 )==0)
        #define VDAC_UAB_X2 (3)
        #define VDAC_UAB__X3_FLAGS (VDAC_UAB__X2_FLAGS|0x8)
    #else
        #error "VDAC_UAB_X2 mapping is bad"
    #endif
#endif

/*x3 input assignment*/
#if ( (0<=VDAC_UAB_halfuab__X3) && (VDAC_UAB_halfuab__X3<=3) )
    /*fitter assignment is valid*/
    #define VDAC_UAB_X3         (VDAC_UAB_halfuab__X3)
    #define VDAC_UAB__X4_FLAGS  (VDAC_UAB__X3_FLAGS)
#else
    /*x2 input is unused (==-1), so map to unused vin*/
    #if   (( VDAC_UAB__X3_FLAGS & 0x1 )==0)
        #define VDAC_UAB_X3 (0)
        #define VDAC_UAB__X4_FLAGS (VDAC_UAB__X3_FLAGS|0x1)
    #elif (( VDAC_UAB__X3_FLAGS & 0x2 )==0)
        #define VDAC_UAB_X3 (1)
        #define VDAC_UAB__X4_FLAGS (VDAC_UAB__X3_FLAGS|0x2)
    #elif (( VDAC_UAB__X3_FLAGS & 0x4 )==0)
        #define VDAC_UAB_X3 (2)
        #define VDAC_UAB__X4_FLAGS (VDAC_UAB__X3_FLAGS|0x4)
    #elif (( VDAC_UAB__X3_FLAGS & 0x8 )==0)
        #define VDAC_UAB_X3 (3)
        #define VDAC_UAB__X4_FLAGS (VDAC_UAB__X3_FLAGS|0x8)
    #else
        #error "VDAC_UAB_X3 mapping is bad"
    #endif
#endif

/*check results of mapping
1. All vin mapped
2. x0,x1,x2, and x3 are in range of 0 to 3
3. x0,x1,x2, and x3 are unique
*/
#if !( (VDAC_UAB__X4_FLAGS==0xF) && \
    ( (0<=VDAC_UAB_X0) && (VDAC_UAB_X0<=3) ) && \
    ( (0<=VDAC_UAB_X1) && (VDAC_UAB_X1<=3) ) && \
    ( (0<=VDAC_UAB_X2) && (VDAC_UAB_X2<=3) ) && \
    ( (0<=VDAC_UAB_X3) && (VDAC_UAB_X3<=3) ) && \
    (VDAC_UAB_X0!=VDAC_UAB_X1) && \
    (VDAC_UAB_X1!=VDAC_UAB_X2) && \
    (VDAC_UAB_X2!=VDAC_UAB_X3) )
#error "bad x input to vin mapping"
#endif

#define VDAC_UAB_XIN_COUNT 4UL



/* UAB half shared switch assymmetry special cases */
#define VDAC_UAB_AGND_TIED_ADDR (VDAC_UAB_halfuab__AGND_TIED)
#define VDAC_UAB_AGND_TIED_PTR  ((reg32*)VDAC_UAB_AGND_TIED_ADDR)
#define VDAC_UAB_AGND_TIED_REG  (*(VDAC_UAB_AGND_TIED_PTR))

#define VDAC_UAB_REF_TIED_PTR  ((reg32*)VDAC_UAB_halfuab__REF_TIED)
#define VDAC_UAB_REF_TIED_REG  (*(VDAC_UAB_REF_TIED_PTR))

#define VDAC_UAB_SW_AA_PTR     ((reg32*)VDAC_UAB_halfuab__SW_AA)
#define VDAC_UAB_SW_AA_REG     (*(VDAC_UAB_SW_AA_PTR))

#define VDAC_UAB_SW_BB_PTR     ((reg32*)VDAC_UAB_halfuab__SW_BB)
#define VDAC_UAB_SW_BB_REG     (*(VDAC_UAB_SW_BB_PTR))

#define VDAC_UAB_SW_CC_ADDR     (VDAC_UAB_halfuab__SW_CC)
#define VDAC_UAB_SW_CC_PTR     ((reg32*)VDAC_UAB_SW_CC_ADDR)
#define VDAC_UAB_SW_CC_REG     (*(VDAC_UAB_SW_CC_PTR))

#define VDAC_UAB_ISPAIRED      (VDAC_UAB_halfuab__ISPAIRED)

#define VDAC_UAB_UAB_CTRL_ADDR                 (VDAC_UAB_halfuab__UAB_CTRL)
#define VDAC_UAB_UAB_CTRL_PTR                 ((reg32*)VDAC_UAB_UAB_CTRL_ADDR)
#define VDAC_UAB_UAB_CTRL_REG                 (*(VDAC_UAB_UAB_CTRL_PTR))

#define VDAC_UAB_INTR_ADDR                     (VDAC_UAB_halfuab__INTR)
#define VDAC_UAB_INTR_PTR                     ((reg32*)VDAC_UAB_INTR_ADDR)
#define VDAC_UAB_INTR_REG                     (*(VDAC_UAB_INTR_PTR))

#define VDAC_UAB_INTR_SET_ADDR                 (VDAC_UAB_halfuab__INTR_SET)
#define VDAC_UAB_INTR_SET_PTR                 ((reg32*)VDAC_UAB_INTR_SET_ADDR)
#define VDAC_UAB_INTR_SET_REG                 (*(VDAC_UAB_INTR_SET_PTR))

#define VDAC_UAB_INTR_MASK_ADDR                (VDAC_UAB_halfuab__INTR_MASK)
#define VDAC_UAB_INTR_MASK_PTR                ((reg32*)VDAC_UAB_INTR_MASK_ADDR)
#define VDAC_UAB_INTR_MASK_REG                (*(VDAC_UAB_INTR_MASK_PTR))

#define VDAC_UAB_INTR_MASKED_ADDR              (VDAC_UAB_halfuab__INTR_MASKED)
#define VDAC_UAB_INTR_MASKED_PTR              ((reg32*)VDAC_UAB_INTR_MASKED_ADDR)
#define VDAC_UAB_INTR_MASKED_REG              (*(VDAC_UAB_INTR_MASKED_PTR))

#define VDAC_UAB_OA_CTRL_ADDR                  (VDAC_UAB_halfuab__OA_CTRL)
#define VDAC_UAB_OA_CTRL_PTR                  ((reg32*)VDAC_UAB_OA_CTRL_ADDR)
#define VDAC_UAB_OA_CTRL_REG                  (*(VDAC_UAB_OA_CTRL_PTR))

#define VDAC_UAB_CAP_CTRL_ADDR                 (VDAC_UAB_halfuab__CAP_CTRL)
#define VDAC_UAB_CAP_CTRL_PTR                 ((reg32*)VDAC_UAB_CAP_CTRL_ADDR)
#define VDAC_UAB_CAP_CTRL_REG                 (*(VDAC_UAB_CAP_CTRL_PTR))

#define VDAC_UAB_CAP_ABCF_VAL_ADDR             (VDAC_UAB_halfuab__CAP_ABCF_VAL)
#define VDAC_UAB_CAP_ABCF_VAL_PTR             ((reg32*)VDAC_UAB_CAP_ABCF_VAL_ADDR)
#define VDAC_UAB_CAP_ABCF_VAL_REG             (*(VDAC_UAB_CAP_ABCF_VAL_PTR))

#define VDAC_UAB_CAP_AB_VAL_NXT_ADDR           (VDAC_UAB_halfuab__CAP_AB_VAL_NXT)
#define VDAC_UAB_CAP_AB_VAL_NXT_PTR           ((reg32*)VDAC_UAB_CAP_AB_VAL_NXT_ADDR)
#define VDAC_UAB_CAP_AB_VAL_NXT_REG           (*(VDAC_UAB_CAP_AB_VAL_NXT_PTR))

#define VDAC_UAB_CAP_CF_VAL_NXT_ADDR           (VDAC_UAB_halfuab__CAP_CF_VAL_NXT)
#define VDAC_UAB_CAP_CF_VAL_NXT_PTR           ((reg32*)VDAC_UAB_CAP_CF_VAL_NXT_ADDR)
#define VDAC_UAB_CAP_CF_VAL_NXT_REG           (*(VDAC_UAB_CAP_CF_VAL_NXT_PTR))

#define VDAC_UAB_STARTUP_DELAY_ADDR            (VDAC_UAB_halfuab__STARTUP_DELAY)
#define VDAC_UAB_STARTUP_DELAY_PTR            ((reg32*)VDAC_UAB_STARTUP_DELAY_ADDR)
#define VDAC_UAB_STARTUP_DELAY_REG            (*(VDAC_UAB_STARTUP_DELAY_PTR))

#define VDAC_UAB_SUBSAMPLE_CTRL_ADDR           (VDAC_UAB_halfuab__SUBSAMPLE_CTRL)
#define VDAC_UAB_SUBSAMPLE_CTRL_PTR           ((reg32*)VDAC_UAB_SUBSAMPLE_CTRL_ADDR)
#define VDAC_UAB_SUBSAMPLE_CTRL_REG           (*(VDAC_UAB_SUBSAMPLE_CTRL_PTR))

#define VDAC_UAB_SW_STATIC_ADDR               (VDAC_UAB_halfuab__SW_STATIC )
#define VDAC_UAB_SW_STATIC_PTR                ((reg32*)VDAC_UAB_SW_STATIC_ADDR)
#define VDAC_UAB_SW_STATIC_REG                (*(VDAC_UAB_SW_STATIC_PTR))

#define VDAC_UAB_SW_MODBIT_SRC_ADDR            (VDAC_UAB_halfuab__SW_MODBIT_SRC)
#define VDAC_UAB_SW_MODBIT_SRC_PTR            ((reg32*)VDAC_UAB_SW_MODBIT_SRC_ADDR)
#define VDAC_UAB_SW_MODBIT_SRC_REG            (*(VDAC_UAB_SW_MODBIT_SRC_PTR))

#define VDAC_UAB_SW_CA_IN0_ADDR                (VDAC_UAB_halfuab__SW_CA_IN0)
#define VDAC_UAB_SW_CA_IN0_PTR                ((reg32*)VDAC_UAB_SW_CA_IN0_ADDR)
#define VDAC_UAB_SW_CA_IN0_REG                (*(VDAC_UAB_SW_CA_IN0_PTR))

#define VDAC_UAB_SW_CA_IN1_ADDR                (VDAC_UAB_halfuab__SW_CA_IN1)
#define VDAC_UAB_SW_CA_IN1_PTR                ((reg32*)VDAC_UAB_SW_CA_IN1_ADDR)
#define VDAC_UAB_SW_CA_IN1_REG                (*(VDAC_UAB_SW_CA_IN1_PTR))

#define VDAC_UAB_SW_CA_TOP_ADDR                (VDAC_UAB_halfuab__SW_CA_TOP)
#define VDAC_UAB_SW_CA_TOP_PTR                ((reg32*)VDAC_UAB_SW_CA_TOP_ADDR)
#define VDAC_UAB_SW_CA_TOP_REG                (*(VDAC_UAB_SW_CA_TOP_PTR))

#define VDAC_UAB_SW_CB_IN0_ADDR                (VDAC_UAB_halfuab__SW_CB_IN0)
#define VDAC_UAB_SW_CB_IN0_PTR                ((reg32*)VDAC_UAB_SW_CB_IN0_ADDR)
#define VDAC_UAB_SW_CB_IN0_REG                (*(VDAC_UAB_SW_CB_IN0_PTR))

#define VDAC_UAB_SW_CB_IN1_ADDR                (VDAC_UAB_halfuab__SW_CB_IN1)
#define VDAC_UAB_SW_CB_IN1_PTR                ((reg32*)VDAC_UAB_SW_CB_IN1_ADDR)
#define VDAC_UAB_SW_CB_IN1_REG                (*(VDAC_UAB_SW_CB_IN1_PTR))

#define VDAC_UAB_SW_CB_TOP_ADDR                (VDAC_UAB_halfuab__SW_CB_TOP)
#define VDAC_UAB_SW_CB_TOP_PTR                ((reg32*)VDAC_UAB_SW_CB_TOP_ADDR)
#define VDAC_UAB_SW_CB_TOP_REG                (*(VDAC_UAB_SW_CB_TOP_PTR))

#define VDAC_UAB_SW_CC_IN0_ADDR                (VDAC_UAB_halfuab__SW_CC_IN0)
#define VDAC_UAB_SW_CC_IN0_PTR                ((reg32*)VDAC_UAB_SW_CC_IN0_ADDR)
#define VDAC_UAB_SW_CC_IN0_REG                (*(VDAC_UAB_SW_CC_IN0_PTR))

#define VDAC_UAB_SW_CC_IN1_ADDR                (VDAC_UAB_halfuab__SW_CC_IN1)
#define VDAC_UAB_SW_CC_IN1_PTR                ((reg32*)VDAC_UAB_SW_CC_IN1_ADDR)
#define VDAC_UAB_SW_CC_IN1_REG                (*(VDAC_UAB_SW_CC_IN1_PTR))

#define VDAC_UAB_SW_CC_TOP_ADDR                (VDAC_UAB_halfuab__SW_CC_TOP)
#define VDAC_UAB_SW_CC_TOP_PTR                ((reg32*)VDAC_UAB_SW_CC_TOP_ADDR)
#define VDAC_UAB_SW_CC_TOP_REG                (*(VDAC_UAB_SW_CC_TOP_PTR))

#define VDAC_UAB_SW_CF_BOT_ADDR                (VDAC_UAB_halfuab__SW_CF_BOT)
#define VDAC_UAB_SW_CF_BOT_PTR                ((reg32*)VDAC_UAB_SW_CF_BOT_ADDR)
#define VDAC_UAB_SW_CF_BOT_REG                (*(VDAC_UAB_SW_CF_BOT_PTR))

#define VDAC_UAB_SW_OTHER_ADDR                 (VDAC_UAB_halfuab__SW_OTHER)
#define VDAC_UAB_SW_OTHER_PTR                 ((reg32*)VDAC_UAB_SW_OTHER_ADDR)
#define VDAC_UAB_SW_OTHER_REG                 (*(VDAC_UAB_SW_OTHER_PTR))

#define VDAC_UAB_SW_BOOST_CTRL_ADDR            (VDAC_UAB_halfuab__SW_BOOST_CTRL)
#define VDAC_UAB_SW_BOOST_CTRL_PTR            ((reg32*)VDAC_UAB_SW_BOOST_CTRL_ADDR)
#define VDAC_UAB_SW_BOOST_CTRL_REG            (*(VDAC_UAB_SW_BOOST_CTRL_PTR))

#define VDAC_UAB_SRAM_CTRL_ADDR                (VDAC_UAB_halfuab__SRAM_CTRL)
#define VDAC_UAB_SRAM_CTRL_PTR                ((reg32*)VDAC_UAB_SRAM_CTRL_ADDR)
#define VDAC_UAB_SRAM_CTRL_REG                (*(VDAC_UAB_SRAM_CTRL_PTR))

#define VDAC_UAB_STAT_ADDR                     (VDAC_UAB_halfuab__STAT)
#define VDAC_UAB_STAT_PTR                     ((reg32*)VDAC_UAB_STAT_ADDR)
#define VDAC_UAB_STAT_REG                     (*(VDAC_UAB_STAT_PTR))

#define VDAC_UAB_SRAM0_ADDR                    (VDAC_UAB_halfuab__SRAM0)
#define VDAC_UAB_SRAM0_PTR                    ((reg32*)VDAC_UAB_SRAM0_ADDR)
#define VDAC_UAB_SRAM0_REG                    (*(VDAC_UAB_SRAM0_PTR))

#define VDAC_UAB_SRAM1_ADDR                    (VDAC_UAB_halfuab__SRAM1)
#define VDAC_UAB_SRAM1_PTR                    ((reg32*)VDAC_UAB_SRAM1_ADDR)
#define VDAC_UAB_SRAM1_REG                    (*(VDAC_UAB_SRAM1_PTR))

#define VDAC_UAB_SRAM2_ADDR                    (VDAC_UAB_halfuab__SRAM2)
#define VDAC_UAB_SRAM2_PTR                    ((reg32*)VDAC_UAB_SRAM2_ADDR)
#define VDAC_UAB_SRAM2_REG                    (*(VDAC_UAB_SRAM2_PTR))

#define VDAC_UAB_SRAM3_ADDR                    (VDAC_UAB_halfuab__SRAM3)
#define VDAC_UAB_SRAM3_PTR                    ((reg32*)VDAC_UAB_SRAM3_ADDR)
#define VDAC_UAB_SRAM3_REG                    (*(VDAC_UAB_SRAM3_PTR))

#define VDAC_UAB_SRAM4_ADDR                    (VDAC_UAB_halfuab__SRAM4)
#define VDAC_UAB_SRAM4_PTR                    ((reg32*)VDAC_UAB_SRAM4_ADDR)
#define VDAC_UAB_SRAM4_REG                    (*(VDAC_UAB_SRAM4_PTR))

#define VDAC_UAB_SRAM5_ADDR                    (VDAC_UAB_halfuab__SRAM5)
#define VDAC_UAB_SRAM5_PTR                    ((reg32*)VDAC_UAB_SRAM5_ADDR)
#define VDAC_UAB_SRAM5_REG                    (*(VDAC_UAB_SRAM5_PTR))

#define VDAC_UAB_SRAM6_ADDR                    (VDAC_UAB_halfuab__SRAM6)
#define VDAC_UAB_SRAM6_PTR                    ((reg32*)VDAC_UAB_SRAM6_ADDR)
#define VDAC_UAB_SRAM6_REG                    (*(VDAC_UAB_SRAM6_PTR))

#define VDAC_UAB_SRAM7_ADDR                    (VDAC_UAB_halfuab__SRAM7)
#define VDAC_UAB_SRAM7_PTR                    ((reg32*)VDAC_UAB_SRAM7_ADDR)
#define VDAC_UAB_SRAM7_REG                    (*(VDAC_UAB_SRAM7_PTR))

#define VDAC_UAB_SRAM8_ADDR                    (VDAC_UAB_halfuab__SRAM8)
#define VDAC_UAB_SRAM8_PTR                    ((reg32*)VDAC_UAB_SRAM8_ADDR)
#define VDAC_UAB_SRAM8_REG                    (*(VDAC_UAB_SRAM8_PTR))

#define VDAC_UAB_SRAM9_ADDR                    (VDAC_UAB_halfuab__SRAM9)
#define VDAC_UAB_SRAM9_PTR                    ((reg32*)VDAC_UAB_SRAM9_ADDR)
#define VDAC_UAB_SRAM9_REG                    (*(VDAC_UAB_SRAM9_PTR))

#define VDAC_UAB_SRAM10_ADDR                   (VDAC_UAB_halfuab__SRAM10)
#define VDAC_UAB_SRAM10_PTR                   ((reg32*)VDAC_UAB_SRAM10_ADDR)
#define VDAC_UAB_SRAM10_REG                   (*(VDAC_UAB_SRAM10_PTR))

#define VDAC_UAB_SRAM11_ADDR                   (VDAC_UAB_halfuab__SRAM11)
#define VDAC_UAB_SRAM11_PTR                   ((reg32*)VDAC_UAB_SRAM11_ADDR)
#define VDAC_UAB_SRAM11_REG                   (*(VDAC_UAB_SRAM11_PTR))

#define VDAC_UAB_SRAM12_ADDR                   (VDAC_UAB_halfuab__SRAM12)
#define VDAC_UAB_SRAM12_PTR                   ((reg32*)VDAC_UAB_SRAM12_ADDR)
#define VDAC_UAB_SRAM12_REG                   (*(VDAC_UAB_SRAM12_PTR))

#define VDAC_UAB_SRAM13_ADDR                   (VDAC_UAB_halfuab__SRAM13)
#define VDAC_UAB_SRAM13_PTR                   ((reg32*)VDAC_UAB_SRAM13_ADDR)
#define VDAC_UAB_SRAM13_REG                   (*(VDAC_UAB_SRAM13_PTR))

#define VDAC_UAB_SRAM14_ADDR                   (VDAC_UAB_halfuab__SRAM14)
#define VDAC_UAB_SRAM14_PTR                   ((reg32*)VDAC_UAB_SRAM14_ADDR)
#define VDAC_UAB_SRAM14_REG                   (*(VDAC_UAB_SRAM14_PTR))

#define VDAC_UAB_SRAM15_ADDR                   (VDAC_UAB_halfuab__SRAM15)
#define VDAC_UAB_SRAM15_PTR                   ((reg32*)VDAC_UAB_SRAM15_ADDR)
#define VDAC_UAB_SRAM15_REG                   (*(VDAC_UAB_SRAM15_PTR))

#define VDAC_UAB_SW_CC1_IN0_ADDR               (VDAC_UAB_halfuab__SW_CC1_IN0)
#define VDAC_UAB_SW_CC1_IN0_PTR               ((reg32*)VDAC_UAB_SW_CC1_IN0_ADDR)
#define VDAC_UAB_SW_CC1_IN0_REG               (*(VDAC_UAB_SW_CC1_IN0_PTR))

#define VDAC_UAB_SW_CC1_IN1_ADDR               (VDAC_UAB_halfuab__SW_CC1_IN1)
#define VDAC_UAB_SW_CC1_IN1_PTR               ((reg32*)VDAC_UAB_SW_CC1_IN1_ADDR)
#define VDAC_UAB_SW_CC1_IN1_REG               (*(VDAC_UAB_SW_CC1_IN1_PTR))

#define VDAC_UAB_SW_CC1_TOP_ADDR               (VDAC_UAB_halfuab__SW_CC1_TOP)
#define VDAC_UAB_SW_CC1_TOP_PTR               ((reg32*)VDAC_UAB_SW_CC1_TOP_ADDR)
#define VDAC_UAB_SW_CC1_TOP_REG               (*(VDAC_UAB_SW_CC1_TOP_PTR))

#define VDAC_UAB_CAP_TRIM_ADDR                 (VDAC_UAB_halfuab__CAP_TRIM)
#define VDAC_UAB_CAP_TRIM_PTR                 ((reg32*)VDAC_UAB_CAP_TRIM_ADDR)
#define VDAC_UAB_CAP_TRIM_REG                 (*(VDAC_UAB_CAP_TRIM_PTR))

#define VDAC_UAB_OA_TRIM_ADDR                  (VDAC_UAB_halfuab__OA_TRIM)
#define VDAC_UAB_OA_TRIM_PTR                  ((reg32*)VDAC_UAB_OA_TRIM_ADDR)
#define VDAC_UAB_OA_TRIM_REG                  (*(VDAC_UAB_OA_TRIM_PTR))

/* Starting address for half UAB region */
#define VDAC_UAB_BASE_ADDR                    (VDAC_UAB_halfuab__OA_CTRL)
    



/*Register Field Definitions*/

    
/*UAB_CTRL*/
#define VDAC_UAB_ENABLED_SHIFT                CyUAB_ENABLED_SHIFT
#define VDAC_UAB_ENABLED_MASK                 (1UL<<VDAC_UAB_ENABLED_SHIFT)


/*INTR*/
#if VDAC_UAB_ISODD==1
    #define VDAC_UAB_INTR_COMP_SHIFT CyUAB_INTR_COMP1_SHIFT
#else
    #define VDAC_UAB_INTR_COMP_SHIFT CyUAB_INTR_COMP0_SHIFT
#endif
#define VDAC_UAB_INTR_COMP_MASK               (1UL<<VDAC_UAB_INTR_COMP_SHIFT)

#if VDAC_UAB_ISODD==1
   #define VDAC_UAB_INTR_VDAC_EMPTY_SHIFT CyUAB_INTR_VDAC1_EMPTY_SHIFT
#else
   #define VDAC_UAB_INTR_VDAC_EMPTY_SHIFT CyUAB_INTR_VDAC0_EMPTY_SHIFT
#endif
#define VDAC_UAB_INTR_VDAC_EMPTY_MASK         (1UL<<VDAC_UAB_INTR_VDAC_EMPTY_SHIFT)


/*INTR_SET*/
#define VDAC_UAB_INTR_COMP_SET_SHIFT          VDAC_UAB_INTR_COMP_SHIFT
#define VDAC_UAB_INTR_COMP_SET_MASK           (1UL<<VDAC_UAB_INTR_COMP_SET_SHIFT)

#define VDAC_UAB_INTR_VDAC_EMPTY_SET_SHIFT    VDAC_UAB_INTR_VDAC_EMPTY_SHIFT
#define VDAC_UAB_INTR_VDAC_EMPTY_SET_MASK     (1UL<<VDAC_UAB_INTR_VDAC_EMPTY_SET_SHIFT)


/*INTR_MASK*/
#define VDAC_UAB_INTR_COMP_MASK_SHIFT         VDAC_UAB_INTR_COMP_SHIFT
#define VDAC_UAB_INTR_COMP_MASK_MASK          (1UL<<VDAC_UAB_INTR_COMP_MASK_SHIFT)

#define VDAC_UAB_INTR_VDAC_EMPTY_MASK_SHIFT   VDAC_UAB_INTR_VDAC_EMPTY_SHIFT
#define VDAC_UAB_INTR_VDAC_EMPTY_MASK_MASK    (1UL<<VDAC_UAB_INTR_VDAC_EMPTY_MASK_SHIFT)


/*INTR_MASKED*/
#define VDAC_UAB_INTR_COMP_MASKED_SHIFT       VDAC_UAB_INTR_COMP_SHIFT
#define VDAC_UAB_INTR_COMP_MASKED_MASK        (1UL<<VDAC_UAB_INTR_COMP_MASKED_SHIFT)

#define VDAC_UAB_INTR_VDAC_EMPTY_MASKED_SHIFT VDAC_UAB_INTR_VDAC_EMPTY_SHIFT
#define VDAC_UAB_INTR_VDAC_EMPTY_MASKED_MASK  (1UL<<VDAC_UAB_INTR_VDAC_EMPTY_MASKED_SHIFT)


/*OA_CTRL*/
#define VDAC_UAB_OA_PWR_SHIFT                 CyUAB_OA_PWR_SHIFT
#define VDAC_UAB_OA_PWR_MASK                  (0x7UL<<VDAC_UAB_OA_PWR_SHIFT)

#define VDAC_UAB_CMP_PWR_SHIFT                CyUAB_CMP_PWR_SHIFT
#define VDAC_UAB_CMP_PWR_MASK                 (0x7UL<<VDAC_UAB_CMP_PWR_SHIFT)

#define VDAC_UAB_CMP_EDGE_SHIFT               CyUAB_CMP_EDGE_SHIFT
#define VDAC_UAB_CMP_EDGE_MASK                (0x3UL<<VDAC_UAB_CMP_EDGE_SHIFT)
#define VDAC_UAB_CMP_EDGE_DISABLE             (0UL)
#define VDAC_UAB_CMP_EDGE_RISING              (1UL)
#define VDAC_UAB_CMP_EDGE_FALLING             (2UL)
#define VDAC_UAB_CMP_EDGE_BOTH                (3UL)

#define VDAC_UAB_CMP_DSI_LEVEL_SHIFT          CyUAB_CMP_DSI_LEVEL_SHIFT
#define VDAC_UAB_CMP_DSI_LEVEL_MASK           (1UL<<VDAC_UAB_CMP_DSI_LEVEL_SHIFT)

#define VDAC_UAB_CTRL_SPARE_SHIFT             CyUAB_CTRL_SPARE_SHIFT
#define VDAC_UAB_CTRL_SPARE_MASK              (1UL<<VDAC_UAB_CTRL_SPARE_SHIFT)

#define VDAC_UAB_REF_PWR_SHIFT                CyUAB_REF_PWR_SHIFT
#define VDAC_UAB_REF_PWR_MASK                 (0x7UL<<VDAC_UAB_REF_PWR_SHIFT)

#define VDAC_UAB_REF_PTS_SHIFT                CyUAB_REF_PTS_SHIFT
#define VDAC_UAB_REF_PTS_MASK                 (1UL<<VDAC_UAB_REF_PTS_SHIFT)

#define VDAC_UAB_AGND_PWR_SHIFT               CyUAB_AGND_PWR_SHIFT
#define VDAC_UAB_AGND_PWR_MASK                (0x7UL<<VDAC_UAB_AGND_PWR_SHIFT)

#define VDAC_UAB_AGND_PTS_SHIFT               CyUAB_AGND_PTS_SHIFT
#define VDAC_UAB_AGND_PTS_MASK                (1UL<<VDAC_UAB_AGND_PTS_SHIFT)

#define VDAC_UAB_AGND_TIED_SHIFT              CyUAB_AGND_TIED_SHIFT
#define VDAC_UAB_AGND_TIED_MASK               (1UL<<VDAC_UAB_AGND_TIED_SHIFT)

#define VDAC_UAB_REF_TIED_SHIFT               CyUAB_REF_TIED_SHIFT
#define VDAC_UAB_REF_TIED_MASK                (1UL<<VDAC_UAB_REF_TIED_SHIFT)    
    
#define VDAC_UAB_UAB_PWR_SHIFT                CyUAB_UAB_PWR_SHIFT
#define VDAC_UAB_UAB_PWR_MASK                 (0x3UL<<VDAC_UAB_UAB_PWR_SHIFT)
#define VDAC_UAB_UAB_PWR_NORMAL               (0UL)
#define VDAC_UAB_UAB_PWR_ULTRA_LOW            (1UL)
#define VDAC_UAB_UAB_PWR_ULTRA_HIGH           (2UL)
#define VDAC_UAB_UAB_PWR_Reserved             (3UL)


/*CAP_CTRL*/
#define VDAC_UAB_CB_GND_SHIFT                 CyUAB_CB_GND_SHIFT
#define VDAC_UAB_CB_GND_MASK                  (1UL<<VDAC_UAB_CB_GND_SHIFT)

#define VDAC_UAB_CC_GND_SHIFT                 CyUAB_CC_GND_SHIFT
#define VDAC_UAB_CC_GND_MASK                  (1UL<<VDAC_UAB_CC_GND_SHIFT)

#define VDAC_UAB_FRC_SIGN_BIT_SHIFT           CyUAB_FRC_SIGN_BIT_SHIFT
#define VDAC_UAB_FRC_SIGN_BIT_MASK            (1UL<<CyUAB_FRC_SIGN_BIT_SHIFT)

#define VDAC_UAB_DAC_MODE_EN_SHIFT            CyUAB_DAC_MODE_EN_SHIFT
#define VDAC_UAB_DAC_MODE_EN_MASK             (1UL<<VDAC_UAB_DAC_MODE_EN_SHIFT)

#define VDAC_UAB_DAC_MODE_SHIFT               CyUAB_DAC_MODE_SHIFT
#define VDAC_UAB_DAC_MODE_MASK                (0x3UL<<VDAC_UAB_DAC_MODE_SHIFT)
#define VDAC_UAB_DAC_MODE_UNSIGNED12          (0UL)
#define VDAC_UAB_DAC_MODE_VIRT_SIGNED12       (1UL)
#define VDAC_UAB_DAC_MODE_SIGNED13            (2UL)
#define VDAC_UAB_DAC_MODE_RESERVED            (3UL)


/*CAP_ABCF_VAL, CAP_AB_VAL_NXT, and CAP_CF_VAL_NXT*/
#define VDAC_UAB_CB_VAL_SHIFT                 CyUAB_CB_VAL_SHIFT
#define VDAC_UAB_CB_VAL_MASK                  (0x3fUL<<VDAC_UAB_CB_VAL_SHIFT)

#define VDAC_UAB_CA_VAL_SHIFT                 CyUAB_CA_VAL_SHIFT
#define VDAC_UAB_CA_VAL_MASK                  (0x3fUL<<VDAC_UAB_CA_VAL_SHIFT)

#define VDAC_UAB_SIGN_VAL_SHIFT               CyUAB_SIGN_VAL_SHIFT
#define VDAC_UAB_SIGN_VAL_MASK                (1UL<<VDAC_UAB_SIGN_VAL_SHIFT)

#define VDAC_UAB_CB_64_SHIFT                  CyUAB_CB_64_SHIFT
#define VDAC_UAB_CB_64_MASK                   (1UL<<VDAC_UAB_CB_64_SHIFT)

#define VDAC_UAB_CC_VAL_SHIFT                 CyUAB_CC_VAL_SHIFT
#define VDAC_UAB_CC_VAL_MASK                  (0x3fUL<<VDAC_UAB_CC_VAL_SHIFT)

#define VDAC_UAB_CF_VAL_SHIFT                 CyUAB_CF_VAL_SHIFT
#define VDAC_UAB_CF_VAL_MASK                  (0x1fUL<<VDAC_UAB_CF_VAL_SHIFT)


/*CAP_CF_VAL_NXT*/
#define VDAC_UAB_CC_VAL_UPDATE_SHIFT          CyUAB_CC_VAL_UPDATE_SHIFT
#define VDAC_UAB_CC_VAL_UPDATE_MASK           (1UL<<VDAC_UAB_CC_VAL_UPDATE_SHIFT)

#define VDAC_UAB_CF_VAL_UPDATE_SHIFT          CyUAB_CF_VAL_UPDATE_SHIFT
#define VDAC_UAB_CF_VAL_UPDATE_MASK           (1UL<<VDAC_UAB_CF_VAL_UPDATE_SHIFT)


/*STARTUP_DELAY*/
#define VDAC_UAB_STARTUP_DELAY_SHIFT          CyUAB_STARTUP_DELAY_SHIFT
#define VDAC_UAB_STARTUP_DELAY_MASK           (0x0000ffffUL)

#define VDAC_UAB_ALIGN_MODE_SHIFT             CyUAB_ALIGN_MODE_SHIFT
#define VDAC_UAB_ALIGN_MODE_MASK              (1UL<<VDAC_UAB_ALIGN_MODE_SHIFT)


/*SUBSAMPLE_CTRL*/
#define VDAC_UAB_SUBSAMPLE_SHIFT              CyUAB_SUBSAMPLE_SHIFT
#define VDAC_UAB_SUBSAMPLE_MASK               (0xffUL<<VDAC_UAB_SUBSAMPLE_SHIFT)

#define VDAC_UAB_SUBSAMPLE_INIT_SHIFT         CyUAB_SUBSAMPLE_INIT_SHIFT
#define VDAC_UAB_SUBSAMPLE_INIT_MASK          (0xffUL<<VDAC_UAB_SUBSAMPLE_INIT_SHIFT)


/*SW_STATIC*/
#define VDAC_UAB_SW_G0_SHIFT                  CyUAB_SW_G0_SHIFT
#define VDAC_UAB_SW_G0_MASK                   (1UL<<VDAC_UAB_SW_G0_SHIFT)

#define VDAC_UAB_SW_G1_SHIFT                  CyUAB_SW_G1_SHIFT
#define VDAC_UAB_SW_G1_MASK                   (1UL<<VDAC_UAB_SW_G1_SHIFT)

#define VDAC_UAB_SW_G2_SHIFT                  CyUAB_SW_G2_SHIFT
#define VDAC_UAB_SW_G2_MASK                   (1UL<<VDAC_UAB_SW_G2_SHIFT)

#define VDAC_UAB_SW_G3_SHIFT                  CyUAB_SW_G3_SHIFT
#define VDAC_UAB_SW_G3_MASK                   (1UL<<VDAC_UAB_SW_G3_SHIFT)

#define VDAC_UAB_SW_RG_SHIFT                  CyUAB_SW_RG_SHIFT
#define VDAC_UAB_SW_RG_MASK                   (1UL<<VDAC_UAB_SW_RG_SHIFT)

#define VDAC_UAB_SW_GG_SHIFT                  CyUAB_SW_GG_SHIFT
#define VDAC_UAB_SW_GG_MASK                   (1UL<<VDAC_UAB_SW_GG_SHIFT)

#define VDAC_UAB_SW_RT_SHIFT                  CyUAB_SW_RT_SHIFT
#define VDAC_UAB_SW_RT_MASK                   (1UL<<VDAC_UAB_SW_RT_SHIFT)

#define VDAC_UAB_SW_GT_SHIFT                  CyUAB_SW_GT_SHIFT
#define VDAC_UAB_SW_GT_MASK                   (1UL<<VDAC_UAB_SW_GT_SHIFT)

#define VDAC_UAB_SW_QT_SHIFT                  CyUAB_SW_QT_SHIFT
#define VDAC_UAB_SW_QT_MASK                   (1UL<<VDAC_UAB_SW_QT_SHIFT)

#define VDAC_UAB_EARLY_PS_SHIFT               CyUAB_EARLY_PS_SHIFT
#define VDAC_UAB_EARLY_PS_MASK                (1UL<<VDAC_UAB_EARLY_PS_SHIFT)

#define VDAC_UAB_EARLY_PO_SHIFT               CyUAB_EARLY_PO_SHIFT
#define VDAC_UAB_EARLY_PO_MASK                (1UL<<VDAC_UAB_EARLY_PO_SHIFT)

#define VDAC_UAB_STRB_RST_SEL_SHIFT           CyUAB_STRB_RST_SEL_SHIFT
#define VDAC_UAB_STRB_RST_SEL_MASK            (0x1fUL<<VDAC_UAB_STRB_RST_SEL_SHIFT)

#define VDAC_UAB_STRB_RST_EN_SHIFT            CyUAB_STRB_RST_EN_SHIFT
#define VDAC_UAB_STRB_RST_EN_MASK             (1UL<<VDAC_UAB_STRB_RST_EN_SHIFT)


/*SW_MODBIT_SRC*/
#define VDAC_UAB_MODBIT0_SRC_SEL_SHIFT        CyUAB_MODBIT0_SRC_SEL_SHIFT
#define VDAC_UAB_MODBIT0_SRC_SEL_MASK         (0x1fUL<<VDAC_UAB_MODBIT0_SRC_SEL_SHIFT)

#define VDAC_UAB_MODBIT1_SRC_SEL_SHIFT        CyUAB_MODBIT1_SRC_SEL_SHIFT
#define VDAC_UAB_MODBIT1_SRC_SEL_MASK         (0x1fUL<<VDAC_UAB_MODBIT1_SRC_SEL_SHIFT)


/*SW_CA_IN0*/
#define VDAC_UAB_SW_A0_MODBIT_SHIFT           CyUAB_SW_A0_MODBIT_SHIFT
#define VDAC_UAB_SW_A0_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_A0_MODBIT_SHIFT)

#define VDAC_UAB_SW_A1_MODBIT_SHIFT           CyUAB_SW_A1_MODBIT_SHIFT
#define VDAC_UAB_SW_A1_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_A1_MODBIT_SHIFT)

#define VDAC_UAB_SW_A2_MODBIT_SHIFT           CyUAB_SW_A2_MODBIT_SHIFT
#define VDAC_UAB_SW_A2_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_A2_MODBIT_SHIFT)

#define VDAC_UAB_SW_A3_MODBIT_SHIFT           CyUAB_SW_A3_MODBIT_SHIFT
#define VDAC_UAB_SW_A3_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_A3_MODBIT_SHIFT)

#define VDAC_UAB_SW_AP_SHIFT                  CyUAB_SW_AP_SHIFT
#define VDAC_UAB_SW_AP_MASK                   (0xfUL<<VDAC_UAB_SW_AP_SHIFT)

#define VDAC_UAB_SW_AQ_SHIFT                  CyUAB_SW_AQ_SHIFT
#define VDAC_UAB_SW_AQ_MASK                   (0xfUL<<VDAC_UAB_SW_AQ_SHIFT)

/*SW_CA_IN1*/    
#define VDAC_UAB_SW_AA_SHIFT                  CyUAB_SW_AA_SHIFT
#define VDAC_UAB_SW_AA_MASK                   (0xfUL<<VDAC_UAB_SW_AA_SHIFT)

#define VDAC_UAB_SW_AR_MODBIT_SHIFT           CyUAB_SW_AR_MODBIT_SHIFT
#define VDAC_UAB_SW_AR_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_AR_MODBIT_SHIFT)

#define VDAC_UAB_SW_AG_MODBIT_SHIFT           CyUAB_SW_AG_MODBIT_SHIFT
#define VDAC_UAB_SW_AG_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_AG_MODBIT_SHIFT)

#define VDAC_UAB_SW_AV_MODBIT_SHIFT           CyUAB_SW_AV_MODBIT_SHIFT
#define VDAC_UAB_SW_AV_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_AV_MODBIT_SHIFT)


/*SW_CA_TOP*/
#define VDAC_UAB_SW_RA_MODBIT_SHIFT           CyUAB_SW_RA_MODBIT_SHIFT
#define VDAC_UAB_SW_RA_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_RA_MODBIT_SHIFT)

#define VDAC_UAB_SW_GA_MODBIT_SHIFT           CyUAB_SW_GA_MODBIT_SHIFT
#define VDAC_UAB_SW_GA_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_GA_MODBIT_SHIFT)

#define VDAC_UAB_SW_VA_MODBIT_SHIFT           CyUAB_SW_VA_MODBIT_SHIFT
#define VDAC_UAB_SW_VA_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_VA_MODBIT_SHIFT)

#define VDAC_UAB_SW_SA_SHIFT                  CyUAB_SW_SA_SHIFT
#define VDAC_UAB_SW_SA_MASK                   (0xfUL<<VDAC_UAB_SW_SA_SHIFT)


/*SW_CB_IN0*/
#define VDAC_UAB_SW_B0_MODBIT_SHIFT           CyUAB_SW_B0_MODBIT_SHIFT
#define VDAC_UAB_SW_B0_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_B0_MODBIT_SHIFT)

#define VDAC_UAB_SW_B1_MODBIT_SHIFT           CyUAB_SW_B1_MODBIT_SHIFT
#define VDAC_UAB_SW_B1_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_B1_MODBIT_SHIFT)

#define VDAC_UAB_SW_B2_MODBIT_SHIFT           CyUAB_SW_B2_MODBIT_SHIFT
#define VDAC_UAB_SW_B2_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_B2_MODBIT_SHIFT)

#define VDAC_UAB_SW_B3_MODBIT_SHIFT           CyUAB_SW_B3_MODBIT_SHIFT
#define VDAC_UAB_SW_B3_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_B3_MODBIT_SHIFT)

#define VDAC_UAB_SW_BP_SHIFT                  CyUAB_SW_BP_SHIFT
#define VDAC_UAB_SW_BP_MASK                   (0xfUL<<VDAC_UAB_SW_BP_SHIFT)

#define VDAC_UAB_SW_BQ_SHIFT                  CyUAB_SW_BQ_SHIFT
#define VDAC_UAB_SW_BQ_MASK                   (0xfUL<<VDAC_UAB_SW_BQ_SHIFT)


/*SW_CB_IN1*/
#define VDAC_UAB_SW_BB_SHIFT                  CyUAB_SW_BB_SHIFT
#define VDAC_UAB_SW_BB_MASK                   (0xfUL<<VDAC_UAB_SW_BB_SHIFT)

#define VDAC_UAB_SW_BR_MODBIT_SHIFT           CyUAB_SW_BR_MODBIT_SHIFT
#define VDAC_UAB_SW_BR_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_BR_MODBIT_SHIFT)

#define VDAC_UAB_SW_BG_MODBIT_SHIFT           CyUAB_SW_BG_MODBIT_SHIFT
#define VDAC_UAB_SW_BG_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_BG_MODBIT_SHIFT)

#define VDAC_UAB_SW_BV_MODBIT_SHIFT           CyUAB_SW_BV_MODBIT_SHIFT
#define VDAC_UAB_SW_BV_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_BV_MODBIT_SHIFT)


/*SW_CB_TOP*/
#define VDAC_UAB_SW_RB_MODBIT_SHIFT           CyUAB_SW_RB_MODBIT_SHIFT
#define VDAC_UAB_SW_RB_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_RB_MODBIT_SHIFT)

#define VDAC_UAB_SW_GB_MODBIT_SHIFT           CyUAB_SW_GB_MODBIT_SHIFT
#define VDAC_UAB_SW_GB_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_GB_MODBIT_SHIFT)

#define VDAC_UAB_SW_VB_MODBIT_SHIFT           CyUAB_SW_VB_MODBIT_SHIFT
#define VDAC_UAB_SW_VB_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_VB_MODBIT_SHIFT)

#define VDAC_UAB_SW_TB_SHIFT                  CyUAB_SW_TB_SHIFT
#define VDAC_UAB_SW_TB_MASK                   (0xfUL<<VDAC_UAB_SW_TB_SHIFT)

#define VDAC_UAB_SW_SB_SHIFT                  CyUAB_SW_SB_SHIFT
#define VDAC_UAB_SW_SB_MASK                   (0xfUL<<VDAC_UAB_SW_SB_SHIFT)


/*SW_CC_IN0*/
#define VDAC_UAB_SW_C0_MODBIT_SHIFT           CyUAB_SW_C0_MODBIT_SHIFT
#define VDAC_UAB_SW_C0_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_C0_MODBIT_SHIFT)

#define VDAC_UAB_SW_C1_MODBIT_SHIFT           CyUAB_SW_C1_MODBIT_SHIFT
#define VDAC_UAB_SW_C1_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_C1_MODBIT_SHIFT)

#define VDAC_UAB_SW_C2_MODBIT_SHIFT           CyUAB_SW_C2_MODBIT_SHIFT
#define VDAC_UAB_SW_C2_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_C2_MODBIT_SHIFT)

#define VDAC_UAB_SW_C3_MODBIT_SHIFT           CyUAB_SW_C3_MODBIT_SHIFT
#define VDAC_UAB_SW_C3_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_C3_MODBIT_SHIFT)

#define VDAC_UAB_SW_CP_SHIFT                  CyUAB_SW_CP_SHIFT
#define VDAC_UAB_SW_CP_MASK                   (0xfUL<<VDAC_UAB_SW_CP_SHIFT)

#define VDAC_UAB_SW_CQ_SHIFT                  CyUAB_SW_CQ_SHIFT
#define VDAC_UAB_SW_CQ_MASK                   (0xfUL<<VDAC_UAB_SW_CQ_SHIFT)


/*SW_CC_IN1*/
#define VDAC_UAB_SW_CC_SHIFT                  CyUAB_SW_CC_SHIFT
#define VDAC_UAB_SW_CC_MASK                   (0xfUL<<VDAC_UAB_SW_CC_SHIFT)

#define VDAC_UAB_SW_CR_MODBIT_SHIFT           CyUAB_SW_CR_MODBIT_SHIFT
#define VDAC_UAB_SW_CR_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_CR_MODBIT_SHIFT)

#define VDAC_UAB_SW_CG_MODBIT_SHIFT           CyUAB_SW_CG_MODBIT_SHIFT
#define VDAC_UAB_SW_CG_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_CG_MODBIT_SHIFT)

#define VDAC_UAB_SW_CV_MODBIT_SHIFT           CyUAB_SW_CV_MODBIT_SHIFT
#define VDAC_UAB_SW_CV_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_CV_MODBIT_SHIFT)


/*SW_CC_TOP*/
#define VDAC_UAB_SW_RC_MODBIT_SHIFT           CyUAB_SW_RC_MODBIT_SHIFT
#define VDAC_UAB_SW_RC_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_RC_MODBIT_SHIFT)

#define VDAC_UAB_SW_GC_MODBIT_SHIFT           CyUAB_SW_GC_MODBIT_SHIFT
#define VDAC_UAB_SW_GC_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_GC_MODBIT_SHIFT)

#define VDAC_UAB_SW_VC_MODBIT_SHIFT           CyUAB_SW_VC_MODBIT_SHIFT
#define VDAC_UAB_SW_VC_MODBIT_MASK            (0xfUL<<VDAC_UAB_SW_VC_MODBIT_SHIFT)

#define VDAC_UAB_SW_TC_SHIFT                  CyUAB_SW_TC_SHIFT
#define VDAC_UAB_SW_TC_MASK                   (0xfUL<<VDAC_UAB_SW_TC_SHIFT)

#define VDAC_UAB_SW_SC_SHIFT                  CyUAB_SW_SC_SHIFT
#define VDAC_UAB_SW_SC_MASK                   (0xfUL<<VDAC_UAB_SW_SC_SHIFT)

#define VDAC_UAB_SW_ZC_SHIFT                  CyUAB_SW_ZC_SHIFT
#define VDAC_UAB_SW_ZC_MASK                   (0xfUL<<VDAC_UAB_SW_ZC_SHIFT)


/*SW_CF_BOT*/
#define VDAC_UAB_SW_GF_SHIFT                  CyUAB_SW_GF_SHIFT
#define VDAC_UAB_SW_GF_MASK                   (0xfUL<<VDAC_UAB_SW_GF_SHIFT)

#define VDAC_UAB_SW_PF_SHIFT                  CyUAB_SW_PF_SHIFT
#define VDAC_UAB_SW_PF_MASK                   (0xfUL<<VDAC_UAB_SW_PF_SHIFT)

#define VDAC_UAB_SW_PS_SHIFT                  CyUAB_SW_PS_SHIFT
#define VDAC_UAB_SW_PS_MASK                   (0xfUL<<VDAC_UAB_SW_PS_SHIFT)

#define VDAC_UAB_SW_PO_SHIFT                  CyUAB_SW_PO_SHIFT
#define VDAC_UAB_SW_PO_MASK                   (0xfUL<<VDAC_UAB_SW_PO_SHIFT)


/*SW_OTHER*/
#define VDAC_UAB_CMP_FF_SHIFT                 CyUAB_CMP_FF_SHIFT
#define VDAC_UAB_CMP_FF_MASK                  (0xfUL<<VDAC_UAB_CMP_FF_SHIFT)

#define VDAC_UAB_VALID_SHIFT                  CyUAB_VALID_SHIFT
#define VDAC_UAB_VALID_MASK                   (0xfUL<<VDAC_UAB_VALID_SHIFT)

#define VDAC_UAB_TRIG_OUT_SHIFT               CyUAB_TRIG_OUT_SHIFT
#define VDAC_UAB_TRIG_OUT_MASK                (0xfUL<<VDAC_UAB_TRIG_OUT_SHIFT)

#define VDAC_UAB_STROBE_SW_SHIFT              CyUAB_STROBE_SW_SHIFT
#define VDAC_UAB_STROBE_SW_MASK               (0xfUL<<VDAC_UAB_STROBE_SW_SHIFT)

#define VDAC_UAB_STROBE_RST_SHIFT             CyUAB_STROBE_RST_SHIFT
#define VDAC_UAB_STROBE_RST_MASK              (0xfUL<<VDAC_UAB_STROBE_RST_SHIFT)


/*SW_BOOST_CTRL*/
#define VDAC_UAB_CA_BOOST_SHIFT               CyUAB_CA_BOOST_SHIFT
#define VDAC_UAB_CA_BOOST_MASK                (0xfUL<<VDAC_UAB_CA_BOOST_SHIFT)

#define VDAC_UAB_CB_BOOST_SHIFT               CyUAB_CB_BOOST_SHIFT
#define VDAC_UAB_CB_BOOST_MASK                (0xfUL<<VDAC_UAB_CB_BOOST_SHIFT)

#define VDAC_UAB_CC_BOOST_SHIFT               CyUAB_CC_BOOST_SHIFT
#define VDAC_UAB_CC_BOOST_MASK                (0xfUL<<VDAC_UAB_CC_BOOST_SHIFT)

#define VDAC_UAB_CF_BOOST_SHIFT               CyUAB_CF_BOOST_SHIFT
#define VDAC_UAB_CF_BOOST_MASK                (0xfUL<<VDAC_UAB_CF_BOOST_SHIFT)

#define VDAC_UAB_SUM_BOOST_SHIFT              CyUAB_SUM_BOOST_SHIFT
#define VDAC_UAB_SUM_BOOST_MASK               (0xfUL<<VDAC_UAB_SUM_BOOST_SHIFT)

#define VDAC_UAB_PUMP_WAVE_SHIFT              CyUAB_PUMP_WAVE_SHIFT
#define VDAC_UAB_PUMP_WAVE_MASK               (0xfUL<<VDAC_UAB_PUMP_WAVE_SHIFT)


/*SRAM_CTRL*/
#define VDAC_UAB_LAST_STEP_SHIFT              CyUAB_LAST_STEP_SHIFT
#define VDAC_UAB_LAST_STEP_MASK               (0xfUL<<VDAC_UAB_LAST_STEP_SHIFT)

#define VDAC_UAB_TRIG_SEL_SHIFT               CyUAB_TRIG_SEL_SHIFT
#define VDAC_UAB_TRIG_SEL_MASK                (0x1fUL<<VDAC_UAB_TRIG_SEL_SHIFT)

#define VDAC_UAB_TRIGGER_EN_SHIFT             CyUAB_TRIGGER_EN_SHIFT
#define VDAC_UAB_TRIGGER_EN_MASK              (1UL<<VDAC_UAB_TRIGGER_EN_SHIFT)

#define VDAC_UAB_RUN_SHIFT                    CyUAB_RUN_SHIFT
#define VDAC_UAB_RUN_MASK                     (1UL<<VDAC_UAB_RUN_SHIFT)


/*STAT*/
#define VDAC_UAB_CURR_STEP_SHIFT              CyUAB_CURR_STEP_SHIFT
#define VDAC_UAB_CURR_STEP_MASK               (0xfUL<<VDAC_UAB_CURR_STEP_SHIFT)

#define VDAC_UAB_COMP_SHIFT                   CyUAB_COMP_SHIFT
#define VDAC_UAB_COMP_MASK                    (1UL<<VDAC_UAB_COMP_SHIFT)

#define VDAC_UAB_CURR_SUBSAMPLE_SHIFT         CyUAB_CURR_SUBSAMPLE_SHIFT
#define VDAC_UAB_CURR_SUBSAMPLE_MASK          (0xffUL<<VDAC_UAB_CURR_SUBSAMPLE_SHIFT)


/*SRAM*/
#define VDAC_UAB_WAVE_STEP_SHIFT              CyUAB_WAVE_STEP_SHIFT
#define VDAC_UAB_WAVE_STEP_MASK               (0x0000ffffUL)


/*CAP_TRIM*/
#define VDAC_UAB_CBTC_VAL_SHIFT               CyUAB_CBTC_VAL_SHIFT
#define VDAC_UAB_CBTC_VAL_MASK                (0x7UL<<VDAC_UAB_CBTC_VAL_SHIFT)

#define VDAC_UAB_CCTC_VAL_SHIFT               CyUAB_CCTC_VAL_SHIFT
#define VDAC_UAB_CCTC_VAL_MASK                (0x7UL<<VDAC_UAB_CCTC_VAL_SHIFT)


/*OA_TRIM*/
#define VDAC_UAB_OA_OFFSET_SHIFT              CyUAB_OA_OFFSET_SHIFT
#define VDAC_UAB_OA_OFFSET_MASK               (0xfUL<<VDAC_UAB_OA_OFFSET_SHIFT)

#define VDAC_UAB_REF_OFFSET_SHIFT             CyUAB_REF_OFFSET_SHIFT
#define VDAC_UAB_REF_OFFSET_MASK              (0x1fUL<<VDAC_UAB_REF_OFFSET_SHIFT)

#define VDAC_UAB_AGND_OFFSET_SHIFT            CyUAB_AGND_OFFSET_SHIFT
#define VDAC_UAB_AGND_OFFSET_MASK             (0x1fUL<<VDAC_UAB_AGND_OFFSET_SHIFT)



#define VDAC_UAB_DAC_NEXT_MASK (CyUAB_DAC_NEXT_MASK)


#endif
