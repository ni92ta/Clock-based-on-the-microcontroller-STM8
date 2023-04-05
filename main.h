#ifndef MAIN_H
#define MAIN_H
//--------------------------------------------------------------
//#define _XTAL_FREQ 3579000
//#include <xc.h>


//--------------------------------------------------------------
#include "lcd.h"
#include "I2C.h"
#include "stm8s.h"
//#include "void_function.h"
void delay_ms(unsigned int set_ms);
void LCD_Init();
//void Day_Switch (void);
//void lcd_mask (unsigned char mask);
 //unsigned char DAY_1 = 0b10101000;//ПН
 //unsigned char DAY_2 = 0b01001000;//ВТ
 //unsigned char Weekdays;//переменная дня недели до преобразования
//--------------------------------------------------------------
#endif /* MAIN_H */