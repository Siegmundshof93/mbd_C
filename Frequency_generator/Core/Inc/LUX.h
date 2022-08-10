#ifndef __LUX_H

#define __LUX_H

#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <string.h>

#define ADDR_LUX 0x23 << 1;
#define TAKE_MEASUREMENT 0x10;

void SunSensor(void);

#endif
