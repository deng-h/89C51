#include "STC15Fxxxx.h"
/********************************************************************************/

void Time0_Init(void);

#define T5MS (65536-MAIN_Fosc*5/1000/12)     //12Tģʽ��5ms��ʱ
#define	T2_BR_Reload	(65536UL -(MAIN_Fosc /4/BaudRate)) //Timer2 ��װֵ��


#define BUFFER_LENGTH 20
unsigned char ReData[BUFFER_LENGTH];
unsigned char ReceiveNum;
unsigned char Num;

/****************************************************
               �����շ�����
******************************************************/

void UART_Write(unsigned char *Buf,unsigned char Num)  //�������ݣ������׵�ַ��������
{
    unsigned char i;
	  //RS485E=1;
    for(i=0;i<Num;i++)
    {
        SBUF = Buf[i];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
        while(!TI);				//�������ݴ���	(TI�����жϱ�־)
        TI=0;		
    }
}

/*
void UART_Hex2Txt(unsigned char Num)
{
    unsigned char Str[4];
	  //RS485E=1;
	Str[0]=Num/100+'0';
	Num%=100;
	Str[1]=Num/10+'0';
	Str[2]=Num%10+'0';
	Str[3]='\n';
	UART_Write(Str,4);
}
*/

/****************************************************
               ���ڳ�ʼ������
******************************************************/
void UART_Init(void) 
{
	Time0_Init();
    //S1_8bit();				  //��ʽ1��8λ����

    //AUXR &= ~(1<<4);	//Timer stop
    //AUXR |= 0x01;		 //S1 BRT Use Timer2;
    //AUXR |=  (1<<2);	 //Timer2 set as 1T mode
    //TH2 = (u8)(T2_BR_Reload >> 8);
    //TL2 = (u8)T2_BR_Reload;
    //AUXR |=  (1<<4);	//Timer run enable
	
	  TMOD=0x20;//��ʱ��1,��λ�Զ���װ��ʽ
		TH1=0xF3;  //����12MHZ�������ʱ�����������4800
		TL1=0xF3;
		PCON=0x80;//SMOD�����ʱ���λ��ֻ�����е����λ
		TR1=1;  //��ʱ��1����
		SCON=0x50; // 0101 0000
	
    RI=0;
    TI=0;
	
    REN = 1;	//�������
    ES  = 1;	//�����ж�
	//ReceiveOK=0;
	ReceiveNum=0;
    //EA = 1;		//����ȫ���ж�
}

void Time0_Init(void)
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
void ser_int (void) interrupt UART1_VECTOR   //�����жϣ�����
{
    if(RI == 1)        //RI�����жϱ�־
    {
		RI = 0;		    //���RI�����жϱ�־
		ReData[Num]=SBUF;  //SUBF����/���ͻ����� 	
		Num++;
		//SBUF=Num;
		TH0 = T5MS >> 8;   //��ʱ���ص���ֵ���¼�ʱ
		TL0 = T5MS;
		TR0=1;
    }
}



void timer0() interrupt TIMER0_VECTOR   
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

