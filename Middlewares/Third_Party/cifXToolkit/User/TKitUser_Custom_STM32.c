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
  $Id: TKitUser_Custom_STM32.c 3205 2017-07-18 06:53:59Z dirk $

  Description:
  	 This is one part of the hardware/OS abstraction layer for the cifX toolkit.
  	 The functions in this C-Module are called from the cifX Toolkit.

     Functions in this C-Module are required mainly for so called "RAM based devices".
     Since the STM32Cube Expansion is prepared for so called "ROM (flash) based devices",
     (e.g. the netSHIELD adapter board) it is not required to implement most of these functions!
     On "ROM based devices", the netX firmware is stored in a flash memory, directly connected to the netX chip.
     In contrast to RAM based devices, where the netX firmware is downloaded via the DPM (Dual Port Memory) from
     the host controller to the netX.

  	 Please refer to the document "cifX/netX Toolkit Manual", available under https://kb.hilscher.com/x/WYWhAQ
     for further information.

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2017-02-16  initial version

 **************************************************************************************/


/*****************************************************************************/
/*! \file TKitUser.c                                                         *
*    USER implemented functions called by the cifX Toolkit                   */
/*****************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include "cifXErrors.h"
#include "cifXToolkit.h"

/*****************************************************************************/
/*!  \addtogroup CIFX_TK_USER User specific implementation
*    \{                                                                      */
/*****************************************************************************/

/*****************************************************************************/
/*! Returns the number of firmware files associated with the card/channel,
*   passed as argument.
*   \param ptDevInfo DeviceInfo including channel number, for which the
*                    firmware file count should be read
*   \return number for firmware files, to download. The returned value will
*           be used as maximum value for ulIdx in calls to
*           USER_GetFirmwareFile                                             */
/*****************************************************************************/
uint32_t USER_GetFirmwareFileCount(PCIFX_DEVICE_INFORMATION ptDevInfo)
{
return 0;
}

/*****************************************************************************/
/*! Returns firmware file information for the given device/channel and Idx
*   passed as argument.
*   \param ptDevInfo  DeviceInfo including channel number, for which the
*                     firmware file should be delivered
*   \param ulIdx      Index of the returned file
*                     (0..USER_GetFirmwareFileCount() - 1)
*   \param ptFileInfo Short and full file name of the firmware. Used in
*                     calls to OS_OpenFile()
*   \return !=0 on success                                                   */
/*****************************************************************************/

int USER_GetFirmwareFile(PCIFX_DEVICE_INFORMATION ptDevInfo, uint32_t ulIdx, PCIFX_FILE_INFORMATION ptFileInfo)
{
  return 0;
}

/*****************************************************************************/
/*! Returns the number of configuration files associated with the card/
*   channel, passed as argument.
*   \param ptDevInfo DeviceInfo including channel number, for which the
*                    configuration file count should be read
*   \return number for confgiuration files, to download. The returned value
*           will be used as maximum value for ulIdx in calls to
*           USER_GetConfgirationFile                                         */
/*****************************************************************************/
uint32_t USER_GetConfigurationFileCount(PCIFX_DEVICE_INFORMATION ptDevInfo)
{
  return 0;
}

/*****************************************************************************/
/*! Returns configuration file information for the given device/channel and
*   Idx passed as argument.
*   \param ptDevInfo  DeviceInfo including channel number, for which the
*                     configuration file should be delivered
*   \param ulIdx      Index of the returned file
*                     (0..USER_GetConfigurationFileCount() - 1)
*   \param ptFileInfo Short and full file name of the configuration. Used in
*                     calls to OS_OpenFile()
*   \return !=0 on success                                                   */
/*****************************************************************************/
int USER_GetConfigurationFile(PCIFX_DEVICE_INFORMATION ptDevInfo, uint32_t ulIdx, PCIFX_FILE_INFORMATION ptFileInfo)
{
  return 0;
}

/*****************************************************************************/
/*! Returns OS file information for the given device/channel and Idx
*   passed as argument. This is needed for module downloading
*   \param ptDevInfo  DeviceInfo for which the
*                     firmware file should be delivered
*   \param ptFileInfo Short and full file name of the firmware. Used in
*                     calls to OS_OpenFile()
*   \return != 0 on success                                                   */
/*****************************************************************************/
int USER_GetOSFile(PCIFX_DEVICE_INFORMATION ptDevInfo, PCIFX_FILE_INFORMATION ptFileInfo)
{
  return 0;
}

/*****************************************************************************/
/*! Retrieve the full file name of the cifX Romloader binary image
*   \param ptDevInstance  Pointer to the device instance
*   \param ptFileInfo Short and full file name of the bootloader. Used in
*                     calls to OS_OpenFile()
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
void USER_GetBootloaderFile(PDEVICEINSTANCE ptDevInstance, PCIFX_FILE_INFORMATION ptFileInfo)
{
  return;
}

/*****************************************************************************/
/*! Retrieve the alias name of a cifX Board depending on the Device and
*   Serialnumber passed during this call
*   \param ptDevInfo Device- and Serial number of the card
*   \param ulMaxLen  Maximum length of alias
*   \param szAlias   Buffer to copy alias to. A string of length 0 means
*                    no alias                                                */
/*****************************************************************************/
void USER_GetAliasName(PCIFX_DEVICE_INFORMATION ptDevInfo, uint32_t ulMaxLen, char* szAlias)
{
  return;
}

/*****************************************************************************/
/*! Read the warmstart data from a given warmstart file
*   \param ptDevInfo Device- and Serial number of the card
*   \param ptPacket  Buffer for the warmstart packet                         */
/*****************************************************************************/
int USER_GetWarmstartParameters(PCIFX_DEVICE_INFORMATION ptDevInfo, CIFX_PACKET* ptPacket)
{
  return 0;
}

/*****************************************************************************/
/*! User trace function
*   right while cifXTKitAddDevice is being processed
*   \param ptDevInstance  Device instance
*   \param ulTraceLevel   Trace level
*   \param szFormat       Format string                                      */
/*****************************************************************************/
void USER_Trace(PDEVICEINSTANCE ptDevInstance, uint32_t ulTraceLevel, const char* szFormat, ...)
{
  va_list vaList;

  if(g_ulTraceLevel & ulTraceLevel)
  {
    va_start(vaList, szFormat);
    vprintf(szFormat, vaList);
    va_end(vaList);
    printf("\r\n");
  }

  UNREFERENCED_PARAMETER(ptDevInstance);
}



/*****************************************************************************/
/*! Check if interrupts should be enabled for this device
*   \param ptDevInfo  Device Infotmation
*   \return !=0 to enable interrupts                                         */
/*****************************************************************************/
int USER_GetInterruptEnable(PCIFX_DEVICE_INFORMATION ptDevInfo)
{
  return 0;
}

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/
