   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.8.1 - 09 Jan 2023
   3                     ; Generator (Limited) V4.5.5 - 08 Nov 2022
  14                     	bsct
  15  0000               _ms:
  16  0000 0000          	dc.w	0
  17  0002               _tio:
  18  0002 00            	dc.b	0
  19  0003               _alarm_1:
  20  0003 30            	dc.b	48
  21  0004               _alarm_2:
  22  0004 30            	dc.b	48
  23  0005               _alarm_3:
  24  0005 30            	dc.b	48
  25  0006               _alarm_4:
  26  0006 31            	dc.b	49
  27  0007               _t:
  28  0007 00            	dc.b	0
  29  0008               _alarm_number:
  30  0008 31            	dc.b	49
  31  0009               _DAY_1:
  32  0009 a8            	dc.b	168
  33  000a               _DAY_2:
  34  000a 48            	dc.b	72
  35  000b               _houre_alar:
  36  000b 30            	dc.b	48
  37  000c               _hourd_alar:
  38  000c 30            	dc.b	48
  79                     ; 45 void delay_ms(unsigned int set_ms) // Задержка в мс
  79                     ; 46 {
  81                     	switch	.text
  82  0000               _delay_ms:
  86                     ; 47    ms = set_ms + 300;
  88  0000 1c012c        	addw	x,#300
  89  0003 bf00          	ldw	_ms,x
  91  0005               L33:
  92                     ; 48 	 while (ms--);
  94  0005 be00          	ldw	x,_ms
  95  0007 1d0001        	subw	x,#1
  96  000a bf00          	ldw	_ms,x
  97  000c 1c0001        	addw	x,#1
  98  000f a30000        	cpw	x,#0
  99  0012 26f1          	jrne	L33
 100                     ; 49 }
 103  0014 81            	ret
 129                     ; 50 void DS1307init (void){//инициализация микросхемы
 130                     	switch	.text
 131  0015               _DS1307init:
 135                     ; 53     i2c_start ();//отправка посылки СТАРТ
 137  0015 cd0000        	call	_i2c_start
 139                     ; 54     I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
 141  0018 a6d0          	ld	a,#208
 142  001a cd0000        	call	_I2C_SendByte
 144                     ; 55     I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
 146  001d 4f            	clr	a
 147  001e cd0000        	call	_I2C_SendByte
 149                     ; 56     I2C_SendByte (0b01010101);//установка секунд 55
 151  0021 a655          	ld	a,#85
 152  0023 cd0000        	call	_I2C_SendByte
 154                     ; 57     I2C_SendByte (0b01011001);//установка минут 00
 156  0026 a659          	ld	a,#89
 157  0028 cd0000        	call	_I2C_SendByte
 159                     ; 58     I2C_SendByte (0b00100011);//установка часов 00  0b00100011
 161  002b a623          	ld	a,#35
 162  002d cd0000        	call	_I2C_SendByte
 164                     ; 59     I2C_SendByte (0b00000110);//установка дня ВС
 166  0030 a606          	ld	a,#6
 167  0032 cd0000        	call	_I2C_SendByte
 169                     ; 60     i2c_stop ();
 171  0035 cd0000        	call	_i2c_stop
 173                     ; 63     i2c_start ();//отправка посылки СТАРТ
 175  0038 cd0000        	call	_i2c_start
 177                     ; 64     I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
 179  003b a6d0          	ld	a,#208
 180  003d cd0000        	call	_I2C_SendByte
 182                     ; 65     I2C_SendByte (0b00000111);//вызов регистра clock out
 184  0040 a607          	ld	a,#7
 185  0042 cd0000        	call	_I2C_SendByte
 187                     ; 66     I2C_SendByte (0b00010000);//включение делителя частоты 1Hz
 189  0045 a610          	ld	a,#16
 190  0047 cd0000        	call	_I2C_SendByte
 192                     ; 67     i2c_stop ();
 194  004a cd0000        	call	_i2c_stop
 196                     ; 68 }
 199  004d 81            	ret
 234                     ; 70 main()
 234                     ; 71 {
 235                     	switch	.text
 236  004e               _main:
 240                     ; 76 	CLK->CKDIVR = 0b00011111; //Делитель частоты внутреннего осцилятора = 8; тактовой частоты ЦПУ -128
 242  004e 351f50c6      	mov	20678,#31
 243                     ; 78 	GPIOA->DDR |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//Выход
 245  0052 72165002      	bset	20482,#3
 246                     ; 79 	GPIOA->CR1 |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//Выход типа Push-pull
 248  0056 72165003      	bset	20483,#3
 249                     ; 80 	GPIOA->CR2 |= (1<<3);// | (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц.
 251  005a 72165004      	bset	20484,#3
 252                     ; 82 	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//Выход
 254  005e c65011        	ld	a,20497
 255  0061 aa78          	or	a,#120
 256  0063 c75011        	ld	20497,a
 257                     ; 83 	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//Выход типа Push-pull
 259  0066 c65012        	ld	a,20498
 260  0069 aa78          	or	a,#120
 261  006b c75012        	ld	20498,a
 262                     ; 84 	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц.
 264  006e c65013        	ld	a,20499
 265  0071 aa78          	or	a,#120
 266  0073 c75013        	ld	20499,a
 267                     ; 86 	GPIOC->DDR &= ~((1<<4) | (1<<3));//вход
 269  0076 c6500c        	ld	a,20492
 270  0079 a4e7          	and	a,#231
 271  007b c7500c        	ld	20492,a
 272                     ; 87 	GPIOC->CR1 |= (1<<4) | (1<<3);//вход с подтягивающим резистором  
 274  007e c6500d        	ld	a,20493
 275  0081 aa18          	or	a,#24
 276  0083 c7500d        	ld	20493,a
 277                     ; 88 	GPIOC->CR2 |= (1<<4) | (1<<3);//Скорость переключения - до 10 МГц. 
 279  0086 c6500e        	ld	a,20494
 280  0089 aa18          	or	a,#24
 281  008b c7500e        	ld	20494,a
 282                     ; 90 	DS1307init();
 284  008e ad85          	call	_DS1307init
 286  0090               L75:
 287                     ; 92 		DS1307init();
 289  0090 ad83          	call	_DS1307init
 291                     ; 93 	 i2c_start();//отправка посылки СТАРТ
 293  0092 cd0000        	call	_i2c_start
 295                     ; 94       I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
 297  0095 a6d0          	ld	a,#208
 298  0097 cd0000        	call	_I2C_SendByte
 300                     ; 95       I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
 302  009a 4f            	clr	a
 303  009b cd0000        	call	_I2C_SendByte
 305                     ; 96       i2c_stop ();//отправка посылки СТОП 
 307  009e cd0000        	call	_i2c_stop
 309                     ; 97       i2c_start ();//отправка посылки СТАРТ
 311  00a1 cd0000        	call	_i2c_start
 313                     ; 98       I2C_SendByte (dev_addrr);//адрес часовой микросхемы - чтение
 315  00a4 a6d1          	ld	a,#209
 316  00a6 cd0000        	call	_I2C_SendByte
 318                     ; 99       sec = I2C_ReadByte();//чтение секунд
 320  00a9 cd0000        	call	_I2C_ReadByte
 322  00ac 01            	rrwa	x,a
 323  00ad b70b          	ld	_sec,a
 324  00af 02            	rlwa	x,a
 325                     ; 100       min = I2C_ReadByte();//чтение минут
 327  00b0 cd0000        	call	_I2C_ReadByte
 329  00b3 01            	rrwa	x,a
 330  00b4 b70a          	ld	_min,a
 331  00b6 02            	rlwa	x,a
 332                     ; 101       hour = I2C_ReadByte();//чтение часов
 334  00b7 cd0000        	call	_I2C_ReadByte
 336  00ba 01            	rrwa	x,a
 337  00bb b707          	ld	_hour,a
 338  00bd 02            	rlwa	x,a
 339                     ; 102       Weekdays = I2C_ReadByte_last();//чтение дня недели
 341  00be cd0000        	call	_I2C_ReadByte_last
 343  00c1 01            	rrwa	x,a
 344  00c2 b700          	ld	_Weekdays,a
 345  00c4 02            	rlwa	x,a
 346                     ; 103       i2c_stop (); 	
 348  00c5 cd0000        	call	_i2c_stop
 350                     ; 108 	if ((GPIOC->IDR & (1 << 3)) == 0 ) tio = 1;
 352  00c8 c6500b        	ld	a,20491
 353  00cb a508          	bcp	a,#8
 354  00cd 2604          	jrne	L36
 357  00cf 35010002      	mov	_tio,#1
 358  00d3               L36:
 359                     ; 109 	if ((GPIOC->IDR & (1 << 4)) == 0 ) tio = 0;
 361  00d3 c6500b        	ld	a,20491
 362  00d6 a510          	bcp	a,#16
 363  00d8 2602          	jrne	L56
 366  00da 3f02          	clr	_tio
 367  00dc               L56:
 368                     ; 110 	if (tio == 0) GPIOA->ODR |=  (1<<3);
 370  00dc 3d02          	tnz	_tio
 371  00de 2604          	jrne	L76
 374  00e0 72165000      	bset	20480,#3
 375  00e4               L76:
 376                     ; 111 	if (tio == 1){
 378  00e4 b602          	ld	a,_tio
 379  00e6 a101          	cp	a,#1
 380  00e8 26a6          	jrne	L75
 381                     ; 112 	GPIOD->ODR |= (1<<5) | (1<<4) | (1<<3);
 383  00ea c6500f        	ld	a,20495
 384  00ed aa38          	or	a,#56
 385  00ef c7500f        	ld	20495,a
 386                     ; 113 	delay_ms(1000);
 388  00f2 ae03e8        	ldw	x,#1000
 389  00f5 cd0000        	call	_delay_ms
 391                     ; 114 	GPIOD->ODR &=  ~((1<<5) | (1<<4) | (1<<3));
 393  00f8 c6500f        	ld	a,20495
 394  00fb a4c7          	and	a,#199
 395  00fd c7500f        	ld	20495,a
 396                     ; 115 	delay_ms(1000);
 398  0100 ae03e8        	ldw	x,#1000
 399  0103 cd0000        	call	_delay_ms
 401                     ; 116 	GPIOA->ODR &=  ~(1<<3);	
 403  0106 72175000      	bres	20480,#3
 404  010a 2084          	jra	L75
 671                     	xdef	_main
 672                     	xdef	_DS1307init
 673                     	xdef	_delay_ms
 674                     	switch	.ubsct
 675  0000               _Weekdays:
 676  0000 00            	ds.b	1
 677                     	xdef	_Weekdays
 678  0001               _houree:
 679  0001 00            	ds.b	1
 680                     	xdef	_houree
 681  0002               _minee:
 682  0002 00            	ds.b	1
 683                     	xdef	_minee
 684                     	xdef	_hourd_alar
 685                     	xdef	_houre_alar
 686  0003               _hourd:
 687  0003 00            	ds.b	1
 688                     	xdef	_hourd
 689  0004               _houre:
 690  0004 00            	ds.b	1
 691                     	xdef	_houre
 692  0005               _min_alar:
 693  0005 00            	ds.b	1
 694                     	xdef	_min_alar
 695  0006               _hour_alar:
 696  0006 00            	ds.b	1
 697                     	xdef	_hour_alar
 698  0007               _hour:
 699  0007 00            	ds.b	1
 700                     	xdef	_hour
 701  0008               _mind:
 702  0008 00            	ds.b	1
 703                     	xdef	_mind
 704  0009               _mine:
 705  0009 00            	ds.b	1
 706                     	xdef	_mine
 707  000a               _min:
 708  000a 00            	ds.b	1
 709                     	xdef	_min
 710  000b               _sec:
 711  000b 00            	ds.b	1
 712                     	xdef	_sec
 713  000c               _secd:
 714  000c 00            	ds.b	1
 715                     	xdef	_secd
 716  000d               _sece:
 717  000d 00            	ds.b	1
 718                     	xdef	_sece
 719                     	xdef	_DAY_2
 720                     	xdef	_DAY_1
 721                     	xdef	_alarm_number
 722  000e               _alarm_flag:
 723  000e 00            	ds.b	1
 724                     	xdef	_alarm_flag
 725  000f               _n:
 726  000f 00            	ds.b	1
 727                     	xdef	_n
 728                     	xdef	_t
 729                     	xdef	_alarm_4
 730                     	xdef	_alarm_3
 731                     	xdef	_alarm_2
 732                     	xdef	_alarm_1
 733                     	xdef	_tio
 734                     	xdef	_ms
 735                     	xref	_I2C_ReadByte_last
 736                     	xref	_I2C_ReadByte
 737                     	xref	_I2C_SendByte
 738                     	xref	_i2c_stop
 739                     	xref	_i2c_start
 759                     	end
