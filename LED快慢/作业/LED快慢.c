#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit k3=P3^2;  //外部中断0,快速按键
sbit k4=P3^3;   //外部中断1，慢速按键

u8 high=0xfc,low=0x18;  //基准 1秒亮一次
u16 i=0,j=0;

u8 code list[]={0xff,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};

void delay(u16 i)
{
	while(i--);
}

void IntEx0()     //外部中断0
{
	EA=1;
	EX0=1;
	IT0=1;
}

void IntEx1()     //外部中断1
{
	EA=1;
	EX1=1;
	IT1=1;
}

void IntT0()    //定时器中断0
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

void Ex0() interrupt 0   //快速，1/10秒
{
	delay(100);
	if(k3==0)
	{
	  high=0xff;
	  low=0x9c;
	}
}
void Ex1() interrupt 2  //慢速，2秒
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
