/*
	k1确认键，k2取消键，k3重置密码键(密码输入正确的情况下能用),k4返回键(用于密码输入正确后想退出的情况)
	密码输入错误会报警，三次后会长时间报警，数码管闪烁
	重置完密码后按确认键，回到输入密码状态
	重置密码时，两次密码不正确蜂鸣器会响，需要重新输入两次密码
	密码重置与验证，处理好两次输入时的显示以及两次密码不对时对两个数组的处理及后续
	复位保存，掉电保存
*/
#include <reg51.h>
#include "i2c.h"
#include "delay.h"
typedef unsigned int u16;	
typedef unsigned char u8;
#define GPIO_KEY P1

sbit ok=P3^1;      //确认键
sbit cancel=P3^0;  //取消键
sbit set=P3^2;     //重置密码键
sbit back=P3^3;    //返回键

sbit Beep=P1^5;    //蜂鸣器
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

int Beat_val=0;  //蜂鸣器
u8 smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  //0~9
u8 Pwd[6]={1,2,3,4,5,6},Mask[8],PwdRead[6],DataHex[8],PwdRead2[6];   //PwdRead2[6]用于密码二次确认
u8 correct[8]={0x39,0x09,0x09,0x09,0x09,0x09,0x09,0x0f};  //用于输入正确时的显示
u8 warning[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};  //3次输入错误时数码管的显示
u8 bdata PassFlg=0,AllowSetPwdFlg=0,SetPwdFlg=0,PwdTwiceFlg=0,VerifyFlg=0;    
u8 counter=0,KeyValue,TryTime=0;   //用来记录输入了几位数

void main()
{
	Timer0_Init();
	PwdWrite(&Pwd,sizeof(Pwd)); //开始时写入密码                           需要掉电保存

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
			if(SetPwdFlg||PwdTwiceFlg||VerifyFlg) DataHex[counter-1]=smgduan[KeyValue];   //储存重置密码的编码
			if(PwdTwiceFlg) PwdRead2[counter-1]=KeyValue;   //储存第二次输入的密码
		}
		
		if((SetPwdFlg||PwdTwiceFlg)&&(counter!=0))    //显示重置的密码
		{
			DigDisplay(&DataHex,sizeof(DataHex));
		}
		
		if((counter!=0)&&(!PassFlg||VerifyFlg))     //修改密码时输入密码用掩码显示 
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
			Buzzer(95,250); //蜂鸣器的频率和节拍
			DigDisplay(&warning,sizeof(warning));
		}
	}
}


void OkKeyPress()
{
	u8 i;
	if(ok==0)  //判断是否按下确认键        
	{
		delay10ms();
		if(ok==0) 
		{
			if(VerifyFlg)              //用于重置密码前的密码验证
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
			
			else if(PwdTwiceFlg)                //第二次的输入确定
			{
				for(i=0;i<6;i++)
				{
					if(PwdRead[i]!=PwdRead2[i]) break;
				}
				if(i<6)   //两次输入的密码不一致
				{
					TR0=1;
					Buzzer(95,250);
					TR0=0;
					for(i=0;i<6;i++) PwdRead[i]=0;
					for(i=0;i<6;i++) PwdRead2[i]=0;
					for(i=0;i<8;i++) DataHex[i]=0x00;
					counter=0;
				}
				else    //两次密码输入正确，存入密码
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
			
			else if(SetPwdFlg)      //第一次的输入确定
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
void PwdWrite(u8 *buff, u8 len)   //数组首地址，数组长度
{
	u8 At24c02_addr=1;     
	while(len--)
	{
		At24c02Write(At24c02_addr++,*buff);
		delay10ms();
		buff++;
	}
}



u8 PwdVerify(u8 *buff, u8 len)   //密码验证
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
	u8 bdata flag=0;   //flag用于判断是否按过键
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
	ET0=1; //EA,TR0不在此处设置
}

