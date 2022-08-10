#include "Boot.h"
#include "FrequencyRead.h"
#include "LUX.h"
#include "lm75.h"
#include "eeprom.h"
#include "pcf8563.h"
#include "CanTx.h"



extern RTC_HandleTypeDef hrtc;
extern CRC_HandleTypeDef hcrc;
extern UART_HandleTypeDef huart2;

extern int frequency_ideal;
extern int frequency_notIdeal;
extern uint16_t lux_val;
extern uint8_t temp_C;



uint8_t payload_data[32];
uint32_t CrcVal;
uint32_t CrcCheck;
uint8_t str[1025];

uint8_t PayloadId = 0x44;
//uint16_t TestEepromRead = 0x0001;
uint8_t testCRC[4] = {0xAA, 0xBB, 0xCC, 0xDD};

uint8_t empty = 0x00;

void Boot()
{
set_time_InnerSTM_rtc();
pwmStart();
freqInit();
CAN_Init();



	while(1)
	{
frequencySequence();

SunSensor();
tempSensor();
final_data_set();
CRCgenerate();


WriteArray();
readMemory();

CAN_CheckTransmit();



/*
int width_of_diff = sprintf(str, "%X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X %X \r\n", \
		eeprom_buf_read[0], eeprom_buf_read[1], eeprom_buf_read[2], eeprom_buf_read[3], eeprom_buf_read[4], \
		eeprom_buf_read[5], eeprom_buf_read[6], eeprom_buf_read[7], eeprom_buf_read[8], eeprom_buf_read[9], \
		eeprom_buf_read[10], eeprom_buf_read[11], eeprom_buf_read[12], eeprom_buf_read[13], eeprom_buf_read[14], \
		eeprom_buf_read[15], eeprom_buf_read[16], eeprom_buf_read[17], eeprom_buf_read[18], eeprom_buf_read[19], \
		eeprom_buf_read[20], eeprom_buf_read[21], eeprom_buf_read[22], eeprom_buf_read[23]);
		  HAL_UART_Transmit(&huart2, str, width_of_diff, 100);
*/

	}
}





void final_data_set()
{

	 RTC_DateTypeDef gDate;
	 RTC_TimeTypeDef gTime;
	 HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	 HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	payload_data[0] = PayloadId;
	payload_data[1] = gTime.Hours;
	payload_data[2] = gTime.Minutes;
	payload_data[3] = gTime.Seconds;
	payload_data[4] = gDate.Date;
	payload_data[5] = gDate.Month;
	payload_data[6] = gDate.Year;
	payload_data[7] = (frequency_ideal >> 16) & 0xFF;
	payload_data[8] = (frequency_ideal >> 8) & 0xFF;
	payload_data[9] = frequency_ideal & 0xFF;
	payload_data[10] = (frequency_notIdeal >> 16) & 0xFF;
	payload_data[11] = (frequency_notIdeal >> 8) & 0xFF;
	payload_data[12] = frequency_notIdeal & 0xFF;
	payload_data[13] = (lux_val >> 8) & 0xFF;
	payload_data[14] = lux_val;
	payload_data[15] = temp_C;


}

void CRCgenerate()
{
	 CrcVal = HAL_CRC_Calculate(&hcrc, payload_data, 16);
	 CrcCheck = HAL_CRC_Calculate(&hcrc, testCRC, 4);
	 payload_data[16] = (CrcVal >> 24) & 0xFF;
	 payload_data[17] = (CrcVal >> 16) & 0xFF;
	 payload_data[18] = (CrcVal >> 8)  & 0xFF;
	 payload_data[19] = CrcVal;
	 payload_data[20] = 0xAA;
	 payload_data[21] = 0xBB;
	 payload_data[22] = 0xCC;
	 payload_data[23] = 0xDD;
}


void set_time_InnerSTM_rtc()
{
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
  sTime.Hours = 0x21; // set hours
  sTime.Minutes = 0x39; // set minutes
  sTime.Seconds = 0x30; // set seconds
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);

  sDate.Month = RTC_MONTH_AUGUST; // month
  sDate.Date = 0x07; // date
  sDate.Year = 0x22; // year
  HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

  //HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2); // backup register
}


