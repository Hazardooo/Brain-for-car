#include "SoftwareSerial.h"

// Создаем класс BTserial для работы с bluetooth модулем.
SoftwareSerial BTserial(6, 7);  // порт RX, порт TX

// Левая сторона
int APWM = 10;
int MotorA1 = 12;
int MotorA2 = 3;

// Правая сторона
int BPWM = 11;
int MotorB1 = 13;
int MotorB2 = 8;

int Buzzer = 4;

int PWMSET = 255;  // SET Speed Motor  Test 50% = 128 and Test 100% = 255
int STPSET = 0;

void setup() {
  // Настраиваем скорость передачи данных.
  Serial.begin(9600);
  BTserial.begin(9600);
  pinMode(4, OUTPUT);

  pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // Получаем данные от bluetooth модуля и передаем их в монитор порта.
  if (BTserial.available()) {
    switch (BTserial.read()) {
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
    Serial.write(BTserial.read());
  }
  // Получаем данные от монитора порта и передаем их в bluetooth модуль.
  // if (Serial.available()) {
  //   BTserial.write(Serial.read());
  // }
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
  delay(300);
  digitalWrite(Buzzer, LOW);
}