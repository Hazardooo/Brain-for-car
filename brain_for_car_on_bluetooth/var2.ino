#include "SoftwareSerial.h"

SoftwareSerial BTserial(6, 7); 

const int APWM = 10, MotorA1 = 12, MotorA2 = 3;
const int BPWM = 11, MotorB1 = 13, MotorB2 = 8;
const int Buzzer = 4;

const int PWMSET = 255;
const int STPSET = 0;
const unsigned long beepDuration = 300;

unsigned long beepStartTime = 0;

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  pinMode({MotorA1, MotorA2, APWM, MotorB1, MotorB2, BPWM}, OUTPUT);
}

void loop() {
  if (BTserial.available()) {
    char command = BTserial.read();
    switch (command) {
      case 'F':
        Move(1, 0, 1, 0);
        break;

      case 'G':
        Move(0, 1, 0, 1);
        break;

      case 'R':
        Move(0, 1, 1, 0);
        break;

      case 'L':
        Move(1, 0, 0, 1);
        break;

      case 'X':
        Beep();
        break;

      case 'S':
        Stop();
        break;

      default:
        Stop();
        break;
    }
    Serial.write(command);
  }
  
  updateBeep();
}

void Move(int pwr1, int pwr2, int pwr3, int pwr4) {
  digitalWrite(MotorA1, pwr1);
  digitalWrite(MotorA2, pwr2);
  analogWrite(APWM, PWMSET);

  digitalWrite(MotorB1, pwr3);
  digitalWrite(MotorB2, pwr4);
  analogWrite(BPWM, PWMSET);
}

void Stop() {
  analogWrite(APWM, STPSET);
  analogWrite(BPWM, STPSET);
}

void Beep() {
  digitalWrite(Buzzer, HIGH);
  beepStartTime = millis();
}

void updateBeep() {
  if (digitalRead(Buzzer) == HIGH && millis() - beepStartTime >= beepDuration) {
    digitalWrite(Buzzer, LOW);
  }
}
