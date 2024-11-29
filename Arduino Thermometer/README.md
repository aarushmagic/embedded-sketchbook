# Arduino Thermometer

## Project Status: Troubleshooting & Final Logic
The device is soldered, but accuracy testing revealed a drift issue due to battery voltage drop.

### Challenges & Solutions
* **The Problem:** The initial code used the default 5V analog reference. Since the 3xAA batteries provide ~4.5V (dropping over time), the `analogRead` logic assumed a stable 5V, causing temperature readings to drift high.
* **The Fix:** Switched to the ATmega328P's **Internal 1.1V Reference**, which is independent of supply voltage.
* **Implementation:** Since the chip was already soldered, I used an Arduino Uno as an ISP (In-System Programmer) to re-flash the chip in-circuit.

![Soldered Circuit](./assets/soldered_circuit.jpg)