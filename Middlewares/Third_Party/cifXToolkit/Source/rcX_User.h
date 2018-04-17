/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: rcX_User.h 6827 2015-03-31 15:23:50Z Robert $:

  Description:
    Definition file for the rcX operating system

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2014-09-17  Added RCX_HW_DEV_CLASS_NETIC_52
    2014-07-07  Added support for IAR C/C++ Compiler (ARM Cores only)
    2014-04-28  Added support for armcc compiler
    2013-12-17  Added RCX_HW_DEV_CLASS_NETPLC_J500
    2013-11-07  Added RCX_HW_DEV_CLASS_NETSMART_T51, RCX_HW_DEV_CLASS_NETSCADA_T52,
                RCX_HW_DEV_CLASS_NETSAFETY_51, RCX_HW_DEV_CLASS_NETSAFETY_52
    2013-10-01  Added RCX_HW_DEV_CLASS_NETRAPID_52
    2013-05-28  Added RCX_HW_DEV_CLASS_NETSCOPE_C100
    2013-04-03  Added RCX_HW_DEV_CLASS_NETHOST_T100
    2013-01-15  Added RCX_HW_DEV_CLASS_COMX_51, RCX_HW_DEV_CLASS_NETJACK_51
    2012-08-03  Added RCX_HW_DEV_CLASS_CHIP_NETX_52, RCX_HW_DEV_CLASS_NETSCADA_T50,
                RCX_HW_DEV_CLASS_NETSMART_50, RCX_HW_DEV_CLASS_IOLINK_GW_51,
                RCX_HW_DEV_CLASS_NETHMI_B500
    2012-07-23  Changed RCX_MAX_PACKET_SIZE to 1596 Bytes (Comm. Channel Mailbox Size)
    2012-05-29  Added DPM structure NETX_8K_DPM_COMM_CHANNEL
                for hardware with only 8 KByte DPM (e.g. COMX10)
    2012-02-29  Added RCX_HW_DEV_CLASS_GW_EU5C
    2012-01-31  Added RCX_HW_DEV_CLASS_NETSCADA_T51,
                RCX_HW_DEV_CLASS_CHIP_NETX_51, RCX_HW_DEV_CLASS_NETRAPID_51
    2011-12-12  Updated ulHWFeatures definitions for extended memory (MRAM)
    2011-12-06  Added ulHWFeatures into SYSTEM_STATUS_BLOCK (RTC/MRAM)
    2011-10-31  Added RCX_HW_DEV_CLASS_NETRAPID_10/50
    2011-07-07  Added PROT_CLASS_3S_PLC_HANDLER
    2010-12-10  Added RCX_HW_DEV_CLASS_NETJACK_10/50/100/500 and RCX_HW_DEV_CLASS_NETLINK_10_USB
    2010-11-29  fixed Mantis 11689 (update rcx_user.h (sync stuff))
    2010-11-15  Added RCX_HW_DEV_CLASS_COMX_50
                Added RCX_PROT_CLASS_VARAN
    2010-11-10  Added RCX_HW_DEV_CLASS_COMX_10
                Added RCX_HW_DEV_CLASS_NETIC_10
                Rename RCX_HW_DEV_CLASS_COMX to RCX_HW_DEV_CLASS_COMX_100
                Rename RCX_HW_DEV_CLASS_NETIC to RCX_HW_DEV_CLASS_NETIC_50
    2010-09-02  Added RCX_HW_DEV_CLASS_CHIP_NETX_10
    2010-08-03  Added RCX_E_INVALID_ALIGNMENT
    2010-07-22  Added RCX_PROT_CLASS_DF1
    2010-05-04  Added HW option validation start/end defines
    2010-05-04  Added "System Status" defines
    2010-03-23  File created.

**************************************************************************************/


/* Prevent multiple inclusion */
#ifndef __RCX_USER_H
#define __RCX_USER_H

#include <stdint.h>

/*---------------------------------------------------------------------------*/
/* Compiler settings */
#ifdef _MSC_VER
  #if _MSC_VER >= 1000
    #define __RCX_PACKED_PRE
    #define __RCX_PACKED_POST
    #pragma once
    #pragma pack(1)            /* Always align structures to byte boundery */
    #ifndef STRICT             /* Check Typdefinition */
      #define STRICT
    #endif
  #endif /* _MSC_VER >= 1000 */
#endif /* _MSC_VER */

/* support for GNU compiler */
#ifdef __GNUC__
  #define __RCX_PACKED_PRE
  #define __RCX_PACKED_POST    __attribute__((__packed__))
#endif

/* support for REALVIEW ARM and IAR compiler (ARM cores only) */
#if defined (__ADS__) || defined (__REALVIEW__) || defined (__CC_ARM) || defined (__ICCARM__)
  #define __RCX_PACKED_PRE   __packed
  #define __RCX_PACKED_POST
#endif

/*===========================================================================*/
/*                                                                           */
/* DEFAULT DPM structure                                                     */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/*   -------------------------    DPM Offset 0                               */
/*  | System Channel          |                                              */
/*   -------------------------                                               */
/*  | Handshake channel       |                                              */
/*   -------------------------                                               */
/*  | Communication channel 0 |                                              */
/*   -------------------------                                               */
/*  | Communication channel 1 |                                              */
/*   -------------------------                                               */
/*  | Communication channel 2 |                                              */
/*   -------------------------                                               */
/*  | Communication channel 3 |                                              */
/*   -------------------------                                               */
/*  | Application channel   0 |                                              */
/*   -------------------------                                               */
/*  | Application channel   1 |                                              */
/*   -------------------------   DPM Offset xxxx                             */
/*===========================================================================*/
/*\/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ */

/* Global definitions */
#define NETX_MAX_SUPPORTED_CHANNELS     8               /*!< Maximum number of possible channels */

/* Global system channel definitions */
#define NETX_SYSTEM_HSK_CELL_OFFSET     0               /*!< Offset of the system handshake cells */
#define NETX_SYSTEM_BLOCK_VERSION       0               /*!< Version of the system block structure */
#define NETX_SYSTEM_CHANNEL_SIZE        512             /*!< Size of the system channel in bytes */
#define NETX_SYSTEM_MAILBOX_MIN_SIZE    124             /*!< Size of a system packet mailbox in bytes */

#define NETX_SYSTEM_CHANNEL_INDEX       0               /*!< Index of the system channel, always 0 */
#define NETX_HANDSHAKE_CHANNEL_INDEX    1               /*!< Index of the handshake channel, always 1 if available */
#define NETX_COM_CHANNEL_START_INDEX    2               /*!< Start index of communication channel 0  */

/* Global handshake channel size */
#define NETX_HANDSHAKE_CHANNEL_SIZE     256             /*!< Length of the handshake channel in bytes */
#define NETX_HANDSHAKE_PAIRS            16              /*!< Number of possible handshake pairs */

/* Global communication channel definitions */
#define NETX_STATUS_BLOCK_VERSION       2               /*!< version of the common status block structure */
#define NETX_EXT_STATE_SIZE             432             /*!< Default size of the extended state block */

#define NETX_CHANNEL_MAILBOX_SIZE       1596            /*!< Default size of a channel packet mailbox in bytes */
#define NETX_HP_IO_DATA_SIZE            64              /*!< Default size of the high prio I/O data */
#define NETX_IO_DATA_SIZE               5760            /*!< Default I/O data size in bytes */
#define NETX_IO_DATA_SIZE_8K_DPM        1536            /*!< I/O data size in bytes for hardware with 8KByte DPM */

/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*XX                                                           XXXXXXXXXXXXXX*/
/*XX SYSTEM CHANNEL LAYOUT                                     XXXXXXXXXXXXXX*/
/*XX                                                           XXXXXXXXXXXXXX*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/

/*****************************************************************************/
/*! System channel information structure (Size always 16 Byte)               */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_SYSTEM_CHANNEL_INFOtag
{
  uint8_t   bChannelType;                                        /*!< 0x00 Type of this channel */
  uint8_t   bReserved;                                           /*!< 0x01 reserved */
  uint8_t   bSizePositionOfHandshake;                            /*!< 0x02 Size and position of the handshake cells */
  uint8_t   bNumberOfBlocks;                                     /*!< 0x03 Number of blocks in this channel */
  uint32_t  ulSizeOfChannel;                                     /*!< 0x04 Size of channel in bytes */
  uint16_t  usSizeOfMailbox;                                     /*!< 0x08 Size of the send and receive mailbox */
  uint16_t  usMailboxStartOffset;                                /*!< 0x0A Start offset of the mailbox structure (see NETX_MAILBOX) */
  uint8_t   abReserved[4];                                       /*!< 0x0C:0x0F Reserved area */
} __RCX_PACKED_POST NETX_SYSTEM_CHANNEL_INFO;

/*****************************************************************************/
/*! Handshake channel information structure (Size always 16 Byte)            */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_HANDSHAKE_CHANNEL_INFOtag
{
  uint8_t   bChannelType;                                        /*!< 0x00 Type of this channel */
  uint8_t   bReserved[3];                                        /*!< 0x01 reserved */
  uint32_t  ulSizeOfChannel;                                     /*!< 0x04 Size of channel in bytes */
  uint8_t   abReserved[8];                                       /*!< 0x08:0x0F Reserved area */
} __RCX_PACKED_POST NETX_HANDSHAKE_CHANNEL_INFO;

/*****************************************************************************/
/*! Communication channel information structure (Size always 16 Byte)        */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_COMMUNICATION_CHANNEL_INFOtag
{
  uint8_t   bChannelType;                                        /*!< 0x00 Type of this channel */
  uint8_t   bChannelId;                                          /*!< 0x01 Channel / Port ID */
  uint8_t   bSizePositionOfHandshake;                            /*!< 0x02 Size and position of the handshake cells */
  uint8_t   bNumberOfBlocks;                                     /*!< 0x03 Number of blocks in this channel */
  uint32_t  ulSizeOfChannel;                                     /*!< 0x04 Size of channel in bytes */
  uint16_t  usCommunicationClass;                                /*!< 0x08 Communication Class (Master, Slave...) */
  uint16_t  usProtocolClass;                                     /*!< 0x0A Protocol Class (PROFIBUS, PROFINET....) */
  uint16_t  usProtocolConformanceClass;                          /*!< 0x0C Protocol Conformance Class (DPV1, DPV2...) */
  uint8_t   abReserved[2];                                       /*!< 0x0E:0x0F Reserved area */
} __RCX_PACKED_POST NETX_COMMUNICATION_CHANNEL_INFO;

