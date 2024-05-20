#include "wheels.h"

#include <Arduino.h>

volatile uint32_t left_motor_ticks_counter;
volatile uint32_t right_motor_ticks_counter;

int wheels_left_direction;
int wheels_right_direction;

int wheels_left_ticks_to_go = 0;
int wheels_right_ticks_to_go = 0;

float wheels_left_speed = 0.0;
float wheels_right_speed = 0.0;

int32_t wheels_left_travelled_ticks = 0;
int32_t wheels_right_travelled_ticks = 0;

uint32_t last_update_time;
uint8_t left_drift;
uint8_t right_drift;

ISR(PCINT1_vect) 
{
 if((PINC & (1 << PC0)))
 {
  left_motor_ticks_counter++;
 }

 if((PINC & (1 << PC1)))
 {
  right_motor_ticks_counter++;
 }
}

void wheels_initialize()
{
  pinMode(MOTOR1_EN, OUTPUT);
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR1_SENSOR, INPUT);
  
  pinMode(MOTOR2_EN, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);
  pinMode(MOTOR2_IN2, OUTPUT);
  pinMode(MOTOR2_SENSOR, INPUT);
  
  left_motor_ticks_counter = 0;
  right_motor_ticks_counter = 0;
  wheels_left_ticks_to_go = 0;
  wheels_right_ticks_to_go = 0;
  wheels_left_travelled_ticks = 0;
  wheels_left_travelled_ticks = 0;

  PCICR = 0x02;
  PCMSK1 = 0x03;

  last_update_time = millis();
}

void wheels_left_forward(int speed)
{
  if(speed > WHEELS_MAX_VALUE) { speed = WHEELS_MAX_VALUE; }
  else if(speed < WHEELS_ZERO_VALUE) { speed = 0; }
  else if(speed < WHEELS_MIN_VALUE) { speed = WHEELS_MIN_VALUE; }
  else { speed = speed; }

  wheels_left_direction = WHEELS_FORWARD;

  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
  analogWrite(MOTOR1_EN, speed);
}

void wheels_left_backward(int speed)
{
  if(speed > WHEELS_MAX_VALUE) { speed = WHEELS_MAX_VALUE; }
  else if(speed < WHEELS_ZERO_VALUE) { speed = 0; }
  else if(speed < WHEELS_MIN_VALUE) { speed = WHEELS_MIN_VALUE; }
  else { speed = speed; }

  wheels_left_direction = WHEELS_BACKWARD;

  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
  analogWrite(MOTOR1_EN, speed);
}

void wheels_left_stop()
{
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, LOW);
}

void wheels_right_forward(int speed)
{
  if(speed > WHEELS_MAX_VALUE) { speed = WHEELS_MAX_VALUE; }
  else if(speed < WHEELS_ZERO_VALUE) { speed = 0; }
  else if(speed < WHEELS_MIN_VALUE) { speed = WHEELS_MIN_VALUE; }
  else { speed = speed; }

  wheels_right_direction = WHEELS_FORWARD;

  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
  analogWrite(MOTOR2_EN, speed);
}

void wheels_right_backward(int speed)
{
  if(speed > WHEELS_MAX_VALUE) { speed = WHEELS_MAX_VALUE; }
  else if(speed < WHEELS_ZERO_VALUE) { speed = 0; }
  else if(speed < WHEELS_MIN_VALUE) { speed = WHEELS_MIN_VALUE; }
  else { speed = speed; }

  wheels_right_direction = WHEELS_BACKWARD;

  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
  analogWrite(MOTOR2_EN, speed);
}

void wheels_right_stop()
{
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, LOW);
}

void wheels_go_distance(int left_cm, int right_cm)
{
  wheels_left_ticks_to_go += left_cm * TICKS_PER_CM;
  wheels_right_ticks_to_go += right_cm * TICKS_PER_CM;
}

void wheels_go_angle(int deg)
{
  wheels_left_ticks_to_go += deg * TICKS_PER_DEG;
  wheels_right_ticks_to_go -= deg * TICKS_PER_DEG;
}

void wheels_update()
{
  uint32_t current_time = millis();
  uint32_t delta_time = (current_time - last_update_time) / 1000;  // miliseconds

  int32_t left_ticks = left_motor_ticks_counter;
  int32_t right_ticks = right_motor_ticks_counter;

  left_motor_ticks_counter = 0;
  right_motor_ticks_counter = 0;

  wheels_left_speed = (float)left_ticks / delta_time / TICKS_PER_CM * wheels_left_direction;        // cm per second
  wheels_right_speed = (float)right_ticks / delta_time / TICKS_PER_CM * wheels_right_direction;     // cm per second

  if(wheels_left_direction == WHEELS_FORWARD)
  {
    wheels_left_ticks_to_go -= left_ticks;
    wheels_left_travelled_ticks += left_ticks;
  }
  else
  {
    wheels_left_ticks_to_go += left_ticks;
    wheels_left_travelled_ticks -= left_ticks;
  }

  if(wheels_right_direction == WHEELS_FORWARD)
  {
    wheels_right_ticks_to_go -= right_ticks;
    wheels_right_travelled_ticks += right_ticks;
  }
  else
  {
    wheels_right_ticks_to_go += right_ticks;
    wheels_right_travelled_ticks -= right_ticks;
  }


  if(left_ticks - right_ticks > MIN_DRIFT_TRESHOLD)
  {
    right_drift += DRIFT_COMPENSATION;
    left_drift -= DRIFT_COMPENSATION;
  }
  else if(right_ticks - left_ticks > MIN_DRIFT_TRESHOLD)
  {
    right_drift -= DRIFT_COMPENSATION;
    left_drift += DRIFT_COMPENSATION;
  }

  // int new_left_speed = wheels_left_ticks_to_go * TICK_SPEED_COEFF;
  // int new_right_speed = wheels_right_ticks_to_go * TICK_SPEED_COEFF;

  // wheels_left_speed = new_left_speed;
  // wheels_right_speed = new_right_speed;

  // int new_left_speed;
  // if(wheels_left_ticks_to_go > 15) {
  //   new_left_speed = 150;
  // }
  // else {
  //   new_left_speed = 0;
  // }

  // int new_right_speed;
  // if(wheels_right_ticks_to_go > 15) {
  //   new_right_speed = 150;
  // }
  // else {
  //   new_right_speed = 0;
  // }

  // if(new_left_speed > 0) {
  //   wheels_left_forward(new_left_speed + left_drift);
  // }
  // else
  // {
  //   wheels_left_backward(-new_left_speed + left_drift);
  // }

  // if(new_right_speed > 0)
  // {
  //   wheels_right_forward(new_right_speed + right_drift);
  // }
  // else
  // {
  //   wheels_right_backward(-new_right_speed + right_drift);
  // }
}
