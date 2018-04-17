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
  $Id: PacketHandlerECS.c 2305 2016-11-23 13:05:55Z Jin $:

  Description:
    Protocol PacketHandler

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file PacketHandlerECS.c
*   Protocol PacketHandler                                                   */
/*****************************************************************************/

#include "cifXApplicationDemo.h"
#include "SystemPackets.h"
#include "EcsV4_Public.h"

#define ECS_PRODUCTCODE_NXEB51_FEATURES                               0x00000038
#define ECS_SECONDARY_VENDORID_HILSCHER                               0xE0000044
#define ECS_REVISIONNUMBER_CIFXMODIFIERMASK                           0x80000000
#define DEV_STR_NXEB51_CERT                                           "7762.000"
/*******************************************************************************
 *                                   _
 *   ____ ____ ____ _   _  ____  ___| |_   ___
 *  / ___) _  ) _  | | | |/ _  )/___)  _) /___)
 * | |  ( (/ / | | | |_| ( (/ /|___ | |__|___ |
 * |_|   \____)_|| |\____|\____|___/ \___|___/
 *               |_|
 * http://www.network-science.de/ascii/  font stop
 ******************************************************************************/
static uint32_t EcatSetConfigReq(APP_DATA_T *ptAppData, CIFX_PACKET *ptPkt, uint32_t ulId)
{
  uint32_t lRet = RCX_S_OK;
  ECAT_SET_CONFIG_REQ_T* ptConfigReq = (ECAT_SET_CONFIG_REQ_T*)ptPkt;
  ECAT_SET_CONFIG_DEVICEINFO_T* ptDevInfo;
  ECAT_SET_CONFIG_COE_T* ptCoECfg;

  memset(ptConfigReq, 0, sizeof(*ptConfigReq));

  ptConfigReq->tHead.ulDest = LOCAL_CHANNEL;
  ptConfigReq->tHead.ulSrc = 0x00;
  ptConfigReq->tHead.ulLen = sizeof(ptConfigReq->tData);
  ptConfigReq->tHead.ulCmd = ECAT_SET_CONFIG_REQ;
  ptConfigReq->tHead.ulSta = 0;
  ptConfigReq->tHead.ulExt = 0;

  ptConfigReq->tData.tBasicCfg.ulSystemFlags = ECAT_SET_CONFIG_SYSTEMFLAGS_APP_CONTROLLED;
  ptConfigReq->tData.tBasicCfg.ulWatchdogTime = 1000;

  ptConfigReq->tData.tBasicCfg.ulVendorId = ECS_SECONDARY_VENDORID_HILSCHER;  /** Creates Vendor ID in Sii Image in accordance to ESI file */
  ptConfigReq->tData.tBasicCfg.ulProductCode = ECS_PRODUCTCODE_NXEB51_FEATURES; /** Creates Product Code in Sii Image in accordance to ESI file */
  ptConfigReq->tData.tBasicCfg.ulRevisionNumber = 1; /** Creates Revision Number in in Sii Image accordance to ESI file: increments with every released change of ESI file */
  if(RCX_HW_DEV_CLASS_CIFX == ptAppData->tBoardInfo.tSystemInfo.usDeviceClass) /* cifX card has netX 100 therefore other configuration in ESI needed */
  {
    ptConfigReq->tData.tBasicCfg.ulRevisionNumber |= ECS_REVISIONNUMBER_CIFXMODIFIERMASK;
  }
  ptConfigReq->tData.tBasicCfg.ulSerialNumber = ptAppData->tBoardInfo.tSystemInfo.ulSerialNumber;
  ptConfigReq->tData.tBasicCfg.ulProcessDataOutputSize = sizeof(APP_OUTPUT_DATA_T); /**< Process Data Output Size from master view */
  ptConfigReq->tData.tBasicCfg.ulProcessDataInputSize = sizeof(APP_INPUT_DATA_T); /**< Process Data Input Size from master view */

  /** ECAT_SET_CONFIG_COE configuration **********************************************/
  ptConfigReq->tData.tBasicCfg.ulComponentInitialization |= ECAT_SET_CONFIG_COE;
  ptCoECfg = &ptConfigReq->tData.tComponentsCfg.tCoECfg;
 // ptCoECfg->bCoeFlags = ECAT_SET_CONFIG_COEFLAGS_USE_CUSTOM_OD;
  ptCoECfg->bCoeDetails = ECAT_SET_CONFIG_COEDETAILS_ENABLE_SDO
                        | ECAT_SET_CONFIG_COEDETAILS_ENABLE_SDOINFO
						| ECAT_SET_CONFIG_COEDETAILS_ENABLE_PDOASSIGN
						| ECAT_SET_CONFIG_COEDETAILS_ENABLE_PDOCONFIGURATION
                        | ECAT_SET_CONFIG_COEDETAILS_ENABLE_UPLOAD
                        | ECAT_SET_CONFIG_COEDETAILS_ENABLE_SDOCOMPLETEACCESS;

  ptCoECfg->ulOdIndicationTimeout = 1000;
  ptCoECfg->ulDeviceType          = 0;

  /** ECAT_SET_CONFIG_DEVICEINFO configuration ***************************************/
  ptConfigReq->tData.tBasicCfg.ulComponentInitialization |= ECAT_SET_CONFIG_DEVICEINFO;
  ptDevInfo = &ptConfigReq->tData.tComponentsCfg.tDeviceInfoCfg;

  strncpy( ptDevInfo->szOrderIdx, DEV_STR_NXEB51_CERT, sizeof(ptDevInfo->szOrderIdx) );
  ptDevInfo->bOrderIdxLength = strlen( ptDevInfo->szOrderIdx );

  strncpy( ptDevInfo->szNameIdx, "NXEB 51-CERT", sizeof(ptDevInfo->szNameIdx) );
  ptDevInfo->bNameIdxLength = strlen( ptDevInfo->szNameIdx );

  lRet = Pkt_SendPacket(ptAppData->hChannel[0], (CIFX_PACKET*)ptConfigReq, ulId, TX_TIMEOUT);
  return lRet;
}




