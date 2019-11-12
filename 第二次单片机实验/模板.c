#include <reg52.h>
#include <intrins.h>
unsigned int count=0,flag=1,i=0;   //flagΪĳһλ�������жϣ�1��0��
char dat[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
void main()
{
	TMOD=0x01;   //T016λ��ʱ��
	TH0=0xfc;   //1ms
	TL0=0x18; 
	TR0=1;     //����T0����
	IE=0x82;   //��EA��ET0
	while(1)
	{
		if(TF0==1)
		{
			TF0=0;      //��������־λ
			TH0=0xfc;   //����װ��ֵ
			TL0=0x18;
			count++;
			if(count>=500)  //0.5s
			{
				count=0;
				if(flag==1)
				{
					flag=0;
					P2=0xff;   //ȫ��
				}
				else
				{
					flag=1;
					P2=dat[i++];
				}
				if(i>=8) i=0;
			}
		}
	}
}