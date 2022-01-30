/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include "Sx1278.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
 uint8_t flag = 0;

 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

 	flag = 1;

 }


 int nmea0183_checksum(char *msg) {

 	int checksum = 0;
 	int j = 0;

 	// the first $ sign and the last two bytes of original CRC + the * sign
 	for (j = 1; j < strlen(msg) - 4; j++) {
 		checksum = checksum ^ (unsigned) msg[j];
 	}

 	return checksum;
 }
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

IWDG_HandleTypeDef hiwdg;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_IWDG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */

  char sendLora[19];

	uint8_t buff[255];
	uint8_t bufI2c[2] = {0xFF, 0xFF};

	char buffStr[255];
	char nmeaSnt[80];

	char *rawSum;
	char smNmbr[3];

	// The Equator has a latitude of 0°,
	//the North Pole has a latitude of 90° North (written 90° N or +90°),
	//and the South Pole has a latitude of 90° South (written 90° S or −90°)

	char *latRaw;
	char latDg[2];
	char latMS[7];
	char *hemNS;

	// longitude in degrees (0° at the Prime Meridian to +180° eastward and −180° westward)
	// that is why 3
	char *lonRaw;
	char lonDg[3];
	char lonMS[7];
	char *hemEW;

	char *utcRaw; // raw UTC time from the NMEA sentence in the hhmmss format
	char strUTC[8]; // UTC time in the readable hh:mm:ss format

	char hH[2]; // hours
	char mM[2]; // minutes
	char sS[2]; // seconds

	uint8_t cnt = 0;


		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 // HAL_I2C_Slave_Receive_IT(&hi2c1,bufI2c, 10);
	  HAL_UART_Receive_DMA(&huart1, buff, 255);
		  if (flag == 1) { // interrupt signals that the buffer buff[300] is full



				memset(buffStr, 0, 255);

				sprintf(buffStr, "%s", buff);

				// if we want to display the incoming raw data
				//HAL_UART_Transmit(&huart2, buff, 255, 70);

				// splitting the buffStr by the "\n" delimiter with the strsep() C function
				// see http://www.manpagez.com/man/3/strsep/
				char *token, *string;

				string = strdup(buffStr);

				// actually splitting the string by "\n" delimiter
				while ((token = strsep(&string, "\n")) != NULL) {

					memset(nmeaSnt, 0, 80);

					sprintf(nmeaSnt, "%s", token);

					// selecting only $GNGLL sentences, combined GPS and GLONASS
					// on my GPS sensor this good NMEA sentence is always 50 characters
					if ((strstr(nmeaSnt, "$GNGLL") != 0)) {

						rawSum = strstr(nmeaSnt, "*");

						memcpy(smNmbr, &rawSum[1], 2);

						smNmbr[2] = '\0';

						uint8_t intSum = nmea0183_checksum(nmeaSnt);

						char hex[2];

						// "%X" unsigned hexadecimal integer (capital letters)
						sprintf(hex, "%X", intSum);

						// checksum data verification, if OK, then we can really trust
						// the data in the the NMEA sentence
						if (strstr(smNmbr, hex) != NULL) {

							//if we want display good $GNGLL NMEA sentences
						//	HAL_UART_Transmit(&huart2, nmeaSnt, 50, 70);
						//	HAL_UART_Transmit(&huart2, (uint8_t*) "\r", 1, 200);
						//	HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);

							cnt = 0;

							// splitting the good NMEA sentence into the tokens by the comma delimiter
							for (char *pV = strtok(nmeaSnt, ","); pV != NULL; pV = strtok(NULL, ",")) {

								switch (cnt) {
								case 1:
									latRaw = strdup(pV);
									break;
								case 2:
									hemNS = strdup(pV);
									break;
								case 3:
									lonRaw = strdup(pV);
									break;
								case 4:
									hemEW = strdup(pV);
									break;
								case 5:
									utcRaw = strdup(pV);
									break;
								}

								cnt++;

							}  // end for()

							memcpy(latDg, &latRaw[0], 2);
							latDg[2] = '\0';

							memcpy(latMS, &latRaw[2], 7);
							latMS[7] = '\0';

							memcpy(lonDg, &lonRaw[0], 3);
							lonDg[3] = '\0';

							memcpy(lonMS, &lonRaw[3], 7);
							lonMS[7] = '\0';
							char strLonMS[7];
							sprintf(strLonMS, "%s", lonMS);




							HAL_UART_Transmit(&huart2, (uint8_t*) latDg, 2, 200);

							HAL_UART_Transmit(&huart2, (uint8_t*) latMS, 7, 200);

							HAL_UART_Transmit(&huart2, (uint8_t*) " ", 1, 200);
							HAL_UART_Transmit(&huart2, (uint8_t*) lonDg, 3, 200);

							HAL_UART_Transmit(&huart2, (uint8_t*) strLonMS, 7, 200);

							HAL_UART_Transmit(&huart2, (uint8_t*) "\r", 1, 200);
							HAL_UART_Transmit(&huart2, (uint8_t*) "\n", 1, 200);

						sendLora[0] = latDg[0];
						sendLora[1] = latDg[1];
						sendLora[2] = latMS[0];
						sendLora[3] = latMS[1];
						sendLora[4] = latMS[2];
						sendLora[5] = latMS[3];
						sendLora[6] = latMS[4];
						sendLora[7] = latMS[5];
						sendLora[8] = latMS[6];
						sendLora[9] = lonDg[0];
						sendLora[10] = lonDg[1];
						sendLora[11] = lonDg[2];
						sendLora[12] = strLonMS[0];
						sendLora[13] = strLonMS[1];
						sendLora[14] = strLonMS[2];
						sendLora[15] = strLonMS[3];
						sendLora[16] = strLonMS[4];
						sendLora[17] = strLonMS[5];
						sendLora[18] = strLonMS[6];





						} // end of of the checksum data verification

					} // end of $GNGLL sentences selection

				} // end of splitting the buffStr by the "\n" delimiter with the strsep() C function

				flag = 0; // we are ready to get new data from the sensor

			} // end of one interrupt/full-buffer cycle




									initTx(19);
									LoRaTransmit((uint8_t*) sendLora, 19);

			HAL_Delay(100);



		                              		 // end of one interrupt/full-buffer cycle


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL10;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0x22;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_128;
  hiwdg.Init.Window = 2300;
  hiwdg.Init.Reload = 2300;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LoRa_CS_Pin|LoRa_RESET_Pin|LoRA_DIO0_Pin|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : LoRa_CS_Pin LoRa_RESET_Pin LoRA_DIO0_Pin PB12
                           PB13 PB14 */
  GPIO_InitStruct.Pin = LoRa_CS_Pin|LoRa_RESET_Pin|LoRA_DIO0_Pin|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
