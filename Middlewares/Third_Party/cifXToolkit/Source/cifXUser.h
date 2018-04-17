/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: cifXUser.h 7155 2015-07-23 11:12:18Z Robert $:

  Description:
    CIFx driver API definition file

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2015-07-23  Added API function pointer definitions usable in a pointer table
    2015-03-31  Added guard for _MSC_VER to allow compilation using -wundef
    2014-07-07  Added support for IAR C/C++ Compiler (ARM Cores only)
    2014-04-28  Added support for armcc compiler
    2012-01-31  Added COM-State notification structure
    2011-12-12  SYSTEM_CHANNEL_SYSTEM_STATUS_BLOCK structure extended by ulHWFeatures
    2011-11-29  Added xSysdeviceExtendedMemory()
    2011-09-13  - CIFX_MAX_PACKET_SIZE changed from 1600 to 1596 bytes because of mailbox counter
                - xSysdeviceBoostart() function added
    2010-04-22  Added ulBootError to SYSTEM_CHANNEL_SYSTEM_STATUS_BLOCK
    2010-04-15  - Added timeout to xChannelSyncState function
                - Added CIFX_SYNC_WAIT_CMD to be able to wait for sync signalling by firmware
    2010-04-01  Data types update
    2010-03-23  - Data types changed for 32/64Bit usage
                - Event functions include
    2009-10-29  DMA state function and states included
    2009-10-01  CIFX_TO_WAIT_COS_CMD/ACK changed to 20ms
    2009-06-08  SYSTEM_CHANNEL_SYSTEM_INFO_BLOCK structure extended by bDevIdNumber
    2009-04-28  New download mode for modules included
    2009-01-23  netX DPM signature included
    2008-11-25  NETX_SYSTEM_STATUS block structure updated
                - removed LEDs
                - added CPU load and system start time values
    2008-06-19  xDriverRestartDevice() function parameters changed
    2008-05-27  APIENTRY now set empty, if not defined outside the file
    2008-04-29  DOWNLOAD_MODE_LICENSECODE added
    2008-03-17  xDriverRestartDevice() included
    2008-02-22  Firmware version changed from Major,Minor,Revision,Build to
                Major,Minor,Build,Revision, as decided on 19.11.2007
    2007-07-26  Added DOWNLOAD_MODE_BOOTLOADER
    2007-04-17  Parameters for the following functions changed
                - xSysdeviceDownload/Upload
                - xSysdeviceFindFirstFile/NextFile
                - xChannelDownload/Upload
                - xChannelFindFirstFile/NextFile
    2007-04-13  CALLBACK state definition included
    2007-04-10  - PFN_TRANSFER_PACKET moved to toolkit headers
                - CIFX_COLDSTART and CIFX_WARMSTART changed to
                  CIFX_SYSTEMSTART and CIFX_CHANNELINIT
    2007-04-04  xChannelBusState() included
    2007-03-28  typedef for PFN_TRANSFER_PACKET included
    2007-03-21  Added:
                - xChannelIOInfo
                - xSysdeviceReset
                - CIFX_WARMSTART/CIFX_COLDSTART
    2007-03-20  Added:
                - xChannelFindFirstFile
                - xChannelFindNextFile
                - xChannelUpload
                - xSysdeviceFindFirstFile
                - xSysdeviceFindNextFile
                - xSysdeviceUpload
    2007-03-16  Removed CIFX_DRIVER define around API functions,
                as it is not needed anymore (since V0.920 of driver)
    2006-12-04  PACKED_POST moved to closing curly brace after type definition
    2006-10-18  Changed HANDLE to CIFXHANDLE which is a void*, to be
                usable on VxWorks without compiler warnings
    2006-03-17  created

**************************************************************************************/

/*****************************************************************************/
/*! \addtogroup CIFX_DRIVER_API cifX Driver API implementation               */
/*! \{                                                                       */
/*****************************************************************************/

/* prevent multiple inclusion */
#ifndef __CIFxUSER_H
#define __CIFxUSER_H

#if defined(_MSC_VER)
  #if _MSC_VER >= 1000
    #define __CIFx_PACKED_PRE
    #define __CIFx_PACKED_POST
    #pragma once
    #pragma pack(1)            /* Always align structures to 1Byte boundery */
    #ifndef STRICT             /* Check Typedefinition */
      #define STRICT
    #endif
  #endif /* _MSC_VER >= 1000 */
#endif /* _MSC_VER */

/* support for GNU compiler */
#ifdef __GNUC__
  #define __CIFx_PACKED_PRE
  #define __CIFx_PACKED_POST   __attribute__((packed))
#endif

/* support for ARMCC and IAR compiler (ARM cores only) */
#if defined (__ADS__) || defined (__REALVIEW__) || defined (__CC_ARM) || defined (__ICCARM__)
  /* tight packing of structure members */
  #define __CIFx_PACKED_PRE  __packed
  #define __CIFx_PACKED_POST
#endif  /* __ADS__, __REALVIEW__, __CC_ARM */

