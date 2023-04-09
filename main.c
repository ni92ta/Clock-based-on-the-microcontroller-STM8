/* MAIN.C file
 * ���� �������� 26.03.2023
 �����: ������
 ���� �� ������ STM8S003F3P6
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 #include "stm8s.h"
 #include "I2C.h"
 #include "lcd.h"
 #include "main.h"
 #include "void_function.h"
 /*
 ���-�� ���� - #define TestRam ((unsigned char *)0x0100)
�� � ��������� � ��� ������������� - *(TestRam) = 0xEE
*/
 unsigned char tul = 0;
 unsigned char tuk;
 #define rs GPIOD->ODR//����� RB2//
#define e GPIOD->ODR//�����RB3//
 
#define dev_addrw 0b11010000 //������ 0b10100000
#define dev_addrr 0b11010001 //������ 0b10100001
unsigned int  ms = 0;//���������� ��� ������� ��������
unsigned char tio=0;//���� ������� ������
//----------------------------------------------------------
unsigned char watchdog = 0;
unsigned char *address_1 = (unsigned char*)0x4000;// = 0x4000; ����������� ����� � ��� (EEPROM) ���������� address
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
unsigned char t = 0;//���� ������� ������
unsigned char n;//���� ������� �������
unsigned char alarm_flag;//���� ��������� ����������
unsigned char alarm_number = 0b11010101;// = 0b00110001;
 //unsigned char DAY_1 = 0b10101000;//��
 //unsigned char DAY_2 = 0b01001000;//��
     unsigned char sece;//������� ������
     unsigned char secd;//������� ������
     unsigned char sec;//������� �� ��������������
     unsigned char min;//������ �� ��������������
     //unsigned char min_alar;//������ ���������� �� ��������������
     unsigned char mine;//������� ����� ����� ��������������
     unsigned char mind;//������� ����� ����� �������������� 
     unsigned char hour;//���� �� ��������������
     unsigned char hour_alar;//���� ���������� �� ��������������
     unsigned char min_alar;//������ ���������� �� ��������������
     unsigned char houre;//������� ����� ����� ��������������
     unsigned char hourd;//������� ����� ����� ��������������
     unsigned char houre_alar = 0b00110000;//������� ����� ���������� ����� ��������������
     unsigned char hourd_alar = 0b00110000;//������� ����� ���������� ����� ��������������
     unsigned char minee;//���������� ��� ��������� ����� 
     unsigned char houree;//���������� ��� ��������� �����
     //unsigned char Weekdays;//���������� ��� ������ �� ��������������
