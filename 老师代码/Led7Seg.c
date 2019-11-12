#include "STC15Fxxxx.h"
#include "stdint.h"

#define DISPLAY_SEG P2
#define DISPLAY_BIT P4


unsigned char code DecToSeg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
                               0x88,0x83,0xc6,0xa1,0x86,0x8e,0xa3,0xab,0xff};
                          //   '0'  '1'  '2'  '3'  '4'  '5'  '6'  '7'  '8'  '9'  
                          //   'a'  'b'  'c'  'd'  'e'  'f'  'o'  'n'  ' '
//uint8_t code BitCode[4]={0x7F,0xBF,0xDF,0xEF};
uint8_t code BitCode[4]={0xF7,0xFB,0xFD,0xFE};

uint8_t DisplayBuf[4];
uint8_t Cnt=0;
void Led7Seg_Flush(void)
{
	Cnt=(Cnt+1)&0x03;
	DISPLAY_SEG=DisplayBuf[Cnt];
	DISPLAY_BIT=BitCode[Cnt];
}	

void Led7Seg_WriteNum(uint8_t * NumBuf)
{
	DisplayBuf[0]=DecToSeg[NumBuf[0]];
	DisplayBuf[1]=DecToSeg[NumBuf[1]];
	DisplayBuf[2]=DecToSeg[NumBuf[2]];
	DisplayBuf[3]=DecToSeg[NumBuf[3]];
}

void Led7Seg_WriteCode(uint8_t * CodeBuf)
{
	DisplayBuf[0]=CodeBuf[0];
	DisplayBuf[1]=CodeBuf[1];
	DisplayBuf[2]=CodeBuf[2];
	DisplayBuf[3]=CodeBuf[3];
}
