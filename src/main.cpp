#include "FileTransferModule.h"
#include "Logic.h"
#include "MeterModule.h"
#include "OpenKNX.h"
#include "UsbExchangeModule.h"

void setup()
{
    const uint8_t firmwareRevision = 0;
    openknx.init(firmwareRevision);
    openknx.addModule(1, openknxLogic);
    openknx.addModule(2, openknxMeterModule);
    openknx.addModule(8, openknxUsbExchangeModule);
    openknx.addModule(9, openknxFileTransferModule);
    openknx.setup();
}

uint32_t _debugCore0 = 0;

void loop()
{
    openknx.loop();
    if (delayCheck(_debugCore0, 15000))
    {
        TpUartDataLinkLayer* dll = knx.bau().getDataLinkLayer();
        // logInfo("BCU<Status>", "%s", dll->isConnected() ? "Connected" : "Disconnected");
        // logInfo("BCU<Received>", "Processed: %i - Ignored: %i - Invalid: %i - Unknown: %i",
        //         dll->getRxProcessdFrameCounter(), dll->getRxIgnoredFrameCounter(), dll->getRxInvalidFrameCounter(), dll->getRxUnknownControlCounter());
        // logInfo("BCU<Transmitted>", "Processed: %i/%i", dll->getTxProcessedFrameCounter(), dll->getTxFrameCounter());

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
}
#endif