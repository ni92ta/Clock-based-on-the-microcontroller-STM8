/* MAIN.C file
 * ���� �������� 26.03.2023
 �����: ������
 ���� �� ������ STM8S003F3P6
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 #include "stm8s.h"
 #include "I2C.h"
 
#define dev_addrw 0b11010000 //������ 0b10100000
#define dev_addrr 0b11010001 //������ 0b10100001
unsigned int  ms = 0;//���������� ��� ������� ��������
unsigned char tio=0;//���� ������� ������
//-----------------------------------------------------------
unsigned char alarm_1 = 0b00110000;
unsigned char alarm_2 = 0b00110000;
unsigned char alarm_3 = 0b00110000;
unsigned char alarm_4 = 0b00110001;
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
   ms = set_ms + 300;
	 while (ms--);
}
void DS1307init (void){//������������� ����������
       // __delay_ms(10);
        
    i2c_start ();//�������� ������� �����
    I2C_SendByte (dev_addrw);//����� ������� ���������� - ������
    I2C_SendByte (0b00000000);//����� �������� ������ (0b00000010)
    I2C_SendByte (0b01010101);//��������� ������ 55
    I2C_SendByte (0b01011001);//��������� ����� 00
    I2C_SendByte (0b00100011);//��������� ����� 00  0b00100011
    I2C_SendByte (0b00000110);//��������� ��� ��
    i2c_stop ();
    
    
    i2c_start ();//�������� ������� �����
    I2C_SendByte (dev_addrw);//����� ������� ���������� - ������ 
    I2C_SendByte (0b00000111);//����� �������� clock out
    I2C_SendByte (0b00010000);//��������� �������� ������� 1Hz
    i2c_stop ();
}
//------------------------------------------------------------------------------
main()
{
//ODR ������� �������� ������
//IDR ������� ������� ������
//DDR ������� ����������� ������
//��������� ������
	CLK->CKDIVR = 0b00011111; //�������� ������� ����������� ���������� = 8; �������� ������� ��� -128
	
	GPIOA->DDR |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//�����
	GPIOA->CR1 |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//����� ���� Push-pull
	GPIOA->CR2 |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//�������� ������������ - �� 10 ���.
	
	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//�����
	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//����� ���� Push-pull
	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//�������� ������������ - �� 10 ���.
	
	GPIOC->DDR &= ~((1<<4) | (1<<3));//����
	GPIOC->CR1 |= (1<<4) | (1<<3);//���� � ������������� ����������  
	GPIOC->CR2 |= (1<<4) | (1<<3);//�������� ������������ - �� 10 ���. 
	
	DS1307init();
	while (1){
		DS1307init();
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