/*****************************************************************************/
/*! Application channel information structure (Size always 16 Byte)          */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_APPLICATION_CHANNEL_INFOtag
{
  uint8_t   bChannelType;                                        /*!< 0x00 Type of this channel */
  uint8_t   bChannelId;                                          /*!< 0x01 Channel / Port ID */
  uint8_t   bSizePositionOfHandshake;                            /*!< 0x02 Size and position of the handshake cells */
  uint8_t   bNumberOfBlocks;                                     /*!< 0x03 Number of blocks in this channel */
  uint32_t  ulSizeOfChannel;                                     /*!< 0x04 Size of channel in bytes */
  uint8_t   abReserved[8];                                       /*!< 0x0C:0x0F Reserved area */
} __RCX_PACKED_POST NETX_APPLICATION_CHANNEL_INFO;

/*****************************************************************************/
/*! System information block (Size = 48 Byte)                                */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_SYSTEM_INFO_BLOCKtag
{
  uint8_t   abCookie[4];                                         /*!< 0x00 "netX" cookie */
  uint32_t  ulDpmTotalSize;                                      /*!< 0x04 Total Size of the whole dual-port memory in bytes */
  uint32_t  ulDeviceNumber;                                      /*!< 0x08 Device number */
  uint32_t  ulSerialNumber;                                      /*!< 0x0C Serial number */
  uint16_t  ausHwOptions[4];                                     /*!< 0x10 Hardware options, xC port 0..3 */
  uint16_t  usManufacturer;                                      /*!< 0x18 Manufacturer Location */
  uint16_t  usProductionDate;                                    /*!< 0x1A Date of production */
  uint32_t  ulLicenseFlags1;                                     /*!< 0x1C License code flags 1 */
  uint32_t  ulLicenseFlags2;                                     /*!< 0x20 License code flags 2 */
  uint16_t  usNetxLicenseID;                                     /*!< 0x24 netX license identification */
  uint16_t  usNetxLicenseFlags;                                  /*!< 0x26 netX license flags */
  uint16_t  usDeviceClass;                                       /*!< 0x28 netX device class */
  uint8_t   bHwRevision;                                         /*!< 0x2A Hardware revision index */
  uint8_t   bHwCompatibility;                                    /*!< 0x2B Hardware compatibility index */
  uint8_t   bDevIdNumber;                                        /*!< 0x2C Device identification number (rotary switch) */
  uint8_t   bReserved;                                           /*!< 0x2D Reserved byte */
  uint16_t  usReserved;                                          /*!< 0x2E:0x2F Reserved */
} __RCX_PACKED_POST NETX_SYSTEM_INFO_BLOCK;

/*****************************************************************************/
/*! Channel information block (Size always 16 Byte)                          */
/*****************************************************************************/
typedef __RCX_PACKED_PRE union NETX_CHANNEL_INFO_BLOCKtag
{
  NETX_SYSTEM_CHANNEL_INFO        tSystem;
  NETX_HANDSHAKE_CHANNEL_INFO     tHandshake;
  NETX_COMMUNICATION_CHANNEL_INFO tCom;
  NETX_APPLICATION_CHANNEL_INFO   tApp;
} __RCX_PACKED_POST NETX_CHANNEL_INFO_BLOCK;

/*****************************************************************************/
/*! System information block (Size = 8 Byte)                                 */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_SYSTEM_CONTROL_BLOCKtag
{
  uint32_t  ulSystemCommandCOS;                                  /*!< 0x00 System channel change of state command */
  uint32_t  ulReserved;                                          /*!< 0x04 Reserved */
} __RCX_PACKED_POST NETX_SYSTEM_CONTROL_BLOCK;

/*****************************************************************************/
/*! System status block (Size = 64 Byte)                                     */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_SYSTEM_STATUS_BLOCKtag
{
  uint32_t  ulSystemCOS;                                         /*!< 0x00 System channel change of state acknowledge */
  uint32_t  ulSystemStatus;                                      /*!< 0x04 Actual system state */
  uint32_t  ulSystemError;                                       /*!< 0x08 Actual system error */
  uint32_t  ulBootError;                                         /*!< 0x0C Bootup error (only set by 2nd Stage Bootloader) */
  uint32_t  ulTimeSinceStart;                                    /*!< 0x10 time since start in seconds */
  uint16_t  usCpuLoad;                                           /*!< 0x14 cpu load in 0,01% units (10000 => 100%) */
  uint16_t  usReserved;                                          /*!< 0x16 Reserved */
  uint32_t  ulHWFeatures;                                        /*!< 0x18 Hardware features */
  uint8_t   abReserved[36];                                      /*!< 0x1C:3F Reserved */
} __RCX_PACKED_POST NETX_SYSTEM_STATUS_BLOCK;

/*****************************************************************************/
/*! System send packet mailbox (Size 128 Byte)                               */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_SYSTEM_SEND_MAILBOXtag
{
  uint16_t  usPackagesAccepted;                                 /*!< Number of packages that can be accepted */
  uint16_t  usReserved;                                         /*!< Reserved */
  uint8_t   abSendMbx[NETX_SYSTEM_MAILBOX_MIN_SIZE];            /*!< Send mailbox packet buffer */
} __RCX_PACKED_POST NETX_SYSTEM_SEND_MAILBOX;

/*****************************************************************************/
/*! System receive packet mailbox (Size 128 Byte)                            */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_SYSTEM_RECV_MAILBOXtag
{
  uint16_t  usWaitingPackages;                                  /*!< Number of packages waiting to be processed */
  uint16_t  usReserved;                                         /*!< Reserved */
  uint8_t   abRecvMbx[NETX_SYSTEM_MAILBOX_MIN_SIZE];            /*!< Receive mailbox packet buffer */
} __RCX_PACKED_POST NETX_SYSTEM_RECV_MAILBOX;

/*****************************************************************************/
/*! Handshake cell definition                                                */
/*****************************************************************************/
typedef __RCX_PACKED_PRE union NETX_HANDSHAKE_CELLtag
{
  __RCX_PACKED_PRE struct
  {
    volatile uint8_t abData[2];        /*!< Data value, not belonging to handshake */
    volatile uint8_t bNetxFlags;       /*!< Device status flags (8Bit Mode) */
    volatile uint8_t bHostFlags;       /*!< Device command flags (8Bit Mode) */
  } __RCX_PACKED_POST t8Bit;

  __RCX_PACKED_PRE struct
  {
    volatile uint16_t usNetxFlags;     /*!< Device status flags (16Bit Mode) */
    volatile uint16_t usHostFlags;     /*!< Device command flags (16Bit Mode)*/
  } __RCX_PACKED_POST t16Bit;
  volatile uint32_t ulValue;            /*!< Handshake cell value */
} __RCX_PACKED_POST NETX_HANDSHAKE_CELL;

/*****************************************************************************/
/*! Structure of the whole system channel (DPM) (Size 512 Byte)              */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_SYSTEM_CHANNELtag
{
  NETX_SYSTEM_INFO_BLOCK      tSystemInfo;                                    /*!< 0x000:0x02F System information block */
  NETX_CHANNEL_INFO_BLOCK     atChannelInfo[NETX_MAX_SUPPORTED_CHANNELS];     /*!< 0x030:0x0AF Channel information block */
  NETX_HANDSHAKE_CELL         tSysHandshake;                                  /*!< 0x0B0:0x0B3 Handshake cells used, if not in Handshake block */
  uint8_t                     abReserved[4];                                  /*!< 0x0B4:0x0B7 unused/reserved */
  NETX_SYSTEM_CONTROL_BLOCK   tSystemControl;                                 /*!< 0x0B8:0x0BF System control block */
  NETX_SYSTEM_STATUS_BLOCK    tSystemState;                                   /*!< 0x0C0:0x0FF System state block */
  NETX_SYSTEM_SEND_MAILBOX    tSystemSendMailbox;                             /*!< 0x100:0x17F Send mailbox */
  NETX_SYSTEM_RECV_MAILBOX    tSystemRecvMailbox;                             /*!< 0x180:0x1FF Receive mailbox */
} __RCX_PACKED_POST NETX_SYSTEM_CHANNEL;

/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*XX                                                           XXXXXXXXXXXXXX*/
/*XX HANDSHAKE CHANNEL LAYOUT                                  XXXXXXXXXXXXXX*/
/*XX                                                           XXXXXXXXXXXXXX*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/

/*****************************************************************************/
/*! Handshake array definition                                               */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_HANDSHAKE_ARRAYtag
{
  NETX_HANDSHAKE_CELL atHsk[NETX_HANDSHAKE_PAIRS]; /*!< Handshake cell block definition */
} __RCX_PACKED_POST NETX_HANDSHAKE_ARRAY;

/*****************************************************************************/
/*! Handshake channel definition                                             */
/*****************************************************************************/
typedef struct NETX_HANDSHAKE_CHANNELtag
{
  NETX_HANDSHAKE_CELL tSysFlags;                                                  /*!< 0x00 System handshake flags */
  NETX_HANDSHAKE_CELL tHskFlags;                                                  /*!< 0x04 not used */
  NETX_HANDSHAKE_CELL tCommFlags0;                                                /*!< 0x08 channel 0 handshake flags */
  NETX_HANDSHAKE_CELL tCommFlags1;                                                /*!< 0x0C channel 1 handshake flags */
  NETX_HANDSHAKE_CELL tCommFlags2;                                                /*!< 0x10 channel 2 handshake flags */
  NETX_HANDSHAKE_CELL tCommFlags3;                                                /*!< 0x14 channel 3 handshake flags */
  NETX_HANDSHAKE_CELL tAppFlags0;                                                 /*!< 0x18 not supported yet         */
  NETX_HANDSHAKE_CELL tAppFlags1;                                                 /*!< 0x1C not supported yet         */
  uint32_t            aulReserved[ 56 ];                                          /*!< 0x20 - 0xFF */
} NETX_HANDSHAKE_CHANNEL;

/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*XX                                                           XXXXXXXXXXXXXX*/
/*XX COMMUNICATION CHANNEL LAYOUT                              XXXXXXXXXXXXXX*/
/*XX                                                           XXXXXXXXXXXXXX*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/

/*****************************************************************************/
/*! Default master status structure                                          */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_MASTER_STATUStag
{
  uint32_t ulSlaveState;         /*!< Slave status */
  uint32_t ulSlaveErrLogInd;     /*!< Slave error indication */
  uint32_t ulNumOfConfigSlaves;  /*!< Number of configured slaves */
  uint32_t ulNumOfActiveSlaves;  /*!< Number of active slaves */
  uint32_t ulNumOfDiagSlaves;    /*!< Number of slaves in diag mode */
  uint32_t ulReserved;           /*!< unused/reserved */
} __RCX_PACKED_POST NETX_MASTER_STATUS;

/* Master Status definitions */
#define RCX_SLAVE_STATE_UNDEFINED                           0x00000000
#define RCX_SLAVE_STATE_OK                                  0x00000001
#define RCX_SLAVE_STATE_FAILED                              0x00000002

