   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.8.1 - 09 Jan 2023
   3                     ; Generator (Limited) V4.5.5 - 08 Nov 2022
  14                     	bsct
  15  0000               _ms:
  16  0000 0000          	dc.w	0
  17  0002               _tio:
  18  0002 00            	dc.b	0
  19  0003               _address_1:
  20  0003 4000          	dc.w	16384
  21  0005               _address_2:
  22  0005 4001          	dc.w	16385
  23  0007               _address_3:
  24  0007 4002          	dc.w	16386
  25  0009               _address_4:
  26  0009 4003          	dc.w	16387
  27  000b               _t:
  28  000b 00            	dc.b	0
  29  000c               _alarm_number:
  30  000c 31            	dc.b	49
  31  000d               _DAY_1:
  32  000d a8            	dc.b	168
  33  000e               _DAY_2:
  34  000e 48            	dc.b	72
  35  000f               _houre_alar:
  36  000f 30            	dc.b	48
  37  0010               _hourd_alar:
  38  0010 30            	dc.b	48
  79                     ; 61 void delay_ms(unsigned int set_ms) // Задержка в мс
  79                     ; 62 {
  81                     	switch	.text
  82  0000               _delay_ms:
  86                     ; 64    ms = set_ms;
  88  0000 bf00          	ldw	_ms,x
  90  0002               L33:
  91                     ; 66 	 while (ms--);
  93  0002 be00          	ldw	x,_ms
  94  0004 1d0001        	subw	x,#1
  95  0007 bf00          	ldw	_ms,x
  96  0009 1c0001        	addw	x,#1
  97  000c a30000        	cpw	x,#0
  98  000f 26f1          	jrne	L33
  99                     ; 68 }
 102  0011 81            	ret
 137                     ; 70 void segment_clear (unsigned char num_seg)
 137                     ; 71 {
 138                     	switch	.text
 139  0012               _segment_clear:
 141  0012 88            	push	a
 142       00000000      OFST:	set	0
 145  0013 2008          	jra	L16
 146  0015               L55:
 147                     ; 74 	sendbyte(0b00100000,1);//очистка сегмента
 149  0015 ae2001        	ldw	x,#8193
 150  0018 cd0000        	call	_sendbyte
 152                     ; 73 	for (; num_seg > 0; num_seg --){//num_seg-количество сегментов для очистки
 154  001b 0a01          	dec	(OFST+1,sp)
 155  001d               L16:
 158  001d 0d01          	tnz	(OFST+1,sp)
 159  001f 26f4          	jrne	L55
 160                     ; 76 }
 163  0021 84            	pop	a
 164  0022 81            	ret
 217                     ; 78 unsigned char RTC_ConvertFromDecd(unsigned char c,unsigned char v){//
 218                     	switch	.text
 219  0023               _RTC_ConvertFromDecd:
 221  0023 89            	pushw	x
 222  0024 88            	push	a
 223       00000001      OFST:	set	1
 226                     ; 80     if (v == 1){
 228  0025 9f            	ld	a,xl
 229  0026 a101          	cp	a,#1
 230  0028 260d          	jrne	L311
 231                     ; 81       c = c>>4;
 233  002a 7b02          	ld	a,(OFST+1,sp)
 234  002c 4e            	swap	a
 235  002d a40f          	and	a,#15
 236  002f 6b02          	ld	(OFST+1,sp),a
 237                     ; 82        ch = (0b00000011&c);   
 239  0031 7b02          	ld	a,(OFST+1,sp)
 240  0033 a403          	and	a,#3
 241  0035 6b01          	ld	(OFST+0,sp),a
 243  0037               L311:
 244                     ; 84     if (v == 0){
 246  0037 0d03          	tnz	(OFST+2,sp)
 247  0039 2607          	jrne	L511
 248                     ; 85     ch = (c >> 4);     
 250  003b 7b02          	ld	a,(OFST+1,sp)
 251  003d 4e            	swap	a
 252  003e a40f          	and	a,#15
 253  0040 6b01          	ld	(OFST+0,sp),a
 255  0042               L511:
 256                     ; 87     if (v==2){
 258  0042 7b03          	ld	a,(OFST+2,sp)
 259  0044 a102          	cp	a,#2
 260  0046 260d          	jrne	L711
 261                     ; 88           c = c>>4;
 263  0048 7b02          	ld	a,(OFST+1,sp)
 264  004a 4e            	swap	a
 265  004b a40f          	and	a,#15
 266  004d 6b02          	ld	(OFST+1,sp),a
 267                     ; 89        ch = (0b00000001&c);  
 269  004f 7b02          	ld	a,(OFST+1,sp)
 270  0051 a401          	and	a,#1
 271  0053 6b01          	ld	(OFST+0,sp),a
 273  0055               L711:
 274                     ; 91     return ch; 
 276  0055 7b01          	ld	a,(OFST+0,sp)
 279  0057 5b03          	addw	sp,#3
 280  0059 81            	ret
 323                     ; 94 unsigned char RTC_ConvertFromDec(unsigned char c){//
 324                     	switch	.text
 325  005a               _RTC_ConvertFromDec:
 327  005a 88            	push	a
 328       00000001      OFST:	set	1
 331                     ; 95     unsigned char ch = (0b00001111&c);
 333  005b a40f          	and	a,#15
 334  005d 6b01          	ld	(OFST+0,sp),a
 336                     ; 96     return ch;
 338  005f 7b01          	ld	a,(OFST+0,sp)
 341  0061 5b01          	addw	sp,#1
 342  0063 81            	ret
 345                     	bsct
 346  0011               _str01:
 347  0011 1e            	dc.b	30
 348  0012 1e            	dc.b	30
 349  0013 18            	dc.b	24
 350  0014 18            	dc.b	24
 351  0015 18            	dc.b	24
 352  0016 18            	dc.b	24
 353  0017 18            	dc.b	24
 354  0018 18            	dc.b	24
 355  0019               _str02:
 356  0019 1e            	dc.b	30
 357  001a 1e            	dc.b	30
 358  001b 06            	dc.b	6
 359  001c 06            	dc.b	6
 360  001d 06            	dc.b	6
 361  001e 06            	dc.b	6
 362  001f 06            	dc.b	6
 363  0020 06            	dc.b	6
 364  0021               _str03:
 365  0021 18            	dc.b	24
 366  0022 18            	dc.b	24
 367  0023 18            	dc.b	24
 368  0024 18            	dc.b	24
 369  0025 18            	dc.b	24
 370  0026 18            	dc.b	24
 371  0027 1e            	dc.b	30
 372  0028 1e            	dc.b	30
 373  0029               _str04:
 374  0029 06            	dc.b	6
 375  002a 06            	dc.b	6
 376  002b 06            	dc.b	6
 377  002c 06            	dc.b	6
 378  002d 06            	dc.b	6
 379  002e 06            	dc.b	6
 380  002f 1e            	dc.b	30
 381  0030 1e            	dc.b	30
 382  0031               _str05:
 383  0031 1e            	dc.b	30
 384  0032 1e            	dc.b	30
 385  0033 06            	dc.b	6
 386  0034 06            	dc.b	6
 387  0035 06            	dc.b	6
 388  0036 06            	dc.b	6
 389  0037 1e            	dc.b	30
 390  0038 1e            	dc.b	30
 391  0039               _str06:
 392  0039 1f            	dc.b	31
 393  003a 1f            	dc.b	31
 394  003b 18            	dc.b	24
 395  003c 18            	dc.b	24
 396  003d 18            	dc.b	24
 397  003e 18            	dc.b	24
 398  003f 1f            	dc.b	31
 399  0040 1f            	dc.b	31
 400  0041               _str07:
 401  0041 00            	dc.b	0
 402  0042 00            	dc.b	0
 403  0043 00            	dc.b	0
 404  0044 00            	dc.b	0
 405  0045 00            	dc.b	0
 406  0046 00            	dc.b	0
 407  0047 0e            	dc.b	14
 408  0048 0e            	dc.b	14
 409  0049               _str08:
 410  0049 0f            	dc.b	15
 411  004a 0f            	dc.b	15
 412  004b 00            	dc.b	0
 413  004c 00            	dc.b	0
 414  004d 00            	dc.b	0
 415  004e 00            	dc.b	0
 416  004f 00            	dc.b	0
 417  0050 00            	dc.b	0
 460                     ; 181 void digit_out (unsigned char digit, unsigned char str1/*, unsigned char str2*/)//digit - цифра от 1 до 9
 460                     ; 182 //str1- номер строки для вывода, сначала 1 потом 2
 460                     ; 183 {
 461                     	switch	.text
 462  0064               _digit_out:
 464  0064 89            	pushw	x
 465       00000000      OFST:	set	0
 468                     ; 184 switch (digit){
 470  0065 9e            	ld	a,xh
 472                     ; 264         break;        
 473  0066 4d            	tnz	a
 474  0067 2737          	jreq	L341
 475  0069 4a            	dec	a
 476  006a 2760          	jreq	L541
 477  006c 4a            	dec	a
 478  006d 2603          	jrne	L61
 479  006f cc00f8        	jp	L741
 480  0072               L61:
 481  0072 4a            	dec	a
 482  0073 2603          	jrne	L02
 483  0075 cc0124        	jp	L151
 484  0078               L02:
 485  0078 4a            	dec	a
 486  0079 2603          	jrne	L22
 487  007b cc0150        	jp	L351
 488  007e               L22:
 489  007e 4a            	dec	a
 490  007f 2603          	jrne	L42
 491  0081 cc017c        	jp	L551
 492  0084               L42:
 493  0084 4a            	dec	a
 494  0085 2603          	jrne	L62
 495  0087 cc01a8        	jp	L751
 496  008a               L62:
 497  008a 4a            	dec	a
 498  008b 2603          	jrne	L03
 499  008d cc01d2        	jp	L161
 500  0090               L03:
 501  0090 4a            	dec	a
 502  0091 2603          	jrne	L23
 503  0093 cc01fc        	jp	L361
 504  0096               L23:
 505  0096 4a            	dec	a
 506  0097 2603          	jrne	L43
 507  0099 cc0226        	jp	L561
 508  009c               L43:
 509  009c ac4e024e      	jpf	L312
 510  00a0               L341:
 511                     ; 185     case 0:
 511                     ; 186 LCD_SetPos(str1,0);
 513  00a0 7b02          	ld	a,(OFST+2,sp)
 514  00a2 5f            	clrw	x
 515  00a3 95            	ld	xh,a
 516  00a4 cd0000        	call	_LCD_SetPos
 518                     ; 187 sendbyte(0b00000000,1);//0
 520  00a7 ae0001        	ldw	x,#1
 521  00aa cd0000        	call	_sendbyte
 523                     ; 188 sendbyte(0b00000001,1);
 525  00ad ae0101        	ldw	x,#257
 526  00b0 cd0000        	call	_sendbyte
 528                     ; 189 LCD_SetPos(str1,1);
 530  00b3 7b02          	ld	a,(OFST+2,sp)
 531  00b5 ae0001        	ldw	x,#1
 532  00b8 95            	ld	xh,a
 533  00b9 cd0000        	call	_LCD_SetPos
 535                     ; 190 sendbyte(0b00000010,1);//0
 537  00bc ae0201        	ldw	x,#513
 538  00bf cd0000        	call	_sendbyte
 540                     ; 191 sendbyte(0b00000011,1);
 542  00c2 ae0301        	ldw	x,#769
 543  00c5 cd0000        	call	_sendbyte
 545                     ; 192         break;
 547  00c8 ac4e024e      	jpf	L312
 548  00cc               L541:
 549                     ; 193     case 1:
 549                     ; 194 LCD_SetPos(str1,0);
 551  00cc 7b02          	ld	a,(OFST+2,sp)
 552  00ce 5f            	clrw	x
 553  00cf 95            	ld	xh,a
 554  00d0 cd0000        	call	_LCD_SetPos
 556                     ; 195 sendbyte(0b00000001,1);//1
 558  00d3 ae0101        	ldw	x,#257
 559  00d6 cd0000        	call	_sendbyte
 561                     ; 196 sendbyte(0b00100000,1);
 563  00d9 ae2001        	ldw	x,#8193
 564  00dc cd0000        	call	_sendbyte
 566                     ; 197 LCD_SetPos(str1,1);
 568  00df 7b02          	ld	a,(OFST+2,sp)
 569  00e1 ae0001        	ldw	x,#1
 570  00e4 95            	ld	xh,a
 571  00e5 cd0000        	call	_LCD_SetPos
 573                     ; 198 sendbyte(0b00000011,1);//1
 575  00e8 ae0301        	ldw	x,#769
 576  00eb cd0000        	call	_sendbyte
 578                     ; 199 sendbyte(0b00000110,1);
 580  00ee ae0601        	ldw	x,#1537
 581  00f1 cd0000        	call	_sendbyte
 583                     ; 200         break;
 585  00f4 ac4e024e      	jpf	L312
 586  00f8               L741:
 587                     ; 201     case 2:
 587                     ; 202 LCD_SetPos(str1,0);
 589  00f8 7b02          	ld	a,(OFST+2,sp)
 590  00fa 5f            	clrw	x
 591  00fb 95            	ld	xh,a
 592  00fc cd0000        	call	_LCD_SetPos
 594                     ; 203 sendbyte(0b00000111,1);//2
 596  00ff ae0701        	ldw	x,#1793
 597  0102 cd0000        	call	_sendbyte
 599                     ; 204 sendbyte(0b00000100,1);
 601  0105 ae0401        	ldw	x,#1025
 602  0108 cd0000        	call	_sendbyte
 604                     ; 205 LCD_SetPos(str1,1);
 606  010b 7b02          	ld	a,(OFST+2,sp)
 607  010d ae0001        	ldw	x,#1
 608  0110 95            	ld	xh,a
 609  0111 cd0000        	call	_LCD_SetPos
 611                     ; 206 sendbyte(0b00000101,1);//2
 613  0114 ae0501        	ldw	x,#1281
 614  0117 cd0000        	call	_sendbyte
 616                     ; 207 sendbyte(0b00000110,1);
 618  011a ae0601        	ldw	x,#1537
 619  011d cd0000        	call	_sendbyte
 621                     ; 208         break;
 623  0120 ac4e024e      	jpf	L312
 624  0124               L151:
 625                     ; 209     case 3:
 625                     ; 210 LCD_SetPos(str1,0);
 627  0124 7b02          	ld	a,(OFST+2,sp)
 628  0126 5f            	clrw	x
 629  0127 95            	ld	xh,a
 630  0128 cd0000        	call	_LCD_SetPos
 632                     ; 211 sendbyte(0b00000111,1);//3
 634  012b ae0701        	ldw	x,#1793
 635  012e cd0000        	call	_sendbyte
 637                     ; 212 sendbyte(0b00000100,1);
 639  0131 ae0401        	ldw	x,#1025
 640  0134 cd0000        	call	_sendbyte
 642                     ; 213 LCD_SetPos(str1,1);
 644  0137 7b02          	ld	a,(OFST+2,sp)
 645  0139 ae0001        	ldw	x,#1
 646  013c 95            	ld	xh,a
 647  013d cd0000        	call	_LCD_SetPos
 649                     ; 214 sendbyte(0b00000110,1);//3
 651  0140 ae0601        	ldw	x,#1537
 652  0143 cd0000        	call	_sendbyte
 654                     ; 215 sendbyte(0b00000011,1);
 656  0146 ae0301        	ldw	x,#769
 657  0149 cd0000        	call	_sendbyte
 659                     ; 216         break;
 661  014c ac4e024e      	jpf	L312
 662  0150               L351:
 663                     ; 217     case 4:
 663                     ; 218 LCD_SetPos(str1,0);
 665  0150 7b02          	ld	a,(OFST+2,sp)
 666  0152 5f            	clrw	x
 667  0153 95            	ld	xh,a
 668  0154 cd0000        	call	_LCD_SetPos
 670                     ; 219 sendbyte(0b00000010,1);//4
 672  0157 ae0201        	ldw	x,#513
 673  015a cd0000        	call	_sendbyte
 675                     ; 220 sendbyte(0b00000011,1);
 677  015d ae0301        	ldw	x,#769
 678  0160 cd0000        	call	_sendbyte
 680                     ; 221 LCD_SetPos(str1,1);
 682  0163 7b02          	ld	a,(OFST+2,sp)
 683  0165 ae0001        	ldw	x,#1
 684  0168 95            	ld	xh,a
 685  0169 cd0000        	call	_LCD_SetPos
 687                     ; 222 sendbyte(0b00100000,1);//4
 689  016c ae2001        	ldw	x,#8193
 690  016f cd0000        	call	_sendbyte
 692                     ; 223 sendbyte(0b00000001,1);
 694  0172 ae0101        	ldw	x,#257
 695  0175 cd0000        	call	_sendbyte
 697                     ; 224         break;
 699  0178 ac4e024e      	jpf	L312
 700  017c               L551:
 701                     ; 225     case 5:
 701                     ; 226 LCD_SetPos(str1,0);
 703  017c 7b02          	ld	a,(OFST+2,sp)
 704  017e 5f            	clrw	x
 705  017f 95            	ld	xh,a
 706  0180 cd0000        	call	_LCD_SetPos
 708                     ; 227 sendbyte(0b00000101,1);//5
 710  0183 ae0501        	ldw	x,#1281
 711  0186 cd0000        	call	_sendbyte
 713                     ; 228 sendbyte(0b00000111,1);
 715  0189 ae0701        	ldw	x,#1793
 716  018c cd0000        	call	_sendbyte
 718                     ; 229 LCD_SetPos(str1,1);
 720  018f 7b02          	ld	a,(OFST+2,sp)
 721  0191 ae0001        	ldw	x,#1
 722  0194 95            	ld	xh,a
 723  0195 cd0000        	call	_LCD_SetPos
 725                     ; 230 sendbyte(0b00000110,1);//5
 727  0198 ae0601        	ldw	x,#1537
 728  019b cd0000        	call	_sendbyte
 730                     ; 231 sendbyte(0b00000100,1);
 732  019e ae0401        	ldw	x,#1025
 733  01a1 cd0000        	call	_sendbyte
 735                     ; 232         break;
 737  01a4 ac4e024e      	jpf	L312
 738  01a8               L751:
 739                     ; 233     case 6:
 739                     ; 234 LCD_SetPos(str1,0);
 741  01a8 7b02          	ld	a,(OFST+2,sp)
 742  01aa 5f            	clrw	x
 743  01ab 95            	ld	xh,a
 744  01ac cd0000        	call	_LCD_SetPos
 746                     ; 235 sendbyte(0b00000000,1);//6
 748  01af ae0001        	ldw	x,#1
 749  01b2 cd0000        	call	_sendbyte
 751                     ; 236 sendbyte(0b00100000,1);
 753  01b5 ae2001        	ldw	x,#8193
 754  01b8 cd0000        	call	_sendbyte
 756                     ; 237 LCD_SetPos(str1,1);
 758  01bb 7b02          	ld	a,(OFST+2,sp)
 759  01bd ae0001        	ldw	x,#1
 760  01c0 95            	ld	xh,a
 761  01c1 cd0000        	call	_LCD_SetPos
 763                     ; 238 sendbyte(0b00000101,1);//6
 765  01c4 ae0501        	ldw	x,#1281
 766  01c7 cd0000        	call	_sendbyte
 768                     ; 239 sendbyte(0b00000100,1);
 770  01ca ae0401        	ldw	x,#1025
 771  01cd cd0000        	call	_sendbyte
 773                     ; 240         break;
 775  01d0 207c          	jra	L312
 776  01d2               L161:
 777                     ; 241     case 7:
 777                     ; 242 LCD_SetPos(str1,0);
 779  01d2 7b02          	ld	a,(OFST+2,sp)
 780  01d4 5f            	clrw	x
 781  01d5 95            	ld	xh,a
 782  01d6 cd0000        	call	_LCD_SetPos
 784                     ; 243 sendbyte(0b00000111,1);//7
 786  01d9 ae0701        	ldw	x,#1793
 787  01dc cd0000        	call	_sendbyte
 789                     ; 244 sendbyte(0b00000001,1);
 791  01df ae0101        	ldw	x,#257
 792  01e2 cd0000        	call	_sendbyte
 794                     ; 245 LCD_SetPos(str1,1);
 796  01e5 7b02          	ld	a,(OFST+2,sp)
 797  01e7 ae0001        	ldw	x,#1
 798  01ea 95            	ld	xh,a
 799  01eb cd0000        	call	_LCD_SetPos
 801                     ; 246 sendbyte(0b00100000,1);//7
 803  01ee ae2001        	ldw	x,#8193
 804  01f1 cd0000        	call	_sendbyte
 806                     ; 247 sendbyte(0b00000001,1);
 808  01f4 ae0101        	ldw	x,#257
 809  01f7 cd0000        	call	_sendbyte
 811                     ; 248         break;
 813  01fa 2052          	jra	L312
 814  01fc               L361:
 815                     ; 249     case 8:
 815                     ; 250 LCD_SetPos(str1,0);
 817  01fc 7b02          	ld	a,(OFST+2,sp)
 818  01fe 5f            	clrw	x
 819  01ff 95            	ld	xh,a
 820  0200 cd0000        	call	_LCD_SetPos
 822                     ; 251 sendbyte(0b00000101,1);//8
 824  0203 ae0501        	ldw	x,#1281
 825  0206 cd0000        	call	_sendbyte
 827                     ; 252 sendbyte(0b00000100,1);
 829  0209 ae0401        	ldw	x,#1025
 830  020c cd0000        	call	_sendbyte
 832                     ; 253 LCD_SetPos(str1,1);
 834  020f 7b02          	ld	a,(OFST+2,sp)
 835  0211 ae0001        	ldw	x,#1
 836  0214 95            	ld	xh,a
 837  0215 cd0000        	call	_LCD_SetPos
 839                     ; 254 sendbyte(0b00000010,1);//8
 841  0218 ae0201        	ldw	x,#513
 842  021b cd0000        	call	_sendbyte
 844                     ; 255 sendbyte(0b00000011,1);        
 846  021e ae0301        	ldw	x,#769
 847  0221 cd0000        	call	_sendbyte
 849                     ; 256         break;
 851  0224 2028          	jra	L312
 852  0226               L561:
 853                     ; 257     case 9:
 853                     ; 258 LCD_SetPos(str1,0);
 855  0226 7b02          	ld	a,(OFST+2,sp)
 856  0228 5f            	clrw	x
 857  0229 95            	ld	xh,a
 858  022a cd0000        	call	_LCD_SetPos
 860                     ; 259 sendbyte(0b00000101,1);//9
 862  022d ae0501        	ldw	x,#1281
 863  0230 cd0000        	call	_sendbyte
 865                     ; 260 sendbyte(0b00000100,1);//
 867  0233 ae0401        	ldw	x,#1025
 868  0236 cd0000        	call	_sendbyte
 870                     ; 261 LCD_SetPos(str1,1);
 872  0239 7b02          	ld	a,(OFST+2,sp)
 873  023b ae0001        	ldw	x,#1
 874  023e 95            	ld	xh,a
 875  023f cd0000        	call	_LCD_SetPos
 877                     ; 262 sendbyte(0b00000110,1);//9
 879  0242 ae0601        	ldw	x,#1537
 880  0245 cd0000        	call	_sendbyte
 882                     ; 263 sendbyte(0b00000011,1);
 884  0248 ae0301        	ldw	x,#769
 885  024b cd0000        	call	_sendbyte
 887                     ; 264         break;        
 889  024e               L312:
 890                     ; 266 }
 893  024e 85            	popw	x
 894  024f 81            	ret
 920                     ; 268 void DS1307init (void){//инициализация микросхемы
 921                     	switch	.text
 922  0250               _DS1307init:
 926                     ; 272     i2c_start ();//отправка посылки СТАРТ
 928  0250 cd0000        	call	_i2c_start
 930                     ; 273     I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
 932  0253 a6d0          	ld	a,#208
 933  0255 cd0000        	call	_I2C_SendByte
 935                     ; 274     I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
 937  0258 4f            	clr	a
 938  0259 cd0000        	call	_I2C_SendByte
 940                     ; 275     I2C_SendByte (0b01010101);//установка секунд 55
 942  025c a655          	ld	a,#85
 943  025e cd0000        	call	_I2C_SendByte
 945                     ; 276     I2C_SendByte (0b01011001);//установка минут 00
 947  0261 a659          	ld	a,#89
 948  0263 cd0000        	call	_I2C_SendByte
 950                     ; 277     I2C_SendByte (0b00100011);//установка часов 00  0b00100011
 952  0266 a623          	ld	a,#35
 953  0268 cd0000        	call	_I2C_SendByte
 955                     ; 278     I2C_SendByte (0b00000110);//установка дня ВС
 957  026b a606          	ld	a,#6
 958  026d cd0000        	call	_I2C_SendByte
 960                     ; 279     i2c_stop ();
 962  0270 cd0000        	call	_i2c_stop
 964                     ; 282     i2c_start ();//отправка посылки СТАРТ
 966  0273 cd0000        	call	_i2c_start
 968                     ; 283     I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
 970  0276 a6d0          	ld	a,#208
 971  0278 cd0000        	call	_I2C_SendByte
 973                     ; 284     I2C_SendByte (0b00000111);//вызов регистра clock out
 975  027b a607          	ld	a,#7
 976  027d cd0000        	call	_I2C_SendByte
 978                     ; 285     I2C_SendByte (0b00010000);//включение делителя частоты 1Hz
 980  0280 a610          	ld	a,#16
 981  0282 cd0000        	call	_I2C_SendByte
 983                     ; 286     i2c_stop ();
 985  0285 cd0000        	call	_i2c_stop
 987                     ; 287 }
 990  0288 81            	ret
1025                     ; 289 unsigned char vyb_raz (unsigned char u){
1026                     	switch	.text
1027  0289               _vyb_raz:
1029  0289 88            	push	a
1030       00000000      OFST:	set	0
1033                     ; 290     minee = u;
1035  028a b702          	ld	_minee,a
1036                     ; 291     minee ++; 
1038  028c 3c02          	inc	_minee
1039                     ; 292     if (u == 0b00001001) minee = 0b00010000;//если больше 9 записываем в переменную 10
1041  028e a109          	cp	a,#9
1042  0290 2604          	jrne	L342
1045  0292 35100002      	mov	_minee,#16
1046  0296               L342:
1047                     ; 293     if (u == 0b00011001) minee = 0b00100000;//если больше 19 записываем в переменную 20
1049  0296 7b01          	ld	a,(OFST+1,sp)
1050  0298 a119          	cp	a,#25
1051  029a 2604          	jrne	L542
1054  029c 35200002      	mov	_minee,#32
1055  02a0               L542:
1056                     ; 294     if (u == 0b00101001) minee = 0b00110000;//если больше 29 записываем в переменную 30
1058  02a0 7b01          	ld	a,(OFST+1,sp)
1059  02a2 a129          	cp	a,#41
1060  02a4 2604          	jrne	L742
1063  02a6 35300002      	mov	_minee,#48
1064  02aa               L742:
1065                     ; 295     if (u == 0b00111001) minee = 0b01000000;//если больше 39 записываем в переменную 40
1067  02aa 7b01          	ld	a,(OFST+1,sp)
1068  02ac a139          	cp	a,#57
1069  02ae 2604          	jrne	L152
1072  02b0 35400002      	mov	_minee,#64
1073  02b4               L152:
1074                     ; 296     if (u == 0b01001001) minee = 0b01010000;//если больше 49 записываем в переменную 50
1076  02b4 7b01          	ld	a,(OFST+1,sp)
1077  02b6 a149          	cp	a,#73
1078  02b8 2604          	jrne	L352
1081  02ba 35500002      	mov	_minee,#80
1082  02be               L352:
1083                     ; 297     if (u == 0b01011001) minee = 0b00000000;//если больше 59 то обнуляем   
1085  02be 7b01          	ld	a,(OFST+1,sp)
1086  02c0 a159          	cp	a,#89
1087  02c2 2602          	jrne	L552
1090  02c4 3f02          	clr	_minee
1091  02c6               L552:
1092                     ; 298 return minee;
1094  02c6 b602          	ld	a,_minee
1097  02c8 5b01          	addw	sp,#1
1098  02ca 81            	ret
1133                     ; 301 unsigned char vyb_raz_h (unsigned char u){
1134                     	switch	.text
1135  02cb               _vyb_raz_h:
1137  02cb 88            	push	a
1138       00000000      OFST:	set	0
1141                     ; 302     houree = u;
1143  02cc b701          	ld	_houree,a
1144                     ; 303     houree ++;
1146  02ce 3c01          	inc	_houree
1147                     ; 304     if (u == 0b00001001) houree = 0b00010000;//если больше 9 то записываем в переменную 10
1149  02d0 a109          	cp	a,#9
1150  02d2 2604          	jrne	L572
1153  02d4 35100001      	mov	_houree,#16
1154  02d8               L572:
1155                     ; 305     if (u == 0b00011001) houree = 0b00100000;//если больше 19 то записываем в переменную 20
1157  02d8 7b01          	ld	a,(OFST+1,sp)
1158  02da a119          	cp	a,#25
1159  02dc 2604          	jrne	L772
1162  02de 35200001      	mov	_houree,#32
1163  02e2               L772:
1164                     ; 306     if (u == 0b00100011) houree = 0b00000000;//если больше 23 то обнуляем
1166  02e2 7b01          	ld	a,(OFST+1,sp)
1167  02e4 a123          	cp	a,#35
1168  02e6 2602          	jrne	L103
1171  02e8 3f01          	clr	_houree
1172  02ea               L103:
1173                     ; 307 return houree;
1175  02ea b601          	ld	a,_houree
1178  02ec 5b01          	addw	sp,#1
1179  02ee 81            	ret
1225                     ; 310 void sending_data (unsigned char registerr, unsigned char data){//register - адрес регистра данных 
1226                     	switch	.text
1227  02ef               _sending_data:
1229  02ef 89            	pushw	x
1230       00000000      OFST:	set	0
1233                     ; 312 i2c_start ();//отправка посылки СТАРТ
1235  02f0 cd0000        	call	_i2c_start
1237                     ; 313     I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
1239  02f3 a6d0          	ld	a,#208
1240  02f5 cd0000        	call	_I2C_SendByte
1242                     ; 314     I2C_SendByte (registerr);//вызов регистра минут
1244  02f8 7b01          	ld	a,(OFST+1,sp)
1245  02fa cd0000        	call	_I2C_SendByte
1247                     ; 315     I2C_SendByte (data);//установка минут
1249  02fd 7b02          	ld	a,(OFST+2,sp)
1250  02ff cd0000        	call	_I2C_SendByte
1252                     ; 316     i2c_stop ();    
1254  0302 cd0000        	call	_i2c_stop
1256                     ; 317 }
1259  0305 85            	popw	x
1260  0306 81            	ret
1322                     .const:	section	.text
1323  0000               L05:
1324  0000 00009c40      	dc.l	40000
1325                     ; 319 void button (unsigned char u,unsigned char i){
1326                     	switch	.text
1327  0307               _button:
1329  0307 89            	pushw	x
1330  0308 89            	pushw	x
1331       00000002      OFST:	set	2
1334                     ; 320   unsigned int butcount=0;
1336  0309 5f            	clrw	x
1337  030a 1f01          	ldw	(OFST-1,sp),x
1340  030c acc303c3      	jpf	L753
1341  0310               L353:
1342                     ; 323     if(butcount < 40000)
1344  0310 9c            	rvf
1345  0311 1e01          	ldw	x,(OFST-1,sp)
1346  0313 cd0000        	call	c_uitolx
1348  0316 ae0000        	ldw	x,#L05
1349  0319 cd0000        	call	c_lcmp
1351  031c 2e0b          	jrsge	L363
1352                     ; 325       butcount++;//Пауза для подавления дребезга
1354  031e 1e01          	ldw	x,(OFST-1,sp)
1355  0320 1c0001        	addw	x,#1
1356  0323 1f01          	ldw	(OFST-1,sp),x
1359  0325 acc303c3      	jpf	L753
1360  0329               L363:
1361                     ; 329     if (i == 1){//настройка минут
1363  0329 7b04          	ld	a,(OFST+2,sp)
1364  032b a101          	cp	a,#1
1365  032d 260d          	jrne	L763
1366                     ; 330     vyb_raz (u);
1368  032f 7b03          	ld	a,(OFST+1,sp)
1369  0331 cd0289        	call	_vyb_raz
1371                     ; 331     sending_data (0b00000001, minee);
1373  0334 b602          	ld	a,_minee
1374  0336 ae0100        	ldw	x,#256
1375  0339 97            	ld	xl,a
1376  033a adb3          	call	_sending_data
1378  033c               L763:
1379                     ; 333     if (i == 2){//настройка часов
1381  033c 7b04          	ld	a,(OFST+2,sp)
1382  033e a102          	cp	a,#2
1383  0340 260c          	jrne	L173
1384                     ; 334     vyb_raz_h (u);
1386  0342 7b03          	ld	a,(OFST+1,sp)
1387  0344 ad85          	call	_vyb_raz_h
1389                     ; 335     sending_data (0b00000010, houree);
1391  0346 b601          	ld	a,_houree
1392  0348 ae0200        	ldw	x,#512
1393  034b 97            	ld	xl,a
1394  034c ada1          	call	_sending_data
1396  034e               L173:
1397                     ; 337     if (i == 3){//настройка дня недели
1399  034e 7b04          	ld	a,(OFST+2,sp)
1400  0350 a103          	cp	a,#3
1401  0352 260a          	jrne	L373
1402                     ; 338     Weekdays ++;
1404  0354 3c00          	inc	_Weekdays
1405                     ; 339     sending_data (0b00000011, Weekdays); 
1407  0356 b600          	ld	a,_Weekdays
1408  0358 ae0300        	ldw	x,#768
1409  035b 97            	ld	xl,a
1410  035c ad91          	call	_sending_data
1412  035e               L373:
1413                     ; 341          if (i == 4){//настройка будильника - часы
1415  035e 7b04          	ld	a,(OFST+2,sp)
1416  0360 a104          	cp	a,#4
1417  0362 263b          	jrne	L573
1418                     ; 342              alarm_2 ++;
1420  0364 3c1a          	inc	_alarm_2
1421                     ; 343                 if (alarm_1 == 0b00110010 && alarm_2 == 0b00110100){//если часы > 23, то равно 00 часов
1423  0366 b61b          	ld	a,_alarm_1
1424  0368 a132          	cp	a,#50
1425  036a 260e          	jrne	L773
1427  036c b61a          	ld	a,_alarm_2
1428  036e a134          	cp	a,#52
1429  0370 2608          	jrne	L773
1430                     ; 344                  alarm_1 = 0b00110000;
1432  0372 3530001b      	mov	_alarm_1,#48
1433                     ; 345                  alarm_2 = 0b00110000; 
1435  0376 3530001a      	mov	_alarm_2,#48
1436  037a               L773:
1437                     ; 347                 if (alarm_1 + alarm_2 > 0b01101010){//если часы > 19, то равно 20 часов
1439  037a 9c            	rvf
1440  037b b61b          	ld	a,_alarm_1
1441  037d 5f            	clrw	x
1442  037e bb1a          	add	a,_alarm_2
1443  0380 2401          	jrnc	L25
1444  0382 5c            	incw	x
1445  0383               L25:
1446  0383 02            	rlwa	x,a
1447  0384 a3006b        	cpw	x,#107
1448  0387 2f08          	jrslt	L104
1449                     ; 348                  alarm_1 = 0b00110010;
1451  0389 3532001b      	mov	_alarm_1,#50
1452                     ; 349                  alarm_2 = 0b00110000; 
1454  038d 3530001a      	mov	_alarm_2,#48
1455  0391               L104:
1456                     ; 351              if (alarm_2 > 0b00111001){//если часы > 09, то равно 10 часов
1458  0391 b61a          	ld	a,_alarm_2
1459  0393 a13a          	cp	a,#58
1460  0395 2508          	jrult	L573
1461                     ; 352              alarm_1 = 0b00110001;
1463  0397 3531001b      	mov	_alarm_1,#49
1464                     ; 353              alarm_2 = 0b00110000;
1466  039b 3530001a      	mov	_alarm_2,#48
1467  039f               L573:
1468                     ; 356           if (i == 5){//настройка будильника - минуты
1470  039f 7b04          	ld	a,(OFST+2,sp)
1471  03a1 a105          	cp	a,#5
1472  03a3 2628          	jrne	L163
1473                     ; 357             alarm_4 ++;
1475  03a5 3c18          	inc	_alarm_4
1476                     ; 358             if (alarm_4 == 0b00111010) {
1478  03a7 b618          	ld	a,_alarm_4
1479  03a9 a13a          	cp	a,#58
1480  03ab 2606          	jrne	L704
1481                     ; 359                 alarm_4 = 0b00110000;
1483  03ad 35300018      	mov	_alarm_4,#48
1484                     ; 360                 alarm_3 ++;
1486  03b1 3c19          	inc	_alarm_3
1487  03b3               L704:
1488                     ; 362             if (alarm_3 > 0b00110101){
1490  03b3 b619          	ld	a,_alarm_3
1491  03b5 a136          	cp	a,#54
1492  03b7 2514          	jrult	L163
1493                     ; 363                 alarm_4 = 0b00110000;
1495  03b9 35300018      	mov	_alarm_4,#48
1496                     ; 364                 alarm_3 = 0b00110000;//
1498  03bd 35300019      	mov	_alarm_3,#48
1499  03c1 200a          	jra	L163
1500  03c3               L753:
1501                     ; 321   while((GPIOC->IDR & (1 << 5)) == 0 )
1503  03c3 c6500b        	ld	a,20491
1504  03c6 a520          	bcp	a,#32
1505  03c8 2603          	jrne	L45
1506  03ca cc0310        	jp	L353
1507  03cd               L45:
1508  03cd               L163:
1509                     ; 370 }
1512  03cd 5b04          	addw	sp,#4
1513  03cf 81            	ret
1541                     ; 372 void Day_Switch (void){
1542                     	switch	.text
1543  03d0               _Day_Switch:
1547                     ; 373 switch (Weekdays){
1549  03d0 b600          	ld	a,_Weekdays
1551                     ; 406         break;        
1552  03d2 4d            	tnz	a
1553  03d3 2714          	jreq	L314
1554  03d5 4a            	dec	a
1555  03d6 271b          	jreq	L514
1556  03d8 4a            	dec	a
1557  03d9 2722          	jreq	L714
1558  03db 4a            	dec	a
1559  03dc 2729          	jreq	L124
1560  03de 4a            	dec	a
1561  03df 2730          	jreq	L324
1562  03e1 4a            	dec	a
1563  03e2 2737          	jreq	L524
1564  03e4 4a            	dec	a
1565  03e5 273e          	jreq	L724
1566  03e7 2044          	jra	L744
1567  03e9               L314:
1568                     ; 374     case 0:
1568                     ; 375 DAY_1 = 0b10101000;//П
1570  03e9 35a8000d      	mov	_DAY_1,#168
1571                     ; 376 DAY_2 = 0b01001000;//Н
1573  03ed 3548000e      	mov	_DAY_2,#72
1574                     ; 377         break;
1576  03f1 203a          	jra	L744
1577  03f3               L514:
1578                     ; 378     case 1:
1578                     ; 379 DAY_1 = 0b01000010;//В
1580  03f3 3542000d      	mov	_DAY_1,#66
1581                     ; 380 DAY_2 = 0b01010100;//Т
1583  03f7 3554000e      	mov	_DAY_2,#84
1584                     ; 381         break;
1586  03fb 2030          	jra	L744
1587  03fd               L714:
1588                     ; 382     case 2:
1588                     ; 383 DAY_1 = 0b01000011;//С
1590  03fd 3543000d      	mov	_DAY_1,#67
1591                     ; 384 DAY_2 = 0b01010000;//Р
1593  0401 3550000e      	mov	_DAY_2,#80
1594                     ; 385         break;
1596  0405 2026          	jra	L744
1597  0407               L124:
1598                     ; 386     case 3:
1598                     ; 387 DAY_1 = 0b10101011;//Ч
1600  0407 35ab000d      	mov	_DAY_1,#171
1601                     ; 388 DAY_2 = 0b01010100;//Т
1603  040b 3554000e      	mov	_DAY_2,#84
1604                     ; 389         break;
1606  040f 201c          	jra	L744
1607  0411               L324:
1608                     ; 390     case 4:
1608                     ; 391 DAY_1 = 0b10101000;//П
1610  0411 35a8000d      	mov	_DAY_1,#168
1611                     ; 392 DAY_2 = 0b01010100;//Т
1613  0415 3554000e      	mov	_DAY_2,#84
1614                     ; 393         break;    
1616  0419 2012          	jra	L744
1617  041b               L524:
1618                     ; 394     case 5:
1618                     ; 395 DAY_1 = 0b01000011;//С
1620  041b 3543000d      	mov	_DAY_1,#67
1621                     ; 396 DAY_2 = 0b10100000;//Б
1623  041f 35a0000e      	mov	_DAY_2,#160
1624                     ; 397         break;    
1626  0423 2008          	jra	L744
1627  0425               L724:
1628                     ; 398     case 6:
1628                     ; 399 DAY_1 = 0b01000010;//В
1630  0425 3542000d      	mov	_DAY_1,#66
1631                     ; 400 DAY_2 = 0b01000011;//С
1633  0429 3543000e      	mov	_DAY_2,#67
1634                     ; 401         break;
1636  042d               L744:
1637                     ; 408 }
1640  042d 81            	ret
1675                     ; 410 void lcd_mask (unsigned char mask){
1676                     	switch	.text
1677  042e               _lcd_mask:
1681                     ; 411 switch (mask){
1684                     ; 449 break;
1685  042e 4d            	tnz	a
1686  042f 2710          	jreq	L154
1687  0431 4a            	dec	a
1688  0432 2747          	jreq	L354
1689  0434 4a            	dec	a
1690  0435 275e          	jreq	L554
1691  0437 4a            	dec	a
1692  0438 2603cc04bb    	jreq	L754
1693  043d acfd04fd      	jpf	L105
1694  0441               L154:
1695                     ; 412     case 0:
1695                     ; 413 sendbyte(0b10100000,1);//Б
1697  0441 aea001        	ldw	x,#40961
1698  0444 cd0000        	call	_sendbyte
1700                     ; 414 sendbyte(0b01111001,1);//у
1702  0447 ae7901        	ldw	x,#30977
1703  044a cd0000        	call	_sendbyte
1705                     ; 415 sendbyte(0b11100011,1);//д
1707  044d aee301        	ldw	x,#58113
1708  0450 cd0000        	call	_sendbyte
1710                     ; 416 sendbyte(0b10111000,1);//и
1712  0453 aeb801        	ldw	x,#47105
1713  0456 cd0000        	call	_sendbyte
1715                     ; 417 sendbyte(0b10111011,1);//л
1717  0459 aebb01        	ldw	x,#47873
1718  045c cd0000        	call	_sendbyte
1720                     ; 418 sendbyte(0b11000100,1);//ь
1722  045f aec401        	ldw	x,#50177
1723  0462 cd0000        	call	_sendbyte
1725                     ; 419 sendbyte(0b10111101,1);//н
1727  0465 aebd01        	ldw	x,#48385
1728  0468 cd0000        	call	_sendbyte
1730                     ; 420 sendbyte(0b10111000,1);//и
1732  046b aeb801        	ldw	x,#47105
1733  046e cd0000        	call	_sendbyte
1735                     ; 421 sendbyte(0b10111010,1);//к       
1737  0471 aeba01        	ldw	x,#47617
1738  0474 cd0000        	call	_sendbyte
1740                     ; 422 break;
1742  0477 acfd04fd      	jpf	L105
1743  047b               L354:
1744                     ; 423     case 1:
1744                     ; 424 sendbyte(0b10101011,1);//Ч
1746  047b aeab01        	ldw	x,#43777
1747  047e cd0000        	call	_sendbyte
1749                     ; 425 sendbyte(0b01100001,1);//а
1751  0481 ae6101        	ldw	x,#24833
1752  0484 cd0000        	call	_sendbyte
1754                     ; 426 sendbyte(0b01100011,1);//с
1756  0487 ae6301        	ldw	x,#25345
1757  048a cd0000        	call	_sendbyte
1759                     ; 427 sendbyte(0b11000011,1);//ы
1761  048d aec301        	ldw	x,#49921
1762  0490 cd0000        	call	_sendbyte
1764                     ; 428 break;
1766  0493 2068          	jra	L105
1767  0495               L554:
1768                     ; 429     case 2:
1768                     ; 430 sendbyte(0b01001101,1);//М
1770  0495 ae4d01        	ldw	x,#19713
1771  0498 cd0000        	call	_sendbyte
1773                     ; 431 sendbyte(0b10111000,1);//и
1775  049b aeb801        	ldw	x,#47105
1776  049e cd0000        	call	_sendbyte
1778                     ; 432 sendbyte(0b10111101,1);//н
1780  04a1 aebd01        	ldw	x,#48385
1781  04a4 cd0000        	call	_sendbyte
1783                     ; 433 sendbyte(0b01111001,1);//у
1785  04a7 ae7901        	ldw	x,#30977
1786  04aa cd0000        	call	_sendbyte
1788                     ; 434 sendbyte(0b10111111,1);//т
1790  04ad aebf01        	ldw	x,#48897
1791  04b0 cd0000        	call	_sendbyte
1793                     ; 435 sendbyte(0b11000011,1);//ы
1795  04b3 aec301        	ldw	x,#49921
1796  04b6 cd0000        	call	_sendbyte
1798                     ; 436 break;
1800  04b9 2042          	jra	L105
1801  04bb               L754:
1802                     ; 437 	 case 3:
1802                     ; 438 sendbyte(0b11100000,1);//Д
1804  04bb aee001        	ldw	x,#57345
1805  04be cd0000        	call	_sendbyte
1807                     ; 439 sendbyte(0b01100101,1);//е
1809  04c1 ae6501        	ldw	x,#25857
1810  04c4 cd0000        	call	_sendbyte
1812                     ; 440 sendbyte(0b10111101,1);//н
1814  04c7 aebd01        	ldw	x,#48385
1815  04ca cd0000        	call	_sendbyte
1817                     ; 441 sendbyte(0b11000100,1);//ь
1819  04cd aec401        	ldw	x,#50177
1820  04d0 cd0000        	call	_sendbyte
1822                     ; 442 sendbyte(0b00100000,1);//_
1824  04d3 ae2001        	ldw	x,#8193
1825  04d6 cd0000        	call	_sendbyte
1827                     ; 443 sendbyte(0b10111101,1);//н
1829  04d9 aebd01        	ldw	x,#48385
1830  04dc cd0000        	call	_sendbyte
1832                     ; 444 sendbyte(0b01100101,1);//е
1834  04df ae6501        	ldw	x,#25857
1835  04e2 cd0000        	call	_sendbyte
1837                     ; 445 sendbyte(0b11100011,1);//д
1839  04e5 aee301        	ldw	x,#58113
1840  04e8 cd0000        	call	_sendbyte
1842                     ; 446 sendbyte(0b01100101,1);//е
1844  04eb ae6501        	ldw	x,#25857
1845  04ee cd0000        	call	_sendbyte
1847                     ; 447 sendbyte(0b10111011,1);//л
1849  04f1 aebb01        	ldw	x,#47873
1850  04f4 cd0000        	call	_sendbyte
1852                     ; 448 sendbyte(0b10111000,1);//и
1854  04f7 aeb801        	ldw	x,#47105
1855  04fa cd0000        	call	_sendbyte
1857                     ; 449 break;
1859  04fd               L105:
1860                     ; 451 }
1863  04fd 81            	ret
1929                     ; 453 void clk_out (void){//
1930                     	switch	.text
1931  04fe               _clk_out:
1933  04fe 89            	pushw	x
1934       00000002      OFST:	set	2
1937                     ; 454     unsigned int butcount = 0;
1939  04ff 5f            	clrw	x
1940  0500 1f01          	ldw	(OFST-1,sp),x
1943  0502 2023          	jra	L525
1944  0504               L125:
1945                     ; 457  if(butcount < 40000)//Подавление дребезга
1947  0504 9c            	rvf
1948  0505 1e01          	ldw	x,(OFST-1,sp)
1949  0507 cd0000        	call	c_uitolx
1951  050a ae0000        	ldw	x,#L05
1952  050d cd0000        	call	c_lcmp
1954  0510 2e09          	jrsge	L135
1955                     ; 459       butcount++;
1957  0512 1e01          	ldw	x,(OFST-1,sp)
1958  0514 1c0001        	addw	x,#1
1959  0517 1f01          	ldw	(OFST-1,sp),x
1962  0519 200c          	jra	L525
1963  051b               L135:
1964                     ; 463   t++;
1966  051b 3c0b          	inc	_t
1967                     ; 464 			if (t > 5) t = 0;//установка флага режима настройки для перехода к следующему пункту меню
1969  051d b60b          	ld	a,_t
1970  051f a106          	cp	a,#6
1971  0521 250b          	jrult	L725
1974  0523 3f0b          	clr	_t
1975  0525 2007          	jra	L725
1976  0527               L525:
1977                     ; 455  while((GPIOC->IDR & (1 << 6)) == 0 )
1979  0527 c6500b        	ld	a,20491
1980  052a a540          	bcp	a,#64
1981  052c 27d6          	jreq	L125
1982  052e               L725:
1983                     ; 469 if (t == 1){
1985  052e b60b          	ld	a,_t
1986  0530 a101          	cp	a,#1
1987  0532 2646          	jrne	L735
1988                     ; 470 digit_out(hourd, 0);//hourd
1990  0534 b603          	ld	a,_hourd
1991  0536 5f            	clrw	x
1992  0537 95            	ld	xh,a
1993  0538 cd0064        	call	_digit_out
1995                     ; 471 digit_out(houre, 2);//houre
1997  053b b604          	ld	a,_houre
1998  053d ae0002        	ldw	x,#2
1999  0540 95            	ld	xh,a
2000  0541 cd0064        	call	_digit_out
2002                     ; 472 button(min,1);//вызов функции изменения значения
2004  0544 b60a          	ld	a,_min
2005  0546 ae0001        	ldw	x,#1
2006  0549 95            	ld	xh,a
2007  054a cd0307        	call	_button
2009                     ; 473 digit_out(mind, 5);
2011  054d b608          	ld	a,_mind
2012  054f ae0005        	ldw	x,#5
2013  0552 95            	ld	xh,a
2014  0553 cd0064        	call	_digit_out
2016                     ; 474 digit_out(mine, 7);
2018  0556 b609          	ld	a,_mine
2019  0558 ae0007        	ldw	x,#7
2020  055b 95            	ld	xh,a
2021  055c cd0064        	call	_digit_out
2023                     ; 475 LCD_SetPos(9,0);
2025  055f ae0900        	ldw	x,#2304
2026  0562 cd0000        	call	_LCD_SetPos
2028                     ; 476 segment_clear (7);//очистка сегмента
2030  0565 a607          	ld	a,#7
2031  0567 cd0012        	call	_segment_clear
2033                     ; 477 LCD_SetPos(9,1);
2035  056a ae0901        	ldw	x,#2305
2036  056d cd0000        	call	_LCD_SetPos
2038                     ; 478 segment_clear (1);//очистка сегмента
2040  0570 a601          	ld	a,#1
2041  0572 cd0012        	call	_segment_clear
2043                     ; 479 lcd_mask(2);//вывод слова "Минуты"
2045  0575 a602          	ld	a,#2
2046  0577 cd042e        	call	_lcd_mask
2048  057a               L735:
2049                     ; 482     if (t == 2){
2051  057a b60b          	ld	a,_t
2052  057c a102          	cp	a,#2
2053  057e 264b          	jrne	L145
2054                     ; 484 button(hour,2);//вызов функции изменения значения
2056  0580 b607          	ld	a,_hour
2057  0582 ae0002        	ldw	x,#2
2058  0585 95            	ld	xh,a
2059  0586 cd0307        	call	_button
2061                     ; 485 digit_out(hourd, 0);//hourd
2063  0589 b603          	ld	a,_hourd
2064  058b 5f            	clrw	x
2065  058c 95            	ld	xh,a
2066  058d cd0064        	call	_digit_out
2068                     ; 486 digit_out(houre, 2);//houre		
2070  0590 b604          	ld	a,_houre
2071  0592 ae0002        	ldw	x,#2
2072  0595 95            	ld	xh,a
2073  0596 cd0064        	call	_digit_out
2075                     ; 487 digit_out(mind, 5);
2077  0599 b608          	ld	a,_mind
2078  059b ae0005        	ldw	x,#5
2079  059e 95            	ld	xh,a
2080  059f cd0064        	call	_digit_out
2082                     ; 488 digit_out(mine, 7);
2084  05a2 b609          	ld	a,_mine
2085  05a4 ae0007        	ldw	x,#7
2086  05a7 95            	ld	xh,a
2087  05a8 cd0064        	call	_digit_out
2089                     ; 489 LCD_SetPos(9,0);
2091  05ab ae0900        	ldw	x,#2304
2092  05ae cd0000        	call	_LCD_SetPos
2094                     ; 490 segment_clear (7);//очистка сегмента
2096  05b1 a607          	ld	a,#7
2097  05b3 cd0012        	call	_segment_clear
2099                     ; 491 LCD_SetPos(9,1);
2101  05b6 ae0901        	ldw	x,#2305
2102  05b9 cd0000        	call	_LCD_SetPos
2104                     ; 492 segment_clear (1);//очистка сегмента
2106  05bc a601          	ld	a,#1
2107  05be cd0012        	call	_segment_clear
2109                     ; 493 lcd_mask (1);//вывод слова "Часы"				
2111  05c1 a601          	ld	a,#1
2112  05c3 cd042e        	call	_lcd_mask
2114                     ; 494 segment_clear (2);//очистка сегмента	
2116  05c6 a602          	ld	a,#2
2117  05c8 cd0012        	call	_segment_clear
2119  05cb               L145:
2120                     ; 497     if (t == 3){
2122  05cb b60b          	ld	a,_t
2123  05cd a103          	cp	a,#3
2124  05cf 263d          	jrne	L345
2125                     ; 498 button(Weekdays,3);
2127  05d1 b600          	ld	a,_Weekdays
2128  05d3 ae0003        	ldw	x,#3
2129  05d6 95            	ld	xh,a
2130  05d7 cd0307        	call	_button
2132                     ; 499 LCD_SetPos(0,0);
2134  05da 5f            	clrw	x
2135  05db cd0000        	call	_LCD_SetPos
2137                     ; 500 segment_clear (16);//очистка сегмента
2139  05de a610          	ld	a,#16
2140  05e0 cd0012        	call	_segment_clear
2142                     ; 501 LCD_SetPos(0,1);
2144  05e3 ae0001        	ldw	x,#1
2145  05e6 cd0000        	call	_LCD_SetPos
2147                     ; 502 lcd_mask(3);//вывод слова "День недели"
2149  05e9 a603          	ld	a,#3
2150  05eb cd042e        	call	_lcd_mask
2152                     ; 503 segment_clear (3);//очистка сегмента
2154  05ee a603          	ld	a,#3
2155  05f0 cd0012        	call	_segment_clear
2157                     ; 504 Day_Switch ();
2159  05f3 cd03d0        	call	_Day_Switch
2161                     ; 505 LCD_SetPos(14,1);
2163  05f6 ae0e01        	ldw	x,#3585
2164  05f9 cd0000        	call	_LCD_SetPos
2166                     ; 506 sendbyte(DAY_1,1);
2168  05fc b60d          	ld	a,_DAY_1
2169  05fe ae0001        	ldw	x,#1
2170  0601 95            	ld	xh,a
2171  0602 cd0000        	call	_sendbyte
2173                     ; 507 sendbyte(DAY_2,1);
2175  0605 b60e          	ld	a,_DAY_2
2176  0607 ae0001        	ldw	x,#1
2177  060a 95            	ld	xh,a
2178  060b cd0000        	call	_sendbyte
2180  060e               L345:
2181                     ; 510     if (t == 4){
2183  060e b60b          	ld	a,_t
2184  0610 a104          	cp	a,#4
2185  0612 265d          	jrne	L545
2186                     ; 511 button(hour_alar,4);
2188  0614 b606          	ld	a,_hour_alar
2189  0616 ae0004        	ldw	x,#4
2190  0619 95            	ld	xh,a
2191  061a cd0307        	call	_button
2193                     ; 512         LCD_SetPos(0,0);
2195  061d 5f            	clrw	x
2196  061e cd0000        	call	_LCD_SetPos
2198                     ; 513 lcd_mask(0);//вывод слова "Будильник"
2200  0621 4f            	clr	a
2201  0622 cd042e        	call	_lcd_mask
2203                     ; 517         LCD_SetPos(0,1);
2205  0625 ae0001        	ldw	x,#1
2206  0628 cd0000        	call	_LCD_SetPos
2208                     ; 518 lcd_mask (1);//вывод слова "Часы"
2210  062b a601          	ld	a,#1
2211  062d cd042e        	call	_lcd_mask
2213                     ; 519         LCD_SetPos(5,1);
2215  0630 ae0501        	ldw	x,#1281
2216  0633 cd0000        	call	_LCD_SetPos
2218                     ; 520         sendbyte(alarm_1,1);
2220  0636 b61b          	ld	a,_alarm_1
2221  0638 ae0001        	ldw	x,#1
2222  063b 95            	ld	xh,a
2223  063c cd0000        	call	_sendbyte
2225                     ; 521         sendbyte(alarm_2,1);
2227  063f b61a          	ld	a,_alarm_2
2228  0641 ae0001        	ldw	x,#1
2229  0644 95            	ld	xh,a
2230  0645 cd0000        	call	_sendbyte
2232                     ; 522 segment_clear (9);//очистка сегмента
2234  0648 a609          	ld	a,#9
2235  064a cd0012        	call	_segment_clear
2237                     ; 524     i2c_start ();//отправка посылки СТАРТ
2239  064d cd0000        	call	_i2c_start
2241                     ; 525     I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
2243  0650 a6d0          	ld	a,#208
2244  0652 cd0000        	call	_I2C_SendByte
2246                     ; 526     I2C_SendByte (0b00001000);//вызов регистра ROM ОЗУ
2248  0655 a608          	ld	a,#8
2249  0657 cd0000        	call	_I2C_SendByte
2251                     ; 527     I2C_SendByte (alarm_1);//
2253  065a b61b          	ld	a,_alarm_1
2254  065c cd0000        	call	_I2C_SendByte
2256                     ; 528 	  I2C_SendByte (alarm_2);//	
2258  065f b61a          	ld	a,_alarm_2
2259  0661 cd0000        	call	_I2C_SendByte
2261                     ; 529     i2c_stop ();
2263  0664 cd0000        	call	_i2c_stop
2265                     ; 530 *address_1 = alarm_1;//записываем переменную по адресу ПЗУ
2267  0667 b61b          	ld	a,_alarm_1
2268  0669 92c703        	ld	[_address_1.w],a
2269                     ; 531 *address_2 = alarm_2;//записываем переменную по адресу ПЗУ
2271  066c b61a          	ld	a,_alarm_2
2272  066e 92c705        	ld	[_address_2.w],a
2273  0671               L545:
2274                     ; 534     if (t == 5){
2276  0671 b60b          	ld	a,_t
2277  0673 a105          	cp	a,#5
2278  0675 2643          	jrne	L745
2279                     ; 535         button(alarm_number,5);
2281  0677 b60c          	ld	a,_alarm_number
2282  0679 ae0005        	ldw	x,#5
2283  067c 95            	ld	xh,a
2284  067d cd0307        	call	_button
2286                     ; 536         LCD_SetPos(0,0);
2288  0680 5f            	clrw	x
2289  0681 cd0000        	call	_LCD_SetPos
2291                     ; 537 lcd_mask(0);//вывод слова "Будильник"
2293  0684 4f            	clr	a
2294  0685 cd042e        	call	_lcd_mask
2296                     ; 541         LCD_SetPos(0,1);
2298  0688 ae0001        	ldw	x,#1
2299  068b cd0000        	call	_LCD_SetPos
2301                     ; 542 lcd_mask(2);//вывод слова "Минуты"
2303  068e a602          	ld	a,#2
2304  0690 cd042e        	call	_lcd_mask
2306                     ; 543 segment_clear (1);//очистка сегмента
2308  0693 a601          	ld	a,#1
2309  0695 cd0012        	call	_segment_clear
2311                     ; 544         LCD_SetPos(7,1);
2313  0698 ae0701        	ldw	x,#1793
2314  069b cd0000        	call	_LCD_SetPos
2316                     ; 545         sendbyte(alarm_3,1);
2318  069e b619          	ld	a,_alarm_3
2319  06a0 ae0001        	ldw	x,#1
2320  06a3 95            	ld	xh,a
2321  06a4 cd0000        	call	_sendbyte
2323                     ; 546         sendbyte(alarm_4,1);
2325  06a7 b618          	ld	a,_alarm_4
2326  06a9 ae0001        	ldw	x,#1
2327  06ac 95            	ld	xh,a
2328  06ad cd0000        	call	_sendbyte
2330                     ; 547 *address_3 = alarm_3;//записываем переменную по адресу ПЗУ
2332  06b0 b619          	ld	a,_alarm_3
2333  06b2 92c707        	ld	[_address_3.w],a
2334                     ; 548 *address_4 = alarm_4;//записываем переменную по адресу ПЗУ
2336  06b5 b618          	ld	a,_alarm_4
2337  06b7 92c709        	ld	[_address_4.w],a
2338  06ba               L745:
2339                     ; 551 if (t == 0){
2341  06ba 3d0b          	tnz	_t
2342  06bc 2703          	jreq	L46
2343  06be cc075d        	jp	L155
2344  06c1               L46:
2345                     ; 552     Day_Switch ();
2347  06c1 cd03d0        	call	_Day_Switch
2349                     ; 553     if (Weekdays > 0b00000110) Weekdays = 0;
2351  06c4 b600          	ld	a,_Weekdays
2352  06c6 a107          	cp	a,#7
2353  06c8 2502          	jrult	L355
2356  06ca 3f00          	clr	_Weekdays
2357  06cc               L355:
2358                     ; 554 digit_out(hourd, 0);//hourd
2360  06cc b603          	ld	a,_hourd
2361  06ce 5f            	clrw	x
2362  06cf 95            	ld	xh,a
2363  06d0 cd0064        	call	_digit_out
2365                     ; 555 digit_out(houre, 2);//houre
2367  06d3 b604          	ld	a,_houre
2368  06d5 ae0002        	ldw	x,#2
2369  06d8 95            	ld	xh,a
2370  06d9 cd0064        	call	_digit_out
2372                     ; 556 LCD_SetPos(4,0);
2374  06dc ae0400        	ldw	x,#1024
2375  06df cd0000        	call	_LCD_SetPos
2377                     ; 557 sendbyte(0b00101110,1);
2379  06e2 ae2e01        	ldw	x,#11777
2380  06e5 cd0000        	call	_sendbyte
2382                     ; 558 LCD_SetPos(4,1);
2384  06e8 ae0401        	ldw	x,#1025
2385  06eb cd0000        	call	_LCD_SetPos
2387                     ; 559 sendbyte(0b11011111,1);
2389  06ee aedf01        	ldw	x,#57089
2390  06f1 cd0000        	call	_sendbyte
2392                     ; 560 digit_out(mind, 5);
2394  06f4 b608          	ld	a,_mind
2395  06f6 ae0005        	ldw	x,#5
2396  06f9 95            	ld	xh,a
2397  06fa cd0064        	call	_digit_out
2399                     ; 561 digit_out(mine, 7);
2401  06fd b609          	ld	a,_mine
2402  06ff ae0007        	ldw	x,#7
2403  0702 95            	ld	xh,a
2404  0703 cd0064        	call	_digit_out
2406                     ; 562 LCD_SetPos(9,0);
2408  0706 ae0900        	ldw	x,#2304
2409  0709 cd0000        	call	_LCD_SetPos
2411                     ; 563 sendbyte(0b00101110,1);
2413  070c ae2e01        	ldw	x,#11777
2414  070f cd0000        	call	_sendbyte
2416                     ; 564 LCD_SetPos(9,1);
2418  0712 ae0901        	ldw	x,#2305
2419  0715 cd0000        	call	_LCD_SetPos
2421                     ; 565 sendbyte(0b11011111,1);
2423  0718 aedf01        	ldw	x,#57089
2424  071b cd0000        	call	_sendbyte
2426                     ; 566 digit_out(secd, 10);
2428  071e b60c          	ld	a,_secd
2429  0720 ae000a        	ldw	x,#10
2430  0723 95            	ld	xh,a
2431  0724 cd0064        	call	_digit_out
2433                     ; 567 digit_out(sece, 12);
2435  0727 b60d          	ld	a,_sece
2436  0729 ae000c        	ldw	x,#12
2437  072c 95            	ld	xh,a
2438  072d cd0064        	call	_digit_out
2440                     ; 568 LCD_SetPos(14,0);
2442  0730 ae0e00        	ldw	x,#3584
2443  0733 cd0000        	call	_LCD_SetPos
2445                     ; 569 sendbyte(0b11101101,1);
2447  0736 aeed01        	ldw	x,#60673
2448  0739 cd0000        	call	_sendbyte
2450                     ; 570 sendbyte(alarm_number,1);
2452  073c b60c          	ld	a,_alarm_number
2453  073e ae0001        	ldw	x,#1
2454  0741 95            	ld	xh,a
2455  0742 cd0000        	call	_sendbyte
2457                     ; 571 LCD_SetPos(14,1);
2459  0745 ae0e01        	ldw	x,#3585
2460  0748 cd0000        	call	_LCD_SetPos
2462                     ; 572 sendbyte(DAY_1,1);//
2464  074b b60d          	ld	a,_DAY_1
2465  074d ae0001        	ldw	x,#1
2466  0750 95            	ld	xh,a
2467  0751 cd0000        	call	_sendbyte
2469                     ; 573 sendbyte(DAY_2,1);//
2471  0754 b60e          	ld	a,_DAY_2
2472  0756 ae0001        	ldw	x,#1
2473  0759 95            	ld	xh,a
2474  075a cd0000        	call	_sendbyte
2476  075d               L155:
2477                     ; 575 }
2480  075d 85            	popw	x
2481  075e 81            	ret
2526                     ; 578 void sets_CGRAM (char* pot){
2527                     	switch	.text
2528  075f               _sets_CGRAM:
2530  075f 89            	pushw	x
2531  0760 88            	push	a
2532       00000001      OFST:	set	1
2535                     ; 580   for (x = 0; x <= 7; x++){
2537  0761 0f01          	clr	(OFST+0,sp)
2539  0763               L775:
2540                     ; 581     sendbyte(pot[x],1);
2542  0763 7b01          	ld	a,(OFST+0,sp)
2543  0765 5f            	clrw	x
2544  0766 97            	ld	xl,a
2545  0767 72fb02        	addw	x,(OFST+1,sp)
2546  076a f6            	ld	a,(x)
2547  076b ae0001        	ldw	x,#1
2548  076e 95            	ld	xh,a
2549  076f cd0000        	call	_sendbyte
2551                     ; 580   for (x = 0; x <= 7; x++){
2553  0772 0c01          	inc	(OFST+0,sp)
2557  0774 7b01          	ld	a,(OFST+0,sp)
2558  0776 a108          	cp	a,#8
2559  0778 25e9          	jrult	L775
2560                     ; 583 }
2563  077a 5b03          	addw	sp,#3
2564  077c 81            	ret
2631                     ; 588 main()
2631                     ; 589 {
2632                     	switch	.text
2633  077d               _main:
2635  077d 88            	push	a
2636       00000001      OFST:	set	1
2639                     ; 594 	CLK->CKDIVR = 0b00000000; //Делитель частоты внутреннего осцилятора = 8; тактовой частоты ЦПУ -128
2641  077e 725f50c6      	clr	20678
2642                     ; 596 	GPIOA->DDR |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Выход
2644  0782 c65002        	ld	a,20482
2645  0785 aa0e          	or	a,#14
2646  0787 c75002        	ld	20482,a
2647                     ; 597 	GPIOA->CR1 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Выход типа Push-pull
2649  078a c65003        	ld	a,20483
2650  078d aa0e          	or	a,#14
2651  078f c75003        	ld	20483,a
2652                     ; 598 	GPIOA->CR2 |= (1<<3) | (1<<2) | (1<<1);// | (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц.
2654  0792 c65004        	ld	a,20484
2655  0795 aa0e          	or	a,#14
2656  0797 c75004        	ld	20484,a
2657                     ; 600 	GPIOD->DDR |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Выход
2659  079a c65011        	ld	a,20497
2660  079d aa7e          	or	a,#126
2661  079f c75011        	ld	20497,a
2662                     ; 601 	GPIOD->CR1 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Выход типа Push-pull
2664  07a2 c65012        	ld	a,20498
2665  07a5 aa7e          	or	a,#126
2666  07a7 c75012        	ld	20498,a
2667                     ; 602 	GPIOD->CR2 |= (1<<6) | (1<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1);//Скорость переключения - до 10 МГц.
2669  07aa c65013        	ld	a,20499
2670  07ad aa7e          	or	a,#126
2671  07af c75013        	ld	20499,a
2672                     ; 604 	GPIOC->DDR &= ~((1<<5) | (1<<4) | (1<<3));//вход
2674  07b2 c6500c        	ld	a,20492
2675  07b5 a4c7          	and	a,#199
2676  07b7 c7500c        	ld	20492,a
2677                     ; 605 	GPIOC->CR1 |= (1<<5) | (1<<4) | (1<<3);//вход с подтягивающим резистором  
2679  07ba c6500d        	ld	a,20493
2680  07bd aa38          	or	a,#56
2681  07bf c7500d        	ld	20493,a
2682                     ; 606 	GPIOC->CR2 |= (1<<5) | (1<<4) | (1<<3);//Скорость переключения - до 10 МГц. 
2684  07c2 c6500e        	ld	a,20494
2685  07c5 aa38          	or	a,#56
2686  07c7 c7500e        	ld	20494,a
2687                     ; 608 	FLASH->DUKR = 0b10101110;
2689  07ca 35ae5064      	mov	20580,#174
2690                     ; 609 	FLASH->DUKR = 0b01010110;
2692  07ce 35565064      	mov	20580,#86
2693                     ; 611 	delay_ms(50);
2695  07d2 ae0032        	ldw	x,#50
2696  07d5 cd0000        	call	_delay_ms
2698                     ; 612 	DS1307init();
2700  07d8 cd0250        	call	_DS1307init
2702                     ; 614 	delay_ms(50);
2704  07db ae0032        	ldw	x,#50
2705  07de cd0000        	call	_delay_ms
2707                     ; 615 	LCD_Init();
2709  07e1 cd0000        	call	_LCD_Init
2711                     ; 616 	delay_ms(50);
2713  07e4 ae0032        	ldw	x,#50
2714  07e7 cd0000        	call	_delay_ms
2716                     ; 617 	sendbyte(0b01000000,0);//sets CGRAM address
2718  07ea ae4000        	ldw	x,#16384
2719  07ed cd0000        	call	_sendbyte
2721                     ; 618   sets_CGRAM (str01);
2723  07f0 ae0011        	ldw	x,#_str01
2724  07f3 cd075f        	call	_sets_CGRAM
2726                     ; 619   sets_CGRAM (str02);
2728  07f6 ae0019        	ldw	x,#_str02
2729  07f9 cd075f        	call	_sets_CGRAM
2731                     ; 620   sets_CGRAM (str03);
2733  07fc ae0021        	ldw	x,#_str03
2734  07ff cd075f        	call	_sets_CGRAM
2736                     ; 621   sets_CGRAM (str04);
2738  0802 ae0029        	ldw	x,#_str04
2739  0805 cd075f        	call	_sets_CGRAM
2741                     ; 622   sets_CGRAM (str05);
2743  0808 ae0031        	ldw	x,#_str05
2744  080b cd075f        	call	_sets_CGRAM
2746                     ; 623   sets_CGRAM (str06);
2748  080e ae0039        	ldw	x,#_str06
2749  0811 cd075f        	call	_sets_CGRAM
2751                     ; 624   sets_CGRAM (str07);
2753  0814 ae0041        	ldw	x,#_str07
2754  0817 cd075f        	call	_sets_CGRAM
2756                     ; 625   sets_CGRAM (str08);
2758  081a ae0049        	ldw	x,#_str08
2759  081d cd075f        	call	_sets_CGRAM
2761                     ; 626 	sendbyte(0b00000001,0);//очистка дисплея*/
2763  0820 ae0100        	ldw	x,#256
2764  0823 cd0000        	call	_sendbyte
2766                     ; 632 	alarm_1 = *address_1;
2768  0826 92c603        	ld	a,[_address_1.w]
2769  0829 b71b          	ld	_alarm_1,a
2770                     ; 633 	alarm_2 = *address_2;
2772  082b 92c605        	ld	a,[_address_2.w]
2773  082e b71a          	ld	_alarm_2,a
2774                     ; 634 	alarm_3 = *address_3;
2776  0830 92c607        	ld	a,[_address_3.w]
2777  0833 b719          	ld	_alarm_3,a
2778                     ; 635 	alarm_4 = *address_4;
2780  0835 92c609        	ld	a,[_address_4.w]
2781  0838 b718          	ld	_alarm_4,a
2782  083a               L516:
2783                     ; 638 	i2c_start();//отправка посылки СТАРТ
2785  083a cd0000        	call	_i2c_start
2787                     ; 639       I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
2789  083d a6d0          	ld	a,#208
2790  083f cd0000        	call	_I2C_SendByte
2792                     ; 640       I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
2794  0842 4f            	clr	a
2795  0843 cd0000        	call	_I2C_SendByte
2797                     ; 641       i2c_stop ();//отправка посылки СТОП 
2799  0846 cd0000        	call	_i2c_stop
2801                     ; 642       i2c_start ();//отправка посылки СТАРТ
2803  0849 cd0000        	call	_i2c_start
2805                     ; 643       I2C_SendByte (dev_addrr);//адрес часовой микросхемы - чтение
2807  084c a6d1          	ld	a,#209
2808  084e cd0000        	call	_I2C_SendByte
2810                     ; 644       sec = I2C_ReadByte();//чтение секунд
2812  0851 cd0000        	call	_I2C_ReadByte
2814  0854 01            	rrwa	x,a
2815  0855 b70b          	ld	_sec,a
2816  0857 02            	rlwa	x,a
2817                     ; 645       min = I2C_ReadByte();//чтение минут
2819  0858 cd0000        	call	_I2C_ReadByte
2821  085b 01            	rrwa	x,a
2822  085c b70a          	ld	_min,a
2823  085e 02            	rlwa	x,a
2824                     ; 646       hour = I2C_ReadByte();//чтение часов
2826  085f cd0000        	call	_I2C_ReadByte
2828  0862 01            	rrwa	x,a
2829  0863 b707          	ld	_hour,a
2830  0865 02            	rlwa	x,a
2831                     ; 647       Weekdays = I2C_ReadByte_last();//чтение дня недели
2833  0866 cd0000        	call	_I2C_ReadByte_last
2835  0869 01            	rrwa	x,a
2836  086a b700          	ld	_Weekdays,a
2837  086c 02            	rlwa	x,a
2838                     ; 648       i2c_stop (); 	
2840  086d cd0000        	call	_i2c_stop
2842                     ; 650       sece = RTC_ConvertFromDec(sec);
2844  0870 b60b          	ld	a,_sec
2845  0872 cd005a        	call	_RTC_ConvertFromDec
2847  0875 b70d          	ld	_sece,a
2848                     ; 651       secd = RTC_ConvertFromDecd(sec,0);
2850  0877 b60b          	ld	a,_sec
2851  0879 5f            	clrw	x
2852  087a 95            	ld	xh,a
2853  087b cd0023        	call	_RTC_ConvertFromDecd
2855  087e b70c          	ld	_secd,a
2856                     ; 652       mine = RTC_ConvertFromDec(min);
2858  0880 b60a          	ld	a,_min
2859  0882 cd005a        	call	_RTC_ConvertFromDec
2861  0885 b709          	ld	_mine,a
2862                     ; 653       mind = RTC_ConvertFromDecd(min,0);
2864  0887 b60a          	ld	a,_min
2865  0889 5f            	clrw	x
2866  088a 95            	ld	xh,a
2867  088b cd0023        	call	_RTC_ConvertFromDecd
2869  088e b708          	ld	_mind,a
2870                     ; 654       houre = RTC_ConvertFromDec(hour);
2872  0890 b607          	ld	a,_hour
2873  0892 cd005a        	call	_RTC_ConvertFromDec
2875  0895 b704          	ld	_houre,a
2876                     ; 655       hourd = RTC_ConvertFromDecd(hour,1);
2878  0897 b607          	ld	a,_hour
2879  0899 ae0001        	ldw	x,#1
2880  089c 95            	ld	xh,a
2881  089d cd0023        	call	_RTC_ConvertFromDecd
2883  08a0 b703          	ld	_hourd,a
2884                     ; 656       Weekdays = RTC_ConvertFromDec(Weekdays);
2886  08a2 b600          	ld	a,_Weekdays
2887  08a4 cd005a        	call	_RTC_ConvertFromDec
2889  08a7 b700          	ld	_Weekdays,a
2890                     ; 657       hourd_alar = RTC_ConvertFromDec(hour_alar);
2892  08a9 b606          	ld	a,_hour_alar
2893  08ab cd005a        	call	_RTC_ConvertFromDec
2895  08ae b710          	ld	_hourd_alar,a
2896                     ; 658       houre_alar = RTC_ConvertFromDecd(hour_alar,1);	
2898  08b0 b606          	ld	a,_hour_alar
2899  08b2 ae0001        	ldw	x,#1
2900  08b5 95            	ld	xh,a
2901  08b6 cd0023        	call	_RTC_ConvertFromDecd
2903  08b9 b70f          	ld	_houre_alar,a
2904                     ; 661 if (Weekdays > 0b00000110) Weekdays = 0;
2906  08bb b600          	ld	a,_Weekdays
2907  08bd a107          	cp	a,#7
2908  08bf 2502          	jrult	L126
2911  08c1 3f00          	clr	_Weekdays
2912  08c3               L126:
2913                     ; 662 if (hour == 0 && min == 0 && sec == 0b00000010) alarm_flag = 0;
2915  08c3 3d07          	tnz	_hour
2916  08c5 260c          	jrne	L326
2918  08c7 3d0a          	tnz	_min
2919  08c9 2608          	jrne	L326
2921  08cb b60b          	ld	a,_sec
2922  08cd a102          	cp	a,#2
2923  08cf 2602          	jrne	L326
2926  08d1 3f0e          	clr	_alarm_flag
2927  08d3               L326:
2928                     ; 663 hour_alar = (((alarm_1 << 4) & 0b00110000)) | (alarm_2 & 0b00001111);// & alarm_2;
2930  08d3 b61a          	ld	a,_alarm_2
2931  08d5 a40f          	and	a,#15
2932  08d7 6b01          	ld	(OFST+0,sp),a
2934  08d9 b61b          	ld	a,_alarm_1
2935  08db 97            	ld	xl,a
2936  08dc a610          	ld	a,#16
2937  08de 42            	mul	x,a
2938  08df 9f            	ld	a,xl
2939  08e0 a430          	and	a,#48
2940  08e2 1a01          	or	a,(OFST+0,sp)
2941  08e4 b706          	ld	_hour_alar,a
2942                     ; 664 min_alar = (((alarm_3 << 4) & 0b00110000)) | (alarm_4 & 0b00001111);// & alarm_2;
2944  08e6 b618          	ld	a,_alarm_4
2945  08e8 a40f          	and	a,#15
2946  08ea 6b01          	ld	(OFST+0,sp),a
2948  08ec b619          	ld	a,_alarm_3
2949  08ee 97            	ld	xl,a
2950  08ef a610          	ld	a,#16
2951  08f1 42            	mul	x,a
2952  08f2 9f            	ld	a,xl
2953  08f3 a430          	and	a,#48
2954  08f5 1a01          	or	a,(OFST+0,sp)
2955  08f7 b705          	ld	_min_alar,a
2956                     ; 667 clk_out ();
2958  08f9 cd04fe        	call	_clk_out
2960                     ; 668 if (hour_alar == hour && alarm_flag == 0){
2962  08fc b606          	ld	a,_hour_alar
2963  08fe b107          	cp	a,_hour
2964  0900 260e          	jrne	L526
2966  0902 3d0e          	tnz	_alarm_flag
2967  0904 260a          	jrne	L526
2968                     ; 669     if (min_alar == min) GPIOA->ODR |=  (1<<3);
2970  0906 b605          	ld	a,_min_alar
2971  0908 b10a          	cp	a,_min
2972  090a 2604          	jrne	L526
2975  090c 72165000      	bset	20480,#3
2976  0910               L526:
2977                     ; 672 if ((GPIOC->IDR & (1 << 3)) == 0){//отключение будильника
2979  0910 c6500b        	ld	a,20491
2980  0913 a508          	bcp	a,#8
2981  0915 2703          	jreq	L27
2982  0917 cc083a        	jp	L516
2983  091a               L27:
2984                     ; 673     GPIOA->ODR &=  ~(1<<3);
2986  091a 72175000      	bres	20480,#3
2987                     ; 674     alarm_flag = 1;
2989  091e 3501000e      	mov	_alarm_flag,#1
2990  0922 ac3a083a      	jpf	L516
3417                     	xdef	_main
3418                     	xdef	_sets_CGRAM
3419                     	xdef	_clk_out
3420                     	xdef	_lcd_mask
3421                     	xdef	_Day_Switch
3422                     	xdef	_button
3423                     	xdef	_sending_data
3424                     	xdef	_vyb_raz_h
3425                     	xdef	_vyb_raz
3426                     	xdef	_DS1307init
3427                     	xdef	_digit_out
3428                     	xdef	_str08
3429                     	xdef	_str07
3430                     	xdef	_str06
3431                     	xdef	_str05
3432                     	xdef	_str04
3433                     	xdef	_str03
3434                     	xdef	_str02
3435                     	xdef	_str01
3436                     	xdef	_RTC_ConvertFromDec
3437                     	xdef	_RTC_ConvertFromDecd
3438                     	xdef	_segment_clear
3439                     	switch	.ubsct
3440  0000               _Weekdays:
3441  0000 00            	ds.b	1
3442                     	xdef	_Weekdays
3443  0001               _houree:
3444  0001 00            	ds.b	1
3445                     	xdef	_houree
3446  0002               _minee:
3447  0002 00            	ds.b	1
3448                     	xdef	_minee
3449                     	xdef	_hourd_alar
3450                     	xdef	_houre_alar
3451  0003               _hourd:
3452  0003 00            	ds.b	1
3453                     	xdef	_hourd
3454  0004               _houre:
3455  0004 00            	ds.b	1
3456                     	xdef	_houre
3457  0005               _min_alar:
3458  0005 00            	ds.b	1
3459                     	xdef	_min_alar
3460  0006               _hour_alar:
3461  0006 00            	ds.b	1
3462                     	xdef	_hour_alar
3463  0007               _hour:
3464  0007 00            	ds.b	1
3465                     	xdef	_hour
3466  0008               _mind:
3467  0008 00            	ds.b	1
3468                     	xdef	_mind
3469  0009               _mine:
3470  0009 00            	ds.b	1
3471                     	xdef	_mine
3472  000a               _min:
3473  000a 00            	ds.b	1
3474                     	xdef	_min
3475  000b               _sec:
3476  000b 00            	ds.b	1
3477                     	xdef	_sec
3478  000c               _secd:
3479  000c 00            	ds.b	1
3480                     	xdef	_secd
3481  000d               _sece:
3482  000d 00            	ds.b	1
3483                     	xdef	_sece
3484                     	xdef	_DAY_2
3485                     	xdef	_DAY_1
3486                     	xdef	_alarm_number
3487  000e               _alarm_flag:
3488  000e 00            	ds.b	1
3489                     	xdef	_alarm_flag
3490  000f               _n:
3491  000f 00            	ds.b	1
3492                     	xdef	_n
3493                     	xdef	_t
3494  0010               _p_alarm_4:
3495  0010 0000          	ds.b	2
3496                     	xdef	_p_alarm_4
3497  0012               _p_alarm_3:
3498  0012 0000          	ds.b	2
3499                     	xdef	_p_alarm_3
3500  0014               _p_alarm_2:
3501  0014 0000          	ds.b	2
3502                     	xdef	_p_alarm_2
3503  0016               _p_alarm_1:
3504  0016 0000          	ds.b	2
3505                     	xdef	_p_alarm_1
3506  0018               _alarm_4:
3507  0018 00            	ds.b	1
3508                     	xdef	_alarm_4
3509  0019               _alarm_3:
3510  0019 00            	ds.b	1
3511                     	xdef	_alarm_3
3512  001a               _alarm_2:
3513  001a 00            	ds.b	1
3514                     	xdef	_alarm_2
3515  001b               _alarm_1:
3516  001b 00            	ds.b	1
3517                     	xdef	_alarm_1
3518                     	xdef	_address_4
3519                     	xdef	_address_3
3520                     	xdef	_address_2
3521                     	xdef	_address_1
3522                     	xdef	_tio
3523                     	xdef	_ms
3524                     	xref	_sendbyte
3525                     	xref	_LCD_SetPos
3526                     	xref	_LCD_Init
3527                     	xdef	_delay_ms
3528                     	xref	_I2C_ReadByte_last
3529                     	xref	_I2C_ReadByte
3530                     	xref	_I2C_SendByte
3531                     	xref	_i2c_stop
3532                     	xref	_i2c_start
3552                     	xref	c_lcmp
3553                     	xref	c_uitolx
3554                     	end
