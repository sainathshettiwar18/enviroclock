#include "add2148.h"
extern volatile u8 interrupt;
extern volatile u16 screen;
extern volatile u8 alarm;
extern volatile u8 alarm_hour;
extern volatile u8 alarm_minute;
volatile u8 indexo;


void menu(void){
				CmdLCD(CLEAR_LCD);
				while(screen){
				while(screen==FIRST_MENU){
					indexo=1;
					first_menu();
				}
				while(screen==RTC_EDIT){
					indexo=1;
					rtc_edit();
					
				}
				while(screen==ALARM_EDIT){
					alarm_edit();
				}
				while(screen==RTC_HOUR){
					rtc_hour();
				}
				while(screen==RTC_MIN){
					rtc_min();
				}
				while(screen==RTC_SEC){
					rtc_sec();
				}
				while(screen==RTC_DATE){
					rtc_date();
				}
				while(screen==RTC_MONTH){
					rtc_month();
				}
				while(screen==RTC_YEAR){
					rtc_year();
				}
				while(screen==RTC_DAY){
					rtc_day();
				}
	}			
}


void first_menu(){
		volatile u8 key;
    u8 c = 1;
    while (indexo) {
        
        if (c) {
            c = 0;
            CmdLCD(CLEAR_LCD);

            if (indexo == 1) {
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("1.EDIT RTC INFO");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("2.SET ALARM");
            } else if (indexo == 2) {
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("2.SET ALARM");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("3.EXIT");
            }
        }

        key = KeyScan();

        switch (key) {
            case 'D':
                if (indexo == 1) {
                    indexo=2;
                    c = 1;
                } else {
                    CmdLCD(GOTO_LINE2_POS0 + 9);
                    StrLCD("(Limit)");
                    delay_ms(400);
                    CmdLCD(GOTO_LINE2_POS0 + 9);
                    StrLCD("       ");
                }
                break;

            case 'U':
                if (indexo == 2) {
                    indexo = 1;
                    c = 1;
                }
                break;

            case '1':
                if (indexo == 1) {
                    indexo = 0;
                    screen = RTC_EDIT;
                    CmdLCD(CLEAR_LCD);
                }
                break;

            case '2':
                indexo = 0;
                screen = ALARM_EDIT;
                CmdLCD(CLEAR_LCD);
                break;

            case '3':
                if (indexo == 2) {
                    screen = 0;
                    indexo = 0;
                    interrupt = 0;
                    CmdLCD(CLEAR_LCD);
                }
                break;
        }
    }
}

void rtc_edit(){
				volatile u8 key;
				u8 c = 1;
					while(indexo){
						if(c){
							CmdLCD(CLEAR_LCD);
							c=0;
							
							if(indexo==1){
								
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("1.HOUR");
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("2.MINUTES");
							}
							
							if(indexo==2){
								
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("3.SECONDS");
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("4.DAY");
							}
							if(indexo==3){
								
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("5.DAY OF MONTH");
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("6.MONTH");
							}
							if(indexo==4){
								
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("7.YEAR");
								CmdLCD(GOTO_LINE2_POS0);
								StrLCD("8.EXIT");
							}
							
						}
						key=KeyScan();
							switch(key){
							case 'D': if (indexo < 4) {
													indexo++;
													c = 1;
												}
												else {
													CmdLCD(GOTO_LINE2_POS0 + 9);
													StrLCD("(Limit)");
													delay_ms(400);
													CmdLCD(GOTO_LINE2_POS0 + 9);
													StrLCD("       ");
												}
												break;
																
							case 'U': if (indexo > 1) {
														indexo--;
														c = 1;
												} 
												else {
														CmdLCD(GOTO_LINE1_POS0 + 9);
														StrLCD("(Limit)");
														delay_ms(400);
														CmdLCD(GOTO_LINE1_POS0 + 9);
														StrLCD("       ");
												}
												break;
								
							case '1': if(indexo==1){
												indexo=0;
												screen=RTC_HOUR;
												}
												break;
							case '2': if(indexo==1){
												indexo=0;
												screen=RTC_MIN;
												}
												break;
							case '3': if(indexo==2){
												indexo=0;
												screen=RTC_SEC;
												}
												break;
							case '4': if(indexo==2){
												indexo=0;
												screen=RTC_DAY;
												}
												break;
							case '5': if(indexo==3){
												indexo=0;
												screen=RTC_DATE;
												}
												break;
							case '6': if(indexo==3){
												indexo=0;
												screen=RTC_MONTH;
												}
												break;
							case '7': if(indexo==4){
												indexo=0;
												screen=RTC_YEAR;
												}
												break;
							case '8': if(indexo==4){
												indexo=0;
												screen=FIRST_MENU;
												}
												break;
							
							case 'B': indexo=0;
												screen=FIRST_MENU;
												break;
					}
				}						
}



