
#include "GpioBinaryInputModule.h"
#include "Logic.h"
#include "MeterModule.h"
#include "NetworkModule.h"
#include "OpenKNX.h"
#include "UsbExchangeModule.h"
#include "VirtualButtonModule.h"
#ifndef OPENKNX_FILE_TRANSFER_IGNORE
    #include "FileTransferModule.h"
#endif
#ifndef ARDUINO_ARCH_ESP32
    #include "SMLModule.h"
    #include <SoftwareSerial.h>
#endif

#ifdef SML_TEST_STRINGS
    #include "SMLSamples.h"
#endif

#define PIO_BUFFER 64U

void setup()
{
    openknx.init();
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxMeterModule);
#ifndef ARDUINO_ARCH_ESP32
    openknx.addModule(3, openknxSMLModule);
#endif
#if defined(OPENKNX_BI_GPIO_PINS) && OPENKNX_BI_GPIO_COUNT > 0 && BI_ChannelCount > 0
    openknx.addModule(6, openknxGpioBinaryInputModule);
#endif
#if MASK_VERSION == 0x57B0
    openknx.addModule(10, openknxNetwork);
#endif
    openknx.addModule(7, openknxVirtualButtonModule);

#ifndef ARDUINO_ARCH_ESP32
    openknx.addModule(8, openknxUsbExchangeModule);
#endif
#ifndef OPENKNX_FILE_TRANSFER_IGNORE
    openknx.addModule(9, openknxFileTransferModule);
#endif

    openknx.setup();

#if defined(INFO3_LED_PIN)
//    openknx.info3Led.activity(openknxSMLModule.lastReceived);
#elif defined(INFO1_LED_PIN)
    openknx.info1Led.activity(openknxSMLModule.lastReceived);
#endif

#if defined(DEVICE_PIPICO_BCU_CONNECTOR)

    pinMode(8, OUTPUT);
    digitalWrite(8, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(NOPIN, 9, PIO_BUFFER));

    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    openknxSMLModule.getChannel(1)->setSerial(new SerialPIO(NOPIN, 11, PIO_BUFFER));

    pinMode(26, OUTPUT);
    digitalWrite(26, HIGH);
    openknxSMLModule.getChannel(2)->setSerial(new SerialPIO(NOPIN, 27, PIO_BUFFER));

#elif defined(DEVICE_REG1_BASE_V0) || defined(DEVICE_REG1_BASE)

    pinMode(OKNXHW_REG1_SENSOR_SDA_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG1_SENSOR_SDA_TX_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(NOPIN, 9, PIO_BUFFER)); // Onboard

#elif defined(DEVICE_REG1_SEN_MULTI)

    pinMode(OKNXHW_REG1_APP_SEN_MULTI_SENSOR1_SDA_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG1_APP_SEN_MULTI_SENSOR1_SDA_TX_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(NOPIN, OKNXHW_REG1_APP_SEN_MULTI_SENSOR1_SCL_RX_PIN, PIO_BUFFER)); // SML Platine A (oben)

    pinMode(OKNXHW_REG1_APP_SEN_MULTI_SENSOR2_SDA_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG1_APP_SEN_MULTI_SENSOR2_SDA_TX_PIN, HIGH);
    openknxSMLModule.getChannel(1)->setSerial(new SerialPIO(NOPIN, OKNXHW_REG1_APP_SEN_MULTI_SENSOR2_SCL_RX_PIN, PIO_BUFFER)); // SML Platine B (unten)

    pinMode(OKNXHW_REG1_SENSOR_SDA_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG1_SENSOR_SDA_TX_PIN, HIGH);
    openknxSMLModule.getChannel(2)->setSerial(new SerialPIO(NOPIN, 9, PIO_BUFFER)); // Onboard

#elif defined(DEVICE_SMARTMF_1TE_BE_3CH)

    pinMode(SMARTMF_BE_VCC_PIN, OUTPUT);
    digitalWrite(SMARTMF_BE_VCC_PIN, HIGH);

#elif defined(DEVICE_SMARTMF_2SML_3BE)

    pinMode(SMARTMF_SML_PWR_PIN, OUTPUT);
    digitalWrite(SMARTMF_SML_PWR_PIN, HIGH);

    pinMode(SMARTMF_SML1_TX_PIN, OUTPUT);
    digitalWrite(SMARTMF_SML1_TX_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(NOPIN, SMARTMF_SML1_RX_PIN, PIO_BUFFER));

    pinMode(SMARTMF_SML2_TX_PIN, OUTPUT);
    digitalWrite(SMARTMF_SML2_TX_PIN, HIGH);
    openknxSMLModule.getChannel(1)->setSerial(new SerialPIO(NOPIN, SMARTMF_SML2_RX_PIN, PIO_BUFFER));

#elif defined(DEVICE_REG2_PIPICO_V1_DD_METER)

    pinMode(OKNXHW_REG2_MSENS_1_SDA0_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG2_MSENS_1_SDA0_TX_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(NOPIN, OKNXHW_REG2_MSENS_1_SCL0_RX_PIN, PIO_BUFFER));

    pinMode(OKNXHW_REG2_MSENS_2_SDA1_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG2_MSENS_2_SDA1_TX_PIN, HIGH);
    openknxSMLModule.getChannel(1)->setSerial(new SerialPIO(NOPIN, OKNXHW_REG2_MSENS_2_SCL1_RX_PIN, PIO_BUFFER));

#endif
}

uint32_t _debugCore0 = 0;
uint32_t _debugCore1 = 0;

void loop()
{
    openknx.loop();
    if (delayCheck(_debugCore0, 1000))
    {
#ifndef OPENKNX_DUALCORE
    #ifdef SML_TEST_STRINGS
        for (int i = 0; i < sizeof(smlResponse1); i++)
        {
            openknxSMLModule.getChannel(0)->writeBuffer(smlResponse1[i]);
        }
    #endif
#endif
        _debugCore0 = millis();
    }
}

#ifdef OPENKNX_DUALCORE
void setup1()
{
    openknx.setup1();
}

void loop1()
{
    openknx.loop1();

    if (delayCheck(_debugCore1, 5000))
    {
    #ifdef SML_TEST_STRINGS
        for (int i = 0; i < sizeof(smlResponse1); i++)
        {
            openknxSMLModule.getChannel(0)->writeBuffer(smlResponse1[i]);
        }
    #endif
        _debugCore1 = millis();
    }
}
#endif