#include "lcd-monitor.h"

static uint8_t animations_frames
[LCD_ANIMATIONS_NUMBER][LCD_FRAMES_NUMBER][8] =
{
  {
    {
      0b00000,
      0b00000,
      0b00100,
      0b01110,
      0b00100,
      0b00000,
      0b00000,
      0b00000,
    },
    {
      0b00000,
      0b00000,
      0b01110,
      0b01110,
      0b01110,
      0b00000,
      0b00000,
      0b00000,
    },
    {
      0b00000,
      0b01110,
      0b11111,
      0b11111,
      0b11111,
      0b01110,
      0b00000,
      0b00000,
    },
    {
      0b00000,
      0b11111,
      0b11111,
      0b11111,
      0b11111,
      0b11111,
      0b00000,
      0b00000,
    }
  },
  {
    {
      0b00100,
      0b01110,
      0b01110,
      0b11111,
      0b11111,
      0b00100,
      0b00100,
      0b00100
    },
    {
      0b01110,
      0b11111,
      0b11111,
      0b00100,
      0b00100,
      0b00100,
      0b00000,
      0b00000
    },
    {
      0b11111,
      0b00100,
      0b00100,
      0b00100,
      0b00000,
      0b00000,
      0b00000,
      0b00000
    },
    {
      0b00100,
      0b00100,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000
    }
  },
  {
    {
      0b00100,
      0b00100,
      0b00100,
      0b11111,
      0b11111,
      0b01110,
      0b01110,
      0b00100
    },
    {
      0b00000,
      0b00000,
      0b00100,
      0b00100,
      0b00100,
      0b11111,
      0b11111,
      0b01110,
    },
    {
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00100,
      0b00100,
      0b00100,
      0b11111,
    },
    {
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00000,
      0b00100,
      0b00100,
    }
  }
};

void lcd_monitor_initialize()
{
  lcd_monitor.init();                     
  lcd_monitor.backlight();
}

void lcd_monitor_clear()
{
  lcd_monitor.clear();
}

void lcd_monitor_display_int(uint8_t row, uint8_t col, int value)
{
  lcd_monitor.setCursor(col, row);
  lcd_monitor.print(value);
}

void lcd_monitor_display_float(uint8_t row, uint8_t col, float value)
{
  lcd_monitor.setCursor(col, row);
  lcd_monitor.print(value);
}

void lcd_monitor_display_special_character(uint8_t row, uint8_t col, uint8_t animation_index, uint8_t frame_index)
{
  lcd_monitor.createChar(0, animations_frames[animation_index][frame_index]);
  lcd_monitor.setCursor(col, row);
  lcd_monitor.write(0);
}
