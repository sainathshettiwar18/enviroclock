//#define __LPC2148__


#ifndef __LPC2148__
#include <lpc21xx.h>
#else
#include <lpc214x.h>
#endif
#include "defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#include "interrupt.h"
#include "types.h"
#include "rtc_defines.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "menu.h"
#include "adc_defines.h"
#include "adc.h"
#include "pin_connect_block.h"
#define BUZZER 24


