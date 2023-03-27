   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.8.1 - 09 Jan 2023
   3                     ; Generator (Limited) V4.5.5 - 08 Nov 2022
  42                     ; 7 void i2c_start(void)
  42                     ; 8 {
  44                     	switch	.text
  45  0000               _i2c_start:
  49                     ; 9 SCL &= ~(1<<4);//���� SCL
  51  0000 72195007      	bres	20487,#4
  52                     ; 10 SDA &= ~(1<<5);//����
  54  0004 721b5007      	bres	20487,#5
  55                     ; 12 SDA |= (1<<5);//�����
  57  0008 721a5007      	bset	20487,#5
  58                     ; 14 SCL |= (1<<4);//����� 
  60  000c 72185007      	bset	20487,#4
  61                     ; 15 }
  64  0010 81            	ret
  87                     ; 17 void i2c_stop (void)
  87                     ; 18 {
  88                     	switch	.text
  89  0011               _i2c_stop:
  93                     ; 19 SDA |= (1<<5);//�����
  95  0011 721a5007      	bset	20487,#5
  96                     ; 21 SCL &= ~(1<<4);//����
  98  0015 72195007      	bres	20487,#4
  99                     ; 23 SDA &= ~(1<<5);//����
 101  0019 721b5007      	bres	20487,#5
 102                     ; 25 }
 105  001d 81            	ret
 148                     ; 27 void I2C_SendByte (unsigned char d)
 148                     ; 28 {
 149                     	switch	.text
 150  001e               _I2C_SendByte:
 152  001e 88            	push	a
 153  001f 88            	push	a
 154       00000001      OFST:	set	1
 157                     ; 31 for (x = 0; x < 8; x ++) { //�������� 8 ��� ������
 159  0020 0f01          	clr	(OFST+0,sp)
 161  0022               L35:
 162                     ; 33 if (d&0x80) SDA &= ~(1<<5);//����//���������� 0
 164  0022 7b02          	ld	a,(OFST+1,sp)
 165  0024 a580          	bcp	a,#128
 166  0026 2706          	jreq	L16
 169  0028 721b5007      	bres	20487,#5
 171  002c 2004          	jra	L36
 172  002e               L16:
 173                     ; 34 else SDA |= (1<<5);//�����//���������� 1
 175  002e 721a5007      	bset	20487,#5
 176  0032               L36:
 177                     ; 36 SCL &= ~(1<<4);//����
 179  0032 72195007      	bres	20487,#4
 180                     ; 37 d <<= 1;
 182  0036 0802          	sll	(OFST+1,sp)
 183                     ; 39 SCL |= (1<<4);}//����� }
 185  0038 72185007      	bset	20487,#4
 186                     ; 31 for (x = 0; x < 8; x ++) { //�������� 8 ��� ������
 188  003c 0c01          	inc	(OFST+0,sp)
 192  003e 7b01          	ld	a,(OFST+0,sp)
 193  0040 a108          	cp	a,#8
 194  0042 25de          	jrult	L35
 195                     ; 42 SDA &= ~(1<<5);//���� //��������� �������� ACK ���
 197  0044 721b5007      	bres	20487,#5
 198                     ; 43 SCL &= ~(1<<4);//����
 200  0048 72195007      	bres	20487,#4
 201                     ; 45 SCL |= (1<<4);//�����
 203  004c 72185007      	bset	20487,#4
 204                     ; 46 SDA |= (1<<5);//�����
 206  0050 721a5007      	bset	20487,#5
 207                     ; 48 }
 210  0054 85            	popw	x
 211  0055 81            	ret
 254                     ; 50 int I2C_ReadByte (void)
 254                     ; 51 {   
 255                     	switch	.text
 256  0056               _I2C_ReadByte:
 258  0056 5203          	subw	sp,#3
 259       00000003      OFST:	set	3
 262                     ; 53 int result = 0;
 264  0058 5f            	clrw	x
 265  0059 1f02          	ldw	(OFST-1,sp),x
 267                     ; 54 SDA &= ~(1<<5);//����
 269  005b 721b5007      	bres	20487,#5
 270                     ; 55 for (i=0; i<8; i++) { //�������� 8 ��� ������ 
 272  005f 0f01          	clr	(OFST-2,sp)
 274  0061               L701:
 275                     ; 56    result<<=1;
 277  0061 0803          	sll	(OFST+0,sp)
 278  0063 0902          	rlc	(OFST-1,sp)
 280                     ; 58 SCL &= ~(1<<4);//����
 282  0065 72195007      	bres	20487,#4
 283                     ; 60 if (SDA_IN) result |= 1;
 285  0069 c65006        	ld	a,20486
 286  006c a520          	bcp	a,#32
 287  006e 2706          	jreq	L511
 290  0070 7b03          	ld	a,(OFST+0,sp)
 291  0072 aa01          	or	a,#1
 292  0074 6b03          	ld	(OFST+0,sp),a
 294  0076               L511:
 295                     ; 62 SCL |= (1<<4);//�����
 297  0076 72185007      	bset	20487,#4
 298                     ; 55 for (i=0; i<8; i++) { //�������� 8 ��� ������ 
 300  007a 0c01          	inc	(OFST-2,sp)
 304  007c 7b01          	ld	a,(OFST-2,sp)
 305  007e a108          	cp	a,#8
 306  0080 25df          	jrult	L701
 307                     ; 64 SDA |= (1<<5);//�����
 309  0082 721a5007      	bset	20487,#5
 310                     ; 66 SCL &= ~(1<<4);//����
 312  0086 72195007      	bres	20487,#4
 313                     ; 68 SCL |= (1<<4);//�����
 315  008a 72185007      	bset	20487,#4
 316                     ; 70 return result; //���������� �������� ���� ACK ����� ������� 
 318  008e 1e02          	ldw	x,(OFST-1,sp)
 321  0090 5b03          	addw	sp,#3
 322  0092 81            	ret
 365                     ; 73 int I2C_ReadByte_last (void)
 365                     ; 74 {
 366                     	switch	.text
 367  0093               _I2C_ReadByte_last:
 369  0093 5203          	subw	sp,#3
 370       00000003      OFST:	set	3
 373                     ; 76 int result = 0;
 375  0095 5f            	clrw	x
 376  0096 1f02          	ldw	(OFST-1,sp),x
 378                     ; 77 SDA &= ~(1<<5);//����
 380  0098 721b5007      	bres	20487,#5
 381                     ; 78 for (i=0; i<8; i++) { //�������� 8 ��� ������
 383  009c 0f01          	clr	(OFST-2,sp)
 385  009e               L141:
 386                     ; 79     result<<=1;
 388  009e 0803          	sll	(OFST+0,sp)
 389  00a0 0902          	rlc	(OFST-1,sp)
 391                     ; 81 SCL &= ~(1<<4);//����
 393  00a2 72195007      	bres	20487,#4
 394                     ; 83 if (SDA_IN) result |=1;
 396  00a6 c65006        	ld	a,20486
 397  00a9 a520          	bcp	a,#32
 398  00ab 2706          	jreq	L741
 401  00ad 7b03          	ld	a,(OFST+0,sp)
 402  00af aa01          	or	a,#1
 403  00b1 6b03          	ld	(OFST+0,sp),a
 405  00b3               L741:
 406                     ; 85 SCL |= (1<<4);//�����
 408  00b3 72185007      	bset	20487,#4
 409                     ; 78 for (i=0; i<8; i++) { //�������� 8 ��� ������
 411  00b7 0c01          	inc	(OFST-2,sp)
 415  00b9 7b01          	ld	a,(OFST-2,sp)
 416  00bb a108          	cp	a,#8
 417  00bd 25df          	jrult	L141
 418                     ; 87 SDA &= ~(1<<5);//����
 420  00bf 721b5007      	bres	20487,#5
 421                     ; 89 SCL &= ~(1<<4);//����
 423  00c3 72195007      	bres	20487,#4
 424                     ; 91 SCL |= (1<<4);//�����
 426  00c7 72185007      	bset	20487,#4
 427                     ; 93 return result; //���������� �������� ���� ACK ����� ������� 
 429  00cb 1e02          	ldw	x,(OFST-1,sp)
 432  00cd 5b03          	addw	sp,#3
 433  00cf 81            	ret
 446                     	xdef	_I2C_ReadByte_last
 447                     	xdef	_I2C_ReadByte
 448                     	xdef	_I2C_SendByte
 449                     	xdef	_i2c_stop
 450                     	xdef	_i2c_start
 469                     	end