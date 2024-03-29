/***************************************************************************//**
* @file    custom_synth.c
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
#include "lpc_synth.h"
#include "custom_synth.h"

/*******************************************************************************
*   Constant definitions
*******************************************************************************/

/// @brief LPC encoded word "zero"
static const uint8_t LPC_ZERO[] = {
    0x00, 0x04, 0x00, 0x9F, 0x02, 0xD2, 0x24, 0x4C, 0x6B, 0xE7, 
    0x18, 0x49, 0xA3, 0x63, 0x6B, 0x59, 0x15, 0x38, 0x4D, 0x09, 
    0x66, 0x94, 0x7B, 0xC9, 0x32, 0x0D, 0x20, 0xE1, 0x51, 0x95, 
    0xDB, 0x74, 0x85, 0x18, 0xAB, 0x36, 0x69, 0xD3, 0xD7, 0x62, 
    0xC4, 0xDA, 0x7A, 0x8C, 0xCF, 0xBA, 0xB1, 0x50, 0xEB, 0xD6, 
    0x4D, 0xC4, 0x6A, 0x9D, 0x0B, 0xC6, 0xD0, 0xA0, 0x68, 0x75, 
    0x8F, 0x1A, 0x7D, 0xC3, 0xE4, 0xD3, 0x55, 0x7A, 0xF4, 0x0D, 
    0x92, 0xD7, 0x54, 0xA5, 0xD5, 0x67, 0xCE, 0x96, 0xDB, 0x25,
    0x4F, 0x9F, 0x84, 0x7A, 0xAF, 0x87, 0x3A, 0x63, 0x56, 0x66,
    0x31, 0x31, 0xF1, 0x8C, 0x3E, 0x68, 0x66, 0x79, 0xE9, 0x35,
    0x85, 0x4C, 0xE3, 0xEE, 0x93, 0xC6, 0xE8, 0x2B, 0x55, 0x84,
    0xCD, 0x1A, 0xA3, 0x6B, 0x34, 0xEE, 0x31, 0x73, 0x4C, 0xA6,
    0xF2, 0xB8, 0x46, 0xAD, 0x31, 0xDA, 0x26, 0x6D, 0x11, 0x25,
    0xD7, 0xE8, 0x8B, 0x96, 0x59, 0x16, 0x5A, 0xA3, 0x2F, 0x5E,
    0xAE, 0x35, 0x78, 0x4C, 0xAA, 0xAC, 0xBB, 0xF2, 0xA8, 0x31,
    0xCB, 0x5D, 0x6A, 0xEA, 0x95, 0xDB, 0x2C, 0xAF, 0xAB, 0x66,
    0x54, 0x2C, 0xB3, 0x38, 0xE9, 0x6C, 0x36, 0x33, 0xCD, 0x6C,
    0xA7, 0xAB, 0x7B, 0xED, 0x34, 0xD1, 0x59, 0xA6, 0x6E, 0xB5,
    0xC3, 0xC4, 0x46, 0x98, 0x7A, 0xD4, 0x75, 0x15, 0x4B, 0x19,
    0xAA, 0x1E, 0x07, 0x4A, 0x50, 0x98, 0xAB, 0x9B, 0x3B, 0x7E
}; 

/// @brief LPC encoded word "one"
static const uint8_t LPC_ONE[] = {
    0x00, 0x04, 0x00, 0x9F, 0x40, 0x35, 0xF8, 0x35, 0x69, 0x86,
    0x6D, 0xD5, 0xB1, 0x6F, 0x98, 0x1D, 0xB6, 0x52, 0xAB, 0x77,
    0xAB, 0x44, 0x14, 0x6C, 0xBD, 0x9F, 0xA1, 0x9A, 0x1D, 0x78,
    0xF4, 0xA1, 0xB5, 0x48, 0x66, 0xE1, 0x33, 0xC4, 0x32, 0x21,
    0x51, 0x85, 0xCF, 0x90, 0xFC, 0xA4, 0x5A, 0x8D, 0x3E, 0x63,
    0x4C, 0x9D, 0xEA, 0x13, 0xE4, 0x8C, 0x29, 0x56, 0x6A, 0x54,
    0x90, 0x33, 0x26, 0x67, 0x45, 0x65, 0xA6, 0xC7, 0x68, 0x8D,
    0xB6, 0x85, 0x39, 0x6E, 0xA3, 0x71, 0x92, 0x36, 0x69, 0xB9,
    0x8D, 0xC6, 0xF0, 0x64, 0x86, 0xED, 0x32, 0x4A, 0x2B, 0x13,
    0x1D, 0xB6, 0xCA, 0x60, 0x0D, 0x95, 0x4F, 0xD6, 0x38, 0x63,
    0xE6, 0x12, 0x9A, 0x51, 0xB9, 0x8D, 0xC6, 0x4B, 0x64, 0xB9,
    0x95, 0x32, 0x7A, 0xAB, 0xA6, 0x99, 0x76, 0xE0, 0x01
};

/// @brief LPC encoded word "two"
static const uint8_t LPC_TWO[] = {
    0x2B, 0x1C, 0xCE, 0x83, 0xC5, 0xBA, 0xB4, 0x5C, 0xBA, 0x88,
    0xCC, 0x88, 0x5D, 0x3A, 0x34, 0xC6, 0xD3, 0xB4, 0x74, 0xE9,
    0xE0, 0x2D, 0x73, 0x8B, 0xD0, 0xA9, 0x47, 0xA3, 0xC5, 0x3A,
    0x46, 0xA6, 0x1E, 0xED, 0x16, 0xAF, 0x18, 0x91, 0x7A, 0xB4,
    0x5A, 0x2D, 0x63, 0x60, 0xE9, 0xE1, 0x1E, 0xD1, 0xF6, 0x92,
    0xA9, 0x47, 0xA7, 0xD8, 0xC6, 0x4B, 0xA5, 0x1E, 0x9D, 0x14,
    0xAB, 0x28, 0x9D, 0x7A, 0x7C, 0x52, 0xAC, 0xBD, 0x54, 0xEA,
    0xF1, 0x09, 0xF1, 0x8A, 0x51, 0x61, 0x20, 0xAB, 0xD8, 0xC6,
    0x22, 0x85, 0x8E, 0xA4, 0x36, 0x4B, 0xAB, 0xEC, 0x7A, 0x9E,
    0x5C, 0x54, 0xBC, 0x89, 0x69, 0x95, 0x2D, 0x35, 0xF5, 0x58,
    0x00, 0x0F
};

/// @brief LPC encoded word "three"
static const uint8_t LPC_THREE[] = {
    0x00, 0x00, 0x06, 0x00, 0x33, 0x4A, 0x01, 0xA0, 0x7B, 0x2B,
    0x00, 0x4C, 0xED, 0xD5, 0x5A, 0xA7, 0x55, 0x6D, 0xA5, 0x4E,
    0x1B, 0x34, 0xD7, 0x76, 0x84, 0x5A, 0x5D, 0xD2, 0xE8, 0x3F,
    0x19, 0xF8, 0x74, 0x99, 0x0B, 0xCF, 0x67, 0xA8, 0xD5, 0x27,
    0xA6, 0x32, 0xDF, 0xA6, 0x56, 0x9F, 0x90, 0x7B, 0x7F, 0x99,
    0x5E, 0x7D, 0x42, 0xEE, 0xF3, 0x25, 0x78, 0xF5, 0x89, 0x98,
    0xCD, 0x97, 0xE9, 0xD5, 0x67, 0xA4, 0x5E, 0x5F, 0xA6, 0x4E,
    0x57, 0xA8, 0x48, 0x7D, 0x24, 0x5E, 0x43, 0x43, 0xA2, 0xF1,
    0x65, 0xA8, 0x95, 0x09, 0x5A, 0xF4, 0x3B, 0xD9, 0x36, 0x45,
    0xE4, 0x39, 0x2B, 0x52, 0x52, 0xD7, 0x34, 0x61, 0x5E, 0x98,
    0x01, 0x78
};

/// @brief LPC encoded word "four"
static const uint8_t LPC_FOUR[] = {
    0x04, 0xC0, 0x1F, 0x25, 0xB5, 0x6A, 0x65, 0x12, 0xF5, 0xE8,
    0x32, 0xEA, 0x17, 0xC6, 0x5A, 0xA3, 0xD3, 0xA0, 0x5E, 0xA8,
    0xD8, 0x0C, 0x2A, 0xBD, 0x3E, 0xA5, 0xA2, 0x79, 0xA8, 0xF4,
    0xFA, 0xA6, 0x8A, 0xF4, 0xA0, 0xD6, 0xEB, 0x9B, 0x22, 0xD6,
    0x83, 0x5A, 0x6F, 0xAE, 0xAB, 0xFA, 0x0C, 0x1A, 0xBD, 0x39,
    0xE6, 0xE2, 0x53, 0x6A, 0x0C, 0x76, 0xBB, 0xAB, 0x57, 0x85,
    0x31, 0xDA, 0xAB, 0xE6, 0x51, 0x91, 0xC6, 0x60, 0xB7, 0xA6,
    0x5B, 0x95, 0x1C, 0x83, 0x5D, 0x52, 0xAE, 0x55, 0x69, 0xF5,
    0x6E, 0x49, 0x94, 0x46, 0xE5, 0xD5, 0xBB, 0x25, 0x51, 0x6A,
    0x95, 0x47, 0xEF, 0xA6, 0x64, 0x89, 0x8D, 0x2E, 0xBD, 0x9E,
    0x92, 0x25, 0x52, 0x25, 0xF5, 0x21, 0x73, 0xB5, 0x88, 0x6D,
    0x80, 0x07
};

