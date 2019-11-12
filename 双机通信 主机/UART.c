
//UART驱动代码.c文件

#include <reg52.h>
#include "UART.h"
#include "display.h"

sbit k3=P3^2;

void delay(int i)
{
	while(i--);
}

void Uart_init()
{
	TMOD=0x20;//定时器1,八位自动重装方式
	TH1=0xF3;  //晶振12MHZ，波特率倍增，波特率4800
	TL1=0xF3;
	PCON=0x80;//SMOD波特率倍增位，只用其中的最高位
	TR1=1;  //定时器1运行
	SCON=0x50; // 0101 0000
	EX0=1;  //打开外部中断0
	IT0=1;  //下降沿触发
	ES=1;
	EA=1;
}

void Ex0_send() interrupt 0  //按键时发送信息
{
	delay(100);
	if(k3==0)
	{
		ES=0;
		SBUF=1;
		while(!TI);
		TI=0;
		ES=1;
	}
}

void Uart_receive() interrupt 4  //用于接收信息
{
	RI=0;
	display();
}