void alarm_edit() {
    volatile u8 key;
    u8 i = 0; 
    
    u8 hour = 0;
    u8 minute = 0;
    
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("HH:MM");
    CmdLCD(GOTO_LINE1_POS0);
    CmdLCD(DSP_ON_CUR_ON);

    while(1) {
        CmdLCD(GOTO_LINE1_POS0 + i);
        
        key = KeyScan();


        if (key >= '0' && key <= '9') {
            u8 val = key - 48;
						if(i<5){
            CharLCD(key);
						}

            switch (i) {
                case 0:if(val>2){
												CmdLCD(GOTO_LINE2_POS0);
												StrLCD("set b/w 0-23");
												delay_ms(400);
												CmdLCD(GOTO_LINE2_POS0);
												StrLCD("                ");
                        hour = 0;
                        i = 0;
                        CmdLCD(GOTO_LINE1_POS0);
												StrLCD("H");
												}
											 else{
												hour = val * 10;
												i = 1;
											 }
                    break;
                case 1:
                    hour += val;
                    if (hour > 23) {
                        CmdLCD(GOTO_LINE2_POS0);
												StrLCD("set b/w 0-23");
												delay_ms(400);
												CmdLCD(GOTO_LINE2_POS0);
												StrLCD("                ");
                        hour = hour-(hour%10);
                        i = 1;
                        CmdLCD(GOTO_LINE1_POS0+1);
												StrLCD("H");
                    } else {
                        i = 3;
                    }
                    break;
                case 3:
										if(val>5){
												CmdLCD(GOTO_LINE2_POS0);
												StrLCD("set b/w 0-59");
												delay_ms(400);
												CmdLCD(GOTO_LINE2_POS0);
												StrLCD("                ");
                        minute = 0;
                        i = 3;
                        CmdLCD(GOTO_LINE1_POS0+3); 
												StrLCD("M");
												}
										else {
												minute = val * 10;
												i = 4;
										}
                    break;
                case 4:
                    minute += val;
                    i = 5;
                    break;
            }
        }
        else if (key == 'B') { 
            switch (i) {
                case 0: screen=FIRST_MENU;
						CmdLCD(DSP_ON_CUR_OFF);
						
												return;
                case 1:
                    i = 0;
                    CmdLCD(GOTO_LINE1_POS0);
										CharLCD('H');
                    hour = 0;
                    break;
                case 3:
                    i = 1;
                    CmdLCD(GOTO_LINE1_POS0 + 1);
										CharLCD('H');
										hour=hour-(hour%10);
                    break;
                case 4:
                    i = 3;
                    CmdLCD(GOTO_LINE1_POS0 + 3);
										CharLCD('M');
										minute=0;
                    break;
								case 5:
										i = 4;
                    CmdLCD(GOTO_LINE1_POS0 + 4);
										CharLCD('M');
                    minute =minute- (minute%10);
										break;
            }
        }
        else if (i==5&&key == 'E') {
						alarm=1;
            alarm_hour = hour;
            alarm_minute = minute;
            CmdLCD(DSP_ON_CUR_OFF);
						CmdLCD(CLEAR_LCD);
						StrLCD("Alarm is set");
						delay_ms(400);
            screen = FIRST_MENU;
            return;
        }
    }
}

