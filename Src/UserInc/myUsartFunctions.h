/*
 * myUsartFunctions.h
 *
 *  Created on: Apr 10, 2018
 *      Author: 402072495
 */
#ifndef USERINC_MYUSARTFUNCTIONS_H_
#define USERINC_MYUSARTFUNCTIONS_H_



#include "stm32f7xx_hal.h"

#define UART_TX_BUF_SIZE 500
#define UART_RX_BUF_SIZE 60
#define COMMAND_SIZE 30

#define UART_TX_BUF_NUM	10

enum  {
  OneJoint_UNKNOWN      = 0x00,
  OneJoint_VOLTAGE,
  OneJoint_PRESSURE,
  OneJoint_KP,
  OneJoint_KI,
  OneJoint_KD,
  OneJoint_STIFFNESS,
  OneJoint_QUIT,
  OneJoint_START,
  OneJoint_ZERO,
  OneJoint_FLOW,
  OneJoint_START_USART,
  OneJoint_STOP_USART,
  OneJoint_POSITION,
  OneJoint_FEEDBACK,
  OneJoint_PID_ILim,
  OneJoint_PID_ULim,
  OneJoint_LAST     /** just for determining number of commands in this list */
};
typedef struct APP_TERMINAL_CMD_Ttag {
  int iCode;
  char szString[50];
  char szHelp[50];
} APP_TERMINAL_CMD_T;

typedef struct UART_DEVICE_STRUCT{

	UART_HandleTypeDef *huart;

	uint8_t TxBuf[UART_TX_BUF_NUM][UART_TX_BUF_SIZE];  /*TxBuffer*/
	uint16_t consumerTxBufNum;
	uint16_t producerTxBufNum;
	uint16_t bufferedTxNum;
	uint16_t countTxBuf[UART_TX_BUF_NUM];

	uint8_t RxBuf[UART_RX_BUF_SIZE];
	uint8_t szCmd[COMMAND_SIZE];
	float	uiArgv[3];
	int     iArgc;
    int usartCommandCode;
	uint16_t countRxBuf;

	uint16_t Received;

	int32_t TxStart;
	int32_t TxEnd;

	int32_t lastTxTime;
	uint32_t lastTxCount;

}UART_DEVICE;
extern UART_DEVICE UsartDevice;

void my_UsartInit(UART_HandleTypeDef *huart);			/*put in the Initialization*/
void HAL_UART_RxIdleCallback(UART_HandleTypeDef *huart);/*put in the ISR*/
void Usart_TerminalHandler(void);						/*put In the polling loop*/

#endif /* USERINC_MYUSARTFUNCTIONS_H_ */
