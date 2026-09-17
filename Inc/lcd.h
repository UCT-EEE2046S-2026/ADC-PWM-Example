#ifndef LCD_H
#define LCD_H

#include "LCD_HD44780U.h"

void Delay_ms(uint32_t ms);

void lcd_set_e_pin(uint8_t state);
void lcd_set_rs_pin(uint8_t state);
void lcd_set_DB0_DB7_pins(uint8_t data);

void Init_LCD_GPIO(void);

#endif // LCD_H