void rtc_hour(){
 volatile u8 key;
    u8 i = 0; 
    
    u8 hour = 0;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("SET HOUR:");
    CmdLCD(GOTO_LINE2_POS0);
		StrLCD("HH");
		CmdLCD(GOTO_LINE2_POS0);
    CmdLCD(DSP_ON_CUR_ON);
	
		while(1){
			CmdLCD(GOTO_LINE2_POS0+i);//bug happened here cursor
			key=KeyScan();
			if(key>='0' && key<='9'){
				u8 val=key-48;
				if(i<2){
					CharLCD(key);
				}
				switch(i){
					case 0: if(val<=2){
										hour=val*10;
										i=1;
									}
									else{
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-23");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=0;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('H');
									}
									break;
					case 1:
                    hour += val;
                    if (hour > 23) {
                    CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-23");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=1;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('H');
										hour = hour-(hour%10);
                    } else {
                        i = 2;
                    }
                    break;
						
				}
			}
			
			else if(key=='B'){
				switch (i) {
                case 0: screen=RTC_EDIT;
						CmdLCD(DSP_ON_CUR_OFF);
												return;
                case 1:
                    i = 0;
                    CmdLCD(GOTO_LINE2_POS0);
										CharLCD('H');
                    hour = 0;
                    break;
								case 2:
                    i = 1;
                    CmdLCD(GOTO_LINE2_POS0 + 1);
										CharLCD('H');
										hour=hour-(hour%10);
                    break;
							}
				
			}
			else if(key=='E' && i==2){
						
						CCR = RESET_RTC;
            HOUR = hour;
						#ifndef __LPC2148__
						CCR=ENABLE_RTC;
						#else
						CCR = CMOS|ENABLE_RTC;
						#endif
            CmdLCD(DSP_ON_CUR_OFF);
						CmdLCD(CLEAR_LCD);
						StrLCD("Hour is set");
						delay_ms(400);
            screen = RTC_EDIT;
            return;
			}
			
		}
	
}


void rtc_min(){
 volatile u8 key;
    u8 i = 0; 
    
    u8 minutes = 0;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("SET MIN:");
    CmdLCD(GOTO_LINE2_POS0);
		StrLCD("MM");
		CmdLCD(GOTO_LINE2_POS0);
    CmdLCD(DSP_ON_CUR_ON);
	
		while(1){
			CmdLCD(GOTO_LINE2_POS0+i);
			key=KeyScan();
			if(key>='0' && key<='9'){
				u8 val=key-48;
				if(i<2){
					CharLCD(key);
				}
				switch(i){
					case 0: if(val<=5){
										minutes=val*10;
										i=1;
									}
									else{
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-59");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=0;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('M');
									}
									break;
					case 1:
                    minutes+= val;
										i = 2;
                    break;
						
				}
			}
			
			else if(key=='B'){
				switch (i) {
                case 0: screen=RTC_EDIT;
						CmdLCD(DSP_ON_CUR_OFF);
												return;
                case 1:
                    i = 0;
                    CmdLCD(GOTO_LINE2_POS0);
										CharLCD('M');
                    minutes = 0;
                    break;
								case 2:
                    i = 1;
                    CmdLCD(GOTO_LINE2_POS0 + 1);
										CharLCD('M');
										minutes=minutes-(minutes%10);
                    break;
							}
				
			}
			else if(key=='E' && i==2){
						
						CCR = RESET_RTC;
            MIN = minutes;
						#ifndef __LPC2148__
						CCR=ENABLE_RTC;
						#else
						CCR = CMOS|ENABLE_RTC;
						#endif
            CmdLCD(DSP_ON_CUR_OFF);
						CmdLCD(CLEAR_LCD);
						StrLCD("Minutes is set");
						delay_ms(400);
            			screen = RTC_EDIT;
            			return;
			}
			
		}
	
}

