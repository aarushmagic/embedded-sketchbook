# Arduino Thermometer

## Project Status: Tuning & Stabilization
I have integrated the battery pack, but encountered signal noise issues.

### Current Progress
* **Issue:** Battery power introduced fluctuations in the sensor readings.
* **Fix:** Added a 100-sample averaging filter in the software to smooth out the noise.
* **Fix:** Added a decoupling capacitor to the power rails.

![Standalone Breadboard](./assets/standalone_breadboard.jpg)