#ifdef __cplusplus
  extern "C" {
#endif  /* _cplusplus */

#include <stdint.h>

#ifndef APIENTRY
  #define APIENTRY
#endif

/* ------------------------------------------------------------------------------------ */
/*  global definitions                                                                  */
/* ------------------------------------------------------------------------------------ */
typedef void* CIFXHANDLE;

/* DPM memory validation */
#define CIFX_DPM_NO_MEMORY_ASSIGNED           0x0BAD0BADUL
#define CIFX_DPM_INVALID_CONTENT              0xFFFFFFFFUL

#define CIFX_DPMSIGNATURE_BSL_STR             "BOOT"
#define CIFX_DPMSIGNATURE_BSL_VAL             0x544F4F42UL
#define CIFX_DPMSIGNATURE_FW_STR              "netX"
#define CIFX_DPMSIGNATURE_FW_VAL              0x5874656EUL

/* CIFx global timeouts in milliseconds */
#define CIFX_TO_WAIT_HW_RESET_ACTIVE          2000UL
#define CIFX_TO_WAIT_HW                       2000UL
#define CIFX_TO_WAIT_COS_CMD                  20UL
#define CIFX_TO_WAIT_COS_ACK                  20UL
#define CIFX_TO_SEND_PACKET                   5000UL
#define CIFX_TO_1ST_PACKET                    1000UL
#define CIFX_TO_CONT_PACKET                   1000UL
#define CIFX_TO_LAST_PACKET                   1000UL
#define CIFX_TO_FIRMWARE_START                10000UL

/* Maximum channel number */
#define CIFX_MAX_NUMBER_OF_CHANNEL_DEFINITION 8
#define CIFX_MAX_NUMBER_OF_CHANNELS           6
#define CIFX_NO_CHANNEL                       0xFFFFFFFF

/* Maximum file name length */
#define CIFX_MAX_FILE_NAME_LENGTH             260
#define CIFX_MIN_FILE_NAME_LENGTH             5

/* The system device port number */
#define CIFX_SYSTEM_DEVICE                    0xFFFFFFFF

/* Information commands */
#define CIFX_INFO_CMD_SYSTEM_INFORMATION      1
#define CIFX_INFO_CMD_SYSTEM_INFO_BLOCK       2
#define CIFX_INFO_CMD_SYSTEM_CHANNEL_BLOCK    3
#define CIFX_INFO_CMD_SYSTEM_CONTROL_BLOCK    4
#define CIFX_INFO_CMD_SYSTEM_STATUS_BLOCK     5

/* General commands */
#define CIFX_CMD_READ_DATA                    1
#define CIFX_CMD_WRITE_DATA                   2

/* HOST mode definition */
#define CIFX_HOST_STATE_NOT_READY             0
#define CIFX_HOST_STATE_READY                 1
#define CIFX_HOST_STATE_READ                  2

/* WATCHDOG commands*/
#define CIFX_WATCHDOG_STOP                    0
#define CIFX_WATCHDOG_START                   1

/* Configuration Lock commands*/
#define CIFX_CONFIGURATION_UNLOCK             0
#define CIFX_CONFIGURATION_LOCK               1
#define CIFX_CONFIGURATION_GETLOCKSTATE       2

/* BUS state commands*/
#define CIFX_BUS_STATE_OFF                    0
#define CIFX_BUS_STATE_ON                     1
#define CIFX_BUS_STATE_GETSTATE               2

/* DMA state commands*/
#define CIFX_DMA_STATE_OFF                    0
#define CIFX_DMA_STATE_ON                     1
#define CIFX_DMA_STATE_GETSTATE               2

/* Memory pointer commands*/
#define CIFX_MEM_PTR_OPEN                     1
#define CIFX_MEM_PTR_OPEN_USR                 2
#define CIFX_MEM_PTR_CLOSE                    3

/* I/O area definition */
#define CIFX_IO_INPUT_AREA                    1
#define CIFX_IO_OUTPUT_AREA                   2

/* Reset definitions */
#define CIFX_SYSTEMSTART                      1
#define CIFX_CHANNELINIT                      2
#define CIFX_BOOTSTART                        3

/* Sync command definitions */
#define CIFX_SYNC_SIGNAL_CMD                  1
#define CIFX_SYNC_ACKNOWLEDGE_CMD             2
#define CIFX_SYNC_WAIT_CMD                    3

typedef struct CIFX_NOTIFY_RX_MBX_FULL_DATA_Ttag
{
  uint32_t ulRecvCount;
} CIFX_NOTIFY_RX_MBX_FULL_DATA_T;

typedef struct CIFX_NOTIFY_TX_MBX_EMPTY_DATA_Ttag
{
  uint32_t ulMaxSendCount;
} CIFX_NOTIFY_TX_MBX_EMPTY_DATA_T;

typedef struct CIFX_NOTIFY_COM_STATE_Ttag
{
  uint32_t ulComState;
} CIFX_NOTIFY_COM_STATE_T;

/* Notifications */
#define CIFX_NOTIFY_RX_MBX_FULL               1
#define CIFX_NOTIFY_TX_MBX_EMPTY              2
#define CIFX_NOTIFY_PD0_IN                    3
#define CIFX_NOTIFY_PD1_IN                    4
#define CIFX_NOTIFY_PD0_OUT                   5
#define CIFX_NOTIFY_PD1_OUT                   6
#define CIFX_NOTIFY_SYNC                      7
#define CIFX_NOTIFY_COM_STATE                 8

/* Extended memory commands */
#define CIFX_GET_EXTENDED_MEMORY_INFO         1
#define CIFX_GET_EXTENDED_MEMORY_POINTER      2
#define CIFX_FREE_EXTENDED_MEMORY_POINTER     3

/*****************************************************************************/
/*! Structure definitions                                                    */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct DRIVER_INFORMATIONtag
{
  char       abDriverVersion[32];                          /*!< Driver version                 */
  uint32_t   ulBoardCnt;                                   /*!< Number of available Boards     */
} __CIFx_PACKED_POST DRIVER_INFORMATION;

#define CIFx_MAX_INFO_NAME_LENTH              16

/*****************************************************************************/
/*! Directory Information structure for enumerating directories              */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct CIFX_DIRECTORYENTRYtag
{
  CIFXHANDLE    hList;                                     /*!< Handle from Enumeration function, do not touch */
  char          szFilename[CIFx_MAX_INFO_NAME_LENTH];      /*!< Returned file name. */
  uint8_t       bFiletype;                                 /*!< Returned file type. */
  uint32_t      ulFilesize;                                /*!< Returned file size. */

} __CIFx_PACKED_POST CIFX_DIRECTORYENTRY;

/*****************************************************************************/
/*! Extended memory information structure                                    */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct CIFX_EXTENDED_MEMORY_INFORMATIONtag
{
  void*         pvMemoryID;                                /*!< Identification of the memory area       */
  void*         pvMemoryPtr;                               /*!< Memory pointer                          */
  uint32_t      ulMemorySize;                              /*!< Memory size of the Extended memory area */
  uint32_t      ulMemoryType;                              /*!< Memory type information                 */

} __CIFx_PACKED_POST CIFX_EXTENDED_MEMORY_INFORMATION;

/*****************************************************************************/
/*! System Channel Information structure                                     */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct SYSTEM_CHANNEL_SYSTEM_INFORMATIONtag
{
  uint32_t   ulSystemError;                                /*!< Global system error            */
  uint32_t   ulDpmTotalSize;                               /*!< Total size dual-port memory in bytes */
  uint32_t   ulMBXSize;                                    /*!< System mailbox data size [Byte]*/
  uint32_t   ulDeviceNumber;                               /*!< Global device number           */
  uint32_t   ulSerialNumber;                               /*!< Global serial number           */
  uint32_t   ulOpenCnt;                                    /*!< Channel open counter           */
} __CIFx_PACKED_POST SYSTEM_CHANNEL_SYSTEM_INFORMATION;

/* System Channel: System Information Block */
typedef __CIFx_PACKED_PRE struct SYSTEM_CHANNEL_SYSTEM_INFO_BLOCKtag
{
  uint8_t   abCookie[4];                                   /*!< 0x00 "netX" cookie */
  uint32_t  ulDpmTotalSize;                                /*!< 0x04 Total Size of the whole dual-port memory in bytes */
  uint32_t  ulDeviceNumber;                                /*!< 0x08 Device number */
  uint32_t  ulSerialNumber;                                /*!< 0x0C Serial number */
  uint16_t  ausHwOptions[4];                               /*!< 0x10 Hardware options, xC port 0..3 */
  uint16_t  usManufacturer;                                /*!< 0x18 Manufacturer Location */
  uint16_t  usProductionDate;                              /*!< 0x1A Date of production */
  uint32_t  ulLicenseFlags1;                               /*!< 0x1C License code flags 1 */
  uint32_t  ulLicenseFlags2;                               /*!< 0x20 License code flags 2 */
  uint16_t  usNetxLicenseID;                               /*!< 0x24 netX license identification */
  uint16_t  usNetxLicenseFlags;                            /*!< 0x26 netX license flags */
  uint16_t  usDeviceClass;                                 /*!< 0x28 netX device class */
  uint8_t   bHwRevision;                                   /*!< 0x2A Hardware revision index */
  uint8_t   bHwCompatibility;                              /*!< 0x2B Hardware compatibility index */
  uint8_t   bDevIdNumber;                                  /*!< 0x2C Device identification number (rotary switch) */
  uint8_t   bReserved;                                     /*!< 0x2D Reserved byte */
  uint16_t  usReserved;                                    /*!< 0x2E:0x2F Reserved */
} __CIFx_PACKED_POST SYSTEM_CHANNEL_SYSTEM_INFO_BLOCK;

/* System Channel: Channel Information Block */
#define CIFX_SYSTEM_CHANNEL_DEFAULT_INFO_BLOCK_SIZE  16
typedef __CIFx_PACKED_PRE struct SYSTEM_CHANNEL_CHANNEL_INFO_BLOCKtag
{
  uint8_t  abInfoBlock[CIFX_MAX_NUMBER_OF_CHANNEL_DEFINITION][CIFX_SYSTEM_CHANNEL_DEFAULT_INFO_BLOCK_SIZE];
} __CIFx_PACKED_POST SYSTEM_CHANNEL_CHANNEL_INFO_BLOCK;

/* System Channel: System Control Block */
typedef __CIFx_PACKED_PRE struct SYSTEM_CHANNEL_SYSTEM_CONTROL_BLOCKtag
{
  uint32_t  ulSystemCommandCOS;                            /*!< 0x00 System channel change of state command */
  uint32_t  ulReserved;                                    /*!< 0x04 Reserved */
} __CIFx_PACKED_POST SYSTEM_CHANNEL_SYSTEM_CONTROL_BLOCK;

/* System Channel: System Status Block */
typedef __CIFx_PACKED_PRE struct SYSTEM_CHANNEL_SYSTEM_STATUS_BLOCKtag
{
  uint32_t  ulSystemCOS;                                   /*!< 0x00 System channel change of state acknowledge */
  uint32_t  ulSystemStatus;                                /*!< 0x04 Actual system state */
  uint32_t  ulSystemError;                                 /*!< 0x08 Actual system error */
  uint32_t  ulBootError;                                   /*!< 0x0C Bootup error code (only valid if Cookie="BOOT") */
  uint32_t  ulTimeSinceStart;                              /*!< 0x10 time since start in seconds */
  uint16_t  usCpuLoad;                                     /*!< 0x14 cpu load in 0,01% units (10000 => 100%) */
  uint16_t  usReserved;                                    /*!< 0x16 Reserved */
  uint32_t  ulHWFeatures;                                  /*!< 0x18 Hardware features */
  uint8_t   abReserved[36];                                /*!< 0x1C:3F Reserved */
} __CIFx_PACKED_POST SYSTEM_CHANNEL_SYSTEM_STATUS_BLOCK;

/*****************************************************************************/
/*! Board Information structure                                              */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct BOARD_INFORMATIONtag
{
  int32_t    lBoardError;                                  /*!< Global Board error. Set when device specific data must not be used */
  char       abBoardName[CIFx_MAX_INFO_NAME_LENTH];        /*!< Global board name              */
  char       abBoardAlias[CIFx_MAX_INFO_NAME_LENTH];       /*!< Global board alias name        */
  uint32_t   ulBoardID;                                    /*!< Unique board ID, driver created*/
  uint32_t   ulSystemError;                                /*!< System error                   */
  uint32_t   ulPhysicalAddress;                            /*!< Physical memory address        */
  uint32_t   ulIrqNumber;                                  /*!< Hardware interrupt number      */
  uint8_t    bIrqEnabled;                                  /*!< Hardware interrupt enable flag */
  uint32_t   ulChannelCnt;                                 /*!< Number of available channels   */
  uint32_t   ulDpmTotalSize;                               /*!< Dual-Port memory size in bytes */
  SYSTEM_CHANNEL_SYSTEM_INFO_BLOCK tSystemInfo;                 /*!< System information             */
} __CIFx_PACKED_POST BOARD_INFORMATION;

/*****************************************************************************/
/*! Channel Information structure                                            */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct CHANNEL_INFORMATIONtag
{
  char       abBoardName[CIFx_MAX_INFO_NAME_LENTH];        /*!< Global board name              */
  char       abBoardAlias[CIFx_MAX_INFO_NAME_LENTH];       /*!< Global board alias name        */
  uint32_t   ulDeviceNumber;                               /*!< Global board device number     */
  uint32_t   ulSerialNumber;                               /*!< Global board serial number     */

  uint16_t   usFWMajor;                                    /*!< Major Version of Channel Firmware  */
  uint16_t   usFWMinor;                                    /*!< Minor Version of Channel Firmware  */
  uint16_t   usFWBuild;                                    /*!< Build number of Channel Firmware   */
  uint16_t   usFWRevision;                                 /*!< Revision of Channel Firmware       */
  uint8_t    bFWNameLength;                                /*!< Length  of FW Name                 */
  uint8_t    abFWName[63];                                 /*!< Firmware Name                      */
  uint16_t   usFWYear;                                     /*!< Build Year of Firmware             */
  uint8_t    bFWMonth;                                     /*!< Build Month of Firmware (1..12)    */
  uint8_t    bFWDay;                                       /*!< Build Day of Firmware (1..31)      */

  uint32_t   ulChannelError;                               /*!< Channel error                  */
  uint32_t   ulOpenCnt;                                    /*!< Channel open counter           */
  uint32_t   ulPutPacketCnt;                               /*!< Number of put packet commands  */
  uint32_t   ulGetPacketCnt;                               /*!< Number of get packet commands  */
  uint32_t   ulMailboxSize;                                /*!< Mailbox packet size in bytes   */
  uint32_t   ulIOInAreaCnt;                                /*!< Number of IO IN areas          */
  uint32_t   ulIOOutAreaCnt;                               /*!< Number of IO OUT areas         */
  uint32_t   ulHskSize;                                    /*!< Size of the handshake cells    */
  uint32_t   ulNetxFlags;                                  /*!< Actual netX state flags        */
  uint32_t   ulHostFlags;                                  /*!< Actual Host flags              */
  uint32_t   ulHostCOSFlags;                               /*!< Actual Host COS flags          */
  uint32_t   ulDeviceCOSFlags;                             /*!< Actual Device COS flags        */

} __CIFx_PACKED_POST CHANNEL_INFORMATION;

/*****************************************************************************/
/*! IO Area Information structure                                            */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct CHANNEL_IO_INFORMATIONtag
{
  uint32_t ulTotalSize;                  /*!< Total IO area size in byte */
  uint32_t ulReserved;                   /*!< reserved for further use */
  uint32_t ulIOMode;                     /*!< Exchange mode */
} __CIFx_PACKED_POST CHANNEL_IO_INFORMATION;

/*****************************************************************************/
/*! Memory Information structure                                             */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct MEMORY_INFORMATIONtag
{
  void*         pvMemoryID;           /*!< Identification of the memory area      */
  void**        ppvMemoryPtr;         /*!< Memory pointer                         */
  uint32_t*     pulMemorySize;        /*!< Complete size of the mapped memory     */
  uint32_t      ulChannel;            /*!< Requested channel number               */
  uint32_t*     pulChannelStartOffset;/*!< Start offset of the requested channel  */
  uint32_t*     pulChannelSize;       /*!< Memory size of the requested channel   */
} __CIFx_PACKED_POST MEMORY_INFORMATION;

/*****************************************************************************/
/*! PLC Memory Information structure                                         */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct PLC_MEMORY_INFORMATIONtag
{
  void*            pvMemoryID;           /*!< Identification of the memory area      */
  void**           ppvMemoryPtr;         /*!< Memory pointer                         */
  uint32_t         ulAreaDefinition;     /*!< Input/output area                      */
  uint32_t         ulAreaNumber;         /*!< Area number                            */
  uint32_t*        pulIOAreaStartOffset; /*!< Start offset                           */
  uint32_t*        pulIOAreaSize;        /*!< Memory size                            */
} __CIFx_PACKED_POST PLC_MEMORY_INFORMATION;


/***************************************************************************/
/* Driver dependent information */

#define CIFX_MAX_PACKET_SIZE               1596                  /*!< Maximum size of the RCX packet in bytes */
#define CIFX_PACKET_HEADER_SIZE            40                    /*!< Maximum size of the RCX packet header in bytes */
#define CIFX_MAX_DATA_SIZE   (CIFX_MAX_PACKET_SIZE - CIFX_PACKET_HEADER_SIZE) /*!< Maximum RCX packet data size */

#define CIFX_MSK_PACKET_ANSWER             0x00000001            /*!< Packet answer bit */

/*****************************************************************************/
/*! Packet header                                                            */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct CIFX_PACKET_HEADERtag
{
  uint32_t   ulDest;   /*!< destination of packet, process queue */
  uint32_t   ulSrc;    /*!< source of packet, process queue */
  uint32_t   ulDestId; /*!< destination reference of packet */
  uint32_t   ulSrcId;  /*!< source reference of packet */
  uint32_t   ulLen;    /*!< length of packet data without header */
  uint32_t   ulId;     /*!< identification handle of sender */
  uint32_t   ulState;  /*!< status code of operation */
  uint32_t   ulCmd;    /*!< packet command defined in TLR_Commands.h */
  uint32_t   ulExt;    /*!< extension */
  uint32_t   ulRout;   /*!< router */
} __CIFx_PACKED_POST CIFX_PACKET_HEADER;

/*****************************************************************************/
/*! Definition of the rcX Packet                                             */
/*****************************************************************************/
typedef __CIFx_PACKED_PRE struct CIFX_PACKETtag
{
  CIFX_PACKET_HEADER  tHeader;                   /**! */
  uint8_t             abData[CIFX_MAX_DATA_SIZE];
} __CIFx_PACKED_POST CIFX_PACKET;

#define CIFX_CALLBACK_ACTIVE   0
#define CIFX_CALLBACK_FINISHED 1
typedef void(APIENTRY *PFN_PROGRESS_CALLBACK)(uint32_t ulStep, uint32_t ulMaxStep, void* pvUser, int8_t bFinished, int32_t lError);
typedef void(APIENTRY *PFN_RECV_PKT_CALLBACK)(CIFX_PACKET* ptRecvPkt, void* pvUser);
typedef void(APIENTRY *PFN_NOTIFY_CALLBACK)  (uint32_t ulNotification, uint32_t ulDataLen, void* pvData, void* pvUser);

#define DOWNLOAD_MODE_FIRMWARE    1
#define DOWNLOAD_MODE_CONFIG      2
#define DOWNLOAD_MODE_FILE        3
#define DOWNLOAD_MODE_BOOTLOADER  4 /*!< Download bootloader update to target. */
#define DOWNLOAD_MODE_LICENSECODE 5 /*!< License update code.                  */
#define DOWNLOAD_MODE_MODULE      6


/***************************************************************************
* API Functions
***************************************************************************/

/* Global driver functions */
int32_t APIENTRY xDriverOpen                 ( CIFXHANDLE* phDriver);
int32_t APIENTRY xDriverClose                ( CIFXHANDLE  hDriver);
int32_t APIENTRY xDriverGetInformation       ( CIFXHANDLE  hDriver, uint32_t ulSize, void* pvDriverInfo);
int32_t APIENTRY xDriverGetErrorDescription  ( int32_t     lError,  char* szBuffer, uint32_t ulBufferLen);
int32_t APIENTRY xDriverEnumBoards           ( CIFXHANDLE  hDriver, uint32_t ulBoard, uint32_t ulSize, void* pvBoardInfo);
int32_t APIENTRY xDriverEnumChannels         ( CIFXHANDLE  hDriver, uint32_t ulBoard, uint32_t ulChannel, uint32_t ulSize, void* pvChannelInfo);
int32_t APIENTRY xDriverMemoryPointer        ( CIFXHANDLE  hDriver, uint32_t ulBoard, uint32_t ulCmd,void* pvMemoryInfo);
int32_t APIENTRY xDriverRestartDevice        ( CIFXHANDLE  hDriver, char* szBoardName,     void* pvData);

/* System device depending functions */
int32_t APIENTRY xSysdeviceOpen              ( CIFXHANDLE  hDriver, char* szBoard, CIFXHANDLE* phSysdevice);
int32_t APIENTRY xSysdeviceClose             ( CIFXHANDLE  hSysdevice);
int32_t APIENTRY xSysdeviceGetMBXState       ( CIFXHANDLE  hSysdevice, uint32_t* pulRecvPktCount, uint32_t* pulSendPktCount);
int32_t APIENTRY xSysdevicePutPacket         ( CIFXHANDLE  hSysdevice, CIFX_PACKET* ptSendPkt, uint32_t ulTimeout);
int32_t APIENTRY xSysdeviceGetPacket         ( CIFXHANDLE  hSysdevice, uint32_t ulSize, CIFX_PACKET* ptRecvPkt, uint32_t ulTimeout);
int32_t APIENTRY xSysdeviceInfo              ( CIFXHANDLE  hSysdevice, uint32_t ulCmd, uint32_t ulSize, void* pvInfo);

int32_t APIENTRY xSysdeviceFindFirstFile     ( CIFXHANDLE  hSysdevice, uint32_t ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
int32_t APIENTRY xSysdeviceFindNextFile      ( CIFXHANDLE  hSysdevice, uint32_t ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
int32_t APIENTRY xSysdeviceDownload          ( CIFXHANDLE  hSysdevice, uint32_t ulChannel, uint32_t ulMode, char* pszFileName, uint8_t* pabFileData, uint32_t ulFileSize,
                                               PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
int32_t APIENTRY xSysdeviceUpload            ( CIFXHANDLE  hSysdevice, uint32_t ulChannel, uint32_t ulMode, char* pszFileName, uint8_t* pabFileData, uint32_t* pulFileSize,
                                               PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);

int32_t APIENTRY xSysdeviceReset             ( CIFXHANDLE  hSysdevice, uint32_t ulTimeout);
int32_t APIENTRY xSysdeviceBootstart         ( CIFXHANDLE  hSysdevice, uint32_t ulTimeout);

int32_t APIENTRY xSysdeviceExtendedMemory    ( CIFXHANDLE  hSysdevice, uint32_t ulCmd, CIFX_EXTENDED_MEMORY_INFORMATION* ptExtMemData);

/* Channel depending functions */
int32_t APIENTRY xChannelOpen                ( CIFXHANDLE  hDriver,  char* szBoard, uint32_t ulChannel, CIFXHANDLE* phChannel);
int32_t APIENTRY xChannelClose               ( CIFXHANDLE  hChannel);
int32_t APIENTRY xChannelFindFirstFile       ( CIFXHANDLE  hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
int32_t APIENTRY xChannelFindNextFile        ( CIFXHANDLE  hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);

int32_t APIENTRY xChannelDownload            ( CIFXHANDLE  hChannel, uint32_t ulMode, char* pszFileName, uint8_t* pabFileData, uint32_t ulFileSize,
                                               PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
int32_t APIENTRY xChannelUpload              ( CIFXHANDLE  hChannel, uint32_t ulMode, char* pszFileName, uint8_t* pabFileData, uint32_t* pulFileSize,
                                               PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);

int32_t APIENTRY xChannelGetMBXState         ( CIFXHANDLE  hChannel, uint32_t* pulRecvPktCount, uint32_t* pulSendPktCount);
int32_t APIENTRY xChannelPutPacket           ( CIFXHANDLE  hChannel, CIFX_PACKET*  ptSendPkt, uint32_t ulTimeout);
int32_t APIENTRY xChannelGetPacket           ( CIFXHANDLE  hChannel, uint32_t ulSize, CIFX_PACKET* ptRecvPkt, uint32_t ulTimeout);
int32_t APIENTRY xChannelGetSendPacket       ( CIFXHANDLE  hChannel, uint32_t ulSize, CIFX_PACKET* ptRecvPkt);

int32_t APIENTRY xChannelConfigLock          ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout);
int32_t APIENTRY xChannelReset               ( CIFXHANDLE  hChannel, uint32_t ulResetMode, uint32_t ulTimeout);
int32_t APIENTRY xChannelInfo                ( CIFXHANDLE  hChannel, uint32_t ulSize, void* pvChannelInfo);
int32_t APIENTRY xChannelWatchdog            ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulTrigger);
int32_t APIENTRY xChannelHostState           ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout);
int32_t APIENTRY xChannelBusState            ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout);
int32_t APIENTRY xChannelDMAState            ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState);

int32_t APIENTRY xChannelIOInfo              ( CIFXHANDLE  hChannel, uint32_t ulCmd,        uint32_t ulAreaNumber, uint32_t ulSize, void* pvData);
int32_t APIENTRY xChannelIORead              ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulOffset,     uint32_t ulDataLen, void* pvData, uint32_t ulTimeout);
int32_t APIENTRY xChannelIOWrite             ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulOffset,     uint32_t ulDataLen, void* pvData, uint32_t ulTimeout);
int32_t APIENTRY xChannelIOReadSendData      ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulOffset,     uint32_t ulDataLen, void* pvData);

