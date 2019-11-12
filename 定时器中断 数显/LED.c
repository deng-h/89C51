#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
                           0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void IntT0()
{
	EA=1;       //打开中断总允许位
	ET0=1;      //打开定时计数器中断允许位
	TMOD|=0x01;  //设置工作方式(GATE,C/T,M1M0)
	TR0=1;      //置1，允许T0运行
	TH0=0xfc;   //设置初值
	TL0=0x18;
}

u16 i=0;
void main()
{	 
	 u16 j=0;
	 LSA=0;    //位选，让LED1端为0
	 LSB=0;
	 LSC=0;
	 IntT0(); 
	while(1)
	{
		 if(j==16) j=0;
			 if(i==1000)
		 {
			  P0=list[j++];
				i=0;
		 }
	 }
}
void t0() interrupt 1
{
	TH0=0xfc;   // 回到初值，重新计时
	TL0=0x18;
	i++;
}
