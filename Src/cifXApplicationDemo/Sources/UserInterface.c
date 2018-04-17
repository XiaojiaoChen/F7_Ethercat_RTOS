/**************************************************************************************
Exclusion of Liability for this demo software:
  The following software is intended for and must only be used for reference and in an
  evaluation laboratory environment. It is provided without charge and is subject to
  alterations. There is no warranty for the software, to the extent permitted by
  applicable law. Except when otherwise stated in writing the copyright holders and/or
  other parties provide the software "as is" without warranty of any kind, either
  expressed or implied.
  Please refer to the Agreement in README_DISCLAIMER.txt, provided together with this file!
  By installing or otherwise using the software, you accept the terms of this Agreement.
  If you do not agree to the terms of this Agreement, then do not install or use the
  Software!
 **************************************************************************************/

/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

 ***************************************************************************************
  $Id: UserInterface.c 3234 2017-07-19 12:22:45Z dirk $

  Description:
    The functions defined in this C-Module are called from the cifXApplicationDemo.
    These functions are protocol independent.
    This module must be adapted to the used Host System. I.e. it is hardware dependent
    and acts as an Hardware Abstraction Layer.
    In this implementation, STM32 HAL functions are used.


  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2017-02-16  initial version

 **************************************************************************************/

#include "main.h"
#include "cifXApplicationDemo.h"
#include "UserInterface.h"
#include "OS_Dependent.h"
#include <stdio.h>
#include "usart.h"
#include "tim.h"


/** STATUS LEDS ****************************/
#define UI_STAT_LED_STATUS_MSK  0x01 /** LED P411 */
#define UI_STAT_LED_DATA_MSK    0x02 /** LED P410 */
#define UI_STAT_LED_ERROR_MSK   0x04 /** LED P409 */
#define UI_STAT_LED_ALARM_MSK   0x08 /** LED P408 */



static uint8_t  g_cStatusLed=0;  /* status LED register */
extern GPIO_TypeDef* GPIO_PORT[];
extern const uint16_t GPIO_PIN[];


UI_RESULT_E UserInterface_updateStatLed(void);

void (*g_pfTimerCallback)(void* pPrm)=NULL;
void *g_pTimerPrm=NULL;


/* Prescaler declaration */
__IO uint32_t uwPrescalerValue = 0;


/**********************************************************************************//**
  Initializes the IO hardware
  \return         eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_init(void){

	/* Configure LED1, LED2 and LED3 */
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);

	return UI_OK;
}


/**********************************************************************************//**
  Function puts output data to LEDs
  \param[in]      ulData cyclic output data to be displayed UI_OUTPUT_BITS wide
  \return         eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_putOutData(uint32_t ulData){

	/*due to limited number of available LEDs on Nucelo board, map only 2 data bits to two LEDs*/
	HAL_GPIO_WritePin(GPIO_PORT[LED1], GPIO_PIN[LED1], ulData & 0x00000008 ? GPIO_PIN_SET:GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_PORT[LED2], GPIO_PIN[LED2], ulData & 0x00000800 ? GPIO_PIN_SET:GPIO_PIN_RESET);

	return UI_OK;
}


/**********************************************************************************//**
  Function puts output data to the console
  \param[in]      ulData cyclic output data to be displayed UI_OUTPUT_BITS wide
  \return         eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_putStatLed(uint32_t ulData){
	return UI_OK;
}


/**********************************************************************************//**
  Function set the defined status LED "on"
  \param[in]     specifies the status LED
  \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_putStatLedOn(UI_STATUS_LED_TYPE_E eStatusLed){
	switch (eStatusLed) {
	case UI_STAT_LED_ALARM:
		g_cStatusLed |= UI_STAT_LED_ALARM_MSK;
		break;
	case UI_STAT_LED_ERROR:
		g_cStatusLed |= UI_STAT_LED_ERROR_MSK;
		break;
	case UI_STAT_LED_STATUS:
		g_cStatusLed |= UI_STAT_LED_STATUS_MSK;
		break;
	case UI_STAT_LED_DATA:
		g_cStatusLed |= UI_STAT_LED_DATA_MSK;
		break;
	default:
		return UI_UNKNOWN_STAT_LED;
	}

	UserInterface_updateStatLed();
	return UI_OK;
}

UI_RESULT_E UserInterface_updateStatLed(void){

	/* map only the ALARM and ERROR flags to one LED (or'ed) , other status flags are ignored due to limited number of status LEDs*/
	if(g_cStatusLed & (UI_STAT_LED_ERROR_MSK | UI_STAT_LED_ALARM_MSK)){
		HAL_GPIO_WritePin(GPIO_PORT[LED3], GPIO_PIN[LED3], GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(GPIO_PORT[LED3], GPIO_PIN[LED3], GPIO_PIN_RESET);
	}

	return UI_OK;
}


