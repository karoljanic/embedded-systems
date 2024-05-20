#include "wheels.h"
#include "lcd-monitor.h"
#include "buzzer.h"
#include "servo.h"
#include "distance_sensor.h"
#include "ir_receiver.h"
#include "ticker.h"
#include "state-machine.hpp"

#define ROT_90_TICKS 17
#define ROT_120_TICKS 24
#define ROT_180_TICKS 80
#define OBSTACLE_DIST 20

uint8_t animation_frame_index = 0;

uint32_t lastTime = 0;
uint32_t startTime = 0;
bool t1 = false, t2 = false;

// IRrecv ir_receiver(RECEIVER_PIN);
// decode_results receiver_results;

// int currentDriveState = SQUARE_STATE_1;
// int currentDriveState = TRIANGLE_STATE_1;
int currentDriveState = AUTO_STATE_1;

int obstacle_length = 0;
int obstacle_width = 0;


void left(int speed, int ticks, int next_state) {
  if (wheels_left_travelled_ticks < ticks) {
    wheels_left_forward(speed);
  } else {
    wheels_left_stop();
  }

  if (wheels_right_travelled_ticks > -ticks) {
    wheels_right_backward(speed);
  } else {
    wheels_right_stop();
  }

  if (wheels_left_travelled_ticks > ticks && wheels_right_travelled_ticks < -ticks) {
    wheels_left_travelled_ticks = 0;
    wheels_right_travelled_ticks = 0;
    currentDriveState = next_state;
  }
}

void right(int speed, int ticks, int next_state) {
  if (wheels_left_travelled_ticks > -ticks) {
    wheels_left_backward(speed);
  } else {
    wheels_left_stop();
  }

  if (wheels_right_travelled_ticks < ticks) {
    wheels_right_forward(speed);
  } else {
    wheels_right_stop();
  }

  if (wheels_left_travelled_ticks < -ticks && wheels_right_travelled_ticks > ticks) {
    wheels_left_travelled_ticks = 0;
    wheels_right_travelled_ticks = 0;
    currentDriveState = next_state;
  }
}

void forward(int lspeed, int rspeed, int ticks, int next_state) {
  if (wheels_left_travelled_ticks < ticks) {
    wheels_left_forward(lspeed);
  } else {
    wheels_left_stop();
  }

  if (wheels_right_travelled_ticks < ticks) {
    wheels_right_forward(rspeed);
  } else {
    wheels_right_stop();
  }

  if (wheels_left_travelled_ticks > ticks && wheels_right_travelled_ticks > ticks) {
    wheels_left_travelled_ticks = 0;
    wheels_right_travelled_ticks = 0;
    currentDriveState = next_state;
  }
}

void backward(int lspeed, int rspeed, int ticks, int next_state) {
  if (wheels_left_travelled_ticks > -ticks) {
    wheels_left_backward(lspeed);
  } else {
    wheels_left_stop();
  }

  if (wheels_right_travelled_ticks > -ticks) {
    wheels_right_backward(rspeed);
  } else {
    wheels_right_stop();
  }

  if (wheels_left_travelled_ticks < -ticks && wheels_right_travelled_ticks < -ticks) {
    wheels_left_travelled_ticks = 0;
    wheels_right_travelled_ticks = 0;
    currentDriveState = next_state;
  }
}

void forward_until1(int lspeed, int rspeed, int current_dist, int target_dist, int next_state) {
  if (current_dist < target_dist) {
    wheels_left_stop();
    wheels_right_stop();
    wheels_left_travelled_ticks = 0;
    wheels_right_travelled_ticks = 0;
    currentDriveState = next_state;
  } else {
    wheels_left_forward(lspeed);
    wheels_right_forward(rspeed);
  }
}

void forward_until2(int lspeed, int rspeed, int current_dist, int target_dist, int next_state) {
  if (current_dist > target_dist) {
    wheels_left_stop();
    wheels_right_stop();
    obstacle_length = (wheels_left_travelled_ticks + wheels_right_travelled_ticks) / 2;
    wheels_left_travelled_ticks = 0;
    wheels_right_travelled_ticks = 0;
    currentDriveState = next_state;
  } else {
    wheels_left_forward(lspeed);
    wheels_right_forward(rspeed);
  }
}

