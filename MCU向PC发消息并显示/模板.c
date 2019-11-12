#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

int sum=48;
u8 list[]="times";

void Uart_init()
{
	TMOD=0x20;//定时器1,八位自动重装方式
	TH1=0xF3;  //晶振12MHZ，波特率倍增，波特率4800
	TL1=0xF3;
	PCON=0x80;//SMOD波特率倍增位，只用其中的最高位
	TR1=1;  //定时器1运行
	SCON=0x50; // 0101 0000
	EX0=1;  //打开外部中断0
	IT0=1;  //下降沿触发
	ES=1;
	EA=1;
}


void main()
{
	Uart_init();
	while(1);
}
void Ex0() interrupt 0
{
	int i;
	sum++;
	for(i=0;i<5;i++)
	{
		SBUF=list[i];
		while(!TI);
		TI=0;
	}
	SBUF=sum;// 发送的是ASCII,不是的为什么。。。
	while(!TI);
	TI=0;
}


	