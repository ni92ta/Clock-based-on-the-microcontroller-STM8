#ifndef MAIN_H
#define MAIN_H
//--------------------------------------------------------------
#define _XTAL_FREQ 3579000
//#include <xc.h>


//--------------------------------------------------------------
#include "lcd.h"
#include "I2C.h"
#include "stm8s.h"
void delay_ms(unsigned int set_ms);
void LCD_Init();
//--------------------------------------------------------------
#endif /* MAIN_H */