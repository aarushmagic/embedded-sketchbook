# ESP32 Bluetooth Speaker (Paper Bowl Driver)

A complete audio system built from scratch. I constructed the physical driver (speaker) using a paper bowl, magnets, and voice coil, and engineered a Single-Ended Class A Amplifier to drive it using an LM317T voltage regulator.

## 🛠️ The Hardware Stack

### 1. The Physical Driver
Instead of buying a speaker, I built one to understand the electromagnetism behind the Analog Output Stage.
* **Diaphragm:** Paper bowl.
* **Voice Coil:** Hand-wound enameled copper wire.
* **Magnet:** Stacked neodymium magnets.

![The Homemade Driver](./assets/homemade_driver.jpg)

### 2. The Amplifier (Class A)
The ESP32 DAC (3.3V / ~40mA) was insufficient to drive the coil. I implemented a single-ended Class A amplifier using an LM317T.
* **Bias Point:** Tuned to ~4.5V using a potentiometer to maximize swing between 0V-9V.
* **Topology:** ![Amp Schematic](./assets/amplifier_schematic.png)

### 3. The Controller (ESP32)
* **Protocol:** Bluetooth A2DP Sink.
* **Output:** 8-bit Internal DAC.

![Class A Amplifier Circuit](./assets/circuit_v2_amp.jpg)