/*****************************************************************************/
/*! Channel handshake block (Size always 8 Byte)                             */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_HANDSHAKE_BLOCKtag
{
  uint8_t  abReserved[8];                                       /*!< unused/reserved */
} __RCX_PACKED_POST NETX_HANDSHAKE_BLOCK;

/*****************************************************************************/
/*! Channel control block (Size 8 Byte)                                      */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_CONTROL_BLOCKtag
{
  uint32_t   ulApplicationCOS;                                   /*!< 0x00 Application "Change Of State" flags */
  uint32_t   ulDeviceWatchdog;                                   /*!< 0x04 Watchdog cell written by the Host */
} __RCX_PACKED_POST NETX_CONTROL_BLOCK;

/*****************************************************************************/
/*! Channel common status block (Size 64 Byte)                               */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_COMMON_STATUS_BLOCKtag
{
  uint32_t  ulCommunicationCOS;                                 /*!< 0x00 Communication channel "Change Of State" */
  uint32_t  ulCommunicationState;                               /*!< 0x04 Actual communication state */
  uint32_t  ulCommunicationError;                               /*!< 0x08 Actual communication error */
  uint16_t  usVersion;                                          /*!< 0x0C Version of the diagnostic structure */
  uint16_t  usWatchdogTime;                                     /*!< 0x0E Configured watchdog time */
  uint8_t   bPDInHskMode;                                       /*!< 0x10 Input area handshake mode. */
  uint8_t   bPDInSource;                                        /*!< 0x11 Reserved. Set to zero.*/
  uint8_t   bPDOutHskMode;                                      /*!< 0x12 Output area handshake mode. */
  uint8_t   bPDOutSource;                                       /*!< 0x13 Reserved. Set to zero.*/
  uint32_t  ulHostWatchdog;                                     /*!< 0x14 Host watchdog */
  uint32_t  ulErrorCount;                                       /*!< 0x18 Number of erros since power-up */
  uint8_t   bErrorLogInd;                                       /*!< 0x1C Counter of available Log Entries (not supported yet) */
  uint8_t   bErrorPDInCnt;                                      /*!< 0x1D Counter of input process data handshake handling errors  */
  uint8_t   bErrorPDOutCnt;                                     /*!< 0x1E Counter of output process data handshake handling errors */
  uint8_t   bErrorSyncCnt;                                      /*!< 0x1F Counter of synchronization handshake handling errors */
  uint8_t   bSyncHskMode;                                       /*!< 0x20 Synchronization Handshake mode. */
  uint8_t   bSyncSource;                                        /*!< 0x21 Synchronization source. */
  uint16_t  ausReserved[3];                                     /*!< 0x22 Reserved */
  __RCX_PACKED_PRE union
  {
    NETX_MASTER_STATUS  tMasterStatusBlock;                     /*!< For master implementations */
    uint32_t            aulReserved[6];                         /*!< reserved */
  } __RCX_PACKED_POST uStackDepended;                           /*!< 0x28 Stack depend status block */
} __RCX_PACKED_POST NETX_COMMON_STATUS_BLOCK;

/*****************************************************************************/
/*! Channel extended status block (Size 432 Byte)                            */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_EXTENDED_STATUS_BLOCKtag
{
  uint8_t abExtendedStatus[NETX_EXT_STATE_SIZE];                /*!< 0x00 Extended status buffer */
} __RCX_PACKED_POST NETX_EXTENDED_STATUS_BLOCK;

/* Description of the extended status block structure */
#define RCX_EXT_STS_MAX_STRUCTURES           24
/* Location definiton of the ext. state information (bStateArea) */
#define RCX_EXT_STS_STD_OUTPUT_BLK_ID        8                            /* State field located in standard output area */
#define RCX_EXT_STS_HI_OUTPUT_BLK_ID         9                            /* State field located in high prio. output area */
#define RCX_EXT_STS_STD_INPUT_BLK_ID         0                            /* State field located in standard input area */
#define RCX_EXT_STS_HI_INPUT_BLK_ID          1                            /* State field located in high prio. input area */
/* Definition of state information (bStateTypeID) */
#define RCX_EXT_STS_SLAVE_CONFIGURED         1                            /* Configured slave bit field */
#define RCX_EXT_STS_SLAVE_ACTIV              2                            /* Activ slave bit field */
#define RCX_EXT_STS_SLAVE_DIAGNOSTIC         3                            /* Slave diagnostic bit field */
typedef __RCX_PACKED_PRE struct NETX_EXTENDED_STATE_STRUCT_Ttag
{
  uint8_t                 bStateArea;                               /* Location of the ext. state information */
  uint8_t                 bStateTypeID;                             /* Type of the state information */
  uint16_t                usNumOfStateEntries;                      /* Number of state entries of the type bStateTypeID */
  uint32_t                ulStateOffset;                            /* Byte start offset in the defined I/O area*/
} __RCX_PACKED_POST NETX_EXTENDED_STATE_STRUCT_T;

typedef __RCX_PACKED_PRE struct NETX_EXTENDED_STATE_FIELD_Ttag
{
  uint8_t                       bReserved[3];                             /* 3 Bytes preserved. Not used.  */
  uint8_t                       bNumStateStructs;                         /* Number of following state structures */
  NETX_EXTENDED_STATE_STRUCT_T  atStateStruct[RCX_EXT_STS_MAX_STRUCTURES];
} __RCX_PACKED_POST NETX_EXTENDED_STATE_FIELD_T;
typedef __RCX_PACKED_PRE struct NETX_EXTENDED_STATE_FIELD_DEFINITION_Ttag
{
  uint8_t               abReserved[172];                            /* Default, protocol specific information area */
  NETX_EXTENDED_STATE_FIELD_T tExtStateField;                             /* Extended status structures */
} __RCX_PACKED_POST NETX_EXTENDED_STATE_FIELD_DEFINITION_T;
/*****************************************************************************/
/*! Channel send packet mailbox block (Size 1600 Byte)                       */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_SEND_MAILBOX_BLOCKtag
{
  uint16_t  usPackagesAccepted;                                 /*!< 0x00 Number of packages that can be accepted */
  uint16_t  usReserved;                                         /*!< 0x02 Reserved */
  uint8_t   abSendMailbox[NETX_CHANNEL_MAILBOX_SIZE];           /*!< 0x04 Send mailbox packet buffer */
} __RCX_PACKED_POST NETX_SEND_MAILBOX_BLOCK;

/*****************************************************************************/
/*! Channel receive packet mailbox block (Size 1600 Byte)                    */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_RECV_MAILBOX_BLOCKtag
{
  uint16_t  usWaitingPackages;                                  /*!< 0x00 Number of packages waiting to be processed */
  uint16_t  usReserved;                                         /*!< 0x02 Reserved */
  uint8_t   abRecvMailbox[NETX_CHANNEL_MAILBOX_SIZE];           /*!< 0x04 Receive mailbox packet buffer */
} __RCX_PACKED_POST NETX_RECV_MAILBOX_BLOCK;

/*****************************************************************************/
/*! Structure of the DEFAULT communication channel (Size 15616 Byte)         */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_DEFAULT_COMM_CHANNELtag
{
  NETX_HANDSHAKE_BLOCK        tReserved;                                    /*!< 0x000:0x007 Reserved for later use */
  NETX_CONTROL_BLOCK          tControl;                                     /*!< 0x008:0x00F Control block */
  NETX_COMMON_STATUS_BLOCK    tCommonStatus;                                /*!< 0x010:0x04F Common status block */
  NETX_EXTENDED_STATUS_BLOCK  tExtendedStatus;                              /*!< 0x050:0x1FF Extended status block */
  NETX_SEND_MAILBOX_BLOCK     tSendMbx;                                     /*!< 0x200:0x83F Send mailbox block */
  NETX_RECV_MAILBOX_BLOCK     tRecvMbx;                                     /*!< 0x840:0xE7F Recveice mailbox block */
  uint8_t                     abPd1Output[NETX_HP_IO_DATA_SIZE];            /*!< 0xE80:0xEBF Process data 1 output area */
  uint8_t                     abPd1Input[NETX_HP_IO_DATA_SIZE];             /*!< 0xEC0:0xEFF Process data 1 input area */
  uint8_t                     abReserved1[256];                             /*!< 0xF00:0xFFF Reserved */
  uint8_t                     abPd0Output[NETX_IO_DATA_SIZE];               /*!< 0x1000:0x267F Process data 0 output area */
  uint8_t                     abPd0Input[NETX_IO_DATA_SIZE];                /*!< 0x2680:0x3CFF Process data 0 input area */
} __RCX_PACKED_POST NETX_DEFAULT_COMM_CHANNEL;


/*****************************************************************************/
/*! Structure of the communication channel for 8K DPM hardware (e.g. COMX10) */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct NETX_8K_DPM_COMM_CHANNELtag
{
  NETX_HANDSHAKE_BLOCK        tReserved;                                    /*!< 0x000:0x007 Reserved for later use */
  NETX_CONTROL_BLOCK          tControl;                                     /*!< 0x008:0x00F Control block */
  NETX_COMMON_STATUS_BLOCK    tCommonStatus;                                /*!< 0x010:0x04F Common status block */
  NETX_EXTENDED_STATUS_BLOCK  tExtendedStatus;                              /*!< 0x050:0x1FF Extended status block */
  NETX_SEND_MAILBOX_BLOCK     tSendMbx;                                     /*!< 0x200:0x83F Send mailbox block */
  NETX_RECV_MAILBOX_BLOCK     tRecvMbx;                                     /*!< 0x840:0xE7F Recveice mailbox block */
  uint8_t                     abPd1Output[NETX_HP_IO_DATA_SIZE];            /*!< 0xE80:0xEBF Process data 1 output area */
  uint8_t                     abPd1Input[NETX_HP_IO_DATA_SIZE];             /*!< 0xEC0:0xEFF Process data 1 input area */
  uint8_t                     abReserved1[256];                             /*!< 0xF00:0xFFF Reserved */
  uint8_t                     abPd0Output[NETX_IO_DATA_SIZE_8K_DPM];        /*!< 0x1000:0x15FF Process data 0 output area */
  uint8_t                     abPd0Input[NETX_IO_DATA_SIZE_8K_DPM];         /*!< 0x1600:0x1BFF Process data 0 input area */
  uint8_t                     abReserved2[256];                             /*!< 0x1C00:0x1CFF Reserved */
} __RCX_PACKED_POST NETX_8K_DPM_COMM_CHANNEL;


/*  /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\ /\  */
/* End of DPM Layout definition */

/*===========================================================================*/
/*                                                                           */
/* Standardized Handshake Flags                                              */
/*                                                                           */
/*===========================================================================*/

