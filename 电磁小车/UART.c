#include "STC15Fxxxx.h"
#include "STDEF.h"
#include <stdio.h>

void Timer0_INIT(void);

#define T5MS  (65536-MAIN_Fosc*5/1000/12)     //12Tģʽ��5ms��ʱ
#define	T2_BR_Reload	(65536UL -(MAIN_Fosc /4/BaudRate)) //Timer2 ��װֵ��


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
        SBUF = BUF[i];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
        while(!TI);				//�������ݴ���	(TI�����жϱ�־)
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
               ���ڳ�ʼ������
******************************************************/
void UART_INIT(void) 
{
	Timer0_INIT();
    S1_8bit();				  //��ʽ1��8λ����

    AUXR &= ~(1<<4);	//Timer stop
    AUXR |= 0x01;		 //S1 BRT Use Timer2;
    AUXR |=  (1<<2);	 //Timer2 set as 1T mode
    TH2 = (u8)(T2_BR_Reload >> 8);
    TL2 = (u8)T2_BR_Reload;
    AUXR |=  (1<<4);	//Timer run enable
	
    RI=0;
    TI=0;
	
    REN = 1;	//�������
    ES  = 1;	//�����ж�
	//ReceiveOK=0;
	ReceiveNUM=0;
    //EA = 1;		//����ȫ���ж�
}

void Timer0_INIT(void)
{
    //AUXR &= 0x7F;
    TMOD &= 0xF0;        //ѡ��ģʽ0  16λ���� ������65535
    TH0 = T5MS>>8;
    TL0 = T5MS;
    ET0=1;	
    TR0=0;    //�ر�T0��ʱ�����ȴ�����
}

/****************************************************
               �����жϳ���
******************************************************/
void SER_INT (void) interrupt UART1_VECTOR 
{
    if(RI == 1)        //RI�����жϱ�־
    {
		RI = 0;		    //���RI�����жϱ�־
		REData[NUM]=SBUF;  //SUBF����/���ͻ����� 	
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

