/***************************************************************************//**
* \file     VDAC_Synth.c
* \version  1.10
*
* \brief
* Provides the source code to the API for the VDAC_Synth Component.
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
#include "VDAC_Synth.h"
#include "VDAC_Synth_UAB.h"
#include "VDAC_Synth_OUTBUFFER.h"

uint8 VDAC_Synth_initVar = 0u; /**< 0 if component is uninitialized. 1 otherwise. */
/*******************************************************************************
* Function Name: VDAC_Synth_Start
****************************************************************************//**
*
* \brief Starts the component.  Must be called before using the UAB_VDAC.
*
*  Invokes VDAC_Synth_Init() (the first time it is called only) and
* VDAC_Synth_Enable().  After this function call the component is enabled
* and ready for operation.  This is the preferred method to begin component
* operation.
*
* \globalvars
*  \ref VDAC_Synth_initVar (RW)
*
* \sideeffect
*  None.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_Start
*
*******************************************************************************/
void VDAC_Synth_Start(void)
{
    if (1u != VDAC_Synth_initVar)
    {
        VDAC_Synth_Init();
        VDAC_Synth_initVar = 1u;
    }
    VDAC_Synth_Enable();
    
    return;
}

/*******************************************************************************
* Function Name: VDAC_Synth_Stop
****************************************************************************//**
*
* \brief Stops the component.
*
* Disables the component.  Output becomes high-Z, and UAB and CTB are disabled.
* The UAB and CTB are only half of their blocks, and disabling them is not the same
* as stopping the blocks.  This function does not stop the block power.
*
* \sideeffect
*  UAB and CTB are not fully powered-down.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_Stop
*
*******************************************************************************/
void VDAC_Synth_Stop(void)
{
    
    /* Stopping the CTB first prevents output glitches. */
    VDAC_Synth_OUTBUFFER_Stop();
    
    /* Stop the UAB */
    VDAC_Synth_UAB_Stop();
    
    VDAC_Synth_initVar = 0u;
    return;
}

/*******************************************************************************
* Function Name: VDAC_Synth_SetValue
****************************************************************************//**
*
* \brief This sets the next value for the DAC to output.
*
* The value is assumed to be correctly formatted according to the DAC mode 
* (ie 13bit 2's complement, 13bit sign magnitude, or 12bit unsigned).
* 
*
* \param value
*  The value with which to update the DAC. Saturates if out of range.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_SetValue
*
*******************************************************************************/
void VDAC_Synth_SetValue(int32 value)
{
    VDAC_Synth_UAB_SetDacNext((int16)value);
    return;
}

/*******************************************************************************
* Function Name: VDAC_Synth_SaturateTwosComp
****************************************************************************//**
*
* \brief Saturates input to the 13-bit 2's complement range.
*
* The maximum value that the DAC supports is 4095.  The minimum is -4096.
*
* \param value
*  The value to saturate.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_SaturateTwosComp
*
*******************************************************************************/
int32 VDAC_Synth_SaturateTwosComp(int32 value)
{
    /* If larger than max, or smaller than min, saturate. Otherwise, do nothing. */
    value = (value > VDAC_Synth_MAX_13b2SCOMP) ? VDAC_Synth_MAX_13b2SCOMP :
            ((value < VDAC_Synth_MIN_13b2SCOMP) ? VDAC_Synth_MIN_13b2SCOMP : value);
    return value;
}

/*******************************************************************************
* Function Name: VDAC_Synth_SaturateSignMagnitude
****************************************************************************//**
*
* \brief Saturates input to the 13-bit sign magnitude range.
*
* The maximum value that the DAC supports is 4095.  The minimum is -4095.
*
* \param sign
*  The sign of the value to saturate.  See \ref sign for values.
*
* \param magnitude
*  The magnitude of the value to saturate.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_SaturateSignMagnitude
*
*******************************************************************************/
int32 VDAC_Synth_SaturateSignMagnitude(VDAC_Synth_sign_enum sign, uint32 magnitude)
{
    uint32 tmpSign = 0u;
    magnitude = (magnitude > VDAC_Synth_MAX_13bSGNMAG_12bUNSIGN) ? VDAC_Synth_MAX_13bSGNMAG_12bUNSIGN : magnitude;
    if (VDAC_Synth_SIGN_POSITIVE != sign)
    {
        tmpSign = 0x00001000UL;
    }
    magnitude = tmpSign | magnitude;
    return (int32) magnitude;
}

