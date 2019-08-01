/***************************************************************************//**
* @file    temperature.c
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
#include "temperature.h"

/*******************************************************************************
* Function Name: temperature_hw_init
****************************************************************************//**
* @par Summary
*     
*******************************************************************************/
void 
temperature_hw_init(void)
{
    // Start the Scanning SAR ADC Component and start conversion
    ADC_Start();
    ADC_StartConvert();

    // Start Reference buffer
    VrefBuffer_Start();

    // Start and enable Programmable Voltage Reference
    PVref_Start();
    PVref_Enable();
}


/*******************************************************************************
* Function Name: get_temperature
****************************************************************************//**
* @par Summary
*     
*
*******************************************************************************/
int16_t 
get_temperature(void)
{
    static int16_t temperature = 0;

    // Filter input and output variables for Vref and Vth measurements
    static int16_t filter_vref = 0;
    static int16_t filter_vth = 0;
    
    if (ADC_IsEndConversion(ADC_RETURN_STATUS))
    {
        // Read the ADC result for reference and thermistor voltages
        int16_t adc_vref = ADC_GetResult16(TEMP_ADC_CH_VREF);
        int16_t adc_vth  = ADC_GetResult16(TEMP_ADC_CH_VTH);

        // Low pass filter the measured ADC counts of Vref
        filter_vref = (adc_vref + (TEMP_FILTER_COEF - 1) * filter_vref) 
                            / TEMP_FILTER_COEF;

        // Low pass filter the measured ADC counts of Vth
        filter_vth = (adc_vth + (TEMP_FILTER_COEF - 1) * filter_vth) 
                            / TEMP_FILTER_COEF;

        int16_t thermistor_resistance = 
            Thermistor_GetResistance(filter_vref, filter_vth);           

        // Calculate temperature in degrees Celsius using the Component API
        temperature = Thermistor_GetTemperature(thermistor_resistance);
    }
    
    return temperature;
}

/* [] END OF FILE */
