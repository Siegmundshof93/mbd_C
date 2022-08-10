#ifndef __PCF8563

#define __PCF8563

#include "main.h"
#include "string.h"
#include "stdio.h"

#define PCF8563_ADDRESS              	(0x51<<1)
#define PCF8563_REG_CLKOUT    			0x0D
#define PCF8563_CLKOUT_CONTROL_FD0				0
#define PCF8563_CONTROL1_STOP		5
#define PCF8563_REG_CONTROL_STATUS2     0x01
#define PCF8563_REG_CONTROL_STATUS1     0x00

void setTime(void);
void set_time_InnerSTM_rtc(void);
void get_time_InnerSTM_rtc(void);
#endif
