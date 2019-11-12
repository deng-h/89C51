#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

u8 flag,a[4],i=0,j=0;
u8 table[]="Give me ";
void UsartInt()//串口初始化函数
{
	TMOD=0x20;//定时器1
	TH1=0xF3;
	TL1=0xF3;
	PCON=0x80;//SMOD波特率倍增位
	TR1=1;  //定时器1运行
	SCON=0x50; // 01(十位异步收发)01(允许串行接收位) 0000
	ES=1;  //(串行中断允许位)
	EA=1;
}

void main()
{
	UsartInt();
	while(1)
	{
		if(flag==1)
		{
			ES=0;//关闭串口中断
			for(i=0;i<8;i++)
			{
				SBUF=table[i];//发送缓冲器
				while(!TI);//检测发送是否完成
				TI=0;
			}
			for(i=0;i<4;i++)
			{
				SBUF=a[i];//发送缓冲器
				while(!TI);//检测发送是否完成
				TI=0;
			}
			while(!TI);
			TI=0;
			ES=1;
			flag=0;
		}
	}
}

void Usart() interrupt 4  //4指串行中断序号
{
	RI=0;
	a[j++]=SBUF;
	if(j==4) 
	{
		j=0;
		flag=1;
	}
}