/// @brief LPC encoded word "five"
static const uint8_t LPC_FIVE[] = {
    0x00, 0x00, 0x02, 0x88, 0x42, 0xBC, 0x25, 0x49, 0x45, 0x04,
    0x49, 0x95, 0xD3, 0xC7, 0x30, 0x61, 0xE2, 0xA3, 0x4F, 0x9F,
    0x42, 0xA5, 0x51, 0x96, 0x39, 0x63, 0xD6, 0x93, 0xCE, 0x51,
    0xFA, 0x8C, 0x45, 0x75, 0xB8, 0x78, 0xE9, 0x33, 0x15, 0x9D,
    0x51, 0xE2, 0x65, 0xCE, 0x54, 0x8D, 0x79, 0x6A, 0x96, 0x3E,
    0x63, 0xD1, 0x6E, 0x15, 0x55, 0xF8, 0x8C, 0xC5, 0x89, 0x76,
    0x95, 0x99, 0x33, 0x56, 0x27, 0xDC, 0x5D, 0xA1, 0xCE, 0x58,
    0xB4, 0x68, 0xD5, 0x18, 0x3E, 0x63, 0x91, 0xAA, 0xDD, 0x1D,
    0x78, 0x8D, 0x45, 0xB3, 0x74, 0x55, 0xE0, 0x31, 0x56, 0x4F,
    0xA2, 0xDE, 0xB5, 0x0C, 0xA0, 0xB4, 0xA5, 0x02, 0x80, 0xF3,
    0x06, 0x00, 0x78
};

/// @brief LPC encoded word "six"
static const uint8_t LPC_SIX[] = {
    0x40, 0x80, 0xC8, 0x4C, 0x19, 0x10, 0x98, 0x99, 0x00, 0xAA,
    0x34, 0x53, 0x40, 0x17, 0x2E, 0x0A, 0x68, 0xDC, 0x54, 0x01,
    0x55, 0x39, 0x1B, 0x20, 0x1B, 0xD5, 0xD3, 0x27, 0x45, 0x39,
    0x3D, 0xA4, 0x4F, 0x5F, 0x24, 0xE9, 0xF5, 0x98, 0x6E, 0x5D,
    0x45, 0xAA, 0xBD, 0x19, 0xA4, 0x74, 0x95, 0x63, 0x4E, 0xB9,
    0x6D, 0x57, 0x3B, 0xE9, 0xD5, 0xE1, 0x96, 0x01, 0x40, 0x01,
    0x2A, 0xBA, 0x1B, 0x20, 0xBB, 0x10, 0x07, 0x14, 0x55, 0x62,
    0x80, 0x24, 0x9C, 0x0C, 0x50, 0x69, 0x8A, 0x01, 0x1A, 0x76,
    0x31, 0x40, 0xE5, 0x2E, 0x0E, 0xC8, 0xCC, 0xD9, 0x00, 0x89,
    0x85, 0xC2, 0x03
};

/// @brief LPC encoded word "seven"
static const uint8_t LPC_SEVEN[] = {
    0x00, 0x04, 0x60, 0x36, 0x8B, 0x01, 0x56, 0x58, 0x08, 0x20,
    0x63, 0x13, 0x01, 0x54, 0xE1, 0xAA, 0x80, 0xCA, 0xDC, 0x15,
    0xD0, 0x71, 0xA8, 0x03, 0x50, 0x8D, 0x3C, 0x43, 0x70, 0x9E,
    0x91, 0x4D, 0xF5, 0xF4, 0xD1, 0x7B, 0x44, 0x16, 0xD9, 0x33,
    0x44, 0x17, 0x11, 0x31, 0x42, 0xD7, 0xE0, 0x5D, 0x46, 0x78,
    0x1A, 0x19, 0xA3, 0x76, 0x19, 0x61, 0x51, 0x79, 0x8C, 0xD6,
    0x86, 0x9B, 0x65, 0xED, 0x31, 0x7A, 0x97, 0xA6, 0x1E, 0x53,
    0xD6, 0xE8, 0xBD, 0x87, 0x76, 0x9A, 0x19, 0x63, 0xB0, 0x92,
    0xD4, 0x65, 0xB9, 0x0D, 0xDC, 0xFA, 0x78, 0x86, 0xA5, 0x31,
    0x4A, 0x6D, 0xE3, 0x19, 0xB2, 0xDB, 0xA8, 0xB4, 0x4E, 0xB6,
    0x29, 0x6E, 0xA3, 0xD2, 0x32, 0xD9, 0x61, 0xBB, 0x8D, 0xC2,
    0x58, 0x57, 0xA7, 0xED, 0x36, 0x5A, 0x25, 0x1D, 0x13, 0x8E,
    0xCA, 0x28, 0x8C, 0x55, 0x74, 0x39, 0x76, 0xB5, 0x51, 0x92,
    0x59, 0x69, 0xDB, 0xE4, 0x52, 0x67, 0x46, 0x44, 0x1C, 0x78
};

/// @brief LPC encoded word "eight"
static const uint8_t LPC_EIGHT[] = {
    0x70, 0x86, 0x6A, 0xC8, 0x7D, 0x26, 0xD4, 0xE9, 0xB3, 0xE4,
    0xCC, 0x4D, 0x41, 0xA7, 0xCF, 0x9A, 0xA2, 0x2E, 0x0D, 0x9D,
    0x3E, 0x72, 0xF5, 0xB9, 0x10, 0x7C, 0xBA, 0xC8, 0x25, 0x76,
    0x23, 0xF0, 0xEA, 0x12, 0x51, 0xEF, 0x2F, 0x43, 0xAB, 0xCB,
    0x48, 0xBD, 0xBE, 0x0D, 0x95, 0x2E, 0x03, 0xCB, 0xBA, 0x14,
    0xEC, 0x7A, 0xA5, 0xAB, 0x3B, 0xCC, 0x96, 0xE9, 0x94, 0xAA,
    0x2A, 0x8F, 0xC4, 0xA6, 0x73, 0x22, 0x72, 0x3C, 0x12, 0xAB,
    0x2E, 0x70, 0x8B, 0x0E, 0xB7, 0x0B, 0x2A, 0x0F, 0xC2, 0x72,
    0xC2, 0x6D, 0xC1, 0x32, 0x87, 0xE5, 0xB0, 0x89, 0xC8, 0x02,
    0x08, 0x52, 0x9B, 0x01, 0x24, 0x47, 0x87, 0x90, 0xF6, 0x49,
    0x52, 0x4B, 0x63, 0x5C, 0xE2, 0xBA, 0xDC, 0x54, 0x36, 0x3C
};

/// @brief LPC encoded word "nine"
static const uint8_t LPC_NINE[] = {
    0xAA, 0x80, 0xB1, 0x7B, 0x50, 0xA5, 0xB8, 0x01, 0xB6, 0x1C,
    0x67, 0xA7, 0x13, 0x06, 0x58, 0x73, 0x8C, 0x8D, 0x49, 0x1A,
    0xA8, 0xF3, 0xB5, 0x30, 0x46, 0x6B, 0x0A, 0xD1, 0x52, 0xC2,
    0xE9, 0x9C, 0x31, 0x05, 0x4F, 0xB1, 0x94, 0x7A, 0x86, 0x14,
    0x32, 0xD9, 0xCA, 0xCC, 0x19, 0x53, 0xA8, 0x24, 0x4F, 0x2B,
    0x67, 0x4C, 0xA9, 0x4C, 0x3C, 0xCD, 0x9C, 0x31, 0xB9, 0x4C,
    0xD5, 0x30, 0x72, 0xA6, 0xEC, 0x3C, 0xD5, 0x32, 0xC8, 0x99,
    0x8A, 0x53, 0x37, 0x2F, 0x23, 0x67, 0x2C, 0x8A, 0xD3, 0x23,
    0x8C, 0x9C, 0xB1, 0x69, 0xB2, 0xC8, 0x0A, 0x72, 0xC6, 0x2A,
    0xC9, 0x23, 0x3B, 0x74, 0x1B, 0xB9, 0xF5, 0x6E, 0x73, 0x33,
    0x65, 0x50, 0x46, 0x27, 0x23, 0xC5, 0x8C, 0xBE, 0x48, 0x72,
    0xA9, 0x88, 0x94, 0x9A, 0x64, 0xD8, 0xA5, 0xDA, 0x68, 0x18,
    0x93, 0x13, 0x13, 0x4F, 0x2A, 0xF0
};

