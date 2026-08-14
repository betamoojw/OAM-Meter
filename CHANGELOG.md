# Changes

## 1.0.0

*(seit 0.6.0, veröffentlicht am 4. Juli 2025)*

### ⚠️ Breaking Change: Anschlussbelegung beim UP1 8xSensor geändert

Beim **OpenKNX UP1 8xSensor** wurden die Anschlüsse **A, B und C** von
Binäreingängen zu SML-Zähleranschlüssen umgewidmet (nötig, damit dort
Platz für Wireless M-Bus entsteht). Die verbleibenden Binäreingänge
liegen jetzt auf den Anschlüssen **G und H** (4 statt vorher 5
Eingänge). Wer an diesem Gerät bereits Binäreingänge über A/B/C
verkabelt hat, **muss diese auf G/H umklemmen**, bevor das Update
eingespielt wird — sonst funktionieren die betroffenen Eingänge nicht
mehr.

### Neue Geräte

- **OpenKNX REG1 868MHz-Gateway** (neu): Zwei SML-Zähleranschlüsse plus
  Funkempfang für Wireless M-Bus (Wasser-/Wärmemengenzähler) in einem
  Gerät.
- **OpenKNX UP1 8xSensor**: kann jetzt zusätzlich Wireless-M-Bus-Zähler
  per Funk einlesen.
- **OpenKNX REG1 MultiSensor**: jetzt auch als LAN- und WLAN-Variante
  erhältlich (statt nur klassisch über den KNX-Bus).

### Neue Funktionen

- **Wireless M-Bus**: Wasser- und Wärmemengenzähler lassen sich jetzt
  komplett kabellos per Funk auslesen (bis zu 9 Zähler gleichzeitig,
  verschlüsselte Telegramme werden automatisch entschlüsselt).
- **Status-LEDs überarbeitet**: Modul- und Kanal-LEDs für SML und
  Wireless M-Bus zeigen jetzt nach einem einheitlichen Schema an, ob
  alles ok ist, ein Zähler nicht antwortet oder ein Fehler vorliegt —
  und tun das auch direkt nach einem Neustart zuverlässig (vorher
  blieben sie bis zum ersten Zählerwert dunkel).
- **SML-Diagnose**: Über einen einfachen Befehl lässt sich jetzt direkt
  am Gerät ablesen, was ein angeschlossener Zähler tatsächlich liefert
  (Zählertyp, Tarife, verfügbare Messwerte) — praktisch bei der
  Inbetriebnahme, ohne vorher etwas in der ETS einstellen zu müssen.
- **Zähler-Kanäle lassen sich einzeln suspendieren** (SML und Wireless
  M-Bus), ohne die komplette Konfiguration zu verändern.
- **MQTT-Unterstützung** für die LAN/WLAN-Geräte.

### Verbesserungen

- SML-Empfang ist robuster gegenüber gestörten oder unvollständigen
  Zählertelegrammen, der Empfangspuffer wurde vergrößert, damit auch
  größere Telegramme sicher ankommen.
- Zählerstände und Referenzwerte im Meter-Modul wurden an mehreren
  Stellen genauer berechnet (u. a. Rundung, Vorzeichenbehandlung,
  Impulsdauer-Begrenzung).

### Aktualisierte Module

| Modul                     | vorher | jetzt       |
| ------------------------- | ------ | ----------- |
| OGM-Common (Basis)        | 1.4.0  | 1.9.1       |
| SML                       | 0.1.1  | 1.0.0       |
| Wireless M-Bus            | —      | 0.1.0 (neu) |
| Meter                     | 0.5.0  | 1.0.0       |
| Netzwerk                  | 0.5.0  | 0.7.0       |
| Logikmodul                | 3.7.0  | 4.4.1       |
| Binäreingang              | 0.2.1  | 0.4.0       |
| Virtuelle Taster          | 0.5.1  | 0.7.0       |
| Konfigurationstransfer    | 0.4.0  | 0.5.0       |
