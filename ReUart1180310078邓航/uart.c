#include "reg52.h"
#include <UART.h>
#define T5MS (65536-11059200L*5/1000/12)     //12Tģʽ��5ms��ʱ
#define	T2_BR_Reload	(65536UL -(11059200L /4/115200UL)) //Timer2 ��װֵ��
#define BUFFER_LENGTH 32
unsigned char ReData[BUFFER_LENGTH];
unsigned char ReceiveNum;
unsigned char Num=0;
/****************************************************
               �����շ�����
******************************************************/

void UART_Write(unsigned char *Buf,unsigned char Num)  //�������ݣ������׵�ַ��������
{
    unsigned char i;
    for(i=0;i<Num;i++)
    {
       SBUF = Buf[i];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
       while(!TI);				//�������ݴ���	(TI�����жϱ�־)
       TI=0;		
    }
}

/****************************************************
               ���ڳ�ʼ������
******************************************************/

void UART_Init(void) 
{
	  TMOD = 0x21;  //��ʱ������1��2ͬʱ����
		TH1=0xF3;  //����12MHZ�������ʱ�����������4800
		TL1=0xF3;
		ET1=1;
		PCON=0x80;//SMOD�����ʱ���λ��ֻ�����е����λ
		TR1=1;  //��ʱ��1����
		SCON=0x50; // 0101 0000
	  TH0 = T5MS>>8;
    TL0 = T5MS;
	  ET0=1;	
    TR0=0;    //�ر�T0��ʱ�����ȴ�����
    RI=0;
    TI=0;
    REN = 1;	//�������
    ES  = 1;	//�����ж�
		ReceiveNum=0;
}

/****************************************************
               �����жϳ���
******************************************************/
void ser_int (void) interrupt 4   //�����жϣ�����
{
    if(RI == 1)        //RI�����жϱ�־
    {
			RI = 0;		    //���RI�����жϱ�־
			ReData[Num]=SBUF;  //SUBF����/���ͻ����� 	
			Num++;
			TH0 = T5MS >> 8;   //��ʱ���ص���ֵ���¼�ʱ
			TL0 = T5MS;
			TR0=1;
    }
}

void timer0() interrupt 1   
{		
  TR0=0;          //�ﵽ�涨ʱ�䣬�����жϣ��رն�ʱ���ж�
	ReceiveNum=Num;   //�����յ��ĸ���
  Num=0;
}

unsigned char UART_Read(unsigned char *Buf)   //�������մ�ŵ������׵�ַ���ѻ�����������ݷ�������
{
	unsigned char i;
	for(i=0; i<ReceiveNum;i++)
	{
		Buf[i]=ReData[i];
	}
	i=ReceiveNum;
	ReceiveNum=0;
	return i;    //��������Ԫ�ظ���
}