/* --------------------------------------------*/
/* System Channel Handshake Flags              */
/* --------------------------------------------*/
/* HOST Flags */
#define HSF_RESET                         0x0001                      /*!< Reset command bitmask */
#define HSF_BOOTSTART                     0x0002                      /*!< Set when device has a second stage loader, to enter bootloader mode after a system start */
#define HSF_HOST_COS_CMD                  0x0004                      /*!< Host "Change Of State" command bitmask */
#define HSF_NETX_COS_ACK                  0x0008                      /*!< NetX "Change Of State" acknowlegde bitmask */
#define HSF_SEND_MBX_CMD                  0x0010                      /*!< Send mailbox command bitmask */
#define HSF_RECV_MBX_ACK                  0x0020                      /*!< Receive mailbox acknowledge bitmask */
#define HSF_EXT_SEND_MBX_CMD              0x0040                      /*!< Second stage loader extended mailbox command bitmask */
#define HSF_EXT_RECV_MBX_ACK              0x0080                      /*!< Second stage loader extended mailbox ack bitmask */

/* HOST Flags as Bit number */
#define HSF_RESET_BIT_NO                  0                           /*!< Reset command bitnumber */
#define HSF_BOOTLOADER_BIT_NO             1                           /*!< Bitnumber to be set when device has a second stage loader, to enter bootloader mode after a system start */
#define HSF_HOST_COS_CMD_BIT_NO           2                           /*!< Host "Change Of State" command bitnumber */
#define HSF_NETX_COS_ACK_BIT_NO           3                           /*!< NetX "Change Of State" acknowlegde bitnumber */
#define HSF_SEND_MBX_CMD_BIT_NO           4                           /*!< Send mailbox command bitnumber */
#define HSF_RECV_MBX_ACK_BIT_NO           5                           /*!< Receive mailbox acknowledge bitnumber */
#define HSF_EXT_SEND_MBX_CMD_BIT_NO       6                           /*!< Second stage loader extended mailbox command bitnumber */
#define HSF_EXT_RECV_MBX_ACK_BIT_NO       7                           /*!< Second stage loader extended mailbox ack bitnumber */


/* netX Flags */
#define NSF_READY                         0x0001                      /*!< netX System READY bitmask */
#define NSF_ERROR                         0x0002                      /*!< General system error bitmask */
#define NSF_HOST_COS_ACK                  0x0004                      /*!< Host "Change Of State" acknowledge bitmask */
#define NSF_NETX_COS_CMD                  0x0008                      /*!< NetX "Change of State command bitmask */
#define NSF_SEND_MBX_ACK                  0x0010                      /*!< Send mailbox acknowledge bitmask */
#define NSF_RECV_MBX_CMD                  0x0020                      /*!< Receive mailbox command bitmask */
#define NSF_EXT_SEND_MBX_ACK              0x0040                      /*!< Second stage loader extended mailbox ack bitmask */
#define NSF_EXT_RECV_MBX_CMD              0x0080                      /*!< Second stage loader extended mailbox command bitmask */
/* netX Flags as Bit number */
#define NSF_READY_BIT_NO                  0                           /*!< netX System READY bitnumber */
#define NSF_ERROR_BIT_NO                  1                           /*!< General system error bitnumber */
#define NSF_HOST_COS_ACK_BIT_NO           2                           /*!< Host "Change Of State" acknowledge bitnumber */
#define NSF_NETX_COS_CMD_BIT_NO           3                           /*!< NetX "Change of State command bitnumber */
#define NSF_SEND_MBX_ACK_BIT_NO           4                           /*!< Send mailbox acknowledge bitnumber */
#define NSF_RECV_MBX_CMD_BIT_NO           5                           /*!< Receive mailbox command bitnumber */
#define NSF_EXT_SEND_MBX_ACK_BIT_NO       6                           /*!< Second stage loader extended mailbox ack bitnumber */
#define NSF_EXT_RECV_MBX_CMD_BIT_NO       7                           /*!< Second stage loader extended mailbox command bitnumber */

/*--------------------------------------------*/
/* Communication Channel Handshake Flags      */
/*--------------------------------------------*/
/* HOST Communication Channel Flags */
#define HCF_HOST_READY                    0x0001                      /*!< Host application is Ready bitmask */
#define HCF_unused                        0x0002                      /*!< unused */
#define HCF_HOST_COS_CMD                  0x0004                      /*!< Host "Change Of State" command bitmask */
#define HCF_NETX_COS_ACK                  0x0008                      /*!< NetX "Change Of State" acknowledge bitmask */
#define HCF_SEND_MBX_CMD                  0x0010                      /*!< Send mailbox command bitmask */
#define HCF_RECV_MBX_ACK                  0x0020                      /*!< Receive mailbox ackowledge bitmask */
#define HCF_PD0_OUT_CMD                   0x0040                      /*!< Process data, block 0, output command bitmask */
#define HCF_PD0_IN_ACK                    0x0080                      /*!< Process data, block 0, input acknowlegde bitmask */
#define HCF_PD1_OUT_CMD                   0x0100                      /*!< Process data, block 1, output command bitmask */
#define HCF_PD1_IN_ACK                    0x0200                      /*!< Process data, block 1, input acknowlegde bitmask */
/* HOST Communication Channel Flags as Bit number */
#define HCF_HOST_READY_BIT_NO             0                           /*!< Host application is Ready bitnumber */
#define HCF_unused_BIT_NO                 1                           /*!< unused */
#define HCF_HOST_COS_CMD_BIT_NO           2                           /*!< Host "Change Of State" command bitnumber */
#define HCF_NETX_COS_ACK_BIT_NO           3                           /*!< NetX "Change Of State" acknowledge bitnumber */
#define HCF_SEND_MBX_CMD_BIT_NO           4                           /*!< Send mailbox command bitnumber */
#define HCF_RECV_MBX_ACK_BIT_NO           5                           /*!< Receive mailbox ackowledge bitnumber */
#define HCF_PD0_OUT_CMD_BIT_NO            6                           /*!< Process data, block 0, output command bitnumber */
#define HCF_PD0_IN_ACK_BIT_NO             7                           /*!< Process data, block 0, input acknowlegde bitnumber */
#define HCF_PD1_OUT_CMD_BIT_NO            8                           /*!< Process data, block 1, output command bitnumber */
#define HCF_PD1_IN_ACK_BIT_NO             9                           /*!< Process data, block 1, input acknowlegde bitnumber */

/* netX Communication Channel Flags */
#define NCF_COMMUNICATING                 0x0001                      /*!< Channel has an active conection bitmask */
#define NCF_ERROR                         0x0002                      /*!< Communication channel error bitmask */
#define NCF_HOST_COS_ACK                  0x0004                      /*!< Host "Change Of State" acknowledge bitmask */
#define NCF_NETX_COS_CMD                  0x0008                      /*!< NetX "Change Of State" command bitmask */
#define NCF_SEND_MBX_ACK                  0x0010                      /*!< Send mailbox acknowldege bitmask */
#define NCF_RECV_MBX_CMD                  0x0020                      /*!< Receive mailbox command bitmask */
#define NCF_PD0_OUT_ACK                   0x0040                      /*!< Process data, block 0, output acknowledge bitmask */
#define NCF_PD0_IN_CMD                    0x0080                      /*!< Process data, block 0, input command bitmask */
#define NCF_PD1_OUT_ACK                   0x0100                      /*!< Process data, block 1, output acknowlegde bitmask */
#define NCF_PD1_IN_CMD                    0x0200                      /*!< Process data, block 1, input command bitmask */
/* netX Communication Channel Flags as Bit number */
#define NCF_COMMUNICATING_BIT_NO          0                           /*!< Channel has an active conection bitnumber */
#define NCF_ERROR_BIT_NO                  1                           /*!< Communication channel error bitnumber */
#define NCF_HOST_COS_ACK_BIT_NO           2                           /*!< Host "Change Of State" acknowledge bitnumber */
#define NCF_NETX_COS_CMD_BIT_NO           3                           /*!< NetX "Change Of State" command bitnumber */
#define NCF_SEND_MBX_ACK_BIT_NO           4                           /*!< Send mailbox acknowldege bitnumber */
#define NCF_RECV_MBX_CMD_BIT_NO           5                           /*!< Receive mailbox command bitnumber */
#define NCF_PD0_OUT_ACK_BIT_NO            6                           /*!< Process data, block 0, output acknowledge bitnumber */
#define NCF_PD0_IN_CMD_BIT_NO             7                           /*!< Process data, block 0, input command bitnumber */
#define NCF_PD1_OUT_ACK_BIT_NO            8                           /*!< Process data, block 1, output acknowlegde bitnumber */
#define NCF_PD1_IN_CMD_BIT_NO             9                           /*!< Process data, block 1, input command bitnumber */

/*--------------------------------------------*/
/* Handshake Flags State Definitions          */
/*--------------------------------------------*/
/* Flag state definition */
#define RCX_FLAGS_EQUAL                   0
#define RCX_FLAGS_NOT_EQUAL               1
#define RCX_FLAGS_CLEAR                   2
#define RCX_FLAGS_SET                     3
#define RCX_FLAGS_NONE                    0xFF

#define RCX_FLAG_CLEAR                    0
#define RCX_FLAG_SET                      1

/*===========================================================================*/
/*                                                                           */
/* SYSTEM CHANNEL Configuration definitions                                  */
/*                                                                           */
/*===========================================================================*/

/*--------------------------------------------*/
/* SYSTEM STATUS BLOCK                        */
/*--------------------------------------------*/
/* System Change of State flags */
#define RCX_SYS_COS_UNDEFINED                               0
#define RCX_SYS_COS_DEFAULT_MEMORY                          0x80000000
/* System Change of State flags as bit number */
#define RCX_SYS_COS_DEFAULT_MEMORY_BIT_NO                   31

/* System Status */
#define RCX_SYS_STATUS_UNDEFINED                            0x00000000
#define RCX_SYS_STATUS_OK                                   0x00000001
#define RCX_SYS_STATUS_BOOTMEDIUM_MASK                      0x0F000000
#define RCX_SYS_STATUS_BOOTMEDIUM_RAM                       0x00000000
#define RCX_SYS_STATUS_BOOTMEDIUM_SERFLASH                  0x01000000
#define RCX_SYS_STATUS_BOOTMEDIUM_PARFLASH                  0x02000000
#define RCX_SYS_STATUS_NO_SYSVOLUME                         0x20000000
#define RCX_SYS_STATUS_SYSVOLUME_FFS                        0x40000000  /* _FFS = Flash File System */
#define RCX_SYS_STATUS_NXO_SUPPORTED                        0x80000000

/* System Status definition */
#define RCX_SYS_STATE_UNDEFINED                             0
#define RCX_SYS_STATE_OK                                    1

/* System Error definitions */
#define RCX_SYS_ERROR_SUCCESS                               0

