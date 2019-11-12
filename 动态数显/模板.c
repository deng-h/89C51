#include <reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
u8 code list[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,
                           0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void delay(u16 i)    //延时
{
	 while(i--);
}
void digdisplay(u16 t)    //动态数显函数
{
	u16 i;
	for(i=0;i<8;i++)
	{
		switch (i)
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
		P0=list[i];
		delay(t);         //延时
		P0=0x00;         //消影
	}
}
void main()
{
   while(1)
	 {
		 u16 i,j,k,p;
		 for(i=30000;i>=6000;i-=6000)
		 {
			 digdisplay(i);
		    if(i==6000)
				{
					for(j=6000;j>=1000;j-=500)
					 {
						 digdisplay(j);
						 if(j==1000)
						 {
							 for(k=1000;k>=500;k-=100)
							 {
								 digdisplay(k);
							   if(k==500)
								 {
									 for(p=500;p>=200;p-=50)
									 {
										 digdisplay(p);
										 while(p==200)
											 digdisplay(p);
									 }
								 }
							 }
						 }
					 }
				}
		 } 
	 }
}



















