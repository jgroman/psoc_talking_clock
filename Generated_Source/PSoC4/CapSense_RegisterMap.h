/***************************************************************************//**
* \file CapSense_RegisterMap.h
* \version 3.10
*
* \brief
*   This file provides the definitions for the component data structure register.
*
* \see CapSense P4 v3.10 Datasheet
*
*//*****************************************************************************
* Copyright (2016), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CapSense_REGISTER_MAP_H)
#define CY_CAPSENSE_CapSense_REGISTER_MAP_H

#include <cytypes.h>
#include "CapSense_Configuration.h"
#include "CapSense_Structure.h"

/*****************************************************************************/
/* RAM Data structure register definitions                                   */
/*****************************************************************************/
#define CapSense_CONFIG_ID_VALUE                            (CapSense_dsRam.configId)
#define CapSense_CONFIG_ID_OFFSET                           (0u)
#define CapSense_CONFIG_ID_SIZE                             (2u)
#define CapSense_CONFIG_ID_PARAM_ID                         (0x87000000u)

#define CapSense_DEVICE_ID_VALUE                            (CapSense_dsRam.deviceId)
#define CapSense_DEVICE_ID_OFFSET                           (2u)
#define CapSense_DEVICE_ID_SIZE                             (2u)
#define CapSense_DEVICE_ID_PARAM_ID                         (0x8B000002u)

#define CapSense_TUNER_CMD_VALUE                            (CapSense_dsRam.tunerCmd)
#define CapSense_TUNER_CMD_OFFSET                           (4u)
#define CapSense_TUNER_CMD_SIZE                             (2u)
#define CapSense_TUNER_CMD_PARAM_ID                         (0xAD000004u)

#define CapSense_SCAN_COUNTER_VALUE                         (CapSense_dsRam.scanCounter)
#define CapSense_SCAN_COUNTER_OFFSET                        (6u)
#define CapSense_SCAN_COUNTER_SIZE                          (2u)
#define CapSense_SCAN_COUNTER_PARAM_ID                      (0x8A000006u)

#define CapSense_STATUS_VALUE                               (CapSense_dsRam.status)
#define CapSense_STATUS_OFFSET                              (8u)
#define CapSense_STATUS_SIZE                                (4u)
#define CapSense_STATUS_PARAM_ID                            (0xCA000008u)

#define CapSense_WDGT_ENABLE0_VALUE                         (CapSense_dsRam.wdgtEnable[0u])
#define CapSense_WDGT_ENABLE0_OFFSET                        (12u)
#define CapSense_WDGT_ENABLE0_SIZE                          (4u)
#define CapSense_WDGT_ENABLE0_PARAM_ID                      (0xE000000Cu)

#define CapSense_WDGT_STATUS0_VALUE                         (CapSense_dsRam.wdgtStatus[0u])
#define CapSense_WDGT_STATUS0_OFFSET                        (16u)
#define CapSense_WDGT_STATUS0_SIZE                          (4u)
#define CapSense_WDGT_STATUS0_PARAM_ID                      (0xCD000010u)

#define CapSense_SNS_STATUS0_VALUE                          (CapSense_dsRam.snsStatus[0u])
#define CapSense_SNS_STATUS0_OFFSET                         (20u)
#define CapSense_SNS_STATUS0_SIZE                           (1u)
#define CapSense_SNS_STATUS0_PARAM_ID                       (0x4B000014u)

#define CapSense_CSD0_CONFIG_VALUE                          (CapSense_dsRam.csd0Config)
#define CapSense_CSD0_CONFIG_OFFSET                         (22u)
#define CapSense_CSD0_CONFIG_SIZE                           (2u)
#define CapSense_CSD0_CONFIG_PARAM_ID                       (0xA9800016u)

#define CapSense_MOD_CSD_CLK_VALUE                          (CapSense_dsRam.modCsdClk)
#define CapSense_MOD_CSD_CLK_OFFSET                         (24u)
#define CapSense_MOD_CSD_CLK_SIZE                           (1u)
#define CapSense_MOD_CSD_CLK_PARAM_ID                       (0x6E800018u)