/*******************************************************************************
* Function Name: VDAC_Synth_ConvertUnsigned2TwosComp
****************************************************************************//**
*
* \brief Saturates input to the 13-bit unsigned, and reformats to two's-complement.
*
* The maximum value that the DAC supports is 8191.  The minimum is 0.
*
* \param value
*  The value to saturate and convert.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_ConvertUnsigned2TwosComp
*
*******************************************************************************/
int32 VDAC_Synth_ConvertUnsigned2TwosComp(uint32 value)
{
    uint32 retVal = 0U;
    /* Saturate value */
    value = ((value > VDAC_Synth_MAX_13bUNSIGNED) ? VDAC_Synth_MAX_13bUNSIGNED :value);
    /* Convert from binary offset to 2's complement */
    retVal = value ^ 0x00001000UL;
    return (int32) retVal;
}
/*******************************************************************************
* Function Name: VDAC_Synth_SetFormat
****************************************************************************//**
*
* \brief This sets the format of the DAC.
*
* The DAC can decode numbers in the formats: 13bit 2's complement, 13bit sign magnitude,
* and 12bit unsigned.
*
* \param dacFormat
*  Which format the DAC should use. See the \ref dacFormat constants for
*  the valid values.
* 
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_SetFormat
*
*******************************************************************************/
void VDAC_Synth_SetFormat(VDAC_Synth_format_enum dacFormat)
{
    switch (dacFormat) 
    {
    case VDAC_Synth_FORMAT_13SIGNMAG:
        VDAC_Synth_UAB_SetDacMode(CyUAB_DAC_MODE_UNSIGNED12); /* Hardware does no conversions. */
        break;
    case VDAC_Synth_FORMAT_13TWOSCOMP:
    default: /* Other format requires UAB to be set in DACMode 2 */
        VDAC_Synth_UAB_SetDacMode(CyUAB_DAC_MODE_SIGNED13); /* Hardware converts negative numbers to sign-mag. */
        break;
    }
    return;
}

/*******************************************************************************
* Function Name: VDAC_Synth_SetStrobeMode
****************************************************************************//**
* \brief Set whether a hardware strobe is required to update DAC value.
*
* Invalid input results in no change.
*
* \param isHWStrobed
*  Whether to continuously update or require HW strobe. 
*  See the \ref isHWStrobed constants for the valid values.
*
* \sideeffect
*  This is a side effect section.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_SetStrobeMode
*
*******************************************************************************/
void VDAC_Synth_SetStrobeMode(VDAC_Synth_strobe_mode_enum isHWStrobed)
{
    switch(isHWStrobed)
    {
    case VDAC_Synth_STROBE_CONTINUOUSLY:
        /* Strobe clock treats strobe signal as "modbit", so to not use HW strobe
           set the strobe clock to a regular clock. */
        VDAC_Synth_UAB_SetStrobeClock(CyUAB_CLK_PHI1);
        break;
    case VDAC_Synth_STROBE_FROM_TERMINAL:
        /* Strobe clock treats strobe signal as "modbit", so to use HW strobe
           set the strobe clock to a mod clock. Use PHI11, since we need a waveform
           that is PHI1 when strobe is high, and 0 when strobe is low.*/
        VDAC_Synth_UAB_SetStrobeClock(CyUAB_CLK_PHI11);
        break;
    default:
        break;
    }
    return;
}

/*******************************************************************************
* Function Name: VDAC_Synth_SetHiZ
****************************************************************************//**
*
* \brief This sets the output state of the DAC.
*
* The output state can be tristated, or restored from tristate.  Invalid input
* results in no change.
*
* \param isHiZ
*  The target setting. See the \ref isHiZ constants for the valid values.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_SetHiZ
*
*******************************************************************************/
void VDAC_Synth_SetHiZ(VDAC_Synth_output_state_enum isHiZ)
{
    switch(isHiZ)
    {
    case VDAC_Synth_OUTSTATE_HIZ:
        VDAC_Synth_OUTBUFFER_Stop();
        break;
    case VDAC_Synth_OUTSTATE_DRIVEN:
        VDAC_Synth_OUTBUFFER_Start();
        break;
    default:
        break;
    }
    
    return;
}

