#include "lcd.h"

/*******************************************************************************
* º¯ Êý Ãû         : Lcd1602_Delay1ms
* º¯Êý¹¦ÄÜ		   : ÑÓÊ±º¯Êý£¬ÑÓÊ±1ms
* Êä    Èë         : c
* Êä    ³ö         : ÎÞ
* Ëµ    Ãû         : ¸Ãº¯ÊýÊÇÔÚ12MHZ¾§ÕñÏÂ£¬12·ÖÆµµ¥Æ¬»úµÄÑÓÊ±¡£
*******************************************************************************/

void Lcd1602_Delay1ms(uint c)   //Îó²î 0us
{
    uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

/*******************************************************************************
* º¯ Êý Ãû         : LcdWriteCom
* º¯Êý¹¦ÄÜ		   : ÏòLCDÐ´ÈëÒ»¸ö×Ö½ÚµÄÃüÁî
* Êä    Èë         : com
* Êä    ³ö         : ÎÞ
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //µ±Ã»ÓÐ¶¨ÒåÕâ¸öLCD1602_4PINSÊ±
void LcdWriteCom(uchar com)	  //Ð´ÈëÃüÁî
{
	LCD1602_E = 0;     //Ê¹ÄÜ
	LCD1602_RS = 0;	   //Ñ¡Ôñ·¢ËÍÃüÁî
	LCD1602_RW = 0;	   //Ñ¡ÔñÐ´Èë
	
	LCD1602_DATAPINS = com;     //·ÅÈëÃüÁî
	Lcd1602_Delay1ms(1);		//µÈ´ýÊý¾ÝÎÈ¶¨

	LCD1602_E = 1;	          //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);	  //±£³ÖÊ±¼ä
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)	  //Ð´ÈëÃüÁî
{
	LCD1602_E = 0;	 //Ê¹ÄÜÇåÁã
	LCD1602_RS = 0;	 //Ñ¡ÔñÐ´ÈëÃüÁî
	LCD1602_RW = 0;	 //Ñ¡ÔñÐ´Èë

	LCD1602_DATAPINS = com;	//ÓÉÓÚ4Î»µÄ½ÓÏßÊÇ½Óµ½P0¿ÚµÄ¸ßËÄÎ»£¬ËùÒÔ´«ËÍ¸ßËÄÎ»²»ÓÃ¸Ä
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = com << 4; //·¢ËÍµÍËÄÎ»
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* º¯ Êý Ãû         : LcdWriteData
* º¯Êý¹¦ÄÜ		   : ÏòLCDÐ´ÈëÒ»¸ö×Ö½ÚµÄÊý¾Ý
* Êä    Èë         : dat
* Êä    ³ö         : ÎÞ
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(uchar dat)			//Ð´ÈëÊý¾Ý
{
	LCD1602_E = 0;	//Ê¹ÄÜÇåÁã
	LCD1602_RS = 1;	//Ñ¡ÔñÊäÈëÊý¾Ý
	LCD1602_RW = 0;	//Ñ¡ÔñÐ´Èë

	LCD1602_DATAPINS = dat; //Ð´ÈëÊý¾Ý
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);   //±£³ÖÊ±¼ä
	LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)			//Ð´ÈëÊý¾Ý
{
	LCD1602_E = 0;	  //Ê¹ÄÜÇåÁã
	LCD1602_RS = 1;	  //Ñ¡ÔñÐ´ÈëÊý¾Ý
	LCD1602_RW = 0;	  //Ñ¡ÔñÐ´Èë

	LCD1602_DATAPINS = dat;	//ÓÉÓÚ4Î»µÄ½ÓÏßÊÇ½Óµ½P0¿ÚµÄ¸ßËÄÎ»£¬ËùÒÔ´«ËÍ¸ßËÄÎ»²»ÓÃ¸Ä
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //Ð´ÈëµÍËÄÎ»
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  //Ð´ÈëÊ±Ðò
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif

/*******************************************************************************
* º¯ Êý Ãû       : LcdInit()
* º¯Êý¹¦ÄÜ		 : ³õÊ¼»¯LCDÆÁ
* Êä    Èë       : ÎÞ
* Êä    ³ö       : ÎÞ
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit()						  //LCD³õÊ¼»¯×Ó³ÌÐò
{
 	LcdWriteCom(0x38);  //¿ªÏÔÊ¾8Î»Êý¾Ý×ÜÏß£¬ÏÔÊ¾Á½ÐÐ£¬Ã¿¸ö×Ö·û5*7´óÐ¡
	LcdWriteCom(0x0e);  //¿ªÏÔÊ¾£¬»ÏÔÊ¾¹â±ê
	LcdWriteCom(0x06);  //Ð´Ò»¸öÖ¸Õë¼Ó1 £¬ÏÔÊ¾ÆÁ²»ÒÆ¶¯£¬Ð´ÈëÊý¾Ýºó¹â±êÏòÓÒÒÆ
	LcdWriteCom(0x01);  //ÇåÆÁ
	LcdWriteCom(0x80);  //ÉèÖÃÊý¾ÝÖ¸ÕëÆðµã,³õÊ¼ÏÔÊ¾Î»ÖÃ
}
#else
void LcdInit()						  //LCD³õÊ¼»¯×Ó³ÌÐò
{
	LcdWriteCom(0x32);	 //½«8Î»×ÜÏß×ªÎª4Î»×ÜÏß
	LcdWriteCom(0x28);	 //ÔÚËÄÎ»ÏßÏÂµÄ³õÊ¼»¯
	LcdWriteCom(0x0c);  //¿ªÏÔÊ¾²»ÏÔÊ¾¹â±ê
	LcdWriteCom(0x06);  //Ð´Ò»¸öÖ¸Õë¼Ó1
	LcdWriteCom(0x01);  //ÇåÆÁ
	LcdWriteCom(0x80);  //ÉèÖÃÊý¾ÝÖ¸ÕëÆðµã
}
#endif
