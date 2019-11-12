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
	for(i=0;i<8;i++)   //һλλ��data������λ�Ĵ������ȸ�λ�����λ
	{
		SER=dat>>7;   //ȡ���λ
		dat=dat<<1;   //��ȥ���λ�����λ��0
		SRCLK=1;   //��λ�Ĵ���������һ�������أ���SER������������λ�Ĵ���
		_nop_();   //��ʱ
		_nop_();
		SRCLK=0;   //���㣬�Ա��ٴβ���������
	}
	RCLK_=1;   //�洢�Ĵ������������أ���SER������������͸������
}
void main()
{
	hc595byte(0xff);
	P0=0x3f;
	while(1);
}