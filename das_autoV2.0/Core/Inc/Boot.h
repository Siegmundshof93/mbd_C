#ifndef BOOT_H_

#define BOOT_H_

//------------------------------------------------

#include "stm32l0xx_hal.h"
#include <string.h>
#include "NRF24.h"

//------------------------------------------------

#define FULL_SPEED 1000
#define LOW_SPEED 500

#define LEFT_FORWARD GPIO_PIN_10
#define LEFT_BACKWARD GPIO_PIN_12
#define RIGHT_FORWARD GPIO_PIN_11
#define RIGHT_BACKWARD GPIO_PIN_9
#define FIRST_MOTOR_LOW __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, LOW_SPEED);
#define SECOND_MOTOR_LOW __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, LOW_SPEED);
#define FIRST_MOTOR_FAST __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, FULL_SPEED);
#define SECOND_MOTOR_FAST __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, FULL_SPEED);
#define FIRST_MOTOR_STOP __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
#define SECOND_MOTOR_STOP __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
#define GO 1
#define STOP 0

void MotorDriver(void);
void Hbridge (uint16_t, int, uint16_t, int);
void Boot(void);

#endif /* BOOT_H_ */
