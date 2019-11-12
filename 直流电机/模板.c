#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit key1=P3^2;
sbit key2=P3^3;
sbit PWM=P1^0;
u8 code list[]={0x01,0x02,0x04,0x08,0x08,0x04,0x02,0x01};
int on_off = 0; //作为电机的开关
void delay(u16 i)
{
	while(i--);
}
void main()
{
	while(1)
	{
		PWM=1;
		delay(50000);
		PWM=0;
		delay(50000);
	}
}

void EX0_key1() interrupt 0  //电机启动
{
	on_off = 1;
}

void EX1_key2() interrupt 2  //电机关闭
{
	on_off = 0;
}