#define CapSense_PROXIMITY0_RESOLUTION_VALUE                (CapSense_dsRam.wdgtList.proximity0.resolution)
#define CapSense_PROXIMITY0_RESOLUTION_OFFSET               (26u)
#define CapSense_PROXIMITY0_RESOLUTION_SIZE                 (2u)
#define CapSense_PROXIMITY0_RESOLUTION_PARAM_ID             (0x8180001Au)

#define CapSense_PROXIMITY0_FINGER_TH_VALUE                 (CapSense_dsRam.wdgtList.proximity0.fingerTh)
#define CapSense_PROXIMITY0_FINGER_TH_OFFSET                (28u)
#define CapSense_PROXIMITY0_FINGER_TH_SIZE                  (2u)
#define CapSense_PROXIMITY0_FINGER_TH_PARAM_ID              (0x8C80001Cu)

#define CapSense_PROXIMITY0_NOISE_TH_VALUE                  (CapSense_dsRam.wdgtList.proximity0.noiseTh)
#define CapSense_PROXIMITY0_NOISE_TH_OFFSET                 (30u)
#define CapSense_PROXIMITY0_NOISE_TH_SIZE                   (1u)
#define CapSense_PROXIMITY0_NOISE_TH_PARAM_ID               (0x4880001Eu)

#define CapSense_PROXIMITY0_NNOISE_TH_VALUE                 (CapSense_dsRam.wdgtList.proximity0.nNoiseTh)
#define CapSense_PROXIMITY0_NNOISE_TH_OFFSET                (31u)
#define CapSense_PROXIMITY0_NNOISE_TH_SIZE                  (1u)
#define CapSense_PROXIMITY0_NNOISE_TH_PARAM_ID              (0x4E80001Fu)

#define CapSense_PROXIMITY0_HYSTERESIS_VALUE                (CapSense_dsRam.wdgtList.proximity0.hysteresis)
#define CapSense_PROXIMITY0_HYSTERESIS_OFFSET               (32u)
#define CapSense_PROXIMITY0_HYSTERESIS_SIZE                 (1u)
#define CapSense_PROXIMITY0_HYSTERESIS_PARAM_ID             (0x48800020u)

#define CapSense_PROXIMITY0_ON_DEBOUNCE_VALUE               (CapSense_dsRam.wdgtList.proximity0.onDebounce)
#define CapSense_PROXIMITY0_ON_DEBOUNCE_OFFSET              (33u)
#define CapSense_PROXIMITY0_ON_DEBOUNCE_SIZE                (1u)
#define CapSense_PROXIMITY0_ON_DEBOUNCE_PARAM_ID            (0x4E800021u)

#define CapSense_PROXIMITY0_LOW_BSLN_RST_VALUE              (CapSense_dsRam.wdgtList.proximity0.lowBslnRst)
#define CapSense_PROXIMITY0_LOW_BSLN_RST_OFFSET             (34u)
#define CapSense_PROXIMITY0_LOW_BSLN_RST_SIZE               (1u)
#define CapSense_PROXIMITY0_LOW_BSLN_RST_PARAM_ID           (0x44800022u)

#define CapSense_PROXIMITY0_BSLN_COEFF_VALUE                (CapSense_dsRam.wdgtList.proximity0.bslnCoeff)
#define CapSense_PROXIMITY0_BSLN_COEFF_OFFSET               (35u)
#define CapSense_PROXIMITY0_BSLN_COEFF_SIZE                 (1u)
#define CapSense_PROXIMITY0_BSLN_COEFF_PARAM_ID             (0x69800023u)

#define CapSense_PROXIMITY0_IDAC_MOD0_VALUE                 (CapSense_dsRam.wdgtList.proximity0.idacMod[0u])
#define CapSense_PROXIMITY0_IDAC_MOD0_OFFSET                (36u)
#define CapSense_PROXIMITY0_IDAC_MOD0_SIZE                  (1u)
#define CapSense_PROXIMITY0_IDAC_MOD0_PARAM_ID              (0x44000024u)