/**********************************************************************************//**
  Function set the defined status LED "off"
  \param[in]     specifies the status LED
  \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_putStatLedOff(UI_STATUS_LED_TYPE_E eStatusLed){
	switch (eStatusLed) {
	case UI_STAT_LED_ALARM:
		g_cStatusLed &= ~UI_STAT_LED_ALARM_MSK;
		break;
	case UI_STAT_LED_ERROR:
		g_cStatusLed &= ~UI_STAT_LED_ERROR_MSK;
		break;
	case UI_STAT_LED_STATUS:
		g_cStatusLed &= ~UI_STAT_LED_STATUS_MSK;
		break;
	case UI_STAT_LED_DATA:
		g_cStatusLed &= ~UI_STAT_LED_DATA_MSK;
		break;
	default:
		return UI_UNKNOWN_STAT_LED;
	}

	UserInterface_updateStatLed();
	return UI_OK;
}



/**********************************************************************************//**
  Function returns process data
  \param[in]
  \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
uint32_t UserInterface_getInData(void){
	uint32_t ulTempInput=0;

	ulTempInput= BSP_PB_GetState(BUTTON_USER);

	return ((uint32_t)ulTempInput);
}




/**********************************************************************************//**
  Function returns rotary switch input
  since Nucleo-144 features just one user push button but no rotary switches, we
  "emulate" rotary switch input by shifting the bush button bit
  \param[in]
  \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
uint32_t UserInterface_getRotary(void){

	uint32_t ulTempInput=0;

	ulTempInput= (BSP_PB_GetState(BUTTON_USER) << 2) + (BSP_PB_GetState(BUTTON_USER) << 4 << 3);

	return((uint32_t)ulTempInput);
}


uint8_t UserInterface_getRotary0(void){

	uint32_t ulTempInput=0;

	ulTempInput= BSP_PB_GetState(BUTTON_USER) << 2;

	return((uint8_t)ulTempInput);
}


uint8_t UserInterface_getRotary1(void){

	uint32_t ulTempInput=0;

	ulTempInput= BSP_PB_GetState(BUTTON_USER) << 3;

	return((uint8_t)ulTempInput);
}


/**********************************************************************************//**
  Function returns diagnosis DIP switch
  \param[in]
  \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_DIAG_T UserInterface_getDiag(void){

	UI_DIAG_T tDiag={{0}};

	tDiag.fAlarm0=BSP_PB_GetState(BUTTON_USER);
	tDiag.fError0=BSP_PB_GetState(BUTTON_USER);

	return tDiag;
}


/*
UI_RESULT_E UserInterface_getTemp(uint32_t *ulData);
 */


/**********************************************************************************//**
  Function returns diagnosis DIP switch
  \param[in]
  \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
uint8_t     UserInterface_getDiagAlarm0(void){
	uint8_t ulTempInput=0;

	ulTempInput= BSP_PB_GetState(BUTTON_USER);

	return ((uint8_t)ulTempInput);
}

/**********************************************************************************//**
  Function returns diagnosis DIP switch
  \param[in]
  \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
uint8_t     UserInterface_getDiagError0(void){
	uint8_t ulTempInput=0;

	ulTempInput= BSP_PB_GetState(BUTTON_USER);

	return ((uint8_t)ulTempInput);
}



/*****************************************************************************/
/*! registers callback function
 *   \param eClbType callback type
 *   \param pfnEventClb callback function pointer
 *   \param pPrm parameters
 *   \return UI_OK on success                                                 */
/*****************************************************************************/
UI_RESULT_E UserInterface_registerCallback(UI_CALLBACK_TYPE_E eClbType, void(*pfnEventClb)(void* pPrm), void* pPrm)
{
	switch(eClbType){
	case UI_CB_TIMER:
		g_pfTimerCallback = pfnEventClb;
		g_pTimerPrm = pPrm;
		break;
	default:
		return UI_UNKNOWN_CALLBACK_TYPE;
	}
	return UI_OK;
}


/*****************************************************************************/
/*! Enable callback functions
 *   \return UI_OK on success                                                 */
/*****************************************************************************/
UI_RESULT_E UserInterface_enableCallbacks(void)
{
	//  NX51_VIC_SetIrqVector(0, 2, UserInterface_timerIsr);
	//  NX51_VIC_EnableIrqSources(1 << 2);  /** TIMER1 IRQ*/
	return UI_OK;
}


/*****************************************************************************/
/*! Disable callback functions
 *   \return UI_OK on success                                                 */
/*****************************************************************************/
UI_RESULT_E UserInterface_disableCallbacks(void)
{
	//  NX51_VIC_DisableIrqSources(1 << 2);  /** TIMER1 IRQ*/
	return UI_OK;
}



int UserInterface_kbhit(void){
	return __HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE);
}


void UserInterface_Sleep(uint32_t ulSleepTimeMs){
	HAL_Delay(ulSleepTimeMs);
}

