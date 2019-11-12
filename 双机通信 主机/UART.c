
//UART��������.c�ļ�

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
	TMOD=0x20;//��ʱ��1,��λ�Զ���װ��ʽ
	TH1=0xF3;  //����12MHZ�������ʱ�����������4800
	TL1=0xF3;
	PCON=0x80;//SMOD�����ʱ���λ��ֻ�����е����λ
	TR1=1;  //��ʱ��1����
	SCON=0x50; // 0101 0000
	EX0=1;  //���ⲿ�ж�0
	IT0=1;  //�½��ش���
	ES=1;
	EA=1;
}

void Ex0_send() interrupt 0  //����ʱ������Ϣ
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

void Uart_receive() interrupt 4  //���ڽ�����Ϣ
{
	RI=0;
	display();
}