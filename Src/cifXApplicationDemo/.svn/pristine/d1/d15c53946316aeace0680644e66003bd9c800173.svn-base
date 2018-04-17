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
  $Id: cifXApplicationDemoFunctions.c 2639 2017-02-08 09:26:08Z Jin $:

  Description:
    cifX Application Demo Functions  

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-23  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file cifXApplicationDemoFunctions.c                             
*   cifX Application Demo Functions                                          */
/*****************************************************************************/
#include "cifXApplicationDemo.h"


/*****************************************************************************/
/*! application self test                                                    */
/*****************************************************************************/
void App_Selftest(void)
{
  uint32_t ulProcessdata;

  UserInterface_putStatLedOn(UI_STAT_LED_DATA);
  UserInterface_Sleep(200);
  UserInterface_putStatLedOff(UI_STAT_LED_DATA);
  
  UserInterface_putStatLedOn(UI_STAT_LED_STATUS);
  UserInterface_Sleep(200);
  UserInterface_putStatLedOff(UI_STAT_LED_STATUS);
  
  UserInterface_putStatLedOn(UI_STAT_LED_ERROR);
  UserInterface_Sleep(200);
  UserInterface_putStatLedOff(UI_STAT_LED_ERROR);
  
  UserInterface_putStatLedOn(UI_STAT_LED_ALARM);
  UserInterface_Sleep(200);
  UserInterface_putStatLedOff(UI_STAT_LED_ALARM);
  
  UserInterface_putOutData(0xAA);
  UserInterface_Sleep(200);
  UserInterface_putOutData(0x55);
  UserInterface_Sleep(200);

  ulProcessdata = UserInterface_getInData();
  UserInterface_putOutData(ulProcessdata);
  UserInterface_Sleep(200);

  ulProcessdata = UserInterface_getRotary();
  UserInterface_putOutData(ulProcessdata);
  UserInterface_Sleep(200);

  ulProcessdata = UserInterface_getDiag().bDiag;
  UserInterface_putStatLed(ulProcessdata);
  UserInterface_Sleep(200);

  UserInterface_putOutData(0x00);
  UserInterface_Sleep(200);
  
  UserInterface_putOutData(0xFF);
  UserInterface_Sleep(200);

  UserInterface_putStatLed(0);
  UserInterface_putOutData(0x00);
  UserInterface_Sleep(200);

} /** App_Selftest */

/*****************************************************************************/
/*! application read board information
*   \param hDriver        Handle of cifX driver  
*   \param ptBoardInfo    Return buffer (BOARD_INFORMATION structure)        */
/*****************************************************************************/
void App_ReadBoardInfo(const CIFXHANDLE hDriver, BOARD_INFORMATION* const ptBoardInfo)
{
  CIFXHANDLE hSys = NULL;
  SYSTEM_CHANNEL_SYSTEM_INFO_BLOCK tSysInfo = ptBoardInfo->tSystemInfo;
  long lRet = 0;      /** Return value for common error codes  */

  /** Retrieve board 0 information */
  if(CIFX_NO_ERROR != (lRet = xDriverEnumBoards(hDriver, 0, sizeof(BOARD_INFORMATION), ptBoardInfo)))
  {
    printf("No board with the given index available: 0x%08X !\r\n", (unsigned int) lRet);
  }
  else if( CIFX_NO_ERROR != (lRet = xSysdeviceOpen(hDriver, "cifX0", &hSys)))
  {
    printf("Error opening SystemDevice: 0x%08X !\r\n", (unsigned int) lRet);
  }
  /** System channel successfully opened, try to read the System Info Block */
  else if( CIFX_NO_ERROR != (lRet = xSysdeviceInfo(hSys, CIFX_INFO_CMD_SYSTEM_INFO_BLOCK, sizeof(tSysInfo), &tSysInfo)))
  {
    printf("Error querying system information block: 0x%08X !\r\n", (unsigned int) lRet);
  }
  else
  {
    printf("System Channel Info Block:\r\n");
    printf("DPM Size         : %u\r\n", (unsigned int)tSysInfo.ulDpmTotalSize);
    printf("Device Number    : %u\r\n", (unsigned int)tSysInfo.ulDeviceNumber);
    printf("Serial Number    : %u\r\n", (unsigned int)tSysInfo.ulSerialNumber);
    printf("Manufacturer     : %u\r\n", (unsigned int)tSysInfo.usManufacturer);
    printf("Production Date  : %u\r\n", (unsigned int)tSysInfo.usProductionDate);
    printf("Device Class     : %u\r\n", (unsigned int)tSysInfo.usDeviceClass);
    printf("HW Revision      : %u\r\n", (unsigned int)tSysInfo.bHwRevision);
    printf("HW Compatibility : %u\r\n", (unsigned int)tSysInfo.bHwCompatibility);
    
    xSysdeviceClose(hSys);
  }
  
} /** App_ReadBoardInfo */

/*****************************************************************************/
/*! application read channel information
*   \param hDriver        Handle of cifX driver  
*   \param hChannel       Handle to the channel
*   \param ptChannelInfo  Return buffer (CHANNEL_INFORMATION structure)      */
/*****************************************************************************/
void App_ReadChannelInfo(const CIFXHANDLE hDriver, const CIFXHANDLE hChannel, CHANNEL_INFORMATION* const ptChannelInfo)
{
  long lRet = 0; /** Return value for common error codes      */

  /** Retrieve the global communication channel information */
  if( CIFX_NO_ERROR != (lRet = xChannelInfo(hChannel, sizeof(CHANNEL_INFORMATION), ptChannelInfo)))
  {
    printf("Error querying communication channel information block: 0x%08X !\r\n", (unsigned int) lRet);
  }
  else
  {
    printf("Communication Channel Info:\r\n");
    printf("Device Number   : %u\r\n", (unsigned int) ptChannelInfo->ulDeviceNumber);
    printf("Serial Number   : %u\r\n", (unsigned int) ptChannelInfo->ulSerialNumber);
    printf("Firmware        : %s\r\n", ptChannelInfo->abFWName);
    printf("FW Version      : %u.%u.%u build %u\r\n", 
                                       (unsigned int) ptChannelInfo->usFWMajor, 
                                       (unsigned int) ptChannelInfo->usFWMinor,
                                       (unsigned int) ptChannelInfo->usFWRevision, 
                                       (unsigned int) ptChannelInfo->usFWBuild);
    printf("FW Date         : %02u/%02u/%04u\r\n", 
                                       (unsigned int) ptChannelInfo->bFWMonth, 
                                       (unsigned int) ptChannelInfo->bFWDay,
                                       (unsigned int) ptChannelInfo->usFWYear);
    printf("Mailbox Size    : %u\r\n", (unsigned int) ptChannelInfo->ulMailboxSize);
  }

} /** App_ReadChannelInfo */
