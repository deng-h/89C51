/*
	k1ȷ�ϼ���k2ȡ������k3���������(����������ȷ�����������),k4���ؼ�(��������������ȷ�����˳������)
	�����������ᱨ�������κ�᳤ʱ�䱨�����������˸
	�����������ȷ�ϼ����ص���������״̬
	��������ʱ���������벻��ȷ���������죬��Ҫ����������������
	������������֤���������������ʱ����ʾ�Լ��������벻��ʱ����������Ĵ�������
	��λ���棬���籣��
*/
#include <reg51.h>
#include "i2c.h"
#include "delay.h"
typedef unsigned int u16;	
typedef unsigned char u8;
#define GPIO_KEY P1

sbit ok=P3^1;      //ȷ�ϼ�
sbit cancel=P3^0;  //ȡ����
sbit set=P3^2;     //���������
sbit back=P3^3;    //���ؼ�

sbit Beep=P1^5;    //������
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

void Buzzer(int tone,int beat);
void Timer0_Init(void);
void PwdWrite(u8 *buff, u8 len);
void DigDisplay(u8 *buff,u8 len);
void OkKeyPress(void);
void CancelKeyPress(void);
void SetPwdKeyPress(void);
void BackKeyPress(void);
u8 PwdVerify(u8 *buff, u8 len);
u8 KeyPress(void);

int Beat_val=0;  //������
u8 smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  //0~9
u8 Pwd[6]={1,2,3,4,5,6},Mask[8],PwdRead[6],DataHex[8],PwdRead2[6];   //PwdRead2[6]�����������ȷ��
u8 correct[8]={0x39,0x09,0x09,0x09,0x09,0x09,0x09,0x0f};  //����������ȷʱ����ʾ
u8 warning[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};  //3���������ʱ����ܵ���ʾ
u8 bdata PassFlg=0,AllowSetPwdFlg=0,SetPwdFlg=0,PwdTwiceFlg=0,VerifyFlg=0;    
u8 counter=0,KeyValue,TryTime=0;   //������¼�����˼�λ��

void main()
{
	Timer0_Init();
	PwdWrite(&Pwd,sizeof(Pwd)); //��ʼʱд������                           ��Ҫ���籣��

	while(1)
	{
		OkKeyPress();
		CancelKeyPress();
		SetPwdKeyPress();
		BackKeyPress();
		
		if(KeyPress()) 
		{
			counter++;
			if(!PwdTwiceFlg||SetPwdFlg||VerifyFlg) PwdRead[counter-1]=KeyValue;
			if(SetPwdFlg||PwdTwiceFlg||VerifyFlg) DataHex[counter-1]=smgduan[KeyValue];   //������������ı���
			if(PwdTwiceFlg) PwdRead2[counter-1]=KeyValue;   //����ڶ������������
		}
		
		if((SetPwdFlg||PwdTwiceFlg)&&(counter!=0))    //��ʾ���õ�����
		{
			DigDisplay(&DataHex,sizeof(DataHex));
		}
		
		if((counter!=0)&&(!PassFlg||VerifyFlg))     //�޸�����ʱ����������������ʾ 
		{
			Mask[counter-1]=0x40;   //0x40='-'	
			DigDisplay(&Mask,sizeof(Mask));
		}
			
		if(PassFlg&&((!SetPwdFlg)&&(!PwdTwiceFlg)&&(!VerifyFlg)))
		{
			DigDisplay(&correct,sizeof(correct));
		}
		
		if(TryTime==3) 
		{
			TR0=1;
			Buzzer(95,250); //��������Ƶ�ʺͽ���
			DigDisplay(&warning,sizeof(warning));
		}
	}
}


