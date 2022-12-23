#include "UBX_GNSS.h"

extern UART_HandleTypeDef huart1;




/*!
 * Make request for navigation position velocity time solution data.
 * @param GNSS Pointer to main GNSS structure.
 */
void GNSS_GetPVTData(void) {
	HAL_UART_Transmit_DMA(&huart1, getPVTData, sizeof(getPVTData));
	HAL_UART_Receive_IT(&huart1, uartWorkingBuffer, 100);
}




/*!
 *  Sends the basic configuration: Activation of the UBX standard, change of NMEA version to 4.10 and turn on of the Galileo system.
 * @param GNSS Pointer to main GNSS structure.
 */
void GNSS_LoadConfig(void) {
	HAL_UART_Transmit(&huart1, configUBX, sizeof(configUBX), 0xFFFF);
	HAL_Delay(250);
	HAL_UART_Transmit(&huart1, setNMEA410, sizeof(setNMEA410), 0xFFFF);
	HAL_Delay(250);
	HAL_UART_Transmit(&huart1, setGNSS, sizeof(setGNSS), 0xFFFF);
	HAL_Delay(250);
}



