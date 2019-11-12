#ifndef __OLED_H
#define __OLED_H

#include <STC15F2K60S2.h>
//#include "intrins.h"

#define uint8 unsigned char
#define uint16 unsigned int
#define int16 int
#define int8  short int

/***************** 引脚选择 *****************/
sbit OLED_SCL_Pin =  P2^7;   //时钟

sbit OLED_SDA_Pin = P2^6;    //发数据

sbit OLED_RES_Pin =  P2^5;    //复位

sbit OLED_DC_Pin  =  P2^4;    //命令


//#define USE_CS
#ifdef USE_CS
#define OLED_CS_Pin
#endif /* USE_CS */

#define OLED_SCLH 	OLED_SCL_Pin=1
#define OLED_SCLL 	OLED_SCL_Pin=0

#define OLED_SDAH 	OLED_SDA_Pin=1
#define OLED_SDAL 	OLED_SDA_Pin=0

#define OLED_RSTH 	OLED_RES_Pin=1
#define OLED_RSTL 	OLED_RES_Pin=0

#define OLED_DCH  	OLED_DC_Pin=1
#define OLED_DCL  	OLED_DC_Pin=0

#ifdef USE_CS
#define OLED_CSH		OLED_CS_Pin=1
#define OLED_CSL		OLED_CS_Pin=0
#endif /* USE_CS */

#define OLED_X_MAX 				128  
#define OLED_Y_MAX 				64
#define OLED_PAGE_MAX  		(OLED_Y_MAX/8)
#define WHITE 						(uint8)0XFF
#define BLACK							(uint8)0X00

void OLED_Init(void);
void OLED_Switch(char NewState);
void OLED_ClearScreen(uint8 color);
void OLED_P6x8Char(uint8 x, uint8 y, char ch);
void OLED_P6x8Str(uint8 x, uint8 y, const char *ch);
void OLED_P6x8Int(uint8 x, uint8 y, int16 data1, int8 set);
void OLED_P6x8Flo(uint8 x, uint8 y, float data1, int8 set);
void OLED_P8x16Char(uint8 x, uint8 y, char ch);
void OLED_P8x16Str(uint8 x, uint8 y, const char *ch);
void OLED_P14x16CHCHAR(uint8 x, uint8 y, const char *ch);
void OLED_PrintBMP(uint8 x0,uint8 y0,uint8 x1,uint8 y1, const char bmp[]);

#endif