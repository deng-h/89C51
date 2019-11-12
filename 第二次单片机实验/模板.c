#include <reg52.h>
#include <intrins.h>
unsigned int count=0,flag=1,i=0;   //flag为某一位的亮灭判断，1亮0灭
char dat[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
void main()
{
	TMOD=0x01;   //T016位计时器
	TH0=0xfc;   //1ms
	TL0=0x18; 
	TR0=1;     //允许T0允许
	IE=0x82;   //打开EA和ET0
	while(1)
	{
		if(TF0==1)
		{
			TF0=0;      //清除溢出标志位
			TH0=0xfc;   //重新装初值
			TL0=0x18;
			count++;
			if(count>=500)  //0.5s
			{
				count=0;
				if(flag==1)
				{
					flag=0;
					P2=0xff;   //全灭
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