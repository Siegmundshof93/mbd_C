#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED


#include <string.h>
#include <stdbool.h>
#include "stm32l0xx_hal.h"

#define FALSE 0
#define TRUE 1


void delay(uint16_t time);

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

void HCSR04_Read (void);

void backwords(void);







#endif
