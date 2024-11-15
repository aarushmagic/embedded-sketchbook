const int sensorPin = A0;

const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8};

const int digit1Pin = 9;
const int digit2Pin = 10; 

const int displayDelay = 5;

byte numPatterns[10][7] = {
  {0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 1, 1, 0},
  {1, 0, 0, 1, 1, 0, 0},
  {0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0}
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(digit1Pin, OUTPUT);
  pinMode(digit2Pin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(sensorPin);
  float voltage = reading * (5.0 / 1024.0);
  float tempC = (voltage - 0.5) * 100.0;

  float tempF = (tempC * 9.0 / 5.0) + 32.0;

  int tempInt = (int)(tempF + 0.5);

  if (tempInt < 0) {
    tempInt = 0;
  }
  if (tempInt > 99) {
    tempInt = 99;
  }

  int tensDigit = tempInt / 10;
  int onesDigit = tempInt % 10;

  Serial.print("Temp: ");
  Serial.print(tempF);
  Serial.println(" F");

  digitalWrite(digit2Pin, LOW);
  setSegments(tensDigit);
  digitalWrite(digit1Pin, HIGH);
  delay(displayDelay);

  digitalWrite(digit1Pin, LOW);
  setSegments(onesDigit);
  digitalWrite(digit2Pin, HIGH);
  delay(displayDelay);
}

void setSegments(int digit) {
  if (digit < 0 || digit > 9) {
    return;
  }
  
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numPatterns[digit][i]);
  }
}