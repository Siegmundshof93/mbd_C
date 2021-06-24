#include "CanRx.h"

extern CAN_HandleTypeDef hcan1;

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint8_t TxData[8];
uint8_t RxData[8];

uint32_t TxMailbox;

bool datacheck = false;

void Boot(void)
{
	Init();

	while(1)
	{

		if(datacheck == true)
		{
			for(int i = 0; i<RxData[1]; i++)
			{
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
				HAL_Delay(RxData[0]);
			}
			datacheck = false;
		}
		HAL_Delay(100);
	}
}

void Init(void)
{
		CanFilterInit();
		HAL_CAN_Start(&hcan1);
		HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);

		/**Initialisation**/
		TxHeader.DLC = 2; //data length
		TxHeader.IDE = CAN_ID_STD; //standart
		TxHeader.RTR = CAN_RTR_DATA; //data frame
		TxHeader.StdId = 0x103; // senders ID
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &RxHeader, RxData);
	if (RxHeader.DLC == 2)
	{
		datacheck = true;
	}
}

void CanFilterInit(void)
{
CAN_FilterTypeDef canfilterconfig;

canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
canfilterconfig.FilterBank = 10;
canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO1;
canfilterconfig.FilterIdHigh = 0x446<<5;
canfilterconfig.FilterIdLow = 0;
canfilterconfig.FilterMaskIdHigh = 0x446<<5;
canfilterconfig.FilterMaskIdLow = 0;
canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;

HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
}

