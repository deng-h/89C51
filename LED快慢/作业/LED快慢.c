#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit k3=P3^2;  //�ⲿ�ж�0,���ٰ���
sbit k4=P3^3;   //�ⲿ�ж�1�����ٰ���

u8 high=0xfc,low=0x18;  //��׼ 1����һ��
u16 i=0,j=0;

u8 code list[]={0xff,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};

void delay(u16 i)
{
	while(i--);
}

void IntEx0()     //�ⲿ�ж�0
{
	EA=1;
	EX0=1;
	IT0=1;
}

void IntEx1()     //�ⲿ�ж�1
{
	EA=1;
	EX1=1;
	IT1=1;
}

void IntT0()    //��ʱ���ж�0
{
	EA=1;
	ET0=1;      
	TMOD=0x01;    //0000 0001
	TR0=1;      
	TH0=high;   
	TL0=low;
}
void main()
{
	IntEx0();
	IntEx1();
	IntT0();
	while(1)
	{
		if(i==1000)
		{
			i=0;
			P2=list[j++];
		}	
		if(j==9) j=0;
	}
}

void Ex0() interrupt 0   //���٣�1/10��
{
	delay(100);
	if(k3==0)
	{
	  high=0xff;
	  low=0x9c;
	}
}
void Ex1() interrupt 2  //���٣�2��
{
	delay(100);
	if(k4==0)
	{
	  high=0xf8;
	  low=0x30;
	}
}

void t0() interrupt 1
{
	TH0=high;   
	TL0=low;
	i++;
}
