#ifndef LCD_BUZZER_H
#define LCD_BUZZER_H

#include "TimerOne.h"

#define BUZZER_PIN  13

static bool buzzer_is_playing;

void buzzer_initialize();
void buzzer_play(uint32_t delay_period);
void buzzer_stop();

#endif // LCD_BUZZER_H
