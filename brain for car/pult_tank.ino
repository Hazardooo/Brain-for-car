#include "IRremote.h"

IRrecv irrecv(2);  // указываем вывод, к которому подключен приемник

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

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(4, OUTPUT);

  pinMode(12, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0xEBBEE2B5:
        Move(1, 0, 1, 0);
        break;
      case 0xE892FE5B:
        Move(0, 1, 0, 1);
        break;
      case 0x9BED4B5B:
        Move(0, 1, 1, 0);
        break;
      case 0xE157D0B5:
        Move(1, 0, 0, 1);
        break;
      case 0x882C9158:
        Stop();
        break;
      case 0xDE5526F7:
        Beep();
        break;
      default:
        Stop();
        break;
    }
    irrecv.resume();  // принимаем следующую команду
  }
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