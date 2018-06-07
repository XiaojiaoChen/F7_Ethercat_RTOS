/*
 * myUsartFunctions.c
 *
 *  Created on: Apr 10, 2018
 *      Author: 402072495
 */

#include "cifXApplicationDemo.h"
#include "cmsis_os.h"
#include "myUsartFunctions.h"
#include "usart.h"
#include "string.h"
#include <stdarg.h>
#include <stdio.h>
#include "main.h"
#include "SystemPackets.h"
#include "trajectoryGeneration.h"
#include "Central.h"
#include "myPID.h"
#include "OS_Dependent.h"
UART_DEVICE UsartDevice;

uint8_t usartLocalRxBuffer[UART_RX_BUF_SIZE];
extern uint16_t start_transmission;

APP_TERMINAL_CMD_T g_tTerminalCommands[] =
{
  {OneJoint_VOLTAGE,         "v",    "Change Voltage 0"},
  {OneJoint_PRESSURE,        "p",      "write var val"},
  {OneJoint_KP,       "kp",  "hardware info"},
  {OneJoint_KI,  "ki",      "display input data image"},
  {OneJoint_KD, "kd",     "display output data image"},
  {OneJoint_STIFFNESS,         "k",     "display variables"},
  {OneJoint_QUIT,         "s",    "returns from main function"},
  {OneJoint_START,         "g",    "returns from main function"},
  {OneJoint_ZERO,         "z",    "returns from main function"},
  {OneJoint_FLOW,         "f",    "returns from main function"},
  {OneJoint_START_USART,         "(",    "returns from main function"},
  {OneJoint_STOP_USART,         ")",    "returns from main function"},
  {OneJoint_POSITION,         "a",    "returns from main function"},
  {OneJoint_FEEDBACK,         "t",    "returns from main function"},
  {OneJoint_PID_ILim,         "ilim",    "returns from main function"},
  {OneJoint_PID_ULim,         "ulim",    "returns from main function"},
};

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

void TerminalCommandHandler()
{
  float   val=0;
  float   angle_temp=0;
  uint32_t  tduration;
  int32_t c1,c2;

  c1 = TIC();
  /*get commands from RxBuffer*/
   UsartDevice.iArgc=sscanf((char *)UsartDevice.RxBuf, "%s %f %f %f", UsartDevice.szCmd, &(UsartDevice.uiArgv[0]),  &(UsartDevice.uiArgv[1]),  &(UsartDevice.uiArgv[2]));
   val = UsartDevice.uiArgv[0];
  UsartDevice.usartCommandCode = OneJoint_UNKNOWN;
   for(int i=0; i<(OneJoint_LAST-1); i++){
     if( 0 == strcmp((const char *)(UsartDevice.szCmd), (const char *)(&g_tTerminalCommands[i].szString[0]))){
     	UsartDevice.usartCommandCode = g_tTerminalCommands[i].iCode;
     	break;
     }
   }

    switch(UsartDevice.usartCommandCode){
    case OneJoint_VOLTAGE:
    	if(val>=0 && val<=15 && UsartDevice.uiArgv[1]>=0 && UsartDevice.uiArgv[1]<=10)
    		ptCentral->LLsetVoltage(ptCentral,UsartDevice.uiArgv[0],UsartDevice.uiArgv[1]);
      break;

    case OneJoint_PRESSURE:
    	ptCentral->LLsetPSource(ptCentral,val);
      break;

    case OneJoint_KP:
      setKp(&(ptCentral->ptControlHub->ptController[0]->pid),val);
      break;

    case OneJoint_KI:
    	setKi(&(ptCentral->ptControlHub->ptController[0]->pid),val);
      break;

    case OneJoint_KD:
    	setKd(&(ptCentral->ptControlHub->ptController[0]->pid),val);
      break;

    case OneJoint_STIFFNESS:
    	ptCentral->ptNominalData->stiffness[0] = val;
      break;

    case   OneJoint_QUIT:
    	ptCentral->LLsetPSource(ptCentral,0);
    	ptCentral->ptActuatorHub->actuator[0][0]->act(ptCentral->ptActuatorHub->actuator[0][0],5.1);
    	ptCentral->ptActuatorHub->actuator[0][1]->act(ptCentral->ptActuatorHub->actuator[0][1],5.1);
    	ptCentral->gogogo = 0;
    	ptCentral->ptControlHub->ptController[0]->state.positionFeedbackFlag = 0;
      break;

    case OneJoint_START:
    	ptCentral->gogogo = 1;
          break;

    case OneJoint_ZERO:
          break;
    case OneJoint_FLOW:
          break;

    case OneJoint_START_USART:
    	start_transmission = 1;
          break;

    case OneJoint_STOP_USART:
    	start_transmission = 0;
          break;

    case OneJoint_POSITION:
    	if(UsartDevice.iArgc >= 3)
    		ptCentral->positionTrajectory[0].lineType = UsartDevice.uiArgv[1];
    	if(ptCentral->positionTrajectory[0].lineType>=5 || ptCentral->positionTrajectory[0].lineType<0)
    		ptCentral->positionTrajectory[0].lineType = TRAJ_GEN_STEP_SCURVE;

    	if(UsartDevice.iArgc == 4)
    		ptCentral->positionTrajectory[0].vaverage = UsartDevice.uiArgv[2];

    	angle_temp = UsartDevice.uiArgv[0];
		if(angle_temp>-1.5 && angle_temp<1.5)
		{
			tduration =(angle_temp-ptCentral->ptSensorData->angle[0])*1000/ptCentral->positionTrajectory[0].vaverage;
			if(tduration<0){
				tduration=-tduration;
			}
			UpdateTraj(&(ptCentral->positionTrajectory[0]),
					angle_temp,
					HAL_GetTick(),
					(uint32_t)tduration,
					(TRAJ_GEN_CurveTypeDef)(ptCentral->positionTrajectory[0].lineType));

		}
          break;
    case OneJoint_FEEDBACK:
    	ptCentral->ptControlHub->ptController[0]->state.positionFeedbackFlag = 1;
          break;

    case OneJoint_PID_ILim:
    	setIlim(&(ptCentral->ptControlHub->ptController[0]->pid),val);
             break;


    case OneJoint_PID_ULim:
    	setUlim(&(ptCentral->ptControlHub->ptController[0]->pid),val);
             break;


    case OneJoint_UNKNOWN:
      break;

    default:
      break;
    }
    c2=TIC();
    ptCentral->process_time.terminalCommandTime = c2-c1;
 //   printf("terminal command time: %ld\r\n",c2-c1);

}


