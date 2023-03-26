/* MAIN.C file
 * Дата создания 26.03.2023
 Автор: Никита
 Часы на основе STM8S003F3P6
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 #include "stm8s.h"
 #include "I2C.h"
 
#define dev_addrw 0b11010000 //запись 0b10100000
#define dev_addrr 0b11010001 //чтение 0b10100001
unsigned int  ms = 0;//переменная для функции задержки
unsigned char tio=0;//Флаг нажатия кнопки
//-----------------------------------------------------------
unsigned char alarm_1 = 0b00110000;
unsigned char alarm_2 = 0b00110000;
unsigned char alarm_3 = 0b00110000;
unsigned char alarm_4 = 0b00110001;
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
   ms = set_ms + 300;
	 while (ms--);
}
void DS1307init (void){//инициализация микросхемы
       // __delay_ms(10);
        
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
    I2C_SendByte (0b01010101);//установка секунд 55
    I2C_SendByte (0b01011001);//установка минут 00
    I2C_SendByte (0b00100011);//установка часов 00  0b00100011
    I2C_SendByte (0b00000110);//установка дня ВС
    i2c_stop ();
    
    
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
    I2C_SendByte (0b00000111);//вызов регистра clock out
    I2C_SendByte (0b00010000);//включение делителя частоты 1Hz
    i2c_stop ();
}
//------------------------------------------------------------------------------
main()
{
//ODR регистр выходных данных
//IDR регистр входных данных
//DDR регистр направления данных
//Настройка портов
	CLK->CKDIVR = 0b00011111; //Делитель частоты внутреннего осцилятора = 8; тактовой частоты ЦПУ -128
	
	GPIOA->DDR |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//Выход
	GPIOA->CR1 |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//Выход типа Push-pull
	GPIOA->CR2 |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц.
	
	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//Выход
	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//Выход типа Push-pull
	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц.
	
	GPIOC->DDR &= ~((1<<4) | (1<<3));//вход
	GPIOC->CR1 |= (1<<4) | (1<<3);//вход с подтягивающим резистором  
	GPIOC->CR2 |= (1<<4) | (1<<3);//Скорость переключения - до 10 МГц. 
	
	DS1307init();
	while (1){
		DS1307init();
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
		
		
		
		
	if ((GPIOC->IDR & (1 << 3)) == 0 ) tio = 1;
	if ((GPIOC->IDR & (1 << 4)) == 0 ) tio = 0;
	if (tio == 0) GPIOA->ODR |=  (1<<3);
	if (tio == 1){
	GPIOD->ODR |= (1<<5) | (1<<4) | (1<<3);
	delay_ms(1000);
	GPIOD->ODR &=  ~((1<<5) | (1<<4) | (1<<3));
	delay_ms(1000);
	GPIOA->ODR &=  ~(1<<3);	
}

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