/*******************************************************************************
 *                    ___ _                        _
 *                   / __|_)                  _   (_)
 *   ____ ___  ____ | |__ _  ____ ____   ____| |_  _  ___  ____   ___
 *  / ___) _ \|  _ \|  __) |/ ___)    \ / _  |  _)| |/ _ \|  _ \ /___)
 * ( (__| |_| | | | | |  | | |   | | | ( ( | | |__| | |_| | | | |___ |
 *  \____)___/|_| |_|_|  |_|_|   |_|_|_|\_||_|\___)_|\___/|_| |_(___/
 *
 * http://www.network-science.de/ascii/  font stop
 ******************************************************************************/
/*******************************************************************************
 *  _           _ _                 _
 * (_)         | (_)           _   (_)
 *  _ ____   _ | |_  ____ ____| |_  _  ___  ____   ___
 * | |  _ \ / || | |/ ___) _  |  _)| |/ _ \|  _ \ /___)
 * | | | | ( (_| | ( (__( ( | | |__| | |_| | | | |___ |
 * |_|_| |_|\____|_|\____)_||_|\___)_|\___/|_| |_(___/
 *
 * http://www.network-science.de/ascii/  font stop
 ******************************************************************************/





/*****************************************************************************/
/** Sends first packet to begin startup sequence.
further packets are sent in Protocol_PacketHandler() if response came in     */
/*****************************************************************************/
uint32_t Protocol_SendFirstPacket(APP_DATA_T *ptAppData)
{
  uint32_t lRet = RCX_S_OK;
  uint8_t abMacAddr[6] = { 0x00, 0x02, 0xA2, 0x2F, 0x90, 0x58 };
  lRet = Sys_SetMacAddressReq(ptAppData->hChannel[0], &ptAppData->tPkt, ptAppData->ulSendPktCnt++, &abMacAddr[0]);

  return lRet;
}


