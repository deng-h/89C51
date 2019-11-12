/*
时间:2019.4.21 星期天 
作用:计时.开发板上的独立按键K3用于计时重置，K4键用于计时暂停或开始
*/
#include <reg52.h>
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit reset=P3^2;  //用于定时器重置
sbit on_off=P3^3;   //用于计时器停止和开启
int hour=0,min=0,sec=0,i=0;
char code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};

void delay(int i)
{
	while(i--);
}

void Init_T0()
{
	EA=1;
	ET0=1;      //打开定时计数器中断允许位
	TMOD|=0x01;  //设置工作方式(GATE,C/T,M1M0)
	TR0=1;      //置1，允许T0运行
	TH0=0xfc;   //设置初值
	TL0=0x18;
}

void Init_Ex()
{
	EX0=1;
	IT0=1; //下降沿触发
	EX1=1;
	IT1=1;
}
void display_part(int x,int pos)   //用以显示数字,x为要显示的数字，pos为显示的位置
{
	switch(pos)
	{
		case(0):LSA=0;LSB=0;LSC=0;break;
		case(1):LSA=1;LSB=0;LSC=0;break;
		case(2):LSA=0;LSB=1;LSC=0;break;
		case(3):LSA=1;LSB=1;LSC=0;break;
		case(4):LSA=0;LSB=0;LSC=1;break;
		case(5):LSA=1;LSB=0;LSC=1;break;
		case(6):LSA=0;LSB=1;LSC=1;break;
		case(7):LSA=1;LSB=1;LSC=1;break;
	}
	P0=list[x];
	delay(100);
	P0=0x00;
}

void display_all(int hour,int min, int sec)
{
	int a,b;  //取出个位十位
	a=sec%10;
	b=sec/10;
	display_part(a,0);  //秒
	display_part(b,1);
	display_part(10,2);
	a=min%10;
	b=min/10;
	display_part(a,3);  //分
	display_part(b,4);
	display_part(10,5);
	a=hour%10;
	b=hour/10;
	display_part(a,6);  //时
	display_part(b,7);
}

void main()
{
	Init_T0();
	Init_Ex();
	while(1)
	{
		if(i>=1000)  //之所以不写(i==1000)时因为i的变化很快，当i==1000(这个时刻)时去判断需要时间，i此时已经不是1000了
		{
			sec++;
			i=0;
		}
		if(sec>=60)  //同上
		{
			min++;
			sec=0;
		}
		if(min>=60)  //同上
		{
			hour++;
			min=0;
		}
		display_all(hour,min,sec);	 //小时，分钟，秒
	}
}

void t0() interrupt 1
{
	TH0=0xfc;   // 回到初值，重新计时
	TL0=0x18;
	i++;
}

void Ex0() interrupt 0   //用于定时器重置
{
	delay(100);
	if(reset==0) 
	{
		hour=0;min=0;sec=0;
	}
}
void Ex1() interrupt 2   //用于计时器停止和开启
{
	delay(100);
	if(on_off==0)
	{
		ET0=~ET0;   //定时计数器中断允许位反转
	}
}