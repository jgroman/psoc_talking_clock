/*******************************************************************************
* File Name: Timer_Sampling_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

#include "Timer_Sampling.h"

static Timer_Sampling_BACKUP_STRUCT Timer_Sampling_backup;


/*******************************************************************************
* Function Name: Timer_Sampling_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer_Sampling_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Timer_Sampling_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer_Sampling_Sleep(void)
{
    if(0u != (Timer_Sampling_BLOCK_CONTROL_REG & Timer_Sampling_MASK))
    {
        Timer_Sampling_backup.enableState = 1u;
    }
    else
    {
        Timer_Sampling_backup.enableState = 0u;
    }

    Timer_Sampling_Stop();
    Timer_Sampling_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Sampling_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer_Sampling_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Timer_Sampling_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timer_Sampling_Wakeup(void)
{
    Timer_Sampling_RestoreConfig();

    if(0u != Timer_Sampling_backup.enableState)
    {
        Timer_Sampling_Enable();
    }
}


/* [] END OF FILE */
