#include "Arduino.h"
#include "servo.h"

void servo_initialize()
{
  serwomechanizm.attach(SERVO_PIN);
}

void servo_set(int angle)
{
  serwomechanizm.write(angle);
}