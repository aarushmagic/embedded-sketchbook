# Embedded Systems Sketchbook

This repository is my digital playground for embedded engineering. It’s where I document my experiments and prototypes using AVR and ESP32 microcontrollers.

I do this mostly because I enjoy building things. There is something satisfying about writing code and seeing it control hardware in the real world. 

While some projects get a full custom build, most of these are practical experiments to test specific software concepts on actual hardware.

## How I Work

My workflow focuses on understanding the hardware constraints to write better software:

* **AVR / Arduino:** I use the Arduino ecosystem to prototype logic quickly. For projects requiring efficiency or portability, I migrate to a standalone ATmega328P. This forces me to handle bare-metal constraints, efficient register usage, and power management manually.
* **ESP32:** For networked or concurrent applications, I use the ESP32. I switch between the ESP-IDF and Arduino frameworks depending on the complexity, often leveraging FreeRTOS for task management in more advanced implementations.

## Tech Stack

* **Languages & Standards**
    * **C / C++:** Focus on pointer arithmetic, memory management, and hardware abstraction.
    * **Protocols:** I2C, SPI, UART, A2DP (Bluetooth), HTTP/WebSockets.
* **Hardware Platforms**
    * **Microcontrollers:** Arduino Uno, ATmega328P (Standalone), ESP32
* **Tools**
    * **Development:** Arduino IDE, ESP-IDF.
    * **Modeling/Sim:** OnShape (3D), Tinkercad (Circuits).

## Project Index

| Project | Hardware | CS & Engineering Concepts | Status |
| :--- | :--- | :--- | :--- |
| [Arduino Thermometer](./Arduino%20Thermometer) | ATmega328P | **Signal Processing:** Implemented software averaging filters to handle noisy sensor data.<br>**Optimization:** Migrated to standalone chip with internal 1.1V reference for precision. | Completed |
| [ESP32 Oscilloscope](https://github.com/aarushmagic/esp-scope) | ESP32 | **Systems Programming:** High-speed ADC sampling and real-time data visualization via WebSockets.<br>**Networking:** Asynchronous web server hosting. | Functional / Iterating |
| Bluetooth Speaker | ESP32 | **Audio Streaming:** Implementing an A2DP Bluetooth sink.<br>**Physics:** Building the physical driver (voice coils/magnets) to understand the analog output stage. | Planned |

## License

This project is open-source and available under the MIT License.