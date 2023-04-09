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
 #include "void_function.h"
 /*
 Что-то типа - #define TestRam ((unsigned char *)0x0100)
ну и обращение к ней соответсвенно - *(TestRam) = 0xEE
*/
 unsigned char tul = 0;
 unsigned char tuk;
 #define rs GPIOD->ODR//выход RB2//
#define e GPIOD->ODR//выходRB3//
 
#define dev_addrw 0b11010000 //запись 0b10100000
#define dev_addrr 0b11010001 //чтение 0b10100001
unsigned int  ms = 0;//переменная для функции задержки
unsigned char tio=0;//Флаг нажатия кнопки
//----------------------------------------------------------
unsigned char watchdog = 0;
unsigned char *address_1 = (unsigned char*)0x4000;// = 0x4000; присваиваем адрес в ПЗУ (EEPROM) переменной address
unsigned char *address_2 = (unsigned char*)0x4001;// = 0x4000;
unsigned char *address_3 = (unsigned char*)0x4002;// = 0x4000;
unsigned char *address_4 = (unsigned char*)0x4003;// = 0x4000;
unsigned char *address_5 = (unsigned char*)0x4004;// = 0x4000;
unsigned char alarm_1;//= 0b00110000;
unsigned char alarm_2;// = 0b00110000;
unsigned char alarm_3;// = 0b00110000;
unsigned char alarm_4;// = 0b00110001;
unsigned char *p_alarm_1;
unsigned char *p_alarm_2;
unsigned char *p_alarm_3;
unsigned char *p_alarm_4;
unsigned char *p_alarm_flag;
unsigned char t = 0;//Флаг нажатия кнопки
unsigned char n;//Флаг очистки дисплея
unsigned char alarm_flag;//Флаг включения будильника
unsigned char alarm_number = 0b11010101;// = 0b00110001;
 //unsigned char DAY_1 = 0b10101000;//ПН
 //unsigned char DAY_2 = 0b01001000;//ВТ
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
     //unsigned char Weekdays;//переменная дня недели до преобразования
