#include <reg52.h>
typedef unsigned int u16;

sbit beep=P1^5;

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
	TH0=0xfc;   // 回到初值，重新计时
	TL0=0x18;
	i++;
}