/// @brief LPC encoded word "ten"
static const uint8_t LPC_TEN[] = {
    0x65, 0x49, 0x5A, 0x2B, 0x6B, 0x43, 0xB6, 0x26, 0x6A, 0x6E,
    0xED, 0xA0, 0xBC, 0xBA, 0x68, 0xB5, 0xB5, 0x82, 0xF2, 0xE9,
    0x93, 0xD3, 0xF2, 0x2C, 0x31, 0x67, 0xC8, 0x56, 0xCA, 0xB3,
    0x44, 0x9F, 0xB1, 0x58, 0x29, 0xAD, 0x22, 0x7D, 0xC6, 0x62,
    0x38, 0x34, 0xDA, 0xF4, 0x98, 0xA5, 0xB5, 0x4E, 0x0F, 0xB9,
    0x6D, 0xD2, 0x4A, 0xD6, 0x3A, 0x68, 0xB7, 0x49, 0x69, 0x19,
    0xEB, 0x92, 0xD5, 0x66, 0xAB, 0x78, 0x6C, 0x52, 0x51, 0x5B,
    0xAC, 0x92, 0xB1, 0x4D, 0x85, 0x69, 0xA1, 0xDE, 0x36, 0x26,
    0x65, 0xAF, 0xB5, 0x05, 0x75, 0x4E, 0xAF, 0x54, 0xA6, 0x1C,
    0xC5, 0x69, 0x4C, 0x51, 0xC8, 0x53, 0x10, 0xE7, 0x36, 0x39,
    0xF0
};

/// @brief LPC encoded word "eleven"
static const uint8_t LPC_ELEVEN[] = {
    0xA6, 0x49, 0x92, 0x7A, 0xB2, 0x0C, 0xA7, 0xBA, 0x7B, 0x34,
    0xCF, 0x0B, 0x95, 0xBA, 0xA2, 0xD0, 0xBA, 0x3A, 0x60, 0xEB,
    0xB3, 0xA2, 0x98, 0xEA, 0x42, 0x63, 0x8A, 0x86, 0x73, 0x3B,
    0x0D, 0xAF, 0x25, 0x28, 0xEF, 0x0D, 0x8D, 0xB2, 0xD6, 0x20,
    0xA6, 0x2A, 0xA8, 0xD6, 0x5A, 0x92, 0xB0, 0x69, 0xB6, 0x26,
    0x63, 0x71, 0xBE, 0x86, 0xB9, 0x67, 0xAD, 0xC5, 0xEB, 0xEE,
    0x44, 0x9B, 0x7D, 0xE6, 0xA8, 0xBA, 0x8B, 0x6C, 0xF2, 0x59,
    0x92, 0xCE, 0x76, 0xEE, 0xD2, 0x67, 0x8A, 0x26, 0x2B, 0xBC,
    0xC3, 0x9C, 0x21, 0x78, 0xCF, 0xF4, 0x12, 0xA3, 0x00, 0xD0,
    0xD2, 0x14, 0x00, 0x72, 0x45, 0x29, 0x23, 0xCB, 0x28, 0xB7,
    0xB0, 0x63, 0x8C, 0x4A, 0xA3, 0xC2, 0xAD, 0xAE, 0x21, 0x68,
    0x6F, 0x95, 0x8E, 0x72, 0x86, 0xE8, 0xCA, 0x54, 0xB6, 0xE8,
    0xE8, 0x7D, 0x08, 0x36, 0x1F, 0x23, 0xA5, 0xE3, 0xD6, 0x5B,
    0xA3, 0x5C, 0x95, 0x8E, 0xEB, 0x18, 0x89, 0x74, 0x94, 0x7A,
    0xAE, 0x6C, 0x7C, 0xD4, 0x51, 0xEA, 0xA9, 0xF1, 0x8E, 0x72,
    0xC7, 0xA9, 0x17, 0x52, 0xC6, 0x26, 0x5C, 0xA7, 0x8E, 0x2B,
    0x6D, 0x9F, 0x70, 0x94, 0x3A, 0xA6, 0xB5, 0xB2, 0xD3, 0x76,
    0xE8, 0xA8, 0xD1, 0xCE, 0x0A, 0x5B, 0xA1, 0xE3, 0x52, 0x33,
    0xB2, 0x6C, 0xBB, 0x56, 0x4A, 0x71, 0x8B, 0xB2, 0x03, 0x00,
    0x0F
};

/// @brief LPC encoded word "twelve"
static const uint8_t LPC_TWELVE[] = {
    0x00, 0x04, 0x00, 0x1F, 0x94, 0x00, 0xF8, 0xA3, 0x8F, 0xC9,
    0x57, 0xB7, 0x48, 0x1F, 0xB2, 0xC6, 0x90, 0x2C, 0xDC, 0x33,
    0xC8, 0x99, 0x92, 0xB7, 0x56, 0xAB, 0xD0, 0x67, 0x0A, 0x29,
    0xC3, 0xA3, 0x82, 0x9C, 0x29, 0x9B, 0x2C, 0xE7, 0x18, 0x7D,
    0xA6, 0xA4, 0xBB, 0x92, 0x6C, 0xCC, 0x99, 0x92, 0xDE, 0x34,
    0xD6, 0xDB, 0x67, 0x8A, 0x7A, 0x2A, 0xC0, 0x6E, 0xAF, 0x31,
    0xA8, 0x0B, 0x65, 0xBD, 0x39, 0xA6, 0x20, 0x2E, 0x9D, 0xE5,
    0xE6, 0x98, 0x9C, 0xDD, 0x30, 0x8A, 0x4B, 0x63, 0x8A, 0x62,
    0xD2, 0xD1, 0x2E, 0x95, 0xD1, 0xEA, 0x4E, 0xC5, 0x9C, 0x3C,
    0xC6, 0xCC, 0xC2, 0xCC, 0x3C, 0xCC, 0x28, 0x87, 0x08, 0x73,
    0xD7, 0x2A, 0x0E, 0x48, 0xDC, 0xCC, 0x00, 0x91, 0x99, 0x18,
    0x20, 0x50, 0x55, 0x05, 0x44, 0xA6, 0xDC, 0xC6, 0x15, 0x4A,
    0x43, 0x38, 0x4A, 0xC9, 0xA7, 0x77, 0x31, 0xD7, 0xA8, 0x0C,
    0x48, 0x5C, 0xE4, 0x01
};

/// @brief LPC encoded prefix word "thir-"
static const uint8_t LPC_THIR_[] = {
    0x00, 0xC0, 0x80, 0x26, 0x85, 0x15, 0x00, 0x73, 0xE4, 0x69,
    0x93, 0xB2, 0x1A, 0xF6, 0xD0, 0xA7, 0x8F, 0x3A, 0xA2, 0xCD,
    0x43, 0x9F, 0x21, 0x4B, 0xF7, 0x51, 0x2B, 0x7C, 0x86, 0xAC,
    0xCC, 0x5B, 0xBC, 0xCC, 0x19, 0x93, 0x53, 0xCF, 0x94, 0x4A,
    0x67, 0x4C, 0x81, 0xA3, 0x5D, 0x27, 0x9D, 0x31, 0x45, 0xF1,
    0x0A, 0xAD, 0x74, 0xC6, 0x18, 0xD5, 0xA7, 0xB4, 0xD2, 0x19,
    0x63, 0xE4, 0xDC, 0x92, 0x4A, 0x63, 0x8C, 0x09, 0x73, 0x5C,
    0x47, 0x8D, 0x29, 0x04, 0xF6, 0x2E, 0xAF, 0xDD, 0xD6, 0xE8,
    0x55, 0x33, 0xAB, 0x56, 0x3A, 0x9C, 0x8F, 0xCA, 0x28, 0xCB,
    0x10, 0xA6, 0xA0, 0x23, 0x2B, 0xDC, 0xD2, 0x03
};

/// @brief LPC encoded prefix word "fif-"
static const uint8_t LPC_FIF_[] = {
    0xC0, 0x80, 0xA8, 0x29, 0x15, 0x40, 0x8A, 0xED, 0xE9, 0xB2,
    0xC3, 0x8E, 0x99, 0xC0, 0xA3, 0x0F, 0x9A, 0x7B, 0x3A, 0x02,
    0x9F, 0x3E, 0x1A, 0xAA, 0xED, 0x0C, 0xBC, 0xC6, 0x6C, 0x30,
    0xA6, 0xB3, 0xD0, 0x9A, 0xAA, 0x23, 0x55, 0xEF, 0x46, 0xAB,
    0xED, 0xC9, 0x94, 0xD9, 0x9B, 0x8E, 0xA2, 0x7B, 0x15, 0xF6,
    0x6C, 0x3A, 0x9A, 0x51, 0x5D, 0x85, 0x2D, 0xC9, 0x18, 0xBA,
    0x37, 0x66, 0xF5, 0x24, 0x0A, 0x88, 0x82, 0x55, 0x01, 0x41,
    0xB2, 0x29, 0x20, 0x4B, 0x32, 0x03, 0x24, 0x89, 0xE1, 0xB2,
    0xAA, 0xD8, 0x3B, 0x3D, 0xF6, 0x03
};

