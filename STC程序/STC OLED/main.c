#include <STC15F2K60S2.h>
#include <OLED.h>
typedef unsigned int uint;
typedef unsigned char uchar;

void main()
{
	OLED_Init();
	OLED_Switch(1);  //´ò¿ªOLED
	OLED_P8x16Str(55,2,"DH");
	OLED_P6x8Int(5,3,2019,4);
	while(1);
}