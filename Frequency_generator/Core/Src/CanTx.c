#include "CanTx.h"

extern CAN_HandleTypeDef hcan1;

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

extern uint8_t eeprom_buf_read[32];

uint8_t TxData1[8];
uint8_t TxData2[8];
uint8_t TxData3[8];
uint8_t RxData[8];

uint32_t TxMailbox;

bool datacheck = false;

void CAN_CheckTransmit()
{

	if(datacheck == true)
				{

		TxData1[0] =  eeprom_buf_read[0];
		TxData1[1] =  eeprom_buf_read[1];
		TxData1[2] =  eeprom_buf_read[2];
		TxData1[3] =  eeprom_buf_read[3];
		TxData1[4] =  eeprom_buf_read[4];
		TxData1[5] =  eeprom_buf_read[5];
		TxData1[6] =  eeprom_buf_read[6];
		TxData1[7] =  eeprom_buf_read[7];

		TxData2[0] =  eeprom_buf_read[8];
		TxData2[1] =  eeprom_buf_read[9];
		TxData2[2] =  eeprom_buf_read[10];
		TxData2[3] =  eeprom_buf_read[11];
		TxData2[4] =  eeprom_buf_read[12];
		TxData2[5] =  eeprom_buf_read[13];
		TxData2[6] =  eeprom_buf_read[14];
		TxData2[7] =  eeprom_buf_read[15];

		TxData3[0] =  eeprom_buf_read[16];
		TxData3[1] =  eeprom_buf_read[17];
		TxData3[2] =  eeprom_buf_read[18];
		TxData3[3] =  eeprom_buf_read[19];
		TxData3[4] =  eeprom_buf_read[20];
		TxData3[5] =  eeprom_buf_read[21];
		TxData3[6] =  eeprom_buf_read[22];
		TxData3[7] =  eeprom_buf_read[23];

			HAL_Delay(10);
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData1, &TxMailbox);
			HAL_Delay(100);
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData2, &TxMailbox);
			HAL_Delay(100);
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData3, &TxMailbox);

			datacheck = false;

		}
		else {
			__NOP();
		}
}

void CAN_Init()
{
		CanFilterInit();

		HAL_CAN_Start(&hcan1);
		HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

		/**Initialisation**/
		TxHeader.DLC = 8; //data length
		TxHeader.IDE = CAN_ID_STD; // extended
		TxHeader.RTR = CAN_RTR_DATA; //data frame
		TxHeader.StdId = 0x44; // senders ID

}



void CanFilterInit(void)
{
CAN_FilterTypeDef canfilterconfig;

canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
canfilterconfig.FilterBank = 5;
canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
canfilterconfig.FilterIdHigh = 0x55<<5;
canfilterconfig.FilterIdLow = 0;
canfilterconfig.FilterMaskIdHigh = 0x55<<5;
canfilterconfig.FilterMaskIdLow = 0;
canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;

HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
	if (RxHeader.DLC == 8)
	{
		datacheck = true;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	}
}
