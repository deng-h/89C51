#include "STC15Fxxxx.h"
#include "stdint.h"
#include "LedShift.h"
#include "tick.h"
#include "UART.h"

#define MAX 32

void main()
{
	uint8_t i,temp;   
	uint8_t ReadBuf[MAX];
	uint8_t Read_Length;
	EA=0;
	Tick_Init();
	UART_Init();
	EA=1;
	while(1)
	{
		if(Read_Length=UART_Read(ReadBuf))   //把接收到的数据放到ReadBuf数组里并把数据个数给Read_Length
		{
			for(i=0;i<Read_Length;i++)     //数组元素反转
			{ 
				temp=ReadBuf[i];
				ReadBuf[i]=ReadBuf[Read_Length-i-1];
				ReadBuf[Read_Length-i-1]=temp;
			}
			UART_Write(ReadBuf,Read_Length);
		}
	}
}

