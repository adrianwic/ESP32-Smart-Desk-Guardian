#include <ESP32Servo.h>

const int dataPin = 21;
const int latchPin = 4;
const int clockPin = 5;

const int trigPin = 12;
const int echoPin = 14;
const int servoPin = 18;
const int lightPin = 32;

Servo myServo;

const int alarmDistance = 12;
bool isAlarmActive = false;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myServo.attach(servoPin);
  myServo.write(0); 
  
  Serial.begin(115200);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  int lightLevel = analogRead(lightPin);
  Serial.print("Poziom swiatla: ");
  Serial.println(lightLevel);

  int numLeds = map(distance, 5, 35, 8, 0);
  numLeds = constrain(numLeds, 0, 8);
  byte ledPattern = (1 << numLeds) - 1;

  if (distance > 0 && distance <= alarmDistance) {
    if (!isAlarmActive) {
      for (int kat = 0; kat <= 90; kat += 2) {
        myServo.write(kat);
        delay(15); 
      }
      isAlarmActive = true;
    }
    
    sendToRegister(0xFF);
    delay(100);
    sendToRegister(0x00);
    delay(100);
    
  } else {
    if (isAlarmActive) {
      for (int kat = 90; kat >= 0; kat -= 2) {
        myServo.write(kat);
        delay(15);
      }
      isAlarmActive = false;
    }
    
    sendToRegister(ledPattern);
    delay(50);
  }
}

void sendToRegister(byte pattern) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, pattern);
  digitalWrite(latchPin, HIGH);
}
