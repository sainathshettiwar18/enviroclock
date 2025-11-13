#include "types.h"
#include <LPC21xx.h>
#include "pin_function_defines.h"
#include "pin_connect_block.h"
#define EINT0_VIC_CHN0 14
void eint0_isr(void) __irq;
extern volatile s16 interrupt;
void ext_int(void)
{
	
  CfgPortPinFunc(0,1,3);	
	VICIntEnable = 1<<EINT0_VIC_CHN0;
	VICVectCntl0 = (1<<5)|EINT0_VIC_CHN0;
	VICVectAddr0 = (u32 )eint0_isr;
	
	EXTMODE = 1<<0;
	IODIR0|=(1<<2);
}	

void eint0_isr(void) __irq
{
	IOPIN0^=(1<<2);
	EXTINT=1<<0;
	interrupt=1;
	VICVectAddr=0;
}