#define CapSense_PROXIMITY0_SNS_CLK_VALUE                   (CapSense_dsRam.wdgtList.proximity0.snsClk)
#define CapSense_PROXIMITY0_SNS_CLK_OFFSET                  (37u)
#define CapSense_PROXIMITY0_SNS_CLK_SIZE                    (1u)
#define CapSense_PROXIMITY0_SNS_CLK_PARAM_ID                (0x4F800025u)

#define CapSense_PROXIMITY0_SNS_CLK_SOURCE_VALUE            (CapSense_dsRam.wdgtList.proximity0.snsClkSource)
#define CapSense_PROXIMITY0_SNS_CLK_SOURCE_OFFSET           (38u)
#define CapSense_PROXIMITY0_SNS_CLK_SOURCE_SIZE             (1u)
#define CapSense_PROXIMITY0_SNS_CLK_SOURCE_PARAM_ID         (0x45800026u)

#define CapSense_PROXIMITY0_FINGER_CAP_VALUE                (CapSense_dsRam.wdgtList.proximity0.fingerCap)
#define CapSense_PROXIMITY0_FINGER_CAP_OFFSET               (40u)
#define CapSense_PROXIMITY0_FINGER_CAP_SIZE                 (2u)
#define CapSense_PROXIMITY0_FINGER_CAP_PARAM_ID             (0xA4000028u)

#define CapSense_PROXIMITY0_SIGPFC_VALUE                    (CapSense_dsRam.wdgtList.proximity0.sigPFC)
#define CapSense_PROXIMITY0_SIGPFC_OFFSET                   (42u)
#define CapSense_PROXIMITY0_SIGPFC_SIZE                     (2u)
#define CapSense_PROXIMITY0_SIGPFC_PARAM_ID                 (0xA800002Au)

#define CapSense_PROXIMITY0_PROX_TOUCH_TH_VALUE             (CapSense_dsRam.wdgtList.proximity0.proxTouchTh)
#define CapSense_PROXIMITY0_PROX_TOUCH_TH_OFFSET            (44u)
#define CapSense_PROXIMITY0_PROX_TOUCH_TH_SIZE              (2u)
#define CapSense_PROXIMITY0_PROX_TOUCH_TH_PARAM_ID          (0xA500002Cu)

#define CapSense_PROXIMITY0_SNS0_RAW0_VALUE                 (CapSense_dsRam.snsList.proximity0[0u].raw[0u])
#define CapSense_PROXIMITY0_SNS0_RAW0_OFFSET                (46u)
#define CapSense_PROXIMITY0_SNS0_RAW0_SIZE                  (2u)
#define CapSense_PROXIMITY0_SNS0_RAW0_PARAM_ID              (0x8200002Eu)

#define CapSense_PROXIMITY0_SNS0_BSLN0_VALUE                (CapSense_dsRam.snsList.proximity0[0u].bsln[0u])
#define CapSense_PROXIMITY0_SNS0_BSLN0_OFFSET               (48u)
#define CapSense_PROXIMITY0_SNS0_BSLN0_SIZE                 (2u)
#define CapSense_PROXIMITY0_SNS0_BSLN0_PARAM_ID             (0x88000030u)

#define CapSense_PROXIMITY0_SNS0_BSLN_EXT0_VALUE            (CapSense_dsRam.snsList.proximity0[0u].bslnExt[0u])
#define CapSense_PROXIMITY0_SNS0_BSLN_EXT0_OFFSET           (50u)
#define CapSense_PROXIMITY0_SNS0_BSLN_EXT0_SIZE             (1u)
#define CapSense_PROXIMITY0_SNS0_BSLN_EXT0_PARAM_ID         (0x4C000032u)

