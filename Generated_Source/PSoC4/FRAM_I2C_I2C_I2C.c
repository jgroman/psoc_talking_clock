/***************************************************************************//**
* \file FRAM_I2C_I2C_I2C.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "FRAM_I2C_I2C_PVT.h"
#include "FRAM_I2C_I2C_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 FRAM_I2C_I2C_state;  /* Current state of I2C FSM */

#if(FRAM_I2C_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const FRAM_I2C_I2C_I2C_INIT_STRUCT FRAM_I2C_I2C_configI2C =
    {
        FRAM_I2C_I2C_I2C_MODE,
        FRAM_I2C_I2C_I2C_OVS_FACTOR_LOW,
        FRAM_I2C_I2C_I2C_OVS_FACTOR_HIGH,
        FRAM_I2C_I2C_I2C_MEDIAN_FILTER_ENABLE,
        FRAM_I2C_I2C_I2C_SLAVE_ADDRESS,
        FRAM_I2C_I2C_I2C_SLAVE_ADDRESS_MASK,
        FRAM_I2C_I2C_I2C_ACCEPT_ADDRESS,
        FRAM_I2C_I2C_I2C_WAKE_ENABLE,
        FRAM_I2C_I2C_I2C_BYTE_MODE_ENABLE,
        FRAM_I2C_I2C_I2C_DATA_RATE,
        FRAM_I2C_I2C_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: FRAM_I2C_I2C_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the FRAM_I2C_I2C for I2C operation.
    *
    *  This function is intended specifically to be used when the FRAM_I2C_I2C 
    *  configuration is set to “Unconfigured FRAM_I2C_I2C” in the customizer. 
    *  After initializing the FRAM_I2C_I2C in I2C mode using this function, 
    *  the component can be enabled using the FRAM_I2C_I2C_Start() or 
    * FRAM_I2C_I2C_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void FRAM_I2C_I2C_I2CInit(const FRAM_I2C_I2C_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            FRAM_I2C_I2C_SetPins(FRAM_I2C_I2C_SCB_MODE_I2C, FRAM_I2C_I2C_DUMMY_PARAM,
                                     FRAM_I2C_I2C_DUMMY_PARAM);

            /* Store internal configuration */
            FRAM_I2C_I2C_scbMode       = (uint8) FRAM_I2C_I2C_SCB_MODE_I2C;
            FRAM_I2C_I2C_scbEnableWake = (uint8) config->enableWake;
            FRAM_I2C_I2C_scbEnableIntr = (uint8) FRAM_I2C_I2C_SCB_IRQ_INTERNAL;

            FRAM_I2C_I2C_mode          = (uint8) config->mode;
            FRAM_I2C_I2C_acceptAddr    = (uint8) config->acceptAddr;

        #if (FRAM_I2C_I2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            FRAM_I2C_I2C_SET_I2C_CFG_SDA_FILT_TRIM(FRAM_I2C_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (FRAM_I2C_I2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((FRAM_I2C_I2C_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= FRAM_I2C_I2C_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (FRAM_I2C_I2C_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                FRAM_I2C_I2C_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = FRAM_I2C_I2C_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                FRAM_I2C_I2C_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = FRAM_I2C_I2C_DIGITAL_FILTER_ENABLE;
            }

        #if (!FRAM_I2C_I2C_CY_SCBIP_V0)
            locEnableWake = (FRAM_I2C_I2C_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!FRAM_I2C_I2C_CY_SCBIP_V0) */

            /* Configure I2C interface */
            FRAM_I2C_I2C_CTRL_REG     = FRAM_I2C_I2C_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            FRAM_I2C_I2C_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            FRAM_I2C_I2C_GET_CTRL_EC_AM_MODE (locEnableWake);

            FRAM_I2C_I2C_I2C_CTRL_REG = FRAM_I2C_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    FRAM_I2C_I2C_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    FRAM_I2C_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    FRAM_I2C_I2C_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            FRAM_I2C_I2C_RX_CTRL_REG      = FRAM_I2C_I2C_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                FRAM_I2C_I2C_I2C_RX_CTRL;
            FRAM_I2C_I2C_RX_FIFO_CTRL_REG = FRAM_I2C_I2C_CLEAR_REG;

            /* Set default address and mask */
            FRAM_I2C_I2C_RX_MATCH_REG    = ((FRAM_I2C_I2C_I2C_SLAVE) ?
                                                (FRAM_I2C_I2C_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 FRAM_I2C_I2C_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (FRAM_I2C_I2C_CLEAR_REG));


            /* Configure TX direction */
            FRAM_I2C_I2C_TX_CTRL_REG      = FRAM_I2C_I2C_I2C_TX_CTRL;
            FRAM_I2C_I2C_TX_FIFO_CTRL_REG = FRAM_I2C_I2C_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (FRAM_I2C_I2C_ISR_NUMBER);
            CyIntSetPriority(FRAM_I2C_I2C_ISR_NUMBER, FRAM_I2C_I2C_ISR_PRIORITY);
            (void) CyIntSetVector(FRAM_I2C_I2C_ISR_NUMBER, &FRAM_I2C_I2C_I2C_ISR);

            /* Configure interrupt sources */
        #if(!FRAM_I2C_I2C_CY_SCBIP_V1)
            FRAM_I2C_I2C_INTR_SPI_EC_MASK_REG = FRAM_I2C_I2C_NO_INTR_SOURCES;
        #endif /* (!FRAM_I2C_I2C_CY_SCBIP_V1) */

            FRAM_I2C_I2C_INTR_I2C_EC_MASK_REG = FRAM_I2C_I2C_NO_INTR_SOURCES;
            FRAM_I2C_I2C_INTR_RX_MASK_REG     = FRAM_I2C_I2C_NO_INTR_SOURCES;
            FRAM_I2C_I2C_INTR_TX_MASK_REG     = FRAM_I2C_I2C_NO_INTR_SOURCES;

            FRAM_I2C_I2C_INTR_SLAVE_MASK_REG  = ((FRAM_I2C_I2C_I2C_SLAVE) ?
                            (FRAM_I2C_I2C_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             FRAM_I2C_I2C_I2C_INTR_SLAVE_MASK) : (FRAM_I2C_I2C_CLEAR_REG));

            FRAM_I2C_I2C_INTR_MASTER_MASK_REG = ((FRAM_I2C_I2C_I2C_MASTER) ?
                                                     (FRAM_I2C_I2C_I2C_INTR_MASTER_MASK) :
                                                     (FRAM_I2C_I2C_CLEAR_REG));

            /* Configure global variables */
            FRAM_I2C_I2C_state = FRAM_I2C_I2C_I2C_FSM_IDLE;

            /* Internal slave variables */
            FRAM_I2C_I2C_slStatus        = 0u;
            FRAM_I2C_I2C_slRdBufIndex    = 0u;
            FRAM_I2C_I2C_slWrBufIndex    = 0u;
            FRAM_I2C_I2C_slOverFlowCount = 0u;

            /* Internal master variables */
            FRAM_I2C_I2C_mstrStatus     = 0u;
            FRAM_I2C_I2C_mstrRdBufIndex = 0u;
            FRAM_I2C_I2C_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: FRAM_I2C_I2C_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void FRAM_I2C_I2C_I2CInit(void)
    {
    #if(FRAM_I2C_I2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        FRAM_I2C_I2C_SET_I2C_CFG_SDA_FILT_TRIM(FRAM_I2C_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (FRAM_I2C_I2C_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        FRAM_I2C_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        FRAM_I2C_I2C_CTRL_REG     = FRAM_I2C_I2C_I2C_DEFAULT_CTRL;
        FRAM_I2C_I2C_I2C_CTRL_REG = FRAM_I2C_I2C_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        FRAM_I2C_I2C_RX_CTRL_REG      = FRAM_I2C_I2C_I2C_DEFAULT_RX_CTRL;
        FRAM_I2C_I2C_RX_FIFO_CTRL_REG = FRAM_I2C_I2C_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        FRAM_I2C_I2C_RX_MATCH_REG     = FRAM_I2C_I2C_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        FRAM_I2C_I2C_TX_CTRL_REG      = FRAM_I2C_I2C_I2C_DEFAULT_TX_CTRL;
        FRAM_I2C_I2C_TX_FIFO_CTRL_REG = FRAM_I2C_I2C_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (FRAM_I2C_I2C_ISR_NUMBER);
        CyIntSetPriority(FRAM_I2C_I2C_ISR_NUMBER, FRAM_I2C_I2C_ISR_PRIORITY);
    #if(!FRAM_I2C_I2C_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(FRAM_I2C_I2C_ISR_NUMBER, &FRAM_I2C_I2C_I2C_ISR);
    #endif /* (FRAM_I2C_I2C_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!FRAM_I2C_I2C_CY_SCBIP_V1)
        FRAM_I2C_I2C_INTR_SPI_EC_MASK_REG = FRAM_I2C_I2C_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!FRAM_I2C_I2C_CY_SCBIP_V1) */

        FRAM_I2C_I2C_INTR_I2C_EC_MASK_REG = FRAM_I2C_I2C_I2C_DEFAULT_INTR_I2C_EC_MASK;
        FRAM_I2C_I2C_INTR_SLAVE_MASK_REG  = FRAM_I2C_I2C_I2C_DEFAULT_INTR_SLAVE_MASK;
        FRAM_I2C_I2C_INTR_MASTER_MASK_REG = FRAM_I2C_I2C_I2C_DEFAULT_INTR_MASTER_MASK;
        FRAM_I2C_I2C_INTR_RX_MASK_REG     = FRAM_I2C_I2C_I2C_DEFAULT_INTR_RX_MASK;
        FRAM_I2C_I2C_INTR_TX_MASK_REG     = FRAM_I2C_I2C_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        FRAM_I2C_I2C_state = FRAM_I2C_I2C_I2C_FSM_IDLE;

    #if(FRAM_I2C_I2C_I2C_SLAVE)
        /* Internal slave variable */
        FRAM_I2C_I2C_slStatus        = 0u;
        FRAM_I2C_I2C_slRdBufIndex    = 0u;
        FRAM_I2C_I2C_slWrBufIndex    = 0u;
        FRAM_I2C_I2C_slOverFlowCount = 0u;
    #endif /* (FRAM_I2C_I2C_I2C_SLAVE) */

    #if(FRAM_I2C_I2C_I2C_MASTER)
    /* Internal master variable */
        FRAM_I2C_I2C_mstrStatus     = 0u;
        FRAM_I2C_I2C_mstrRdBufIndex = 0u;
        FRAM_I2C_I2C_mstrWrBufIndex = 0u;
    #endif /* (FRAM_I2C_I2C_I2C_MASTER) */
    }
#endif /* (FRAM_I2C_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: FRAM_I2C_I2C_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void FRAM_I2C_I2C_I2CStop(void)
{
    FRAM_I2C_I2C_state = FRAM_I2C_I2C_I2C_FSM_IDLE;
}


#if(FRAM_I2C_I2C_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: FRAM_I2C_I2C_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables FRAM_I2C_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void FRAM_I2C_I2C_I2CSaveConfig(void)
    {
    #if (!FRAM_I2C_I2C_CY_SCBIP_V0)
        #if (FRAM_I2C_I2C_I2C_MULTI_MASTER_SLAVE_CONST && FRAM_I2C_I2C_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (FRAM_I2C_I2C_CTRL_REG & FRAM_I2C_I2C_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                FRAM_I2C_I2C_Stop();
                FRAM_I2C_I2C_CTRL_REG |= FRAM_I2C_I2C_CTRL_EC_AM_MODE;
                FRAM_I2C_I2C_Enable();
            }
        #endif /* (FRAM_I2C_I2C_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (FRAM_I2C_I2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            FRAM_I2C_I2C_SCBCLK_Stop();
        #endif /* (FRAM_I2C_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!FRAM_I2C_I2C_CY_SCBIP_V0) */

        FRAM_I2C_I2C_SetI2CExtClkInterruptMode(FRAM_I2C_I2C_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: FRAM_I2C_I2C_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables FRAM_I2C_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void FRAM_I2C_I2C_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        FRAM_I2C_I2C_SetI2CExtClkInterruptMode(FRAM_I2C_I2C_NO_INTR_SOURCES);

    #if (!FRAM_I2C_I2C_CY_SCBIP_V0)
        #if (FRAM_I2C_I2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            FRAM_I2C_I2C_SCBCLK_Start();
        #endif /* (FRAM_I2C_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!FRAM_I2C_I2C_CY_SCBIP_V0) */
    }
#endif /* (FRAM_I2C_I2C_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