int left_distance;
int right_distance;

void check_neighbourhood() {
  uint32_t currTime = millis();

  if (startTime == 0) {
    startTime = currTime;
  }
  uint32_t diff = currTime - startTime;
  
  servo_set(0);
  
  if(diff < 2000) {
    return;
  }

  if(!t1) {
    for(int i = 0; i < 5; i++) {
      distance_sensor_unit_read();
      delay(100);
    }
    left_distance = distance_sensor_read();
    lcd_monitor_display_int(0, 8, left_distance);
    t1 = true;
  }

  servo_set(180);

  if(diff < 4000) {
    return;
  }

  if(!t2) {
    for(int i = 0; i < 5; i++) {
      distance_sensor_unit_read();
      delay(100);
    }
    right_distance = distance_sensor_read();
    lcd_monitor_display_int(1, 8, right_distance);
    t2 = true;
  }

  lcd_monitor_display_int(0, 8, left_distance);
  lcd_monitor_display_int(1, 8, right_distance);

  if (left_distance < 50 && right_distance < 50) {
    currentDriveState = AUTO_STATE_5;
  } else if (left_distance < right_distance) {
    currentDriveState = AUTO_STATE_3;
  } else {
    currentDriveState = AUTO_STATE_4;
  }

  startTime = 0;
  t1 = false;
  t2 = false;
}

void update_wheels() {
  wheels_update();

  unsigned int dist = distance_sensor_read();

  int go_straight_lspeed = 100;
  int go_straight_rspeed = 180;
  int rotate_speed = 200;

  switch (currentDriveState) {
    case SQUARE_STATE_1:
      forward(go_straight_lspeed, go_straight_rspeed, 100, SQUARE_STATE_2);
      break;
    case SQUARE_STATE_2:
      right(rotate_speed, ROT_90_TICKS, SQUARE_STATE_1);
      break;
    case TRIANGLE_STATE_1:
      forward(go_straight_lspeed, go_straight_rspeed, 100, TRIANGLE_STATE_2);
      break;
    case TRIANGLE_STATE_2:
      left(rotate_speed, 40, TRIANGLE_STATE_1);
      break;
    case AUTO_STATE_1:
      forward_until1(go_straight_lspeed, go_straight_rspeed, dist, OBSTACLE_DIST, AUTO_STATE_2);
      break;
    case AUTO_STATE_2:
      check_neighbourhood();
      break;
    case AUTO_STATE_3:
      servo_set(90);
      delay(50);
      left(rotate_speed, ROT_90_TICKS, AUTO_STATE_1);
      break;
    case AUTO_STATE_4:
      servo_set(90);
      delay(50);
      right(rotate_speed, ROT_90_TICKS - 5, AUTO_STATE_1);
      break;
    case AUTO_STATE_5:
      servo_set(90);
      delay(50);
      right(rotate_speed, ROT_180_TICKS, AUTO_STATE_1);
      break;
    case AUTO_STATE_6:
      forward_until2(go_straight_lspeed, go_straight_rspeed, dist, OBSTACLE_DIST, AUTO_STATE_8);
      break;
    case AUTO_STATE_7:
      forward_until2(go_straight_lspeed, go_straight_rspeed, dist, OBSTACLE_DIST, AUTO_STATE_9);
      break;
    case AUTO_STATE_8:
      right(rotate_speed, ROT_90_TICKS, AUTO_STATE_10);
      break;
    case AUTO_STATE_9:
      left(rotate_speed, ROT_90_TICKS, AUTO_STATE_11);
      break;
    case AUTO_STATE_10:
      forward_until2(go_straight_lspeed, go_straight_rspeed, dist, OBSTACLE_DIST, AUTO_STATE_12);
      break;
    case AUTO_STATE_11:
      forward_until2(go_straight_lspeed, go_straight_rspeed, dist, OBSTACLE_DIST, AUTO_STATE_13);
      break;
    case AUTO_STATE_12:
      right(rotate_speed, ROT_90_TICKS, AUTO_STATE_14);
      break;
    case AUTO_STATE_13:
      left(rotate_speed, ROT_90_TICKS, AUTO_STATE_15);
      break;
    case AUTO_STATE_14:
      forward(go_straight_lspeed, go_straight_rspeed, obstacle_length, AUTO_STATE_16);
      break;
    case AUTO_STATE_15:
      forward(go_straight_lspeed, go_straight_rspeed, obstacle_length, AUTO_STATE_17);
      break;
    case AUTO_STATE_16:
      left(rotate_speed, ROT_90_TICKS, AUTO_STATE_1);
      break;
    case AUTO_STATE_17:
      right(rotate_speed, ROT_90_TICKS, AUTO_STATE_1);
      break;
  }
}

