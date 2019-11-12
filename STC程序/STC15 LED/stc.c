#include <STC15F2K60S2.h>
typedef unsigned int uint;
typedef unsigned char uchar;
sbit LED0 = P5^5;

uint count=0;
void Timer0Init(void)		//1����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xCD;		//���ö�ʱ��ֵ
	TH0 = 0xD4;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	ET0 = 1;    //�򿪶�ʱ������T0��ע����򿪶�ʱ��0(TR0)������
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void main()
{
	P30=0;
	P33=0;
	P36=0;
	P37=0;
	P20=0;
	P23=0;
	P25=0;
	P26=0;
	Timer0Init();
	EA = 1;         //�����ж�
	while(1)
	{
		if(count>=1000)
		{
			count=0;
			LED0=~LED0;
		}
	}
}
void Timer0_Routine(void) interrupt 1
{
	count++;
}