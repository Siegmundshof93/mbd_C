 #include "eeprom.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;


uint8_t eepromBuf[100];
uint16_t device = EEPROM_DEV;
uint8_t str[100];
uint16_t i = 0;
uint8_t eeprom_buf_read[32];
extern uint8_t payload_data[32];


void eeprom_Write (uint16_t addr, uint8_t data)
{
	 HAL_I2C_Mem_Write(&hi2c1, device, addr,I2C_MEMADD_SIZE_16BIT, &data, 1, 100);
}

uint8_t eeprom_Read (uint16_t addr)
{

	HAL_I2C_Mem_Read(&hi2c1, device, addr,I2C_MEMADD_SIZE_16BIT, eepromBuf, 10, 100);

uint8_t val = eepromBuf[0];
//	int width =	sprintf(str, "0x%X\r\n", val);
//		HAL_UART_Transmit(&huart2, str, width, 0xFFFF);
		return val;
}



void WriteArray()
{
	if(i < 240)
	{
		eeprom_Write(i, payload_data[0]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[1]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[2]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[3]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[4]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[5]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[6]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[7]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[8]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[9]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[10]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[11]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[12]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[13]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[14]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[15]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[16]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[17]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[18]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[19]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[20]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[21]);
		i = i+1;
		HAL_Delay(10);

		eeprom_Write(i, payload_data[22]);
		i = i+1;
		HAL_Delay(10);
		eeprom_Write(i, payload_data[23]);
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
	if (i > 23)
	{
		memCount = i - 24;
		eeprom_buf_read[0] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 23;
		eeprom_buf_read[1] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 22;
		eeprom_buf_read[2] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 21;
		eeprom_buf_read[3] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 20;
		eeprom_buf_read[4] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 19;
		eeprom_buf_read[5] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 18;
		eeprom_buf_read[6] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 17;
		eeprom_buf_read[7] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 16;
		eeprom_buf_read[8] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 15;
		eeprom_buf_read[9] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 14;
		eeprom_buf_read[10] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 13;
		eeprom_buf_read[11] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 12;
		eeprom_buf_read[12] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 11;
		eeprom_buf_read[13] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 10;
		eeprom_buf_read[14] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 9;
		eeprom_buf_read[15] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 8;
		eeprom_buf_read[16] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 7;
		eeprom_buf_read[17] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 6;
		eeprom_buf_read[18] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 5;
		eeprom_buf_read[19] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 4;
		eeprom_buf_read[20] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 3;
		eeprom_buf_read[21] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 2;
		eeprom_buf_read[22] = eeprom_Read(memCount);
		HAL_Delay(10);

		memCount = i - 1;
		eeprom_buf_read[23] = eeprom_Read(memCount);
		HAL_Delay(10);


	}

	if (i < 20)
	{
				memCount = 216;
				eeprom_buf_read[0] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 217;
				eeprom_buf_read[1] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 218;
				eeprom_buf_read[2] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 219;
				eeprom_buf_read[3] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 220;
				eeprom_buf_read[4] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 221;
				eeprom_buf_read[5] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 222;
				eeprom_buf_read[6] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 223;
				eeprom_buf_read[7] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 224;
				eeprom_buf_read[8] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 225;
				eeprom_buf_read[9] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 226;
				eeprom_buf_read[10] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 227;
				eeprom_buf_read[11] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 228;
				eeprom_buf_read[12] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 229;
				eeprom_buf_read[13] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 230;
				eeprom_buf_read[14] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 231;
				eeprom_buf_read[15] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 232;
				eeprom_buf_read[16] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 233;
				eeprom_buf_read[17] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 234;
				eeprom_buf_read[18] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 235;
				eeprom_buf_read[19] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 236;
				eeprom_buf_read[20] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 237;
				eeprom_buf_read[21] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 238;
				eeprom_buf_read[22] = eeprom_Read(memCount);
				HAL_Delay(10);

				memCount = 239;
				eeprom_buf_read[23] = eeprom_Read(memCount);

	}
//	int width =	sprintf(str, "memcount = %d i = %d\r\n", memCount, i);
//		HAL_UART_Transmit(&huart2, str, width, 100);
}