/* System Status */
#define RCX_SYS_STATE_RESET                                 0x000000F0
#define RCX_SYS_STATE_SELF_TEST                             0x000000EF
#define RCX_SYS_STATE_RAM_TEST                              0x000000EE
#define RCX_SYS_STATE_FAULT_INIT                            0x000000ED
#define RCX_SYS_STATE_DEVICE_INIT                           0x000000EC
#define RCX_SYS_STATE_MAILBOX_INIT                          0x000000EB
#define RCX_SYS_STATE_SERIAL_INIT                           0x000000EA
#define RCX_SYS_STATE_SEMAPHORE_INIT                        0x000000E9
#define RCX_SYS_STATE_QUEUE_INIT                            0x000000E8
#define RCX_SYS_STATE_MUTEX_INIT                            0x000000E7
#define RCX_SYS_STATE_EVENT_INIT                            0x000000E6
#define RCX_SYS_STATE_SIGNAL_INIT                           0x000000E5
#define RCX_SYS_STATE_TIMER_INIT                            0x000000E4
#define RCX_SYS_STATE_BARRIER_INIT                          0x000000E3
#define RCX_SYS_STATE_DIAGNOSTIC_INIT                       0x000000E2
#define RCX_SYS_STATE_FINITE_STATE_INIT                     0x000000E1
#define RCX_SYS_STATE_INTERRUPT_INIT                        0x000000E0
#define RCX_SYS_STATE_LED_INIT                              0x000000DF
/*#define RCX_SYS_STATE_TIMER_INIT                          0x000000DE*/
#define RCX_SYS_STATE_PAR_FLASH_INIT                        0x000000DD
#define RCX_SYS_STATE_XC_INIT                               0x000000DC
#define RCX_SYS_STATE_PHY_INIT                              0x000000DB
#define RCX_SYS_STATE_UART_INIT                             0x000000DA
#define RCX_SYS_STATE_VOL_INIT                              0x000000D9
#define RCX_SYS_STATE_EDD_INIT                              0x000000D8
#define RCX_SYS_STATE_ICM_INIT                              0x000000D7
#define RCX_SYS_STATE_USB_INIT                              0x000000D6
#define RCX_SYS_STATE_FIFO_INIT                             0x000000D5
#define RCX_SYS_STATE_EBUS_INIT                             0x000000D4
#define RCX_SYS_STATE_MMU_INIT                              0x000000D3
#define RCX_SYS_STATE_TCM_INIT                              0x000000D2
#define RCX_SYS_STATE_CCH_INIT                              0x000000D1
#define RCX_SYS_STATE_MID_SYS_INIT                          0x000000D0
#define RCX_SYS_STATE_MID_DBM_INIT                          0x000000CF
#define RCX_SYS_STATE_HIF_INIT                              0x000000CE
#define RCX_SYS_STATE_HIFPIO_INIT                           0x000000CD
#define RCX_SYS_STATE_SPI_INIT                              0x000000CC
#define RCX_SYS_STATE_FIQ_INIT                              0x000000CB
#define RCX_SYS_STATE_SEC_INIT                              0x000000CA
#define RCX_SYS_STATE_CRC_INIT                              0x000000C9
#define RCX_SYS_STATE_MEMORY_INIT                           0x000000C8
#define RCX_SYS_STATE_SER_FLASH_INIT                        0x000000C7
#define RCX_SYS_STATE_TASKS_INIT                            0x000000C6
#define RCX_SYS_STATE_MID_STA_INIT                          0x000000C5
#define RCX_SYS_STATE_MULTITASK_INIT                        0x000000C4
#define RCX_SYS_STATE_IDLE_TASK_INIT                        0x000000C3
#define RCX_SYS_STATE_GPIO_INIT                             0x000000C2
#define RCX_SYS_STATE_PIO_INIT                              0x000000C1
#define RCX_SYS_STATE_SUCCESS                               0x00000000

/* System Error */
#define RCX_SYS_SUCCESS                                     0x00000000
#define RCX_SYS_RAM_NOT_FOUND                               0x00000001
#define RCX_SYS_RAM_TYPE                                    0x00000002
#define RCX_SYS_RAM_SIZE                                    0x00000003
#define RCX_SYS_RAM_TEST                                    0x00000004
#define RCX_SYS_FLASH_NOT_FOUND                             0x00000005
#define RCX_SYS_FLASH_TYPE                                  0x00000006
#define RCX_SYS_FLASH_SIZE                                  0x00000007
#define RCX_SYS_FLASH_TEST                                  0x00000008
#define RCX_SYS_EEPROM_NOT_FOUND                            0x00000009
#define RCX_SYS_EEPROM_TYPE                                 0x0000000A
#define RCX_SYS_EEPROM_SIZE                                 0x0000000B
#define RCX_SYS_EEPROM_TEST                                 0x0000000C
#define RCX_SYS_SECURE_EEPROM                               0x0000000D
#define RCX_SYS_SECURE_EEPROM_NOT_INIT                      0x0000000E
#define RCX_SYS_FILE_SYSTEM_FAULT                           0x0000000F
#define RCX_SYS_VERSION_CONFLICT                            0x00000010
#define RCX_SYS_NOT_INITIALIZED                             0x00000011
#define RCX_SYS_MEM_ALLOC                                   0x00000012

/* LED State definition */
#define RCX_LED_STATE_MASK                                  0x0F
#define RCX_LED_STATE_OFF                                   0x00
#define RCX_LED_STATE_SOLID_ON                              0x01
#define RCX_LED_STATE_FLICKER                               0x02
#define RCX_LED_STATE_SINGLE_FLICKER                        0x03
#define RCX_LED_STATE_FLASH_CYCLIC                          0x04
#define RCX_LED_STATE_FLASH_CYCLIC_FAST                     0x05
#define RCX_LED_STATE_SINGLE_FLASH                          0x06
#define RCX_LED_STATE_DOUBLE_FLASH                          0x07
#define RCX_LED_STATE_QUADRUPLE_FLASH                       0x08
#define RCX_LED_STATE_FLASH_NON_CYCLIC                      0x09
#define RCX_LED_STATE_TRIPLE_FLASH                          0x0A

/* LED Color State */
#define RCX_LED_COLOR_STATE_MASK                            0xF0
#define RCX_LED_COLOR_NOT_USED                              0x00
#define RCX_LED_COLOR_RED                                   0x10
#define RCX_LED_COLOR_YELLOW                                0x20
#define RCX_LED_COLOR_GREEN                                 0x30
#define RCX_LED_COLOR_BLUE                                  0x40
#define RCX_LED_COLOR_RED_GREEN                             0x50
#define RCX_LED_COLOR_RED_YELLOW                            0x60
#define RCX_LED_COLOR_GREEN_YELLOW                          0x70

/* System LED definition */
#define RCX_LED_OFF                                         0x00
#define RCX_LED_YEL_CYCLIC_FAST                             0x25
#define RCX_LED_YEL_CYCLIC                                  0x24
#define RCX_LED_YEL_NONCYCLIC                               0x29
#define RCX_LED_GRN_SOLID                                   0x31
#define RCX_LED_GRN_CYCLIC                                  0x34
#define RCX_LED_GRN_NONCYCLIC                               0x39

/* System Hardware Features */
/* Extended Memory */
#define RCX_SYSTEM_EXTMEM_TYPE_MSK                          0x0000000F
#define RCX_SYSTEM_EXTMEM_TYPE_NONE                         0x00000000
#define RCX_SYSTEM_EXTMEM_TYPE_MRAM_128K                    0x00000001

#define RCX_SYSTEM_EXTMEM_ACCESS_MSK                        0x000000C0
#define RCX_SYSTEM_EXTMEM_ACCESS_NONE                       0x00000000
#define RCX_SYSTEM_EXTMEM_ACCESS_EXTERNAL                   0x00000040
#define RCX_SYSTEM_EXTMEM_ACCESS_INTERNAL                   0x00000080
#define RCX_SYSTEM_EXTMEM_ACCESS_BOTH                       0x000000C0

/* RTC */
#define RCX_SYSTEM_HW_RTC_MSK                               0x00000700
#define RCX_SYSTEM_HW_RTC_TYPE_MSK                          0x00000300
#define RCX_SYSTEM_HW_RTC_TYPE_NONE                         0x00000000
#define RCX_SYSTEM_HW_RTC_TYPE_INTERNAL                     0x00000100
#define RCX_SYSTEM_HW_RTC_TYPE_EXTERNAL                     0x00000200
#define RCX_SYSTEM_HW_RTC_TYPE_EMULATED                     0x00000300
#define RCX_SYSTEM_HW_RTC_STATE                             0x00000400

/*--------------------------------------------*/
/* SYSTEM INFORMATION BLOCK                   */
/*--------------------------------------------*/
/* Hardware options */
#define RCX_HW_ASSEMBLY_UNDEFINED                           0x0000
#define RCX_HW_ASSEMBLY_NOT_AVAILABLE                       0x0001

#define RCX_HW_ASSEMBLY_VALIDATION_START                    0x0010    /* Start of HW option validation area */

#define RCX_HW_ASSEMBLY_SERIAL                              0x0010
#define RCX_HW_ASSEMBLY_ASI                                 0x0020
#define RCX_HW_ASSEMBLY_CAN                                 0x0030
#define RCX_HW_ASSEMBLY_DEVICENET                           0x0040
#define RCX_HW_ASSEMBLY_PROFIBUS                            0x0050

#define RCX_HW_ASSEMBLY_CCLINK                              0x0070
#define RCX_HW_ASSEMBLY_ETHERNET                            0x0080
#define RCX_HW_ASSEMBLY_ETHERNET_X_PHY                      0x0081
#define RCX_HW_ASSEMBLY_ETHERNET_FIBRE_OPTIC                0x0082

#define RCX_HW_ASSEMBLY_SPI                                 0x0090
#define RCX_HW_ASSEMBLY_IO_LINK                             0x00A0
#define RCX_HW_ASSEMBLY_COMPONET                            0x00B0

#define RCX_HW_ASSEMBLY_VALIDATION_END                      0xFFEF    /* End of HW option validation area */

#define RCX_HW_ASSEMBLY_I2C_UNKNOWN                         0xFFF4
#define RCX_HW_ASSEMBLY_SSI                                 0xFFF5
#define RCX_HW_ASSEMBLY_SYNC                                0xFFF6

#define RCX_HW_ASSEMBLY_FIELDBUS                            0xFFF8

#define RCX_HW_ASSEMBLY_TOUCH_SCREEN                        0xFFFA
#define RCX_HW_ASSEMBLY_I2C_PIO                             0xFFFB
#define RCX_HW_ASSEMBLY_I2C_PIO_NT                          0xFFFC
#define RCX_HW_ASSEMBLY_PROPRIETARY                         0xFFFD
#define RCX_HW_ASSEMBLY_NOT_CONNECTED                       0xFFFE
#define RCX_HW_ASSEMBLY_RESERVED                            0xFFFF