/*******************************************************************************
* Function Name: VDAC_Synth_SetRange
****************************************************************************//**
*
* \brief Set the range.
*
* \param gainFactor
*  The range to be applied to input codes. See the \ref rangeFactor constants for
*  the valid values.
*
* \sideeffect
*  None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_SetGain
*
*******************************************************************************/
void VDAC_Synth_SetRange(VDAC_Synth_range_enum rangeFactor)
{   
    /* DAC Range is inversely proportional to feedback capacitors, so
       set the feedback capacitors to maximum amount, divided by desired gain.
       This division is built-in to the range_enum definitions, so they may
       simply be set as the feedback capacitance. */
    VDAC_Synth_UAB_SetCapF((CyUAB_f_cap_enum)rangeFactor);
}


/*******************************************************************************
* Function Name: VDAC_Synth_Init
****************************************************************************//**
*
* \brief Configures hardware, after reset, according to parameters defined in 
* the customizer.
*
* It is not necessary to call Init() because the Start() API 
* calls this function and is the preferred method to begin the component operation.  
* Init will not necessarily restore a default state if the block is not in a reset state.
* VDAC_Synth_Init only writes registers when the resulting register will be
* nonzero, and it only writes to registers that the VDAC utilizes.
*
* \sideeffect
*  Component output will be in a high impedance state until 
*  VDAC_Synth_Enable() is called.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_Init
*
*******************************************************************************/
void VDAC_Synth_Init(void)
{
    /* Call the default UAB init*/
    VDAC_Synth_UAB_Init(&VDAC_Synth_UAB_config);
    /* Set several of the UAB switches or buffers based on what source is used as Vagnd/Vref. */
    #if VDAC_Synth_UAB_halfuab__VAGND_SRC != VDAC_Synth_UAB_halfuab__SRC_AGNDBUF
        VDAC_Synth_UAB_SetStaticSwitch(VDAC_Synth_SW_EXTAGND, CyUAB_SW_CLOSED);
    #else
        VDAC_Synth_UAB_SetAgndPower(CyUAB_PWR_HIGH);
    #endif
    
    #if VDAC_Synth_UAB_halfuab__VREF_SRC != VDAC_Synth_UAB_halfuab__SRC_REFBUF
        VDAC_Synth_UAB_SetSwitch(VDAC_Synth_SW_EXTREFA, CyUAB_CLK_PHI9);
        VDAC_Synth_UAB_SetSwitch(VDAC_Synth_SW_EXTREFB, CyUAB_CLK_PHI9);
    #else
        VDAC_Synth_UAB_SetSwitch(CyUAB_SW_AR_MODBIT, CyUAB_CLK_PHI9);
        VDAC_Synth_UAB_SetSwitch(CyUAB_SW_BR_MODBIT, CyUAB_CLK_PHI9);
        VDAC_Synth_UAB_SetRefPower(CyUAB_PWR_HIGH);
    #endif
    
    /* Highest power, Bypass, Enable OA Pump*/
    VDAC_Synth_OUTBUFFER_Init();
    return;
}

/*******************************************************************************
* Function Name: VDAC_Synth_Enable
****************************************************************************//**
*
* \brief Enables the component.
*
* It is not necessary to call Enable() because the Start() API 
* calls this function and is the preferred method to begin the component operation.
* Activates the UAB and CTB.  Requires that the blocks have been configured, such
* as by calling VDAC_Synth_Init().
*
* \sideeffect
*  Causes output state to be driven until set to analog high impedance by, for
*  example, VDAC_Synth_Stop().
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_VDAC_Synth_Enable
*
*******************************************************************************/
void VDAC_Synth_Enable(void) 
{
    /* Enable the UAB */
    VDAC_Synth_UAB_Run(1u);
    /* Enable the CTB */
    VDAC_Synth_OUTBUFFER_Enable();
    return;
}
/* [] END OF FILE */
