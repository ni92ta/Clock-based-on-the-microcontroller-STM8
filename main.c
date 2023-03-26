/* MAIN.C file
 * ���� �������� 26.03.2023
 �����: ������
 ���� �� ������ STM8S003F3P6
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 #include "stm8s.h"
unsigned int  ms = 0;//���������� ��� ������� ��������
unsigned char t=0;//���� ������� ������

void delay_ms(unsigned int set_ms) // �������� � ��
{
   ms = set_ms + 300;
	 while (ms--);
}

main()
{
//ODR ������� �������� ������
//IDR ������� ������� ������
//DDR ������� ����������� ������
//��������� ������
	CLK->CKDIVR = 0b00011111; //�������� ������� = 8
	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3);
	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3);  //����� ���� Push-pull
	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3);  // �������� ������������ - �� 10 ���.
	
	GPIOC->DDR &= ~((1<<4) | (1<<3));//����
	GPIOC->CR1 |= (1<<4) | (1<<3);//���� � ������������� ����������  
	GPIOC->CR2 |= (1<<4) | (1<<3); 
	while (1){
	if ((GPIOC->IDR & (1 << 3)) == 0 ) t = 1;
	if ((GPIOC->IDR & (1 << 4)) == 0 ) t = 0;
	
	if (t == 1){
	GPIOD->ODR |= (1<<5) | (1<<4) | (1<<3);
	delay_ms(1000);
	GPIOD->ODR &=  ~((1<<5) | (1<<4) | (1<<3));
	delay_ms(1000);
	
}

	}
}