#include "lcd.h"
#include "stm8s.h"
//#include "main.h"
//#include "I2C.h"
//#define _XTAL_FREQ 3579000
//--------------------------------------------------------------
#define rs GPIOD->ODR//����� RB2//
#define e GPIOD->ODR//�����RB3//
//--------------------------------------------------------------
void LCD_delay()
{
int i;
for(i=0;i<19;i++);
}
void sendbyteHalf(unsigned char c)
{
c <<= 4;
GPIOD->ODR &= 0b00001111;//&= 0b00001111;
GPIOD->ODR |= c; //|= c;
e &= ~(1<<5);
delay_ms(50);
e |= (1<<5);
delay_ms(50);
}
//--------------------------------------------------------------
void sendbyte(unsigned char c, unsigned char mode) //
{
unsigned char hc = 0;  
if(mode == 0) rs &= ~(1<<6); 
else rs |= (1<<6);
hc = c >> 4;
sendbyteHalf(hc); 
sendbyteHalf(c);
}
//--------------------------------------------------------------
void LCD_Init()
{
delay_ms(50000);//50ms
  sendbyte(0b00110000, 0);//0b00110000
  delay_ms(4500);//0b00110000
  sendbyte(00110000, 0);//
  delay_ms(4500);
 // sendbyte(0b11000000, 0);//����������������
 delay_ms(200);//����������������
 //sendbyte(0b00000000, 0);//���������
 sendbyte(0b00001111, 0);//0b00001000
  delay_ms(1000);//1ms

sendbyte(0b00001111,0);//0b00001100
//              ||+---1:���������, 0:���������� ������� ������� �������
//              |+----1:���������, 0:���������� �������
//              +-----1:���������, 0:���������� �������
delay_ms(37);

sendbyte(0b00000001,0);//������� �������
delay_ms(2000);
sendbyte(0b00000110,0);//direction left to right
//               |+---1:���������, 0:��������� ����� �������, ������� ������
//               +----1:����������, 0:���������� �������
delay_ms(1000);

sendbyte(0b00000111,0);// increment mode, entire shift on
delay_ms(37);
  
sendbyte(0b00010100,0);
//             |+-----1:����� ������, 0:����� �����
//             +------1:����� �������, 0:����� �������
delay_ms(37);

sendbyte(0b00000010,0);//������� DDRAM � 0
delay_ms(2000);//2ms

sendbyte(0b00000010,0);//������� DDRAM � 0
delay_ms(2000);//2ms

sendbyte(0b01000000,0);//���������� ����� CGRAM � 0
delay_ms(37);

}
//--------------------------------------------------------------
/*
void LCD_Init() //
{
__delay_ms(50); 


sendbyte(0b00110000,0);//on 
__delay_us(37);
       
sendbyte(0b00101000,0);
//            ||+-----1:����� 5*10 �����, 0: 5*8 �����
//            |+------1:��� ������, 0:���� ������
//            +-------1:��������� 8 ���, 0:4 ����
__delay_us(37);
  
sendbyte(0b00001100,0);
//              ||+---1:���������, 0:���������� ������� ������� �������
//              |+----1:���������, 0:���������� �������
//              +-----1:���������, 0:���������� �������
__delay_us(37);

sendbyte(0b00000001,0);//������� �������
//__delay_ms(2);
   
sendbyte(0b00000111,0);// increment mode, entire shift on
__delay_us(37);
  
sendbyte(0b00010100,0);
//             |+-----1:����� ������, 0:����� �����
//             +------1:����� �������, 0:����� �������
__delay_us(37);
  
sendbyte(0b00000110,0);//direction left to right
//               |+---1:���������, 0:��������� ����� �������, ������� ������
//               +----1:����������, 0:���������� �������
__delay_us(37);

sendbyte(0b00000010,0);//������� DDRAM � 0
__delay_ms(2);
  
sendbyte(0b01000000,0);//���������� ����� CGRAM � 0
__delay_us(37);
  
sendbyte(0b10000000,0);//���������� ����� DDRAM � 0
__delay_us(37);
}*/
//--------------------------------------------------------------
void LCD_Clear()
{
  sendbyte(0x01, 0);
  delay_ms(1500);
}
//--------------------------------------------------------------
void LCD_SetPos(unsigned char x, unsigned char y)//
{
switch(y) //
{
case 0:
sendbyte((unsigned char)(x | 0x80),0);//
break;
case 1:
sendbyte((unsigned char)((0x40 + x) | 0x80),0);
break;
}
}
//--------------------------------------------------------------
/*void LCD_String(char* st)//
{
unsigned char i = 0;
while(st[i] != 0) //
{
sendbyte(st[i],1); //
i++;
}
}*/
//--------------------------------------------------------------
/*
 void sendbyte(unsigned char c, unsigned char mode) //
{
PORTB = c; //
if(mode == 0) rs = 0;
else rs = 1;
e = 0;
LCD_delay();
e = 1;
//c=0;
}
//--------------------------------------------------------------
 */
