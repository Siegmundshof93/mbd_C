#include "das_auto.h"



extern TIM_HandleTypeDef htim3;
extern bool point;
//extern uint8_t Distance;
extern uint8_t turn;


void PWM_GO (uint16_t IN1, int FLAG1, uint16_t IN2, int FLAG2) {
		  HAL_GPIO_WritePin(GPIOA,IN1, FLAG1); // in1 0x0400U left forward
		  HAL_GPIO_WritePin(GPIOA,IN2, FLAG2); // in4 0x0800U right forward
		  	  	  	  	  	  	  	  	  	   // in2 0x0200U right backwords
		  	  	  	  	  	  	  	  	  	   // in3 0x1000U
}


void PWM_SPEED (int S1, int S12, int S2, int S22, int S3, int S32, int S4, int S42, int S5, int S52) {
//	Disable Bckwrds if (Distance < 10){

//	Disable Bckwrds	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
					/**__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S3); //PA6
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S3); //PA7
					PWM_GO(0x0400U, 0, 0x0800U, 0);
					PWM_GO(0x1000U, 1, 0x0200U, 1);**/
//	Disable Bckwrds	point = TRUE;



// Disable Bckwrds	}  else

	/*
					if (Distance < 20){
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S1); //PA6
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S12); //PA7
					PWM_GO(0x1000U, 0, 0x0200U, 0);
					PWM_GO(0x0400U, 1, 0x0800U, 1);
				} else if (Distance < 30){
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S2); //PA6
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S22);
					PWM_GO(0x1000U, 0, 0x0200U, 0);
					PWM_GO(0x0400U, 1, 0x0800U, 1);
				} else if (Distance < 40){
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S3); //PA6
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S32);
					PWM_GO(0x1000U, 0, 0x0200U, 0);
					PWM_GO(0x0400U, 1, 0x0800U, 1);
				} else if (Distance < 50){
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S4); //PA6
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S42);
					PWM_GO(0x1000U, 0, 0x0200U, 0);
					PWM_GO(0x0400U, 1, 0x0800U, 1);
				} else {
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S5); //PA6
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S52); //PA7
					PWM_GO(0x1000U, 0, 0x0200U, 0);
					PWM_GO(0x0400U, 1, 0x0800U, 1);
				}
				*/



						switch (turn)
						 {

						case 0:
											PWM_GO(0x1000U, 0, 0x0200U, 0);
											PWM_GO(0x0400U, 0, 0x0800U, 0);
											break;

						case 1:
											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0); //PA6
											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S5); //PA7
											PWM_GO(0x1000U, 0, 0x0200U, 0);
											PWM_GO(0x0400U, 1, 0x0800U, 1);
											turn = 0;
											break;
						case 2:
											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S5); //PA6
											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0); //PA7
											PWM_GO(0x1000U, 0, 0x0200U, 0);
											PWM_GO(0x0400U, 1, 0x0800U, 1);
											turn = 0;
											break;
						case 3:
						  					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S5); //PA6
						  					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S5); //PA7
						  					PWM_GO(0x1000U, 0, 0x0200U, 0);
						  					PWM_GO(0x0400U, 1, 0x0800U, 1);
						  					turn = 0;
											break;
						case 4:
											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, S2); //PA6
						  					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, S2); //PA7
						  					PWM_GO(0x0400U, 0, 0x0800U, 0);
						  					PWM_GO(0x1000U, 1, 0x0200U, 1);
						  					turn = 0;
											break;
					}
}


void backwords() {
	if (point == TRUE) {
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 700); //PA6
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 700); //PA7
		PWM_GO(0x0400U, 0, 0x0800U, 0);
		PWM_GO(0x1000U, 1, 0x0200U, 1);
		HAL_Delay(1000);
		PWM_GO(0x1000U, 0, 0x0200U, 0);
		HAL_Delay(200);
		PWM_GO(0x0200U, 1, 0x0800U, 1);
		HAL_Delay(350);
		PWM_GO(0x0200U, 0, 0x0800U, 0);
		point = FALSE;
		turn = 0;
	} else {
		__NOP();
	}
}






