/*
*********************************************************************************************************
*                                         OTHER FUNCTIONS
*                               You can define any functions that you need
*                        
*                                          
*
* File : function.c
* By   :  Junmin Zheng (zhengjunm@263.net)
*********************************************************************************************************
*/

#include "..\mainfile\includes.h"
#include "os_kcdef.h"

#define interrupt
#define far	xdata



data INT16U TickCount;

void UserTickTimer(void) KCREENTRANT
{
	TickCount++;
}

void EnablePrintf(unsigned char Crystal,unsigned int BaudRate )
{
  unsigned long temparory=0;
  temparory=Crystal*1000000/BaudRate;
  temparory=temparory/(32*12);
  temparory=256-temparory;
 #ifndef MONITOR51
    SCON  = 0x50;		              /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TMOD |= 0x20;                     /* TMOD: timer 1, mode 2, 8-bit reload        */
    TH1   = (unsigned char)temparory; /* TH1:  load value*/
    TR1   = 1;                        /* TR1:  timer 1 run                          */
    TI    = 1;                        /* TI:   set TI to send first char of UART    */
#endif	
   P1 ^= 0x01; /* Toggle P1.0 each time we print */
}


void TimerInitiate(unsigned char Crystal,unsigned char Frequence)
{
    unsigned long temporary=0;
    temporary=1000000/(12*Frequence);
	temporary=65535-Crystal*temporary;
    TMOD=(TMOD & 0XF0) | 0X01;	/* Timer 0 working in MODE 1 */
	TL0=(unsigned char )temporary;				
	TH0=(unsigned char )(temporary>>8);
	TR0=1;
    ET0=1;
}


