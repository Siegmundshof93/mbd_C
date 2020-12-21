#include "das_auto.h"


extern TIM_HandleTypeDef htim2;




uint32_t IC_Val1 = 0;
uint32_t IC_Val2 = 0;
uint32_t Difference = 0;
uint8_t Is_First_Captured = 0;  // is the first value captured ?
uint8_t Distance  = 0;
uint8_t buf[12];
bool point = FALSE;





void delay(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim2,0);
	while(__HAL_TIM_GET_COUNTER(&htim2) < time);
}



void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
	{
		if (Is_First_Captured==0) // if the first value is not captured
		{
			IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			Is_First_Captured = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured==1)   // if the first is already captured
		{
			IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // read second value
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

			if (IC_Val2 > IC_Val1)
			{
				Difference = IC_Val2-IC_Val1;
			}

			else if (IC_Val1 > IC_Val2)
			{
				Difference = (0xffff - IC_Val1) + IC_Val2;
			}

			Distance = Difference * .034/2;

			PWM_SPEED(575, 600, 675, 700, 775, 800, 875, 900, 975, 1000);



			sprintf((char*)buf, "%u.%u cm \r\n",
								((unsigned int)Distance / 1),
								((unsigned int)Distance % 1));
			Is_First_Captured = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC1);
		}
	}
}

void HCSR04_Read (void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);  // pull the TRIG pin low

	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC1);
	HAL_Delay(10);
}
/**
void PWM_init (uint16_t pulse) {
	  HAL_TIM_Base_Start(&htim3);

	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);


	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse); //PA6
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse); //PA7

}
**/



/* USER CODE END 0 */

