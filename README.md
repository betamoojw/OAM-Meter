# OAM-Meter

Dies ist die konkrete OpenKNX-Applikation "Zählermodul": Sie bindet die
Funktionsmodule (OFM) für SML, Wireless M-Bus, Zähler-/Logikverarbeitung,
Binäreingänge, virtuelle Taster und Netzwerk zusammen und verdrahtet sie
jeweils auf die tatsächliche Hardware der unterstützten Geräte.

## Unterstützte Geräte

Jedes Gerät hat einen eigenen PlatformIO-Release-Build in
[platformio.custom.ini](platformio.custom.ini) und einen eigenen
`#elif defined(DEVICE_...)`-Zweig in [src/main.cpp](src/main.cpp), der die
physischen Pins auf die Kanäle der Funktionsmodule verdrahtet:

- OpenKNX PiPico BCU Connector
- OpenKNX UP1 8xSensor (inkl. Wireless M-Bus über CC1101)
- OpenKNX REG1 Basismodul (V0, TP und IP)
- OpenKNX REG1 MultiSensor (TP, LAN und WLAN)
- OpenKNX REG1 868MHz-Gateway (zwei SML-Eingänge + Wireless M-Bus)
- OpenKNX REG2 PiPico V1 DeviceDisplay Meter
- Smart-MF S0-Zählermodul / eHZ-Schnittstelle

Welcher Kanal bei welchem Gerät mit welcher physikalischen Schnittstelle
verbunden ist, steht in [scripts/Readme-Hardware.html](scripts/Readme-Hardware.html).

## Status-LEDs

Modul- und Kanal-LEDs werden für die jeweils passenden Geräte über
`openknx.ledFunctions.assignLed2Function()` mit Standardwerten belegt, bevor
`openknx.setup()` läuft — nur so übernehmen die Funktionsmodule beim eigenen
`setup()` bereits eine registrierte physische LED. Details zum
Zustandsmodell stehen in der jeweiligen OFM-Dokumentation (SML, Wireless
M-Bus).

## Build

Abhängigkeiten liegen als Symlinks unter `lib/` und werden über
[restore/Restore-Dependencies.ps1](restore/Restore-Dependencies.ps1) bzw.
die VSCode-Tasks in [.vscode/tasks.json](.vscode/tasks.json) verwaltet.
Releases für alle Geräte baut [scripts/Build-Release.ps1](scripts/Build-Release.ps1).
