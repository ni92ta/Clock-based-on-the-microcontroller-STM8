/* MAIN.C file
 * Дата создания 26.03.2023
 Автор: Никита
 Часы на основе STM8S003F3P6
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 #include "stm8s.h"
 #include "I2C.h"
 #include "lcd.h"
 #include "main.h"
 //#include "lcd.c"
 
 #define rs GPIOD->ODR//выход RB2//
#define e GPIOD->ODR//выходRB3//
 
#define dev_addrw 0b11010000 //запись 0b10100000
#define dev_addrr 0b11010001 //чтение 0b10100001
unsigned int  ms = 0;//переменная для функции задержки
unsigned char tio=0;//Флаг нажатия кнопки
//-----------------------------------------------------------
unsigned char alarm_1;//= 0b00110000;
unsigned char alarm_2;// = 0b00110000;
unsigned char alarm_3;// = 0b00110000;
unsigned char alarm_4;// = 0b00110001;
unsigned char t=0;//Флаг нажатия кнопки
unsigned char n;//Флаг очистки дисплея
unsigned char alarm_flag;//Флаг включения будильника
unsigned char alarm_number = 0b00110001;
 unsigned char DAY_1 = 0b10101000;//ПН
 unsigned char DAY_2 = 0b01001000;//ВТ
     unsigned char sece;//единицы секунд
     unsigned char secd;//десятки секунд
     unsigned char sec;//секунды до преобразования
     unsigned char min;//минуты до преобразования
     //unsigned char min_alar;//минуты будильника до преобразования
     unsigned char mine;//единицы минут после преобразования
     unsigned char mind;//десятки минут после преобразования 
     unsigned char hour;//часы до преобразования
     unsigned char hour_alar;//часы будильника до преобразования
     unsigned char min_alar;//минуты будильника до преобразования
     unsigned char houre;//единицы часов после преобразования
     unsigned char hourd;//десятки часов после преобразования
     unsigned char houre_alar = 0b00110000;//единицы часов будильника после преобразования
     unsigned char hourd_alar = 0b00110000;//десятки часов будильника после преобразования     
     unsigned char minee;//переменная для настройки минут 
     unsigned char houree;//переменная для настройки часов
     unsigned char Weekdays;//переменная дня недели до преобразования
//------------------------------------------------------------------------------
void delay_ms(unsigned int set_ms) // Задержка в мс
{
	char x;
   ms = set_ms;
	 //for (x = 100; x>0; x--){
	 while (ms--);
 //}
}
//--------------Очистка сегмента дисплея--------------------
void segment_clear (unsigned char num_seg)
{
	//unsigned char x;
	for (; num_seg > 0; num_seg --){//num_seg-количество сегментов для очистки
	sendbyte(0b00100000,1);//очистка сегмента
	}
}
//----------------------------------------------------------
unsigned char RTC_ConvertFromDecd(unsigned char c,unsigned char v){//
    unsigned char ch;
    if (v == 1){
      c = c>>4;
       ch = (0b00000011&c);   
    }
    if (v == 0){
    ch = (c >> 4);     
    }
    if (v==2){
          c = c>>4;
       ch = (0b00000001&c);  
    }
    return ch; 
}
//--------------------перевод из двоичного в единицы минут и часов--------------
unsigned char RTC_ConvertFromDec(unsigned char c){//
    unsigned char ch = (0b00001111&c);
    return ch;
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
//--------------------Вывод собственных символов на дисплей---------------------
void digit_out (unsigned char digit, unsigned char str1/*, unsigned char str2*/)//digit - цифра от 1 до 9
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
//------------Инициализация микросхемы DC1307---------------
void DS1307init (void){//инициализация микросхемы
       // __delay_ms(10);
			     i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrr);//адрес часовой микросхемы - запись 
    I2C_SendByte (0b00001000);//вызов регистра ROM ОЗУ
    alarm_1 = I2C_SendByte ();//
	  alarm_2 = I2C_SendByte ();//	
    i2c_stop ();
			 
			 
			 
   /*     
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
    I2C_SendByte (0b01010101);//установка секунд 55
    I2C_SendByte (0b01011001);//установка минут 00
    I2C_SendByte (0b00100011);//установка часов 00  0b00100011
    I2C_SendByte (0b00000110);//установка дня ВС
    i2c_stop ();
    */
    
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
    I2C_SendByte (0b00000111);//вызов регистра clock out
    I2C_SendByte (0b00010000);//включение делителя частоты 1Hz
    i2c_stop ();
}
//-----------------------переключение десятков минут----------------------------
unsigned char vyb_raz (unsigned char u){
    minee = u;
    minee ++; 
    if (u == 0b00001001) minee = 0b00010000;//если больше 9 записываем в переменную 10
    if (u == 0b00011001) minee = 0b00100000;//если больше 19 записываем в переменную 20
    if (u == 0b00101001) minee = 0b00110000;//если больше 29 записываем в переменную 30
    if (u == 0b00111001) minee = 0b01000000;//если больше 39 записываем в переменную 40
    if (u == 0b01001001) minee = 0b01010000;//если больше 49 записываем в переменную 50
    if (u == 0b01011001) minee = 0b00000000;//если больше 59 то обнуляем   
return minee;
}
//-----------------------переключение десятков часов----------------------------
unsigned char vyb_raz_h (unsigned char u){
    houree = u;
    houree ++;
    if (u == 0b00001001) houree = 0b00010000;//если больше 9 то записываем в переменную 10
    if (u == 0b00011001) houree = 0b00100000;//если больше 19 то записываем в переменную 20
    if (u == 0b00100011) houree = 0b00000000;//если больше 23 то обнуляем
return houree;
}
//-----------------------Отправка данных в микросхему DS1307--------------------
void sending_data (unsigned char registerr, unsigned char data){//register - адрес регистра данных 
//data - отправляемые данные    
i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (registerr);//вызов регистра минут
    I2C_SendByte (data);//установка минут
    i2c_stop ();    
}
//-----------------------обработка нажатия кнопки (изменение значения)---------- 
void button (unsigned char u,unsigned char i){
  unsigned int butcount=0;
  while((GPIOC->IDR & (1 << 5)) == 0 )
  { 
    if(butcount < 40000)
    {
      butcount++;//Пауза для подавления дребезга
    }
    else
    {   
    if (i == 1){//настройка минут
    vyb_raz (u);
    sending_data (0b00000001, minee);
    } 
    if (i == 2){//настройка часов
    vyb_raz_h (u);
    sending_data (0b00000010, houree);
    }
    if (i == 3){//настройка дня недели
    Weekdays ++;
    sending_data (0b00000011, Weekdays); 
    }
         if (i == 4){//настройка будильника - часы
             alarm_2 ++;
                if (alarm_1 == 0b00110010 && alarm_2 == 0b00110100){//если часы > 23, то равно 00 часов
                 alarm_1 = 0b00110000;
                 alarm_2 = 0b00110000; 
             }
                if (alarm_1 + alarm_2 > 0b01101010){//если часы > 19, то равно 20 часов
                 alarm_1 = 0b00110010;
                 alarm_2 = 0b00110000; 
             }
             if (alarm_2 > 0b00111001){//если часы > 09, то равно 10 часов
             alarm_1 = 0b00110001;
             alarm_2 = 0b00110000;
             } 
    } 
          if (i == 5){//настройка будильника - минуты
            alarm_4 ++;
            if (alarm_4 == 0b00111010) {
                alarm_4 = 0b00110000;
                alarm_3 ++;
            }
            if (alarm_3 > 0b00110101){
                alarm_4 = 0b00110000;
                alarm_3 = 0b00110000;//
            }
          }
 break;    
    }
  }
}
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
//--------------------------Вывод на LCD--------------------
void clk_out (void){//
    unsigned int butcount = 0;
 while((GPIOC->IDR & (1 << 6)) == 0 )
  { 
 if(butcount < 40000)//Подавление дребезга
    {
      butcount++;
    }
    else
    {
  t++;
			if (t > 5) t = 0;//установка флага режима настройки для перехода к следующему пункту меню
      break;     
    }   
    }    
//--------------Первое нажатие настройка минут--------------
if (t == 1){
digit_out(hourd, 0);//hourd
digit_out(houre, 2);//houre
button(min,1);//вызов функции изменения значения
digit_out(mind, 5);
digit_out(mine, 7);
LCD_SetPos(9,0);
segment_clear (7);//очистка сегмента
LCD_SetPos(9,1);
segment_clear (1);//очистка сегмента
lcd_mask(2);//вывод слова "Минуты"
    }
//--------------Второе нажатие настройка часа-------
    if (t == 2){
       // n = 0;????????????
button(hour,2);//вызов функции изменения значения
digit_out(hourd, 0);//hourd
digit_out(houre, 2);//houre		
digit_out(mind, 5);
digit_out(mine, 7);
LCD_SetPos(9,0);
segment_clear (7);//очистка сегмента
LCD_SetPos(9,1);
segment_clear (1);//очистка сегмента
lcd_mask (1);//вывод слова "Часы"				
segment_clear (2);//очистка сегмента	
    }
    //--------------Третье нажатие настройка дня недели-----
    if (t == 3){
button(Weekdays,3);
LCD_SetPos(0,0);
segment_clear (16);//очистка сегмента
LCD_SetPos(0,1);
lcd_mask(3);//вывод слова "День недели"
segment_clear (3);//очистка сегмента
Day_Switch ();
LCD_SetPos(14,1);
sendbyte(DAY_1,1);
sendbyte(DAY_2,1);
    }
//----------Четвёртое нажатие настройка будильника , часы---
    if (t == 4){
button(hour_alar,4);
        LCD_SetPos(0,0);
lcd_mask(0);//вывод слова "Будильник"
//LCD_SetPos(14,0);
//sendbyte(0b11101101,1);
//sendbyte(0b11111111,1);
        LCD_SetPos(0,1);
lcd_mask (1);//вывод слова "Часы"
        LCD_SetPos(5,1);
        sendbyte(alarm_1,1);
        sendbyte(alarm_2,1);
segment_clear (9);//очистка сегмента

    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
    I2C_SendByte (0b00001000);//вызов регистра ROM ОЗУ
    I2C_SendByte (alarm_1);//
	  I2C_SendByte (alarm_2);//	
    i2c_stop ();
     }
//--------------Пятое нажатие настройка будильника, минуты--
    if (t == 5){
        button(alarm_number,5);
        LCD_SetPos(0,0);
lcd_mask(0);//вывод слова "Будильник"
//LCD_SetPos(14,0);
//sendbyte(0b11101101,1);
//sendbyte(0b11111111,1);
        LCD_SetPos(0,1);
lcd_mask(2);//вывод слова "Минуты"
segment_clear (1);//очистка сегмента
        LCD_SetPos(7,1);
        sendbyte(alarm_3,1);
        sendbyte(alarm_4,1);

    }
//--------------Вывод на дисплей--------------------
if (t == 0){
    Day_Switch ();
    if (Weekdays > 0b00000110) Weekdays = 0;
digit_out(hourd, 0);//hourd
digit_out(houre, 2);//houre
LCD_SetPos(4,0);
sendbyte(0b00101110,1);
LCD_SetPos(4,1);
sendbyte(0b11011111,1);
digit_out(mind, 5);
digit_out(mine, 7);
LCD_SetPos(9,0);
sendbyte(0b00101110,1);
LCD_SetPos(9,1);
sendbyte(0b11011111,1);
digit_out(secd, 10);
digit_out(sece, 12);
LCD_SetPos(14,0);
sendbyte(0b11101101,1);
sendbyte(alarm_number,1);
LCD_SetPos(14,1);
sendbyte(DAY_1,1);//
sendbyte(DAY_2,1);//
}
}
//--------------------------------------------------

