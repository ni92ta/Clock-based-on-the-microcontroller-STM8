   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.8.1 - 09 Jan 2023
   3                     ; Generator (Limited) V4.5.5 - 08 Nov 2022
  43                     ; 8 void i2c_start(void)
  43                     ; 9 {
  45                     	switch	.text
  46  0000               _i2c_start:
  50                     ; 10 SCL &= ~(1<<4);//вход SCL
  52  0000 72195007      	bres	20487,#4
  53                     ; 11 SDA &= ~(1<<5);//вход
  55  0004 721b5007      	bres	20487,#5
  56                     ; 12 delay_ms(22);
  58  0008 ae0016        	ldw	x,#22
  59  000b cd0000        	call	_delay_ms
  61                     ; 13 SDA |= (1<<5);//выход
  63  000e 721a5007      	bset	20487,#5
  64                     ; 14 delay_ms(22);
  66  0012 ae0016        	ldw	x,#22
  67  0015 cd0000        	call	_delay_ms
  69                     ; 15 SCL |= (1<<4);//выход 
  71  0018 72185007      	bset	20487,#4
  72                     ; 16 }
  75  001c 81            	ret
  99                     ; 18 void i2c_stop (void)
  99                     ; 19 {
 100                     	switch	.text
 101  001d               _i2c_stop:
 105                     ; 20 SDA |= (1<<5);//выход
 107  001d 721a5007      	bset	20487,#5
 108                     ; 21 delay_ms(22);
 110  0021 ae0016        	ldw	x,#22
 111  0024 cd0000        	call	_delay_ms
 113                     ; 22 SCL &= ~(1<<4);//вход
 115  0027 72195007      	bres	20487,#4
 116                     ; 23 delay_ms(22);
 118  002b ae0016        	ldw	x,#22
 119  002e cd0000        	call	_delay_ms
 121                     ; 24 SDA &= ~(1<<5);//вход
 123  0031 721b5007      	bres	20487,#5
 124                     ; 25 delay_ms(22);
 126  0035 ae0016        	ldw	x,#22
 127  0038 cd0000        	call	_delay_ms
 129                     ; 26 }
 132  003b 81            	ret
 176                     ; 28 void I2C_SendByte (unsigned char d)
 176                     ; 29 {
 177                     	switch	.text
 178  003c               _I2C_SendByte:
 180  003c 88            	push	a
 181  003d 88            	push	a
 182       00000001      OFST:	set	1
 185                     ; 32 for (x = 0; x < 8; x ++) { //передача 8 бит данных
 187  003e 0f01          	clr	(OFST+0,sp)
 189  0040               L35:
 190                     ; 33 delay_ms(22);
 192  0040 ae0016        	ldw	x,#22
 193  0043 cd0000        	call	_delay_ms
 195                     ; 34 if (d&0x80) SDA &= ~(1<<5);//вход//логический 0
 197  0046 7b02          	ld	a,(OFST+1,sp)
 198  0048 a580          	bcp	a,#128
 199  004a 2706          	jreq	L16
 202  004c 721b5007      	bres	20487,#5
 204  0050 2004          	jra	L36
 205  0052               L16:
 206                     ; 35 else SDA |= (1<<5);//выход//логическая 1
 208  0052 721a5007      	bset	20487,#5
 209  0056               L36:
 210                     ; 36 delay_ms(22);
 212  0056 ae0016        	ldw	x,#22
 213  0059 cd0000        	call	_delay_ms
 215                     ; 37 SCL &= ~(1<<4);//вход
 217  005c 72195007      	bres	20487,#4
 218                     ; 38 d <<= 1;
 220  0060 0802          	sll	(OFST+1,sp)
 221                     ; 39 delay_ms(22);
 223  0062 ae0016        	ldw	x,#22
 224  0065 cd0000        	call	_delay_ms
 226                     ; 40 SCL |= (1<<4);}//выход }
 228  0068 72185007      	bset	20487,#4
 229                     ; 32 for (x = 0; x < 8; x ++) { //передача 8 бит данных
 231  006c 0c01          	inc	(OFST+0,sp)
 235  006e 7b01          	ld	a,(OFST+0,sp)
 236  0070 a108          	cp	a,#8
 237  0072 25cc          	jrult	L35
 238                     ; 41 delay_ms(22);
 240  0074 ae0016        	ldw	x,#22
 241  0077 cd0000        	call	_delay_ms
 243                     ; 42 delay_ms(22);
 245  007a ae0016        	ldw	x,#22
 246  007d cd0000        	call	_delay_ms
 248                     ; 43 SDA &= ~(1<<5);//вход //готовимся получить ACK бит
 250  0080 721b5007      	bres	20487,#5
 251                     ; 44 SCL &= ~(1<<4);//вход
 253  0084 72195007      	bres	20487,#4
 254                     ; 45 delay_ms(22);
 256  0088 ae0016        	ldw	x,#22
 257  008b cd0000        	call	_delay_ms
 259                     ; 46 SCL |= (1<<4);//выход
 261  008e 72185007      	bset	20487,#4
 262                     ; 47 SDA |= (1<<5);//выход
 264  0092 721a5007      	bset	20487,#5
 265                     ; 49 }
 268  0096 85            	popw	x
 269  0097 81            	ret
 313                     ; 51 int I2C_ReadByte (void)
 313                     ; 52 {   
 314                     	switch	.text
 315  0098               _I2C_ReadByte:
 317  0098 5203          	subw	sp,#3
 318       00000003      OFST:	set	3
 321                     ; 54 int result = 0;
 323  009a 5f            	clrw	x
 324  009b 1f02          	ldw	(OFST-1,sp),x
 326                     ; 55 SDA &= ~(1<<5);//вход
 328  009d 721b5007      	bres	20487,#5
 329                     ; 56 for (i=0; i<8; i++) { //передача 8 бит данных 
 331  00a1 0f01          	clr	(OFST-2,sp)
 333  00a3               L701:
 334                     ; 57    result<<=1;
 336  00a3 0803          	sll	(OFST+0,sp)
 337  00a5 0902          	rlc	(OFST-1,sp)
 339                     ; 58 delay_ms(22);
 341  00a7 ae0016        	ldw	x,#22
 342  00aa cd0000        	call	_delay_ms
 344                     ; 59 SCL &= ~(1<<4);//вход
 346  00ad 72195007      	bres	20487,#4
 347                     ; 60 delay_ms(22);
 349  00b1 ae0016        	ldw	x,#22
 350  00b4 cd0000        	call	_delay_ms
 352                     ; 61 if (SDA_IN) result |= 1;
 354  00b7 c65006        	ld	a,20486
 355  00ba a520          	bcp	a,#32
 356  00bc 2706          	jreq	L511
 359  00be 7b03          	ld	a,(OFST+0,sp)
 360  00c0 aa01          	or	a,#1
 361  00c2 6b03          	ld	(OFST+0,sp),a
 363  00c4               L511:
 364                     ; 63 SCL |= (1<<4);//выход
 366  00c4 72185007      	bset	20487,#4
 367                     ; 56 for (i=0; i<8; i++) { //передача 8 бит данных 
 369  00c8 0c01          	inc	(OFST-2,sp)
 373  00ca 7b01          	ld	a,(OFST-2,sp)
 374  00cc a108          	cp	a,#8
 375  00ce 25d3          	jrult	L701
 376                     ; 65 SDA |= (1<<5);//выход
 378  00d0 721a5007      	bset	20487,#5
 379                     ; 66 delay_ms(22);
 381  00d4 ae0016        	ldw	x,#22
 382  00d7 cd0000        	call	_delay_ms
 384                     ; 67 SCL &= ~(1<<4);//вход
 386  00da 72195007      	bres	20487,#4
 387                     ; 68 delay_ms(22);
 389  00de ae0016        	ldw	x,#22
 390  00e1 cd0000        	call	_delay_ms
 392                     ; 69 SCL |= (1<<4);//выход
 394  00e4 72185007      	bset	20487,#4
 395                     ; 70 delay_ms(22);
 397  00e8 ae0016        	ldw	x,#22
 398  00eb cd0000        	call	_delay_ms
 400                     ; 71 return result; //Возвращаем значение бита ACK через функцию 
 402  00ee 1e02          	ldw	x,(OFST-1,sp)
 405  00f0 5b03          	addw	sp,#3
 406  00f2 81            	ret
 450                     ; 74 int I2C_ReadByte_last (void)
 450                     ; 75 {
 451                     	switch	.text
 452  00f3               _I2C_ReadByte_last:
 454  00f3 5203          	subw	sp,#3
 455       00000003      OFST:	set	3
 458                     ; 77 int result = 0;
 460  00f5 5f            	clrw	x
 461  00f6 1f02          	ldw	(OFST-1,sp),x
 463                     ; 78 SDA &= ~(1<<5);//вход
 465  00f8 721b5007      	bres	20487,#5
 466                     ; 79 for (i=0; i<8; i++) { //передача 8 бит данных
 468  00fc 0f01          	clr	(OFST-2,sp)
 470  00fe               L141:
 471                     ; 80     result<<=1;
 473  00fe 0803          	sll	(OFST+0,sp)
 474  0100 0902          	rlc	(OFST-1,sp)
 476                     ; 81 delay_ms(22);
 478  0102 ae0016        	ldw	x,#22
 479  0105 cd0000        	call	_delay_ms
 481                     ; 82 SCL &= ~(1<<4);//вход
 483  0108 72195007      	bres	20487,#4
 484                     ; 83 delay_ms(22);
 486  010c ae0016        	ldw	x,#22
 487  010f cd0000        	call	_delay_ms
 489                     ; 84 if (SDA_IN) result |=1;
 491  0112 c65006        	ld	a,20486
 492  0115 a520          	bcp	a,#32
 493  0117 2706          	jreq	L741
 496  0119 7b03          	ld	a,(OFST+0,sp)
 497  011b aa01          	or	a,#1
 498  011d 6b03          	ld	(OFST+0,sp),a
 500  011f               L741:
 501                     ; 86 SCL |= (1<<4);//выход
 503  011f 72185007      	bset	20487,#4
 504                     ; 79 for (i=0; i<8; i++) { //передача 8 бит данных
 506  0123 0c01          	inc	(OFST-2,sp)
 510  0125 7b01          	ld	a,(OFST-2,sp)
 511  0127 a108          	cp	a,#8
 512  0129 25d3          	jrult	L141
 513                     ; 88 SDA &= ~(1<<5);//вход
 515  012b 721b5007      	bres	20487,#5
 516                     ; 89 delay_ms(22);
 518  012f ae0016        	ldw	x,#22
 519  0132 cd0000        	call	_delay_ms
 521                     ; 90 SCL &= ~(1<<4);//вход
 523  0135 72195007      	bres	20487,#4
 524                     ; 91 delay_ms(22);
 526  0139 ae0016        	ldw	x,#22
 527  013c cd0000        	call	_delay_ms
 529                     ; 92 SCL |= (1<<4);//выход
 531  013f 72185007      	bset	20487,#4
 532                     ; 93 delay_ms(22);
 534  0143 ae0016        	ldw	x,#22
 535  0146 cd0000        	call	_delay_ms
 537                     ; 94 return result; //Возвращаем значение бита ACK через функцию 
 539  0149 1e02          	ldw	x,(OFST-1,sp)
 542  014b 5b03          	addw	sp,#3
 543  014d 81            	ret
 556                     	xref	_delay_ms
 557                     	xdef	_I2C_ReadByte_last
 558                     	xdef	_I2C_ReadByte
 559                     	xdef	_I2C_SendByte
 560                     	xdef	_i2c_stop
 561                     	xdef	_i2c_start
 580                     	end
