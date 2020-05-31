// hcsr04.cpp
// author ; sato.mshr@gmail.com
#include "Arduino.h"
#include "hcsr04.h"

Hcsr04::Hcsr04(int p_trig, int p_echo)
{
  _p_trig = p_trig;
  _p_echo = p_echo;
  pinMode(_p_trig, OUTPUT);
  pinMode(_p_echo, INPUT);
  _distance = 0;
}

float Hcsr04::distance(void)
{
  digitalWrite(_p_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_p_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_p_trig, LOW);
  _distance = pulseIn(_p_echo, HIGH) / 58.0;
  return _distance;
}
