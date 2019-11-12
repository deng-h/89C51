#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit led1=P2^0;
sbit key3=P3^2;
sbit key4=P3^3;
sbit led2=P2^1;
void delay(u16 i)
{
	while(i--);
}

void Int_ex0()
{
	EA=1;   //�ж�������λ ��
	EX0=1;   //�ⲿ�ж�0����λ ��
	IT0=1;   //ѡ�񴥷���ʽ Ϊ�½��ش���
}

void Int_ex1()
{
	EA=1;
	EX1=1;   //�ⲿ�ж�1����λ ��
	IT1=1;
}

void main()
{
	Int_ex0();
	Int_ex1();
	while(1);
}
void IntIE0() interrupt 0
{
	delay(1000);
	if(key3==0)
		led1=~led1;
}
void IntIE1() interrupt 2
{
	delay(1000);
	if(key4==0)
		led2=~led2;
}





