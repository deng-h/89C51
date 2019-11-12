/*********************
波特率4800，51单片机
*********************/
#include "reg52.h"
#include <UART.h>
#define MAX 32
typedef unsigned int u16;
typedef unsigned char u8;

void main()
{
	u8 i,temp;   
	u8 ReadBuf[MAX];
	u8 Read_Length;
	EA=0;
	UART_Init();
	EA=1;
	while(1)
	{
		Read_Length=UART_Read(ReadBuf);   //把接收到的数据放到ReadBuf数组里并把数据个数给Read_Length
		for(i=0;i<Read_Length/2;i++)     //数组元素反转
		{ 
			temp=ReadBuf[i];
			ReadBuf[i]=ReadBuf[Read_Length-i-1];
			ReadBuf[Read_Length-i-1]=temp;
		}
		UART_Write(ReadBuf,Read_Length);
	}
}