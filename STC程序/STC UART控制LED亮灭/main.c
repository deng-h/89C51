/*
效果：通过串口助手发送一位数据，LED实现亮灭
*/
#include <STC15F2K60S2.h>
typedef unsigned int uint;
typedef unsigned char uchar;
sbit LED = P5^5;
uint count=0;
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0xE0;		//设定定时初值
	TH1 = 0xFE;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void main()
{
	UartInit();
	EA = 1;
	ES = 1;
	while(1);
}

void UART_Routine() interrupt 4
{
	if(RI)
	{
		RI = 0;
		count++;
		if(count%2==0) LED=1;
		else LED=0;
	}
}