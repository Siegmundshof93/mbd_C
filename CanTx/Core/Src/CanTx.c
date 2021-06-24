#include "CanTx.h"

extern CAN_HandleTypeDef hcan1;

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint8_t TxData[8];
uint8_t RxData[8];

uint32_t TxMailbox;

bool datacheck = false;

void Boot(void)
{


	while(1)
	{
		if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) == 0) {
			Init();
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			HAL_Delay(10);
			Init2();
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			HAL_Delay(10);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			HAL_Delay(1000);
		}
	}
}

void Init(void)
{
		//CanFilterInit();
		TxData[0] = 0xF0;
		TxData[1] = 0xF1;
		TxData[2] = 0xF2;
		TxData[3] = 0xF3;
		TxData[4] = 0xF4;
		TxData[5] = 0xF5;
		TxData[6] = 0xF6;
		TxData[7] = 0xF7;
		HAL_CAN_Start(&hcan1);
		//HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

		/**Initialisation**/
		TxHeader.DLC = 8; //data length
		TxHeader.IDE = CAN_ID_EXT; // extended
		TxHeader.RTR = CAN_RTR_DATA; //data frame
		TxHeader.ExtId = 0x1C0100FA; // senders ID
}

void Init2(void)
{
		//CanFilterInit();
		TxData[0] = 0xE8;
		TxData[1] = 0xE9;
		TxData[2] = 0xE0;
		TxData[3] = 0xE1;
		TxData[4] = 0xE2;
		TxData[5] = 0xE3;
		TxData[6] = 0xE4;
		TxData[7] = 0xE5;
		//HAL_CAN_Start(&hcan1);
		//HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

		/**Initialisation**/
		TxHeader.DLC = 8; //data length
		TxHeader.IDE = CAN_ID_EXT; //extended
		TxHeader.RTR = CAN_RTR_DATA; //data frame
		TxHeader.ExtId = 0x1C0181FA; // senders ID
}

void CanFilterInit(void)
{
CAN_FilterTypeDef canfilterconfig;

canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
canfilterconfig.FilterBank = 5;
canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
canfilterconfig.FilterIdHigh = 0x103<<5;
canfilterconfig.FilterIdLow = 0;
canfilterconfig.FilterMaskIdHigh = 0x103<<5;
canfilterconfig.FilterMaskIdLow = 0;
canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;

HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
}