/******************************************************************************/
/** Handles every incoming response and indication.
Startup sequence is finished if RCX_START_STOP_COMM_CNF came in.              */
/******************************************************************************/
uint32_t Protocol_PacketHandler( APP_DATA_T *ptAppData )
{
  int32_t lRet = CIFX_NO_ERROR;

  lRet = Pkt_ReceivePacket(ptAppData->hChannel[0],&ptAppData->tPkt,0);

  if( CIFX_NO_ERROR == lRet )
  {
    switch( ptAppData->tPkt.tHeader.ulCmd )
    {
    case RCX_SET_MAC_ADDR_CNF:
      lRet = Sys_SetMacAddressCnf(&ptAppData->tPkt);
      /* ignore lRet, because cifX card will throw an error. It can be ignored,
       * because EtherCAT does not need a MAC address */
      lRet = Sys_EmptyPacketReq(ptAppData->hChannel[0],
                                &ptAppData->tPkt,
                                ptAppData->ulSendPktCnt++,
                                RCX_REGISTER_APP_REQ);
      break;

    case RCX_REGISTER_APP_CNF:
      lRet = Sys_RegisterAppCnf( &ptAppData->tPkt );
      if(CIFX_NO_ERROR == lRet)
      {
        lRet = EcatSetConfigReq(ptAppData,
                                &ptAppData->tPkt,
                                ptAppData->ulSendPktCnt++);
      }
      break;

    case ECAT_SET_CONFIG_CNF:
      lRet = ptAppData->tPkt.tHeader.ulState;
      if(CIFX_NO_ERROR == lRet)
      {
        lRet = Sys_EmptyPacketReq(ptAppData->hChannel[0],
                                  &ptAppData->tPkt,
                                  ptAppData->ulSendPktCnt++,
                                  RCX_CHANNEL_INIT_REQ);
      }
      break;

    case RCX_CHANNEL_INIT_CNF:
      lRet = ptAppData->tPkt.tHeader.ulState;
      if(CIFX_NO_ERROR == lRet)
      {
        lRet = Sys_StartStopCommReq(ptAppData->hChannel[0],
                                    &ptAppData->tPkt,
                                    ptAppData->ulSendPktCnt++,
                                    true);
      }
      break;

    case RCX_START_STOP_COMM_CNF:
      lRet = ptAppData->tPkt.tHeader.ulState;
      break;

    case RCX_FIRMWARE_IDENTIFY_CNF:
      lRet = Sys_FirmwareIdentifyCnf(&ptAppData->tPkt);
      break;

    case RCX_HW_HARDWARE_INFO_CNF:
      lRet = Sys_HardwareInfoCnf(&ptAppData->tPkt);
      break;

    case RCX_LINK_STATUS_CHANGE_IND:
      lRet = Sys_LinkStatusChangeInd(ptAppData->hChannel[0], &ptAppData->tPkt);
      break;

    case ECAT_ESM_ALSTATUS_CHANGED_IND:
      ptAppData->tPkt.tHeader.ulLen = sizeof(ECAT_ESM_ALSTATUS_CHANGED_RES_T) - sizeof(TLR_PACKET_HEADER_T);
      lRet = Pkt_ReturnPacket(ptAppData->hChannel[0], &ptAppData->tPkt, TX_TIMEOUT);
      break;

    default:
      if( (ptAppData->tPkt.tHeader.ulCmd & 0x1) == 0 ) /* received an indication*/
      {
        ptAppData->tPkt.tHeader.ulLen   = 0;
        ptAppData->tPkt.tHeader.ulState = RCX_E_UNKNOWN_COMMAND;
      //  lRet = Pkt_ReturnPacket(ptAppData->hChannel[0], &ptAppData->tPkt, TX_TIMEOUT);
      }
      else{ /* received a confirmation */
#ifndef DEMO_QUIET
        printf("warning: unhandled confirmation packet: 0x%08x\r\n", (unsigned int)ptAppData->tPkt.tHeader.ulCmd);
#endif
      }
      break;

    } /*switch*/

  } /* CIFX_NO_ERROR xChannelGetPacket */
  else if( CIFX_DEV_GET_NO_PACKET == lRet )
  {
    lRet = CIFX_NO_ERROR;
  }
  return lRet;
}

