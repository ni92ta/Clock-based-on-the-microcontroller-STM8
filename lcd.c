#include "lcd.h"
#include "stm8s.h"
#include "main.h"
//----------------------------------------------------------
#define rs GPIOD->ODR//выход RB2//
#define e GPIOD->ODR//выходRB3//
//----------------------------------------------------------
void LCD_delay()
{
int i;
for(i=0;i<19;i++);
}
//------Запись байта в регистр------------------------------
void sendbyteHalf(unsigned char c)
{
c <<= 1;//Сдвигаем байт значащие биты 0b000XXXX0
GPIOD->ODR &= 0b11100001;//Очищаем регистр МК передачи данных ЖКИ
GPIOD->ODR |= c;//Записываем байт в регистр
e &= ~(1<<5);
delay_ms(5);
e |= (1<<5);
delay_ms(50);
}
//----------------------------------------------------------
void sendbyte(unsigned char c, unsigned char mode)
{
unsigned char hc = 0;  
if(mode == 0) rs &= ~(1<<6); 
else rs |= (1<<6);
hc = c >> 4;//Сдвигаем старшие 4 бита вправо
sendbyteHalf(hc);//Записываем в порт старшие 4 бита 
sendbyteHalf(c);//Записываем в порт младшие 4 бита 
}
//----------------------------------------------------------
void LCD_Init(void)
{
 delay_ms(50);//50ms
  sendbyte(0b00110000, 0);//0b01110000
  delay_ms(5);//
  sendbyte(0b00110000, 0);//0b11110000
  delay_ms(5);
 delay_ms(1);//закомментировано
 sendbyte(0b00001111, 0);//0b00001111
  delay_ms(1);//1ms

sendbyte(0b00001000,0);//0b00001111
//              ||+---1:Включение, 0:Отключение мигания позиции курсора
//              |+----1:Включение, 0:Отключение курсора
//              +-----1:Включение, 0:Отключение дисплея
delay_ms(1);

sendbyte(0b0000001,0);//очистка дисплея
delay_ms(2);
sendbyte(0b00000110,0);//direction left to right
//               |+---1:Разрешить, 0:Запретить сдвиг дисплея, двигать курсор
//               +----1:Приращение, 0:Уменьшение курсора
delay_ms(1);

sendbyte(0b00000111,0);// increment mode, entire shift on
delay_ms(1);
  
sendbyte(0b00010100,0);
//             |+-----1:Сдвиг вправо, 0:Сдвиг влево
//             +------1:Сдвиг дисплея, 0:Сдвиг курсора
delay_ms(1);

sendbyte(0b00000010,0);//Счётчик DDRAM в 0
delay_ms(2);//2ms

sendbyte(0b00000010,0);//Счётчик DDRAM в 0
delay_ms(2);//2ms

sendbyte(0b01000000,0);//Установить адрес CGRAM в 0  0b01000000
delay_ms(1);
}
//--------------------------------------------------------------
void LCD_Clear(void)
{
  sendbyte(0x01, 0);
  delay_ms(2);
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

