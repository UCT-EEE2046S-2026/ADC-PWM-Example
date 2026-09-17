#include "lcd.h"
#include "stm32f0xx.h"

#define EN_PORT GPIOC
#define EN_PIN	15

#define RS_PORT GPIOC
#define RS_PIN	14

#define D7_PORT GPIOA
#define D7_PIN	15

#define D6_PORT GPIOA
#define D6_PIN	12

#define D5_PORT GPIOB
#define D5_PIN	9

#define D4_PORT GPIOB
#define D4_PIN	8

void Init_LCD_GPIO(void) {
	// Enable GPIO clocks for the ports used
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;

	// Set the pins as output
	GPIOA->MODER |= GPIO_MODER_MODER15_0 | GPIO_MODER_MODER12_0; // D7 and D6 pins
	GPIOB->MODER |= GPIO_MODER_MODER9_0 | GPIO_MODER_MODER8_0;	 // D5 and D4 pins
	GPIOC->MODER |= GPIO_MODER_MODER15_0 | GPIO_MODER_MODER14_0; // EN and RS pins
}

LCD_Init_t lcd_init = {
	.delay_ms		  = Delay_ms,
	.set_E_pin		  = lcd_set_e_pin,
	.set_RS_pin		  = lcd_set_rs_pin,
	.set_DB0_DB7_pins = lcd_set_DB0_DB7_pins,
	.pin_mode		  = LCD_4BIT_MODE,
	.line_mode		  = LCD_2LINE,
	.font_size		  = LCD_5x8_DOTS
};

void pin_set(GPIO_TypeDef *port, uint32_t pin, uint8_t state) {
	if (state) {
		port->ODR |= (1U << pin); // Set the pin
	} else {
		port->ODR &= ~(1U << pin); // Clear the pin
	}
}

void lcd_set_e_pin(uint8_t state) {
	pin_set(EN_PORT, EN_PIN, state);
}

void lcd_set_rs_pin(uint8_t state) {
	pin_set(RS_PORT, RS_PIN, state);
}

void lcd_set_DB0_DB7_pins(uint8_t data) {
	pin_set(D4_PORT, D4_PIN, (data >> 4) & 0x01);
	pin_set(D5_PORT, D5_PIN, (data >> 5) & 0x01);
	pin_set(D6_PORT, D6_PIN, (data >> 6) & 0x01);
	pin_set(D7_PORT, D7_PIN, (data >> 7) & 0x01);
}
