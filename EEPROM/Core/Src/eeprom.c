/* #include "eeprom.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;



uint16_t device = EEPROM_DEV;
uint8_t str[100];




void eeprom_Write (uint16_t addr, uint8_t data)
{
	 HAL_I2C_Mem_Write(&hi2c1, device, addr,I2C_MEMADD_SIZE_16BIT, &data, 1, 100);
}

void eeprom_Read (uint16_t addr, uint8_t buf)
{

	HAL_I2C_Mem_Read(&hi2c1, device, addr,I2C_MEMADD_SIZE_16BIT, &buf, 10, 100);


	int width =	sprintf(str, "0x%X\r\n", buf);
		HAL_UART_Transmit(&huart2, str, width, 0xFFFF);
}

*/






