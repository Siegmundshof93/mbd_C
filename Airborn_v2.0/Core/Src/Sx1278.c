#include "Sx1278.h"



extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart2;

uint8_t buffer[512];




/*
buffer[0] = 0x01;
buffer[1] = 0x02;
buffer[2] = 0x03;
*/

//	while(1)
//	{
//		LoRaReceive();
		//LoRaRead(RegHopPeriod);
		//LoRaTransmit(buffer, 3);
//		HAL_Delay(10);

//	}

//}


uint8_t LoRaRead(uint8_t addr)
{
	uint8_t TxBuf[2];
	uint8_t RxBuf[2];
//	uint8_t str[100];


	addr &= 0x7F;
	TxBuf[0] = addr;
	TxBuf[1] = 0x0;

		CS_OFF;
		HAL_SPI_TransmitReceive(&hspi1,TxBuf,RxBuf,2,100);
		while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
		CS_ON;
	//	int length = sprintf((char*)str, "Value = 0x%X \r\n", RxBuf[1]);
	//	HAL_UART_Transmit(&huart2, str, length, 1000);


		return RxBuf[1];
}


void LoRaBurstRead(uint8_t addr, uint8_t* bufRx, uint8_t length)
{
	uint8_t i;
	if (length <= 1)
	{
		return;
	} else {
	CS_OFF;
	HAL_SPI_Transmit(&hspi1, &addr, 1, 1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);

	for(i = 0; i<length; i++)
	{
		*(bufRx + i) = LoRaRead_hw();
	}
	CS_ON;
	}
}

uint8_t LoRaRead_hw(void)
{
	uint8_t bufTx = {0};
	uint8_t bufRx = {0};

	HAL_SPI_TransmitReceive(&hspi1, &bufTx, &bufRx, 1 ,1000);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	return bufRx;
}



void LoRaWrite(uint8_t addr, uint8_t* value)
{
	addr |= 0x80;
	CS_OFF;
	HAL_SPI_Transmit(&hspi1, &addr, 1, TRANSMIT_TIMEOUT);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, value, 1, TRANSMIT_TIMEOUT);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	CS_ON;

}

void LoRa_BurstWrite(uint8_t addr, uint8_t* value, uint8_t length)
{
	addr |= 0x80;

	CS_OFF;
	HAL_SPI_Transmit(&hspi1, &addr, 1, TRANSMIT_TIMEOUT);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, value, length, TRANSMIT_TIMEOUT);
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	CS_ON;

}

void LoRa_Mode(int mode)
{
uint8_t read;

	read = LoRaRead(RegOpMode);


	if(mode == SLEEP_MODE){
		read = (read & 0xF8) | 0x00;

	}else if (mode == STNBY_MODE){
		read = (read & 0xF8) | 0x01;


	}else if (mode == TRANSMIT_MODE){
		read = (read & 0xF8) | 0x03;

	}else if (mode == RXCONTIN_MODE){
		read = (read & 0xF8) | 0x05;

	}else if (mode == RXSINGLE_MODE){
		read = (read & 0xF8) | 0x06;

	}
	LoRaWrite(RegOpMode, &read);
}


void SetFrequency(int freq)
{
 uint8_t data;
 uint32_t F;

 F = (freq * 524288) / 32;

 //write MSB
 data = F >> 16;
 LoRaWrite(RegFrMsb, &data);
 HAL_Delay(5);

 //write MID
 data = F >> 8;
 LoRaWrite(RegFrMid, &data);
 HAL_Delay(5);

 //Write LSB
 data = F >> 0;
 LoRaWrite(RegFrLsb, &data);
 HAL_Delay(5);
}

void SetSpreadFactor (int SF, int CRC_)
{
	uint8_t data;

	data = SF << 4 | CRC_ << 2;
	LoRaWrite(RegModemConfig2, &data);
	HAL_Delay(10);
}

void SetPower (uint8_t power)
{
	uint8_t Power = power;
	LoRaWrite(RegPaConfig, &Power);
	HAL_Delay(10);
}

void SetOCP (uint8_t current)
{


	uint8_t OcpTrim;

	if(current < 45)
			current = 45;

	if(current > 120)
			current = 120;


	if(current <= 120)
			OcpTrim = (current - 45)/5;
	else if(current <= 240)
			OcpTrim = (current + 30)/10;



	//OcpTrim |= 0x10;

	LoRaWrite(RegOcp, &OcpTrim);
	HAL_Delay(10);


}

void SetLNA(uint8_t gain)
{

	uint8_t Gain = gain;
	LoRaWrite(RegLna, &Gain);
	HAL_Delay(10);

}



void SetBandWcrcRate(uint8_t bandW, uint8_t crcRate)
{
uint8_t data = {0};

data = bandW << 4 | crcRate << 1;
LoRaWrite(RegModemConfig1, &data);
HAL_Delay(10);
}

void SetPreamble(uint8_t preamble)
{
	uint8_t data = preamble;
	LoRaWrite(RegPreambleLsb, &data);
	HAL_Delay(10);
}

