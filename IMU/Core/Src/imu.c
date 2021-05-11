#include "imu.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

uint8_t buf1[100] = {0};
uint8_t str[120];
uint8_t slave_addr = DEV_ADDR << 1;


void Boot (void)
{

	Imu_init();



	while (1)
	{
	//	AccelRead();
	//	GyroRead();
	AccelGyroRead();
	LED_TOGGLE;
	HAL_Delay(100);

	}

}
//---------------------------------------------------------------------------
void Imu_init(void)

{

	//i2c_read(WHO_AM_I);
	//i2c_write(CTRL3_C, BDU);
	i2c_write(CTRL1_XL, HZ140); //turn on Accelelrometer
	i2c_write(CTRL2_G, HZ140);  //turn on Gyro

}
//---------------------------------------------------------------------------
void AccelRead(void)
{

	uint8_t buffer[6] = {0};
	int16_t AccX, AccY, AccZ;

	buffer[0] = i2c_read(X_L);
	buffer[1] = i2c_read(X_H);
	buffer[2] = i2c_read(Y_L);
	buffer[3] = i2c_read(Y_H);
	buffer[4] = i2c_read(Z_L);
	buffer[5] = i2c_read(Z_H);

	AccX = ((uint16_t)buffer[1]<<8 | buffer[0]);
	AccY = ((uint16_t)buffer[3]<<8 | buffer[2]);
	AccZ = ((uint16_t)buffer[5]<<8 | buffer[4]);

	//Two's compliment for negative values when the first bit is "1"
if(AccX > 0x7FFF)
{
	AccX = ~AccX;
}
if (AccY > 0x7FFF)
{
	AccY = ~AccY;

}
if (AccZ > 0x7FFF)
{
	AccZ = ~AccZ;
}

	sprintf((char*)str, "Accelerometer X:%6d Y:%6d Z:%6d\r\n", AccX,AccY,AccZ);
	//sprintf((char*)str, "%d,%d,%d\r\n", AccX, AccY, AccZ);
	HAL_UART_Transmit(&huart2, str, sizeof(str), 0xFFFF);


}
//----------------------------------------------------------------------
void GyroRead(void)
{
	uint8_t buffer[6] = {0};
	int16_t GyroX, GyroY, GyroZ;

		buffer[0] = i2c_read(GYRO_X_L);
		buffer[1] = i2c_read(GYRO_X_H);
		buffer[2] = i2c_read(GYRO_Y_L);
		buffer[3] = i2c_read(GYRO_Y_H);
		buffer[4] = i2c_read(GYRO_Z_L);
		buffer[5] = i2c_read(GYRO_Z_H);

		GyroX = ((uint16_t)buffer[1]<<8 | buffer[0]);
		GyroY = ((uint16_t)buffer[3]<<8 | buffer[2]);
		GyroZ = ((uint16_t)buffer[5]<<8 | buffer[4]);

		//Two's compliment for negative values when the first bit is "1"
	if(GyroX > 0x7FFF)
	{
		GyroX = ~GyroX;
	}
	if (GyroY > 0x7FFF)
	{
		GyroY = ~GyroY;

	}
	if (GyroZ > 0x7FFF)
	{
		GyroZ = ~GyroZ;
	}
		sprintf((char*)str, "Gyro          X:%6d Y:%6d Z:%6d\r\n", GyroX,GyroY,GyroZ);
		HAL_UART_Transmit(&huart2, str, sizeof(str), 0xFFFF);

}
//---------------------------------------------------------------------------
void AccelGyroRead(void)
{
	uint8_t buffer[12] = {0};
		int16_t AccX, AccY, AccZ;
		int16_t GyroX, GyroY, GyroZ;

	//-------------Accelerometer---------------------

		buffer[0] = i2c_read(X_L);
		buffer[1] = i2c_read(X_H);
		buffer[2] = i2c_read(Y_L);
		buffer[3] = i2c_read(Y_H);
		buffer[4] = i2c_read(Z_L);
		buffer[5] = i2c_read(Z_H);

		AccX = ((uint16_t)buffer[1]<<8 | buffer[0]);
		AccY = ((uint16_t)buffer[3]<<8 | buffer[2]);
		AccZ = ((uint16_t)buffer[5]<<8 | buffer[4]);

		//Two's compliment for negative values when the first bit is "1"
	if(AccX > 0x7FFF)
	{
		AccX = ~AccX;
	}
	if (AccY > 0x7FFF)
	{
		AccY = ~AccY;

	}
	if (AccZ > 0x7FFF)
	{
		AccZ = ~AccZ;
	}

	//-----------------Gyro-----------------


			buffer[6]  = i2c_read(GYRO_X_L);
			buffer[7]  = i2c_read(GYRO_X_H);
			buffer[8]  = i2c_read(GYRO_Y_L);
			buffer[9]  = i2c_read(GYRO_Y_H);
			buffer[10] = i2c_read(GYRO_Z_L);
			buffer[11] = i2c_read(GYRO_Z_H);

			GyroX = ((uint16_t)buffer[7]<<8 | buffer[6]);
			GyroY = ((uint16_t)buffer[9]<<8 | buffer[8]);
			GyroZ = ((uint16_t)buffer[11]<<8 | buffer[10]);

			//Two's compliment for negative values when the first bit is "1"
		if(GyroX > 0x7FFF)
		{
			GyroX = ~GyroX;
		}
		if (GyroY > 0x7FFF)
		{
			GyroY = ~GyroY;

		}
		if (GyroZ > 0x7FFF)
		{
			GyroZ = ~GyroZ;
		}

		sprintf((char*)str, "%d,%d,%d,%d,%d,%d\r\n", AccX, AccY, AccZ, GyroX, GyroY, GyroZ);
			HAL_UART_Transmit(&huart2, str, sizeof(str), 0xFFFF);
}

//----------------------------------------------------------------------------
 uint8_t i2c_read (uint8_t addr)
{

	HAL_I2C_Master_Transmit(&hi2c1, slave_addr, &addr, 1, 0xFFFF);
	HAL_I2C_Master_Receive(&hi2c1, slave_addr, buf1, 1, 0xFFFF);
uint8_t val = buf1[0];

//sprintf(str, "0x%X\r\n", val);
//HAL_UART_Transmit(&huart2, str, sizeof(str), 0xFFFF);
return val;
}
//----------------------------------------------------------------------------
void i2c_write(uint8_t addr, uint8_t data)
{

	HAL_I2C_Master_Transmit(&hi2c1, slave_addr, &addr, 1, 0xFFFF);
	HAL_I2C_Master_Receive(&hi2c1, slave_addr, buf1, 1, 0xFFFF);

	uint8_t val = buf1[0];
	val |= data;

	HAL_I2C_Mem_Write(&hi2c1, (uint16_t)slave_addr, (uint16_t)addr,I2C_MEMADD_SIZE_8BIT, &val, 1,0xFFFF);

	HAL_I2C_Master_Transmit(&hi2c1, slave_addr, &addr, 1, 0xFFFF);
	HAL_I2C_Master_Receive(&hi2c1, slave_addr, buf1, 1, 0xFFFF);

	//uint8_t val1 = buf1[0];


//	sprintf(str, "0x%X\r\n", val1);
//	HAL_UART_Transmit(&huart2, str, sizeof(str), 0xFFFF);
}
