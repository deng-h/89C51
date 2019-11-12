#include <REG51.H>
#include "stdint.h"

uint8_t SavedKey;

bit KeyPress;
bit KeyEvent;
bit KeyNotice;

#define KEY_PORT P3
#define KEY_MASK 0x0f


void Key_Init(void)
{
	KeyPress=0;
	KeyEvent=0;
	KeyNotice=0;	
}

void Key_Scan(void)
{
	uint8_t TempValue;
	TempValue= (~KEY_PORT) & KEY_MASK;	
	if(TempValue == 0x00)     //No Key Pressed
    {
        if(KeyPress==1)       //
		{
			KeyEvent=1;
		}
		else
		{
			KeyEvent=0;
		}
		KeyPress=0;
		
    }
    else                      //Detect Key Pressed       
    {
        if(KeyPress==0)       //is first detect
		{
			KeyEvent=1;
		}
		else
		{
			KeyEvent=0;
		}
		KeyPress=1;
    }
	
	if(KeyEvent==1)
	{
		KeyEvent=0;
		if(KeyPress==1)
		{
			SavedKey=TempValue;
		}
		else
		{
			KeyNotice=1;
		}
	}
}

unsigned char Key_Read(void)
{
	if(KeyNotice)
	{
		KeyNotice=0;
		return SavedKey;
	}
	else
	{
		return 0;
	}
}
