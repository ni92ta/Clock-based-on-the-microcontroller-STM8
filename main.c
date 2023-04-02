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
 //#include "lcd.c"
 
 #define rs GPIOD->ODR//����� RB2//
#define e GPIOD->ODR//�����RB3//
 
#define dev_addrw 0b11010000 //������ 0b10100000
#define dev_addrr 0b11010001 //������ 0b10100001
unsigned int  ms = 0;//���������� ��� ������� ��������
unsigned char tio=0;//���� ������� ������
//-----------------------------------------------------------
unsigned char alarm_1;//= 0b00110000;
unsigned char alarm_2;// = 0b00110000;
unsigned char alarm_3;// = 0b00110000;
unsigned char alarm_4;// = 0b00110001;
unsigned char t=0;//���� ������� ������
unsigned char n;//���� ������� �������
unsigned char alarm_flag;//���� ��������� ����������
unsigned char alarm_number = 0b00110001;
 unsigned char DAY_1 = 0b10101000;//��
 unsigned char DAY_2 = 0b01001000;//��
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
     unsigned char Weekdays;//���������� ��� ������ �� ��������������
//------------------------------------------------------------------------------
void delay_ms(unsigned int set_ms) // �������� � ��
{
	char x;
   ms = set_ms;
	 //for (x = 100; x>0; x--){
	 while (ms--);
 //}
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
//--------------������� � ���������� ���������� ����--------
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
//--------------------����� ����������� �������� �� �������---------------------
void digit_out (unsigned char digit, unsigned char str1/*, unsigned char str2*/)//digit - ����� �� 1 �� 9
//str1- ����� ������ ��� ������, ������� 1 ����� 2
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
//------------������������� ���������� DC1307---------------
void DS1307init (void){//������������� ����������
       // __delay_ms(10);
			     i2c_start ();//�������� ������� �����
    I2C_SendByte (dev_addrr);//����� ������� ���������� - ������ 
    I2C_SendByte (0b00001000);//����� �������� ROM ���
    alarm_1 = I2C_SendByte ();//
	  alarm_2 = I2C_SendByte ();//	
    i2c_stop ();
			 
			 
			 
   /*     
    i2c_start ();//�������� ������� �����
    I2C_SendByte (dev_addrw);//����� ������� ���������� - ������
    I2C_SendByte (0b00000000);//����� �������� ������ (0b00000010)
    I2C_SendByte (0b01010101);//��������� ������ 55
    I2C_SendByte (0b01011001);//��������� ����� 00
    I2C_SendByte (0b00100011);//��������� ����� 00  0b00100011
    I2C_SendByte (0b00000110);//��������� ��� ��
    i2c_stop ();
    */
    
    i2c_start ();//�������� ������� �����
    I2C_SendByte (dev_addrw);//����� ������� ���������� - ������ 
    I2C_SendByte (0b00000111);//����� �������� clock out
    I2C_SendByte (0b00010000);//��������� �������� ������� 1Hz
    i2c_stop ();
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
    if(butcount < 40000)
    {
      butcount++;//����� ��� ���������� ��������
    }
    else
    {   
    if (i == 1){//��������� �����
    vyb_raz (u);
    sending_data (0b00000001, minee);
    } 
    if (i == 2){//��������� �����
    vyb_raz_h (u);
    sending_data (0b00000010, houree);
    }
    if (i == 3){//��������� ��� ������
    Weekdays ++;
    sending_data (0b00000011, Weekdays); 
    }
         if (i == 4){//��������� ���������� - ����
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
          if (i == 5){//��������� ���������� - ������
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
//-------------------������� ���� ������ � �� �� ��---------
void Day_Switch (void){
switch (Weekdays){
    case 0:
DAY_1 = 0b10101000;//�
DAY_2 = 0b01001000;//�
        break;
    case 1:
DAY_1 = 0b01000010;//�
DAY_2 = 0b01010100;//�
        break;
    case 2:
DAY_1 = 0b01000011;//�
DAY_2 = 0b01010000;//�
        break;
    case 3:
DAY_1 = 0b10101011;//�
DAY_2 = 0b01010100;//�
        break;
    case 4:
DAY_1 = 0b10101000;//�
DAY_2 = 0b01010100;//�
        break;    
    case 5:
DAY_1 = 0b01000011;//�
DAY_2 = 0b10100000;//�
        break;    
    case 6:
DAY_1 = 0b01000010;//�
DAY_2 = 0b01000011;//�
        break;
    Default:
DAY_1 = 0b11111111;//�
DAY_2 = 0b11111111;//�
Weekdays = 0;
        break;        
}    
}
//-------------------����� ��������-------------------------
void lcd_mask (unsigned char mask){
switch (mask){
    case 0:
sendbyte(0b10100000,1);//�
sendbyte(0b01111001,1);//�
sendbyte(0b11100011,1);//�
sendbyte(0b10111000,1);//�
sendbyte(0b10111011,1);//�
sendbyte(0b11000100,1);//�
sendbyte(0b10111101,1);//�
sendbyte(0b10111000,1);//�
sendbyte(0b10111010,1);//�       
break;
    case 1:
sendbyte(0b10101011,1);//�
sendbyte(0b01100001,1);//�
sendbyte(0b01100011,1);//�
sendbyte(0b11000011,1);//�
break;
    case 2:
sendbyte(0b01001101,1);//�
sendbyte(0b10111000,1);//�
sendbyte(0b10111101,1);//�
sendbyte(0b01111001,1);//�
sendbyte(0b10111111,1);//�
sendbyte(0b11000011,1);//�
break;
	 case 3:
sendbyte(0b11100000,1);//�
sendbyte(0b01100101,1);//�
sendbyte(0b10111101,1);//�
sendbyte(0b11000100,1);//�
sendbyte(0b00100000,1);//_
sendbyte(0b10111101,1);//�
sendbyte(0b01100101,1);//�
sendbyte(0b11100011,1);//�
sendbyte(0b01100101,1);//�
sendbyte(0b10111011,1);//�
sendbyte(0b10111000,1);//�
break;
}      
}
//--------------------------����� �� LCD--------------------
void clk_out (void){//
    unsigned int butcount = 0;
 while((GPIOC->IDR & (1 << 6)) == 0 )
  { 
 if(butcount < 40000)//���������� ��������
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
//--------------������ ������� ��������� �����--------------
if (t == 1){
digit_out(hourd, 0);//hourd
digit_out(houre, 2);//houre
button(min,1);//����� ������� ��������� ��������
digit_out(mind, 5);
digit_out(mine, 7);
LCD_SetPos(9,0);
segment_clear (7);//������� ��������
LCD_SetPos(9,1);
segment_clear (1);//������� ��������
lcd_mask(2);//����� ����� "������"
    }
//--------------������ ������� ��������� ����-------
    if (t == 2){
       // n = 0;????????????
button(hour,2);//����� ������� ��������� ��������
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
    if (t == 3){
button(Weekdays,3);
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
//----------�������� ������� ��������� ���������� , ����---
    if (t == 4){
button(hour_alar,4);
        LCD_SetPos(0,0);
lcd_mask(0);//����� ����� "���������"
//LCD_SetPos(14,0);
//sendbyte(0b11101101,1);
//sendbyte(0b11111111,1);
        LCD_SetPos(0,1);
lcd_mask (1);//����� ����� "����"
        LCD_SetPos(5,1);
        sendbyte(alarm_1,1);
        sendbyte(alarm_2,1);
segment_clear (9);//������� ��������

    i2c_start ();//�������� ������� �����
    I2C_SendByte (dev_addrw);//����� ������� ���������� - ������ 
    I2C_SendByte (0b00001000);//����� �������� ROM ���
    I2C_SendByte (alarm_1);//
	  I2C_SendByte (alarm_2);//	
    i2c_stop ();
     }
//--------------����� ������� ��������� ����������, ������--
    if (t == 5){
        button(alarm_number,5);
        LCD_SetPos(0,0);
lcd_mask(0);//����� ����� "���������"
//LCD_SetPos(14,0);
//sendbyte(0b11101101,1);
//sendbyte(0b11111111,1);
        LCD_SetPos(0,1);
lcd_mask(2);//����� ����� "������"
segment_clear (1);//������� ��������
        LCD_SetPos(7,1);
        sendbyte(alarm_3,1);
        sendbyte(alarm_4,1);

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
//ODR ������� �������� ������
//IDR ������� ������� ������
//DDR ������� ����������� ������
//��������� ������
	CLK->CKDIVR = 0b00000000; //�������� ������� ����������� ���������� = 8; �������� ������� ��� -128
	
	GPIOA->DDR |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//�����
	GPIOA->CR1 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//����� ���� Push-pull
	GPIOA->CR2 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//�������� ������������ - �� 10 ���.
	
	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//�����
	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//����� ���� Push-pull
	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//�������� ������������ - �� 10 ���.
	
	GPIOC->DDR &= ~((1<<5) | (1<<4) | (1<<3));//����
	GPIOC->CR1 |= (1<<5) | (1<<4) | (1<<3);//���� � ������������� ����������  
	GPIOC->CR2 |= (1<<5) | (1<<4) | (1<<3);//�������� ������������ - �� 10 ���. 
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
	sendbyte(0b00000001,0);//������� �������*/
	while (1){
		
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
		
	
if (Weekdays > 0b00000110) Weekdays = 0;
if (hour == 0 && min == 0 && sec == 0b00000010) alarm_flag = 0;
hour_alar = (((alarm_1 << 4) & 0b00110000)) | (alarm_2 & 0b00001111);// & alarm_2;
min_alar = (((alarm_3 << 4) & 0b00110000)) | (alarm_4 & 0b00001111);// & alarm_2;

//GPIOA->ODR |=  (1<<3) | (1<<2) | (1<<1);
clk_out ();
if (hour_alar == hour && alarm_flag == 0){
    if (min_alar == min) GPIOA->ODR |=  (1<<3);
}

if ((GPIOC->IDR & (1 << 3)) == 0){//���������� ����������
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
__STATIC_INLINE void Delay_us (uint32_t __IO us) //������� �������� � ������������� us
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