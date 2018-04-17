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
  $Id: cifXApplicationDemo.h 2639 2017-02-08 09:26:08Z Jin $:

  Description:
    cifX Application Demo header file

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file  cifXApplicationDemo.h
*   cifX Application Demo header file                                        */
/*****************************************************************************/

#ifndef COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_CIFXAPPLICATIONDEMO_H_
#define COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_CIFXAPPLICATIONDEMO_H_


#include <stdio.h>                  /** Include C standard library input/output header */
#include <string.h>           
                              
#include "rcX_Public.h"       
                              
#include "cifXErrors.h"             /** Include cifX driver API error definition */
#include "cifXUser.h"               /** Include cifX driver API definition       */
#include "rcX_User.h"               /** rcX definition file for the rcX operating system */
                             
#include "UserInterface.h"

/*****************************************************************************/
/*! typedef                                                                  */
/*****************************************************************************/
typedef struct APP_INPUT_DATA_Ttag {
  uint8_t bApp_Dip_Inputdata;       /** DIP 1:8 switch  */
  uint8_t bApp_CycleCnt;            /** Cycle counter  */
  uint8_t bApp_Alarm0_Code;         /** Rotary 0 switch */
  uint8_t bApp_Error0_Code;         /** Rotary 1 switch */
  uint8_t bApp_Alarm0;              /** DIP 9 switch */
  uint8_t bApp_Error0;              /** DIP 10 switch */
  uint8_t bApp_Uart_Inputdata0;     /** Uart changeable variables */
  uint8_t bApp_Uart_Inputdata1;     /** Uart changeable variables */
  uint8_t bApp_Alarm1;              /** Uart changeable variables */
  uint8_t bApp_Error1;              /** Uart changeable variables */
} APP_INPUT_DATA_T;


typedef struct APP_OUTPUT_DATA_Ttag {
  uint32_t ulApp_Outputdata0;
} APP_OUTPUT_DATA_T;


typedef struct APP_VAR_DATA_Ttag {
  uint8_t bApp_Diag0;
} APP_VAR_DATA_T;


typedef struct APP_DATA_Ttag {
  int fRunning;
  int fOutputDataValid;

  CIFX_PACKET tPkt;       /** Buffer for mailbox packets, dual usage send and receive */
  uint32_t ulSendPktCnt;  /** global send packet counter*/

  CIFXHANDLE hChannel[2];
  CHANNEL_INFORMATION tChannelInfo[2];
  BOARD_INFORMATION tBoardInfo;

  APP_INPUT_DATA_T tInputData;
  APP_OUTPUT_DATA_T tOutputData;
  APP_VAR_DATA_T tVarData;

} APP_DATA_T;


/*****************************************************************************/
/*! FUNCTION PROTOTYPES                                                      */
/*****************************************************************************/
extern uint32_t Protocol_PacketHandler( APP_DATA_T *ptAppData );
extern uint32_t Protocol_SendFirstPacket(APP_DATA_T *ptAppData);

int App_CifXApplicationDemo(void);
void App_IODataHandler(void *pPrm);
void App_Selftest(void);
void App_ReadBoardInfo(const CIFXHANDLE hDriver, BOARD_INFORMATION* const ptBoardInfo);
void App_ReadChannelInfo(const CIFXHANDLE hDriver, const CIFXHANDLE hChannel, CHANNEL_INFORMATION* const ptChannelInfo);

#endif /** COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_CIFXAPPLICATIONDEMO_H_ */
