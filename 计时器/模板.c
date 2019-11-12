/*
ʱ��:2019.4.21 ������ 
����:��ʱ.�������ϵĶ�������K3���ڼ�ʱ���ã�K4�����ڼ�ʱ��ͣ��ʼ
*/
#include <reg52.h>
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit reset=P3^2;  //���ڶ�ʱ������
sbit on_off=P3^3;   //���ڼ�ʱ��ֹͣ�Ϳ���
int hour=0,min=0,sec=0,i=0;
char code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};

void delay(int i)
{
	while(i--);
}

void Init_T0()
{
	EA=1;
	ET0=1;      //�򿪶�ʱ�������ж�����λ
	TMOD|=0x01;  //���ù�����ʽ(GATE,C/T,M1M0)
	TR0=1;      //��1������T0����
	TH0=0xfc;   //���ó�ֵ
	TL0=0x18;
}

void Init_Ex()
{
	EX0=1;
	IT0=1; //�½��ش���
	EX1=1;
	IT1=1;
}
void display_part(int x,int pos)   //������ʾ����,xΪҪ��ʾ�����֣�posΪ��ʾ��λ��
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
	int a,b;  //ȡ����λʮλ
	a=sec%10;
	b=sec/10;
	display_part(a,0);  //��
	display_part(b,1);
	display_part(10,2);
	a=min%10;
	b=min/10;
	display_part(a,3);  //��
	display_part(b,4);
	display_part(10,5);
	a=hour%10;
	b=hour/10;
	display_part(a,6);  //ʱ
	display_part(b,7);
}

void main()
{
	Init_T0();
	Init_Ex();
	while(1)
	{
		if(i>=1000)  //֮���Բ�д(i==1000)ʱ��Ϊi�ı仯�ܿ죬��i==1000(���ʱ��)ʱȥ�ж���Ҫʱ�䣬i��ʱ�Ѿ�����1000��
		{
			sec++;
			i=0;
		}
		if(sec>=60)  //ͬ��
		{
			min++;
			sec=0;
		}
		if(min>=60)  //ͬ��
		{
			hour++;
			min=0;
		}
		display_all(hour,min,sec);	 //Сʱ�����ӣ���
	}
}

void t0() interrupt 1
{
	TH0=0xfc;   // �ص���ֵ�����¼�ʱ
	TL0=0x18;
	i++;
}

void Ex0() interrupt 0   //���ڶ�ʱ������
{
	delay(100);
	if(reset==0) 
	{
		hour=0;min=0;sec=0;
	}
}
void Ex1() interrupt 2   //���ڼ�ʱ��ֹͣ�Ϳ���
{
	delay(100);
	if(on_off==0)
	{
		ET0=~ET0;   //��ʱ�������ж�����λ��ת
	}
}