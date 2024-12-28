#include <Arduino.h>

#define SPEAKER_PIN 25

void setup() {

}

void playKick() {
  float frequency = 150.0; 
  float volume = 255.0;

  while (frequency > 40.0) {
    float period = 1000000.0 / frequency;

    for (int t = 0; t < period; t += 20) {
      float angle = (float)t / period * 2.0 * PI;
      int value = (sin(angle) + 1.0) * (volume / 2.0);

      dacWrite(SPEAKER_PIN, value);
      delayMicroseconds(10);
    }

    frequency -= 3.0; 
    volume -= 4.0; 
  }
  dacWrite(SPEAKER_PIN, 0);
}

void playSnare() {
  int volume = 200;

  for (int i = 0; i < 800; i++) {
    int randomValue = random(0, volume);
    dacWrite(SPEAKER_PIN, randomValue);
    delayMicroseconds(40);
    if (i % 5 == 0 && volume > 0) volume--; 
  }
  dacWrite(SPEAKER_PIN, 0);
}

void loop() {
  playKick();
  delay(200);
  playSnare();
  delay(200);
  playKick();
  delay(100);
  playKick();
  delay(100);
  playSnare();
  delay(400);
}