#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <Arduino.h>

#define DISTANCE_SENSOR_TRIG   16
#define DISTANCE_SENSOR_ECHO   17

void distance_sensor_initialize();
void distance_sensor_unit_read();
unsigned int distance_sensor_read();

#endif // DISTANCE_SENSOR_H