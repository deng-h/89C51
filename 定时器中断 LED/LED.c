#include <reg52.h>
typedef unsigned int u16;

sbit led=P2^0;

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
			 if(i==1000)
		 {
				i=0;
				led=~led;
		 }
	 }
}
void t0() interrupt 1
{
	TH0=0xfc;   // �ص���ֵ�����¼�ʱ
	TL0=0x18;
	i++;
}
