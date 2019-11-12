#include "STC15Fxxxx.h"
#include "STDEF.h"
#include <stdio.h>

void Timer0_INIT(void);

#define T5MS  (65536-MAIN_Fosc*5/1000/12)     //12T模式，5ms定时
#define	T2_BR_Reload	(65536UL -(MAIN_Fosc /4/BaudRate)) //Timer2 重装值，


#define Buffer_Length 20
uchar REData[Buffer_Length];
uchar ReceiveNUM;
uchar NUM;


void UART_Write(uchar *BUF, uchar NUM)
{
    uchar i;
	  //RS485E=1;
    for(i=0;i<NUM;i++)
    {
        SBUF = BUF[i];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
        while(!TI);				//等特数据传送	(TI发送中断标志)
        TI=0;		
    }
}

void UART_Write_Byte(uchar byte)
{
	SBUF = byte;
	while(!TI);
	TI=0;
}


//void UART_HEX2TXT(uchar NUM)
//{
//    uchar str[4];
//	  //RS485E=1;
//	str[0]=NUM/100+'0';
//	NUM%=100;
//	str[1]=NUM/10+'0';
//	str[2]=NUM%10+'0';
//	str[3]='\n';
//	UART_Write(str,4);
//}


/****************************************************
               串口初始化程序
******************************************************/
void UART_INIT(void) 
{
	Timer0_INIT();
    S1_8bit();				  //方式1，8位数据

    AUXR &= ~(1<<4);	//Timer stop
    AUXR |= 0x01;		 //S1 BRT Use Timer2;
    AUXR |=  (1<<2);	 //Timer2 set as 1T mode
    TH2 = (u8)(T2_BR_Reload >> 8);
    TL2 = (u8)T2_BR_Reload;
    AUXR |=  (1<<4);	//Timer run enable
	
    RI=0;
    TI=0;
	
    REN = 1;	//允许接收
    ES  = 1;	//允许中断
	//ReceiveOK=0;
	ReceiveNUM=0;
    //EA = 1;		//允许全局中断
}

void Timer0_INIT(void)
{
    //AUXR &= 0x7F;
    TMOD &= 0xF0;        //选择模式0  16位计数 最大计数65535
    TH0 = T5MS>>8;
    TL0 = T5MS;
    ET0=1;	
    TR0=0;    //关闭T0定时器，等待开启
}

/****************************************************
               串口中断程序
******************************************************/
void SER_INT (void) interrupt UART1_VECTOR 
{
    if(RI == 1)        //RI接受中断标志
    {
		RI = 0;		    //清除RI接受中断标志
		REData[NUM]=SBUF;  //SUBF接受/发送缓冲器 	
		NUM++;
		//SBUF=Num;
		TH0 = T5MS >> 8;
		TL0 = T5MS;
		TR0=1;
    }
}



void Timer0() interrupt TIMER0_VECTOR   
{		
    TR0=0;
	ReceiveNUM=NUM;
    NUM=0;
}

uchar UART_Read(uchar *BUF)
{
	uchar i;
	for(i=0; i<ReceiveNUM;i++)
	{
		BUF[i]=REData[i];
	}
	i=ReceiveNUM;
	ReceiveNUM=0;
	return i;
}