void update_lcd_monitor() {
  lcd_monitor_clear();

  float speeds_sum = wheels_left_speed + wheels_right_speed;
  unsigned int sensor_distance = distance_sensor_read();

  lcd_monitor_display_int(0, 2, wheels_left_speed);
  lcd_monitor_display_int(0, 11, wheels_right_speed);
  lcd_monitor_display_int(0, 8, currentDriveState);
  lcd_monitor_display_int(1, 1, wheels_left_travelled_ticks);
  lcd_monitor_display_int(1, 12, wheels_right_travelled_ticks);
  lcd_monitor_display_int(1, 8, sensor_distance);

  // if(speeds_sum == 0)
  // {
  //   lcd_monitor_display_special_character(0, 8, LCD_STOP_ANIMATION, animation_frame_index);
  //   animation_frame_index = (animation_frame_index + 1) % LCD_FRAMES_NUMBER;
  // }
  // else if(speeds_sum > 0)
  // {
  //   lcd_monitor_display_special_character(0, 8, LCD_FORWARD_ANIMATION, animation_frame_index);
  //   animation_frame_index = (animation_frame_index + 1) % LCD_FRAMES_NUMBER;
  // }
  // else
  // {
  //   lcd_monitor_display_special_character(0, 8, LCD_BACKWARD_ANIMATION, animation_frame_index);
  //   animation_frame_index = (animation_frame_index + 1) % LCD_FRAMES_NUMBER;
  // }
}

void update_buzzer() {
  float speeds_sum = wheels_left_speed + wheels_right_speed;

  if (speeds_sum < 0) {
    buzzer_play(-speeds_sum * 100);
  } else {
    buzzer_stop();
  }
}

// void update_remote()
// {
//   if (ir_receiver.decode()) {
//     if(ir_receiver.decodedIRData.decodedRawData == IR_RECEIVER_FORWARD_CHAR)
//     {
//       wheels_go_distance(50, 50);
//     }
//     else if(ir_receiver.decodedIRData.decodedRawData == IR_RECEIVER_BACKWARD_CHAR)
//     {
//       wheels_go_distance(-50, -50);
//     }

//     ir_receiver.resume();
//   }
// }

void update_distance_sensor() {
  distance_sensor_unit_read();
}

Ticker wheels_ticker(200, update_wheels);
Ticker lcd_monitor_ticker(750, update_lcd_monitor);
Ticker buzzer_ticker(1000, update_buzzer);
Ticker distance_sensor_ticker(50, update_distance_sensor);
// Ticker remote_ticker(300, update_remote);

void setup() {
  Serial.begin(9600);

  wheels_initialize();
  lcd_monitor_initialize();

  buzzer_initialize();
  servo_initialize();
  distance_sensor_initialize();

  servo_set(90);
  delay(1000);

  // ir_receiver.enableIRIn();

  for (int i = 0; i < 5; i++) {
    update_distance_sensor();
    delay(100);
  }
}

void loop() {
  // remote_ticker.check();
  distance_sensor_ticker.check();
  lcd_monitor_ticker.check();
  wheels_ticker.check();
  // buzzer_ticker.check();
}
