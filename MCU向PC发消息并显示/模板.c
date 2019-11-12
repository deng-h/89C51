#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

int sum=48;
u8 list[]="times";

void Uart_init()
{
	TMOD=0x20;//��ʱ��1,��λ�Զ���װ��ʽ
	TH1=0xF3;  //����12MHZ�������ʱ�����������4800
	TL1=0xF3;
	PCON=0x80;//SMOD�����ʱ���λ��ֻ�����е����λ
	TR1=1;  //��ʱ��1����
	SCON=0x50; // 0101 0000
	EX0=1;  //���ⲿ�ж�0
	IT0=1;  //�½��ش���
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
	SBUF=sum;// ���͵���ASCII,���ǵ�Ϊʲô������
	while(!TI);
	TI=0;
}


	