void rtc_sec(){
 volatile u8 key;
    u8 i = 0; 
    
    u8 seconds = 0;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("SET SEC:");
    CmdLCD(GOTO_LINE2_POS0);
		StrLCD("SS");
		CmdLCD(GOTO_LINE2_POS0);
    CmdLCD(DSP_ON_CUR_ON);
	
		while(1){
			CmdLCD(GOTO_LINE2_POS0+i);
			key=KeyScan();
			if(key>='0' && key<='9'){
				u8 val=key-48;
				if(i<2){
					CharLCD(key);
				}
				switch(i){
					case 0: if(val<=5){
										seconds=val*10;
										i=1;
									}
									else{
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-59");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=0;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('S');
									}
									break;
					case 1:
                    seconds+= val;
										i = 2;
                    break;
						
				}
			}
			
			else if(key=='B'){
				switch (i) {
                case 0: screen=RTC_EDIT;
						CmdLCD(DSP_ON_CUR_OFF);
					
												return;
                case 1:
                    i = 0;
                    CmdLCD(GOTO_LINE2_POS0);
										CharLCD('S');
                    seconds = 0;
                    break;
								case 2:
                    i = 1;
                    CmdLCD(GOTO_LINE2_POS0 + 1);
										CharLCD('S');
										seconds=seconds-(seconds%10);
                    break;
							}
				
			}
			else if(key=='E' && i==2){
						
						CCR = RESET_RTC;
            SEC = seconds;
						#ifndef __LPC2148__
						CCR=ENABLE_RTC;
						#else
						CCR = CMOS|ENABLE_RTC;
						#endif
            CmdLCD(DSP_ON_CUR_OFF);
						CmdLCD(CLEAR_LCD);
						StrLCD("SECONDS is set");
						delay_ms(400);
            screen = RTC_EDIT;
			
            return;
			}
			
		}
	
}
u8 days_31(){
	if(MONTH==1||MONTH==3||MONTH==5||MONTH==7||MONTH==8||MONTH==10||MONTH==12){
		return 1;
	}
	return 0;
}
u8 days_30(){
	if(MONTH==4||MONTH==6||MONTH==9||MONTH==11){
		return 1;
	}
	return 0;
}
u8 days_28(){
	if(MONTH==2){
		return 1;
	}
	return 0;
}

