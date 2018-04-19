/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "Central.h"
#include "usart.h"
#include "main.h"
#include "UserInterface.h"
#include "cifXErrors.h"
#include "tim.h"
#include "cifXApplicationDemo.h"
#include "myUsartFunctions.h"
#include "Controller.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId sendTaskHandle;
uint32_t sendTaskBuffer[ 2048 ];
osStaticThreadDef_t sendTaskControlBlock;
osThreadId EthPacketTaskHandle;
uint32_t EthPacketTaskBuffer[ 2048 ];
osStaticThreadDef_t EthPacketTaskControlBlock;
osThreadId EthCyclicTaskHandle;
uint32_t EthCyclicTaskBuffer[ 2048 ];
osStaticThreadDef_t EthCyclicTaskControlBlock;

/* USER CODE BEGIN Variables */
int EthCyclicTask_Ready = 0;


/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void sendTaskFunc(void const * argument);
void EthPacketTaskFunc(void const * argument);
void EthCyclicTaskFunc(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of sendTask */
  osThreadStaticDef(sendTask, sendTaskFunc, osPriorityBelowNormal, 0, 2048, sendTaskBuffer, &sendTaskControlBlock);
  sendTaskHandle = osThreadCreate(osThread(sendTask), NULL);

  /* definition and creation of EthPacketTask */
  osThreadStaticDef(EthPacketTask, EthPacketTaskFunc, osPriorityNormal, 0, 2048, EthPacketTaskBuffer, &EthPacketTaskControlBlock);
  EthPacketTaskHandle = osThreadCreate(osThread(EthPacketTask), NULL);

  /* definition and creation of EthCyclicTask */
  osThreadStaticDef(EthCyclicTask, EthCyclicTaskFunc, osPriorityAboveNormal, 0, 2048, EthCyclicTaskBuffer, &EthCyclicTaskControlBlock);
  EthCyclicTaskHandle = osThreadCreate(osThread(EthCyclicTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* sendTaskFunc function */
void sendTaskFunc(void const * argument)
{

  /* USER CODE BEGIN sendTaskFunc */
	TickType_t xLastWakeTime=xTaskGetTickCount();;
	TickType_t sendTaskPeriod=pdMS_TO_TICKS(10);   //100ms Period
	AS5311_DEVICE *ptAngle1=(AS5311_DEVICE *)(ptCentral->ptAngleHub->angleDevices[0]);
  /* Infinite loop */
  for(;;)
  {
	  /*************100us*********************/
	//  printf("%.3f",HAL_GetTick()/1000.0f);
	  printf("%.3f %.6f %.6f %.6f     %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f  %2.5f  %6.0f %6.0f %6.0f %6.0f %6.0f %6.0f %6.0f %6.0f   %ld %ld  %ld %ld %ld %u %ld %ld %ld\r\n",
	  			   HAL_GetTick()/1000.0f,
	  			   ptCentral->ptSensorData->angle[0],
				   ptAngle1->AngleABZ,
				   ptAngle1->AngleSPI,

				   ptCentral->ADDevice.fChannel[0],
				   ptCentral->ADDevice.fChannel[1],
				   ptCentral->ADDevice.fChannel[2],
				   ptCentral->ADDevice.fChannel[3],
				   ptCentral->ADDevice.fChannel[4],
				   ptCentral->ADDevice.fChannel[5],
				   ptCentral->ADDevice.fChannel[6],
				   ptCentral->ADDevice.fChannel[7],

				   ptCentral->ptSensorData->pressure[0][0],
				   ptCentral->ptSensorData->pressure[0][1],
				   ptCentral->ptSensorData->pressure[1][0],
				   ptCentral->ptSensorData->pressure[1][1],
				   ptCentral->ptSensorData->pressure[2][0],
				   ptCentral->ptSensorData->pressure[2][1],
				   ptCentral->ptSensorData->pressure[3][0],
				   ptCentral->ptSensorData->pressure[3][1],




				  ptCentral->process_time.SensorTime,
				  ptCentral->process_time.EthercatIOTime,
				  ptCentral->process_time.EthercatPacketTime,
				  ptCentral->process_time.taskTime1,
				  ptCentral->process_time.taskTime2,
				  UsartDevice.bufferedTxNum,
				  UsartDevice.lastTxCount,
				  UsartDevice.lastTxTime,
				  ptCentral->ptPressureHub->lastDMATime);

	  vTaskDelayUntil(&xLastWakeTime,sendTaskPeriod);
  }
  /* USER CODE END sendTaskFunc */
}

/* EthPacketTaskFunc function */
void EthPacketTaskFunc(void const * argument)
{
  /* USER CODE BEGIN EthPacketTaskFunc */
	TickType_t xLastWakeTime=xTaskGetTickCount();
	TickType_t EthPacketTaskPeriod=pdMS_TO_TICKS(10);   //10ms Period for command handle
	int32_t lRet;
    lRet = Protocol_SendFirstPacket(&tAppData);
    int32_t c1,c2;
  /* Infinite loop */
    /****100 us****/
  for(;;)
  {
	  while(tAppData.fRunning && lRet == CIFX_NO_ERROR){
		  c1 = TIC();
		/** check and process incoming packets */
		  lRet = EthercatPacketEventHandler();

		/* process Terminal command, if any.*/
		  Usart_TerminalHandler();
		  c2=TIC();
		  ptCentral->process_time.taskTime2 = c2-c1;
		  vTaskDelayUntil(&xLastWakeTime,EthPacketTaskPeriod);
		}
		/** remove calling of App_IODataHandler, because we don't have valid IO Data any more */
	  Ethercat_DeInit();
  }
  /* USER CODE END EthPacketTaskFunc */
}

/* EthCyclicTaskFunc function */
void EthCyclicTaskFunc(void const * argument)
{
  /* USER CODE BEGIN EthCyclicTaskFunc */
	TickType_t xLastWakeTime=xTaskGetTickCount();
	TickType_t EthCyclicTaskPeriod=pdMS_TO_TICKS(1);   //1ms Period
	CENTRAL *ptCentral=&gCentral;
	int32_t c1,c2,c3,c4;
  /* Infinite loop */
	/*****500 us******/
  for(;;)
  {
	  c1 = TIC();
	  /*updateData part: 400 us
	   *Update Sensor: 250 us
	   *		1.Pressure DMA 8 channels	 200 us
	   *		2.AD board 8 channels		  40 us
	   *		3.Angle blocking 4 channels  100 us
	   *
	   *EthercatIO: 150 us*/
	  ptCentral->updateData(ptCentral);

	  c2 = TIC();

	  /*control according to commands,50us*/
	  ptCentral->control(ptCentral);

	  c3 = TIC();

	  /*apply control outcome, 50us*/
	  ptCentral->applyControl(ptCentral);

	  c4=TIC();
	  ptCentral->process_time.taskTime1 = c4-c1;

	//  printf("Time:%ld %ld %ld\r\n",c2-c1,c3-c2,c4-c3);
	  vTaskDelayUntil(&xLastWakeTime,EthCyclicTaskPeriod);
  }
  /* USER CODE END EthCyclicTaskFunc */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
