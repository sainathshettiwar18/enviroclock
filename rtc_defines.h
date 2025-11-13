void init_rtc(void);

#define RESET_RTC (1<<1)
#define CMOS (1<<4)
#define ENABLE_RTC (1<<0)
#define PCLK 15000000
#define FRTC 32768
#define PREINT_VAL (int)(PCLK/FRTC)-1
#define PREFRAC_VAL ((PCLK)-((PREINT_VAL+1)*FRTC))
