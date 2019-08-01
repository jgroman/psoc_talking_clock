/***************************************************************************//**
* @file    main.c
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

#include "custom_assert.h"
#include "iprintf.h"
#include "lpc_synth.h"
#include "custom_synth.h"
#include "temperature.h"
#include "main.h"

/// @brief Single character received from UART.
static uint8_t g_rx_char;

/// @brief Output current RTC time to UART.
/// @return void
static void uart_output_time(RTC_DATE_TIME dateTime);

/// @brief Output current temperature to UART.
/// @return void
static void uart_output_temperature(int16_t temperature);

/// @brief Interactive RTC time editor using UART.
/// @return void
static void uart_edit_time(RTC_DATE_TIME dateTime);

/*******************************************************************************
* Function Name: main
****************************************************************************//**
* @brief Application entry point.
*
* @par Summary
*    This is the main entry point for this application. 
*
* @return
*    None
*
*******************************************************************************/
int 
main(void)
{
    // CapSense variables
    uint8_t b_is_touch_ignored = 0;
    uint8_t b_is_short_touch_done = 0;
    uint32_t touch_active_counter = 0;

    // Thermometer variables
    int16_t temperature;
    
    // RTC variables
    RTC_DATE_TIME dateTime;

    // UART variables
    uint8_t b_is_prompt_skipped = 1;
    
    CyIntEnable(CYDMA_INTR_NUMBER);
    CyGlobalIntEnable;

    // Start UART as soon as possible for assert messages
    UART_Start();

    // Display app banner
    UART_UartPutString(STRING_CRLF APP_BANNER STRING_CRLF);
    
    // Initialize speech synthesizer hardware
    synth_hw_init();
        
    // Initialize temperature hardware
    temperature_hw_init();
    
    // Initialize CapSense and run initial scan
    CapSense_Start();
    CapSense_ScanAllWidgets();

    // Initialize RTC
    RTC_Start();
    
    // Send READY message to UART
    UART_UartPutString(STRING_CRLF STRING_READY STRING_CRLF);

    for(;;)
    {
        // *** CapSense Block ***

        // If CapSense scan finished, process results
        if (CapSense_NOT_BUSY == CapSense_IsBusy())
        {
            CapSense_ProcessAllWidgets();

            // The only possibly active widget is proximity sensor
            if (CapSense_IsAnyWidgetActive())
            {
                if (!b_is_touch_ignored)
                {
                    touch_active_counter++;

                    if (TOUCH_THRSHLD_LONG < touch_active_counter)
                    {
                        // Long touch action
                        //UART_UartPutString("Touch temp\r\n");
                        temperature = get_temperature();
                        say_temperature(temperature);
                        
                        // Ongoing touch is not processed anymore
                        b_is_touch_ignored = 1;
                    }
                    else if ((TOUCH_THRSHLD_SHORT < touch_active_counter) && 
                                (!b_is_short_touch_done))
                    {
                        // Short touch action
                        //UART_UartPutString("Touch time\r\n");
                        RTC_GetDateAndTime(&dateTime);
                        say_time(dateTime);
                        
                        // Do not activate more short touch events
                        b_is_short_touch_done = 1;
                    }
                }
            }
            else
            {
                if (0 != touch_active_counter)
                {
                    // Touch event just ended
                    // Enable touch processing and short event action
                    b_is_touch_ignored = 0;
                    b_is_short_touch_done = 0;
                    touch_active_counter = 0;
                }
            }

            // Start next scan
            CapSense_ScanAllWidgets();
        }

        // *** User Interaction Block ***

        // Nonblocking read from UART
        g_rx_char = UART_UartGetChar();

        switch (g_rx_char) 
        {
            // No key pressed
            case 0:
            break;

            // Enter: echo ready message
            case UART_KEYCODE_ENTER:
                b_is_prompt_skipped = 0;
            break;

            // H: Help
            case 'h':
            case 'H':
                UART_UartPutString(STRING_HELP STRING_CRLF);
                b_is_prompt_skipped = 0;
            break;

            // D: Display data
            case 'd':
            case 'D':
                // Display time
                RTC_GetDateAndTime(&dateTime);
                uart_output_time(dateTime);

                // Display temperature
                temperature = get_temperature();
                uart_output_temperature(temperature);

                b_is_prompt_skipped = 0;
            break;

            // T: Say time
            case 't':
            case 'T':
                RTC_GetDateAndTime(&dateTime);
                uart_output_time(dateTime);
                say_time(dateTime);
                b_is_prompt_skipped = 0;
            break;

            // E: Edit RTC time
            case 'e':
            case 'E':
                RTC_GetDateAndTime(&dateTime);
                uart_edit_time(dateTime);
                b_is_prompt_skipped = 0;
            break;

            // M: Say temperature
            case 'm':
            case 'M':
                temperature = get_temperature();
                uart_output_temperature(temperature);
                say_temperature(temperature);
                b_is_prompt_skipped = 0;
            break;

            // Unhandled keys
            default:
            break;
        }
        
        if (!b_is_prompt_skipped)
        {
            // Output help hint and READY message
            UART_UartPutString(STRING_CRLF STRING_HELP_PROMPT STRING_CRLF);
            UART_UartPutString(STRING_READY STRING_CRLF STRING_CRLF);
            b_is_prompt_skipped = 1;
        }
    }
}

