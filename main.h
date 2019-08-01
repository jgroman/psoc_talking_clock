/***************************************************************************//**
* @file    main.h
* @version 1.0.0
* @authors Jaroslav Groman
*
* @par Project Name
*    Touch Activated Talking Clock with Thermometer
*
* @par Description
*    This project demonstrates usage of various capabilities of Cypress PSoC
* Analog Coprocessor, namely CapSense, real time clock, thermal measurement and
* UART interfacing. Current time and temperature are announced using
* synthesized speech which allows device usage by visually impaired people.
*
* @par Target device
*    CY8C4A45LQI-483
*
* @par Related hardware
*    CY8CKIT-048
*
* @par Code Tested With
*    1. Silicon: PSoC Analog Coprocessor
*    2. IDE: PSoC Creator 4.0 Update 1 (4.0.0.432)
*    3. Compiler: GCC 4.9.3, ARM MDK 4.54.0.0 (armcc 4.1 b894)
*
* @par Notes
*    For exact time measurement it is necessary to perform hardware modification
* of CY8CKIT-048 developer kit. This modification enables use of kit WCO. 
* Correct WCO operation is enabled by moving zero ohm resistor R149 to position
* R138 and zero ohm resistor R150 to position R30.
* For evaluation purposes it is possible to use kit as-is, using ILO as LFCLK
* source, but timekeeping function will be inaccurate.
* Please see project documentation for details.
*
*******************************************************************************/

#ifndef MAIN_H
	#define MAIN_H

/*******************************************************************************
*   Included Headers
*******************************************************************************/
    #include <project.h>

/*******************************************************************************
*   Macros and #define Constants
*******************************************************************************/
    /// @brief App banner to display on reset.
    #define APP_BANNER      "*** Talking clock V1.0 ***"
    
    /// @brief String "Hours".
    #define STRING_HOURS    "Hours"

    /// @brief String "Minutes".
    #define STRING_MINUTES  "Minutes"

    /// @brief String "AM".
    #define STRING_AM       "AM"

    /// @brief String "PM".
    #define STRING_PM       "PM"

    /// @brief String "degrees Celsius".
    #define STRING_DEG_CELSIUS      "deg C"

    /// @brief String "Invalid value".
    #define STRING_INVALID_VALUE    "Invalid value"
    
    /// @brief String "ready".
    #define STRING_READY    "READY"

    /// @brief String Help prompt.
    #define STRING_HELP_PROMPT    "(Press H for help)"

    /// @brief String for Menu options.
    #define STRING_HELP    "[D] Display data\r\n" \
                           "[T] Say time\r\n" \
                           "[E] Edit time\r\n" \
                           "[M] Say temperature"

    /// @brief String CR + LF.
    #define STRING_CRLF     "\r\n"
    
    /// @brief String "Current time is ".
    #define STRING_CURR_TIME    "Current time is "

    /// @brief String "Current temperature is ".
    #define STRING_CURR_TEMP    "Current temperature is "

    /// @brief ENTER key scancode for UART.
    #define UART_KEYCODE_ENTER       (13u)

    /// @brief BACKSPACE key scancode for UART.
    #define UART_KEYCODE_BKSPC       (127u)
    
    /// @brief Threshold for detecting short touch
    #define TOUCH_THRSHLD_SHORT      (1000u)
    
    /// @brief Threshold for detecting long touch
    #define TOUCH_THRSHLD_LONG       (2800u)

    
/*******************************************************************************
*   Global Variables and Constant Declarations with Applicable Initializations
*******************************************************************************/

/*******************************************************************************
*   Function Declarations
*******************************************************************************/

#endif

/* [] END OF FILE */
