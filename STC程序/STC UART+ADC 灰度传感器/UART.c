#include "STC15F2K60S2.h"

/****************************************************
               串口收发程序
******************************************************/

void UART_Write(unsigned char *Buf,unsigned char Num)  //发送数据，数组首地址，数组数 
{
    unsigned char i;
    for(i=0;i<Num;i++)
    {
       SBUF = Buf[i];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
       while(!TI);				//等特数据传送	(TI发送中断标志)
       TI=0;		
    }
}

void UART_Write_byte(unsigned char dat)
{
	SBUF=dat;
	while(!TI);
	TI=0;
}

/***********************************************************
										串口初始化程序
************************************************************/

void UART_Init(void)		//9600bps@11.0592MHz
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

