# OAM-Meter — Architektur

OAM-Meter ist keine eigene OFM-Bibliothek, sondern die konkrete
Geräte-Applikation ("Zählermodul"), die mehrere OpenKNX-Funktionsmodule
(OFM) zu fertigen Firmwares für unterschiedliche Hardware zusammenbaut.

## Basis: OGM-Common

Alle Module hier (inkl. dieser Applikation selbst) bauen auf
[lib/OGM-Common/AGENTS.md](lib/OGM-Common/AGENTS.md) auf — Modulsystem,
LED-/Flash-/Zeit-API, Logging, Embedded-Rahmenbedingungen und
Code-Konventionen sind dort beschrieben und gelten hier unverändert
mit. Vorhandene Claude-Skills/Agents aus OGM-Common (z. B.
`.claude/agents/openknx-channelselect.md` für das Kanalauswahl-Muster)
gelten ebenso für dieses Projekt.

## Aufbau

- `src/main.cpp` — einziger Applikationscode. `setup()` registriert die
  Module (`openknx.addModule(...)`) und verdrahtet danach in einem
  `#if defined(DEVICE_...) #elif ... #endif`-Block die physischen Pins auf
  die Kanäle der Module, abhängig vom aktiven `DEVICE_*`-Build-Flag.
- `include/hardware.h` — pro `DEVICE_*` ein Block mit Macros für
  Binäreingang-Pins (`OPENKNX_BI_GPIO_*`) und, falls vorhanden,
  Wireless-M-Bus-Pins (`WMBUS_*`). Diese Macros werden von den jeweiligen
  OFM-Bibliotheken gelesen, nicht von `main.cpp` selbst.
- `platformio.custom.ini` — ein `[env:release_DEVICE_*]` pro Gerät, das
  genau ein `-D DEVICE_*`-Flag setzt (plus Netzwerk-Flags wie `KNX_IP_LAN`
  bei IP-Geräten). LAN- und WLAN-Variante eines Geräts teilen sich dasselbe
  `DEVICE_*`-Flag für die Verdrahtung — sie unterscheiden sich nur über
  `KNX_IP_LAN` vs. `KNX_IP_WIFI`.
- `include/knxprod.h`, `src/MeterModule-Dev.xml`, `src/MeterModule-Release.xml`,
  `dependencies.txt` — von OpenKNXproducer bzw. den Restore-Skripten
  generierte Artefakte. Nicht von Hand pflegen, außer für punktuelle Fixes
  (z. B. Versionsnummer) — Quelle der Wahrheit ist `MeterModule.base.xml`.

## Wichtige Reihenfolge-Regel: LED-Zuweisung vor `openknx.setup()`

`openknx.ledFunctions.assignLed2Function()` schreibt direkt in die interne
`_leds`-Liste der jeweiligen `FunctionGroup`. Ruft ein Modul in seinem
eigenen `setup()` (das innerhalb von `openknx.setup()` läuft) bereits
`led->on()`/`color()`/... auf, bevor hier eine physische LED zugewiesen
wurde, geht der Aufruf ins Leere — die LED bleibt bis zur nächsten
Statusänderung aus. Deshalb müssen alle `assignLed2Function()`-Aufrufe in
`main.cpp` **vor** `openknx.setup()` erfolgen (aber nach `openknx.init()`,
das die physischen LED-Objekte erst registriert).

## Geräte hinzufügen

1. `include/hardware.h`: neuen `#ifdef DEVICE_*`-Block mit den benötigten
   Pin-Macros ergänzen.
2. `src/main.cpp`: `#elif defined(DEVICE_*)`-Zweig mit der Verdrahtung
   ergänzen, LED-Default-Zuweisung (falls gewünscht) in den Block vor
   `openknx.setup()` einsortieren.
3. `platformio.custom.ini`: `[env:release_DEVICE_*]` ergänzen.
4. `scripts/Build-Release.ps1`: Build-Step für das neue Environment
   ergänzen.
5. `scripts/Readme-Hardware.html`: Tabellenzeile mit der Pin-Belegung
   ergänzen.
6. ETS-Producer laufen lassen (VSCode-Task "OpenKNXproducer (Dev)"), um
   `include/knxprod.h` und `src/MeterModule-Dev.xml` zu regenerieren.

## Referenzen

- [README.md](README.md) — Funktionsüberblick
- [scripts/Readme-Hardware.html](scripts/Readme-Hardware.html) — Pin-Belegung pro Gerät
- [CHANGELOG.md](CHANGELOG.md) — Versionshistorie
