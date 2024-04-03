#ifndef WHEELS_H
#define WHEELS_H

#include <Arduino.h>

#define MOTOR1_EN           3
#define MOTOR1_IN1          4
#define MOTOR1_IN2          2
#define MOTOR1_SENSOR       14

#define MOTOR2_EN           6
#define MOTOR2_IN1          7
#define MOTOR2_IN2          5
#define MOTOR2_SENSOR       15

#define WHEELS_MAX_VALUE    255
#define WHEELS_MIN_VALUE    70
#define WHEELS_ZERO_VALUE   10

#define TICKS_PER_CM        2
#define TICKS_PER_DEG       5

#define WHEELS_FORWARD      1
#define WHEELS_BACKWARD     -1

#define MIN_DRIFT_TRESHOLD  10
#define DRIFT_COMPENSATION  0
#define TICK_SPEED_COEFF    5

extern float wheels_left_speed;
extern float wheels_right_speed;

extern int32_t wheels_left_ticks_to_go;
extern int32_t wheels_right_ticks_to_go;

void wheels_initialize();

void wheels_left_forward(int speed);
void wheels_left_backward(int speed);
void wheels_left_stop();

void wheels_right_forward(int speed);
void wheels_right_backward(int speed);
void wheels_right_stop();

void wheels_go_distance(int left_cm, int right_cm);
void wheels_go_angle(int deg);

void wheels_update();

#endif // WHEELS_H