int32_t APIENTRY xChannelControlBlock        ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData);
int32_t APIENTRY xChannelCommonStatusBlock   ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData);
int32_t APIENTRY xChannelExtendedStatusBlock ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData);
int32_t APIENTRY xChannelUserBlock           ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData);

int32_t APIENTRY xChannelPLCMemoryPtr        ( CIFXHANDLE  hChannel, uint32_t ulCmd,        void* pvMemoryInfo);
int32_t APIENTRY xChannelPLCIsReadReady      ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t* pulReadState);
int32_t APIENTRY xChannelPLCIsWriteReady     ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t* pulWriteState);
int32_t APIENTRY xChannelPLCActivateWrite    ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber);
int32_t APIENTRY xChannelPLCActivateRead     ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber);

int32_t APIENTRY xChannelRegisterNotification  ( CIFXHANDLE  hChannel, uint32_t ulNotification, PFN_NOTIFY_CALLBACK  pfnCallback, void* pvUser);
int32_t APIENTRY xChannelUnregisterNotification( CIFXHANDLE  hChannel, uint32_t ulNotification);
int32_t APIENTRY xChannelSyncState             ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t ulTimeout, uint32_t* pulErrorCount);
/***************************************************************************/

/***************************************************************************
* API Functionpointer definitions
***************************************************************************/

