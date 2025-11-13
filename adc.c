#include "add2148.h"

void Init_ADC(void)
{
	//cfg ADCR sfr
	
#ifndef __LPC2148__
ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
CfgPortPinFunc(0,27,1);
#else
AD0CR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
CfgPortPinFunc(0,28,2);
#endif
	
	//cfg p0.27 pin as Analog Input pin0 (AIN0)

}

void Read_ADC(u32 chNo,u32 *adcDVal,f32 *eAR)
{
	
#ifndef __LPC2148__
//clear any previous channel selection
	ADCR&=0xFFFFFF00;
	//update req channel select,
	//start analog samping & conversion
	ADCR|=1<<chNo|1<<ADC_START_BIT;
	delay_us(3);
	while(((ADDR>>DONE_BIT)&1)==0);
	ADCR&=~(1<<ADC_START_BIT);
	*adcDVal=(ADDR>>RESULT_BITS)&1023;
	*eAR = (*adcDVal * (3.3/1023));
#else
//clear any previous channel selection
	AD0CR&=0xFFFFFF00;
	//update req channel select,
	//start analog samping & conversion
	AD0CR|=1<<chNo|1<<ADC_START_BIT;
	delay_us(3);
	while(((AD0GDR >>DONE_BIT)&1)==0);
	AD0CR&=~(1<<ADC_START_BIT);
	*adcDVal=(AD0GDR >>RESULT_BITS)&1023;
	*eAR = (*adcDVal * (3.3/1023));
#endif

}