#define CapSense_PROXIMITY0_SNS0_DIFF_VALUE                 (CapSense_dsRam.snsList.proximity0[0u].diff)
#define CapSense_PROXIMITY0_SNS0_DIFF_OFFSET                (52u)
#define CapSense_PROXIMITY0_SNS0_DIFF_SIZE                  (2u)
#define CapSense_PROXIMITY0_SNS0_DIFF_PARAM_ID              (0x89000034u)

#define CapSense_PROXIMITY0_SNS0_NEG_BSLN_RST_CNT0_VALUE    (CapSense_dsRam.snsList.proximity0[0u].negBslnRstCnt[0u])
#define CapSense_PROXIMITY0_SNS0_NEG_BSLN_RST_CNT0_OFFSET   (54u)
#define CapSense_PROXIMITY0_SNS0_NEG_BSLN_RST_CNT0_SIZE     (1u)
#define CapSense_PROXIMITY0_SNS0_NEG_BSLN_RST_CNT0_PARAM_ID (0x4D000036u)

#define CapSense_PROXIMITY0_SNS0_IDAC_COMP0_VALUE           (CapSense_dsRam.snsList.proximity0[0u].idacComp[0u])
#define CapSense_PROXIMITY0_SNS0_IDAC_COMP0_OFFSET          (55u)
#define CapSense_PROXIMITY0_SNS0_IDAC_COMP0_SIZE            (1u)
#define CapSense_PROXIMITY0_SNS0_IDAC_COMP0_PARAM_ID        (0x4B000037u)

#define CapSense_SNR_TEST_WIDGET_ID_VALUE                   (CapSense_dsRam.snrTestWidgetId)
#define CapSense_SNR_TEST_WIDGET_ID_OFFSET                  (56u)
#define CapSense_SNR_TEST_WIDGET_ID_SIZE                    (1u)
#define CapSense_SNR_TEST_WIDGET_ID_PARAM_ID                (0x69000038u)

#define CapSense_SNR_TEST_SENSOR_ID_VALUE                   (CapSense_dsRam.snrTestSensorId)
#define CapSense_SNR_TEST_SENSOR_ID_OFFSET                  (57u)
#define CapSense_SNR_TEST_SENSOR_ID_SIZE                    (1u)
#define CapSense_SNR_TEST_SENSOR_ID_PARAM_ID                (0x6F000039u)

#define CapSense_SNR_TEST_SCAN_COUNTER_VALUE                (CapSense_dsRam.snrTestScanCounter)
#define CapSense_SNR_TEST_SCAN_COUNTER_OFFSET               (58u)
#define CapSense_SNR_TEST_SCAN_COUNTER_SIZE                 (2u)
#define CapSense_SNR_TEST_SCAN_COUNTER_PARAM_ID             (0x8600003Au)

#define CapSense_SNR_TEST_RAW_COUNT0_VALUE                  (CapSense_dsRam.snrTestRawCount[0u])
#define CapSense_SNR_TEST_RAW_COUNT0_OFFSET                 (60u)
#define CapSense_SNR_TEST_RAW_COUNT0_SIZE                   (2u)
#define CapSense_SNR_TEST_RAW_COUNT0_PARAM_ID               (0x8B00003Cu)


/*****************************************************************************/
/* Flash Data structure register definitions                                 */
/*****************************************************************************/
#define CapSense_PROXIMITY0_PTR2SNS_FLASH_VALUE             (CapSense_dsFlash.wdgtArray[0].ptr2SnsFlash)
#define CapSense_PROXIMITY0_PTR2SNS_FLASH_OFFSET            (0u)
#define CapSense_PROXIMITY0_PTR2SNS_FLASH_SIZE              (4u)
#define CapSense_PROXIMITY0_PTR2SNS_FLASH_PARAM_ID          (0xD1000000u)

#define CapSense_PROXIMITY0_PTR2WD_RAM_VALUE                (CapSense_dsFlash.wdgtArray[0].ptr2WdgtRam)
#define CapSense_PROXIMITY0_PTR2WD_RAM_OFFSET               (4u)
#define CapSense_PROXIMITY0_PTR2WD_RAM_SIZE                 (4u)
#define CapSense_PROXIMITY0_PTR2WD_RAM_PARAM_ID             (0xD0000004u)

