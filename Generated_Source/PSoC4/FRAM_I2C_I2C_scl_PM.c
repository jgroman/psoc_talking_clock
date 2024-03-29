/*******************************************************************************
* File Name: FRAM_I2C_I2C_scl.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "FRAM_I2C_I2C_scl.h"

static FRAM_I2C_I2C_scl_BACKUP_STRUCT  FRAM_I2C_I2C_scl_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: FRAM_I2C_I2C_scl_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet FRAM_I2C_I2C_scl_SUT.c usage_FRAM_I2C_I2C_scl_Sleep_Wakeup
*******************************************************************************/
void FRAM_I2C_I2C_scl_Sleep(void)
{
    #if defined(FRAM_I2C_I2C_scl__PC)
        FRAM_I2C_I2C_scl_backup.pcState = FRAM_I2C_I2C_scl_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            FRAM_I2C_I2C_scl_backup.usbState = FRAM_I2C_I2C_scl_CR1_REG;
            FRAM_I2C_I2C_scl_USB_POWER_REG |= FRAM_I2C_I2C_scl_USBIO_ENTER_SLEEP;
            FRAM_I2C_I2C_scl_CR1_REG &= FRAM_I2C_I2C_scl_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(FRAM_I2C_I2C_scl__SIO)
        FRAM_I2C_I2C_scl_backup.sioState = FRAM_I2C_I2C_scl_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        FRAM_I2C_I2C_scl_SIO_REG &= (uint32)(~FRAM_I2C_I2C_scl_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: FRAM_I2C_I2C_scl_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to FRAM_I2C_I2C_scl_Sleep() for an example usage.
*******************************************************************************/
void FRAM_I2C_I2C_scl_Wakeup(void)
{
    #if defined(FRAM_I2C_I2C_scl__PC)
        FRAM_I2C_I2C_scl_PC = FRAM_I2C_I2C_scl_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            FRAM_I2C_I2C_scl_USB_POWER_REG &= FRAM_I2C_I2C_scl_USBIO_EXIT_SLEEP_PH1;
            FRAM_I2C_I2C_scl_CR1_REG = FRAM_I2C_I2C_scl_backup.usbState;
            FRAM_I2C_I2C_scl_USB_POWER_REG &= FRAM_I2C_I2C_scl_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(FRAM_I2C_I2C_scl__SIO)
        FRAM_I2C_I2C_scl_SIO_REG = FRAM_I2C_I2C_scl_backup.sioState;
    #endif
}


/* [] END OF FILE */
