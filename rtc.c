#include "add2148.h"
#include "rtc_defines.h"

void init_rtc(){
	
	CCR = RESET_RTC;
#ifndef __LPC2148__
PREINT = PREINT_VAL;
PREFRAC = PREFRAC_VAL;
	SEC=59;//
	MIN=59;//
	HOUR=00;//
	DOM=24;//
	DOY=366;//
	DOW=0;
	MONTH=10;//
	YEAR=2025;//4095
CCR=ENABLE_RTC;
#else
	CCR = CMOS|ENABLE_RTC;
	
#endif
}
