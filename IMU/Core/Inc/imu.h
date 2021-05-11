#ifndef IMU_H_

#define IMU_H_

#include <stdio.h>
#include <string.h>
#include "stm32l4xx_hal.h"


#define WHO_AM_I 0x0F
#define DEV_ADDR 0x6A
#define CTRL3_C 0x12
#define IF_INC 0x04
#define BDU 0x40
#define CTRL1_XL 0x10
#define CTRL2_G 0x11
#define HZ140 0x40
#define HZOFF 0x00
//-----------------------------------
#define X_L 0x28
#define X_H 0x29
#define Y_L 0x2A
#define Y_H 0x2B
#define Z_L 0x2C
#define Z_H 0x2D
//-----------------------------------
#define GYRO_X_L 0x22
#define GYRO_X_H 0x23
#define GYRO_Y_L 0x24
#define GYRO_Y_H 0x25
#define GYRO_Z_L 0x26
#define GYRO_Z_H 0x27
//-----------------------------------
#define LED_TOGGLE HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)
#define TWOS_COMPLEMENT 0x7FFF

void Imu_init(void);
uint8_t i2c_read (uint8_t);
void i2c_write (uint8_t, uint8_t);
void AccelRead(void);
void GyroRead(void);
void AccelGyroRead(void);
void Boot(void);


#endif
