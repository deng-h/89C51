#ifndef __UART_H__  //���û�ж���__UART_H__
#define __UART_H__  //��ô����__UART_H__

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

#endif  //����if���