/*******************************************************************************
* Function Name: uart_output_time
****************************************************************************//**
* @par Summary
*    Outputs current RTC time to UART.
*******************************************************************************/
static void
uart_output_time(RTC_DATE_TIME dateTime)
{
    uint32 time_format = RTC_GetTimeFormat(dateTime.time);
    uint32 hours = RTC_GetHours(dateTime.time);
    uint32 minutes = RTC_GetMinutes(dateTime.time);
    uint32 ampm = RTC_GetAmPm(dateTime.time);
    uint32 seconds = RTC_GetSecond(dateTime.time);

    iprintf(STRING_CURR_TIME"%d:", hours);

    if (10 > minutes) {
        UART_UartPutChar('0');
    }
    iprintf("%d:", minutes);

    if (10 > seconds) {
        UART_UartPutChar('0');
    }
    iprintf("%d", seconds);
    
    if (RTC_12_HOURS_FORMAT == time_format)
    {
        if (RTC_AM == ampm)
        {
            UART_UartPutString(" "STRING_AM);
        }
        else if (RTC_PM == ampm)
        {
            UART_UartPutString(" "STRING_PM);
        }
    }
    
    UART_UartPutString(STRING_CRLF);
}

/*******************************************************************************
* Function Name: uart_output_temperature
****************************************************************************//**
* @par Summary
*    Outputs current temperature to UART.
*******************************************************************************/
static void
uart_output_temperature(int16_t temperature)
{
    int16_t temperature100 = temperature / 100;
    iprintf(STRING_CURR_TEMP"%d.%d "STRING_DEG_CELSIUS STRING_CRLF, 
                temperature100, 
                temperature - (temperature100 * 100));
}