#define CapSense_PROXIMITY0_PTR2SNS_RAM_VALUE               (CapSense_dsFlash.wdgtArray[0].ptr2SnsRam)
#define CapSense_PROXIMITY0_PTR2SNS_RAM_OFFSET              (8u)
#define CapSense_PROXIMITY0_PTR2SNS_RAM_SIZE                (4u)
#define CapSense_PROXIMITY0_PTR2SNS_RAM_PARAM_ID            (0xD3000008u)

#define CapSense_PROXIMITY0_PTR2FLTR_HISTORY_VALUE          (CapSense_dsFlash.wdgtArray[0].ptr2FltrHistory)
#define CapSense_PROXIMITY0_PTR2FLTR_HISTORY_OFFSET         (12u)
#define CapSense_PROXIMITY0_PTR2FLTR_HISTORY_SIZE           (4u)
#define CapSense_PROXIMITY0_PTR2FLTR_HISTORY_PARAM_ID       (0xD200000Cu)

#define CapSense_PROXIMITY0_PTR2DEBOUNCE_VALUE              (CapSense_dsFlash.wdgtArray[0].ptr2DebounceArr)
#define CapSense_PROXIMITY0_PTR2DEBOUNCE_OFFSET             (16u)
#define CapSense_PROXIMITY0_PTR2DEBOUNCE_SIZE               (4u)
#define CapSense_PROXIMITY0_PTR2DEBOUNCE_PARAM_ID           (0xD4000010u)

#define CapSense_PROXIMITY0_STATIC_CONFIG_VALUE             (CapSense_dsFlash.wdgtArray[0].staticConfig)
#define CapSense_PROXIMITY0_STATIC_CONFIG_OFFSET            (20u)
#define CapSense_PROXIMITY0_STATIC_CONFIG_SIZE              (2u)
#define CapSense_PROXIMITY0_STATIC_CONFIG_PARAM_ID          (0x9A000014u)

#define CapSense_PROXIMITY0_TOTAL_NUM_SNS_VALUE             (CapSense_dsFlash.wdgtArray[0].totalNumSns)
#define CapSense_PROXIMITY0_TOTAL_NUM_SNS_OFFSET            (22u)
#define CapSense_PROXIMITY0_TOTAL_NUM_SNS_SIZE              (2u)
#define CapSense_PROXIMITY0_TOTAL_NUM_SNS_PARAM_ID          (0x96000016u)

#define CapSense_PROXIMITY0_TYPE_VALUE                      (CapSense_dsFlash.wdgtArray[0].wdgtType)
#define CapSense_PROXIMITY0_TYPE_OFFSET                     (24u)
#define CapSense_PROXIMITY0_TYPE_SIZE                       (1u)
#define CapSense_PROXIMITY0_TYPE_PARAM_ID                   (0x51000018u)

#define CapSense_PROXIMITY0_NUM_COLS_VALUE                  (CapSense_dsFlash.wdgtArray[0].numCols)
#define CapSense_PROXIMITY0_NUM_COLS_OFFSET                 (25u)
#define CapSense_PROXIMITY0_NUM_COLS_SIZE                   (1u)
#define CapSense_PROXIMITY0_NUM_COLS_PARAM_ID               (0x57000019u)

#define CapSense_PROXIMITY0_PTR2NOISE_ENVLP_VALUE           (CapSense_dsFlash.wdgtArray[0].ptr2NoiseEnvlp)
#define CapSense_PROXIMITY0_PTR2NOISE_ENVLP_OFFSET          (28u)
#define CapSense_PROXIMITY0_PTR2NOISE_ENVLP_SIZE            (4u)
#define CapSense_PROXIMITY0_PTR2NOISE_ENVLP_PARAM_ID        (0xD700001Cu)


#endif /* End CY_CAPSENSE_CapSense_REGISTER_MAP_H */

/* [] END OF FILE */