void rtc_date(){
 volatile u8 key;
    u8 i = 0; 
    
    u8 date = 0;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("SET DATE:");
    CmdLCD(GOTO_LINE2_POS0);
		StrLCD("DD");
		CmdLCD(GOTO_LINE2_POS0);
    CmdLCD(DSP_ON_CUR_ON);
	
		while(1){
			CmdLCD(GOTO_LINE2_POS0+i);//bug happened here cursor
			key=KeyScan();
			if(key>='0' && key<='9'){
				u8 val=key-48;
				if(i<2){
					CharLCD(key);
				}
				switch(i){
					case 0: while(days_31()){
									if(val<=3){
										date=val*10;
										i=1;
									}
									else{
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-31");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=0;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('D');
									}
									break;
								}
								while(days_30()){
									if(val<=3){
										date=val*10;
										i=1;
									}
									else{
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-30");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=0;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('D');
									}
									break;
								}
								while(days_28()){
									if(val<=2){
										date=val*10;
										i=1;
									}
									else{
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-28");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=0;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('D');
									}
									break;
								}
								break;
								
					case 1:
                    date += val;
                    while(days_31()){
											if (date > 31) {
                    CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-31");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=1;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('D');
										date = date-(date%10);
                    } else {
                        i = 2;
                    }
										break;
								}
								while(days_30()){
									if (date > 30) {
                    CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-31");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=1;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('D');
										date = date-(date%10);
                    } else {
                        i = 2;
                    }
										break;
								}
								while(days_28()){
									if (date > 28) {
                    CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-31");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=1;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('D');
										date = date-(date%10);
                    } else {
                        i = 2;
                    }
										break;
								}
								
								
								break;
						
				}
			}
			
			else if(key=='B'){
				switch (i) {
                case 0: screen=RTC_EDIT;
												CmdLCD(DSP_ON_CUR_OFF);
												return;
                case 1:
                    i = 0;
                    CmdLCD(GOTO_LINE2_POS0);
										CharLCD('D');
                    date = 0;
                    break;
								case 2:
                    i = 1;
                    CmdLCD(GOTO_LINE2_POS0 + 1);
										CharLCD('D');
										date=date-(date%10);
                    break;
							}
				
			}
			else if(key=='E' && i==2){
						
						CCR = RESET_RTC;
            DOM = date;
						#ifndef __LPC2148__
						CCR=ENABLE_RTC;
						#else
						CCR = CMOS|ENABLE_RTC;
						#endif
            CmdLCD(DSP_ON_CUR_OFF);
						CmdLCD(CLEAR_LCD);
						StrLCD("Date is set");
						delay_ms(400);
            screen = RTC_EDIT;
            return;
			}
			
		}
	
}



void rtc_month(){
 volatile u8 key;
    u8 i = 0; 
    
    u8 month = 0;
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("SET MONTH:");
    CmdLCD(GOTO_LINE2_POS0);
		StrLCD("MM");
		CmdLCD(GOTO_LINE2_POS0);
    CmdLCD(DSP_ON_CUR_ON);
	
		while(1){
			CmdLCD(GOTO_LINE2_POS0+i);//bug happened here cursor
			key=KeyScan();
			if(key>='0' && key<='9'){
				u8 val=key-48;
				if(i<2){
					CharLCD(key);
				}
				switch(i){
					case 0: if(val<=1){
										month=val*10;
										i=1;
									}
									else{
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-12");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=0;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('M');
									}
									break;
					case 1:
                    month += val;
                    if (month > 12) {
                    CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD(" 0-12");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("          ");
										i=1;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('M');
										month = month-(month%10);
                    } else {
                        i = 2;
                    }
                    break;
						
				}
			}
			
			else if(key=='B'){
				switch (i) {
                case 0: screen=RTC_EDIT;
						CmdLCD(DSP_ON_CUR_OFF);
												return;
                case 1:
                    i = 0;
                    CmdLCD(GOTO_LINE2_POS0);
										CharLCD('M');
                    month = 0;
                    break;
								case 2:
                    i = 1;
                    CmdLCD(GOTO_LINE2_POS0 + 1);
										CharLCD('M');
										month=month-(month%10);
                    break;
							}
				
			}
			else if(key=='E' && i==2){
						
						CCR = RESET_RTC;
            MONTH = month;
						#ifndef __LPC2148__
						CCR=ENABLE_RTC;
						#else
						CCR = CMOS|ENABLE_RTC;
						#endif
            CmdLCD(DSP_ON_CUR_OFF);
						CmdLCD(CLEAR_LCD);
						StrLCD("MONTH is set");
						delay_ms(400);
            screen = RTC_EDIT;
            return;
			}
			
		}
	
}
void rtc_year() {
    volatile u8 key;
    u8 i = 0; 
    
    u16 year = 0;
    
    
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("SET YEAR:");
    CmdLCD(GOTO_LINE2_POS0);
		StrLCD("YYYY");
		CmdLCD(GOTO_LINE2_POS0);
    CmdLCD(DSP_ON_CUR_ON);

    while(1) {
        CmdLCD(GOTO_LINE2_POS0 + i);
        
        key = KeyScan();


        if (key >= '0' && key <= '9') {
            u8 val = key - 48;
						if(i<4){
            CharLCD(key);
						}

            switch (i) {
                case 0:if(val<=4){
										year=val*1000;
										i=1;
									}
									else{
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("0-4095");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("      ");
										i=0;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('Y');
									}
									break;
									
                case 1:if(year==4000 && val!=0){
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("0-4095");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("      ");
										i=1;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('Y');
									}
									else{
										year=year+(val*100);
										i=2;
									}
									
								   break;
                case 2:
										year=year+(val*10);
										i=3;
								   	break;
									
                case 3:
                    year += val;
                    if (year > 4095) {
                    CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("0-4095");
										delay_ms(400);
										CmdLCD(GOTO_LINE1_POS0+10);
										StrLCD("      ");
										i=3;
										CmdLCD(GOTO_LINE2_POS0+i);
										CharLCD('Y');
										year = year-(year%10);
                    } else {
                        i = 4;
                    }
                    break;
            }
        }
        else if (key == 'B') { 
            switch (i) {
                case 0: screen=FIRST_MENU;
												CmdLCD(DSP_ON_CUR_OFF);
												return;
                case 1:
                    i = 0;
                    CmdLCD(GOTO_LINE2_POS0);
										CharLCD('Y');
                    year = 0;
                    break;
                case 2:
                    i = 1;
                    CmdLCD(GOTO_LINE2_POS0 + 1);
										CharLCD('Y');
										year=year-(year%1000);
                    break;
                case 3:
                    i = 2;
                    CmdLCD(GOTO_LINE2_POS0 + 2);
										CharLCD('Y');
										year=year-(year%100);
                    break;
								case 4:
										i = 3;
                    CmdLCD(GOTO_LINE2_POS0 + 3);
										CharLCD('Y');
                    year=year-(year%10);
										break;
            }
        }
        else if (i==4&&key == 'E') {
						CCR = RESET_RTC;
            YEAR = year;
						#ifndef __LPC2148__
						CCR=ENABLE_RTC;
						#else
						CCR = CMOS|ENABLE_RTC;
						#endif
            CmdLCD(DSP_ON_CUR_OFF);
						CmdLCD(CLEAR_LCD);
						StrLCD("YEAR is set");
						delay_ms(400);
            screen = RTC_EDIT;
            return;
        }
    }
}


