#include "reg52.h"
#include <UART.h>
#define T5MS (65536-11059200L*5/1000/12)     //12T模式，5ms定时
#define	T2_BR_Reload	(65536UL -(11059200L /4/115200UL)) //Timer2 重装值，
#define BUFFER_LENGTH 32
unsigned char ReData[BUFFER_LENGTH];
unsigned char ReceiveNum;
unsigned char Num=0;
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

/****************************************************
               串口初始化程序
******************************************************/

void UART_Init(void) 
{
	  TMOD = 0x21;  //定时计数器1，2同时启用
		TH1=0xF3;  //晶振12MHZ，波特率倍增，波特率4800
		TL1=0xF3;
		ET1=1;
		PCON=0x80;//SMOD波特率倍增位，只用其中的最高位
		TR1=1;  //定时器1运行
		SCON=0x50; // 0101 0000
	  TH0 = T5MS>>8;
    TL0 = T5MS;
	  ET0=1;	
    TR0=0;    //关闭T0定时器，等待开启
    RI=0;
    TI=0;
    REN = 1;	//允许接收
    ES  = 1;	//允许中断
		ReceiveNum=0;
}

/****************************************************
               串口中断程序
******************************************************/
void ser_int (void) interrupt 4   //串行中断，接收
{
    if(RI == 1)        //RI接受中断标志
    {
			RI = 0;		    //清除RI接受中断标志
			ReData[Num]=SBUF;  //SUBF接受/发送缓冲器 	
			Num++;
			TH0 = T5MS >> 8;   //定时器回到初值重新计时
			TL0 = T5MS;
			TR0=1;
    }
}

void timer0() interrupt 1   
{		
  TR0=0;          //达到规定时间，进入中断，关闭定时器中断
	ReceiveNum=Num;   //记下收到的个数
  Num=0;
}

unsigned char UART_Read(unsigned char *Buf)   //给出最终存放的数组首地址，把缓存数组的数据放入其内
{
	unsigned char i;
	for(i=0; i<ReceiveNum;i++)
	{
		Buf[i]=ReData[i];
	}
	i=ReceiveNum;
	ReceiveNum=0;
	return i;    //返回数据元素个数
}
