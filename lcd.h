#ifndef LCD_H
#define LCD_H
#include "stm8s.h"
#include "main.h"
//#include "I2C.h"

//#define rs GPIOD->ODR//выход RB2//
//#define e GPIOD->ODR//выходRB3//
//--------------------------------------------------------------
//#include <xc.h>
//--------------------------------------------------------------
//void LCD_PORT_init(void);
void LCD_Init(void);
//void LCD_String(char* st);
void LCD_SetPos(unsigned char x, unsigned char y);
void sendbyte(unsigned char c, unsigned char mode);
void sendbyteHalf(unsigned char c);
void LCD_Clear(void);
//--------------------------------------------------------------
#endif /* LCD_H */