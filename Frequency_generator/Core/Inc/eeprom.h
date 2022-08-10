

#ifndef __EEPROM

#define __EEPROM

#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <string.h>

#define EEPROM_DEV 0x50 << 1

void eeprom_Write (uint16_t, uint8_t);
uint8_t eeprom_Read (uint16_t);
void WriteArray(void);
void readMemory(void);

#endif


