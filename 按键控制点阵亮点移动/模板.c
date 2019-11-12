/*
�涨S2Ϊ�ϣ�S10Ϊ�£�S5Ϊ��S7Ϊ��
*/
#include <reg52.h>
#include <intrins.h>
#include <stdlib.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit RCLK_=P3^5;
sbit SRCLK=P3^6;
sbit SER=P3^4;
u16 key[]={0,0,0,0};
u8 code point[][2]={{0x7f,0x80},{0xbf,0x80},{0xdf,0x80},{0xef,0x80},{0xf7,0x80},{0xfb,0x80},{0xfd,0x80},{0xfe,0x80},
										{0x7f,0x40},{0xbf,0x40},{0xdf,0x40},{0xef,0x40},{0xf7,0x40},{0xfb,0x40},{0xfd,0x40},{0xfe,0x40},
										{0x7f,0x20},{0xbf,0x20},{0xdf,0x20},{0xef,0x20},{0xf7,0x20},{0xfb,0x20},{0xfd,0x20},{0xfe,0x20},
										{0x7f,0x10},{0xbf,0x10},{0xdf,0x10},{0xef,0x10},{0xf7,0x10},{0xfb,0x10},{0xfd,0x10},{0xfe,0x10},
										{0x7f,0x08},{0xbf,0x08},{0xdf,0x08},{0xef,0x08},{0xf7,0x08},{0xfb,0x08},{0xfd,0x08},{0xfe,0x08},
										{0x7f,0x04},{0xbf,0x04},{0xdf,0x04},{0xef,0x04},{0xf7,0x04},{0xfb,0x04},{0xfd,0x04},{0xfe,0x04},
										{0x7f,0x02},{0xbf,0x02},{0xdf,0x02},{0xef,0x02},{0xf7,0x02},{0xfb,0x02},{0xfd,0x02},{0xfe,0x02},
										{0x7f,0x01},{0xbf,0x01},{0xdf,0x01},{0xef,0x01},{0xf7,0x01},{0xfb,0x01},{0xfd,0x01},{0xfe,0x01}};
void delay(u16 i)
{
	while(i--);
}
void hc595byte(u8 dat)   //�����Ǹ�����������ߵ͵�ƽ
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

u16 key_press()     //��ⰴ���Ƿ񱻰��£������£����ط���0-�ϣ�1-�£�2-��3-��
{
	u16 i,direct=-1;
	P1=0xf0;      //�ж����¼�
	if(P1!=0xf0)
	{
		delay(100);
		switch(P1)
		{
			case(0x70):key[0]=1;break;  //��⵽S2��
			case(0xd0):key[1]=1;break; //��⵽S10��
		}
	}
	P1=0x2f;      //�ж����Ҽ���2f�е�2��Ϊ����ֹ��������
	if(P1!=0x2f)
	{
		delay(100);
		switch(P1)
		{
			case(0x27):key[2]=1;break; //��⵽S5��
			case(0x2d):key[3]=1;break;//��⵽S7��
		}
	}

	delay(5000);  //!!!!!!!!!!!!
	delay(5000);	//��ʱ�������������ʱ���ںܶ�ʱ���ڴ˺���һֱ��Ч��Ҫ�����ֱܷ��ʱ����
	delay(5000);  //!!!!!!!!!!
	for(i=0;i<4;i++)
	{
		if(key[i]==1)
		{
			direct=i;
			break;
		}
	}
	return direct;
}
void open_point(u16 pos)  //����ĳһ���ڵ����е�λ�ã�����ĳһ��
{
	P0=point[pos][0];
	hc595byte(point[pos][1]);
}
u16 move(u16 direct,u16 position)  //�βμ��������λ������
{
	switch(direct)
	{
		case 0:position-=8;break;
		case 1:position+=8;break;
		case 2:position-=1;break;
		case 3:position+=1;break;
	}
	return position;
}

void main()
{
	u16 p=20;
	open_point(p);
	while(1)
	{
		switch(key_press())
		{
			case 0:open_point(move(0,p));p-=8;key[0]=0;break;
			case 1:open_point(move(1,p));p+=8;key[1]=0;break;
			case 2:open_point(move(2,p));p-=1;key[2]=0;break;
			case 3:open_point(move(3,p));p+=1;key[3]=0;break;
		}
	}
}