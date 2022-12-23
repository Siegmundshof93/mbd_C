#ifndef IMU_H_

#define IMU_H_


#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "main.h"


#define CS_PIN GPIO_PIN_4
#define CS_PORT GPIOA
#define CS_ON HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
#define CS_OFF HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_RESET);

#define LED_PIN GPIO_PIN_4
#define LED_PORT GPIOB
#define LED_ON HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
#define LED_OFF HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);

#define RESET_PIN GPIO_PIN_0
#define RESET_PORT GPIOB
#define RESET_ON HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);
#define RESET_OFF HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);

#define DIO0_PIN GPIO_PIN_1
#define DIO0_PORT GPIOB


#define TRANSMIT_TIMEOUT	2000
#define RECEIVE_TIMEOUT		2000

//--------- MODES ---------//
#define SLEEP_MODE				0
#define	STNBY_MODE				1
#define TRANSMIT_MODE			3
#define RXCONTIN_MODE			5
#define RXSINGLE_MODE			6

//------- BANDWIDTH -------//
#define BW_7_8KHz					0
#define BW_10_4KHz				1
#define BW_15_6KHz				2
#define BW_20_8KHz				3
#define BW_31_25KHz				4
#define BW_41_7KHz				5
#define BW_62_5KHz				6
#define BW_125KHz					7
#define BW_250KHz					8
#define BW_500KHz					9

//------ CODING RATE ------//
#define CR_4_5						1
#define CR_4_6						2
#define CR_4_7						3
#define CR_4_8						4

//--- SPREADING FACTORS ---//
#define SF_7							7
#define SF_8							8
#define SF_9							9
#define SF_10							10
#define SF_11  						11
#define SF_12							12

//------ POWER GAIN ------//
#define POWER_11db				0xF6
#define POWER_14db				0xF9
#define POWER_17db				0xFC
#define POWER_20db				0xFF

//------- REGISTERS -------//
#define RegFiFo								0x00
#define RegOpMode							0x01
#define RegFrMsb							0x06
#define RegFrMid							0x07
#define RegFrLsb							0x08
#define RegPaConfig						0x09
#define RegOcp								0x0B
#define RegLna								0x0C
#define RegFiFoAddPtr					0x0D
#define RegFiFoTxBaseAddr			0x0E
#define RegFiFoRxBaseAddr			0x0F
#define RegFiFoRxCurrentAddr	0x10
#define RegIrqMaskFlag					0x11
#define RegIrqFlags						0x12
#define RegRxNbBytes					0x13
#define LR_RegModemStat					0x18
#define RegPktRssiValue				0x1A
#define	RegModemConfig1				0x1D
#define RegModemConfig2				0x1E
#define RegSymbTimeoutL				0x1F
#define RegPreambleMsb				0x20
#define RegPreambleLsb				0x21
#define RegPayloadLength			0x22
#define RegHopPeriod				0x24
#define RegSync						0x39
#define RegDioMapping1				0x40
#define RegDioMapping2				0x41
#define RegVersion						0x42
#define	RegLrPadac					0x4D


//------ LORA STATUS ------//
#define LORA_OK							200
#define LORA_NOT_FOUND			404
#define LORA_LARGE_PAYLOAD	413
#define LORA_UNAVAILABLE		503
//------ FREQUENCY ------//
#define FREQ_434				 434
//------ CURRENT ------//
#define CURR_100                 0x64//100mA
//------ LNA GAIN ------//
#define MAX_GAIN 				0x23
//------ PREAMBLE ------//
#define PRMBL_10                0xA
#define PRMBL_8					0x8
//-------CRC------------//
#define CRC_EN 					0x01
#define CRC_DIS					0x00




//prototype functions//
void LoRaWrite(uint8_t, uint8_t*);
void LoRa_BurstWrite(uint8_t, uint8_t* , uint8_t);
void LoRaBurstRead(uint8_t, uint8_t*, uint8_t);
uint8_t LoRaRead_hw(void);
uint8_t LoRaRead(uint8_t);
void LoRa_Mode(int);
void SetSpreadFactor (int, int);
void SetFrequency(int);
void SetPower (uint8_t);
void SetOCP (uint8_t);
void SetLNA(uint8_t);
void ExtraSetup(void);
void SetBandWcrcRate(uint8_t, uint8_t);
void SetPreamble(uint8_t);
void SetDIO(uint8_t);
void preInit(void);
void init(void);
void initRx(uint8_t);
void initTx(uint8_t);
void LoRaReceive(void);
void LoRaTransmit(uint8_t*, uint8_t);

#endif
