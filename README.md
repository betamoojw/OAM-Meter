# OAM-Meter

Die OpenKNX-Applikation "Zählermodul". Je nach angeschlossener Hardware
liest sie Zählerdaten ein und stellt sie über KNX zur Verfügung.

## Funktionsumfang

- **SML** – Zählerdaten per Optokoppler/serieller Schnittstelle
- **Wireless M-Bus** – Zählerdaten per Funk (CC1101)
- **Meter** – Aufbereitung der Zählerstände, Referenzwerte und Ausgabeformate
- **Binäreingänge** – zusätzliche Eingänge, je nach Hardware
- **Virtuelle Taster**
- **Logikmodul**
- **Netzwerk** – bei IP-fähiger Hardware (LAN/WLAN)

Welche Funktion auf welcher Hardware verfügbar ist und wie die Anschlüsse
belegt sind, steht in [scripts/Readme-Hardware.html](scripts/Readme-Hardware.html).
