#ifndef I2C_H
#define	I2C_H
#include "stm8s.h"
#define SCL GPIOB->DDR 
#define SDA GPIOB->DDR 
#define SCL_IN GPIOB->IDR & (1 << 4) 
#define SDA_IN GPIOB->IDR & (1 << 5)
#define dev_addrw 0b11010000
#define dev_addrr 0b11010001
//----------------------------------------
void i2c_start(void);
void i2c_stop (void);
void I2C_SendByte (unsigned char d);
int I2C_ReadByte (void);
int I2C_ReadByte_last (void);

#endif	/* I2C_H */