void rtc_day(){
 volatile s8 key,val=-1;
    u8 i = 0; 
    
u8 week1[][4]= {"SUN","MON","TUE","WED","THU","FRI","SAT"};
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
		StrLCD("SET DAY:");
    CmdLCD(GOTO_LINE2_POS0);
		StrLCD("XXX");
		CmdLCD(GOTO_LINE2_POS0);
    CmdLCD(DSP_ON_CUR_ON);
	
		while(1){
			CmdLCD(GOTO_LINE2_POS0+i);
			key=KeyScan();
			if(key>='0' && key<='6' && i==0){
				 val=key-48;
				if(i<3){
					StrLCD(week1[val]);
				}
				i=3;
			}
			
			else if(key=='B'){
				switch (i) {
                case 0: screen=RTC_EDIT;
												CmdLCD(DSP_ON_CUR_OFF);
												return;
								case 3:
                    i = 0;
                    CmdLCD(GOTO_LINE2_POS0);
										StrLCD("XXX");
                    break;
							}
				
			}
			else if(key=='E' && i==3){
						
						CCR = RESET_RTC;
            DOW= val;
						#ifndef __LPC2148__
						CCR=ENABLE_RTC;
						#else
						CCR = CMOS|ENABLE_RTC;
						#endif
            CmdLCD(DSP_ON_CUR_OFF);
						CmdLCD(CLEAR_LCD);
						StrLCD("DAY is set");
						delay_ms(400);
            screen = RTC_EDIT;
			
            return;
			}
			
		}
	
}
