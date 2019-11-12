#include "STC15Fxxxx.h"
#include "STDEF.h"

#define CCP_S0 0x10
#define CCP_S1 0x20

void PWM_INIT(void)
{
	ACC = AUXR1;
	ACC &= ~(CCP_S0 | CCP_S1);
	ACC |= CCP_S0;
	AUXR1 = ACC;
	
//	AUXR1 &= 0xCF;	//choose I/O output series (P3.6/P3.5)
	CCON   = 0;		//initialize CCON, including stoping PCA counter & resetting overflow flag
	CL     = 0;
	CH     = 0;		//initialize counter CH & CL
	
	CMOD   = 0x02;	//set PCA timer source (SYSclk/2)
					//disable PCA timer overflow interruption
	
	PCA_PWM0 = 0x00;			//PCA module 0 work as 8 bit mode
//	CCAP0H = CCAP0L = 26;		//duty ratio is 90%
	CCAPM0 = 0x42;
	
	PCA_PWM1 = 0x00;			//PCA module 1 work as 8 bit mode
//	CCAP1H = CCAP1L = 51;		//duty ratio is 80%
	CCAPM1 = 0x42;
	
//	PCA_PWM2 = 0x00;			//PCA module 2 work as 8 bit mode
//	CCAP0H = CCAP0L = 77;		//duty ratio is 70%
//	CCAPM0 = 0x42;

	CR = 1;		//enable PCA timer

}

void PWM_Out (uchar channal , uchar duty)
{
	uchar value;
	value = 256 - duty*256/100;
	
	if (channal == 0)
	{
		CCAP0H = CCAP0L = value;
	}
	
	if (channal == 1)
	{
		CCAP1H = CCAP1L = value;
	}
}

