//#include <xc.h>
#include "main.h"
#include "I2C.h"
#include "stm8s.h"
//#define _XTAL_FREQ 3579000
//int result = 0;
//-------------------------------------------------------
void i2c_start(void)
{
SCL &= ~(1<<4);//���� SCL
SDA &= ~(1<<5);//����
//delay_ms(1);
SDA |= (1<<5);//�����
//delay_ms(1);
SCL |= (1<<4);//����� 
}
//-------------------------------------------------------
void i2c_stop (void)
{
SDA |= (1<<5);//�����
//delay_ms(1);
SCL &= ~(1<<4);//����
//delay_ms(1);
SDA &= ~(1<<5);//����
//delay_ms(1);
}
//-------------------------------------------------------
void I2C_SendByte (unsigned char d)
{
char x;
//unsigned char b;
for (x = 0; x < 8; x ++) { //�������� 8 ��� ������
//delay_ms(1);
if (d&0x80) SDA &= ~(1<<5);//����//���������� 0
else SDA |= (1<<5);//�����//���������� 1
//delay_ms(1);;
SCL &= ~(1<<4);//����
d <<= 1;
//delay_ms(1);
SCL |= (1<<4);}//����� }
//delay_ms(1);
//__delay_us(20);
SDA &= ~(1<<5);//���� //��������� �������� ACK ���
SCL &= ~(1<<4);//����
//delay_ms(1);
SCL |= (1<<4);//�����
SDA |= (1<<5);//�����
//return result; //���������� �������� ���� ACK ����� �������  
}
//-------------------------------------------------------
int I2C_ReadByte (void)
{   
char i;
int result = 0;
SDA &= ~(1<<5);//����
for (i=0; i<8; i++) { //�������� 8 ��� ������ 
   result<<=1;
//delay_ms(1);
SCL &= ~(1<<4);//����
//delay_ms(1);
if (SDA_IN) result |= 1;
//else result |= 0;
SCL |= (1<<4);//�����
}
SDA |= (1<<5);//�����
//delay_ms(1);
SCL &= ~(1<<4);//����
//delay_ms(1);
SCL |= (1<<4);//�����
//delay_ms(1);
return result; //���������� �������� ���� ACK ����� ������� 
}
//-------------------------------------------------------
int I2C_ReadByte_last (void)
{
char i;
int result = 0;
SDA &= ~(1<<5);//����
for (i=0; i<8; i++) { //�������� 8 ��� ������
    result<<=1;
//delay_ms(1);
SCL &= ~(1<<4);//����
//delay_ms(1);
if (SDA_IN) result |=1;
//else result |= 0;
SCL |= (1<<4);//�����
}
SDA &= ~(1<<5);//����
//delay_ms(1);
SCL &= ~(1<<4);//����
//delay_ms(1);
SCL |= (1<<4);//�����
//delay_ms(1);
return result; //���������� �������� ���� ACK ����� ������� 
}
//-------------------------------------------------------