/* Global driver functions */
typedef int32_t (APIENTRY *PFN_XDRIVEROPEN)                ( CIFXHANDLE* phDriver);
typedef int32_t (APIENTRY *PFN_XDRIVERCLOSE)               ( CIFXHANDLE  hDriver);
typedef int32_t (APIENTRY *PFN_XDRIVERGETINFORMATION)      ( CIFXHANDLE  hDriver, uint32_t ulSize,   void*    pvDriverInfo);
typedef int32_t (APIENTRY *PFN_XDRIVERGETERRORDESCRIPTION) ( int32_t     lError,  char*    szBuffer, uint32_t ulBufferLen);
typedef int32_t (APIENTRY *PFN_XDRIVERENUMBOARDS)          ( CIFXHANDLE  hDriver, uint32_t ulBoard,  uint32_t ulSize,    void*    pvBoardInfo);
typedef int32_t (APIENTRY *PFN_XDRIVERENUMCHANNELS)        ( CIFXHANDLE  hDriver, uint32_t ulBoard,  uint32_t ulChannel, uint32_t ulSize, void* pvChannelInfo);
typedef int32_t (APIENTRY *PFN_XDRIVERMEMORYPOINTER)       ( CIFXHANDLE  hDriver, uint32_t ulBoard,  uint32_t ulCmd,     void*    pvMemoryInfo);
typedef int32_t (APIENTRY *PFN_XDRIVERRESTARTDEVICE)       ( CIFXHANDLE  hDriver, char* szBoardName, void* pvData);

