/*
Ч����ͨ���������ַ���һλ���ݣ�LEDʵ������
*/
#include <STC15F2K60S2.h>
typedef unsigned int uint;
typedef unsigned char uchar;
sbit LED = P5^5;
uint count=0;
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xE0;		//�趨��ʱ��ֵ
	TH1 = 0xFE;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}

void main()
{
	UartInit();
	EA = 1;
	ES = 1;
	while(1);
}

void UART_Routine() interrupt 4
{
	if(RI)
	{
		RI = 0;
		count++;
		if(count%2==0) LED=1;
		else LED=0;
	}
}