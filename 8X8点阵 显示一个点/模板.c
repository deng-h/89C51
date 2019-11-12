#include <reg52.h>
#include <intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit RCLK_=P3^5;
sbit SRCLK=P3^6;
sbit SER=P3^4;

void hc595byte(u8 dat)
{
	u16 i;
	RCLK_=0;
	SRCLK=0;
	for(i=0;i<8;i++)   //一位位将data送入移位寄存器，先高位，后低位
	{
		SER=dat>>7;   //取最高位
		dat=dat<<1;   //移去最高位，最低位补0
		SRCLK=1;   //移位寄存器，产生一个上升沿，将SER的数据移入移位寄存器
		_nop_();   //延时
		_nop_();
		SRCLK=0;   //归零，以便再次产生上升沿
	}
	RCLK_=1;   //存储寄存器产生上升沿，将SER已移入的数据送给输出端
}
void main()
{
	hc595byte(0xff);
	P0=0x3f;
	while(1);
}