/* System device depending functions */
typedef int32_t (APIENTRY *PFN_XSYSDEVICEOPEN)             ( CIFXHANDLE  hDriver, char* szBoard, CIFXHANDLE* phSysdevice);
typedef int32_t (APIENTRY *PFN_XSYSDEVICECLOSE)            ( CIFXHANDLE  hSysdevice);
typedef int32_t (APIENTRY *PFN_XSYSDEVICEGETMBXSTATE)      ( CIFXHANDLE  hSysdevice, uint32_t* pulRecvPktCount, uint32_t* pulSendPktCount);
typedef int32_t (APIENTRY *PFN_XSYSDEVICEPUTPACKET)        ( CIFXHANDLE  hSysdevice, CIFX_PACKET* ptSendPkt, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XSYSDEVICEGETPACKET)        ( CIFXHANDLE  hSysdevice, uint32_t ulSize, CIFX_PACKET* ptRecvPkt, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XSYSDEVICEINFO)             ( CIFXHANDLE  hSysdevice, uint32_t ulCmd, uint32_t ulSize, void* pvInfo);

typedef int32_t (APIENTRY *PFN_XSYSDEVICEFINDFIRSTFILE)    ( CIFXHANDLE  hSysdevice, uint32_t ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
typedef int32_t (APIENTRY *PFN_XSYSDEVICEFINDNEXTFILE)     ( CIFXHANDLE  hSysdevice, uint32_t ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
typedef int32_t (APIENTRY *PFN_XSYSDEVICEDOWNLOAD)         ( CIFXHANDLE  hSysdevice, uint32_t ulChannel, uint32_t ulMode, char* pszFileName, uint8_t* pabFileData, uint32_t ulFileSize,
                                                             PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
typedef int32_t (APIENTRY *PFN_XSYSDEVICEUPLOAD)           ( CIFXHANDLE  hSysdevice, uint32_t ulChannel, uint32_t ulMode, char* pszFileName, uint8_t* pabFileData, uint32_t* pulFileSize,
                                                             PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);

typedef int32_t (APIENTRY *PFN_XSYSDEVICERESET)            ( CIFXHANDLE  hSysdevice, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XSYSDEVICEBOOTSTART)        ( CIFXHANDLE  hSysdevice, uint32_t ulTimeout);

typedef int32_t (APIENTRY *PFN_XSYSDEVICEEXTENDEDMEMORY)   ( CIFXHANDLE  hSysdevice, uint32_t ulCmd, CIFX_EXTENDED_MEMORY_INFORMATION* ptExtMemData);

/* Channel depending functions */
typedef int32_t (APIENTRY *PFN_XCHANNELOPEN)               ( CIFXHANDLE  hDriver,  char* szBoard, uint32_t ulChannel, CIFXHANDLE* phChannel);
typedef int32_t (APIENTRY *PFN_XCHANNELCLOSE)              ( CIFXHANDLE  hChannel);
typedef int32_t (APIENTRY *PFN_XCHANNELFINDFIRSTFILE)      ( CIFXHANDLE  hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
typedef int32_t (APIENTRY *PFN_XCHANNELFINDNEXTFILE)       ( CIFXHANDLE  hChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);

typedef int32_t (APIENTRY *PFN_XCHANNELDOWNLOAD)           ( CIFXHANDLE  hChannel, uint32_t ulMode, char* pszFileName, uint8_t* pabFileData, uint32_t ulFileSize,
                                                             PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
typedef int32_t (APIENTRY *PFN_XCHANNELUPLOAD)             ( CIFXHANDLE  hChannel, uint32_t ulMode, char* pszFileName, uint8_t* pabFileData, uint32_t* pulFileSize,
                                                             PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);

typedef int32_t (APIENTRY *PFN_XCHANNELGETMBXSTATE)        ( CIFXHANDLE  hChannel, uint32_t* pulRecvPktCount, uint32_t* pulSendPktCount);
typedef int32_t (APIENTRY *PFN_XCHANNELPUTPACKET)          ( CIFXHANDLE  hChannel, CIFX_PACKET*  ptSendPkt, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XCHANNELGETPACKET)          ( CIFXHANDLE  hChannel, uint32_t ulSize, CIFX_PACKET* ptRecvPkt, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XCHANNELGETSENDPACKET)      ( CIFXHANDLE  hChannel, uint32_t ulSize, CIFX_PACKET* ptRecvPkt);

typedef int32_t (APIENTRY *PFN_XCHANNELCONFIGLOCK)         ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XCHANNELRESET)              ( CIFXHANDLE  hChannel, uint32_t ulResetMode, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XCHANNELINFO)               ( CIFXHANDLE  hChannel, uint32_t ulSize, void* pvChannelInfo);
typedef int32_t (APIENTRY *PFN_XCHANNELWATCHDOG)           ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulTrigger);
typedef int32_t (APIENTRY *PFN_XCHANNELHOSTSTATE)          ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XCHANNELBUSSTATE)           ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XCHANNELDMASTATE)           ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState);