/* Manufacturer definition */
#define RCX_MANUFACTURER_UNDEFINED                          0x0000
#define RCX_MANUFACTURER_HILSCHER_GMBH                      0x0001    /* Hilscher GmbH */
#define RCX_MANUFACTURER_HILSCHER_GMBH_MAX                  0x00FF    /* Hilscher GmbH max. value*/

/* Production date definition */
#define RCX_PRODUCTION_DATE_YEAR_MASK                       0xFF00    /* Year offset (0..255) starting at 2000 */
#define RCX_PRODUCTION_DATE_WEEK_MASK                       0x00FF    /* Week of year ( 1..52) */

/* Device class definition */
#define RCX_HW_DEV_CLASS_UNDEFINED                          0x0000
#define RCX_HW_DEV_CLASS_UNCLASSIFIABLE                     0x0001
#define RCX_HW_DEV_CLASS_CHIP_NETX_500                      0x0002
#define RCX_HW_DEV_CLASS_CIFX                               0x0003
#define RCX_HW_DEV_CLASS_COMX_100                           0x0004
#define RCX_HW_DEV_CLASS_COMX                               0x0004    /* old definition only for compatibility reasons */
#define RCX_HW_DEV_CLASS_EVA_BOARD                          0x0005
#define RCX_HW_DEV_CLASS_NETDIMM                            0x0006
#define RCX_HW_DEV_CLASS_CHIP_NETX_100                      0x0007
#define RCX_HW_DEV_CLASS_NETX_HMI                           0x0008

#define RCX_HW_DEV_CLASS_NETIO_50                           0x000A
#define RCX_HW_DEV_CLASS_NETIO_100                          0x000B
#define RCX_HW_DEV_CLASS_CHIP_NETX_50                       0x000C
#define RCX_HW_DEV_CLASS_GW_NETPAC                          0x000D
#define RCX_HW_DEV_CLASS_GW_NETTAP                          0x000E
#define RCX_HW_DEV_CLASS_NETSTICK                           0x000F
#define RCX_HW_DEV_CLASS_NETANALYZER                        0x0010
#define RCX_HW_DEV_CLASS_NETSWITCH                          0x0011
#define RCX_HW_DEV_CLASS_NETLINK                            0x0012
#define RCX_HW_DEV_CLASS_NETIC_50                           0x0013
#define RCX_HW_DEV_CLASS_NETIC                              0x0013    /* old definition only for compatibility reasons */
#define RCX_HW_DEV_CLASS_NPLC_C100                          0x0014
#define RCX_HW_DEV_CLASS_NPLC_M100                          0x0015
#define RCX_HW_DEV_CLASS_GW_NETTAP_50                       0x0016
#define RCX_HW_DEV_CLASS_NETBRICK                           0x0017
#define RCX_HW_DEV_CLASS_NPLC_T100                          0x0018
#define RCX_HW_DEV_CLASS_NETLINK_PROXY                      0x0019
#define RCX_HW_DEV_CLASS_CHIP_NETX_10                       0x001A
#define RCX_HW_DEV_CLASS_NETJACK_10                         0x001B
#define RCX_HW_DEV_CLASS_NETJACK_50                         0x001C
#define RCX_HW_DEV_CLASS_NETJACK_100                        0x001D
#define RCX_HW_DEV_CLASS_NETJACK_500                        0x001E
#define RCX_HW_DEV_CLASS_NETLINK_10_USB                     0x001F
#define RCX_HW_DEV_CLASS_COMX_10                            0x0020
#define RCX_HW_DEV_CLASS_NETIC_10                           0x0021
#define RCX_HW_DEV_CLASS_COMX_50                            0x0022
#define RCX_HW_DEV_CLASS_NETRAPID_10                        0x0023
#define RCX_HW_DEV_CLASS_NETRAPID_50                        0x0024
#define RCX_HW_DEV_CLASS_NETSCADA_T51                       0x0025
#define RCX_HW_DEV_CLASS_CHIP_NETX_51                       0x0026
#define RCX_HW_DEV_CLASS_NETRAPID_51                        0x0027
#define RCX_HW_DEV_CLASS_GW_EU5C                            0x0028
#define RCX_HW_DEV_CLASS_NETSCADA_T50                       0x0029
#define RCX_HW_DEV_CLASS_NETSMART_50                        0x002A
#define RCX_HW_DEV_CLASS_IOLINK_GW_51                       0x002B
#define RCX_HW_DEV_CLASS_NETHMI_B500                        0x002C
#define RCX_HW_DEV_CLASS_CHIP_NETX_52                       0x002D
#define RCX_HW_DEV_CLASS_COMX_51                            0x002E
#define RCX_HW_DEV_CLASS_NETJACK_51                         0x002F
#define RCX_HW_DEV_CLASS_NETHOST_T100                       0x0030
#define RCX_HW_DEV_CLASS_NETSCOPE_C100                      0x0031
#define RCX_HW_DEV_CLASS_NETRAPID_52                        0x0032
#define RCX_HW_DEV_CLASS_NETSMART_T51                       0x0033
#define RCX_HW_DEV_CLASS_NETSCADA_T52                       0x0034
#define RCX_HW_DEV_CLASS_NETSAFETY_51                       0x0035
#define RCX_HW_DEV_CLASS_NETSAFETY_52                       0x0036
#define RCX_HW_DEV_CLASS_NETPLC_J500                        0x0037
#define RCX_HW_DEV_CLASS_NETIC_52                           0x0038

#define RCX_HW_DEV_CLASS_HILSCHER_GMBH_MAX                  0x7FFF    /* Hilscher GmbH max. value*/
#define RCX_HW_DEV_CLASS_OEM_DEVICE                         0xFFFE

/*--------------------------------------------*/
/* CHANNEL INFORMATION BLOCK                  */
/*--------------------------------------------*/
/* Channel type definitions */
#define RCX_CHANNEL_TYPE_UNDEFINED                          0         /*!< Type of the channel is undefined */
#define RCX_CHANNEL_TYPE_NOT_AVAILABLE                      1         /*!< Type of the channel not available */
#define RCX_CHANNEL_TYPE_RESERVED                           2         /*!< Reserved */
#define RCX_CHANNEL_TYPE_SYSTEM                             3         /*!< System channel */
#define RCX_CHANNEL_TYPE_HANDSHAKE                          4         /*!< Handshake channel */
#define RCX_CHANNEL_TYPE_COMMUNICATION                      5         /*!< Communication channel */
#define RCX_CHANNEL_TYPE_APPLICATION                        6         /*!< Application channnel */
#define RCX_CHANNEL_TYPE_MAX                                127       /*!< Maximum used channel number */
#define RCX_CHANNEL_TYPE_USER_DEFINED_START                 128       /*!< User defined channel */

/* Handshake cell, size and position */
#define RCX_HANDSHAKE_SIZE_MASK                             0x0F      /*!< Handshake size mask */
#define RCX_HANDSHAKE_SIZE_NOT_AVAILABLE                    0x00      /*!< No handshake cells */
#define RCX_HANDSHAKE_SIZE_8BIT                             0x01      /*!< Handshake cell size 8bit */
#define RCX_HANDSHAKE_SIZE_16BIT                            0x02      /*!< Handshake cell size 16bit */

#define RCX_HANDSHAKE_POSITION_MASK                         0xF0      /*!< Handshake position mask */
#define RCX_HANDSHAKE_POSITION_BEGINNING                    0x00      /*!< Handshake cells located at the start of each channel */
#define RCX_HANDSHAKE_POSITION_CHANNEL                      0x10      /*!< Handshake cells located in an own channel */

/* Communication Class information */
#define RCX_COMM_CLASS_UNDEFINED                            0x0000
#define RCX_COMM_CLASS_UNCLASSIFIABLE                       0x0001
#define RCX_COMM_CLASS_MASTER                               0x0002
#define RCX_COMM_CLASS_SLAVE                                0x0003
#define RCX_COMM_CLASS_SCANNER                              0x0004
#define RCX_COMM_CLASS_ADAPTER                              0x0005
#define RCX_COMM_CLASS_MESSAGING                            0x0006
#define RCX_COMM_CLASS_CLIENT                               0x0007
#define RCX_COMM_CLASS_SERVER                               0x0008
#define RCX_COMM_CLASS_IO_CONTROLLER                        0x0009
#define RCX_COMM_CLASS_IO_DEVICE                            0x000A
#define RCX_COMM_CLASS_IO_SUPERVISOR                        0x000B
#define RCX_COMM_CLASS_GATEWAY                              0x000C
#define RCX_COMM_CLASS_MONITOR                              0x000D
#define RCX_COMM_CLASS_PRODUCER                             0x000E
#define RCX_COMM_CLASS_CONSUMER                             0x000F
#define RCX_COMM_CLASS_SWITCH                               0x0010
#define RCX_COMM_CLASS_HUB                                  0x0011
#define RCX_COMM_CLASS_COMBI                                0x0012
#define RCX_COMM_CLASS_MANAGING_NODE                        0x0013
#define RCX_COMM_CLASS_CONTROLLED_NODE                      0x0014
#define RCX_COMM_CLASS_PLC                                  0x0015
#define RCX_COMM_CLASS_HMI                                  0x0016
#define RCX_COMM_CLASS_ITEM_SERVER                          0x0017

/* Protocol Class information */
#define RCX_PROT_CLASS_UNDEFINED                            0x0000
#define RCX_PROT_CLASS_3964R                                0x0001
#define RCX_PROT_CLASS_ASINTERFACE                          0x0002
#define RCX_PROT_CLASS_ASCII                                0x0003
#define RCX_PROT_CLASS_CANOPEN                              0x0004
#define RCX_PROT_CLASS_CCLINK                               0x0005
#define RCX_PROT_CLASS_COMPONET                             0x0006
#define RCX_PROT_CLASS_CONTROLNET                           0x0007
#define RCX_PROT_CLASS_DEVICENET                            0x0008
#define RCX_PROT_CLASS_ETHERCAT                             0x0009
#define RCX_PROT_CLASS_ETHERNET_IP                          0x000A
#define RCX_PROT_CLASS_FOUNDATION_FB                        0x000B
#define RCX_PROT_CLASS_FL_NET                               0x000C
#define RCX_PROT_CLASS_INTERBUS                             0x000D
#define RCX_PROT_CLASS_IO_LINK                              0x000E
#define RCX_PROT_CLASS_LON                                  0x000F
#define RCX_PROT_CLASS_MODBUS_PLUS                          0x0010
#define RCX_PROT_CLASS_MODBUS_RTU                           0x0011
#define RCX_PROT_CLASS_OPEN_MODBUS_TCP                      0x0012
#define RCX_PROT_CLASS_PROFIBUS_DP                          0x0013
#define RCX_PROT_CLASS_PROFIBUS_MPI                         0x0014
#define RCX_PROT_CLASS_PROFINET_IO                          0x0015
#define RCX_PROT_CLASS_RK512                                0x0016
#define RCX_PROT_CLASS_SERCOS_II                            0x0017
#define RCX_PROT_CLASS_SERCOS_III                           0x0018
#define RCX_PROT_CLASS_TCP_IP_UDP_IP                        0x0019
#define RCX_PROT_CLASS_POWERLINK                            0x001A
#define RCX_PROT_CLASS_HART                                 0x001B
#define RCX_PROT_CLASS_COMBI                                0x001C
#define RCX_PROT_CLASS_PROG_GATEWAY                         0x001D
#define RCX_PROT_CLASS_PROG_SERIAL                          0x001E
#define RCX_PROT_CLASS_PLC_CODESYS                          0x001F
#define RCX_PROT_CLASS_PLC_PROCONOS                         0x0020
#define RCX_PROT_CLASS_PLC_IBH_S7                           0x0021
#define RCX_PROT_CLASS_PLC_ISAGRAF                          0x0022
#define RCX_PROT_CLASS_VISU_QVIS                            0x0023
#define RCX_PROT_CLASS_ETHERNET                             0x0024
#define RCX_PROT_CLASS_RFC1006                              0x0025
#define RCX_PROT_CLASS_DF1                                  0x0026
#define RCX_PROT_CLASS_VARAN                                0x0027
#define PROT_CLASS_3S_PLC_HANDLER                           0x0028
#define RCX_PROT_CLASS_OEM                                  0xFFF0

