#pragma once

/************************************************
 *
 * Sensor Breakout
 *
 */
#ifdef SMARTMF_SENSOR_BREAKOUT
    #define PROG_LED_PIN 1
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
    #define SAVE_INTERRUPT_PIN 22
    #define INFO_LED_PIN 38
    #define INFO_LED_PIN_ACTIVE_ON HIGH
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define KNX_I2C_SDA_PIN 20
    #define KNX_I2C_SCL_PIN 21
    #define HARDWARE_NAME "SMARTMF-SESNOR-BREAKOUT"

    #define BUZZER_PIN 9
    #define I2C_RGBLED_DEVICE_ADDRESS 0x60 // Address of PCA9632 RBGW-LED-Driver
    #define SMARTMF_HARDWARE_VARIANT_PIN 26
    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 10
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 11
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 12

    #define PLAYER_UART_RX_PIN 9
    #define PLAYER_UART_TX_PIN 8
    #define PLAYER_I2S_BCLK_PIN 8
    #define PLAYER_I2S_DATA_PIN 20

    #define SMARTMF_BE_VCC_PIN 5
    #define SMARTMF_BE1_PIN 2
    #define SMARTMF_BE2_PIN 4
    #define SMARTMF_BE3_PIN 6
    #define SMARTMF_BE4_PIN 7

    #define OPENKNX_BI_PULSE_PAUSE_TIME 5  // MS
    #define OPENKNX_BI_PULSE_WAIT_TIME 250 // US

    #define OPENKNX_BI_GPIO_PINS SMARTMF_BE1_PIN, SMARTMF_BE2_PIN, SMARTMF_BE3_PIN, SMARTMF_BE4_PIN
    #define OPENKNX_BI_GPIO_COUNT 4
#endif

#ifdef SMARTMF_SOM_UP
    #define PROG_LED_PIN 2
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define INFO1_LED_PIN 29
    #define INFO1_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define FUNC1_BUTTON_PIN 1
    #define SAVE_INTERRUPT_PIN 13
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #define PLAYER_UART_RX_PIN 9
    #define PLAYER_UART_TX_PIN 8
    #define PLAYER_I2S_BCLK_PIN 8
    #define PLAYER_I2S_DATA_PIN 20
    #define PLAYER_POWER_PIN 3
    #define HARDWARE_NAME "SMARTMF-SOM-UP"

    #define SMARTMF_HARDWARE_VARIANT_PIN 26
    #define SMARTMF_HARDWARE_REVISION_ID1_PIN 10
    #define SMARTMF_HARDWARE_REVISION_ID2_PIN 11
    #define SMARTMF_HARDWARE_REVISION_ID3_PIN 12

    #define SMARTMF_BE_VCC_PIN 14
    #define SMARTMF_BE1_PIN 4
    #define SMARTMF_BE2_PIN 5
    #define SMARTMF_BE3_PIN 19
    #define SMARTMF_BE4_PIN 18

    #define OPENKNX_BI_GPIO_PINS SMARTMF_BE1_PIN, SMARTMF_BE2_PIN, SMARTMF_BE3_PIN, SMARTMF_BE4_PIN
    #define OPENKNX_BI_GPIO_COUNT 4
    #define OPENKNX_BI_PULSE SMARTMF_BE_VCC_PIN
#endif

/************************************************
 *
 * 1TE RP2040
 *
 */

// BE3
#ifdef SMARTMF_1TE_BE3
    #define SMARTMF_1TE_BASE
    #define HARDWARE_NAME "SMARTMF-1TE-BE3"

    #define SMARTMF_BE_VCC_PIN 5
    #define SMARTMF_BE1_PIN 14
    #define SMARTMF_BE2_PIN 15
    #define SMARTMF_BE3_PIN 4

    #define OPENKNX_BI_GPIO_PINS SMARTMF_BE1_PIN, SMARTMF_BE2_PIN, SMARTMF_BE3_PIN
    #define OPENKNX_BI_GPIO_COUNT 3
#endif

// 1WIRE - TODO
#ifdef SMARTMF_1TE_1WIRE
    #define SMARTMF_1TE_BASE
    #define HARDWARE_NAME "SMARTMF-1TE-1WIRE"

    #define SMARTMF_BE_VCC_PIN 5
    #define SMARTMF_BE1_PIN 14
    #define SMARTMF_BE2_PIN 15
    #define SMARTMF_BE3_PIN 4
#endif

// BASE
#ifdef SMARTMF_1TE_BASE
    #define PROG_LED_PIN 1
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 0
    #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
    #define SAVE_INTERRUPT_PIN 29
    #define KNX_UART_RX_PIN 17
    #define KNX_UART_TX_PIN 16
    #ifndef HARDWARE_NAME
        #define HARDWARE_NAME "SMARTMF-1TE"
    #endif
#endif

/************************************************
 *
 *  2TE RP2040
 *
 */

// BE2-SML2
#ifdef SMARTMF_2TE_BE2_SML2
    #define SMARTMF_2TE_BASE
    #define HARDWARE_NAME "SMARTMF-2TE-BE2-SML2"

    #define SMARTMF_BE1_PIN 26
    #define SMARTMF_BE2_PIN 27
    #define SMARTMF_SML1_RX_PIN 5
    #define SMARTMF_SML1_TX_PIN 6
    #define SMARTMF_SML2_RX_PIN 22
    #define SMARTMF_SML2_TX_PIN 23

    #define OPENKNX_BI_GPIO_PINS SMARTMF_BE1_PIN, SMARTMF_BE2_PIN
    #define OPENKNX_BI_GPIO_COUNT 2
#endif

// BASE
#ifdef SMARTMF_2TE_BASE
    #define PROG_LED_PIN 11
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 14
    #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
    #define SAVE_INTERRUPT_PIN 8
    #define KNX_UART_RX_PIN 1
    #define KNX_UART_TX_PIN 0
    #ifndef HARDWARE_NAME
        #define HARDWARE_NAME "SMARTMF-2TE"
    #endif
#endif

/*****************
 *
 * Backward compatibility
 *
 */
#ifdef SMARTMF_HARDWARE_VARIANT_PIN
    #define SmartMF_HardwareVariant_PIN SMARTMF_HARDWARE_VARIANT_PIN
#endif

#ifdef SMARTMF_HARDWARE_REVISION_ID1_PIN
    #define SmartMF_HardwareRevision_PIN1 SMARTMF_HARDWARE_REVISION_ID1_PIN
#endif

#ifdef SMARTMF_HARDWARE_REVISION_ID2_PIN
    #define SmartMF_HardwareRevision_PIN2 SMARTMF_HARDWARE_REVISION_ID2_PIN
#endif

#ifdef SMARTMF_HARDWARE_REVISION_ID3_PIN
    #define SmartMF_HardwareRevision_PIN3 SMARTMF_HARDWARE_REVISION_ID3_PIN
#endif
