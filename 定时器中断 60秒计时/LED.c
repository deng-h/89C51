#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void IntT0()
{
	EA=1;       //打开中断总允许位
	ET0=1;      //打开定时计数器中断允许位
	TMOD|=0x01;  //设置工作方式(GATE,C/T,M1M0)
	TR0=1;      //置1，允许T0运行
	TH0=0xfc;   //设置初值
	TL0=0x18;
}

/*void IntT1()
{
	EA=1;
	ET1=1;
	PT1=1;
	TMOD=0x10;
	TR1=1;
	TH1=0xd8;
	TL1=0xf0;
}*/

void delay(u16 i)
{
	while(i--);
}
u16 i=0,j=0;

void display(u16 a, u16 b)
{
	while(1)
	{
		LSA=0;LSB=0;LSC=0;
		P0=list[a];
		delay(200);
		P0=0x00; 
		LSA=1;LSB=0;LSC=0;
		P0=list[b];
	  delay(200);
	  P0=0x00;
		if(i!=1000) break;
	}
}
void main()
{	
	u16 a=0,b=0;
  IntT0();
	//IntT1();
	while(1)
	{
		if(i==1000)
		{
			if(a==10) a=0;
			a++;
			b++;
			i=0;
			display(a,b/10);
		}	
	}
}

void t0() interrupt 1
{
	TH0=0xfc;   
	TL0=0x18;
	i++;
}
/*void t1() interrupt 3
{
	TH1=0xd8;
	TL1=0xf0;
  j++;
}*/