/// @brief LPC encoded suffix word "-teen"
static const uint8_t LPC__TEEN[] = {
    0xA3, 0x5C, 0x41, 0x99, 0xB4, 0x2A, 0xB7, 0x26, 0x12, 0x8D,
    0xD9, 0x12, 0x32, 0xDA, 0x44, 0x34, 0xFA, 0xCB, 0xF0, 0xE8,
    0x13, 0xB2, 0xE8, 0x4F, 0x21, 0xAB, 0xCF, 0x48, 0xBD, 0xBE,
    0x0C, 0xAD, 0xBE, 0x40, 0x89, 0xFA, 0x12, 0x74, 0xFA, 0x8C,
    0xD4, 0xEA, 0x53, 0xD0, 0xE9, 0x0B, 0x12, 0xCB, 0x2F, 0xC1,
    0xA7, 0xCF, 0x48, 0xA2, 0xAE, 0x04, 0x9F, 0xBE, 0x40, 0x89,
    0xFA, 0x30, 0xBC, 0xFA, 0x8C, 0xC5, 0xEA, 0xD3, 0xD0, 0x19,
    0x32, 0x96, 0xE8, 0x2B, 0xC3, 0x67, 0xC8, 0x48, 0x62, 0x2E,
    0x0C, 0x8D, 0xD1, 0x91, 0xEC, 0x69, 0x33, 0xD3, 0x06, 0x66,
    0x73, 0x5A, 0xD5, 0x74, 0x1B, 0xB8, 0xF6, 0x2D, 0x73, 0x29,
    0x6D, 0x14, 0xCA, 0x36, 0x22, 0x69, 0xB7, 0x51, 0x69, 0x99,
    0xEC, 0x90, 0xD5, 0x46, 0xA1, 0x6D, 0xA2, 0x4A, 0x72, 0x1B,
    0x8C, 0xD4, 0xF1, 0x36, 0x3A, 0x65, 0x90, 0x4A, 0x2B, 0x3A,
    0x64, 0x8F, 0x36, 0x4A, 0x51, 0xA9, 0xAC, 0x5C, 0xDA, 0x68,
    0x58, 0x34, 0x2B, 0x72, 0x1A, 0x92, 0x63, 0xD1, 0x74, 0x29,
    0x00, 0x0F
};

/// @brief LPC encoded word "twenty"
static const uint8_t LPC_TWENTY[] = {
    0x29, 0x1B, 0x8A, 0xC5, 0xC7, 0x13, 0x32, 0x00, 0x8C, 0x2A,
    0x02, 0x80, 0x1D, 0x91, 0x66, 0xDE, 0x32, 0xC3, 0xAD, 0x54,
    0x99, 0x64, 0xAC, 0x88, 0xD2, 0x42, 0x63, 0xF4, 0xDE, 0x33,
    0xC3, 0x86, 0x9E, 0x31, 0x3A, 0xAB, 0x0C, 0x1F, 0x7C, 0xC6,
    0x6A, 0xD5, 0x23, 0x7C, 0xF0, 0x19, 0xAB, 0x51, 0xF3, 0xAC,
    0xC0, 0x67, 0xAE, 0x4A, 0xC5, 0xA2, 0x4B, 0xB5, 0x51, 0x6B,
    0x9D, 0x0A, 0x67, 0x32, 0x26, 0xA3, 0xA5, 0x2B, 0x4B, 0x4E,
    0x19, 0x85, 0xB6, 0x8D, 0x0A, 0x29, 0x69, 0xC4, 0x21, 0xA6,
    0xDD, 0xAC, 0xA4, 0x11, 0x87, 0xDC, 0x32, 0x37, 0x13, 0x26,
    0x98, 0xBB, 0xCA, 0x3C, 0x30, 0x00, 0x80, 0x01, 0x12, 0x63,
    0x56, 0x80, 0x12, 0x1C, 0xA5, 0x0C, 0x5C, 0xE2, 0xDA, 0x04,
    0x95, 0x36, 0x33, 0xF2, 0x6D, 0x0F, 0x93, 0x96, 0xCC, 0xD1,
    0xBB, 0x42, 0x0C, 0xC0, 0x03
};

/// @brief LPC encoded suffix word "-ty"
static const uint8_t LPC__TY[] = {
    0x90, 0xA6, 0xCC, 0xDD, 0xC2, 0xDC, 0xF1, 0x99, 0x66, 0x1E,
    0x63, 0xE5, 0xC5, 0xAB, 0xEB, 0x56, 0x50, 0x2D, 0x4B, 0xAF,
    0x32, 0x31, 0x8E, 0x6B, 0x37, 0x3C, 0xA6, 0xC4, 0xD8, 0xB7,
    0x3D, 0x88, 0x01, 0x80, 0xCF, 0x15, 0x00, 0xD0, 0x3E, 0x0F
}; 

/// @brief LPC encoded word "minus"
static const uint8_t LPC_MINUS[] = {
    0xA0, 0x0A, 0x30, 0xAA, 0x83, 0xC3, 0xB2, 0x69, 0x60, 0xC9,
    0x4C, 0x6D, 0xD9, 0x6E, 0x04, 0x3D, 0xC6, 0x34, 0x15, 0x85,
    0x11, 0xB4, 0x68, 0xCF, 0x90, 0x9D, 0x46, 0xD8, 0xB2, 0x35,
    0xD3, 0x71, 0x9A, 0x60, 0x8F, 0x8A, 0xC8, 0x38, 0xA3, 0xF3,
    0xD3, 0x44, 0x32, 0xAC, 0x9E, 0x29, 0xE6, 0x74, 0xB1, 0x32,
    0x7A, 0xA6, 0xEC, 0xBC, 0x5C, 0x22, 0xCC, 0x19, 0x4B, 0xD0,
    0x34, 0xAB, 0xC0, 0x67, 0xC8, 0x5E, 0x34, 0x3D, 0x8D, 0x9C,
    0xB1, 0x78, 0xCE, 0xCA, 0x34, 0x73, 0xC6, 0x16, 0x58, 0x32,
    0xAB, 0xF0, 0x19, 0x9B, 0x15, 0xCC, 0x89, 0xC2, 0x67, 0xAC,
    0x92, 0xB9, 0x3A, 0x43, 0x9F, 0x29, 0x11, 0xB3, 0x5E, 0x33,
    0x53, 0x26, 0x14, 0x6B, 0x2A, 0xC2, 0x72, 0x99, 0x70, 0x88,
    0xED, 0x34, 0xCB, 0x6D, 0xE2, 0xCE, 0xA6, 0x33, 0x22, 0xAD,
    0x29, 0x72, 0x2E, 0xDB, 0x6C, 0x7C, 0xA6, 0xAC, 0x24, 0x34,
    0x2A, 0xCC, 0x99, 0xB2, 0x31, 0x35, 0xEF, 0xB0, 0x67, 0x0E,
    0x3A, 0xC4, 0x2B, 0x83, 0xAC, 0x59, 0x98, 0xF2, 0x8C, 0x36,
    0x3B, 0xF2, 0x62, 0x5D, 0xC4, 0x2B, 0x8C, 0x03, 0x02, 0x0F,
    0x35, 0x40, 0x24, 0xEE, 0x06, 0x88, 0x28, 0xCD, 0x00, 0x8D,
    0x84, 0x1A, 0xA0, 0xD3, 0x52, 0x03, 0x74, 0x1C, 0xA2, 0x80,
    0x8E, 0x43, 0x05, 0xD0, 0x51, 0x84, 0x00, 0x06, 0x72, 0x13,
    0x40, 0x45, 0xEE, 0x0C, 0xC8, 0x20, 0x82, 0x00, 0x19, 0x54,
    0xC0, 0x03
}; 

/// @brief LPC encoded word "point"
static const uint8_t LPC_POINT[] = {
    0x2E, 0xF1, 0xD6, 0xA6, 0x3D, 0xA4, 0x88, 0x54, 0xC5, 0x2E,
    0x07, 0x8D, 0x65, 0x32, 0xBE, 0x53, 0x99, 0x63, 0x64, 0xA8,
    0xF5, 0x0D, 0x11, 0xEB, 0xC2, 0x6D, 0xB0, 0x37, 0x94, 0x6D,
    0x0B, 0xB7, 0xC1, 0xEE, 0x12, 0xF5, 0x1E, 0x3C, 0x06, 0xDB,
    0x5B, 0xD5, 0xF2, 0xF0, 0x98, 0x6C, 0x73, 0xF7, 0xA8, 0xA2,
    0x6B, 0x32, 0x25, 0x22, 0x2D, 0xCA, 0x9C, 0xD9, 0xDB, 0xF4,
    0x6A, 0x2D, 0x7C, 0x96, 0x60, 0xD5, 0xBB, 0x6D, 0xF0, 0x99,
    0x92, 0xE2, 0x9C, 0xF2, 0x40, 0x63, 0x0E, 0x9C, 0x6B, 0x26,
    0x22, 0xA7, 0x19, 0xB6, 0xEC, 0x0A, 0xB7, 0x92, 0x66, 0x98,
    0x73, 0x32, 0xD2, 0x74, 0x9A, 0x89, 0xF7, 0xCD, 0x2A, 0xDB,
    0x61, 0x42, 0x29, 0xBA, 0xA3, 0x23, 0xBB, 0x91, 0x59, 0x9F,
    0xF4, 0x8C, 0x6D, 0x26, 0xAD, 0x2D, 0xC2, 0x32, 0x96, 0xE9,
    0xA2, 0xD2, 0xC8, 0x88, 0xC4, 0xAA, 0x70, 0x2A, 0xB2, 0xCC,
    0x13, 0x8B, 0x22, 0x08, 0xCD, 0x74, 0x8F, 0x6D, 0x80, 0xA4,
    0xA4, 0x15, 0xD0, 0x83, 0x18, 0x01, 0xAC, 0x91, 0x74, 0x6B,
    0xD0, 0x6C, 0x19, 0x15, 0x4A, 0x94, 0x81, 0xAB, 0x95, 0x66,
    0x6C, 0x78
}; 