typedef int32_t (APIENTRY *PFN_XCHANNELIOINFO)             ( CIFXHANDLE  hChannel, uint32_t ulCmd,        uint32_t ulAreaNumber, uint32_t ulSize,    void* pvData);
typedef int32_t (APIENTRY *PFN_XCHANNELIOREAD)             ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulOffset,     uint32_t ulDataLen, void* pvData, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XCHANNELIOWRITE)            ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulOffset,     uint32_t ulDataLen, void* pvData, uint32_t ulTimeout);
typedef int32_t (APIENTRY *PFN_XCHANNELIOREADSENDDATA)     ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulOffset,     uint32_t ulDataLen, void* pvData);

typedef int32_t (APIENTRY *PFN_XCHANNELCONTROLBLOCK)       ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData);
typedef int32_t (APIENTRY *PFN_XCHANNELCOMMONSTATUSBLOCK)  ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData);
typedef int32_t (APIENTRY *PFN_XCHANNELEXTENDEDSTATUSBLOCK)( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData);
typedef int32_t (APIENTRY *PFN_XCHANNELUSERBLOCK)          ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData);

typedef int32_t (APIENTRY *PFN_XCHANNELPLCMEMORYPTR)       ( CIFXHANDLE  hChannel, uint32_t ulCmd,        void* pvMemoryInfo);
typedef int32_t (APIENTRY *PFN_XCHANNELPLCISREADREADY)     ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t* pulReadState);
typedef int32_t (APIENTRY *PFN_XCHANNELPLCISWRITEREADY)    ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t* pulWriteState);
typedef int32_t (APIENTRY *PFN_XCHANNELPLCACTIVATEWRITE)   ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber);
typedef int32_t (APIENTRY *PFN_XCHANNELPLCACTIVATEREAD)    ( CIFXHANDLE  hChannel, uint32_t ulAreaNumber);

typedef int32_t (APIENTRY *PFN_XCHANNELREGISTERNOTIFICATION)  ( CIFXHANDLE  hChannel, uint32_t ulNotification, PFN_NOTIFY_CALLBACK  pfnCallback, void* pvUser);
typedef int32_t (APIENTRY *PFN_XCHANNELUNREGISTERNOTIFICATION)( CIFXHANDLE  hChannel, uint32_t ulNotification);
typedef int32_t (APIENTRY *PFN_XCHANNELSYNCSTATE)             ( CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t ulTimeout, uint32_t* pulErrorCount);
/***************************************************************************/

#ifdef __cplusplus
}
#endif

#if defined(_MSC_VER)
  #if _MSC_VER >= 1000
    #pragma pack()            /* Always align structures to default boundery */
  #endif /* _MSC_VER >= 1000 */
#endif /* _MSC_VER */

#undef __CIFx_PACKED_PRE
#undef __CIFx_PACKED_POST

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/

#endif  /* __CIFxUSER_H */
