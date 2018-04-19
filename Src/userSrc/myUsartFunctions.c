/*
 * myUsartFunctions.c
 *
 *  Created on: Apr 10, 2018
 *      Author: 402072495
 */

#include "cifXApplicationDemo.h"
#include "TerminalHandler.h"
#include "cmsis_os.h"
#include "myUsartFunctions.h"
#include "usart.h"
#include "string.h"
#include <stdarg.h>
#include <stdio.h>
#include "main.h"
UART_DEVICE UsartDevice;




/*This file enables to use printf() to output strings to a uart:
 * 1.None blocking Tx and Rx using DMA
 * 2.Tx has Buffers without loss of transmission data
 * 3.Rx accept variable size
 *
 *
 * Usage:
 * 1.configure as below.
 * 2.For transmitting, use printf() as usual.
 * 3.For receiving, received string is automatically updated in UsartDevice.RxBuf
 *
 * Stm32CubeMx configuration:
 * Usart configuration: Tx DMA  Rx	DMA Enable Interrupt
 * file location:
 * 1. put my_UsartInit() in initialization part
 * 2. put HAL_UART_RxIdleCallback() in ISR for receiving data
 * 3. put Usart_TerminalHandler() in polling loop for processing data
 *
 */

/*Put this function in a loop for polling*/
void Usart_TerminalHandler()
{
	char          szCmd[50]; /** note, in sscanf format string below, command length is hard coded */
	unsigned int  uiArgv[3];
	int           iArgc = 0;
    int commandNum;

    if(UsartDevice.Received == 1){

    /*get commands from RxBuffer*/
	iArgc=sscanf((char *)UsartDevice.RxBuf, "%6s %x %x %x", &szCmd[0], &uiArgv[0], &uiArgv[1], &uiArgv[2]);
	commandNum=Term_MatchTerminalCommand(&szCmd[0]);

	/*Process commands*/
	TerminalCommandHandler(&tAppData, commandNum, iArgc, &uiArgv[0]);

	/*clear Recived flag and Rxbuffer*/
	 UsartDevice.Received = 0;
	 memset(UsartDevice.RxBuf,0,UsartDevice.countRxBuf);

	 /*get ready for the next receive*/
	 HAL_UART_Receive_DMA(UsartDevice.huart, UsartDevice.RxBuf, UART_RX_BUF_SIZE-1);

    }
}

/*put this function in the main.c for initilization*/
void my_UsartInit(UART_HandleTypeDef *huart)
{
	 memset(&UsartDevice,0,sizeof(UsartDevice));
	 UsartDevice.huart = huart;

	 /*get ready for receive*/
	 HAL_UART_Receive_DMA(UsartDevice.huart, UsartDevice.RxBuf, UART_RX_BUF_SIZE-1);

	 /*Enable USART_Rx IDLE Detection to stop USART1_Rx_DMA*/
	 __HAL_UART_ENABLE_IT(UsartDevice.huart, UART_IT_IDLE);

}


/*put this function in stm32f7xx_it.c as below
void USART3_IRQHandler(void)
{
  HAL_UART_RxIdleCallback(UsartDevice.huart);
  HAL_UART_IRQHandler(&huart3);
}
*/
void HAL_UART_RxIdleCallback(UART_HandleTypeDef *huart)
{
	 UsartDevice.countRxBuf = 0;
	 uint32_t tmp_flag = __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE);
	 uint32_t tmp_it_source = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE);

	 /* UART RX Idle interrupt*/
	 if((tmp_flag != RESET) && (tmp_it_source != RESET)){

		 /*Clear Idle Flag*/
		__HAL_UART_CLEAR_IDLEFLAG(huart);

		if(huart->hdmarx != NULL){
			/* Determine how many items of data have been received */
			UsartDevice.countRxBuf = huart->RxXferSize -__HAL_DMA_GET_COUNTER(huart->hdmarx);

			HAL_DMA_Abort(huart->hdmarx);

			huart->RxXferCount = 0;

			/* Disable RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts*/
			CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));
			CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

			huart->RxState = HAL_UART_STATE_READY;

			/*inform polling process function in the controlling task*/
			UsartDevice.Received = 1;
		}
	 }
}

/*Redirect printf() to use HAL_USART_Transmit_DMA() by implementing _write function who is "weak".
 *Every printf() call would store one output string in TxBuf[producerTxBufNum]
 *This custom _write would cause printf to output the string to a Tx buffer, instead of directly output*/
int _write(int file, char *pSrc, int len)
{
	uint8_t *pDes=UsartDevice.TxBuf[UsartDevice.producerTxBufNum];

	/*store the string to next buffer*/
	memcpy(pDes,pSrc,len);
	*(pDes+len)='\0';
	UsartDevice.countTxBuf[UsartDevice.producerTxBufNum] = strlen((const char*)pDes);

	/*add one bufferedTxNum, recording how many buffered strings that haven't been sent*/
	UsartDevice.bufferedTxNum++;

	/*Try to send just buffered string if this is the only one*/
	if(UsartDevice.bufferedTxNum == 1){
		HAL_UART_Transmit_DMA(UsartDevice.huart,pDes,UsartDevice.countTxBuf[UsartDevice.producerTxBufNum]);
		UsartDevice.TxStart = TIC();
	}
	/*move producerTxBufNum forward*/
	UsartDevice.producerTxBufNum++;
	UsartDevice.producerTxBufNum%=UART_TX_BUF_NUM;

	/*Buffered term full, wait for consumer to reduce producerTxBufNum*/
	while(UsartDevice.bufferedTxNum > (UART_TX_BUF_NUM-2)){
		//Danger! May block the main program continuously !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//This waiting mechanism is to take care of the high frequency output within a short interval during the Ethercat Initialization
		//If the producer is always quicker than consumer, for example a high frequency output ,this function would block the program continuously
	};

	return len;
}


/*this function would overwrite HAL's weak HAL_UART_TxCpltCallback*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	 /*update information*/
	 UsartDevice.TxEnd = TIC();
	 UsartDevice.lastTxTime = UsartDevice.TxEnd - UsartDevice.TxStart;
	 UsartDevice.lastTxCount = UsartDevice.countTxBuf[UsartDevice.consumerTxBufNum];

	/*One consumption done. move consumer forward*/
	UsartDevice.consumerTxBufNum++;
	UsartDevice.consumerTxBufNum%=UART_TX_BUF_NUM;

	/*reduce one bufferedTxNum*/
	 UsartDevice.bufferedTxNum--;



	/*If it is still positive, go on consume next*/
	if(UsartDevice.bufferedTxNum>0){
		UsartDevice.TxStart = TIC();
		uint8_t *px = &UsartDevice.TxBuf[UsartDevice.consumerTxBufNum][0];
		HAL_UART_Transmit_DMA(UsartDevice.huart,px,UsartDevice.countTxBuf[UsartDevice.consumerTxBufNum]);
	}

}