/*Put this function in a loop for polling*/
void Usart_TerminalHandler()
{
	/*Only process with idle receiving detection*/
	if (UsartDevice.Received == 1) {

		/* Stop UART DMA Rx request if ongoing */
		if ((UsartDevice.huart->RxState == HAL_UART_STATE_BUSY_RX) && (HAL_IS_BIT_SET(UsartDevice.huart->Instance->CR3, USART_CR3_DMAR))) {
			CLEAR_BIT(UsartDevice.huart->Instance->CR3, USART_CR3_DMAR);

			/* Abort the UART DMA Rx channel */
			if (UsartDevice.huart->hdmarx != NULL) {
				/* Determine how many items of data have been received */
				UsartDevice.countRxBuf = UsartDevice.huart->RxXferSize - __HAL_DMA_GET_COUNTER(UsartDevice.huart->hdmarx);
				UsartDevice.huart->RxXferCount = 0;

				/*Abort DMA*/
				HAL_DMA_Abort(UsartDevice.huart->hdmarx);
			}

			/* Disable RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts */
			CLEAR_BIT(UsartDevice.huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));
			CLEAR_BIT(UsartDevice.huart->Instance->CR3, USART_CR3_EIE);

			/* At end of Rx process, restore huart->RxState to Ready */
			UsartDevice.huart->RxState = HAL_UART_STATE_READY;
		}

		/*Process commands*/
		TerminalCommandHandler();

		/*clear Recived flag*/
		UsartDevice.Received = 0;

		/*clear buffer*/
		memset(UsartDevice.szCmd, 0, sizeof(UsartDevice.szCmd));
		memset(UsartDevice.RxBuf, 0, UsartDevice.countRxBuf);
		UsartDevice.countRxBuf = 0;
	}

	//Always try to start a new reception
	HAL_UART_Receive_DMA(UsartDevice.huart, UsartDevice.RxBuf, UART_RX_BUF_SIZE - 1);

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
	 uint32_t tmp_flag = __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE);
	 uint32_t tmp_it_source = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE);

	 /* UART RX Idle interrupt*/
	 if((tmp_flag != RESET) && (tmp_it_source != RESET)){

		 /*Clear Idle Flag*/
		__HAL_UART_CLEAR_IDLEFLAG(huart);

		/*receive flag*/
		UsartDevice.Received = 1;

		/*We stop the DMA in the polling task, not here, since some data are still on the fly now*/


	}

}

/*Redirect printf() by implementing (weak) _write function.
 *Every printf() call would store the output string in TxBuf[], ready for Usart DMA output instead of directly output*/
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
		//This waiting mechanism is to take care of the high frequency output within a short period during the Ethercat Initialization
		//If the producer is always quicker than consumer, for example a high frequency output ,this function would block the program permanently
	};
	return len;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//printf("RxCplCall_Test\r\n");
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




