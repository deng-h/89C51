#include <reg52.h>
#include <intrins.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit RCLK_=P3^5;
sbit SRCLK=P3^6;
sbit SER=P3^4;
void delay(u16 i)
{
	while(i--);
}
void hc595byte(u8 dat)
{
	u16 i;
	RCLK_=0;
	SRCLK=0;
	for(i=0;i<8;i++)   //һλλ��dat������λ�Ĵ������ȸ�λ�����λ
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
u8 P0duan[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
u8 zero595[]={0x00,0x3c,0x42,0x81,0x81,0x42,0x3c,0x00};
u8 one595[]={0x00,0x02,0x02,0x42,0xfe,0x02,0x02,0x00};
u8 two595[]={0x00,0x22,0x46,0x8a,0x52,0x22,0x02,0x00};
u8 three595[]={0x00,0x00,0x42,0x81,0x89,0x89,0x77,0x00};
u8 four595[]={0x00,0x18,0x28,0x48,0xff,0x08,0x08,0x00};
u8 five595[]={0x00,0x71,0x89,0x89,0x89,0x8e,0x00,0x00};
u8 six595[]={0x00,0x3e,0x51,0x91,0x91,0x0e,0x00,0x00};
u8 seven595[]={0x00,0x80,0x80,0x9f,0xa0,0xc0,0x80,0x00};
u8 eight595[]={0x00,0x76,0x89,0x89,0x89,0x76,0x00,0x00};
u8 nine595[]={0x00,0x72,0x89,0x89,0x89,0x7f,0x00,0x00};
void display(u8 a[])
{
	u16 i,j;
	for(j=0;j<100;j++)
	{
		for(i=0;i<8;i++)
		{
       P0=P0duan[i];
			 hc595byte(a[i]);
			 delay(100);
			 hc595byte(0x00);
		}
	}
}
void main()
{
	u16 j;
	while(1)
	{
		for(j=0;j<10;j++)
		{
			switch(j)
			{
				case (0):display(zero595);break;
				case (1):display(one595);break;
				case (2):display(two595);break;
				case (3):display(three595);break;
				case (4):display(four595);break;
				case (5):display(five595);break;
				case (6):display(six595);break;
				case (7):display(seven595);break;
				case (8):display(eight595);break;
				case (9):display(nine595);break;
			}
			delay(1000);
		}
	}
	
}