#include "wheels.h"
#include "lcd-monitor.h"
#include "buzzer.h"
#include "ir_receiver.h"
#include "ticker.h"

#define RECEIVER_PIN 11

uint8_t animation_frame_index = 0;

IRrecv ir_receiver(RECEIVER_PIN);
decode_results receiver_results;

void update_wheels()
{
  wheels_update();
}

void update_lcd_monitor()
{
  float speeds_sum = wheels_left_speed + wheels_right_speed;

  lcd_monitor_display_int(0, 2, wheels_left_speed);
  lcd_monitor_display_int(0, 11, wheels_right_speed);
  lcd_monitor_display_int(1, 2, wheels_left_ticks_to_go);
  lcd_monitor_display_int(1, 11, wheels_right_ticks_to_go);

  if(speeds_sum == 0)
  {
    lcd_monitor_display_special_character(0, 8, LCD_STOP_ANIMATION, animation_frame_index);
    animation_frame_index = (animation_frame_index + 1) % LCD_FRAMES_NUMBER;
  }
  else if(speeds_sum > 0)
  {
    lcd_monitor_display_special_character(0, 8, LCD_FORWARD_ANIMATION, animation_frame_index);
    animation_frame_index = (animation_frame_index + 1) % LCD_FRAMES_NUMBER;
  }
  else
  {
    lcd_monitor_display_special_character(0, 8, LCD_BACKWARD_ANIMATION, animation_frame_index);
    animation_frame_index = (animation_frame_index + 1) % LCD_FRAMES_NUMBER;
  }
}

void update_buzzer()
{
  float speeds_sum = wheels_left_speed + wheels_right_speed;

  if(speeds_sum < 0)
  {
    buzzer_play(-speeds_sum * 100);
  }
  else
  {
    buzzer_stop();
  }
}

void update_remote()
{
  if (ir_receiver.decode()) {
    if(ir_receiver.decodedIRData.decodedRawData == IR_RECEIVER_FORWARD_CHAR)
    {
      wheels_go_distance(50, 50);
    }
    else if(ir_receiver.decodedIRData.decodedRawData == IR_RECEIVER_BACKWARD_CHAR)
    {
      wheels_go_distance(-50, -50);
    }

    ir_receiver.resume();
  }
}


Ticker wheels_ticker(200, update_wheels);
Ticker lcd_monitor_ticker(500, update_lcd_monitor);
Ticker buzzer_ticker(1000, update_buzzer);
Ticker remote_ticker(300, update_remote);

void setup() {
  Serial.begin(9600);

  wheels_initialize();
  lcd_monitor_initialize();
  buzzer_initialize();
  
  ir_receiver.enableIRIn();
}

void loop() {
  wheels_ticker.check();
  lcd_monitor_ticker.check();
  buzzer_ticker.check();
  remote_ticker.check();
}
