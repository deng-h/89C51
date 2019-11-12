#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

u8 flag,a[4],i=0,j=0;
u8 table[]="Give me ";
void UsartInt()//���ڳ�ʼ������
{
	TMOD=0x20;//��ʱ��1
	TH1=0xF3;
	TL1=0xF3;
	PCON=0x80;//SMOD�����ʱ���λ
	TR1=1;  //��ʱ��1����
	SCON=0x50; // 01(ʮλ�첽�շ�)01(�����н���λ) 0000
	ES=1;  //(�����ж�����λ)
	EA=1;
}

void main()
{
	UsartInt();
	while(1)
	{
		if(flag==1)
		{
			ES=0;//�رմ����ж�
			for(i=0;i<8;i++)
			{
				SBUF=table[i];//���ͻ�����
				while(!TI);//��ⷢ���Ƿ����
				TI=0;
			}
			for(i=0;i<4;i++)
			{
				SBUF=a[i];//���ͻ�����
				while(!TI);//��ⷢ���Ƿ����
				TI=0;
			}
			while(!TI);
			TI=0;
			ES=1;
			flag=0;
		}
	}
}

void Usart() interrupt 4  //4ָ�����ж����
{
	RI=0;
	a[j++]=SBUF;
	if(j==4) 
	{
		j=0;
		flag=1;
	}
}