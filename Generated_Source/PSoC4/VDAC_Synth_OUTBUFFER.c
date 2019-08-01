/*******************************************************************************
* File Name: VDAC_Synth_OUTBUFFER.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the Opamp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "VDAC_Synth_OUTBUFFER.h"

uint8 VDAC_Synth_OUTBUFFER_initVar = 0u; /* Defines if component was initialized */
static uint32 VDAC_Synth_OUTBUFFER_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: VDAC_Synth_OUTBUFFER_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void VDAC_Synth_OUTBUFFER_Init(void)
{
    VDAC_Synth_OUTBUFFER_internalPower = VDAC_Synth_OUTBUFFER_POWER;
    VDAC_Synth_OUTBUFFER_CTB_CTRL_REG = VDAC_Synth_OUTBUFFER_DEFAULT_CTB_CTRL;
    VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG = VDAC_Synth_OUTBUFFER_DEFAULT_OA_RES_CTRL;
    VDAC_Synth_OUTBUFFER_OA_COMP_TRIM_REG = VDAC_Synth_OUTBUFFER_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: VDAC_Synth_OUTBUFFER_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void VDAC_Synth_OUTBUFFER_Enable(void)
{
    VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG |= VDAC_Synth_OUTBUFFER_internalPower | \
                                        VDAC_Synth_OUTBUFFER_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: VDAC_Synth_OUTBUFFER_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables power 
*  to the block. The first time the routine is executed, the Power level, Mode, 
*  and Output mode are set. When called to restart the Opamp following a Stop() call, 
*  the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  VDAC_Synth_OUTBUFFER_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void VDAC_Synth_OUTBUFFER_Start(void)
{
    if( 0u == VDAC_Synth_OUTBUFFER_initVar)
    {
        VDAC_Synth_OUTBUFFER_Init();
        VDAC_Synth_OUTBUFFER_initVar = 1u;
    }
    VDAC_Synth_OUTBUFFER_Enable();
}


/*******************************************************************************
* Function Name: VDAC_Synth_OUTBUFFER_Stop
********************************************************************************
*
* Summary:
*  Turn off the Opamp block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void VDAC_Synth_OUTBUFFER_Stop(void)
{
    VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG &= ((uint32)~(VDAC_Synth_OUTBUFFER_OA_PWR_MODE_MASK | \
                                                   VDAC_Synth_OUTBUFFER_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: VDAC_Synth_OUTBUFFER_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   VDAC_Synth_OUTBUFFER_LOW_POWER - Lowest active power
*   VDAC_Synth_OUTBUFFER_MED_POWER - Medium power
*   VDAC_Synth_OUTBUFFER_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void VDAC_Synth_OUTBUFFER_SetPower(uint32 power)
{
    uint32 tmp;
    
    VDAC_Synth_OUTBUFFER_internalPower = VDAC_Synth_OUTBUFFER_GET_OA_PWR_MODE(power);
    tmp = VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG & \
           (uint32)~VDAC_Synth_OUTBUFFER_OA_PWR_MODE_MASK;
    VDAC_Synth_OUTBUFFER_OA_RES_CTRL_REG = tmp | VDAC_Synth_OUTBUFFER_internalPower;
}


/*******************************************************************************
* Function Name: VDAC_Synth_OUTBUFFER_PumpControl
********************************************************************************
*
* Summary:
*  Allows the user to turn the Opamp's boost pump on or off. By Default the Start() 
*  function turns on the pump. Use this API to turn it off. The boost must be 
*  turned on when the supply is less than 2.7 volts and off if the supply is more 
*  than 4 volts.
*
* Parameters:
*  onOff: Control the pump.
*   VDAC_Synth_OUTBUFFER_PUMP_OFF - Turn off the pump
*   VDAC_Synth_OUTBUFFER_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void VDAC_Synth_OUTBUFFER_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        VDAC_Synth_OUTBUFFER_OA_RES_CTRL |= VDAC_Synth_OUTBUFFER_OA_PUMP_EN;    
    }
    else
    {
        VDAC_Synth_OUTBUFFER_OA_RES_CTRL &= (uint32)~VDAC_Synth_OUTBUFFER_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