/*===========================================================================*/
/*                                                                           */
/* COMMUNICATION / APPLICATION CHANNEL Configuration definitions             */
/*                                                                           */
/*===========================================================================*/
/*-----------------------------------*/
/* CHANNEL CONTROL BLOCK             */
/*-----------------------------------*/
/* Application Change of State */
#define RCX_APP_COS_APPLICATION_READY                       0x00000001
#define RCX_APP_COS_BUS_ON                                  0x00000002
#define RCX_APP_COS_BUS_ON_ENABLE                           0x00000004
#define RCX_APP_COS_INITIALIZATION                          0x00000008
#define RCX_APP_COS_INITIALIZATION_ENABLE                   0x00000010
#define RCX_APP_COS_LOCK_CONFIGURATION                      0x00000020
#define RCX_APP_COS_LOCK_CONFIGURATION_ENABLE               0x00000040
#define RCX_APP_COS_DMA                                     0x00000080
#define RCX_APP_COS_DMA_ENABLE                              0x00000100

/* Application Change of State flags as bit number */
#define RCX_APP_COS_APPLICATION_READY_BIT_NO                0
#define RCX_APP_COS_BUS_ON_BIT_NO                           1
#define RCX_APP_COS_BUS_ON_ENABLE_BIT_NO                    2
#define RCX_APP_COS_INITIALIZATION_BIT_NO                   3
#define RCX_APP_COS_INITIALIZATION_ENABLE_BIT_NO            4
#define RCX_APP_COS_LOCK_CONFIGURATION_BIT_NO               5
#define RCX_APP_COS_LOCK_CONFIGURATION_ENABLE_BIT_NO        6
#define RCX_APP_COS_DMA_BIT_NO                              7
#define RCX_APP_COS_DMA_ENABLE_BIT_NO                       8

/*-----------------------------------*/
/* CHANNEL COMMON STATUS BLOCK       */
/*-----------------------------------*/
/* Channel Change Of State flags */
#define RCX_COMM_COS_UNDEFINED                              0x00000000
#define RCX_COMM_COS_READY                                  0x00000001
#define RCX_COMM_COS_RUN                                    0x00000002
#define RCX_COMM_COS_BUS_ON                                 0x00000004
#define RCX_COMM_COS_CONFIG_LOCKED                          0x00000008
#define RCX_COMM_COS_CONFIG_NEW                             0x00000010
#define RCX_COMM_COS_RESTART_REQUIRED                       0x00000020
#define RCX_COMM_COS_RESTART_REQUIRED_ENABLE                0x00000040
#define RCX_COMM_COS_DMA                                    0x00000080

/* Channel Change Of State flags as bit numbers */
#define RCX_COMM_COS_READY_BIT_NO                           0
#define RCX_COMM_COS_RUN_BIT_NO                             1
#define RCX_COMM_COS_BUS_ON_BIT_NO                          2
#define RCX_COMM_COS_CONFIG_LOCKED_BIT_NO                   3
#define RCX_COMM_COS_CONFIG_NEW_BIT_NO                      4
#define RCX_COMM_COS_RESTART_REQUIRED_BIT_NO                5
#define RCX_COMM_COS_RESTART_REQUIRED_ENABLE_BIT_NO         6
#define RCX_COMM_COS_DMA_BIT_NO                             7

/*===========================================================================*/
/*                                                                           */
/* Channel block information                                                 */
/*                                                                           */
/*===========================================================================*/

/*****************************************************************************/
/*! Block configuration information                                          */
/*****************************************************************************/
typedef struct NETX_BLOCK_DEFINITIONtag
{
  uint8_t   bChannelNumber;
  uint8_t   blBlockNumber;
  uint8_t   bBlockID;
  uint8_t   bPad;
  uint32_t  ulOffset;
  uint32_t  ulSize;
  uint16_t  usFlags;
  uint16_t  usHandshakeMode;
  uint16_t  usHandshakePosition;
  uint16_t  usReserved;
} NETX_BLOCK_DEFINITION;

/* Block ID */
#define RCX_BLOCK_MASK                                      0x00FFL
#define RCX_BLOCK_UNDEFINED                                 0x0000L
#define RCX_BLOCK_UNKNOWN                                   0x0001L
#define RCX_BLOCK_DATA_IMAGE                                0x0002L
#define RCX_BLOCK_DATA_IMAGE_HI_PRIO                        0x0003L
#define RCX_BLOCK_MAILBOX                                   0x0004L
#define RCX_BLOCK_CTRL_PARAM                                0x0005L
#define RCX_BLOCK_COMMON_STATE                              0x0006L
#define RCX_BLOCK_EXTENDED_STATE                            0x0007L
#define RCX_BLOCK_USER                                      0x0008L

/* Flags definition: Direction */
#define RCX_DIRECTION_MASK                                  0x000F
#define RCX_DIRECTION_UNDEFINED                             0x0000
#define RCX_DIRECTION_IN                                    0x0001
#define RCX_DIRECTION_OUT                                   0x0002
#define RCX_DIRECTION_INOUT                                 0x0003

/* Flags definition: Transmission type */
#define RCX_TRANSMISSION_TYPE_MASK                          0x00F0
#define RCX_TRANSMISSION_TYPE_UNDEFINED                     0x0000
#define RCX_TRANSMISSION_TYPE_DPM                           0x0010
#define RCX_TRANSMISSION_TYPE_DMA                           0x0020

/* Block definition: I/O Mode */
#define RCX_IO_MODE_DEFAULT                                 0x0000    /*!< I/O mode default, for compability reasons this value is identical to 0x4 (buffered host controlled) */
#define RCX_IO_MODE_BUFF_DEV_CTRL                           0x0002    /*!< I/O mode buffered device controlled */
#define RCX_IO_MODE_UNCONTROLLED                            0x0003    /*!< I/O mode bus synchronous device controlled */
#define RCX_IO_MODE_BUFF_HST_CTRL                           0x0004    /*!< I/O mode buffered host controlled */

/* Block definition: Synchronization Mode */
#define RCX_SYNC_MODE_OFF                                   0x00
#define RCX_SYNC_MODE_DEV_CTRL                              0x01
#define RCX_SYNC_MODE_HST_CTRL                              0x02

/* Block definition: Synchronization Sources */
#define RCX_SYNC_SOURCE_OFF                                 0x00
#define RCX_SYNC_SOURCE_1                                   0x01
#define RCX_SYNC_SOURCE_2                                   0x02




/*===========================================================================*/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*===========================================================================*/

/* Status Information */
#define RCX_SI_STATE_SUCCESS                                0x0000

/* Fault State */
#define RCX_FS_STATE_UNDEFINED                              0x0000
#define RCX_FS_STATE_NO_FAULT                               0x0001
#define RCX_FS_STATE_CONF_ERROR                             0x0002
#define RCX_FS_STATE_RECOVERABLE                            0x0003
#define RCX_FS_STATE_SEVERE                                 0x0004
#define RCX_FS_STATE_FATAL                                  0x0005
#define RCX_FS_STATE_WATCHDOG                               0x0006

/* Network State */
#define RCX_COMM_STATE_UNKNOWN                              0x0000
#define RCX_COMM_STATE_NOT_CONFIGURED                       0x0001
#define RCX_COMM_STATE_STOP                                 0x0002
#define RCX_COMM_STATE_IDLE                                 0x0003
#define RCX_COMM_STATE_OPERATE                              0x0004

/* Input / Output data states */
#define RCX_IODS_FIELDBUS_MASK                              0x00F0
#define RCX_IODS_DATA_STATE_GOOD                            0x0080
#define RCX_IODS_PROVIDER_RUN                               0x0040
#define RCX_IODS_GENERATED_LOCALLY                          0x0020

/* System Reset cookie */
#define RCX_SYS_RESET_COOKIE                                0x55AA55AA
#define RCX_SYS_BAD_MEMORY_COOKIE                           0x0BAD

/*===========================================================================*/
/*                                                                           */
/* RCX Packet Definition                                                     */
/*                                                                           */
/*===========================================================================*/
/* Structure of the RCX packet header */
#define RCX_MAX_PACKET_SIZE               1596            /*!< Maximum size of the RCX packet in bytes */
#define RCX_PACKET_HEADER_SIZE            40              /*!< Maximum size of the RCX packet header in bytes */
#define RCX_MAX_DATA_SIZE   (RCX_MAX_PACKET_SIZE - RCX_PACKET_HEADER_SIZE) /* Maximum RCX packet data size */

#define RCX_MSK_PACKET_ANSWER             0x00000001      /*!< Packet answer bit */

/* Packet default Destination */
#define RCX_SYSTEM_CHANNEL                0xFFFFFFFF

/* Packet destinations */
#define RCX_PACKET_DEST_SYSTEM            0
#define RCX_PACKET_DEST_PORT_0            1
#define RCX_PACKET_DEST_PORT_1            2
#define RCX_PACKET_DEST_PORT_2            3
#define RCX_PACKET_DEST_PORT_3            4
#define RCX_PACKET_DEST_DEFAULT_CHANNEL   0x00000020
#define RCX_PKT_COMM_CHANNEL_TOKEN        0x00000020