//----------------------------------------------------------
void delay_ms(unsigned int set_ms) // �������� � ��
{
   ms = set_ms + 0b11111111;
	 while (ms--);
}
//-------------�������� � �������������---------------------
void delay_us(unsigned int set_us) // �������� � ��
{
	unsigned char  us;
	us = set_us;
	 us = us>>1;
	 us = us>>1;
	 while (us--);
}
//--------------������� �������� �������--------------------
void segment_clear (unsigned char num_seg)
{
	//unsigned char x;
	for (; num_seg > 0; num_seg --){//num_seg-���������� ��������� ��� �������
	sendbyte(0b00100000,1);//������� ��������
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
//--------------------������� �� ��������� � ������� ����� � �����--------------
unsigned char RTC_ConvertFromDec(unsigned char c){//
    unsigned char ch = (0b00001111&c);
    return ch;
}
//-----------------------������������ �������� �����----------------------------
unsigned char vyb_raz (unsigned char u){
    minee = u;
    minee ++; 
    if (u == 0b00001001) minee = 0b00010000;//���� ������ 9 ���������� � ���������� 10
    if (u == 0b00011001) minee = 0b00100000;//���� ������ 19 ���������� � ���������� 20
    if (u == 0b00101001) minee = 0b00110000;//���� ������ 29 ���������� � ���������� 30
    if (u == 0b00111001) minee = 0b01000000;//���� ������ 39 ���������� � ���������� 40
    if (u == 0b01001001) minee = 0b01010000;//���� ������ 49 ���������� � ���������� 50
    if (u == 0b01011001) minee = 0b00000000;//���� ������ 59 �� ��������   
return minee;
}
//-----------------------������������ �������� �����----------------------------
unsigned char vyb_raz_h (unsigned char u){
    houree = u;
    houree ++;
    if (u == 0b00001001) houree = 0b00010000;//���� ������ 9 �� ���������� � ���������� 10
    if (u == 0b00011001) houree = 0b00100000;//���� ������ 19 �� ���������� � ���������� 20
    if (u == 0b00100011) houree = 0b00000000;//���� ������ 23 �� ��������
return houree;
}
//-----------------------�������� ������ � ���������� DS1307--------------------
void sending_data (unsigned char registerr, unsigned char data){//register - ����� �������� ������ 
//data - ������������ ������    
i2c_start ();//�������� ������� �����
    I2C_SendByte (dev_addrw);//����� ������� ���������� - ������
    I2C_SendByte (registerr);//����� �������� �����
    I2C_SendByte (data);//��������� �����
    i2c_stop ();    
}
//-----------------------��������� ������� ������ (��������� ��������)---------- 
void button (unsigned char u,unsigned char i){
  unsigned int butcount=0;
  while((GPIOC->IDR & (1 << 5)) == 0 )
  { 
    if(butcount < 1000)//����� ��� ���������� ��������
    {
      butcount++;
    }
    else
    {   
    if (i == 3){//��������� �����
    vyb_raz (u);
    sending_data (0b00000001, minee);
    } 
    if (i == 4){//��������� �����
    vyb_raz_h (u);
    sending_data (0b00000010, houree);
    }
    if (i == 5){//��������� ��� ������
    Weekdays ++;
    sending_data (0b00000011, Weekdays); 
    }
         if (i == 1){//��������� ���������� - ����
             alarm_2 ++;
                if (alarm_1 == 0b00110010 && alarm_2 == 0b00110100){//���� ���� > 23, �� ����� 00 �����
                 alarm_1 = 0b00110000;
                 alarm_2 = 0b00110000; 
             }
                if (alarm_1 + alarm_2 > 0b01101010){//���� ���� > 19, �� ����� 20 �����
                 alarm_1 = 0b00110010;
                 alarm_2 = 0b00110000; 
             }
             if (alarm_2 > 0b00111001){//���� ���� > 09, �� ����� 10 �����
             alarm_1 = 0b00110001;
             alarm_2 = 0b00110000;
             } 
    } 
          if (i == 2){//��������� ���������� - ������
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
//--------------------------���������/���������� ����������-
void alarm_on (void){
	 unsigned int butcount = 0;
 while((GPIOC->IDR & (1 << 4)) == 0 )
  { 
 if(butcount < 1000)//����� ��� ���������� ��������
    {
      butcount++;
    }
    else
    {
 if(tul == 0){//��������� ����� ��������� ����������
LCD_SetPos(14,0);		
sendbyte(0b11101101,1);
tul = 1;
tuk = 1;
alarm_flag = 0;
alarm_number = 0b00110001;
break;
}
if (tul == 1){//��������� ����� ���������� ����������
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
//--------------------------����� �� LCD--------------------
void clk_out (void){//
    unsigned int butcount = 0;
 while((GPIOC->IDR & (1 << 6)) == 0 )
  { 
 if(butcount < 1000)//����� ��� ���������� ��������
    {
      butcount++;
    }
    else
    {
  t++;
			if (t > 5) t = 0;//��������� ����� ������ ��������� ��� �������� � ���������� ������ ����
      break;     
    }   
    }  
//----------�������� ������� ��������� ���������� 1-----
	if (t == 1){

alarm_on();			
button(min_alar,2);
        LCD_SetPos(0,0);
lcd_mask(0);//����� ����� "���������"
segment_clear (5);//������� ��������
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
lcd_mask (2);//����� ����� "������"
segment_clear (3);//������� ��������
        LCD_SetPos(7,1);
        sendbyte(alarm_1,1);
        sendbyte(alarm_2,1);
				sendbyte(0b00111010,1);
				sendbyte(alarm_3,1);
				sendbyte(alarm_4,1);
segment_clear (4);//������� ��������
//����������������� ����� �������
//*address_3 = alarm_3;//���������� ���������� �� ������ ���  
//*address_4 = alarm_4;//���������� ���������� �� ������ ���	
}
if (t == 2){
	alarm_on();	
        button(hour_alar,1);
        LCD_SetPos(0,0);
lcd_mask(0);//����� ����� "���������"
        LCD_SetPos(0,1);
lcd_mask(1);//����� ����� "����"
segment_clear (2);//������� ��������
        LCD_SetPos(7,1);
        sendbyte(alarm_1,1);
        sendbyte(alarm_2,1);
				sendbyte(0b00111010,1);				
        sendbyte(alarm_3,1);
        sendbyte(alarm_4,1);
				segment_clear (4);//������� ��������
							LCD_SetPos(15,0);
			sendbyte(alarm_number,1);
//����������������� ����� �������				
//*address_1 = alarm_1;//���������� ���������� �� ������ ���
//*address_2 = alarm_2;//���������� ���������� �� ������ ���
    }		
//--------------������ ������� ��������� �����--------------
if (t == 3){
	button(min,3);//����� ������� ��������� ��������
digit_out(hourd, 0);//hourd
digit_out(houre, 2);//houre
LCD_SetPos(4,0);
sendbyte(0b00101110,1);//����� ���������
LCD_SetPos(4,1);
sendbyte(0b11011111,1);//����� ���������
digit_out(mind, 5);
digit_out(mine, 7);
LCD_SetPos(9,0);
segment_clear (7);//������� ��������
LCD_SetPos(9,1);
segment_clear (1);//������� ��������
lcd_mask(2);//����� ����� "������"
    }
//--------------������ ������� ��������� ����-------
    if (t == 4){
       // n = 0;????????????
button(hour,4);//����� ������� ��������� ��������
digit_out(hourd, 0);//hourd
digit_out(houre, 2);//houre		
digit_out(mind, 5);
digit_out(mine, 7);
LCD_SetPos(9,0);
segment_clear (7);//������� ��������
LCD_SetPos(9,1);
segment_clear (1);//������� ��������
lcd_mask (1);//����� ����� "����"				
segment_clear (2);//������� ��������	
    }
    //--------------������ ������� ��������� ��� ������-----
    if (t == 5){
button(Weekdays,5);
LCD_SetPos(0,0);
segment_clear (16);//������� ��������
LCD_SetPos(0,1);
lcd_mask(3);//����� ����� "���� ������"
segment_clear (3);//������� ��������
Day_Switch ();
LCD_SetPos(14,1);
sendbyte(DAY_1,1);
sendbyte(DAY_2,1);
    }

//--------------����� �� �������--------------------
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
sendbyte(0b00101110,1);//����� ���������
LCD_SetPos(9,1);
sendbyte(0b11011111,1);//����� ���������
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
//ODR ������� �������� ������
//IDR ������� ������� ������
//DDR ������� ����������� ������
//��������� ������
  CLK->ECKR |= (1<<0);//��������� HSE ����������
	CLK->SWCR |= (1<<1);//��������� ����������� �������� ������������
while(CLK->ECKR & (1<<1) == 1){}//���� ���������� ��������� ������������
	CLK->CKDIVR = 0b00000001;//�������� ������� ����������� ���������� = 0; �������� ������� ��� -2
  CLK->SWR = 0b10110100;//HSE �������� �������� �������������
while (CLK->SWCR & (1<<1) == 1){}// ���� ���������� ������������
	
	GPIOA->DDR |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//�����
	GPIOA->CR1 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//����� ���� Push-pull
	GPIOA->CR2 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//�������� ������������ - �� 10 ���.
	
	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//�����
	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//����� ���� Push-pull
	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//�������� ������������ - �� 10 ���.
	
	GPIOC->DDR &= ~((1<<5) | (1<<4) | (1<<3));//����
	GPIOC->CR1 |= (1<<5) | (1<<4) | (1<<3);//���� � ������������� ����������  
	GPIOC->CR2 |= (1<<5) | (1<<4) | (1<<3);//�������� ������������ - �� 10 ���. 
	
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
	sendbyte(0b00000001,0);//������� �������
	
	alarm_1 = *address_1;//������������ ���������� alarm_1 ����� � ��� EEPROM
	alarm_2 = *address_2;//������������ ���������� alarm_2 ����� � ��� EEPROM
	alarm_3 = *address_3;//������������ ���������� alarm_3 ����� � ��� EEPROM
	alarm_4 = *address_4;//������������ ���������� alarm_4 ����� � ��� EEPROM
//	p_alarm_flag = *address_5;
	
	while (1){
//	unsigned char reset_alarm_flag;	
	i2c_start();//�������� ������� �����
      I2C_SendByte (dev_addrw);//����� ������� ���������� - ������
      I2C_SendByte (0b00000000);//����� �������� ������ (0b00000010)
      i2c_stop ();//�������� ������� ���� 
      i2c_start ();//�������� ������� �����
      I2C_SendByte (dev_addrr);//����� ������� ���������� - ������
      sec = I2C_ReadByte();//������ ������
      min = I2C_ReadByte();//������ �����
      hour = I2C_ReadByte();//������ �����
      Weekdays = I2C_ReadByte_last();//������ ��� ������
      i2c_stop (); 	
	//--------------������� �������� ������� � ���������� ������--------------------     
      sece = RTC_ConvertFromDec(sec);
      secd = RTC_ConvertFromDecd(sec,0);
      mine = RTC_ConvertFromDec(min);
      mind = RTC_ConvertFromDecd(min,0);
      houre = RTC_ConvertFromDec(hour);
      hourd = RTC_ConvertFromDecd(hour,1);
      Weekdays = RTC_ConvertFromDec(Weekdays);
      hourd_alar = RTC_ConvertFromDec(hour_alar);
      houre_alar = RTC_ConvertFromDecd(hour_alar,1);	
//------������ ������� ds1307 ��� ������ �������------------
		while(watchdog == 0){
    i2c_start ();//�������� ������� �����
    I2C_SendByte (dev_addrw);//����� ������� ���������� - ������
    I2C_SendByte (0b00000000);//����� �������� ������ (0b00000010)
    I2C_SendByte (0b00000000);//��������� ������ 55  01010101
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
//����������������� ����� �������
//*address_5 = alarm_flag;//
clk_out ();
if (hour_alar == hour && alarm_flag == 0){
    if (min_alar == min) GPIOA->ODR |=  (1<<3);//��������� ������� ����������
}
//----------------------------------------------------------
if ((GPIOC->IDR & (1 << 3)) == 0){//���������� ����������
//reset_alarm_flag = mine;
    GPIOA->ODR &=  ~(1<<3);
    alarm_flag = 1;
}
}
}


