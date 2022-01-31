#include "Boot.h"


uint8_t temp_reg = 0x00;
uint16_t val1;
uint16_t val2;
 float temp_C1;
 float temp_C2;
 uint8_t buf1[12];
 uint8_t buf2[12];
 uint8_t str1[12];
 uint8_t str2[12];


 extern I2C_HandleTypeDef hi2c1;
 extern I2C_HandleTypeDef hi2c2;
 extern UART_HandleTypeDef huart2;

void Boot(void)
{
	uint8_t str[100] = "--------------------------- \r\n";
	uint8_t addr_1 = 0x48 << 1;
	uint8_t addr_2 = 0x4F << 1;
	uint8_t addr_3 = 0x4C << 1;
	uint8_t addr_4 = 0x49 << 1;
	uint8_t addr_5 = 0x4B << 1;
	uint8_t addr_6 = 0x4E << 1;
	uint8_t addr_7 = 0x4D << 1;
	uint8_t addr_8 = 0x4A << 1;
	buf1[0] = temp_reg;
	buf2[0] = temp_reg;


	while(1)
	{

		i2c1(addr_1);
		i2c1(addr_2);
		i2c1(addr_3);
		i2c1(addr_4);
		i2c1(addr_5);
		i2c1(addr_6);
		i2c1(addr_7);
		i2c1(addr_8);
HAL_UART_Transmit(&huart2, str, sizeof(str), 100);
		i2c2(addr_1);
		i2c2(addr_2);
		i2c2(addr_3);
		i2c2(addr_4);
		i2c2(addr_5);
		i2c2(addr_6);
		i2c2(addr_7);
		i2c2(addr_8);
HAL_UART_Transmit(&huart2, str, sizeof(str), 100);

		HAL_Delay(5000);

	}
}

void i2c1 (uint8_t addr)
{
HAL_StatusTypeDef ret;

buf1[0] = temp_reg;
ret = HAL_I2C_Master_Transmit(&hi2c1, addr, buf1, 1, HAL_MAX_DELAY);
if (ret != HAL_OK) {
	strcpy((char*)buf1,"Error Tx\r\n");
} else {
	ret = HAL_I2C_Master_Receive(&hi2c1, addr, buf1, 2, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		strcpy((char*)buf1,"Error Rx\r\n");
	} else {
		val1 = ((int16_t)buf1[0] << 3) | (buf1[1] >> 5);
		temp_C1 = val1 * 0.125;
		temp_C1 *= 100;
		sprintf((char*)buf1, "I2C1 = %u.%2u C \r\n",
				((unsigned int)temp_C1 / 100),
				((unsigned int)temp_C1 % 100));
	}
}

HAL_UART_Transmit(&huart2, buf1, strlen((char*)buf1), HAL_MAX_DELAY);

}

void i2c2 (uint8_t addr)
{
HAL_StatusTypeDef ret;

buf2[0] = temp_reg;
ret = HAL_I2C_Master_Transmit(&hi2c2, addr, buf2, 1, HAL_MAX_DELAY);
if (ret != HAL_OK) {
	strcpy((char*)buf2,"Error Tx\r\n");
} else {
	ret = HAL_I2C_Master_Receive(&hi2c2, addr, buf2, 2, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		strcpy((char*)buf2,"Error Rx\r\n");
	} else {
		val2 = ((int16_t)buf2[0] << 3) | (buf2[1] >> 5);
		temp_C2 = val2 * 0.125;
		temp_C2 *= 100;
		sprintf((char*)buf2, "I2C2 = %u.%2u C \r\n",
				((unsigned int)temp_C2 / 100),
				((unsigned int)temp_C2 % 100));
	}
}

HAL_UART_Transmit(&huart2, buf2, strlen((char*)buf2), HAL_MAX_DELAY);

}


