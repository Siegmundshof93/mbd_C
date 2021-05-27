#include "Boot.h"
#include "NRF24.h"

extern TIM_HandleTypeDef htim3;
extern uint8_t RadioData;
char str1[150]={0};
uint8_t buf1[20]={0};



void Boot(void)
{

	 NRF24_ini();
     HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
     HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);


	while(1)
	{
		NRF24L01_Receive();
		MotorDriver();
	}

}


void MotorDriver(void)
{

	switch (RadioData)
							 {

						case 0:
												Hbridge(LEFT_BACKWARD, STOP, RIGHT_BACKWARD, STOP);
												Hbridge(LEFT_FORWARD, STOP, RIGHT_FORWARD, STOP);
												break;

						case RIGHT_DIRECTION:
												FIRST_MOTOR_STOP;
												SECOND_MOTOR_FAST;
												Hbridge(LEFT_BACKWARD, STOP, RIGHT_BACKWARD, STOP);
												Hbridge(LEFT_FORWARD, GO, RIGHT_FORWARD, GO);
												RadioData = 0;
												break;
						case LEFT_DIRECTION:
												FIRST_MOTOR_FAST;
												SECOND_MOTOR_STOP;
												Hbridge(LEFT_BACKWARD, STOP, RIGHT_BACKWARD, STOP);
											    Hbridge(LEFT_FORWARD, GO, RIGHT_FORWARD, GO);
												RadioData = 0;
												break;
						case FORWARD_DIRECTION:
							  					FIRST_MOTOR_FAST;
							  					SECOND_MOTOR_FAST;
							  					Hbridge(LEFT_BACKWARD, STOP, RIGHT_BACKWARD, STOP);
							  					Hbridge(LEFT_FORWARD, GO, RIGHT_FORWARD, GO);
							  					HAL_Delay(10);
							  					RadioData = 0;
												break;
						case BACKWARD_DIRECTION:
												FIRST_MOTOR_LOW;
							  					SECOND_MOTOR_LOW;
							  					Hbridge(LEFT_FORWARD, STOP, RIGHT_FORWARD, STOP);
							  					Hbridge(LEFT_BACKWARD, GO, RIGHT_BACKWARD, GO);
							  					RadioData = 0;
												break;
							 }

}

void Hbridge (uint16_t Pin1, int Flag1, uint16_t Pin2, int Flag2) {
		  HAL_GPIO_WritePin(GPIOA, Pin1, Flag1);
		  HAL_GPIO_WritePin(GPIOA, Pin2, Flag2);
}