//----------------------------------------------------------
void delay_ms(unsigned int set_ms) // Задержка в мс
{
   ms = set_ms + 0b11111111;
	 while (ms--);
}
//-------------Задержка в микросекундах---------------------
void delay_us(unsigned int set_us) // Задержка в мс
{
	unsigned char  us;
	us = set_us;
	 us = us>>1;
	 us = us>>1;
	 while (us--);
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
    if(butcount < 1000)//Пауза для подавления дребезга
    {
      butcount++;
    }
    else
    {   
    if (i == 3){//настройка минут
    vyb_raz (u);
    sending_data (0b00000001, minee);
    } 
    if (i == 4){//настройка часов
    vyb_raz_h (u);
    sending_data (0b00000010, houree);
    }
    if (i == 5){//настройка дня недели
    Weekdays ++;
    sending_data (0b00000011, Weekdays); 
    }
         if (i == 1){//настройка будильника - часы
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
          if (i == 2){//настройка будильника - минуты
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
//--------------------------Включение/выключение будильника-
void alarm_on (void){
	 unsigned int butcount = 0;
 while((GPIOC->IDR & (1 << 4)) == 0 )
  { 
 if(butcount < 1000)//Пауза для подавления дребезга
    {
      butcount++;
    }
    else
    {
 if(tul == 0){//установка флага включения будильника
LCD_SetPos(14,0);		
sendbyte(0b11101101,1);
tul = 1;
tuk = 1;
alarm_flag = 0;
alarm_number = 0b00110001;
break;
}
if (tul == 1){//установка флага отключения будильника
LCD_SetPos(14,0);
sendbyte(0b00100000,1);
tul = 0;
tuk = 0;
alarm_flag = 1;
alarm_number = 0b11010101;
}
      break;     
    }   
    } 
}
//--------------------------Вывод на LCD--------------------
void clk_out (void){//
    unsigned int butcount = 0;
 while((GPIOC->IDR & (1 << 6)) == 0 )
  { 
 if(butcount < 1000)//Пауза для подавления дребезга
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
//----------Четвёртое нажатие настройка будильника 1-----
	if (t == 1){

alarm_on();			
button(min_alar,2);
        LCD_SetPos(0,0);
lcd_mask(0);//вывод слова "Будильник"
segment_clear (5);//очистка сегмента
				LCD_SetPos(14,0);
if (tuk == 1){
sendbyte(0b11101101,1);
			LCD_SetPos(15,0);
			sendbyte(alarm_number,1);
}
else{
sendbyte(0b00100000,1);
			LCD_SetPos(15,0);
			sendbyte(alarm_number,1);
}
LCD_SetPos(0,1);
lcd_mask (2);//вывод слова "Минуты"
segment_clear (3);//очистка сегмента
        LCD_SetPos(7,1);
        sendbyte(alarm_1,1);
        sendbyte(alarm_2,1);
				sendbyte(0b00111010,1);
				sendbyte(alarm_3,1);
				sendbyte(alarm_4,1);
segment_clear (4);//очистка сегмента
//РАССКОМЕНТИРОВАТЬ ПОСЛЕ НАЛАДКИ
//*address_3 = alarm_3;//записываем переменную по адресу ПЗУ  
//*address_4 = alarm_4;//записываем переменную по адресу ПЗУ	
}
if (t == 2){
	alarm_on();	
        button(hour_alar,1);
        LCD_SetPos(0,0);
lcd_mask(0);//вывод слова "Будильник"
        LCD_SetPos(0,1);
lcd_mask(1);//вывод слова "Часы"
segment_clear (2);//очистка сегмента
        LCD_SetPos(7,1);
        sendbyte(alarm_1,1);
        sendbyte(alarm_2,1);
				sendbyte(0b00111010,1);				
        sendbyte(alarm_3,1);
        sendbyte(alarm_4,1);
				segment_clear (4);//очистка сегмента
							LCD_SetPos(15,0);
			sendbyte(alarm_number,1);
//РАССКОМЕНТИРОВАТЬ ПОСЛЕ НАЛАДКИ				
//*address_1 = alarm_1;//записываем переменную по адресу ПЗУ
//*address_2 = alarm_2;//записываем переменную по адресу ПЗУ
    }		
//--------------Первое нажатие настройка минут--------------
if (t == 3){
	button(min,3);//вызов функции изменения значения
digit_out(hourd, 0);//hourd
digit_out(houre, 2);//houre
LCD_SetPos(4,0);
sendbyte(0b00101110,1);//вывод двоеточия
LCD_SetPos(4,1);
sendbyte(0b11011111,1);//вывод двоеточия
digit_out(mind, 5);
digit_out(mine, 7);
LCD_SetPos(9,0);
segment_clear (7);//очистка сегмента
LCD_SetPos(9,1);
segment_clear (1);//очистка сегмента
lcd_mask(2);//вывод слова "Минуты"
    }
//--------------Второе нажатие настройка часа-------
    if (t == 4){
       // n = 0;????????????
button(hour,4);//вызов функции изменения значения
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
    if (t == 5){
button(Weekdays,5);
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
sendbyte(0b00101110,1);//вывод двоеточия
LCD_SetPos(9,1);
sendbyte(0b11011111,1);//вывод двоеточия
digit_out(secd, 10);
digit_out(sece, 12);
LCD_SetPos(14,0);
if (tuk == 1)sendbyte(0b11101101,1);
else sendbyte(0b00100000,1);
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
  CLK->ECKR |= (1<<0);//Включение HSE осцилятора
	CLK->SWCR |= (1<<1);//Разрешаем переключить источник тактирования
while(CLK->ECKR & (1<<1) == 1){}//Ждем готовности источника тактирования
	CLK->CKDIVR = 0b00000001;//Делитель частоты внутреннего осцилятора = 0; тактовой частоты ЦПУ -2
  CLK->SWR = 0b10110100;//HSE основной источник синхронизации
while (CLK->SWCR & (1<<1) == 1){}// Ждем готовности переключения
	
	GPIOA->DDR |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Выход
	GPIOA->CR1 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Выход типа Push-pull
	GPIOA->CR2 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц.
	
	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Выход
	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Выход типа Push-pull
	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Скорость переключения - до 10 МГц.
	
	GPIOC->DDR &= ~((1<<5) | (1<<4) | (1<<3));//вход
	GPIOC->CR1 |= (1<<5) | (1<<4) | (1<<3);//вход с подтягивающим резистором  
	GPIOC->CR2 |= (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц. 
	
	FLASH->DUKR = 0b10101110;
	FLASH->DUKR = 0b01010110;
	
	delay_ms(1);
	DS1307init();

	delay_ms(1);
	LCD_Init();
	delay_ms(1);
	sendbyte(0b01000000,0);//sets CGRAM address
  sets_CGRAM (str01);
  sets_CGRAM (str02);
  sets_CGRAM (str03);
  sets_CGRAM (str04);
  sets_CGRAM (str05);
  sets_CGRAM (str06);
  sets_CGRAM (str07);
  sets_CGRAM (str08);
	sendbyte(0b00000001,0);//очистка дисплея
	
	alarm_1 = *address_1;//присваимавем переменной alarm_1 адрес в ПЗУ EEPROM
	alarm_2 = *address_2;//присваимавем переменной alarm_2 адрес в ПЗУ EEPROM
	alarm_3 = *address_3;//присваимавем переменной alarm_3 адрес в ПЗУ EEPROM
	alarm_4 = *address_4;//присваимавем переменной alarm_4 адрес в ПЗУ EEPROM
//	p_alarm_flag = *address_5;
	
	while (1){
//	unsigned char reset_alarm_flag;	
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
//------модуль запуска ds1307 при сбросе питания------------
		while(watchdog == 0){
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
    I2C_SendByte (0b00000000);//установка секунд 55  01010101
    i2c_stop ();
		watchdog = 1;
}
//----------------------------------------------------------
if (Weekdays > 0b00000110) Weekdays = 0;
if (hour == 0 && min == 0 && sec == 0b00000010) alarm_flag = 0;
hour_alar = (((alarm_1 << 4) & 0b00110000)) | (alarm_2 & 0b00001111);// & alarm_2;
min_alar = (((alarm_3 << 4) & 0b00110000)) | (alarm_4 & 0b00001111);// & alarm_2;
/*
GPIOD->ODR |=  (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);
delay_us(10);
GPIOD->ODR &=  ~((1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1));
delay_us(10);*/
//GPIOA->ODR |=  (1<<3);
//Расскоментировать после наладки
//*address_5 = alarm_flag;//
clk_out ();
if (hour_alar == hour && alarm_flag == 0){
    if (min_alar == min) GPIOA->ODR |=  (1<<3);//включение сигнала будилиника
}
//----------------------------------------------------------
if ((GPIOC->IDR & (1 << 3)) == 0){//отключение будильника
//reset_alarm_flag = mine;
    GPIOA->ODR &=  ~(1<<3);
    alarm_flag = 1;
}
}
}


