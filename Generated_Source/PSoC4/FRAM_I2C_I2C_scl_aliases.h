/*******************************************************************************
* File Name: FRAM_I2C_I2C_scl.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_FRAM_I2C_I2C_scl_ALIASES_H) /* Pins FRAM_I2C_I2C_scl_ALIASES_H */
#define CY_PINS_FRAM_I2C_I2C_scl_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define FRAM_I2C_I2C_scl_0			(FRAM_I2C_I2C_scl__0__PC)
#define FRAM_I2C_I2C_scl_0_PS		(FRAM_I2C_I2C_scl__0__PS)
#define FRAM_I2C_I2C_scl_0_PC		(FRAM_I2C_I2C_scl__0__PC)
#define FRAM_I2C_I2C_scl_0_DR		(FRAM_I2C_I2C_scl__0__DR)
#define FRAM_I2C_I2C_scl_0_SHIFT	(FRAM_I2C_I2C_scl__0__SHIFT)
#define FRAM_I2C_I2C_scl_0_INTR	((uint16)((uint16)0x0003u << (FRAM_I2C_I2C_scl__0__SHIFT*2u)))

#define FRAM_I2C_I2C_scl_INTR_ALL	 ((uint16)(FRAM_I2C_I2C_scl_0_INTR))


#endif /* End Pins FRAM_I2C_I2C_scl_ALIASES_H */


/* [] END OF FILE */
