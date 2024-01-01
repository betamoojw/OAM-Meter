#include "Logic.h"
#include "OpenKNX.h"
#include "MeterModule.h"
#include "FileTransferModule.h"
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

void loop()
{
  openknx.loop();
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