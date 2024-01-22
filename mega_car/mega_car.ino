#include "SoftwareSerial.h"
SoftwareSerial BTserial(11, 12);  // порт RX, порт TX

const int Light = 10;
const int MoveUp1 = 2, MoveUp2 = 3;
const int MoveDown1 = 4, MoveDown2 = 5;
const int MoveRight1 = 6, MoveRight2 = 7;
const int MoveLeft1 = 8, MoveLeft2 = 9;

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);

  pinMode(Light, INPUT);

  pinMode(MoveUp1, OUTPUT);
  pinMode(MoveUp2, OUTPUT);

  pinMode(MoveDown1, OUTPUT);
  pinMode(MoveDown2, OUTPUT);

  pinMode(MoveRight1, OUTPUT);
  pinMode(MoveRight2, OUTPUT);

  pinMode(MoveLeft1, OUTPUT);
  pinMode(MoveLeft2, OUTPUT);
}

void loop() {
  Initialization();
  while (true) {
    if (BTserial.available()) {
      // Serial.write(BTserial.read());
      switch (BTserial.read()) {
        case 'F':
          MoveUp();
          break;

        case 'G':
          MoveDown();
          break;

        case 'R':
          MoveRight();
          break;
        
        // case 'FR':
        //   MoveUpRight();
        //   break;

        case 'L':
          MoveLeft();
          break;

        case 'X':
          LightOn();
          break;

        case 'S':
          Initialization();
          break;

        default:
          Initialization();
          break;
      }
    }
  }
}

void Initialization() {
  digitalWrite(MoveUp1, 1);
  digitalWrite(MoveUp2, 1);

  digitalWrite(MoveDown1, 1);
  digitalWrite(MoveDown2, 1);

  digitalWrite(MoveRight1, 1);
  digitalWrite(MoveRight2, 1);

  digitalWrite(MoveLeft1, 1);
  digitalWrite(MoveLeft2, 1);
}

void LightOn() {
  digitalWrite(Light, 1);
}

void MoveUp() {
  digitalWrite(MoveUp1, 0);
  digitalWrite(MoveUp2, 0);
}

// void MoveUpRight() {
//   MoveUp();
//   MoveRight();
// }

void MoveDown() {
  digitalWrite(MoveDown1, 0);
  digitalWrite(MoveDown2, 0);
}

void MoveRight() {
  digitalWrite(MoveRight1, 0);
  digitalWrite(MoveRight2, 0);
}

void MoveLeft() {
  digitalWrite(MoveLeft1, 0);
  digitalWrite(MoveLeft2, 0);
}