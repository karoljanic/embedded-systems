#ifndef LCD_MONITOR_H
#define LCD_MONITOR_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS               0x27
#define LCD_COLS                  16
#define LCD_ROWS                  2

#define LCD_ANIMATIONS_NUMBER     3
#define LCD_FRAMES_NUMBER         4

#define LCD_STOP_ANIMATION        0
#define LCD_FORWARD_ANIMATION     1
#define LCD_BACKWARD_ANIMATION    2


static LiquidCrystal_I2C lcd_monitor(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

void lcd_monitor_initialize();
void lcd_monitor_clear();
void lcd_monitor_display_int(uint8_t row, uint8_t col, int value);
void lcd_monitor_display_float(uint8_t row, uint8_t col, float value);
void lcd_monitor_display_special_character(uint8_t row, uint8_t col, uint8_t animation_index, uint8_t frame_index);

#endif // LCD_MONITOR_H