/// @brief LPC encoded word "degrees"
static const uint8_t LPC_DEGREES[] = {
    0xC0, 0x0A, 0x70, 0xA7, 0x12, 0xD9, 0xB2, 0x98, 0xC1, 0x99,
    0x0C, 0x72, 0x4B, 0x6A, 0x04, 0xB3, 0xCB, 0xD9, 0x2D, 0xAB,
    0x11, 0xDC, 0xF1, 0x60, 0x97, 0x52, 0x86, 0xC0, 0xB5, 0xCB,
    0xD5, 0xCA, 0xE8, 0x03, 0xD3, 0xDE, 0x32, 0xC3, 0xA3, 0xF7,
    0xD4, 0xA6, 0xC6, 0x89, 0x8E, 0xC1, 0x63, 0x9F, 0x1E, 0x15,
    0xD3, 0x46, 0x8F, 0x7D, 0xA6, 0x43, 0x4C, 0x4A, 0xB9, 0xEE,
    0xEE, 0xD4, 0x38, 0x61, 0x60, 0xB6, 0xBB, 0xDC, 0x63, 0x81,
    0x01, 0x54, 0x60, 0x2D, 0x49, 0xCA, 0xC6, 0xE6, 0x59, 0xA7,
    0x15, 0xC2, 0x95, 0x65, 0x59, 0xED, 0x31, 0xA8, 0x64, 0xA5,
    0x1D, 0x09, 0xD7, 0x10, 0x82, 0xB8, 0x76, 0x36, 0x5A, 0x7D,
    0x30, 0xDC, 0x39, 0x9E, 0xF0, 0xF4, 0x25, 0x90, 0x59, 0x55,
    0xE3, 0xD3, 0x67, 0x4D, 0x36, 0x13, 0x25, 0x4E, 0x5F, 0x04,
    0x73, 0x5E, 0x94, 0x3A, 0x43, 0xA6, 0x62, 0x7D, 0x11, 0xEA,
    0x0C, 0x89, 0x89, 0xF7, 0x96, 0xA1, 0x35, 0x44, 0xA6, 0x3E,
    0x1F, 0x86, 0xCF, 0x90, 0x98, 0x58, 0x5F, 0x84, 0x39, 0x43,
    0xC2, 0x9A, 0xBD, 0x19, 0xF8, 0x8C, 0x15, 0x89, 0xE5, 0x55,
    0x20, 0x07, 0x40, 0x1D, 0x15, 0x00, 0x4F, 0x22, 0x12, 0x50,
    0x91, 0x78, 0x00, 0x2A, 0x10, 0x73, 0xC0, 0x00, 0x62, 0x01,
    0x58, 0x58, 0xCC, 0x01, 0x9B, 0x8A, 0x3B, 0xE0, 0x30, 0x09,
    0x03, 0x0C, 0xE8, 0x66, 0x80, 0x09, 0xD5, 0x05, 0x30, 0xB1,
    0xEA, 0x03
};

/// @brief LPC encoded word "Celsius"
static const uint8_t LPC_CELSIUS[] = {
    0xC0, 0x00, 0x24, 0x27, 0x18, 0x00, 0x49, 0x9B, 0x00, 0x12,
    0x0C, 0x56, 0x40, 0xC1, 0x61, 0x06, 0x68, 0x3C, 0x55, 0x01,
    0x93, 0xA4, 0x2A, 0x60, 0xD2, 0x74, 0x03, 0x74, 0x94, 0xAE,
    0x00, 0x21, 0xC7, 0xCF, 0x5C, 0x54, 0xB8, 0x6B, 0x95, 0x5E,
    0x6B, 0x8C, 0x11, 0xA6, 0x13, 0xFA, 0x6C, 0xD1, 0xB7, 0x07,
    0x77, 0x91, 0xB3, 0x86, 0x50, 0x69, 0x9C, 0xB5, 0xD6, 0xE4,
    0x62, 0x97, 0x58, 0x54, 0x3E, 0xB3, 0xF3, 0xD5, 0x14, 0x59,
    0x79, 0x2C, 0x26, 0x65, 0x63, 0x76, 0xE4, 0x31, 0xAB, 0x90,
    0x8D, 0x55, 0x91, 0xC6, 0x14, 0x49, 0x95, 0x99, 0x37, 0x5C,
    0x53, 0xC2, 0xE5, 0xEE, 0xD1, 0x78, 0xCD, 0x05, 0x87, 0x59,
    0x66, 0xE2, 0x35, 0x4C, 0xD9, 0xCE, 0x22, 0x49, 0x4E, 0xBB,
    0xB0, 0x3B, 0xBB, 0x25, 0x71, 0x80, 0x06, 0x13, 0x0E, 0xE8,
    0xD0, 0x6D, 0x14, 0x83, 0x3B, 0x8B, 0xDB, 0xEC, 0x33, 0x56,
    0xA1, 0x14, 0x53, 0x83, 0xCF, 0x58, 0x95, 0xB0, 0xF7, 0x8C,
    0x5E, 0x53, 0xE4, 0x6A, 0x33, 0x15, 0xE4, 0x2C, 0x49, 0xAA,
    0xF4, 0x79, 0xA8, 0x33, 0x27, 0x2D, 0xDA, 0x9D, 0x85, 0xCE,
    0x1C, 0x9D, 0xEA, 0x74, 0x14, 0x69, 0x75, 0x54, 0x61, 0x59,
    0x39, 0x48, 0x01, 0x28, 0x94, 0x1A, 0x20, 0x18, 0x67, 0x03,
    0x08, 0x11, 0x2A, 0x80, 0x04, 0xC3, 0x04, 0x30, 0x80, 0xBB,
    0x00, 0x06, 0x72, 0x57, 0xC0, 0x46, 0x12, 0x02, 0x58, 0x48,
    0x53, 0x00, 0x13, 0x49, 0x08, 0x60, 0x00, 0x0B, 0x01, 0x54,
    0x90, 0xCE, 0x80, 0x08, 0x26, 0x08, 0xE0, 0xC8, 0x06, 0x3C
};

/// @brief LPC encoded word "temperature"
static const uint8_t LPC_TEMPERATURE[] = {
    0x21, 0x4B, 0xA2, 0xA2, 0xAD, 0xC2, 0x96, 0x22, 0x58, 0x6D,
    0xAD, 0x02, 0xB3, 0xFA, 0x60, 0xBD, 0x23, 0x52, 0xE8, 0xEA,
    0x92, 0x51, 0xCF, 0x2C, 0xA1, 0xA3, 0xB3, 0xCE, 0x22, 0xD3,
    0xA9, 0xA6, 0x0A, 0xF9, 0x98, 0x88, 0xB4, 0x92, 0x6A, 0x1C,
    0x7C, 0x22, 0x3C, 0x76, 0xA8, 0x91, 0x8F, 0x0D, 0x2F, 0x3B,
    0xAE, 0x82, 0xA9, 0xAA, 0x22, 0x22, 0x03, 0x00, 0xB4, 0xD3,
    0xA5, 0x88, 0x8C, 0x88, 0x3D, 0xBA, 0xD8, 0x70, 0xA5, 0xBC,
    0xD2, 0x6A, 0x52, 0x85, 0xD1, 0xF2, 0x4A, 0xAB, 0x8D, 0x09,
    0x57, 0xC7, 0xA2, 0xB4, 0xCE, 0x79, 0xDE, 0x1C, 0x32, 0x33,
    0xFA, 0xA8, 0xA9, 0xAB, 0x2D, 0x74, 0xE9, 0xA3, 0xC4, 0xC9,
    0x72, 0xCA, 0xAD, 0xEF, 0x9C, 0x34, 0xC3, 0x6B, 0x95, 0x6E,
    0x30, 0x96, 0x1A, 0x4B, 0x02, 0x00, 0x0E, 0x18, 0x82, 0x2C,
    0x01, 0xAB, 0x85, 0x14, 0x60, 0x16, 0x93, 0x02, 0x24, 0x49,
    0xEC, 0x00, 0xD8, 0xB5, 0x1C, 0xC0, 0x2B, 0xCF, 0x9A, 0x62,
    0xA1, 0xF6, 0xB4, 0x49, 0xA3, 0x8F, 0x11, 0x37, 0xC2, 0x6A,
    0xB5, 0x29, 0x14, 0xEA, 0x72, 0xAD, 0x34, 0xC6, 0x94, 0xB1,
    0xDC, 0xAC, 0x66, 0x9B, 0x72, 0x85, 0x36, 0xF5, 0xD8, 0x65,
    0x4A, 0x05, 0x33, 0x5D, 0x6B, 0x12, 0x40, 0x24, 0xEA, 0x07
};

