//#include <xc.h>
#include "main.h"
#include "I2C.h"
#include "stm8s.h"
//#define _XTAL_FREQ 3579000
//int result = 0;
//-------------------------------------------------------
void i2c_start(void)
{
SCL &= ~(1<<4);//вход SCL
SDA &= ~(1<<5);//вход
//delay_ms(1);
SDA |= (1<<5);//выход
//delay_ms(1);
SCL |= (1<<4);//выход 
}
//-------------------------------------------------------
void i2c_stop (void)
{
SDA |= (1<<5);//выход
//delay_ms(1);
SCL &= ~(1<<4);//вход
//delay_ms(1);
SDA &= ~(1<<5);//вход
//delay_ms(1);
}
//-------------------------------------------------------
void I2C_SendByte (unsigned char d)
{
char x;
//unsigned char b;
for (x = 0; x < 8; x ++) { //передача 8 бит данных
//delay_ms(1);
if (d&0x80) SDA &= ~(1<<5);//вход//логический 0
else SDA |= (1<<5);//выход//логическая 1
//delay_ms(1);;
SCL &= ~(1<<4);//вход
d <<= 1;
//delay_ms(1);
SCL |= (1<<4);}//выход }
//delay_ms(1);
//__delay_us(20);
SDA &= ~(1<<5);//вход //готовимся получить ACK бит
SCL &= ~(1<<4);//вход
//delay_ms(1);
SCL |= (1<<4);//выход
SDA |= (1<<5);//выход
//return result; //Возвращаем значение бита ACK через функцию  
}
//-------------------------------------------------------
int I2C_ReadByte (void)
{   
char i;
int result = 0;
SDA &= ~(1<<5);//вход
for (i=0; i<8; i++) { //передача 8 бит данных 
   result<<=1;
//delay_ms(1);
SCL &= ~(1<<4);//вход
//delay_ms(1);
if (SDA_IN) result |= 1;
//else result |= 0;
SCL |= (1<<4);//выход
}
SDA |= (1<<5);//выход
//delay_ms(1);
SCL &= ~(1<<4);//вход
//delay_ms(1);
SCL |= (1<<4);//выход
//delay_ms(1);
return result; //Возвращаем значение бита ACK через функцию 
}
//-------------------------------------------------------
int I2C_ReadByte_last (void)
{
char i;
int result = 0;
SDA &= ~(1<<5);//вход
for (i=0; i<8; i++) { //передача 8 бит данных
    result<<=1;
//delay_ms(1);
SCL &= ~(1<<4);//вход
//delay_ms(1);
if (SDA_IN) result |=1;
//else result |= 0;
SCL |= (1<<4);//выход
}
SDA &= ~(1<<5);//вход
//delay_ms(1);
SCL &= ~(1<<4);//вход
//delay_ms(1);
SCL |= (1<<4);//выход
//delay_ms(1);
return result; //Возвращаем значение бита ACK через функцию 
}
//-------------------------------------------------------
