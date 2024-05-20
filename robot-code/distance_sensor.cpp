#include "distance_sensor.h"

#define LAST_DISTANCES_NUMBER 1

volatile unsigned int last_distances[LAST_DISTANCES_NUMBER];
volatile int last_distances_index = -1;

void distance_sensor_initialize()
{
  pinMode(DISTANCE_SENSOR_TRIG, OUTPUT);
  pinMode(DISTANCE_SENSOR_ECHO, INPUT);
}

void distance_sensor_unit_read()
{
  /* uruchamia sonar (puls 10 ms na `TRIGGER')
  * oczekuje na powrotny sygnał i aktualizuje
  */
  digitalWrite(DISTANCE_SENSOR_TRIG, HIGH);
  delay(10);
  digitalWrite(DISTANCE_SENSOR_TRIG, LOW);

  unsigned long time_of_travel = pulseIn(DISTANCE_SENSOR_ECHO, HIGH);

  /* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
  * droga tam i z powrotem, zatem:
  */

  last_distances_index  = (last_distances_index + 1) % LAST_DISTANCES_NUMBER;

  last_distances[last_distances_index] = time_of_travel / 58;
}

unsigned int distance_sensor_read()
{
  unsigned int sum = 0;
  for(int i = 0; i < LAST_DISTANCES_NUMBER; i++)
  {
    sum += last_distances[(last_distances_index + i) % LAST_DISTANCES_NUMBER];
  }

  return sum / LAST_DISTANCES_NUMBER;
}