/// @brief LPC encoded word "the"
static const uint8_t LPC_THE[]  = {
    0x20, 0x26, 0x30, 0xBA, 0x93, 0x3D, 0x94, 0x9A, 0xC0, 0xEC,
    0x35, 0x70, 0x27, 0xAA, 0x01, 0xA7, 0x3B, 0x28, 0x24, 0xAB,
    0x01, 0xCC, 0xC9, 0x90, 0x34, 0x15, 0x06, 0x61, 0xBC, 0x22,
    0x32, 0xF6, 0xC8, 0x9D, 0xA9, 0x4C, 0x9D, 0x20, 0x67, 0xF0,
    0x7A, 0x3D, 0x32, 0x8A, 0xAE, 0xDE, 0xAB, 0x2B, 0x4D, 0x2B,
    0x34, 0xFA, 0x60, 0x2A, 0x25, 0x6A, 0x50, 0x19, 0x7C, 0xC8,
    0x94, 0xAC, 0x32, 0xF0, 0x00, 0xFF, 0x0F
};

/// @brief LPC encoded word "time"
static const uint8_t LPC_TIME[] = {
    0x25, 0xAA, 0x56, 0x22, 0x3D, 0xE2, 0xB4, 0xDA, 0xFB, 0xCA,
    0xE4, 0x90, 0xB2, 0xA6, 0xE0, 0x3A, 0x82, 0xA2, 0xCC, 0x99,
    0x53, 0x88, 0x34, 0xAC, 0x22, 0x6B, 0x8E, 0xA9, 0x42, 0x78,
    0xC2, 0x9C, 0x29, 0xB9, 0x0E, 0xA3, 0x28, 0x73, 0x96, 0x18,
    0xDA, 0x85, 0xDB, 0xEC, 0x99, 0x63, 0x6D, 0x15, 0x9B, 0x20,
    0x67, 0x4E, 0x71, 0xCC, 0xAC, 0x8A, 0x9C, 0x29, 0xF9, 0x09,
    0xA3, 0x2C, 0x7C, 0xC6, 0x6C, 0xB3, 0x1C, 0xAB, 0xF4, 0x19,
    0x93, 0xED, 0x70, 0xF1, 0xD2, 0x67, 0x8C, 0x2E, 0xB3, 0xD5,
    0xC3, 0x9C, 0x31, 0xAB, 0xF6, 0x71, 0x0D, 0x72, 0x86, 0x64,
    0xDC, 0x2A, 0xD3, 0xD0, 0xE9, 0xB2, 0x56, 0xED, 0xCC, 0x20,
    0xA7, 0xCB, 0x4A, 0x6D, 0x32, 0x03, 0x9F, 0xA6, 0x18, 0x8A,
    0xAC, 0x12, 0xB3, 0x9A, 0xA4, 0xA8, 0x3A, 0xC2, 0x48, 0xA8,
    0xB1, 0xF3, 0x9E, 0x50, 0x2B, 0xA1, 0x86, 0xC1, 0xBB, 0x32,
    0xC2, 0xA4, 0x1A, 0x7B, 0xEF, 0x8C, 0x8A, 0x1B, 0x6A, 0xEC,
    0xBD, 0xCB, 0x2B, 0x8E, 0xAB, 0xB0, 0x8B, 0xCE, 0xAC, 0xD8,
    0xA5, 0x4A, 0x42, 0x2C, 0xC2, 0x9B, 0x00, 0x3C
};

/// @brief LPC encoded word "is"
static const uint8_t LPC_IS[] = {
    0xAB, 0xAA, 0x1A, 0x2D, 0xB3, 0x03, 0x9F, 0x2E, 0x4B, 0xD6,
    0xEE, 0x08, 0x7C, 0x86, 0x2C, 0xD9, 0x2B, 0xCB, 0xD0, 0x19,
    0x13, 0x37, 0xEB, 0x8E, 0x40, 0x67, 0x0A, 0xC2, 0xA3, 0xB3,
    0x02, 0x9F, 0x72, 0x60, 0x53, 0xCB, 0xA8, 0x74, 0xF2, 0x6F,
    0x2D, 0x58, 0xBD, 0x71, 0x02, 0x12, 0xC8, 0x4D, 0x40, 0x05,
    0x92, 0x01, 0xD8, 0x88, 0x3D, 0x00, 0x0B, 0x6B, 0x04, 0xE0,
    0x60, 0xC9, 0x00, 0x5C, 0x26, 0xE9, 0x80, 0xCB, 0xD9, 0x0C,
    0xF0, 0x05, 0x9B, 0x03, 0x3E, 0x97, 0x50, 0xC0, 0x85, 0x9C,
    0x00, 0x0F
};

/// @brief LPC encoded word "A.M."
static const uint8_t LPC_A_M_[] = {
    0x29, 0x8F, 0x81, 0xDB, 0x47, 0x49, 0xB7, 0x2A, 0x38, 0x6D,
    0x6F, 0x26, 0x3A, 0xAA, 0x10, 0x78, 0xA2, 0x88, 0xEA, 0xA8,
    0x83, 0xA7, 0xCE, 0x56, 0xB2, 0xA3, 0x56, 0x4E, 0x3B, 0x5A,
    0xC4, 0x8C, 0x46, 0x6B, 0x5B, 0x2F, 0x15, 0xDC, 0x1A, 0x6E,
    0x6B, 0xCB, 0x49, 0x4A, 0x6B, 0xA8, 0x9F, 0x4D, 0x27, 0x39,
    0xAD, 0x61, 0xBE, 0xB7, 0x83, 0xA5, 0x8C, 0x56, 0x1A, 0xDF,
    0x2A, 0x15, 0xBD, 0x1A, 0x6B, 0x6C, 0xB2, 0x5C, 0xF0, 0x6A,
    0x82, 0xE1, 0x8E, 0x76, 0xA2, 0xAB, 0x8D, 0x96, 0xCB, 0xDA,
    0x05, 0x9F, 0x36, 0x3A, 0x4E, 0x6F, 0x13, 0x72, 0xBA, 0x9C,
    0xB0, 0x62, 0x54, 0xEC, 0x69, 0x53, 0xC2, 0xCC, 0x32, 0xA9,
    0xA3, 0x75, 0x91, 0x3A, 0x5A, 0xE4, 0xA4, 0x06, 0x65, 0xEB,
    0x4C, 0x37, 0x9D, 0x1A, 0xD0, 0xAD, 0x3B, 0x4D, 0x72, 0x6A,
    0x40, 0xB5, 0xEE, 0x76, 0x53, 0xA9, 0x01, 0x5D, 0xA7, 0x32,
    0x24, 0x95, 0x16, 0x47, 0xEB, 0xE8, 0x34, 0x9D, 0x3A, 0x9C,
    0xB5, 0xB2, 0xDD, 0x4A, 0x69, 0x64, 0xA5, 0x88, 0xB0, 0x24,
    0xA9, 0x31, 0x95, 0x2C, 0x42, 0x13, 0xBB, 0x8A, 0x45, 0xB6,
    0x34, 0x77, 0x63, 0x0A, 0xED, 0x45, 0x3C, 0xC2, 0x8A, 0x29,
    0x8D, 0x53, 0x71, 0x75, 0xC7, 0xA2, 0x64, 0xC6, 0xD5, 0xCD,
    0x93, 0x88, 0x92, 0xFA, 0xF4, 0xF2, 0xB4, 0xA4, 0x4A, 0xE2,
    0xDA, 0xCA, 0xD3, 0x96, 0x2A, 0xA1, 0x2B, 0x2F, 0x0F, 0x47,
    0x04, 0x00, 0x3F, 0x04, 0x1E
};

