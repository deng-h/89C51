#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

u16 flag=0,i;
u8 a;
u8 list[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

void UsartInt()//串口初始化函数
{
	TMOD=0x20;//定时器1
	TH1=0xF3;
	TL1=0xF3;
	PCON=0x80;//SMOD波特率倍增位
	TR1=1;  //定时器1运行
	SCON=0x50; // 0101 0000
	ES=1;
	EA=1;
}
void main()
{
	 UsartInt();
	 while(1)
	 {
		 i=(int)(a-'0');
		 if(flag==1)
		 {
			 switch(i)
			 {
				 case 0:P2=list[0];break;
				 case 1:P2=list[1];break;
				 case 2:P2=list[2];break;
				 case 3:P2=list[3];break;
				 case 4:P2=list[4];break;
				 case 5:P2=list[5];break;
				 case 6:P2=list[6];break;
				 case 7:P2=list[7];break;
			 }
			 flag=0;
		 }
   }
}
void Usart() interrupt 4
{
	RI=0;
	a=SBUF;
	flag=1;
}


