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

#include "main.h"
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

	uint32_t timeTick;
	float	angle[JOINT_NUM];				//angle=
	float 	velocity[JOINT_NUM];
	float 	acceleration[JOINT_NUM];
	float   stiffness[JOINT_NUM];
	float 	torque[JOINT_NUM];
	float 	pressure[JOINT_NUM][2];

}__attribute__((packed)) APP_INPUT_DATA_T;


typedef struct APP_OUTPUT_DATA_Ttag {


	float	angle[JOINT_NUM];				//angle=
	float 	velocity[JOINT_NUM];
	float 	acceleration[JOINT_NUM];
	float   stiffness[JOINT_NUM];
	float 	torque[JOINT_NUM];
	float 	pressure[JOINT_NUM][2];
	int8_t	commandType[JOINT_NUM];

}__attribute__((packed)) APP_OUTPUT_DATA_T;


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

extern APP_DATA_T tAppData;
extern CIFXHANDLE hDriver;  /** Handle of cifX driver                    */

/*****************************************************************************/
/*! FUNCTION PROTOTYPES                                                      */
/*****************************************************************************/
extern uint32_t Protocol_PacketHandler( APP_DATA_T *ptAppData );
extern uint32_t Protocol_SendFirstPacket(APP_DATA_T *ptAppData);

int Ethercat_Init(void);
void Ethercat_DeInit(void);
int32_t EthercatPacketEventHandler(void);
void EthercatCyclicIODataHandler(void);

void App_Selftest(void);
void App_ReadBoardInfo(const CIFXHANDLE hDriver, BOARD_INFORMATION* const ptBoardInfo);
void App_ReadChannelInfo(const CIFXHANDLE hDriver, const CIFXHANDLE hChannel, CHANNEL_INFORMATION* const ptChannelInfo);

#endif /** COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_CIFXAPPLICATIONDEMO_H_ */