/* Flags for the packet extension field */
/* Sequence numbering */
#define RCX_PACKET_SEQ_NR_MASK            0x0000003f      /*!< Packet sequence number mask */
#define RCX_PACKET_SEQ_MASK               0x000000c0      /*!< Mask for the sequence bits */
#define RCX_PACKET_SEQ_NONE               0x00000000      /*!< No packet sequence */
#define RCX_PACKET_SEQ_FIRST              0x00000080      /*!< First packet of a sequence */
#define RCX_PACKET_SEQ_MIDDLE             0x000000c0      /*!< Packet in a sequence */
#define RCX_PACKET_SEQ_LAST               0x00000040      /*!< Last packet of a sequence */

/* Flag bits */
#define RCX_PACKET_RETRY                  0x00000200      /*!< Packet will be resent based on retry mechanism defined by e.g. stacks */

/* Default NO_ERROR packet state */
#define RCX_S_OK                          0

/* Global packet state errors */
#define RCX_E_FAIL                                0xC0000001
#define RCX_E_UNEXPECTED                          0xC0000002
#define RCX_E_OUTOFMEMORY                         0xC0000003
#define RCX_E_UNKNOWN_COMMAND                     0xC0000004
#define RCX_E_UNKNOWN_DESTINATION                 0xC0000005
#define RCX_E_UNKNOWN_DESTINATION_ID              0xC0000006
#define RCX_E_INVALID_PACKET_LEN                  0xC0000007
#define RCX_E_INVALID_EXTENSION                   0xC0000008
#define RCX_E_INVALID_PARAMETER                   0xC0000009
#define RCX_E_INVALID_ALIGNMENT                   0xC000000A
#define RCX_E_WATCHDOG_TIMEOUT                    0xC000000C
#define RCX_E_INVALID_LIST_TYPE                   0xC000000D
#define RCX_E_UNKNOWN_HANDLE                      0xC000000E
#define RCX_E_PACKET_OUT_OF_SEQ                   0xC000000F
#define RCX_E_PACKET_OUT_OF_MEMORY                0xC0000010
#define RCX_E_QUE_PACKETDONE                      0xC0000011
#define RCX_E_QUE_SENDPACKET                      0xC0000012
#define RCX_E_POOL_PACKET_GET                     0xC0000013
#define RCX_E_POOL_GET_LOAD                       0xC0000015
#define RCX_E_REQUEST_RUNNING                     0xC000001A

/* Global state errors */
#define RCX_E_INIT_FAULT                          0xC0000100
#define RCX_E_DATABASE_ACCESS_FAILED              0xC0000101
#define RCX_E_NOT_CONFIGURED                      0xC0000119
#define RCX_E_CONFIGURATION_FAULT                 0xC0000120
#define RCX_E_INCONSISTENT_DATA_SET               0xC0000121
#define RCX_E_DATA_SET_MISMATCH                   0xC0000122
#define RCX_E_INSUFFICIENT_LICENSE                0xC0000123
#define RCX_E_PARAMETER_ERROR                     0xC0000124
#define RCX_E_INVALID_NETWORK_ADDRESS             0xC0000125
#define RCX_E_NO_SECURITY_MEMORY                  0xC0000126
#define RCX_E_NETWORK_FAULT                       0xC0000140
#define RCX_E_CONNECTION_CLOSED                   0xC0000141
#define RCX_E_CONNECTION_TIMEOUT                  0xC0000142
#define RCX_E_LONELY_NETWORK                      0xC0000143
#define RCX_E_DUPLICATE_NODE                      0xC0000144
#define RCX_E_CABLE_DISCONNECT                    0xC0000145
#define RCX_E_BUS_OFF                             0xC0000180
#define RCX_E_CONFIG_LOCKED                       0xC0000181
#define RCX_E_APPLICATION_NOT_READY               0xC0000182

#define RCX_E_TIMER_APPL_PACKET_SENT              0xC002000C

/* MidSys packet state Error Codes */
#define RCX_E_QUE_UNKNOWN                         0xC02B0001
#define RCX_E_QUE_INDEX_UNKNOWN                   0xC02B0002
#define RCX_E_TASK_UNKNOWN                        0xC02B0003
#define RCX_E_TASK_INDEX_UNKNOWN                  0xC02B0004
#define RCX_E_TASK_HANDLE_INVALID                 0xC02B0005
#define RCX_E_TASK_INFO_IDX_UNKNOWN               0xC02B0006
#define RCX_E_FILE_XFR_TYPE_INVALID               0xC02B0007
#define RCX_E_FILE_REQUEST_INCORRECT              0xC02B0008
#define RCX_E_UNKNOWN_PORT_INDEX                  0xC02B0009
#define RCX_E_ROUTER_TABLE_FULL                   0xC02B000A
#define RCX_E_NO_SUCH_ROUTER_IN_TABLE             0xC02B000B
#define RCX_E_INSTANCE_NOT_NULL                   0xC02B000C
#define RCX_E_COMMAND_INVALID                     0xC02B000D
#define RCX_E_TASK_INVALID                        0xC02B000E
#define RCX_E_TASK_NOT_A_USER_TASK                0xC02B000F
#define RCX_E_INVALID_FIRMWARE_SIZE               0xC02B001B
#define RCX_E_SEC_FAILED                          0xC02B001D
#define RCX_E_SEC_DISABLED                        0xC02B001E
#define RCX_E_BLOCK_SIZE_OUT_OF_RANGE             0xC02B0020
#define RCX_E_INVALID_CHANNEL                     0xC02B0021
#define RCX_E_INVALID_FILE_LENGTH                 0xC02B0022
#define RCX_E_INVALID_CHARACTER                   0xC02B0023
#define RCX_E_PACKET_OUT_OF_SEQUNCE               0xC02B0024
#define RCX_E_NOT_POSSIBLE_IN_CURRENT_STATE       0xC02B0025
#define RCX_E_SECURTY_EEPROM_INVALID_ZONE         0xC02B0026
#define RCX_E_SECURTY_EEPROM_NOT_ALLOWED          0xC02B0027
#define RCX_E_SECURTY_EEPROM_NOT_AVAILABLE        0xC02B0028
#define RCX_E_SECURTY_EEPROM_INVALID_CHECKSUM     0xC02B0029
#define RCX_E_SECURTY_EEPROM_ZONE_NOT_WRITEABLE   0xC02B002A
#define RCX_E_SECURTY_EEPROM_READ_FAILED          0xC02B002B
#define RCX_E_SECURTY_EEPROM_WRITE_FAILED         0xC02B002C
#define RCX_E_SECURTY_EEPROM_ZONE_ACCESS_DENIDED  0xC02B002D
#define RCX_E_SECURTY_EEPROM_EMULATED             0xC02B002E
#define RCX_E_FILE_NAME_INVALID                   0xC02B002F
#define RCX_E_FILE_SEQUENCE_ERROR                 0xC02B0030
#define RCX_E_FILE_SEQUENCE_END_ERROR             0xC02B0031
#define RCX_E_FILE_SEQUENCE_BEGIN_ERROR           0xC02B0032
#define RCX_E_FILE_UNEXPECTED_BLOCK_SIZE          0xC02B0033
#define RCX_E_HIL_FILE_HEADER_CRC_ERROR           0xC02B0034
#define RCX_E_HIL_FILE_HEADER_MODULE_SIZE_DIFFERS 0xC02B0035
#define RCX_E_HIL_FILE_HEADER_MD5_CHECKSUM_ERROR  0xC02B0036
#define RCX_E_PACKET_WOULD_BE_TO_LONG_FOR_MTU     0xC02B0037
#define RCX_E_INVALID_BLOCK                       0xC02B0038
#define RCX_E_INVALID_STRUCT_NUMBER               0xC02B0039

/*****************************************************************************/
/*! Default RCX packet header structure                                      */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct RCX_PACKET_HEADERtag
{
  uint32_t   ulDest;                                 /*!< 00:04, Destination of packet, process queue */
  uint32_t   ulSrc;                                  /*!< 04:04, Source of packet, process queue */
  uint32_t   ulDestId;                               /*!< 08:04, Destination reference of packet*/
  uint32_t   ulSrcId;                                /*!< 12:04, Source reference of packet */
  uint32_t   ulLen;                                  /*!< 16:04, Length of packet data without header */
  uint32_t   ulId;                                   /*!< 20:04, Identification handle of sender */
  uint32_t   ulState;                                /*!< 24:04, Status code of operation */
  uint32_t   ulCmd;                                  /*!< 28:04, Packet command */
  uint32_t   ulExt;                                  /*!< 32:04, Extension */
  uint32_t   ulRout;                                 /*!< 36:04, Router (internal use only) */
} __RCX_PACKED_POST RCX_PACKET_HEADER;

/*****************************************************************************/
/*! Default RCX packet structure, including user data                        */
/*****************************************************************************/
typedef __RCX_PACKED_PRE struct RCX_PACKETtag
{
  RCX_PACKET_HEADER tHeader;                              /*!< Packet header */
  uint8_t     abData[RCX_MAX_DATA_SIZE];            /*!< Packet data */
} __RCX_PACKED_POST RCX_PACKET;

/*****************************************************************************/
/*! Firmware Identification                                                  */
/*****************************************************************************/

typedef __RCX_PACKED_PRE struct tagNETX_FW_VERSION
{
  uint16_t    usMajor;
  uint16_t    usMinor;
  uint16_t    usBuild;
  uint16_t    usRevision;
} __RCX_PACKED_POST NETX_FW_VERSION;

typedef __RCX_PACKED_PRE struct tagNETX_FW_NAME
{
  uint8_t bNameLength;
  uint8_t abName[ 63 ];
} __RCX_PACKED_POST NETX_FW_NAME;

typedef __RCX_PACKED_PRE struct tagNETX_FW_DATE
{
  uint16_t  usYear;
  uint8_t   bMonth;
  uint8_t   bDay;
} __RCX_PACKED_POST NETX_FW_DATE;

typedef __RCX_PACKED_PRE struct tagNETX_FW_IDENTIFICATION
{
  NETX_FW_VERSION tFwVersion;                           /* !< firmware version */
  NETX_FW_NAME    tFwName;                              /* !< firmware name    */
  NETX_FW_DATE    tFwDate;                              /* !< firmware date    */
} __RCX_PACKED_POST NETX_FW_IDENTIFICATION;

/*****************************************************************************/
/*! Hardware name                                                            */
/*****************************************************************************/

typedef __RCX_PACKED_PRE struct tagNETX_HW_NAME
{
  uint8_t bNameLength;
  uint8_t abName[ 63 ];
} __RCX_PACKED_POST NETX_HW_NAME;


/*---------------------------------------------------------------------------*/
/* Compiler settings */
#ifdef _MSC_VER
  #if _MSC_VER >= 1000
    #pragma pack()           /* Always allign structures to compiler settings  */
  #endif /* _MSC_VER >= 1000 */
#endif /* _MSC_VER */
/*---------------------------------------------------------------------------*/

#undef __RCX_PACKED_PRE
#undef __RCX_PACKED_POST

#endif  /* __RCX_USER_H */