/// @brief LPC encoded word "P.M."
static const uint8_t LPC_P_M_[] = {
    0x90, 0xDA, 0xC0, 0x79, 0xBA, 0x3C, 0x54, 0x69, 0x24, 0x9B,
    0xAD, 0x10, 0xC1, 0xAD, 0x33, 0xA4, 0xB6, 0x4B, 0xC9, 0xB4,
    0x4E, 0xD3, 0xDE, 0x4A, 0x21, 0xDD, 0xFA, 0x08, 0x7C, 0xAB,
    0x95, 0x4C, 0xE9, 0x03, 0x88, 0x9B, 0x54, 0xD1, 0xA5, 0xF3,
    0x28, 0xAE, 0xD3, 0x08, 0xB7, 0x56, 0xB2, 0x9A, 0x69, 0x13,
    0x3C, 0x1A, 0xC5, 0x6A, 0x66, 0x54, 0xF4, 0x68, 0x0C, 0x8B,
    0x9D, 0x36, 0xC1, 0xAB, 0xF1, 0xD4, 0x77, 0xC6, 0x05, 0x8D,
    0x46, 0xA8, 0xDA, 0x6D, 0x11, 0xB2, 0x5A, 0xA5, 0x63, 0xBA,
    0x5D, 0xC8, 0xEA, 0x82, 0xD2, 0xEE, 0x8D, 0xC0, 0xAB, 0x0B,
    0x4A, 0xAB, 0x26, 0x02, 0xAD, 0x3E, 0x58, 0xA9, 0x9C, 0x34,
    0x72, 0xBA, 0x64, 0xA5, 0x62, 0xDB, 0xC8, 0xEA, 0x82, 0xB5,
    0x8E, 0x0E, 0xA1, 0xAB, 0x8B, 0x4E, 0x2D, 0x3A, 0x8D, 0xB4,
    0xDE, 0x5B, 0x0D, 0xED, 0x0A, 0x9A, 0x3A, 0x1A, 0xBD, 0xA2,
    0xDC, 0x70, 0xEA, 0xA8, 0xF7, 0x8E, 0x4A, 0xC3, 0xA9, 0x63,
    0xDE, 0x3A, 0xB2, 0x84, 0xA4, 0x9E, 0x7B, 0xA9, 0xAA, 0x30,
    0x1D, 0x7A, 0x61, 0xB9, 0xB2, 0x33, 0x74, 0xEA, 0x8C, 0xE1,
    0xB2, 0x69, 0xCB, 0xA9, 0xD3, 0x96, 0xCB, 0xB6, 0x6C, 0x87,
    0x56, 0x5A, 0xA9, 0x98, 0x0A, 0xE3, 0x3A, 0xEA, 0x35, 0xB3,
    0xCA, 0x4A, 0xE8, 0x8C, 0xA7, 0xA8, 0x08, 0xBB, 0xA1, 0x0B,
    0x11, 0xDD, 0xCB, 0x9D, 0xB8, 0x26, 0x15, 0x94, 0x70, 0x75,
    0x6C, 0xBA, 0x98, 0xC5, 0x42, 0x05, 0xB6, 0x69, 0x63, 0x62,
    0x0D, 0x55, 0x32, 0x66, 0x08, 0xD1, 0x34, 0x94, 0x25, 0xAB,
    0x2E, 0x64, 0xF7, 0x10, 0x26, 0xA3, 0x0A, 0x1C, 0xC3, 0xC3,
    0x52, 0x0A, 0x3C
};

/// @brief LPC encoded word "o'clock"
static const uint8_t LPC_OCLOCK[] = {
    0x0C, 0x80, 0x2B, 0xA5, 0xD4, 0x36, 0x9B, 0x66, 0xA4, 0x91,
    0x54, 0x8B, 0xEE, 0x9E, 0x6E, 0x62, 0x52, 0xC3, 0x4A, 0x59,
    0x84, 0x86, 0x31, 0x1D, 0xAF, 0x61, 0x19, 0x6E, 0xD1, 0xB5,
    0x31, 0xA8, 0x7B, 0x95, 0x2D, 0xD5, 0x8A, 0xDC, 0x51, 0xA6,
    0x96, 0x54, 0x2D, 0x63, 0x57, 0xAA, 0x47, 0x02, 0x00, 0x05,
    0xA8, 0x9C, 0x56, 0xA6, 0xA0, 0x62, 0xC4, 0x38, 0x5A, 0x99,
    0x44, 0xCF, 0xC2, 0xF2, 0x34, 0x6D, 0x34, 0xA5, 0x1A, 0xA2,
    0x26, 0x8F, 0xC9, 0x8E, 0x0A, 0x8C, 0x1E, 0xD2, 0x46, 0xDF,
    0x26, 0xC0, 0xF3, 0x70, 0x99, 0x7C, 0x19, 0x87, 0x8C, 0xB1,
    0xE9, 0x34, 0xA5, 0x53, 0xDC, 0x63, 0x87, 0xD1, 0xCE, 0x72,
    0xF5, 0xA8, 0xE3, 0x3A, 0x93, 0xBB, 0xCD, 0x22, 0xB6, 0x9B,
    0xBC, 0xF7, 0x0C, 0x37, 0xA7, 0x04, 0x40, 0x4D, 0x1B, 0x08,
    0x80, 0x92, 0x0A, 0x01, 0xA8, 0x17, 0x83, 0x07
};

/// @brief LPC encoded word "hour"
static const uint8_t LPC_HOUR[] = {
    0xD0, 0x9A, 0xD0, 0x33, 0xD4, 0x33, 0xCC, 0x69, 0x63, 0xCD,
    0x50, 0x8B, 0xB0, 0xAB, 0x0B, 0x29, 0x4B, 0xC5, 0xC3, 0xAE,
    0xC1, 0x1F, 0x33, 0xCB, 0x30, 0xB3, 0x7A, 0x7F, 0xDD, 0x2C,
    0xD3, 0xCC, 0xEA, 0xFD, 0x74, 0x73, 0x0B, 0x33, 0xA3, 0x77,
    0x3D, 0x4D, 0x52, 0x2A, 0x8D, 0xCE, 0x4E, 0x73, 0x4B, 0xA9,
    0x35, 0x3A, 0x3D, 0xB4, 0x42, 0xBD, 0x72, 0xEB, 0x4D, 0x95,
    0x53, 0xF3, 0x4A, 0xA3, 0xD7, 0x4D, 0xD6, 0xD5, 0x6B, 0xB6,
    0x5E, 0x5E, 0x19, 0x73, 0x8D, 0x55, 0x7A, 0x79, 0x65, 0x43,
    0xCD, 0x66, 0xEB, 0xF5, 0xE0, 0x4D, 0xD7, 0x88, 0xAD, 0x73,
    0x95, 0xD6, 0x22, 0x42, 0xB4, 0xCE, 0x56, 0x3E, 0xF1, 0x08,
    0xD5, 0xFA, 0x94, 0x71, 0xB9, 0x2A, 0x64, 0x69, 0x63, 0xC4,
    0x95, 0xAC, 0x50, 0xAD, 0x29, 0x19, 0xC6, 0x22, 0x2A, 0x8E,
    0xA6, 0x2B, 0x57, 0x2A, 0x0F, 0xFD
};

/// @brief LPC encoded word "hours"
static const uint8_t LPC_HOURS[] = {
    0x70, 0xDA, 0x58, 0x33, 0xD4, 0x22, 0xCC, 0xEA, 0x42, 0xCD,
    0x54, 0x8D, 0xB0, 0xAB, 0x0B, 0xCB, 0x5D, 0x23, 0x83, 0xAE,
    0xDE, 0x5F, 0x37, 0xCF, 0x30, 0xB3, 0xFA, 0x30, 0xDD, 0xC5,
    0xD3, 0xCC, 0xE8, 0xDD, 0x48, 0xD3, 0x90, 0x4A, 0xAB, 0x73,
    0x3D, 0x43, 0x9D, 0x12, 0x8D, 0x4E, 0x0F, 0xCD, 0x30, 0xAB,
    0xD4, 0x7A, 0x53, 0xE4, 0x4C, 0x3C, 0x56, 0xEB, 0x75, 0x93,
    0x53, 0xF3, 0x9A, 0x6D, 0x10, 0x47, 0xC6, 0xCD, 0x62, 0xB5,
    0x5E, 0x3E, 0x99, 0x50, 0xB7, 0xD5, 0x7A, 0x35, 0x78, 0xD3,
    0x2C, 0x46, 0xE9, 0x6D, 0xA3, 0x73, 0x8F, 0x08, 0xA5, 0xB3,
    0x95, 0x4E, 0x32, 0x03, 0x95, 0xCE, 0x67, 0x3A, 0xC9, 0x34,
    0xD9, 0xBA, 0x18, 0x71, 0x25, 0x3B, 0x54, 0x6B, 0x4A, 0x82,
    0xD1, 0xC8, 0x52, 0x00, 0x0E, 0x28, 0xCC, 0xC5, 0x01, 0x9D,
    0xB8, 0x3B, 0xA0, 0x43, 0x0F, 0x00, 0x00, 0x80, 0x07
};

/// @brief LPC encoded word "minute"
static const uint8_t LPC_MINUTE[] = {
    0x40, 0x00, 0xF0, 0x35, 0x18, 0x00, 0x7E, 0x6A, 0x5A, 0x51,
    0x8E, 0x89, 0x08, 0xA3, 0x61, 0xC6, 0x35, 0x26, 0xDC, 0xC4,
    0xB8, 0x09, 0x97, 0x58, 0x57, 0x13, 0x1B, 0x46, 0xD8, 0x63,
    0x54, 0x5D, 0xF4, 0x18, 0x83, 0xA3, 0xCA, 0x76, 0xA1, 0x6B,
    0x08, 0x5C, 0x7B, 0x8D, 0xCD, 0x9C, 0x21, 0x0B, 0xEA, 0x09,
    0x15, 0x73, 0x86, 0x2C, 0x28, 0xBB, 0x5C, 0xC8, 0x18, 0x1C,
    0xB7, 0x69, 0x57, 0x23, 0xAD, 0x67, 0x26, 0xAA, 0xCA, 0x45,
    0x9F, 0x3E, 0x09, 0xF6, 0xE8, 0x36, 0x72, 0xFA, 0x2C, 0xA8,
    0xB3, 0x53, 0xF0, 0xE9, 0x13, 0x97, 0xEE, 0x10, 0xB3, 0x6B,
    0x08, 0x52, 0xAB, 0x4A, 0xC9, 0xB5, 0xD1, 0x4A, 0xEB, 0x0E,
    0x27, 0x9B, 0x4A, 0xA9, 0xB2, 0x2A, 0x4C, 0x4A, 0xE8, 0x85,
    0x8C, 0x2A, 0xF7, 0xD8, 0x6E, 0x54, 0x2A, 0x2B, 0xDC, 0x2C,
    0xBB, 0xD1, 0x08, 0xCF, 0xF2, 0x88, 0x2D, 0x00, 0xEA, 0xC2,
    0x21, 0x0D, 0x8D, 0xAA, 0x5A, 0x84, 0x9D, 0x07
};

