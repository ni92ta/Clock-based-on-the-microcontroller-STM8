#ifndef MAIN_H
#define MAIN_H
//----------------------------------------------------------
#include "lcd.h"
#include "I2C.h"
#include "stm8s.h"
void delay_ms(unsigned int set_ms);
void delay_us(unsigned int set_us);
void LCD_Init();
//----------------------------------------------------------
#endif /* MAIN_H */