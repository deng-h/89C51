
//UART驱动代码.c文件

#include <reg52.h>
#include "UART.h"
#include "digital.h"

void Uart_init()
{
	TMOD=0x20;//定时器1,八位自动重装方式
	TH1=0xF3;  //晶振12MHZ，波特率倍增，波特率4800
	TL1=0xF3;
	PCON=0x80;//SMOD波特率倍增位，只用其中的最高位
	TR1=1;  //定时器1运行
	SCON=0x50; // 0101 0000
	ES=1;
	EA=1;
}

void Uart_Send_Receive() interrupt 4  //用于接收并发送信息
{
	RI=0;
	display();
	ES=0;       //关掉通信中断，否则发送完信息又会进入中断
	SBUF=1;
	while(!TI);
	TI=0;
	ES=1;
}