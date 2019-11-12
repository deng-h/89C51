#include <STC15F2K60S2.h>
typedef unsigned int uint;
typedef unsigned char uchar;
sbit LED0 = P5^5;

uint count=0;
void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	ET0 = 1;    //打开定时计数器T0，注意与打开定时器0(TR0)的区别
	TR0 = 1;		//定时器0开始计时
}

void main()
{
	P30=0;
	P33=0;
	P36=0;
	P37=0;
	P20=0;
	P23=0;
	P25=0;
	P26=0;
	Timer0Init();
	EA = 1;         //打开总中断
	while(1)
	{
		if(count>=1000)
		{
			count=0;
			LED0=~LED0;
		}
	}
}
void Timer0_Routine(void) interrupt 1
{
	count++;
}