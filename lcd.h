#ifndef LCD_H
#define LCD_H
#include "stm8s.h"
#include "main.h"
//----------------------------------------------------------
void LCD_Init(void);
void LCD_SetPos(unsigned char x, unsigned char y);
void sendbyte(unsigned char c, unsigned char mode);
void sendbyteHalf(unsigned char c);
void LCD_Clear(void);
//----------------------------------------------------------
#endif /* LCD_H */