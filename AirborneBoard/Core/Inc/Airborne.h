#ifndef AIRBORNE_H_
#define AIRBORNE_H_

#include "main.h"






void BlueBlink (void);
void WriteMemory(uint16_t);
void LoRaSend (uint16_t);

//------------------------------------------------

#define FULL_SPEED 1000
#define LOW_SPEED 500

#define LEFT_FORWARD GPIO_PIN_12
#define LEFT_BACKWARD GPIO_PIN_8
#define RIGHT_FORWARD GPIO_PIN_11
#define RIGHT_BACKWARD GPIO_PIN_1
#define FIRST_MOTOR_LOW __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, LOW_SPEED);
#define SECOND_MOTOR_LOW __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, LOW_SPEED);
#define FIRST_MOTOR_FAST __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, FULL_SPEED);
#define SECOND_MOTOR_FAST __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, FULL_SPEED);
#define FIRST_MOTOR_STOP __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
#define SECOND_MOTOR_STOP __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
#define GO 1
#define STOP 0

#define RIGHT_DIRECTION 0x01
#define LEFT_DIRECTION 0x02
#define FORWARD_DIRECTION 0x03
#define BACKWARD_DIRECTION 0x04

void MotorDriver(void);
void Hbridge (uint16_t, int, uint16_t, int);
void Boot(void);









#endif
