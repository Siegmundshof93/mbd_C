#include "LUX.h"
#include "W25Q.h"
uint8_t buf[60];
uint8_t receive[100];
uint16_t val;
uint8_t Address = ADDR_LUX;
uint8_t Lux = TAKE_MEASUREMENT;
uint32_t i = 0;

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_i2c1_rx;
extern DMA_HandleTypeDef hdma_i2c1_tx;
extern UART_HandleTypeDef huart2;

void Get_I2C_Value(void)
{

buf[0] = Lux;
	   HAL_I2C_Master_Transmit(&hi2c1,Address,buf,1,HAL_MAX_DELAY);
	   HAL_Delay(200);

	   HAL_I2C_Master_Receive_IT(&hi2c1,Address,receive,2);
	   HAL_Delay(1);
}

void 	HAL_I2C_MasterRxCpltCallback (I2C_HandleTypeDef *hi2c){
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	val = ((uint16_t)receive[0]<<8 | receive[1]);
	Write_Flash(val, i);
	i = i + 2;
	//sprintf((char*)receive,"lux = %u \r\n",val);
	//HAL_UART_Transmit(&huart2, receive, strlen((char*)receive), HAL_MAX_DELAY);

}
