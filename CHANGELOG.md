# Changes

## upcomming releases

* Feature: Add hardware support for the OpenKNX REG1 868MHz-Gateway (REG1-GW-RF868M) — two SML inputs (onboard + unten) plus a CC1101 radio for Wireless M-Bus
* Feature: Add wireless M-Bus support for the OpenKNX UP1 8xSensor (SEN-UP1-8xTH) via CC1101, repurposing the Binäreingang pins A/B/C as SML inputs
* Feature: Add ESP32-based REG1 MultiSensor devices (LAN and WLAN variants), with WebServer/MQTT/WebClient build flags for IP-capable devices
* Feature: Assign default status LEDs (SML/BI Gesamtstatus, SmartMF channel LEDs) before `openknx.setup()` runs, fixing LEDs staying off after a restart until the first status change
* Fix: Enlarge the SML serial receive buffer to 512 bytes so a full telegram fits even if the main loop is briefly busy
* Fix: REG1 Basismodul/MultiSensor's onboard SML pin was hardcoded to `9` instead of using `OKNXHW_REG1_SENSOR_SCL_RX_PIN`
* Fix: `dependencies.txt` pointed at the pre-rewrite OFM-SML/OFM-WirelessMBus commits
* Update: Migrate `OPENKNX_TRACE1`/`OPENKNX_TRACE2` filters to the combined `OPENKNX_TRACE` syntax
* Update: Adapt to the current OGM-Common API (`openknx.init()` without a firmware revision argument, `SerialPIO::NOPIN` → `NOPIN`)
* Doc: Add README, AGENTS.md and CLAUDE.md
