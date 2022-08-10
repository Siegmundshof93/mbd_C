#include "pcf8563.h"


extern RTC_HandleTypeDef hrtc;
extern I2C_HandleTypeDef hi2c3;
extern UART_HandleTypeDef huart2;

uint8_t val[10];
uint8_t str[100];
uint8_t buf_h;
uint8_t buf_min;
uint8_t buf_sec;
uint8_t buf_day;
uint8_t buf_mon;
uint8_t buf_year;



void rtcRead()
{
	HAL_I2C_Mem_Read(&hi2c3, PCF8563_ADDRESS, 0x02, I2C_MEMADD_SIZE_8BIT, val, 1, 100);
		    buf_sec = val[0];
		  HAL_I2C_Mem_Read(&hi2c3, PCF8563_ADDRESS, 0x03, I2C_MEMADD_SIZE_8BIT, val, 1, 100);
			buf_min = val[0];
		  HAL_I2C_Mem_Read(&hi2c3, PCF8563_ADDRESS, 0x04, I2C_MEMADD_SIZE_8BIT, val, 1, 100);
			buf_h = val[0];
				    buf_h &= 0x3f;
		  HAL_I2C_Mem_Read(&hi2c3, PCF8563_ADDRESS, 0x05, I2C_MEMADD_SIZE_8BIT, val, 1, 100);
				buf_day = val[0];
				buf_day &= 0x3f;
		  HAL_I2C_Mem_Read(&hi2c3, PCF8563_ADDRESS, 0x07, I2C_MEMADD_SIZE_8BIT, val, 1, 100);
				buf_mon = val[0];
				buf_mon &= 0x1f;
		  HAL_I2C_Mem_Read(&hi2c3, PCF8563_ADDRESS, 0x08, I2C_MEMADD_SIZE_8BIT, val, 1, 100);
				buf_year = val[0];
		   // int width = sprintf(str, "%X:%X:%X %X-%X-%X\r\n", buf_h, buf_min, buf_sec, buf_day, buf_mon, buf_year);
		   // HAL_UART_Transmit(&huart2, str, width, 100);


}





void PCF8563_ClkoutFrequency()
{
	uint8_t tmp = 0x83;


	HAL_I2C_Mem_Write(&hi2c3, PCF8563_ADDRESS, PCF8563_REG_CLKOUT, I2C_MEMADD_SIZE_8BIT, &tmp, 1, 100);
}



void setTime()
{
	uint8_t tmp1 = 0x00;
	HAL_I2C_Mem_Write(&hi2c3, PCF8563_ADDRESS, 0x02, I2C_MEMADD_SIZE_8BIT, &tmp1, 1, 100);
	uint8_t tmp2 = 0x16;
	HAL_I2C_Mem_Write(&hi2c3, PCF8563_ADDRESS, 0x03, I2C_MEMADD_SIZE_8BIT, &tmp2, 1, 100);
	uint8_t tmp3 = 0x22;
	HAL_I2C_Mem_Write(&hi2c3, PCF8563_ADDRESS, 0x04, I2C_MEMADD_SIZE_8BIT, &tmp3, 1, 100);
	uint8_t tmp4 = 0x15;
	HAL_I2C_Mem_Write(&hi2c3, PCF8563_ADDRESS, 0x05, I2C_MEMADD_SIZE_8BIT, &tmp4, 1, 100);
	uint8_t tmp5 = 0x07;
	HAL_I2C_Mem_Write(&hi2c3, PCF8563_ADDRESS, 0x07, I2C_MEMADD_SIZE_8BIT, &tmp5, 1, 100);
	uint8_t tmp6 = 0x22;
	HAL_I2C_Mem_Write(&hi2c3, PCF8563_ADDRESS, 0x08, I2C_MEMADD_SIZE_8BIT, &tmp6, 1, 100);
}

void PCF8563_Init()
{


	PCF8563_ClkoutFrequency();
    setTime();

}


/*
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

void get_time_InnerSTM_rtc()
//{
 RTC_DateTypeDef gDate;
 RTC_TimeTypeDef gTime;
/* Get the RTC current Time */
 //HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
/* Get the RTC current Date */
 //HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
/* Display time Format: hh:mm:ss */
// int width_of = sprintf(str,"%02d:%02d:%02d \r\n",gTime.Hours, gTime.Minutes, gTime.Seconds);
 //HAL_UART_Transmit(&huart2, str, width_of, 100);
/* Display date Format: dd-mm-yy */
 //int width_of1 = sprintf(str,"%02d-%02d-%2d \r\n",gDate.Date, gDate.Month, gDate.Year);
 //HAL_UART_Transmit(&huart2, str, width_of1, 100);

//}

