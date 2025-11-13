
#include "add2148.h"

volatile u8 interrupt;
volatile u8 alarm;
volatile u8 stop_alarm;
volatile u8 alarm_hour;
volatile u8 alarm_minute;
volatile u16 screen;
 u32 adcDVal;
 f32 eAR; 
volatile u32 temp;

u8 cgramLUT[32]=
{ 0x1f,0x15,0x15,0x17,0x11,0x11,0x1f,0x00,
	0x1b,0x11,0x0e,0x11,0x15,0x11,0x0e,0x00,
	0x04,0x0e,0x1f,0x11,0x15,0x11,0x1f,0x00,
	0x11,0x00,0x1f,0x11,0x15,0x11,0x1f,0x00
};

u8 week1[][4]= {"SUN","MON","TUE","WED","THU","FRI","SAT"};





main()
{
	IODIR1|=(1<<BUZZER);
	Init_ADC();
	ext_int();
	init_rtc();
	Init_KPM();
	Init_LCD();
	CmdLCD(CLEAR_LCD);
	
		while(1){
			
			while(interrupt){
				screen=FIRST_MENU;
				menu();
			}
			
			
			
			CmdLCD(GOTO_LINE1_POS0);
			CmdLCD(DSP_ON_CUR_OFF);
			CharLCD((HOUR/10)+48);
			CharLCD((HOUR%10)+48);
			CharLCD(':');
			CharLCD((MIN/10)+48);
			CharLCD((MIN%10)+48);
			CharLCD(':');
			CharLCD((SEC/10)+48);
			CharLCD((SEC%10)+48);
			CmdLCD(GOTO_LINE1_POS0+10);
			StrLCD(week1[DOW]);
			if(alarm){
				BuildCGRAM(cgramLUT,8);
				CmdLCD(GOTO_LINE1_POS0+14);
				CharLCD(0);
				
				
				if(HOUR==alarm_hour && MIN==alarm_minute){
					IOSET1=1<<BUZZER;
					}
				
				if(HOUR==alarm_hour && MIN==alarm_minute && SEC==30){
					stop_alarm=0;
					IOCLR1=1<<BUZZER;
					alarm--;
					CmdLCD(GOTO_LINE1_POS0+14);
					CharLCD(' ');
				}
				else if(HOUR==alarm_hour && MIN==alarm_minute && SEC<30){
					if(READNIBBLE(IOPIN1,COLs_4)<15){
					stop_alarm=1;
					}
					
					if(stop_alarm){
					
					IOCLR1=1<<BUZZER;
					alarm--;
					CmdLCD(GOTO_LINE1_POS0+14);
					CharLCD(' ');
					stop_alarm=0;
				}
			}
			}
			CmdLCD(GOTO_LINE2_POS0);
			CharLCD((DOM/10)+48);
			CharLCD((DOM%10)+48);
			CharLCD('/');
			CharLCD((MONTH/10)+48);
			CharLCD((MONTH%10)+48);
			CharLCD('/');
			CharLCD(((YEAR%100)/10)+48);
			CharLCD((YEAR%10)+48);
			CmdLCD(GOTO_LINE2_POS0+10);
			#ifndef __LPC2148__
			Read_ADC(0, &adcDVal, &eAR);
			#else
			Read_ADC(1, &adcDVal, &eAR);
			#endif
			
			temp = eAR * 100;
			CharLCD('T');
			CharLCD(':');
			U32LCD(temp);
			CharLCD(0xDF);
			CharLCD('C');
			
		}
}
