#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit led1=P2^0;
sbit key1=P3^1;
void delay(u16 i)
{
	while(i--);
}
void keypress()
{
	if(key1==0)    //�ж�P3^1�Ƿ�������ӣ��������Ƿ���
	{
		delay(1000);  //��ʱ1ms�����·���
		if(key1==0)   //�ٴ��ж��Ƿ��������
		{
			led1=~led1;  //P2^0��1��0��ת��
		}
		while(!key1);   //���Ϊ0��ѭ����ֱ��Ϊ1���ɿ�������
	}
}
void main()
{
	keypress();
}




