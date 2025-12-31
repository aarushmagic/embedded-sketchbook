# New Year Countdown

A quick holiday project to build a precise countdown clock for the New Year.

## Overview
This project uses an ESP32 and a TFT display to show a live countdown to the New Year. It connects to WiFi to fetch the exact time via NTP (Network Time Protocol), ensuring the countdown is perfectly synchronized.

## Features
* **Accurate Timekeeping:** Syncs with `time.nist.gov` to prevent drift.
* **Dynamic Display:** The visual layout changes as the time gets closer:
    * **Standard:** Hours, Minutes, Seconds cards.
    * **Final Hour:** Focuses on Minutes and Seconds.
    * **Final Minute:** Large seconds counter with a progress bar.
* **Celebration Mode:** Triggers a particle-based fireworks animation at midnight.
* **Graphics:** Uses `TFT_eSPI` sprites for flicker-free rendering.

## Hardware
* ESP32 Development Board
* TFT LCD Display (compatible with TFT_eSPI)