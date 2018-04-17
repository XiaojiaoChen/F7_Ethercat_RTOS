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
  $Id: SystemPackets.c 2845 2017-03-08 11:02:39Z Ricky $:

  Description:
    protocol independent system packets 

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file SystemPackets.c                                               
*   protocol independent system packets                                      */
/*****************************************************************************/
#include "SystemPackets.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "UserInterface.h"


/*****************************************************************************/
/*! Displays a hex dump on the debug console (16 bytes per line)
*   \param pbData     pointer to dump data
*   \param ulDataLen  length of data dump                                    */
/*****************************************************************************/
static void DumpData(unsigned char* pbData, unsigned long ulDataLen)
{
  unsigned long ulIdx;

  if(CIFX_MAX_DATA_SIZE < ulDataLen)
  {
    ulDataLen = CIFX_MAX_DATA_SIZE;
  }

  for(ulIdx = 0; ulIdx < ulDataLen; ++ulIdx)
  {
    if(0 == (ulIdx % 16))
      printf("\r\n");

    printf("%02X ", pbData[ulIdx]);
  }
  printf("\r\n");

} /** DumpData */


/*****************************************************************************/
/*! Dumps a rcX packet to debug console
*   \param ptPacket  Packet to be dumped                                     */
/*****************************************************************************/
static void DumpPacket(CIFX_PACKET* ptPacket)
{
  printf("Dest   : 0x%08X      ID   : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulDest, (unsigned int) ptPacket->tHeader.ulId);
  printf("Src    : 0x%08X      Sta  : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulSrc, (unsigned int) ptPacket->tHeader.ulState);
  printf("DestID : 0x%08X      Cmd  : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulDestId, (unsigned int) ptPacket->tHeader.ulCmd);
  printf("SrcID  : 0x%08X      Ext  : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulSrcId, (unsigned int) ptPacket->tHeader.ulExt);
  printf("Len    : 0x%08X      Rout : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulLen, (unsigned int) ptPacket->tHeader.ulRout);

  if(ptPacket->tHeader.ulLen) {
  printf("Data:");

  /** Displays a hex dump on the debug console (16 bytes per line) */
  DumpData(ptPacket->abData, ptPacket->tHeader.ulLen);
  }

} /** DumpPacket */


/*****************************************************************************/
/*! send a rcX packet to a DPM channel mailbox
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptSendPkt  Packet to send to channel
*   \param ulId       Packet Identification as Unique Number
*   \param ulTimeout  Time in ms to wait for card to accept the packet
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
uint32_t Pkt_SendPacket(CIFXHANDLE hChannel, CIFX_PACKET* ptSendPkt, uint32_t ulId, uint32_t ulTimeout)
{
  uint32_t lRet = CIFX_NO_ERROR;

  ptSendPkt->tHeader.ulSrc = 0x00;
  ptSendPkt->tHeader.ulId  = ulId;

  lRet = xChannelPutPacket(hChannel, ptSendPkt, ulTimeout);

  if(CIFX_NO_ERROR == lRet)
  {
#ifndef DEMO_QUIET
    printf("sent packet:\r\n");
    DumpPacket(ptSendPkt);
#endif
  }

  return lRet;
} /** Pkt_SendPacket */

/*****************************************************************************/
/*! send back a return packet to the sender
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptSendPkt  Packet to send to channel
*   \param ulTimeout  Time in ms to wait for card to accept the packet
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
uint32_t Pkt_ReturnPacket(CIFXHANDLE hChannel, CIFX_PACKET* ptSendPkt, uint32_t ulTimeout)
{
  uint32_t lRet = CIFX_NO_ERROR;

  ptSendPkt->tHeader.ulCmd   |= 0x01;

  lRet = xChannelPutPacket(hChannel, ptSendPkt, ulTimeout);

  if(CIFX_NO_ERROR == lRet)
  {
#ifndef DEMO_QUIET
    printf("returned packet:\r\n");
    DumpPacket(ptSendPkt);
#endif
  }

  return lRet;
} /** Pkt_ReturnPacket */


/*****************************************************************************/
/*! Retrieve a pending packet from the channel mailbox
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptRecvPkt  Returned packet
*   \param ulTimeout  Time in ms to wait for available message
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
uint32_t Pkt_ReceivePacket(CIFXHANDLE hChannel, CIFX_PACKET* ptRecvPkt, uint32_t ulTimeout)
{
  uint32_t lRet = CIFX_NO_ERROR;

  lRet = xChannelGetPacket(hChannel, sizeof(*ptRecvPkt), ptRecvPkt, ulTimeout);

  if(CIFX_NO_ERROR == lRet)
  {
#ifndef DEMO_QUIET
    printf("received packet:\r\n");
    DumpPacket(ptRecvPkt);
#endif
  }

  return lRet;
} /** Pkt_ReceivePacket */


/*******************************************************************************
 *                                   _
 *   ____ ____ ____ _   _  ____  ___| |_   ___
 *  / ___) _  ) _  | | | |/ _  )/___)  _) /___)
 * | |  ( (/ / | | | |_| ( (/ /|___ | |__|___ |
 * |_|   \____)_|| |\____|\____|___/ \___|___/
 *               |_|
 * http://www.network-science.de/ascii/  font stop
 ******************************************************************************/

/*****************************************************************************/
/*! send an empty rcX packet with command ulCmd which is provided in param to channel mailbox
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptPkt      Packet to send to channel
*   \param ulId       Packet Identification as Unique Number
*   \param ulCmd      Packet Command
*   \return           CIFX_NO_ERROR on success                               */
/*****************************************************************************/
int32_t Sys_EmptyPacketReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt, uint32_t ulId, uint32_t ulCmd)
{
  uint32_t lRet = CIFX_NO_ERROR;
  CIFX_PACKET_HEADER* ptHead = (CIFX_PACKET_HEADER*)&ptPkt->tHeader;

  memset(ptHead, 0, sizeof(*ptHead));

  ptHead->ulDest = LOCAL_CHANNEL;
  ptHead->ulCmd = ulCmd;
  ptHead->ulLen = 0;

  lRet = Pkt_SendPacket(hChannel, ptPkt, ulId, TX_TIMEOUT);

  return lRet;
} /** Sys_EmptyPacketReq */


/*****************************************************************************/
/*! send a start/stop communication request through packet
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptPkt      Packet to send to channel
*   \param ulId       Packet Identification as Unique Number
*   \param fStart     true: start, false: stop
*   \return           CIFX_NO_ERROR on success                               */
/*****************************************************************************/
int32_t Sys_StartStopCommReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt, uint32_t ulId, bool fStart)
{
  uint32_t lRet = CIFX_NO_ERROR;
  RCX_START_STOP_COMM_REQ_T* ptReq = (RCX_START_STOP_COMM_REQ_T*)ptPkt;

  memset(ptReq, 0, sizeof(*ptReq));

  ptReq->tHead.ulDest = LOCAL_CHANNEL;
  ptReq->tHead.ulCmd = RCX_START_STOP_COMM_REQ;
  ptReq->tHead.ulLen = sizeof(ptReq->tData);

  ptReq->tData.ulParam = fStart ? 1 : 2;

  lRet = Pkt_SendPacket(hChannel, ptPkt, ulId, TX_TIMEOUT);

  return lRet;
} /** Sys_StartStopCommReq */


/*****************************************************************************/
/*! send a set MAC address request through packet
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptPkt      Packet to send to channel
*   \param ulId       Packet Identification as Unique Number
*   \param abMacAddr  mac address pointer
*   \return           CIFX_NO_ERROR on success                               */
/*****************************************************************************/
int32_t Sys_SetMacAddressReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt, uint32_t ulId, uint8_t *abMacAddr)
{
  uint32_t lRet = CIFX_NO_ERROR;

  RCX_SET_MAC_ADDR_REQ_T* ptSetMacAddrReq=(RCX_SET_MAC_ADDR_REQ_T*)ptPkt;
  memset(ptSetMacAddrReq, 0, sizeof(RCX_SET_MAC_ADDR_REQ_T));

  ptSetMacAddrReq->tHead.ulDest = SYSTEM_CHANNEL;
  ptSetMacAddrReq->tHead.ulCmd  = RCX_SET_MAC_ADDR_REQ;
  ptSetMacAddrReq->tHead.ulLen  = sizeof(ptSetMacAddrReq->tData);

  ptSetMacAddrReq->tData.ulParam   = 0x00;
  memcpy(&ptSetMacAddrReq->tData.abMacAddr, abMacAddr, sizeof(ptSetMacAddrReq->tData.abMacAddr));


  lRet = Pkt_SendPacket(hChannel, ptPkt, ulId, TX_TIMEOUT);

  return lRet;
} /** Sys_SetMacAddressReq */


/*****************************************************************************/
/*! send an Identifying channel firmware request through packet
*   \param hChannel     Channel handle acquired by xChannelOpen
*   \param ptPkt        Packet to send to channel
*   \param ulId         Packet Identification as Unique Number
*   \param ulChannelId  Channel Identification
                          RCX_SYSTEM_CHANNEL 0xFFFFFFFF
                          RCX_COMM_CHANNEL_0 0x00000000
                          RCX_COMM_CHANNEL_1 0x00000001
                          RCX_COMM_CHANNEL_2 0x00000002
                          RCX_COMM_CHANNEL_3 0x00000003
*   \return             CIFX_NO_ERROR on success                             */
/*****************************************************************************/
int32_t Sys_FirmwareIdentifyReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt, uint32_t ulId,  uint32_t ulChannelId)
{
  uint32_t lRet = CIFX_NO_ERROR;

  RCX_FIRMWARE_IDENTIFY_REQ_T* ptFirmwareIdentityReq=(RCX_FIRMWARE_IDENTIFY_REQ_T*)ptPkt;
  memset(ptFirmwareIdentityReq, 0, sizeof(RCX_FIRMWARE_IDENTIFY_REQ_T));

  ptFirmwareIdentityReq->tHead.ulDest = SYSTEM_CHANNEL;
  ptFirmwareIdentityReq->tHead.ulCmd  = RCX_FIRMWARE_IDENTIFY_REQ;
  ptFirmwareIdentityReq->tHead.ulLen  = sizeof(ptFirmwareIdentityReq->tData);

  ptFirmwareIdentityReq->tData.ulChannelId  = ulChannelId;

  lRet = Pkt_SendPacket(hChannel, ptPkt, ulId, TX_TIMEOUT);

  return lRet;
} /** Sys_FirmwareIdentifyReq */


/*****************************************************************************/
/*! send read hardware information request through packet
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptPkt      Packet to send to channel
*   \param ulId       Packet Identification as Unique Number
*   \return           CIFX_NO_ERROR on success                               */
/*****************************************************************************/
int32_t Sys_HardwareInfoReq(CIFXHANDLE hChannel, CIFX_PACKET *ptPkt,  uint32_t ulId)
{
  uint32_t lRet = CIFX_NO_ERROR;

  RCX_HW_HARDWARE_INFO_REQ_T* ptReq=(RCX_HW_HARDWARE_INFO_REQ_T*)ptPkt;
  memset(ptReq, 0, sizeof(RCX_HW_HARDWARE_INFO_REQ_T));

  ptReq->tHead.ulDest = SYSTEM_CHANNEL;
  ptReq->tHead.ulCmd  = RCX_HW_HARDWARE_INFO_REQ;
  ptReq->tHead.ulLen  = 0;

  lRet = Pkt_SendPacket(hChannel, ptPkt, ulId, TX_TIMEOUT);

  return lRet;
} /** Sys_HardwareInfoReq */

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
/*! send link status change response
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptPkt      Packet to send to channel
*   \return           CIFX_NO_ERROR on success                               */
/*****************************************************************************/
int32_t Sys_LinkStatusChangeInd(CIFXHANDLE hChannel, CIFX_PACKET* ptPkt)
{
  uint32_t lRet = CIFX_NO_ERROR;

  ptPkt->tHeader.ulLen   = 0;
  ptPkt->tHeader.ulState = RCX_S_OK;
  lRet = Pkt_ReturnPacket(hChannel, ptPkt, TX_TIMEOUT);

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

/*****************************************************************************/
/*! check status of confirmation packet header
*   \param  ptRegisterAppCnf Register application confirmation Packet pointer
*   \return confirmation packet status                                       */
/*****************************************************************************/
int32_t Sys_RegisterAppCnf(CIFX_PACKET* ptRegisterAppCnf)
{
  uint32_t lRet = CIFX_NO_ERROR;

  if(ptRegisterAppCnf->tHeader.ulState){
#ifndef DEMO_QUIET
    printf("Register application failed ERROR: 0x%08x\r\n", (unsigned int)ptRegisterAppCnf->tHeader.ulState);
#endif
    lRet = ptRegisterAppCnf->tHeader.ulState;
  }
  else {
#ifndef DEMO_QUIET
    printf("Application registered successfully\r\n");
#endif
  }

  return lRet;
} /** Sys_RegisterAppCnf */

/*****************************************************************************/
/*! check set mac address confirmation packet header status
*   \param  pvSetMacAddressCnf pointer tp Set MAC Address Confirmation Packet
*   \return confirmation packet status                                       */
/*****************************************************************************/
int32_t Sys_SetMacAddressCnf(CIFX_PACKET* pvSetMacAddressCnf)
{
  RCX_SET_MAC_ADDR_CNF_T* ptSetMacAddressCnf = (RCX_SET_MAC_ADDR_CNF_T*)pvSetMacAddressCnf;
  uint32_t lRet = CIFX_NO_ERROR;

  if(ptSetMacAddressCnf->tHead.ulSta){
#ifndef DEMO_QUIET
    printf("Set MAC Address ERROR: 0x%08x\r\n",(unsigned int)ptSetMacAddressCnf->tHead.ulSta);
#endif
    lRet = ptSetMacAddressCnf->tHead.ulSta;
  }
  else {
#ifndef DEMO_QUIET
    printf("MAC Address set successfully\r\n");
#endif
  }

  return lRet;
} /** Sys_SetMacAddressCnf */


/*****************************************************************************/
/*! get identifying firmware confirmation data
*   \param  pvFirmwareIdentifyCnf pointer to identifying firmware confirmation Packet
*   \return IFX_NO_ERROR on success                                          */
/*****************************************************************************/
int32_t Sys_FirmwareIdentifyCnf(CIFX_PACKET* pvFirmwareIdentifyCnf)
{
  RCX_FIRMWARE_IDENTIFY_CNF_T* ptFirmwareIdentifyCnf = (RCX_FIRMWARE_IDENTIFY_CNF_T*)pvFirmwareIdentifyCnf;
  uint32_t lRet = CIFX_NO_ERROR;

#ifndef DEMO_QUIET
  printf("Identified firmware: %s V%u.%u.%u.%u\r\n",
         ptFirmwareIdentifyCnf->tData.tFirmwareIdentification.tFwName.abName,
         ptFirmwareIdentifyCnf->tData.tFirmwareIdentification.tFwVersion.usMajor,
         ptFirmwareIdentifyCnf->tData.tFirmwareIdentification.tFwVersion.usMinor,
         ptFirmwareIdentifyCnf->tData.tFirmwareIdentification.tFwVersion.usBuild,
         ptFirmwareIdentifyCnf->tData.tFirmwareIdentification.tFwVersion.usRevision);
#endif

  return lRet;
} /** Sys_FirmwareIdentifyCnf */


/*****************************************************************************/
/*! read Hardware Information confirmation data
*   \param  pvHardwareInfoCnf pointer to Read Hardware Information confirmation Packet
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t Sys_HardwareInfoCnf(CIFX_PACKET* pvHardwareInfoCnf)
{
  RCX_HW_HARDWARE_INFO_CNF_T* ptHardwareInfoCnf = (RCX_HW_HARDWARE_INFO_CNF_T*)pvHardwareInfoCnf;
  uint32_t lRet = CIFX_NO_ERROR;

#ifndef DEMO_QUIET
  printf("identified hardware device number: %d\r\n",(int)ptHardwareInfoCnf->tData.ulDeviceNumber);
  printf("identified hardware serial number: %d\r\n",(int)ptHardwareInfoCnf->tData.ulSerialNumber);
#endif

  return lRet;
} /** Sys_HardwareInfoCnf */

