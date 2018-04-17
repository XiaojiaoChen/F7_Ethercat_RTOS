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
  $Id: SystemPackets.h 2608 2017-02-03 11:35:17Z Ricky $:

  Description:
    System Packets header file

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file  SystemPackets.h
*   System Packets header file                                               */
/*****************************************************************************/

#ifndef COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_SYSTEMPACKETS_H_
#define COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_SYSTEMPACKETS_H_

#include "cifXApplicationDemo.h"
#include <stdint.h>
#include <stdbool.h>
#include "cifXUser.h"
#include "cifXErrors.h"
#include "rcX_Public.h"

#define SYSTEM_CHANNEL 0x00
#define CHANNEL0 0x01
#define CHANNEL1 0x02
#define CHANNEL2 0x03
#define CHANNEL3 0x04
#define LOCAL_CHANNEL 0x20

#define TX_TIMEOUT 500
#define RX_TIMEOUT 10

/*****************************************************************************/
/*! FUNCTION PROTOTYPES                                                      */
/*****************************************************************************/
uint32_t Pkt_SendPacket(CIFXHANDLE hChannel, CIFX_PACKET* ptSendPkt, uint32_t ulId, uint32_t ulTimeout);
uint32_t Pkt_ReturnPacket(CIFXHANDLE hChannel, CIFX_PACKET* ptSendPkt, uint32_t ulTimeout);
uint32_t Pkt_ReceivePacket(CIFXHANDLE hChannel, CIFX_PACKET* ptRecvPkt, uint32_t ulTimeout);

int32_t Sys_EmptyPacketReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt, uint32_t ulId, uint32_t ulCmd);
int32_t Sys_StartStopCommReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt, uint32_t ulId, bool fStart);
int32_t Sys_SetMacAddressReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt,  uint32_t ulId, uint8_t *abMacAddr);
int32_t Sys_FirmwareIdentifyReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt, uint32_t ulId,  uint32_t ulChannelId);
int32_t Sys_HardwareInfoReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt, uint32_t ulId);

int32_t Sys_LinkStatusChangeInd(CIFXHANDLE hChannel, CIFX_PACKET* ptPkt);

int32_t Sys_RegisterAppCnf(CIFX_PACKET* ptRegisterAppCnf);
int32_t Sys_SetMacAddressCnf(CIFX_PACKET* ptSetMacAddressCnf);
int32_t Sys_FirmwareIdentifyCnf(CIFX_PACKET* ptFirmwareIdentifyCnf);
int32_t Sys_HardwareInfoCnf(CIFX_PACKET* ptCnf);

#endif /** COMPONENTS_CIFXAPPLICATIONDEMO_INCLUDES_SYSTEMPACKETS_H_ */
