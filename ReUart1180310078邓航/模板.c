/*********************
������4800��51��Ƭ��
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
		Read_Length=UART_Read(ReadBuf);   //�ѽ��յ������ݷŵ�ReadBuf�����ﲢ�����ݸ�����Read_Length
		for(i=0;i<Read_Length/2;i++)     //����Ԫ�ط�ת
		{ 
			temp=ReadBuf[i];
			ReadBuf[i]=ReadBuf[Read_Length-i-1];
			ReadBuf[Read_Length-i-1]=temp;
		}
		UART_Write(ReadBuf,Read_Length);
	}
}