void ExtraSetup(void)
{
uint8_t maxTime = 0x08;
uint8_t Sync =0x34;
uint8_t MapPream = 0x01;

LoRaWrite(RegSymbTimeoutL,&maxTime); 	//set timeout
HAL_Delay(10);
LoRaWrite(RegSync, &Sync);			 	//set sync
HAL_Delay(10);
LoRaWrite(RegDioMapping2, &MapPream); 	//map preamble detect
HAL_Delay(10);
}




void preInit(void)
{

	uint8_t data;
	uint8_t read;


	CS_ON;
	RESET_OFF;
	HAL_Delay(1);
	RESET_ON;
	HAL_Delay(100);

	//goto sleep mode
	LoRa_Mode(SLEEP_MODE);
	HAL_Delay(15);

	//Turn on LoRa mode
	read = LoRaRead(RegOpMode);
	HAL_Delay(10);
	data = read | 0x88;
	LoRaWrite(RegOpMode, &data);
	HAL_Delay(100);
}



void init(void)
{

preInit(); //initial superBasic setup

SetFrequency(FREQ_434); 					//set frequency
SetPower(POWER_17db); 						//set output power gain
SetOCP(CURR_100);	  						//set over current protection
SetLNA(MAX_GAIN);							//set LNA gain
SetBandWcrcRate(BW_125KHz, CR_4_5);			//set Bandwidth and coding rate
SetSpreadFactor(SF_7,CRC_EN);				//set spread factor + CRC EN
SetPreamble(PRMBL_8);						//set Preamble
ExtraSetup();								//extra function

LoRa_Mode(STNBY_MODE);
HAL_Delay(10);

}

void initRx(uint8_t messageLength)
{
uint8_t Clear = 0xFF;
uint8_t DioMap = 0x01;
uint8_t RxDone = 0x3F;
uint8_t LengtH = messageLength;
uint8_t read;

init();

LoRaWrite(RegDioMapping1, &DioMap);		//DIO=00,DIO1=00,DIO2=00, DIO3=01 (rx done)
LoRaWrite(RegIrqMaskFlag, &RxDone);		//Open RxDone interrupt & Timeout
LoRaWrite(RegIrqFlags, &Clear);			//Clear Irq
LoRaWrite(RegPayloadLength, &LengtH);	//set payload length
read = LoRaRead(RegFiFoRxBaseAddr);		//read base addr
LoRaWrite(RegFiFoAddPtr, &read);		//RegFifoRxBaseAddr->RegFifoAddPtr
LoRa_Mode(RXCONTIN_MODE);
}

void initTx(uint8_t length)
{
	uint8_t power = 0x87;
	uint8_t map = 0x41;
	uint8_t Clear = 0xFF;
	uint8_t TxDone = 0xF7;
	uint8_t Length = length;
	uint8_t read;

	init();

	LoRaWrite(RegLrPadac, &power); 			 //20 dbm
	LoRaWrite(RegDioMapping1, &map);		 // DIO=01,DIO1=00,DIO2=00, DIO3=01 (tx done)
	LoRaWrite(RegIrqFlags, &Clear);			 //clear flags
	LoRaWrite(RegIrqMaskFlag, &TxDone); 	 //open Tx interrupt
	LoRaWrite(RegPayloadLength, &Length);	 //set payload length
	read = LoRaRead(RegFiFoTxBaseAddr);		 //read base addr
	LoRaWrite(RegFiFoAddPtr, &read);		 //RegFifoRxBaseAddr->RegFifoAddPtr
}




void LoRaReceive(void){

	uint8_t bufferRx[256];
	uint8_t lastAddr;
	uint8_t packetSize;
	uint8_t Clear = 0xFF;
	uint8_t str[100];


	if(HAL_GPIO_ReadPin(DIO0_PORT, DIO0_PIN) == GPIO_PIN_SET)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		memset(&bufferRx, 0x00, 256);
		lastAddr = LoRaRead(RegFiFoRxCurrentAddr);
		LoRaWrite(RegFiFoAddPtr, &lastAddr);
		packetSize = LoRaRead(RegRxNbBytes);
		LoRaBurstRead(RegFiFo, bufferRx, packetSize);
		LoRaWrite(RegIrqFlags, &Clear);
		memcpy(buffer, bufferRx, packetSize);
		buffer[packetSize] = '\0';

		int length = sprintf((char*)str, " %X \r\n", buffer[1]);
		HAL_UART_Transmit(&huart2, str, length, 1000);

	}
}

void LoRaTransmit(uint8_t* bufTx, uint8_t length)
{


	uint8_t Clear = 0xFF;
	uint8_t TxDone = 0xF7;


	LoRaWrite(RegIrqFlags, &Clear);			 //clear flags
	LoRaWrite(RegIrqMaskFlag, &TxDone); 	 //open Tx interrupt

//uint8_t Clear = 0xFF;
LoRa_BurstWrite(RegFiFo, bufTx, length);
LoRa_Mode(TRANSMIT_MODE);

if(HAL_GPIO_ReadPin(DIO0_PORT, DIO0_PIN) == GPIO_PIN_SET)
	{
	LoRaWrite(RegIrqFlags, &Clear);
	LoRa_Mode(STNBY_MODE);
	}


}

