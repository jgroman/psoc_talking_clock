/***************************************************************************//**
* @file    custom_synth.h
* @version 1.0.0
*
* @brief Project dependent LPC audio constants and functions.
*
* @par Target device
*    CY8C4A45LQI-483
*
* @par Related hardware
*    CY8CKIT-048
*
* @par Code Tested With
*    - Silicon: PSoC Analog Coprocessor
*    - IDE: PSoC Creator 4.0 (4.0.0.432)
*    - Compiler: GCC 4.9.3, ARM MDK 4.54.0.0 (armcc 4.1 b894)
*
* @par Components
*    - RTC_P4       [RTC]
*
* @par Creating LPC encoded sound samples
* Download QBoxPro from http://ftp.whtech.com/pc%20utilities/qboxpro.zip
*
* This is a 16-bit Windows application, it will work ONLY in 32-bit Windows,
* tested working in 32-bit Windows XP. This software also requires a copy 
* of BWCC.DLL library.
* This program can be used to convert WAV files into LPC encoded data.
* WAV format MUST be 16bit PCM, 8 kHz sample rate, mono.
* 
* Installing QBoxPro: (if using CLI type backslash instead of forward slash)
* 1. Copy QBoxPro files into C:/QBOX directory
* 2. Move QBOXPRO.INI to C:/WINDOWS
* 3. Find BWCC.DLL (tested with 1.3.14.1) and copy to C:/QBOX
* 4. Launch QBoxPro and exit via Project.. -> Exit
* 5. Edit C:/WINDOWS/QBOXPRO.INI, find LPCNB=12, change to LPCNB=10
*
* Using QBoxPro
* 1. Create new project
* 2. Project Settings: Set Alignment: Byte, Frequency: 8kHz, Coding Table: 5220
* 3. Add Wav file: Project... -> Add Files... 
* 4. Click Process... -> Medium bitrate -> OK
* 5. Click Edit... -> Concatenations -> Insert... -> Concatenation...
* 6. Enter sample description -> OK
* 7. Click Insert... -> Phrase... -> OK
* 8. Click Format... -> LPC 10V, 4UV -> OK
* 9. Optionally save project: Click Project... -> Save
*
* Generated LPC file is in the project directory with *.bin extension
*
*******************************************************************************/
#ifndef CUSTOM_SYNTH_H
	#define CUSTOM_SYNTH_H
    
/*******************************************************************************
*   Included Headers
*******************************************************************************/
    #include <project.h>
    
/*******************************************************************************
*   Function Declarations
*******************************************************************************/
    /// @brief Vocalize given number parameter.
    /// @param number Number to vocalize.
    /// @return none
    void say_number(int16_t number);

    /// @brief Vocalize given time.
    /// @param dateTime Time to vocalize.
    /// @return none
    void say_time(RTC_DATE_TIME dateTime);

    /// @brief Vocalize given temperature.
    /// @param temp Temperature to vocalize.
    /// @return none
    void say_temperature(int16_t temp);

#endif

/* [] END OF FILE */