/*******************************************************************************
* Function Name: uart_edit_time
****************************************************************************//**
* @par Summary
*    Interactive editor for configuring current RTC time setting via UART.
*******************************************************************************/
static void
uart_edit_time(RTC_DATE_TIME dateTime)
{
    uint32 time_format = RTC_GetTimeFormat(dateTime.time);
    uint32 hours = RTC_GetHours(dateTime.time);
    uint32 minutes = RTC_GetMinutes(dateTime.time);
    uint32 ampm = RTC_GetAmPm(dateTime.time);
    
    uint8_t input_char_count = 0u;
    uint8_t input_seq[3] = "\0\0";

    uint8_t hours_new = 0;
    uint8_t minutes_new = 0;
    uint8_t ampm_char;
    
    uint8_t max_hours = 12u;
    
    if (RTC_24_HOURS_FORMAT == time_format)
    {
        max_hours = 23u;
    }

    if (RTC_AM == ampm)
    {
        ampm_char = 'A';
    }
    else if (RTC_PM == ampm)
    {
        ampm_char = 'P';
    }
    else
    {
        ampm_char = ' ';
    }
    
    // Edit hours value
    iprintf(STRING_HOURS" [%d]:", hours);

    uint8_t b_exit_editing = 0;
    while (!b_exit_editing) 
    {
        // Read next char from input
        g_rx_char = UART_UartGetChar();        

        // Enter keypress handling
        if (UART_KEYCODE_ENTER == g_rx_char)
        {
            UART_UartPutString(STRING_CRLF);

            // Validate entered hours value
            if (0 < input_char_count)
            {
                // Calculate hours value
                if (1 == input_char_count)
                {
                    // Converting ASCII '0' - '9' to decimal value
                    hours_new = input_seq[0] - '0';
                }
                else
                {
                    hours_new = 10 * (input_seq[0] - '0') + input_seq[1] - '0';
                }

                // Validate hours value
                if ((0 <= hours_new) && (max_hours >= hours_new))
                {
                    hours = hours_new;
                    b_exit_editing = 1;
                }
                else
                {
                    UART_UartPutString(STRING_INVALID_VALUE STRING_CRLF);
                    iprintf(STRING_HOURS" [%d]:%s", hours, input_seq);
                }
            }
            else
            // No numbers entered
            {
                b_exit_editing = 1;
            }
        }

        // Backspace keypress handling
        else if ((UART_KEYCODE_BKSPC == g_rx_char) && (0 < input_char_count))
        {
            // In result string replace deleted character with space, output
            // result string over previous string using CR without LF. Then trim
            // trailing space and output string again to position cursor
            // correctly
            input_seq[--input_char_count] = ' ';
            iprintf("\r"STRING_HOURS" [%d]:%s", hours, input_seq);
            input_seq[input_char_count] = '\0';
            iprintf("\r"STRING_HOURS" [%d]:%s", hours, input_seq);
        }

        // Numeric keys handling
        else if (('0' <= g_rx_char) && 
                 ('9' >= g_rx_char) && 
                 (2 > input_char_count))
        {
            input_seq[input_char_count++] = g_rx_char;
            iprintf("\r"STRING_HOURS" [%d]:%s", hours, input_seq);
        }
    }

    // Reset input character buffer
    input_char_count = 0u;
    input_seq[0] = '\0';
    input_seq[1] = '\0';
    
    // Edit minutes value
    iprintf(STRING_MINUTES" [%d]:", minutes);

    b_exit_editing = 0;
    while (!b_exit_editing) 
    {
        // Read next char from input
        g_rx_char = UART_UartGetChar();

        // Enter keypress handling
        if (UART_KEYCODE_ENTER == g_rx_char)
        {
            UART_UartPutString(STRING_CRLF);

            // Validate entered minutes value
            if (0 < input_char_count)
            {
                // Calculate minutes value
                if (1 == input_char_count)
                {
                    // Converting ASCII '0' - '9' to decimal value
                    minutes_new = input_seq[0] - '0';
                }
                else
                {
                    // Converting double digits
                    minutes_new = 10 * (input_seq[0] - '0') + 
                                        input_seq[1] - '0';
                }

                // Validate minutes value
                if ((0 <= minutes_new) && (59 >= minutes_new))
                {
                    minutes = minutes_new;
                    b_exit_editing = 1;
                }
                else
                {
                    UART_UartPutString(STRING_INVALID_VALUE STRING_CRLF);
                    iprintf(STRING_MINUTES" [%d]:%s", minutes, input_seq);
                }
            }
            else
            // No numbers entered
            {
                b_exit_editing = 1;
            }
        }

        // Backspace keypress handling
        else if ((UART_KEYCODE_BKSPC == g_rx_char) && (0 < input_char_count))
        {
            // In result string replace deleted character with space, output
            // result string over previous string using CR without LF. Then trim
            // trailing space and output string again to position cursor
            // correctly
            input_seq[--input_char_count] = ' ';
            iprintf("\r"STRING_MINUTES" [%d]:%s", minutes, input_seq);
            input_seq[input_char_count] = '\0';
            iprintf("\r"STRING_MINUTES" [%d]:%s", minutes, input_seq);
        }

        // Numeric keys handling
        else if (('0' <= g_rx_char) && 
                 ('9' >= g_rx_char) && 
                 (2 > input_char_count))
        {
            input_seq[input_char_count++] = g_rx_char;
            iprintf("\r"STRING_MINUTES" [%d]:%s", minutes, input_seq);
        }
    }

    if (RTC_12_HOURS_FORMAT == time_format)
    {
        // Reset input character buffer
        input_char_count = 0u;
        input_seq[0] = '\0';
        input_seq[1] = '\0';

        // Edit AM/PM
        iprintf(STRING_AM"/"STRING_PM" [%c]:", ampm_char);
        
        b_exit_editing = 0;
        while (!b_exit_editing) 
        {
            // Read next char from input
            g_rx_char = UART_UartGetChar();

            // Enter keypress handling
            if (UART_KEYCODE_ENTER == g_rx_char)
            {
                UART_UartPutString(STRING_CRLF);

                // Calculate ampm value
                if (0 < input_char_count)
                {
                    if (('a' == input_seq[0]) ||
                        ('A' == input_seq[0]))
                    {
                        ampm = RTC_AM;
                    }
                    else if (('p' == input_seq[0]) ||
                            ('P' == input_seq[0]))
                    {
                        ampm = RTC_PM;
                    }
                }
                // Leave editing loop
                b_exit_editing = 1;
            }

            // Backspace keypress handling
            else if ((UART_KEYCODE_BKSPC == g_rx_char) && 
                     (0 < input_char_count))
            {
                // In result string replace deleted character with space, output
                // result string over previous string using CR without LF. Then 
                // trim trailing space and output string again to position 
                // cursor correctly
                input_seq[--input_char_count] = ' ';
                iprintf("\r"STRING_AM"/"STRING_PM" [%c]:%s", ampm_char, 
                            input_seq);
                input_seq[input_char_count] = '\0';
                iprintf("\r"STRING_AM"/"STRING_PM" [%c]:%s", ampm_char, 
                            input_seq);
            }

            // A and P keys handling
            else if ((('a' == g_rx_char) ||
                     ('A' == g_rx_char) || 
                     ('p' == g_rx_char) || 
                     ('P' == g_rx_char)) &&
                     (1 > input_char_count))
            {
                input_seq[input_char_count++] = g_rx_char;
                iprintf("\r"STRING_AM"/"STRING_PM" [%c]:%s", ampm_char, 
                        input_seq);
            }
        }
        
    }
    else
    {
        // We are using 24 hour time format, just calculate ampm value
        // for RTC_ConstructTime
        if (12 < hours)
        {
            ampm = RTC_PM;
        }
        else
        {
            ampm = RTC_AM;
        }
    }
    
    RTC_SetDateAndTime(RTC_ConstructTime(time_format, ampm, hours, minutes, 0),
                        dateTime.date);
}

/* [] END OF FILE */
