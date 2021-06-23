#include "seg7.h"
#include "Arduino.h"
#include "SPI.h"

const int hex[] = {0x7E, 0x0A, 0xB6, 0x9E, 0xCA, 0xDC, 0xFC, 0x0E, 0xFE, 0xDE};

Seg7::Seg7(int ss, int pwm) {
  _ss = ss;
  _pwm = pwm;
}

void Seg7::begin() {
  pinMode(_ss, OUTPUT);
  digitalWrite(_ss, LOW);
  digitalWrite(_pwm, LOW);
  SPI.begin();
}

void Seg7::on() {
  digitalWrite(_pwm, HIGH);
}

void Seg7::off() {
  digitalWrite(_pwm, LOW);
}

void Seg7::displayRaw(int field1, int field2) {
  SPI.transfer(field2);
  SPI.transfer(field1);
  digitalWrite(_ss, HIGH);
  digitalWrite(_ss, LOW);
}

void Seg7::display(int num) {
  if (num < 10) {
    SPI.transfer(getHexFromNum(num));
    SPI.transfer(0);
  } else if (num < 100){
    int first = num % 10;
    int second = num / 10;
    SPI.transfer(getHexFromNum(first));
    SPI.transfer(getHexFromNum(second));
  } else {
    SPI.transfer(0x80);
    SPI.transfer(0x80);
  }
  digitalWrite(_ss, HIGH);
  digitalWrite(_ss, LOW);
}

int Seg7::getHexFromNum(int num) {
  return hex[num];
}
