#include <STC15F2K60S2.h>
#define uchar unsigned char
#define uint unsigned int
void delay_ms(uint t)
{
	while(t--)
	{
		uchar i=11,j=190;
		do
		{
			while(--j);
		}while(--i);
	}
}

//sbit blue=P20;
//sbit pink=P21;
//sbit yellow=P22;
//sbit orange=P23;
//sbit power=P40;
 uchar code CCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //逆时钟旋转相序表
 uchar code CW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //正时钟旋转相序表
void main()
{
	uint i;
	P40=1;
	P41=0;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			P2=CCW[i];
			delay_ms(100);
		}
		delay_ms(1000);
		for(i=0;i<8;i++)
		{
			P2=CW[i];
			delay_ms(100);
		}
	}
}