void OkKeyPress()
{
	u8 i;
	if(ok==0)  //�ж��Ƿ���ȷ�ϼ�        
	{
		delay10ms();
		if(ok==0) 
		{
			if(VerifyFlg)              //������������ǰ��������֤
			{
				AllowSetPwdFlg=(PwdVerify(&PwdRead,sizeof(PwdRead)))? 1 : 0;
				if(AllowSetPwdFlg)         //
				{
					SetPwdFlg=1;
					VerifyFlg=0;
					counter=0;
					for(i=0;i<8;i++) Mask[i]=0x00;
					for(i=0;i<8;i++) DataHex[i]=0x00;
				}
				else
				{
					TR0=1;
					Buzzer(95,250);
					TR0=0;
					for(i=0;i<8;i++) DataHex[i]=0x00;
					counter=0;
				}
			}
			
			else if(PwdTwiceFlg)                //�ڶ��ε�����ȷ��
			{
				for(i=0;i<6;i++)
				{
					if(PwdRead[i]!=PwdRead2[i]) break;
				}
				if(i<6)   //������������벻һ��
				{
					TR0=1;
					Buzzer(95,250);
					TR0=0;
					for(i=0;i<6;i++) PwdRead[i]=0;
					for(i=0;i<6;i++) PwdRead2[i]=0;
					for(i=0;i<8;i++) DataHex[i]=0x00;
					counter=0;
				}
				else    //��������������ȷ����������
				{
					PwdWrite(PwdRead,sizeof(PwdRead));
					PwdTwiceFlg=0;
					PassFlg=0;
					TryTime=0;
					counter=0;
					for(i=0;i<8;i++) Mask[i]=0x00;
					for(i=0;i<8;i++) DataHex[i]=0x00;
					for(i=0;i<6;i++) PwdRead[i]=0;
					for(i=0;i<6;i++) PwdRead2[i]=0;
				}
			}
			
			else if(SetPwdFlg)      //��һ�ε�����ȷ��
			{
				PwdTwiceFlg=1;
//				PwdWrite(PwdRead,sizeof(PwdRead));
				SetPwdFlg=0;
//				PassFlg=0;
//				TryTime=0;
				counter=0;
				TryTime=0;
				for(i=0;i<8;i++) Mask[i]=0x00;
				for(i=0;i<8;i++) DataHex[i]=0x00;
				
//				for(i=0;i<6;i++) PwdRead[i]=0;
			}
			
			else
			{
				PassFlg=(PwdVerify(&PwdRead,sizeof(PwdRead)))? 1 : 0;
				if((!PassFlg)&&(TryTime==0)) 
				{
					TryTime=1;
					TR0=1;
					Buzzer(95,250);
					TR0=0;
					for(i=0;i<8;i++) Mask[i]=0x00;
					for(i=0;i<6;i++) PwdRead[i]=0;
					counter=0;
				}
				else if ((!PassFlg)&&(TryTime==1)) 
				{
					TryTime=2;
					TR0=1;
					Buzzer(95,250);
					TR0=0;
					for(i=0;i<8;i++) Mask[i]=0x00;
					for(i=0;i<6;i++) PwdRead[i]=0;
					counter=0;
				}
				else if ((!PassFlg)&&(TryTime==2)) 
				{
					TryTime=3;
					TR0=1;
					Buzzer(95,250);
					TR0=0;
					for(i=0;i<8;i++) Mask[i]=0x00;
					for(i=0;i<6;i++) PwdRead[i]=0;
					counter=0;
				}
			}
		}
		while(!ok);
	}
}

void CancelKeyPress(void)
{
	if(cancel==0)
	{
		delay10ms();
		if(cancel==0)
		{
			if(counter>0)
			{
				Mask[counter-1]=0x00;
				DataHex[counter-1]=0x00; 
				counter--;
			}
		}
		while(!cancel);
	}
}

void SetPwdKeyPress(void)
{
	u8 i;
	if(set==0)
	{
		delay10ms();
		if(set==0)
		{
			if(PassFlg==1)
			{
				VerifyFlg=1;  
				TryTime=0;
				for(i=0;i<8;i++) Mask[i]=0x00;
				for(i=0;i<8;i++) DataHex[i]=0x00;
				counter=0;
			}
		}
		while(!set);
	}
}

void BackKeyPress(void)
{
	if(back==0)
	{
		delay10ms();
		if(back==0)
		{
			PassFlg=0;
		}
		while(!back);
	}
}
void PwdWrite(u8 *buff, u8 len)   //�����׵�ַ�����鳤��
{
	u8 At24c02_addr=1;     
	while(len--)
	{
		At24c02Write(At24c02_addr++,*buff);
		delay10ms();
		buff++;
	}
}



u8 PwdVerify(u8 *buff, u8 len)   //������֤
{
	u8 At24c02_addr=1,Pass=0,i=0,num; 
	for(i=0;i<len;i++)
	{
		num=At24c02Read(At24c02_addr);
		delay10ms();
		if(num==buff[i]) At24c02_addr++;
		else break;
	}
	if(i>=len) Pass=1;
	return Pass;
}


void DigDisplay(u8 *buff,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		switch(i)	 
		{
			case(0):LSA=0;LSB=0;LSC=0; break;
			case(1):LSA=1;LSB=0;LSC=0; break;
			case(2):LSA=0;LSB=1;LSC=0; break;
			case(3):LSA=1;LSB=1;LSC=0; break;
			case(4):LSA=0;LSB=0;LSC=1; break;
			case(5):LSA=1;LSB=0;LSC=1; break;
			case(6):LSA=0;LSB=1;LSC=1; break;
			case(7):LSA=1;LSB=1;LSC=1; break;	
		}
		P0=buff[7-i];
		delay1ms(); 
		P0=0x00;
	}
}


u8 KeyPress(void)
{
	char a=0;
	u8 bdata flag=0;   //flag�����ж��Ƿ񰴹���
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
	{
		delay10ms();
		if(GPIO_KEY!=0x0f)
		{	
			
			GPIO_KEY=0x0f;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			GPIO_KEY=0Xf0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;flag=1;break;
				case(0Xb0):	KeyValue=KeyValue+4;flag=1;break;
				case(0Xd0): KeyValue=KeyValue+8;flag=1;break;
				case(0Xe0):	KeyValue=KeyValue+12;flag=1;break;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 
			{
				delay10ms();
				a++;
			}
		}
	}
	if(flag) return 1;
	else return 0;
}

void Timer0() interrupt 1
{
	TH0=0xfc;   
	TL0=0x18;
	Beat_val--;
}


void Buzzer(int tone,int beat)
{
	int i=0;
	Beat_val=beat;
	EA=1;	
	while(Beat_val>0)
	{
		Beep=0;
		i=tone;
		while(i) i--;
		Beep=1;
		i=tone;
		while(i) i--;
	}
	  EA=0;	
}


void Timer0_Init()
{
	TMOD=0x01;
	TH0=0xfc;   //1ms
	TL0=0x18;
	ET0=1; //EA,TR0���ڴ˴�����
}

