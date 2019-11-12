#include <reg52.h>
#include <stdio.h>
typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u16 a;
u8 list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	      0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};



void Display(u8 i)
{
	LSA=0;LSB=0;LSC=0;  //第一个数码管显示
	switch(i)   //用switch是因为传入的是字符串类型
	{
		case '0':P0=list[0];break;
		case '1':P0=list[1];break;
		case '2':P0=list[2];break;
		case '3':P0=list[3];break;
		case '4':P0=list[4];break;
		case '5':P0=list[5];break;
		case '6':P0=list[6];break;
		case '7':P0=list[7];break;
		case '8':P0=list[8];break;
		case '9':P0=list[9];break;
		case 'a':P0=list[10];break;
		case 'b':P0=list[11];break;
		case 'c':P0=list[12];break;
		case 'd':P0=list[13];break;
		case 'e':P0=list[14];break;
		case 'f':P0=list[15];break;
		default :P0=0x80;
		
	}
}

void main()
{
	Uart_init();
	LSA=0;LSB=0;LSC=0;
	P0=list[0];
	while(1);
}

void Uart() interrupt 4
{
	RI=0;  //取消中断申请
	a=SBUF;
	Display(a);
}
	