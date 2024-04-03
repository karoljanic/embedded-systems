#include "buzzer.h"

static beep() 
{
  digitalWrite(BUZZER_PIN, digitalRead(BUZZER_PIN) ^ 1);
}

void buzzer_initialize()
{
  pinMode(BUZZER_PIN, OUTPUT);
  Timer1.initialize();
  buzzer_is_playing = false;
}

void buzzer_play(uint32_t delay_period)
{
  buzzer_stop();
  Timer1.attachInterrupt(beep, delay_period);
  buzzer_is_playing = true;
}

void buzzer_stop()
{
  if(buzzer_is_playing)
  {
    Timer1.detachInterrupt();
    buzzer_is_playing = false;
  }
}
