#include "main.h"
 unsigned char DAY_1 = 0b10101000;//ПН
 unsigned char DAY_2 = 0b01001000;//ВТ
 unsigned char Weekdays;//переменная дня недели до преобразования
//------------Инициализация микросхемы DC1307---------------
void DS1307init (void){//инициализация микросхемы
        delay_ms(2);
        
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
    I2C_SendByte (0b00000000);//установка секунд 55  01010101
    i2c_stop ();
    
		i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
    I2C_SendByte (0b00000111);//вызов регистра clock out
    I2C_SendByte (0b00010000);//включение делителя частоты 1Hz
    i2c_stop ();	
}
void digit_out (unsigned char digit, unsigned char str1)//digit - цифра от 1 до 9
//str1- номер строки для вывода, сначала 1 потом 2
{
switch (digit){
    case 0:
LCD_SetPos(str1,0);
sendbyte(0b00000000,1);//0
sendbyte(0b00000001,1);
LCD_SetPos(str1,1);
sendbyte(0b00000010,1);//0
sendbyte(0b00000011,1);
        break;
    case 1:
LCD_SetPos(str1,0);
sendbyte(0b00000001,1);//1
sendbyte(0b00100000,1);
LCD_SetPos(str1,1);
sendbyte(0b00000011,1);//1
sendbyte(0b00000110,1);
        break;
    case 2:
LCD_SetPos(str1,0);
sendbyte(0b00000111,1);//2
sendbyte(0b00000100,1);
LCD_SetPos(str1,1);
sendbyte(0b00000101,1);//2
sendbyte(0b00000110,1);
        break;
    case 3:
LCD_SetPos(str1,0);
sendbyte(0b00000111,1);//3
sendbyte(0b00000100,1);
LCD_SetPos(str1,1);
sendbyte(0b00000110,1);//3
sendbyte(0b00000011,1);
        break;
    case 4:
LCD_SetPos(str1,0);
sendbyte(0b00000010,1);//4
sendbyte(0b00000011,1);
LCD_SetPos(str1,1);
sendbyte(0b00100000,1);//4
sendbyte(0b00000001,1);
        break;
    case 5:
LCD_SetPos(str1,0);
sendbyte(0b00000101,1);//5
sendbyte(0b00000111,1);
LCD_SetPos(str1,1);
sendbyte(0b00000110,1);//5
sendbyte(0b00000100,1);
        break;
    case 6:
LCD_SetPos(str1,0);
sendbyte(0b00000000,1);//6
sendbyte(0b00100000,1);
LCD_SetPos(str1,1);
sendbyte(0b00000101,1);//6
sendbyte(0b00000100,1);
        break;
    case 7:
LCD_SetPos(str1,0);
sendbyte(0b00000111,1);//7
sendbyte(0b00000001,1);
LCD_SetPos(str1,1);
sendbyte(0b00100000,1);//7
sendbyte(0b00000001,1);
        break;
    case 8:
LCD_SetPos(str1,0);
sendbyte(0b00000101,1);//8
sendbyte(0b00000100,1);
LCD_SetPos(str1,1);
sendbyte(0b00000010,1);//8
sendbyte(0b00000011,1);        
        break;
    case 9:
LCD_SetPos(str1,0);
sendbyte(0b00000101,1);//9
sendbyte(0b00000100,1);//
LCD_SetPos(str1,1);
sendbyte(0b00000110,1);//9
sendbyte(0b00000011,1);
        break;        
}  
}
//--------------Массивы с сегментами самописных цифр--------
  unsigned char str01[8]={
                0b00011110,
                0b00011110,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000
  };
  unsigned char str02[8]={
                0b00011110,
                0b00011110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110
  };
  unsigned char str03[8]={
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011110,
                0b00011110
  };
  unsigned char str04[8]={
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00011110,
                0b00011110
  };
  unsigned char str05[8]={
                0b00011110,
                0b00011110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00011110,
                0b00011110
  };
  unsigned char str06[8]={
                0b00011111,
                0b00011111,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011111,
                0b00011111
  };
  unsigned char str07[8]={
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00001110,
                0b00001110
  };
  unsigned char str08[8]={
                0b00001111,
                0b00001111,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000
  };
//----------------------------------------------------
//-------------------Пропись дней недели с ПН по ВС---------
void Day_Switch (void){
switch (Weekdays){
    case 0:
DAY_1 = 0b10101000;//П
DAY_2 = 0b01001000;//Н
        break;
    case 1:
DAY_1 = 0b01000010;//В
DAY_2 = 0b01010100;//Т
        break;
    case 2:
DAY_1 = 0b01000011;//С
DAY_2 = 0b01010000;//Р
        break;
    case 3:
DAY_1 = 0b10101011;//Ч
DAY_2 = 0b01010100;//Т
        break;
    case 4:
DAY_1 = 0b10101000;//П
DAY_2 = 0b01010100;//Т
        break;    
    case 5:
DAY_1 = 0b01000011;//С
DAY_2 = 0b10100000;//Б
        break;    
    case 6:
DAY_1 = 0b01000010;//В
DAY_2 = 0b01000011;//С
        break;
    Default:
DAY_1 = 0b11111111;//П
DAY_2 = 0b11111111;//Н
Weekdays = 0;
        break;        
}    
}
//-------------------Вывод надписей-------------------------
void lcd_mask (unsigned char mask){
switch (mask){
    case 0:
sendbyte(0b10100000,1);//Б
sendbyte(0b01111001,1);//у
sendbyte(0b11100011,1);//д
sendbyte(0b10111000,1);//и
sendbyte(0b10111011,1);//л
sendbyte(0b11000100,1);//ь
sendbyte(0b10111101,1);//н
sendbyte(0b10111000,1);//и
sendbyte(0b10111010,1);//к       
break;
    case 1:
sendbyte(0b10101011,1);//Ч
sendbyte(0b01100001,1);//а
sendbyte(0b01100011,1);//с
sendbyte(0b11000011,1);//ы
break;
    case 2:
sendbyte(0b01001101,1);//М
sendbyte(0b10111000,1);//и
sendbyte(0b10111101,1);//н
sendbyte(0b01111001,1);//у
sendbyte(0b10111111,1);//т
sendbyte(0b11000011,1);//ы
break;
	 case 3:
sendbyte(0b11100000,1);//Д
sendbyte(0b01100101,1);//е
sendbyte(0b10111101,1);//н
sendbyte(0b11000100,1);//ь
sendbyte(0b00100000,1);//_
sendbyte(0b10111101,1);//н
sendbyte(0b01100101,1);//е
sendbyte(0b11100011,1);//д
sendbyte(0b01100101,1);//е
sendbyte(0b10111011,1);//л
sendbyte(0b10111000,1);//и
break;
}      
}
