#include <Arduino.h>

#define SPEAKER_PIN 25
#define NOTE_A  440
#define NOTE_F  349
#define NOTE_C  523
#define NOTE_E  659

void setup() {

}

void beep(int note, int duration) {
  long delayValue = 1000000 / note / 2;
  long numCycles = note * duration / 1000;

  for (long i = 0; i < numCycles; i++) {
    dacWrite(SPEAKER_PIN, 255);
    delayMicroseconds(delayValue);
    dacWrite(SPEAKER_PIN, 0);
    delayMicroseconds(delayValue);
  }
  delay(20);
}

void loop() {
  beep(NOTE_A, 500);
  beep(NOTE_A, 500);
  beep(NOTE_A, 500);
  beep(NOTE_F, 350);
  beep(NOTE_C, 150);
  beep(NOTE_A, 500);
  beep(NOTE_F, 350);
  beep(NOTE_C, 150);
  beep(NOTE_A, 650);

  delay(3000);
}