void sets_CGRAM (char* pot){
unsigned char x;
  for (x = 0; x <= 7; x++){
    sendbyte(pot[x],1);
}
}




main()
{
//ODR регистр выходных данных
//IDR регистр входных данных
//DDR регистр направления данных
//Настройка портов
	CLK->CKDIVR = 0b00000000; //Делитель частоты внутреннего осцилятора = 8; тактовой частоты ЦПУ -128
	
	GPIOA->DDR |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Выход
	GPIOA->CR1 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Выход типа Push-pull
	GPIOA->CR2 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц.
	
	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Выход
	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Выход типа Push-pull
	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Скорость переключения - до 10 МГц.
	
	GPIOC->DDR &= ~((1<<5) | (1<<4) | (1<<3));//вход
	GPIOC->CR1 |= (1<<5) | (1<<4) | (1<<3);//вход с подтягивающим резистором  
	GPIOC->CR2 |= (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц. 
	delay_ms(50);
	DS1307init();

	delay_ms(50);
	LCD_Init();
	delay_ms(50);
	sendbyte(0b01000000,0);//sets CGRAM address
  sets_CGRAM (str01);
  sets_CGRAM (str02);
  sets_CGRAM (str03);
  sets_CGRAM (str04);
  sets_CGRAM (str05);
  sets_CGRAM (str06);
  sets_CGRAM (str07);
  sets_CGRAM (str08);
	sendbyte(0b00000001,0);//очистка дисплея*/
	while (1){
		
	i2c_start();//отправка посылки СТАРТ
      I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
      I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
      i2c_stop ();//отправка посылки СТОП 
      i2c_start ();//отправка посылки СТАРТ
      I2C_SendByte (dev_addrr);//адрес часовой микросхемы - чтение
      sec = I2C_ReadByte();//чтение секунд
      min = I2C_ReadByte();//чтение минут
      hour = I2C_ReadByte();//чтение часов
      Weekdays = I2C_ReadByte_last();//чтение дня недели
      i2c_stop (); 	
	//--------------перевод значения времени в десятичный формат--------------------     
      sece = RTC_ConvertFromDec(sec);
      secd = RTC_ConvertFromDecd(sec,0);
      mine = RTC_ConvertFromDec(min);
      mind = RTC_ConvertFromDecd(min,0);
      houre = RTC_ConvertFromDec(hour);
      hourd = RTC_ConvertFromDecd(hour,1);
      Weekdays = RTC_ConvertFromDec(Weekdays);
      hourd_alar = RTC_ConvertFromDec(hour_alar);
      houre_alar = RTC_ConvertFromDecd(hour_alar,1);	
		
	
if (Weekdays > 0b00000110) Weekdays = 0;
if (hour == 0 && min == 0 && sec == 0b00000010) alarm_flag = 0;
hour_alar = (((alarm_1 << 4) & 0b00110000)) | (alarm_2 & 0b00001111);// & alarm_2;
min_alar = (((alarm_3 << 4) & 0b00110000)) | (alarm_4 & 0b00001111);// & alarm_2;

//GPIOA->ODR |=  (1<<3) | (1<<2) | (1<<1);
clk_out ();
if (hour_alar == hour && alarm_flag == 0){
    if (min_alar == min) GPIOA->ODR |=  (1<<3);
}

if ((GPIOC->IDR & (1 << 3)) == 0){//отключение будильника
    GPIOA->ODR &=  ~(1<<3);
    alarm_flag = 1;
}


		
	/*if ((GPIOC->IDR & (1 << 3)) == 0 ) tio = 1;
	if ((GPIOC->IDR & (1 << 4)) == 0 ) tio = 0;
	if (tio == 0) GPIOA->ODR |=  (1<<3);
	if (tio == 1){
	GPIOD->ODR |= (1<<5) | (1<<4) | (1<<3);
	delay_ms(22);
	GPIOD->ODR &=  ~((1<<5) | (1<<4) | (1<<3));
	delay_ms(22);
	GPIOA->ODR &=  ~(1<<3);	
}*/

	}
}


/*
//-----------------------------------------------------------
__STATIC_INLINE void Delay_us (uint32_t __IO us) //Функция задержки в микросекундах us
{
us *=(SystemCoreClock/1000000)/5;
	while(us--);
}


	if ((GPIOC->IDR & (1 << 3)) == 0 ) t = 1;
	if ((GPIOC->IDR & (1 << 4)) == 0 ) t = 0;
	if (t == 0) GPIOA->ODR |=  (1<<3);
	if (t == 1){
	GPIOD->ODR |= (1<<5) | (1<<4) | (1<<3);
	delay_ms(1000);
	GPIOD->ODR &=  ~((1<<5) | (1<<4) | (1<<3));
	delay_ms(1000);
	GPIOA->ODR &=  ~(1<<3);	
}
*/