#include "SoftwareSerial.h"
SoftwareSerial BTserial(11, 12);  // порт RX, порт TX



void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
}

void loop() {
  if (BTserial.available()) {
    Serial.write(BTserial.read());
  }

  if (Serial.available()) {
    BTserial.write(Serial.read());
  }
}
