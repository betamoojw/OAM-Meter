#include "OpenKNX.h"

#include "GpioBinaryInputModule.h"
#include "Logic.h"
#include "MeterModule.h"
#include "NetworkModule.h"
#ifdef WMBUS_SPI
    #include "MBusModule.h"
#endif
#include "UsbExchangeModule.h"
#include "VirtualButtonModule.h"
#ifndef OPENKNX_FILE_TRANSFER_IGNORE
    #include "FileTransferModule.h"
#endif
#if defined(KNX_IP_LAN) || defined(KNX_IP_WIFI)
    #include "NetworkModule.h"
#endif
#include "SMLModule.h"

#ifdef SML_TEST_STRINGS
    #include "SMLSamples.h"
#endif

#define PIO_BUFFER 64U

void setup()
{
    openknx.init();

    // Muss vor openknx.setup() erfolgen: setzt ein Modul in seinem setup() die LED
    // seiner Function-ID, bevor ihr hier eine physische LED zugewiesen wurde, läuft
    // das ins Leere und die LED bleibt bis zur nächsten Statusänderung aus.
    if (openknx.ledFunctions.useDefaultFunction())
    {
#if defined(DEVICE_REG1_BASE_V0) || defined(DEVICE_REG1_BASE) || defined(DEVICE_REG1_SEN_MULTI) || defined(DEVICE_REG1_LAN_SEN_MULTI)
        openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO3), 200); // SML Gesamtstatus
        openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_INFO2), 600); // BI Status
#endif
    }

#if defined(DEVICE_SMARTMF_2SML_3BE)
    openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_USER + 1), 701); // BE1
    openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_USER + 2), 702); // BE2
    openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_USER + 3), 703); // BE3
    openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_USER + 4), 202); // SML02!
    openknx.ledFunctions.assignLed2Function(openknx.leds.getLed(OpenKNX::Led::LED_TYPE_USER + 5), 201); // SML01!
#endif

    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxMeterModule);
    openknx.addModule(3, openknxSMLModule);

#if defined(OPENKNX_BI_GPIO_PINS) && OPENKNX_BI_GPIO_COUNT > 0 && BI_ChannelCount > 0
    openknx.addModule(6, openknxGpioBinaryInputModule);
#endif
#if defined(KNX_IP_LAN) || defined(KNX_IP_WIFI)
    openknx.addModule(10, openknxNetwork);
#endif
    openknx.addModule(7, openknxVirtualButtonModule);
#ifdef WMBUS_SPI
    openknx.addModule(10, openknxMBusModule);
#endif

#ifndef ARDUINO_ARCH_ESP32
    openknx.addModule(8, openknxUsbExchangeModule);
#endif
#ifndef OPENKNX_FILE_TRANSFER_IGNORE
    openknx.addModule(9, openknxFileTransferModule);
#endif

    openknx.setup();

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

#elif defined(DEVICE_SEN_UP1_8XTH)

    pinMode(OKNXHW_SENSOR_A2_SDA_PIN, OUTPUT);
    digitalWrite(OKNXHW_SENSOR_A2_SDA_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(NOPIN, OKNXHW_SENSOR_A1_SCL_PIN, PIO_BUFFER));

    pinMode(OKNXHW_SENSOR_B2_SDA_PIN, OUTPUT);
    digitalWrite(OKNXHW_SENSOR_B2_SDA_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(NOPIN, OKNXHW_SENSOR_B1_SCL_PIN, PIO_BUFFER));

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

#elif defined(DEVICE_REG1_LAN_SEN_MULTI)
    Serial1.setRxBufferSize(PIO_BUFFER);
    Serial1.setPins(OKNXHW_REG1_APP_SEN_MULTI_SENSOR1_SCL_RX_PIN, OKNXHW_REG1_APP_SEN_MULTI_SENSOR1_SDA_TX_PIN);
    openknxSMLModule.getChannel(0)->setSerial(&Serial1); // SML Platine A (oben)

    Serial2.setRxBufferSize(PIO_BUFFER);
    Serial2.setPins(OKNXHW_REG1_APP_SEN_MULTI_SENSOR2_SCL_RX_PIN, OKNXHW_REG1_APP_SEN_MULTI_SENSOR2_SDA_TX_PIN);
    openknxSMLModule.getChannel(1)->setSerial(&Serial2); // SML Platine B (unten)

#elif defined(DEVICE_REG2_PIPICO_V1_DD_METER)

    pinMode(OKNXHW_REG2_MSENS_1_SDA0_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG2_MSENS_1_SDA0_TX_PIN, HIGH);
    openknxSMLModule.getChannel(0)->setSerial(new SerialPIO(NOPIN, OKNXHW_REG2_MSENS_1_SCL0_RX_PIN, PIO_BUFFER));

    pinMode(OKNXHW_REG2_MSENS_2_SDA1_TX_PIN, OUTPUT);
    digitalWrite(OKNXHW_REG2_MSENS_2_SDA1_TX_PIN, HIGH);
    openknxSMLModule.getChannel(1)->setSerial(new SerialPIO(NOPIN, OKNXHW_REG2_MSENS_2_SCL1_RX_PIN, PIO_BUFFER));

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

#endif
}

uint32_t _debugCore0 = 0;
uint32_t _debugCore1 = 0;
uint32_t _gaExtractorTimer = 0;
bool _gaExtractorStarted = false;

void loop()
{
    openknx.loop();

    // Query gaextractor after 10 s, then every 30 s
    // auto queryGaExtractor = []() {
    //     logInfo("GAExtractor", "Querying https://tools.openknx.de/gaextractor/");
    //     openknxNetwork.webclient.get("https://tools.openknx.de/gaextractor/")
    //         // .ignoreBody()
    //         .onDone([](const OpenKNX::Network::Webclient::Response &res) {
    //             logIndentUp();
    //             logInfo("GAExtractor", "HTTP %d (%s) %u bytes", res.status(), res.success() ? "ok" : "failed", (unsigned)res.bodySize());
    //             logIndentDown();
    //         })
    //         .send();
    // };

    // if (!_gaExtractorStarted && millis() >= 10000)
    // {
    //     _gaExtractorStarted = true;
    //     _gaExtractorTimer = millis();
    //     queryGaExtractor();
    // }
    // else if (_gaExtractorStarted && delayCheck(_gaExtractorTimer, 30000))
    // {
    //     _gaExtractorTimer = millis();
    //     queryGaExtractor();
    // }

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