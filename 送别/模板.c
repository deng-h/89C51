#include <reg52.h>
sbit beep=P1^5;
int Beat_val=0;
#define Do0 358
#define Do  179
#define Do1 90

#define Re0 319
#define Re  160
#define Re1 80

#define Mi0 284
#define Mi  142
#define Mi1 71

#define Fa0 269
#define Fa  135
#define Fa1 67

#define So0 239
#define So  119
#define So1 60

#define La0 213
#define La  106
#define La1 53

#define Si0 189
#define Si 95
#define Si1 47

#define STP 10000

#define B41 2000  
#define B31 3000
#define B21 1000
#define B32 750
#define B11 500
#define B34 313
#define B12 250
#define B13 125
#define B14 63
int code T_B[]={So,B11,Mi,B12,So,B12,Do1,B21,La,B11,Do1,B11,So,B21,
								So,B11,Do,B12,Re,B12,Mi,B11,Re,B12,Do,B12,Re,B21,
								So,B11,Mi,B12,So,B12,Do1,B32,Si,B12,La,B11,Do1,B11,
								So,B21,So,B11,Re,B12,Mi,B12,Fa,B32,Si0,B12,Do,B21,La,B11,
								Do1,B11,Do1,B21,Si,B11,La,B12,Si,B12,Do1,B21,La,B12,Si,B12,
								Do1,B12,La,B12,La,B12,So,B12,Mi,B12,Do,B12,Re,B21,So,B11,
								Mi,B12,So,B12,Do1,B32,Si,B12,La,B11,Do1,B11,So,B21,So,B11,
								Re,B12,Mi,B12,Fa,B32,Si0,B12,Do,B21,B21};
void IntT0()   
{  
	ET0=1;      
	TMOD|=0x01; 
	TR0=1;      
	TH0=0xfc;   
	TL0=0x18;
}
void t0() interrupt 1
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
		beep=0;
		i=tone;
		while(i) i--;
		beep=1;
		i=tone;
		while(i) i--;
	}
	  EA=0;	
}

void playmusic()
{
	int tone=0;
	int beat=1;
	while(T_B[beat]>0)
	{
		tone+=2;
		beat+=2;
		Buzzer(T_B[tone],T_B[beat]);
	}
}

void main()
{
	IntT0();
	while(1)
	{
		playmusic();
	}
}

