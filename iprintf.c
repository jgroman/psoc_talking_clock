/***************************************************************************//**
* @file    iprintf.c
* @version 1.0.0
*
* @brief Low resource printf() replacement.
*
* @par Description
*    Simplified low resource printf() function replacement. Outputs directly
* to UART. Available format modifiers: \%s, \%d, \%c, \%x.
*
* @warning
*    - Modify function iputc() according to current UART name.
*
* @par Source
*    http://www.cypress.com/knowledge-base-article/alternate-printf-function-psoc-4-kba87093
*
* @par Components
*    - SCB_P4         [UART]
*
*******************************************************************************/
#include "iprintf.h"

/// @var static const uint8_t NUM_CHARS[]
/// @brief Character table for decimal and hexadecimal conversion
static const uint8_t NUM_CHARS[16] = "0123456789ABCDEF";

/// @brief Customized single character output function.
/// @param ch Character to output
/// @return none
static void iputc(char8 ch);

/*******************************************************************************
* Function Name: iputc
****************************************************************************//**
* @par Summary
*    Outputs single character to UART specified by UartPutChar() function
* prefix.
*******************************************************************************/
static void 
iputc(char8 ch)
{
	// !! MODIFY HERE function prefix according to current UART name
	UART_UartPutChar(ch);
}

/*******************************************************************************
* Function Name: iprintf
****************************************************************************//**
* @par Summary
*    This is a drop-in printf() function replacement which outputs straight 
* to UART. It supports only a subset of printf format specifiers. Supported
* format specifiers are \%s, \%d, \%c and \%x.
*******************************************************************************/
void 
iprintf(char8 *pszFmt, ...)
{
    uint8 *pszVal;
    uint32  index = 1;
    uint32  num_cnt;
    uint8_t buffer[12];
    uint32 *p_arg;

    p_arg = (uint32 *)&pszFmt;

    while (*pszFmt)
    {
        if('%' != *pszFmt)
        {
            iputc(*pszFmt);
            pszFmt++;
            continue;
        }

        pszFmt++;

        if ('s' == *pszFmt)
        {
            pszVal = (uint8*)p_arg[index++];
            for (; *pszVal != '\0'; pszVal++)
            {
                iputc(*pszVal);
            }
            pszFmt++;
            continue;
        }

        if ('d' == *pszFmt)
        {
            uint32_t i_val = p_arg[index++];
            num_cnt = 0;
            do
            {
                buffer[num_cnt++] = i_val % 10;
                i_val /= 10;
            }
            while (i_val);
            
            while (num_cnt > 0)
            {
                num_cnt--;
                iputc(NUM_CHARS[buffer[num_cnt]]);
            }
            pszFmt++;
            continue;
        }

        if ('c' == *pszFmt)
        {
            iputc((uint8_t)p_arg[index++]);
            pszFmt++;
            continue;
        }

        if ('x' == *pszFmt)
        {
            uint32_t x_val = p_arg[index++];
            num_cnt = 0;
            do
            {
                buffer[num_cnt++] = x_val % 16;
                x_val /= 16;
            } 
            while (x_val);

            if (0 != (num_cnt % 2))
            {
                buffer[num_cnt++] = 0;
            }

            if (2 > num_cnt)
            {
                buffer[num_cnt++] = 0;
            }

            while (0 < num_cnt)
            {
                num_cnt--;
                iputc(NUM_CHARS[buffer[num_cnt]]);
            }

            pszFmt++;
            continue;
        }
        
        if ('\0' == pszFmt)
        {
            break;
        }
    }
}

/* [] END OF FILE */
