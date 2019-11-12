#ifndef __UART_H__  //如果没有定义__UART_H__
#define __UART_H__  //那么定义__UART_H__

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

#endif  //结束if语句