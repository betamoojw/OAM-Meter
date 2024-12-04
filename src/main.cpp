#include "FileTransferModule.h"
#include "GpioBinaryInputModule.h"
#include "Logic.h"
#include "MeterModule.h"
#include "OpenKNX.h"
#include "SMLModule.h"
#include "UsbExchangeModule.h"
#include "VirtualButtonModule.h"
#include <SoftwareSerial.h>

#ifdef SML_TEST_STRINGS
    #include "SMLSamples.h"
#endif

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxMeterModule);
    openknx.addModule(3, openknxSMLModule);
#if defined(OPENKNX_BI_GPIO_PINS) && OPENKNX_BI_GPIO_COUNT > 0 && BI_ChannelCount > 0
    openknx.addModule(6, openknxGpioBinaryInputModule);
#endif
    openknx.addModule(7, openknxVirtualButtonModule);
    openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(9, openknxFileTransferModule);

    openknx.setup();

#if defined(INFO3_LED_PIN)
    openknx.info3Led.activity(openknxSMLModule.lastReceived);
#elif defined(INFO1_LED_PIN)
    openknx.info1Led.activity(openknxSMLModule.lastReceived);
#endif

#if defined(DEVICE_PIPICO_BCU_CONNECTOR)

    pinMode(8, OUTPUT);
    digitalWrite(8, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(SerialPIO::NOPIN, 9, 64U));

    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    openknxSMLModule.getChannel(1)->setSerial(new SerialPIO(SerialPIO::NOPIN, 11, 64U));

    pinMode(26, OUTPUT);
    digitalWrite(26, HIGH);
    openknxSMLModule.getChannel(2)->setSerial(new SerialPIO(SerialPIO::NOPIN, 27, 64U));

#elif defined(DEVICE_REG1_BASE_V0) || defined(DEVICE_REG1_BASE) || defined(DEVICE_REG1_SEN_MULTI)

    pinMode(OKNXHW_REG1_SENSOR_SDA_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG1_SENSOR_SDA_TX_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(SerialPIO::NOPIN, 9, 64U)); // Onboard

    #ifdef DEVICE_REG1_SEN_MULTI
    pinMode(OKNXHW_REG1_APP_SEN_MULTI_SENSOR1_SDA_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG1_APP_SEN_MULTI_SENSOR1_SDA_TX_PIN, HIGH);
    openknxSMLModule.getChannel(1)->setSerial(new SerialPIO(SerialPIO::NOPIN, OKNXHW_REG1_APP_SEN_MULTI_SENSOR1_SCL_RX_PIN, 64U)); // SML Platine A (oben)

    pinMode(OKNXHW_REG1_APP_SEN_MULTI_SENSOR2_SDA_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG1_APP_SEN_MULTI_SENSOR2_SDA_TX_PIN, HIGH);
    openknxSMLModule.getChannel(2)->setSerial(new SerialPIO(SerialPIO::NOPIN, OKNXHW_REG1_APP_SEN_MULTI_SENSOR2_SCL_RX_PIN, 64U)); // SML Platine B (unten)
    #endif

#elif defined(OKNXHW_REG2_PIPICO_V1_BASE)

    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(SerialPIO::NOPIN, 5, 64U));

    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(SerialPIO::NOPIN, 7, 64U));

#elif defined(DEVICE_SMARTMF_1TE_BE_3CH)

    pinMode(SMARTMF_BE_VCC_PIN, OUTPUT);
    digitalWrite(SMARTMF_BE_VCC_PIN, HIGH);

#elif defined(DEVICE_SMARTMF_2SML_3BE)

    pinMode(SMARTMF_SML1_TX_PIN, OUTPUT);
    pinMode(SMARTMF_SML2_TX_PIN, OUTPUT);
    digitalWrite(SMARTMF_SML1_TX_PIN, HIGH);
    digitalWrite(SMARTMF_SML2_TX_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(SerialPIO::NOPIN, SMARTMF_SML1_RX_PIN, 64U));
    openknxSMLModule.getChannel(1)->setSerial(new SerialPIO(SerialPIO::NOPIN, SMARTMF_SML2_RX_PIN, 64U));

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