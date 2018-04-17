/*
 * myUsartFunctions.h
 *
 *  Created on: Apr 10, 2018
 *      Author: 402072495
 */
#ifndef USERINC_MYUSARTFUNCTIONS_H_
#define USERINC_MYUSARTFUNCTIONS_H_



#include "stm32f7xx_hal.h"

#define UART_TX_BUF_SIZE 200
#define UART_RX_BUF_SIZE 300

#define UART_TX_BUF_NUM	5

typedef struct UART_DEVICE_STRUCT{

	UART_HandleTypeDef *huart;

	uint8_t TxBuf[UART_TX_BUF_NUM][UART_TX_BUF_SIZE];  /*TxBuffer*/
	uint16_t consumerTxBufNum;
	uint16_t producerTxBufNum;
	uint16_t bufferedTxNum;
	uint16_t countTxBuf[UART_TX_BUF_NUM];

	uint8_t RxBuf[UART_RX_BUF_SIZE];
	uint16_t countRxBuf;

	uint16_t Received;

}UART_DEVICE;
extern UART_DEVICE UsartDevice;

void my_UsartInit(UART_HandleTypeDef *huart);			/*put in the Initialization*/
void HAL_UART_RxIdleCallback(UART_HandleTypeDef *huart);/*put in the ISR*/
void Usart_TerminalHandler(void);						/*put In the polling loop*/

#endif /* USERINC_MYUSARTFUNCTIONS_H_ */
