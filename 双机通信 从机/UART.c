
//UART��������.c�ļ�

#include <reg52.h>
#include "UART.h"
#include "digital.h"

void Uart_init()
{
	TMOD=0x20;//��ʱ��1,��λ�Զ���װ��ʽ
	TH1=0xF3;  //����12MHZ�������ʱ�����������4800
	TL1=0xF3;
	PCON=0x80;//SMOD�����ʱ���λ��ֻ�����е����λ
	TR1=1;  //��ʱ��1����
	SCON=0x50; // 0101 0000
	ES=1;
	EA=1;
}

void Uart_Send_Receive() interrupt 4  //���ڽ��ղ�������Ϣ
{
	RI=0;
	display();
	ES=0;       //�ص�ͨ���жϣ�����������Ϣ�ֻ�����ж�
	SBUF=1;
	while(!TI);
	TI=0;
	ES=1;
}