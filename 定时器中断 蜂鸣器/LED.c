#include <reg52.h>
typedef unsigned int u16;

sbit beep=P1^5;

void IntT0()
{
	EA=1;       //���ж�������λ
	ET0=1;      //�򿪶�ʱ�������ж�����λ
	TMOD|=0x01;  //���ù�����ʽ(GATE,C/T,M1M0)
	TR0=1;      //��1������T0����
	TH0=0xfc;   //���ó�ֵ
	TL0=0x18;
}
u16 i=0;
void main()
{
	IntT0(); 
	while(1)
	{
			 if(i==250)
		 {
				i=0;
				beep=~beep;
		 }
	 }
}
void t0() interrupt 1
{
	TH0=0xfc;   // �ص���ֵ�����¼�ʱ
	TL0=0x18;
	i++;
}
