/***************************************************************************//**
* @file    custom_assert.h
* @version 1.0.0
*
* @brief Assert macro outputting to UART.
*
* @par Description
*    Custom Assert macro printing messages via UART. Uses iprintf module.
*
* @warning Set correct UART name in iprintf.c file.
*
*******************************************************************************/

#ifndef CUSTOM_ASSERT_H
	#define CUSTOM_ASSERT_H
    
/*******************************************************************************
*   Included Headers
*******************************************************************************/
    #include <project.h>
    #include "iprintf.h"
    
/*******************************************************************************
*   Macros and #define Constants
*******************************************************************************/
    /// @brief Custom assert message.
    #define ASSERT_MESSAGE "File %s - Assert failed at line %d\r\n"
    
    /// @brief Assert macro outputting to UART.
    #define ASSERT(expr) \
        if (expr) \
            {} \
        else \
            { \
                iprintf(ASSERT_MESSAGE, __FILE__, __LINE__); \
                for (;;); \
            }

#endif

/* [] END OF FILE */
