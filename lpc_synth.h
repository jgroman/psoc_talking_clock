/***************************************************************************//**
* @file    lpc_synth.h
* @version 1.0.0
*
* @brief Project independent LPC audio decoder implementation.
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
*    - cy_clock       [Clock_Synth]
*    - TCPWM_P4       [Timer_Synth]
*    - cy_isr         [isr_Synth]
*    - DMA_Channel_P4 [DMA_Synth]         optional
*    - UAB_VDAC       [VDAC_Synth]
*    - cy_pins        [Pin_Synth_Out]
*
* @par Source
*    LPC synth code adapted from https://github.com/going-digital/Talkie
*
* @warning
*    Define / undefine hardware flags DMA_AVAILABLE and FRAM_AVAILABLE
* according to project resources and configuration.
*
* @note
*    Enabling DMA increases SRAM and flash consumption but decreases ISR
* trigger rate.
*
*******************************************************************************/
#ifndef LPC_SYNTH_H
	#define LPC_SYNTH_H
    
/*******************************************************************************
*   Hardware dependent flags
*   - define/undefine according to available resources and configuration
*******************************************************************************/

    /// @def DMA_AVAILABLE
    /// @brief Define if sythesizer should enable DMA transfer
    #define DMA_AVAILABLE

    /// @def FRAM_AVAILABLE
    /// @brief Define if synthesizer reads data from FRAM nonvolatile memory
    #undef FRAM_AVAILABLE

/*******************************************************************************
*   Included Headers
*******************************************************************************/
    #include <project.h>

    #ifdef FRAM_AVAILABLE
        #include <device.h>
    #endif

/*******************************************************************************
*   Macros and #define Constants
*******************************************************************************/
    /// @brief Synthesizer timer clock frequency in Hz
    #define CLOCK_SYNTH  1000000
        
    /// @brief LPC audio sample rate in Hz
    #define SAMPLE_RATE     8000

    /// @brief LPC chirp sample size in bytes
    #define CHIRP_SIZE        41

    #ifdef DMA_AVAILABLE
        /// @brief DMA descriptor 0
        #define DMA_DESCR0          0

        /// @brief DMA descriptor 1
        #define DMA_DESCR1          1

        /// @brief DMA buffer size in bytes
        #define DMA_BUFFER_SIZE    20
    #endif

/*******************************************************************************
*   Global Variables and Constant Declarations with Applicable Initializations
*******************************************************************************/

/*******************************************************************************
*   Function Declarations
*******************************************************************************/

    /// @brief Initialize synthesizer hardware components.
    /// @return none
    void synth_hw_init(void);

    /// @brief Generate speech audio based on LPC encoded bitstream.
    /// @param p_lpc_data Pointer to LPC encoded bitstream data.
    /// @return none
    void synth_say(const uint8_t* p_lpc_data);

    #ifdef FRAM_AVAILABLE
        /// @brief Generate speech audio based on LPC encoded bitstream in FRAM.
        /// @param fram_addr LPC encoded bitstream data address in FRAM.
        /// @return none
        void synth_say_fram(uint32_t fram_addr);
    #endif

    #ifndef DMA_AVAILABLE
        /// @brief Synth ISR prototype.
        /// @param synth_isr ISR name.
        /// @return none
        CY_ISR_PROTO(synth_isr);
    #endif

#endif

/* [] END OF FILE */
