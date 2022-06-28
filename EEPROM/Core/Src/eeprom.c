 #include "eeprom.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;


uint8_t eepromBuf[100];
uint16_t device = EEPROM_DEV;
uint8_t str[100];
uint8_t test1 = 0x11;
uint8_t test2 = 0x22;
uint8_t test3 = 0x33;
uint16_t i = 0;


void eeprom_Write (uint16_t addr, uint8_t data)
{
	 HAL_I2C_Mem_Write(&hi2c1, device, addr,I2C_MEMADD_SIZE_16BIT, &data, 1, 100);
}

void eeprom_Read (uint16_t addr)
{

	HAL_I2C_Mem_Read(&hi2c1, device, addr,I2C_MEMADD_SIZE_16BIT, eepromBuf, 10, 100);

uint8_t val = eepromBuf[0];
	int width =	sprintf(str, "0x%X\r\n", val);
		HAL_UART_Transmit(&huart2, str, width, 0xFFFF);
}



void WriteArray()
{
	if(i < 9)
	{
		eeprom_Write(i, test1);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, test2);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, test3);
		i = i+1;
		HAL_Delay(10);
	}
	else
	{
		i = 0;
	}
}

void readMemory()
{
	uint16_t memCount = 0;
	if (i > 2)
	{

		memCount = i - 2;
		eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 1;
		eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i;
		eeprom_Read(memCount);
	}

	if (i < 3)
	{
		memCount = 9;
		eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = 10;
		eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = 11;
		eeprom_Read(memCount);
	}
	int width =	sprintf(str, "memcount = %d i = %d\r\n", memCount, i);
		HAL_UART_Transmit(&huart2, str, width, 100);
}