/// @brief LPC encoded word "minutes"
static const uint8_t LPC_MINUTES[] = {
    0x6E, 0x80, 0x35, 0x26, 0x34, 0xC8, 0x98, 0x09, 0xE7, 0x58,
    0xF3, 0x20, 0x93, 0x56, 0x54, 0x62, 0xC2, 0x43, 0x48, 0x5A,
    0x98, 0xD7, 0xF1, 0x4A, 0xD2, 0x61, 0xC2, 0x25, 0xD6, 0xD5,
    0xA8, 0x86, 0x11, 0xF6, 0x18, 0x13, 0x17, 0xD3, 0x06, 0xED,
    0x79, 0x32, 0x4D, 0xEA, 0x1A, 0x83, 0xE4, 0xAE, 0x30, 0xA1,
    0x67, 0xC8, 0x9C, 0x6A, 0x43, 0x45, 0x9F, 0x21, 0x73, 0xAE,
    0x49, 0x23, 0xB2, 0xA6, 0xCC, 0xA9, 0x3B, 0x5C, 0x48, 0x19,
    0xB0, 0xCF, 0x35, 0x37, 0xAA, 0xA7, 0x8B, 0x52, 0x2C, 0xA7,
    0x8C, 0x9C, 0xBE, 0x08, 0xEC, 0xA8, 0x12, 0xB4, 0xFA, 0xC8,
    0xA5, 0x3B, 0x45, 0xEC, 0x1A, 0x82, 0xD0, 0xAA, 0x52, 0x72,
    0x63, 0xB4, 0xD2, 0xAB, 0xC3, 0xC8, 0xA6, 0x89, 0x9B, 0xEC,
    0x0A, 0x93, 0x12, 0x7A, 0x21, 0x23, 0x2B, 0x22, 0xB6, 0x1B,
    0xA4, 0x8E, 0x0A, 0x77, 0xDB, 0x6E, 0x34, 0xC2, 0xAA, 0x3C,
    0xE2, 0x30, 0x00, 0xFA, 0x08, 0x06, 0xC0, 0x10, 0x91, 0x86,
    0x4A, 0xD4, 0xC3, 0x2C, 0x76, 0x39, 0x26, 0x4F, 0x11, 0x4F,
    0xCB, 0x63, 0xDC, 0x2A, 0xC2, 0xCC, 0x22, 0x1A, 0xA0, 0xC2,
    0x50, 0x03, 0x74, 0xE0, 0x6E, 0x80, 0x0E, 0x3D, 0x1C, 0xD0,
    0x88, 0xBB, 0x03, 0x1A, 0x75, 0x1F, 0xD1, 0x34, 0x17, 0xE2,
    0x11, 0xA7, 0xE5, 0xC3, 0xAC, 0x51, 0x54, 0x9C, 0x92, 0x6E,
    0x5E, 0xC1, 0x62, 0xB5, 0xE0, 0x01
};

/// @brief LPC encoded short pause
static const uint8_t LPC_PAUSE1[] = {
    0x00,0x00,0x00,0x00,0xFF,0x0F
};

/*******************************************************************************
* Function Name: say_number
****************************************************************************//**
* @par Summary
*    
*******************************************************************************/
void
say_number(int16_t number)
{
    if (0 > number)
    {
        synth_say(LPC_MINUS);
        say_number(- number);
    }
    else if (0 == number)
    {
        synth_say(LPC_ZERO);
    }
    else if (19 < number)
    {
        switch (number / 10)
        {
            case 2:
                synth_say(LPC_TWENTY);
            break;
            case 3:
                synth_say(LPC_THIR_);
                synth_say(LPC__TY);
            break;
            case 4:
                synth_say(LPC_FOUR);
                synth_say(LPC__TY);
            break;
            case 5:
                synth_say(LPC_FIF_);
                synth_say(LPC__TY);
            break;
            case 6:
                synth_say(LPC_SIX);
                synth_say(LPC__TY);
            break;
            case 7:
                synth_say(LPC_SEVEN);
                synth_say(LPC__TY);
            break;
            case 8:
                synth_say(LPC_EIGHT);
                synth_say(LPC__TY);
            break;
            case 9:
                synth_say(LPC_NINE);
                synth_say(LPC__TY);
            break;
            default:
            break;
        }
        
        uint8_t rest = number % 10;
        if (0 < rest)
        {
            say_number(rest);
        }
    }
    else
    {
        switch (number)
        {
            case 0:
                synth_say(LPC_ZERO);
            break;

            case 1:
                synth_say(LPC_ONE);
            break;
            
            case 2:
                synth_say(LPC_TWO);
            break;
            
            case 3:
                synth_say(LPC_THREE);
            break;
            
            case 4:
                synth_say(LPC_FOUR);
            break;
            
            case 5:
                synth_say(LPC_FIVE);
            break;
            
            case 6:
                synth_say(LPC_SIX);
            break;

            case 7:
                synth_say(LPC_SEVEN);
            break;

            case 8:
                synth_say(LPC_EIGHT);
            break;

            case 9:
                synth_say(LPC_NINE);
            break;

            case 10:
                synth_say(LPC_TEN);
            break;

            case 11:
                synth_say(LPC_ELEVEN);
            break;

            case 12:
                synth_say(LPC_TWELVE);
            break;

            case 13:
                synth_say(LPC_THIR_);
                synth_say(LPC__TEEN);
            break;

            case 14:
                synth_say(LPC_FOUR);
                synth_say(LPC__TEEN);
            break;

            case 15:
                synth_say(LPC_FIF_);
                synth_say(LPC__TEEN);
            break;

            case 16:
                synth_say(LPC_SIX);
                synth_say(LPC__TEEN);
            break;

            case 17:
                synth_say(LPC_SEVEN);
                synth_say(LPC__TEEN);
            break;

            case 18:
                synth_say(LPC_EIGHT);
                synth_say(LPC__TEEN);
            break;

            case 19:
                synth_say(LPC_NINE);
                synth_say(LPC__TEEN);
            break;
            
            default:
            break;
        }
    }
    synth_say(LPC_PAUSE1);
    return;
}

/*******************************************************************************
* Function Name: say_time
****************************************************************************//**
* @par Summary
*    
*******************************************************************************/
void
say_time(RTC_DATE_TIME dateTime)
{
    uint32 hours = RTC_GetHours(dateTime.time);
    uint32 minutes = RTC_GetMinutes(dateTime.time);
    uint32 ampm = RTC_GetAmPm(dateTime.time);
    uint32 time_format = RTC_GetTimeFormat(dateTime.time);
    
    // Say: "The time is"
    synth_say(LPC_THE);
    synth_say(LPC_TIME);
    synth_say(LPC_IS);
    synth_say(LPC_PAUSE1);
    
    // Say hours
    say_number(hours);
    if (1 == hours)
    {
        synth_say(LPC_HOUR);
    }
    else
    {
        synth_say(LPC_HOURS);
    }
    synth_say(LPC_PAUSE1);
    
    // Say minutes
    say_number(minutes);
    if (1 == minutes)
    {
        synth_say(LPC_MINUTE);
    }
    else
    {
        synth_say(LPC_MINUTES);
    }
    synth_say(LPC_PAUSE1);
    
    // If RTC uses 12 hour format say AM/PM
    if (RTC_12_HOURS_FORMAT == time_format)
    {
        if (RTC_AM == ampm)
        {
            synth_say(LPC_A_M_);
        }
        else 
        {
            synth_say(LPC_P_M_);
        }
    }
}

/*******************************************************************************
* Function Name: say_temperature
****************************************************************************//**
* @par Summary
*    
*******************************************************************************/
void
say_temperature(int16_t temp)
{
    int16_t whole_part = temp / 100;
    uint16_t fraction = (temp % 100) / 10;
    
    // Say: "The temperature is"
    synth_say(LPC_THE);
    synth_say(LPC_TEMPERATURE);
    synth_say(LPC_IS);
    
    // Say decimal number
    say_number(whole_part);
    synth_say(LPC_POINT);
    say_number(fraction);
    
    // Say: "degrees Celsius"
    synth_say(LPC_DEGREES);
    synth_say(LPC_CELSIUS);    
}

/* [] END OF FILE */
