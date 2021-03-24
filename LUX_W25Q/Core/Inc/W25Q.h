#ifndef __W25Q_H

#define __W25Q_H

#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <string.h>

#define    W25_ENABLE_RESET  0x66
#define    W25_RESET  0x99
#define    W25_READ  0x03
#define    W25_GET_JEDEC_ID  0x9f
#define    W25_FAST_READ  0x0B

#define cs_set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET)
#define cs_reset() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET)

void SPI1_Send (uint8_t *dt, uint16_t cnt);
void SPI1_Recv (uint8_t *dt, uint16_t cnt);
void W25_Reset (void);
void W25_Read_Data(uint32_t addr, uint8_t* data, uint32_t sz);
uint32_t W25_Read_ID(void);
void W25_Read_Page(uint8_t* data, uint32_t page_addr, uint32_t offset, uint32_t sz);
void Write_En(void);
void W25_Display (void);
void Write_Flash(uint16_t,uint32_t);
void Erase(void);
void W25_Ini(void);


#endif
