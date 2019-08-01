/***************************************************************************//**
* @file    iprintf.h
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
#ifndef IPRINTF_H
    #define IPRINTF_H

/*******************************************************************************
*   Included Headers
*******************************************************************************/
    #include <project.h>

/*******************************************************************************
*   Function Declarations
*******************************************************************************/

    /// @brief Low resource printf() function replacement.
    /// @param pszFmt String format.
    /// @param ... Optional variables to output
    /// @return none
    void iprintf(char8 *pszFmt,...);

#endif
/* [] END OF FILE */
