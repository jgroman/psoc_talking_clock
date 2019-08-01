/***************************************************************************//**
* @file    temperature.h
* @version 1.0.0
*
* @brief Thermal sensing implementation.
*
* @par Target device
*    CY8C4A45LQI-483
*
* @par Related hardware
*    CY8CKIT-048
*
* @par Code Tested With
*    1. Silicon: PSoC Analog Coprocessor
*    2. IDE: PSoC Creator 4.0 (4.0.0.432)
*    3. Compiler: GCC 4.9.3, ARM MDK 4.54.0.0 (armcc 4.1 b894)
*
* @par Source
*    Code Example CE211321 - Temperature Sensing
*
* @par Components
*    - Scan_ADC       [ADC]
*    - PVref_P4       [PVref]
*    - Opamp_P4       [VrefBuffer]
*    - ThermistorCalc [Thermistor]
*
*******************************************************************************/
    
#ifndef TEMPERATURE_H
	#define TEMPERATURE_H
    
/*******************************************************************************
*   Included Headers
*******************************************************************************/
    #include <project.h>

/*******************************************************************************
*   Macros and #define Constants
*******************************************************************************/
    /// @brief Temperature ADC channel reference voltage
    #define TEMP_ADC_CH_VREF			(0u)
    
    /// @brief Temperature ADC channel thermistor voltage
    #define TEMP_ADC_CH_VTH				(1u)

    /* Cut off frequency = fs/(2 * pi * iir_filter_constant).  In this project
    fs ~= 1 ksps. This results in a cut-off frequency of 4.97 Hz.  We are using
    IIR filter as FIR requires more order of filter to get the same
    cut-off frequency */
    /// @brief Temperature IIR Filter coefficients for each signal
    #define TEMP_FILTER_COEF        	(32u)

/*******************************************************************************
*   Global Variables and Constant Declarations with Applicable Initializations
*******************************************************************************/

/*******************************************************************************
*   Function Declarations
*******************************************************************************/
    /// @brief Initialize thermal sensing hardware components.
    /// @return none
    void temperature_hw_init(void);
    
    /// @brief Get current temperature.
    /// @return int16_t Temperature in degrees Celsius.
    int16_t get_temperature(void);

#endif

/* [] END OF FILE */
