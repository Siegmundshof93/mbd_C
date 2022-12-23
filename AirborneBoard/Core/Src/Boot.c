#include "Airborne.h"
#include "Sx1278.h"


extern TIM_HandleTypeDef htim1;

uint8_t RadioData;
void Boot()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);

 //   HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
  //  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	uint8_t signalX[3];
	signalX[0] = 0xAA;
	signalX[1] = 0xBB;
	signalX[2] = 0xCC;
	initTx(3);

	while(1)
	{



			//	initRx(1);

			//	LoRaReceive();

				LoRaTransmit(signalX, 3);
				//MotorDriver();


HAL_Delay(100);


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
												HAL_Delay(10);
												RadioData = 0;
												break;
						case LEFT_DIRECTION:
												FIRST_MOTOR_FAST;
												SECOND_MOTOR_STOP;
												Hbridge(LEFT_BACKWARD, STOP, RIGHT_BACKWARD, STOP);
											    Hbridge(LEFT_FORWARD, GO, RIGHT_FORWARD, GO);
											    HAL_Delay(10);
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
												FIRST_MOTOR_FAST;
							  					SECOND_MOTOR_FAST;
							  					Hbridge(LEFT_FORWARD, STOP, RIGHT_FORWARD, STOP);
							  					Hbridge(LEFT_BACKWARD, GO, RIGHT_BACKWARD, GO);
							  					HAL_Delay(10);
							  					RadioData = 0;
												break;
							 }

}




void Hbridge (uint16_t Pin1, int Flag1, uint16_t Pin2, int Flag2) {
		  HAL_GPIO_WritePin(GPIOA, Pin1, Flag1);
		  HAL_GPIO_WritePin(GPIOA, Pin2, Flag2);
}

void BlueBlink (void)
{
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
HAL_Delay(100);
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0);

}

