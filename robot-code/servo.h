#ifndef SERVO_H
#define SERVO_H

#define SERVO_PIN   9

#include <Servo.h>

static Servo serwomechanizm;

void servo_initialize();
void servo_set(int angle);

#endif // SERVO_H