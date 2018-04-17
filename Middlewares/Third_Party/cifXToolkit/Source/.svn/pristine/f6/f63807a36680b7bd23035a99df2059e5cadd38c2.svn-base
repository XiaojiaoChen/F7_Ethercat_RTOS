/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: rcX_Public.h 6827 2015-03-31 15:23:50Z Robert $:

  Description:
    rcX Public Packet functions

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2014-12-05  added structure definition for RCX_PHYSMEM_READ_REQ
    2014-05-06  added RCX_FILE_RENAME_REQ to support file renaming
    2014-04-28  packed RCX_VERIFY_MASTER_DATABASE_T to handle strict
                packing rules of armcc compiler
    2012-08-28  added RCX_LINK_STATUS_CHANGE_IND and definitions
    2012-07-17  added RCX_GET_FW_PARAMETER_REQ and definitions
    2012-06-27  added parameter id PID_BAUDRATE (RCX_SET_FW_PARAMETER_REQ)
    2012-03-28  removed C++ comments, to prevent compiler warnings
    2012-02-13  added RCX_SET_FW_PARAMETER_REQ and definitions
    2011-12-06  added RCX_TIME_COMMAND_REQ and definitions
    2011-05-13  added definitions for configuration in run
    2011-02-25  added structure definition for RCX_FORMAT_REQ
    2011-02-24  added command definition for RCX_FORMAT_REQ
    2010-12-02  added packet RCX_MALLINFO_REQ
    2010-10-06  renamed ulCmd to ulAction in RCX_BUSSCAN_REQ_DATA_T
    2010-09-14  Added RCX_FILE_GET_HEADER_MD5_REQ
    2010-04-28  Removed define CIFX_TOOLKIT and included common
                packing __TLR_PACKED_PRE / POST
    2010-04-27  For CIFX_TOOLKIT: Changed defines
                __TKITPACKED_xx from __PACKED_xx to
                __TLR_PACKED_xx
                Changed include of TLR_INX_Includes.h to TLR_Types.h
    2010-04-20  added new packet definition RCX_SET_HANDSHAKE_CONFIG_REQ
    2010-04-16  RCX_VERIFY_DATABASE_REQ_SIZE did not work due
                to an additional space character
    2010-04-13  Included TLR_INX_Includes.h instead of TLR_Includes.h
    2010-03-23  File created.

**************************************************************************************/


#ifndef __RCX_PUBLIC_H
#define __RCX_PUBLIC_H


#include "TLR_Types.h"
#include "rcX_User.h"

#define RCX_PROCESS_QUEUE_NAME "RCX_QUE"

/* firmware control */
#define RCX_FIRMWARE_RESET_REQ                        0x00001E00
#define RCX_FIRMWARE_RESET_CNF                        0x00001E01

/* firmware information */
#define RCX_LISTS_GET_NUM_ENTRIES_REQ                 0x00001E10
#define RCX_LISTS_GET_NUM_ENTRIES_CNF                 0x00001E11

/* queue identification */
#define RCX_QUE_IDENTIFY_REQ                          0x00001E20
#define RCX_QUE_IDENTIFY_CNF                          0x00001E21
#define RCX_QUE_IDENTIFY_IDX_REQ                      0x00001E22
#define RCX_QUE_IDENTIFY_IDX_CNF                      0x00001E23

/* queue load retrieval */
#define RCX_QUE_GET_LOAD_REQ                          0x00001E30
#define RCX_QUE_GET_LOAD_CNF                          0x00001E31

/* DPM data access functions */
#define RCX_SYSTEM_INFORMATION_BLOCK_REQ              0x00001E32
#define RCX_SYSTEM_INFORMATION_BLOCK_CNF              0x00001E33
#define RCX_CHANNEL_INFORMATION_BLOCK_REQ             0x00001E34
#define RCX_CHANNEL_INFORMATION_BLOCK_CNF             0x00001E35
#define RCX_SYSTEM_CONTROL_BLOCK_REQ                  0x00001E36
#define RCX_SYSTEM_CONTROL_BLOCK_CNF                  0x00001E37
#define RCX_SYSTEM_STATUS_BLOCK_REQ                   0x00001E38
#define RCX_SYSTEM_STATUS_BLOCK_CNF                   0x00001E39
#define RCX_CONTROL_BLOCK_REQ                         0x00001E3A
#define RCX_CONTROL_BLOCK_CNF                         0x00001E3B
#define RCX_HANDSHAKE_CHANNEL_REQ                     0x00001E3C
#define RCX_HANDSHAKE_CHANNEL_CNF                     0x00001E3D

/* task identification and readout of diagnosis data */
#define RCX_TSK_GET_NAME_REQ                          0x00001E3E
#define RCX_TSK_GET_NAME_CNF                          0x00001E3F
#define RCX_TSK_IDENTIFY_REQ                          0x00001E40
#define RCX_TSK_IDENTIFY_CNF                          0x00001E41
#define RCX_TSK_IDENTIFY_IDX_REQ                      0x00001E42
#define RCX_TSK_IDENTIFY_IDX_CNF                      0x00001E43
#define RCX_TSK_GET_STATUS_REQ                        0x00001E44
#define RCX_TSK_GET_STATUS_CNF                        0x00001E45
#define RCX_TSK_GET_INFO_FIELD_REQ                    0x00001E46
#define RCX_TSK_GET_INFO_FIELD_CNF                    0x00001E47

/* task control */
#define RCX_TSK_START_REQ                             0x00001E48
#define RCX_TSK_START_CNF                             0x00001E49
#define RCX_TSK_STOP_REQ                              0x00001E4A
#define RCX_TSK_STOP_CNF                              0x00001E4B

#define RCX_TSK_GET_STATUS_ARRAY_REQ                  0x00001E4E
#define RCX_TSK_GET_STATUS_ARRAY_CNF                  0x00001E4F

/* task array identification and structure information readout */
#define RCX_TSK_GET_INFO_ARRAY_REQ                    0x00001E50
#define RCX_TSK_GET_INFO_ARRAY_CNF                    0x00001E51
#define RCX_TSK_GET_INFO_STRUCT_REQ                   0x00001E52
#define RCX_TSK_GET_INFO_STRUCT_CNF                   0x00001E53
#define RCX_TSK_GET_INFO_STRUCT_IDX_REQ               0x00001E54
#define RCX_TSK_GET_INFO_STRUCT_IDX_CNF               0x00001E55
#define RCX_TSK_GET_INFO_FIELD_SIZE_REQ               0x00001E56
#define RCX_TSK_GET_INFO_FIELD_SIZE_CNF               0x00001E57
#define RCX_TSK_GET_INFO_FIELD_SIZE_IDX_REQ           0x00001E58
#define RCX_TSK_GET_INFO_FIELD_SIZE_IDX_CNF           0x00001E59

/* read information about memory usage */
#define RCX_MALLINFO_REQ                              0x00001E5A
#define RCX_MALLINFO_CNF                              0x00001E5B

/* file upload/download */
#define RCX_FILE_DOWNLOAD_REQ                         0x00001E62
#define RCX_FILE_DOWNLOAD_CNF                         0x00001E63
#define RCX_FILE_DOWNLOAD_DATA_REQ                    0x00001E64
#define RCX_FILE_DOWNLOAD_DATA_CNF                    0x00001E65

#define RCX_FILE_DOWNLOAD_ABORT_REQ                   0x00001E66
#define RCX_FILE_DOWNLOAD_ABORT_CNF                   0x00001E67

#define RCX_FILE_UPLOAD_REQ                           0x00001E60
#define RCX_FILE_UPLOAD_CNF                           0x00001E61
#define RCX_FILE_UPLOAD_DATA_REQ                      0x00001E6E
#define RCX_FILE_UPLOAD_DATA_CNF                      0x00001E6F

#define RCX_FILE_UPLOAD_ABORT_REQ                     0x00001E5E
#define RCX_FILE_UPLOAD_ABORT_CNF                     0x00001E5F

#define RCX_FORMAT_REQ                                0x00001ED6
#define RCX_FORMAT_CNF                                0x00001ED7

/* file information */
#define RCX_FILE_GET_MD5_REQ                          0x00001E68
#define RCX_FILE_GET_MD5_CNF                          0x00001E69
#define RCX_FILE_GET_HEADER_MD5_REQ                   0x00001E72
#define RCX_FILE_GET_HEADER_MD5_CNF                   0x00001E73

/* file delete */
#define RCX_FILE_DELETE_REQ                           0x00001E6A
#define RCX_FILE_DELETE_CNF                           0x00001E6B

/* file rename */
#define RCX_FILE_RENAME_REQ                           0x00001E7C
#define RCX_FILE_RENAME_CNF                           0x00001E7D

/* volume information */
#define RCX_VOLUME_GET_ENTRY_REQ                      0x00001E6C
#define RCX_VOLUME_GET_ENTRY_CNF                      0x00001E6D

/* directory list */
#define RCX_DIR_LIST_REQ                              0x00001E70
#define RCX_DIR_LIST_CNF                              0x00001E71

/* indexed task access */
#define RCX_TSK_GET_STATUS_IDX_REQ                    0x00001E74
#define RCX_TSK_GET_STATUS_IDX_CNF                    0x00001E75
#define RCX_TSK_GET_INFO_FIELD_IDX_REQ                0x00001E76
#define RCX_TSK_GET_INFO_FIELD_IDX_CNF                0x00001E77

/* indexed task control */
#define RCX_TSK_START_IDX_REQ                         0x00001E78
#define RCX_TSK_START_IDX_CNF                         0x00001E79
#define RCX_TSK_STOP_IDX_REQ                          0x00001E7A
#define RCX_TSK_STOP_IDX_CNF                          0x00001E7B

/* log queues */
#define RCX_QUE_LOG_SET_REQ                           0x00001EA0
#define RCX_QUE_LOG_SET_CNF                           0x00001EA1
#define RCX_QUE_LOG_CLR_REQ                           0x00001EA2
#define RCX_QUE_LOG_CLR_CNF                           0x00001EA3

/* read/write memory */
#define RCX_PHYSMEM_READ_REQ                          0x00001EA8
#define RCX_PHYSMEM_READ_CNF                          0x00001EA9

#define RCX_PHYSMEM_WRITE_REQ                         0x00001EAA
#define RCX_PHYSMEM_WRITE_CNF                         0x00001EAB

/* firmware info */
#define RCX_GET_LIB_VERSION_INFO_REQ                  0x00001EBA
#define RCX_GET_LIB_VERSION_INFO_CNF                  0x00001EBB


#define RCX_FIRMWARE_IDENTIFY_REQ                     0x00001EB6
#define RCX_FIRMWARE_IDENTIFY_CNF                     0x00001EB7

#define RCX_HW_IDENTIFY_REQ                           0x00001EB8
#define RCX_HW_IDENTIFY_CNF                           0x00001EB9

#define RCX_SECURITY_EEPROM_READ_REQ                  0x00001EBC
#define RCX_SECURITY_EEPROM_READ_CNF                  0x00001EBD
#define RCX_SECURITY_EEPROM_WRITE_REQ                 0x00001EBE
#define RCX_SECURITY_EEPROM_WRITE_CNF                 0x00001EBF

/* module management */
#define RCX_MODULE_INSTANTIATE_REQ                    0x00001EC0
#define RCX_MODULE_INSTANTIATE_CNF                    0x00001EC1
#define RCX_MODULE_GET_INFO_IDX_REQ                   0x00001EC2
#define RCX_MODULE_GET_INFO_IDX_CNF                   0x00001EC3
#define RCX_CHANNEL_INSTANTIATE_REQ                   0x00001EC4
#define RCX_CHANNEL_INSTANTIATE_CNF                   0x00001EC5

#define RCX_SET_MAC_ADDR_REQ                          0x00001EEE
#define RCX_SET_MAC_ADDR_CNF                          0x00001EEF

#define RCX_HW_LICENSE_INFO_REQ                       0x00001EF4
#define RCX_HW_LICENSE_INFO_CNF                       0x00001EF5

#define RCX_HW_HARDWARE_INFO_REQ                      0x00001EF6
#define RCX_HW_HARDWARE_INFO_CNF                      0x00001EF7

/* DPM info functions */
#define RCX_DPM_GET_BLOCK_INFO_REQ                    0x00001EF8
#define RCX_DPM_GET_BLOCK_INFO_CNF                    0x00001EF9

/* Communication flag info functions */
#define RCX_DPM_GET_COMFLAG_INFO_REQ                  0x00001EFA
#define RCX_DPM_GET_COMFLAG_INFO_CNF                  0x00001EFB


/* Common Status block functions */
#define RCX_DPM_GET_COMMON_STATE_REQ                  0x00001EFC
#define RCX_DPM_GET_COMMON_STATE_CNF                  0x00001EFD

/* Extended status block */
#define RCX_DPM_GET_EXTENDED_STATE_REQ                0x00001EFE
#define RCX_DPM_GET_EXTENDED_STATE_CNF                0x00001EFF

/* reserved for further functions (documented at DPM Spec) */

#define RCX_ENABLE_PERF_MEASUREMENT_REQ               0x00001ED2
#define RCX_ENABLE_PERF_MEASUREMENT_CNF               0x00001ED3

#define RCX_GET_PERF_COUNTERS_REQ                     0x00001ED4
#define RCX_GET_PERF_COUNTERS_CNF                     0x00001ED5

/* Time handling requests */
#define RCX_TIME_COMMAND_REQ                          0x00001ED8
#define RCX_TIME_COMMAND_CNF                          0x00001ED9


/* Backup / Restore commands */
#define RCX_BACKUP_REQ                                0x00001F50
#define RCX_BACKUP_CNF                                0x00001F51
#define RCX_RESTORE_REQ                               0x00001F52
#define RCX_RESTORE_CNF                               0x00001F53
/* do NOT add further commands in the range 0x00001FXX (because of collosion with PNS_IF task) */

/***************************************************************************************/
/* Common global stack commands */

#define RCX_GET_WATCHDOG_TIME_REQ                     0x00002F02
#define RCX_GET_WATCHDOG_TIME_CNF                     0x00002F03

#define RCX_SET_WATCHDOG_TIME_REQ                     0x00002F04
#define RCX_SET_WATCHDOG_TIME_CNF                     0x00002F05

#define RCX_GET_SLAVE_HANDLE_REQ                      0x00002F08
#define RCX_GET_SLAVE_HANDLE_CNF                      0x00002F09

#define RCX_GET_SLAVE_CONN_INFO_REQ                   0x00002F0A
#define RCX_GET_SLAVE_CONN_INFO_CNF                   0x00002F0B

#define RCX_GET_DPM_IO_INFO_REQ                       0x00002F0C
#define RCX_GET_DPM_IO_INFO_CNF                       0x00002F0D

#define RCX_REGISTER_APP_REQ                          0x00002F10
#define RCX_REGISTER_APP_CNF                          0x00002F11

#define RCX_UNREGISTER_APP_REQ                        0x00002F12
#define RCX_UNREGISTER_APP_CNF                        0x00002F13

#define RCX_DELETE_CONFIG_REQ                         0x00002F14
#define RCX_DELETE_CONFIG_CNF                         0x00002F15

#define RCX_READ_IO_DATA_IMAGE_REQ                    0x00002F20
#define RCX_READ_IO_DATA_IMAGE_CNF                    0x00002F21

#define RCX_BUSSCAN_REQ                               0x00002f22
#define RCX_BUSSCAN_CNF                               0x00002f23

#define RCX_GET_DEVICE_INFO_REQ                       0x00002f24
#define RCX_GET_DEVICE_INFO_CNF                       0x00002f25

#define RCX_START_STOP_COMM_REQ                       0x00002F30
#define RCX_START_STOP_COMM_CNF                       0x00002F31

#define RCX_LOCK_UNLOCK_CONFIG_REQ                    0x00002F32
#define RCX_LOCK_UNLOCK_CONFIG_CNF                    0x00002F33

#define RCX_SET_HANDSHAKE_CONFIG_REQ                  0x00002F34
#define RCX_SET_HANDSHAKE_CONFIG_CNF                  0x00002F35

#define RCX_CHANNEL_INIT_REQ                          0x00002F80
#define RCX_CHANNEL_INIT_CNF                          0x00002F81

#define RCX_VERIFY_DATABASE_REQ                       0x00002F82
#define RCX_VERIFY_DATABASE_CNF                       0x00002F83

#define RCX_ACTIVATE_DATABASE_REQ                     0x00002F84
#define RCX_ACTIVATE_DATABASE_CNF                     0x00002F85

#define RCX_SET_FW_PARAMETER_REQ                      0x00002F86
#define RCX_SET_FW_PARAMETER_CNF                      0x00002F87

#define RCX_GET_FW_PARAMETER_REQ                      0x00002F88
#define RCX_GET_FW_PARAMETER_CNF                      0x00002F89

#define RCX_LINK_STATUS_CHANGE_IND                    0x00002F8A
#define RCX_LINK_STATUS_CHANGE_RES                    0x00002F8B


/* pragma pack */
#ifdef PRAGMA_PACK_ENABLE
  #pragma PRAGMA_PACK_1(RCX_PUBLIC)
#endif

/******************************************************************************
 * Packet: RCX_TIME_COMMAND_REQ/RCX_TIME_COMMAND_CNF
 *
 */

/* Time command codes */
#define TIME_CMD_GETSTATE                 0x00000001
#define TIME_CMD_GETTIME                  0x00000002
#define TIME_CMD_SETTIME                  0x00000003

/* Time RTC information */
#define TIME_INFO_RTC_MSK                 0x00000007
#define TIME_INFO_RTC_TYPE_MSK            0x00000003
#define TIME_INFO_RTC_RTC_STATE           0x00000004

typedef __TLR_PACKED_PRE struct RCX_TIME_CMD_DATA_Ttag
{
  TLR_UINT32  ulTimeCmd;
  TLR_UINT32  ulData;
  TLR_UINT32  ulReserved;
} __TLR_PACKED_POST RCX_TIME_CMD_DATA_T;

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TIME_CMD_REQ_Ttag
{
  TLR_PACKET_HEADER_T   tHead;  /* packet header  */
  RCX_TIME_CMD_DATA_T   tData;  /* packet data    */
} RCX_TIME_CMD_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TIME_CMD_CNF_Ttag
{
  TLR_PACKET_HEADER_T   tHead;  /* packet header  */
  RCX_TIME_CMD_DATA_T   tData;  /* packet data    */
} RCX_TIME_CMD_CNF_T;


/******************************************************************************
 * Packet: RCX_ENABLE_PERF_MEASUREMENT_REQ/RCX_ENABLE_PERF_MEASUREMENT_CNF
 *
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_ENABLE_PERF_MEASUREMENT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
} __TLR_PACKED_POST RCX_ENABLE_PERF_MEASUREMENT_REQ_T;

/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_ENABLE_PERF_MEASUREMENT_CNF_DATA_Ttag
{
  TLR_UINT32                              ulOldState;
} RCX_ENABLE_PERF_MEASUREMENT_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_ENABLE_PERF_MEASUREMENT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_ENABLE_PERF_MEASUREMENT_CNF_DATA_T  tData;
} __TLR_PACKED_POST RCX_ENABLE_PERF_MEASUREMENT_CNF_T;

/******************************************************************************
 * Packet: RCX_GET_PERF_COUNTERS_REQ/RCX_GET_PERF_COUNTERS_CNF
 *
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_GET_PERF_COUNTERS_REQ_DATA_Ttag
{
  TLR_UINT16                              usStartToken;
  TLR_UINT16                              usTokenCount;
} __TLR_PACKED_POST RCX_GET_PERF_COUNTERS_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_PERF_COUNTERS_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_GET_PERF_COUNTERS_REQ_DATA_T        tData;
} __TLR_PACKED_POST RCX_GET_PERF_COUNTERS_REQ_T;

/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_PERF_COUNTER_DATA_Ttag
{
  TLR_UINT32                              ulNanosecondsLower;
  TLR_UINT32                              ulNanosecondsUpper;
} __TLR_PACKED_POST RCX_PERF_COUNTER_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_PERF_COUNTERS_CNF_DATA_Ttag
{
  TLR_UINT16                              usStartToken;
  TLR_UINT16                              usTokenCount;
  RCX_PERF_COUNTER_DATA_T                 tPerfSystemUptime;
  /* following entry is a placeholder for a dynamic array whose length is given by ulLen in the packet header */
  RCX_PERF_COUNTER_DATA_T                 atPerfCounters[1];
} __TLR_PACKED_POST RCX_GET_PERF_COUNTERS_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_PERF_COUNTERS_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_GET_PERF_COUNTERS_CNF_DATA_T        tData;
} __TLR_PACKED_POST RCX_GET_PERF_COUNTERS_CNF_T;

/******************************************************************************
 * Packet: RCX_SET_MAC_ADDR_REQ/RCX_SET_MAC_ADDR_CNF
 *
 *          This packet reconfigures the MAC address
 *          If RCX_STORE_MAC_ADDRESS is set, it will also update the Sec EEPROM permanently.
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_SET_MAC_ADDR_REQ_DATA_Ttag
{
  TLR_UINT32                      ulParam;              /* Parameter Bit Field */
  TLR_UINT8                       abMacAddr[6];         /* MAC address */
  TLR_UINT8                       abPad[2];             /* Pad bytes, set to zero */
} __TLR_PACKED_POST RCX_SET_MAC_ADDR_REQ_DATA_T;

#define RCX_STORE_MAC_ADDRESS         0x00000001
#define RCX_FORCE_MAC_ADDRESS         0x00000002

typedef __TLR_PACKED_PRE struct RCX_SET_MAC_ADDR_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_SET_MAC_ADDR_REQ_DATA_T     tData;                /* packet data */
} __TLR_PACKED_POST RCX_SET_MAC_ADDR_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_SET_MAC_ADDR_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
} __TLR_PACKED_POST RCX_SET_MAC_ADDR_CNF_T;


/******************************************************************************
 * Packet: RCX_FIRMWARE_RESET_REQ/RCX_FIRMWARE_RESET_CNF
 *
 *          This packet executes a RESET on the netX
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FIRMWARE_RESET_REQ_DATA_Ttag
{
  TLR_UINT32                      ulTimeToReset;        /* time to reset in ms */
  TLR_UINT32                      ulResetMode;          /* reset mode param */
} __TLR_PACKED_POST RCX_FIRMWARE_RESET_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FIRMWARE_RESET_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_FIRMWARE_RESET_REQ_DATA_T   tData;                /* packet data */
} __TLR_PACKED_POST RCX_FIRMWARE_RESET_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FIRMWARE_RESET_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
} __TLR_PACKED_POST RCX_FIRMWARE_RESET_CNF_T;


/******************************************************************************
 * Packet: RCX_QUE_IDENTIFY_REQ/RCX_QUE_IDENTIFY_CNF
 *
 *        This packet allows identifying a queue by name
 */


/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_QUE_IDENTIFY_REQ_DATA_Ttag
{
  TLR_STR                         szQueName[16];        /* queue name */
  TLR_UINT32                      ulInst;               /* instance of queue */
} __TLR_PACKED_POST RCX_QUE_IDENTIFY_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_QUE_IDENTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_QUE_IDENTIFY_REQ_DATA_T     tData;                /* packet data */
} __TLR_PACKED_POST RCX_QUE_IDENTIFY_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_IDENTIFY_CNF_DATA_Ttag
{
  TLR_UINT32                      ulQue;                /* queue handle */
} __TLR_PACKED_POST RCX_QUE_IDENTIFY_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_QUE_IDENTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_QUE_IDENTIFY_CNF_DATA_T     tData;                /* packet data */
} __TLR_PACKED_POST RCX_QUE_IDENTIFY_CNF_T;


/******************************************************************************
 * Packet: RCX_QUE_IDENTIFY_IDX_REQ/RCX_QUE_IDENTIFY_IDX_CNF
 *
 *        This packet allows identifying a queue by index
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_IDENTIFY_IDX_REQ_DATA_Ttag
{
  TLR_UINT32                      ulIndex;              /* queue table index */
} __TLR_PACKED_POST RCX_QUE_IDENTIFY_IDX_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_QUE_IDENTIFY_IDX_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_QUE_IDENTIFY_IDX_REQ_DATA_T tData;                /* packet data */
} __TLR_PACKED_POST RCX_QUE_IDENTIFY_IDX_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_IDENTIFY_IDX_CNF_DATA_Ttag
{
  TLR_UINT32                      ulIndex;              /* queue table index */
  TLR_STR                         szQueName[16];        /* queue name */
  TLR_UINT32                      ulInst;               /* instance of queue */
  TLR_UINT32                      ulQue;                /* queue handle */
} __TLR_PACKED_POST RCX_QUE_IDENTIFY_IDX_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_QUE_IDENTIFY_IDX_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_QUE_IDENTIFY_IDX_CNF_DATA_T tData;                /* packet data */
} __TLR_PACKED_POST RCX_QUE_IDENTIFY_IDX_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_IDENTIFY_REQ/RCX_TSK_IDENTIFY_CNF
 *
 *          This packet allows identifying a task by name
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_IDENTIFY_REQ_DATA_Ttag
{
  TLR_STR                         szTskName[16];        /* task name */
  TLR_UINT32                      ulInst;               /* task instance */
} __TLR_PACKED_POST RCX_TSK_IDENTIFY_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_IDENTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_TSK_IDENTIFY_REQ_DATA_T     tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_IDENTIFY_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_IDENTIFY_CNF_DATA_Ttag
{
  TLR_UINT32                      ulTsk;                /* task handle */
  TLR_UINT32                      ulTskIdentifier;      /* task identifier */
  TLR_UINT16                      usTskMajorVersion;    /* task major version */
  TLR_UINT16                      usTskMinorVersion;    /* task minor version */
  TLR_UINT32                      ulNumOfDiagStructs;   /* count of task diagnostic structures */
  TLR_UINT32                      ulPriority;           /* task priority */
} __TLR_PACKED_POST RCX_TSK_IDENTIFY_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_IDENTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_TSK_IDENTIFY_CNF_DATA_T     tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_IDENTIFY_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_GET_NAME_REQ/RCX_TSK_GET_NAME_CNF
 *
 *          This packet allows retrieving a task name from a given handle
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_NAME_REQ_DATA_Ttag
{
  TLR_UINT32                      ulTsk;                /* task handle */
} __TLR_PACKED_POST RCX_TSK_GET_NAME_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_NAME_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_TSK_GET_NAME_REQ_DATA_T     tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_NAME_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_NAME_CNF_DATA_Ttag
{
  TLR_UINT8                       abTskName[16];        /* task name */
  TLR_UINT32                      ulInstance;           /* task instance */
} __TLR_PACKED_POST RCX_TSK_GET_NAME_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_NAME_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_TSK_GET_NAME_CNF_DATA_T     tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_NAME_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_IDENTIFY_IDX_REQ/RCX_TSK_IDENTIFY_IDX_CNF
 *
 *          This packet allows identifying a task by index
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_IDENTIFY_IDX_REQ_DATA_Ttag
{
  TLR_UINT32                      ulIndex;              /* task table index */
} __TLR_PACKED_POST RCX_TSK_IDENTIFY_IDX_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_IDENTIFY_IDX_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_TSK_IDENTIFY_IDX_REQ_DATA_T tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_IDENTIFY_IDX_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_IDENTIFY_IDX_CNF_DATA_Ttag
{
  TLR_UINT32                      ulIndex;              /* task table index */
  TLR_STR                         szTskName[16];        /* task name */
  TLR_UINT32                      ulInstance;           /* task instance */
  TLR_UINT32                      ulTsk;                /* task handle */
  TLR_UINT32                      ulTskIdentifier;      /* task identifier */
  TLR_UINT16                      usTskMajorVersion;    /* task major version */
  TLR_UINT16                      usTskMinorVersion;    /* task minor version */
  TLR_UINT32                      ulNumOfDiagStructs;   /* count of task diagnostic structures */
  TLR_UINT32                      ulPriority;           /* task priority */
} __TLR_PACKED_POST RCX_TSK_IDENTIFY_IDX_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_IDENTIFY_IDX_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_TSK_IDENTIFY_IDX_CNF_DATA_T tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_IDENTIFY_IDX_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_GET_STATUS_IDX_REQ/RCX_TSK_GET_STATUS_IDX_CNF
 * Packet: RCX_TSK_GET_STATUS_REQ    /RCX_TSK_GET_STATUS_CNF
 *
 *          These packets allow retrieving the task status either by index or handle
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STATUS_REQ_DATA_Ttag
{
  TLR_UINT32                      ulTsk;                /* task handle */
} __TLR_PACKED_POST RCX_TSK_GET_STATUS_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STATUS_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_TSK_GET_STATUS_REQ_DATA_T   tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_STATUS_REQ_T;

typedef RCX_TSK_GET_STATUS_REQ_T RCX_TSK_GET_STATUS_IDX_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STATUS_CNF_DATA_Ttag
{
  TLR_UINT32                      ulStatusCode;         /* task status code */
} __TLR_PACKED_POST RCX_TSK_GET_STATUS_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STATUS_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                /* packet header */
  RCX_TSK_GET_STATUS_CNF_DATA_T   tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_STATUS_CNF_T;

typedef RCX_TSK_GET_STATUS_CNF_T RCX_TSK_GET_STATUS_IDX_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_GET_INFO_FIELD_REQ/RCX_TSK_GET_INFO_FIELD_CNF
 *
 *          This packet retrieves the diagnostic structures of a given task
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_FIELD_REQ_DATA_Ttag
{
  TLR_UINT32                      ulTsk;                /* task handle */
  TLR_UINT32                      ulInfoNo;             /* index of information field */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_FIELD_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_FIELD_REQ_Ttag
{
  TLR_PACKET_HEADER_T               tHead;              /* packet header */
  RCX_TSK_GET_INFO_FIELD_REQ_DATA_T tData;              /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_FIELD_REQ_T;

typedef RCX_TSK_GET_INFO_FIELD_REQ_T RCX_TSK_GET_INFO_FIELD_IDX_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_FIELD_CNF_DATA_Ttag
{
  TLR_UINT8                       abData[1];       /* ATTENTION: This is a placeholder for info field data.
                                                                 The packet must be allocated in correct size*/
} __TLR_PACKED_POST RCX_TSK_GET_INFO_FIELD_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_FIELD_CNF_Ttag
{
  TLR_PACKET_HEADER_T               tHead;            /* packet header */
  RCX_TSK_GET_INFO_FIELD_CNF_DATA_T tData;            /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_FIELD_CNF_T;

typedef RCX_TSK_GET_INFO_FIELD_CNF_T RCX_TSK_GET_INFO_FIELD_IDX_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_GET_INFO_FIELD_SIZE_REQ/RCX_TSK_GET_INFO_FIELD_SIZE_CNF
 *
 *          This function retrieves the sizes of the diagnostic structures of a given task
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_FIELD_SIZE_REQ_DATA_Ttag
{
  TLR_UINT32                      ulTsk;              /* task handle */
  TLR_UINT32                      ulInfoNo;           /* index of information field */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_FIELD_SIZE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_FIELD_SIZE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;      /* packet header */
  RCX_TSK_GET_INFO_FIELD_SIZE_REQ_DATA_T  tData;      /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_FIELD_SIZE_REQ_T;

typedef RCX_TSK_GET_INFO_FIELD_SIZE_REQ_T RCX_TSK_GET_INFO_FIELD_SIZE_IDX_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_FIELD_SIZE_CNF_DATA_Ttag
{
  TLR_UINT32                              ulInfoSize; /* info field size in bytes */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_FIELD_SIZE_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_FIELD_SIZE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;      /* packet header */
  RCX_TSK_GET_INFO_FIELD_SIZE_CNF_DATA_T  tData;      /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_FIELD_SIZE_CNF_T;

typedef RCX_TSK_GET_INFO_FIELD_SIZE_CNF_T RCX_TSK_GET_INFO_FIELD_SIZE_IDX_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_GET_INFO_STRUCT_REQ/RCX_TSK_GET_INFO_STRUCT_CNF
 *
 *          This function retrieves the structural information of the
 *          diagnostic structures of a given task
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_STRUCT_REQ_DATA_Ttag
{
  TLR_UINT32                              ulTsk;      /* task handle */
  TLR_UINT32                              ulInfoNo;   /* index of information field */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_STRUCT_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STRUCT_FIELD_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;      /* packet header */
  RCX_TSK_GET_INFO_STRUCT_REQ_DATA_T      tData;      /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_STRUCT_REQ_T;

typedef RCX_TSK_GET_INFO_FIELD_REQ_T RCX_TSK_GET_INFO_STRUCT_IDX_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_STRUCT_CNF_DATA_Ttag
{
  TLR_UINT8                               abData[1]; /* ATTENTION: This is a placeholder for info field data.
                                                                   The packet must be allocated in correct size*/
} __TLR_PACKED_POST RCX_TSK_GET_INFO_STRUCT_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_STRUCT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;      /* packet header */
  RCX_TSK_GET_INFO_FIELD_CNF_DATA_T       tData;      /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_STRUCT_CNF_T;

typedef RCX_TSK_GET_INFO_FIELD_CNF_T RCX_TSK_GET_INFO_STRUCT_IDX_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_GET_INFO_ARRAY_REQ/RCX_TSK_GET_INFO_ARRAY_CNF
 *
 *          This function retrieves the diagnostic structure count and the task handle
 *          by reading the task table in an indexed way
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_ARRAY_REQ_DATA_Ttag
{
  TLR_UINT32                              ulStartIndex; /* start index of requested list */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_ARRAY_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_ARRAY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;      /* packet header */
  RCX_TSK_GET_INFO_ARRAY_REQ_DATA_T       tData;      /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_ARRAY_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_ARRAY_CNF_DATA_ELEMENTtag
{
  TLR_UINT32                              ulTsk;                /* task handle */
  TLR_UINT32                              ulNumberOfInfoFields; /* number of info fields */
  /* the field ulInfoNo of the earlier two requests will have the value range of 0 - (ulNumberOfInfoFields-1) */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_ARRAY_CNF_DATA_ELEMENT;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_ARRAY_CNF_DATA_Ttag
{
  TLR_UINT32                              ulStartIndex;       /* start index */
  TLR_UINT32                              ulNumberOfEntries;  /* number of entries (declaring range of start to start+count-1) */
  TLR_UINT32                              ulCurrentTskCount;  /* current number of tasks */
  RCX_TSK_GET_INFO_ARRAY_CNF_DATA_ELEMENT atInfoData[1];      /* ATTENTION: This is a placeholder for task info data.
                                                                            The packet must be allocated in correct size*/
} __TLR_PACKED_POST RCX_TSK_GET_INFO_ARRAY_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_INFO_ARRAY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;              /* packet header */
  RCX_TSK_GET_INFO_ARRAY_CNF_DATA_T       tData;              /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_INFO_ARRAY_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_START_REQ/RCX_TSK_START_CNF
 *
 *          This packet allows starting a user task
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_START_REQ_DATA_Ttag
{
  TLR_UINT32                              ulTsk;              /* task handle */
} __TLR_PACKED_POST RCX_TSK_START_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_START_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;              /* packet header */
  RCX_TSK_START_REQ_DATA_T                tData;              /* packet data */
} __TLR_PACKED_POST RCX_TSK_START_REQ_T;

typedef RCX_TSK_START_REQ_T RCX_TSK_START_IDX_REQ_T;

/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_START_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_TSK_START_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_STOP_REQ/RCX_TSK_STOP_CNF
 *
 *          This packet allows stopping a user task
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_STOP_REQ_DATA_Ttag
{
  TLR_UINT32                              ulTsk;                /* task handle */
} __TLR_PACKED_POST RCX_TSK_STOP_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_STOP_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                /* packet header */
  RCX_TSK_STOP_REQ_DATA_T                 tData;                /* packet data */
} __TLR_PACKED_POST RCX_TSK_STOP_REQ_T;

typedef RCX_TSK_STOP_REQ_T RCX_TSK_STOP_IDX_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_STOP_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_TSK_STOP_CNF_T;


/******************************************************************************
 * Packet: MID_SYS_QUE_LOG_SET_REQ/MID_SYS_QUE_LOG_SET_CNF
 *
 *          This packet sets a logical queue entry
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_LOG_SET_REQ_DATA_Ttag
{
  TLR_UINT32                              ulLogQue;               /* logical queue id */
} __TLR_PACKED_POST RCX_QUE_LOG_SET_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_QUE_LOG_SET_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_QUE_LOG_SET_REQ_DATA_T              tData;                  /* packet data */
} __TLR_PACKED_POST RCX_QUE_LOG_SET_REQ_T;

/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_LOG_SET_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_QUE_LOG_SET_CNF_T;


/******************************************************************************
 * Packet: MID_SYS_QUE_LOG_CLR_REQ/MID_SYS_QUE_LOG_CLR_CNF
 *
 *          This packet clears a logical queue entry
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_LOG_CLR_REQ_DATA_Ttag
{
  TLR_UINT32                              ulLogQue;               /* logical queue id */
} __TLR_PACKED_POST RCX_QUE_LOG_CLR_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_QUE_LOG_CLR_REQ_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                          /* packet header */
  RCX_QUE_LOG_CLR_REQ_DATA_T      tData;                          /* packet data */
} __TLR_PACKED_POST RCX_QUE_LOG_CLR_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_LOG_CLR_CNF_Ttag
{
  TLR_PACKET_HEADER_T             tHead;                          /* packet data */
} __TLR_PACKED_POST RCX_QUE_LOG_CLR_CNF_T;


/******************************************************************************
 * Packet: RCX_QUE_GET_LOAD_REQ/RCX_QUE_GET_LOAD_CNF
 *
 *          This packet allows retrieving the queue load of a given queue
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_GET_LOAD_REQ_DATA_Ttag
{
  TLR_UINT32                            ulQue[1];   /* ATTENTION: This is a placeholder for number of queues to query.
                                                                  The packet must be allocated in correct size*/
} __TLR_PACKED_POST RCX_QUE_GET_LOAD_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_QUE_GET_LOAD_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_QUE_GET_LOAD_REQ_DATA_T           tData;                  /* packet data */
} __TLR_PACKED_POST RCX_QUE_GET_LOAD_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_QUE_GET_LOAD_CNF_DATA_Ttag
{
  TLR_UINT32                            ulQueLoad[1]; /* ATTENTION: This is a placeholder for queue load entries
                                                                    The packet must be allocated in correct size*/
} __TLR_PACKED_POST RCX_QUE_GET_LOAD_CNF_DATA_T;

#define RCX_QUE_LOAD_INVALID (0xffffffffL)

typedef __TLR_PACKED_PRE struct RCX_QUE_GET_LOAD_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_QUE_GET_LOAD_CNF_DATA_T           tData;                  /* packet data */
} __TLR_PACKED_POST RCX_QUE_GET_LOAD_CNF_T;

/******************************************************************************
 * Packet: RCX_PHYSMEM_READ_REQ/RCX_PHYSMEM_READ_CNF
 *
 *          This packet allows read accesss to physical memory area
 */

#define RCX_PHYSMEM_ACCESSTYPE_8BIT     0
#define RCX_PHYSMEM_ACCESSTYPE_16BIT    1
#define RCX_PHYSMEM_ACCESSTYPE_32BIT    2
#define RCX_PHYSMEM_ACCESSTYPE_TASK     3

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_PHYSMEM_READ_REQ_DATA_Ttag
{
  TLR_UINT32 ulPhysicalAddress;
  TLR_UINT32 ulAccessType;
  TLR_UINT32 ulReadLength;

} __TLR_PACKED_POST RCX_PHYSMEM_READ_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_PHYSMEM_READ_REQ_Ttag
{
  TLR_PACKET_HEADER_T               tHead;
  RCX_PHYSMEM_READ_REQ_DATA_T       tData;
} __TLR_PACKED_POST RCX_PHYSMEM_READ_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_PHYSMEM_READ_CNF_Ttag
{
  TLR_PACKET_HEADER_T               tHead;
} __TLR_PACKED_POST RCX_PHYSMEM_READ_CNF_T;

/******************************************************************************
 * Packet: RCX_PHYSMEM_WRITE_REQ/RCX_PHYSMEM_WRITE_CNF
 *
 *          This packet allows write accesss to physical memory area
 */

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_PHYSMEM_WRITE_REQ_DATA_Ttag
{
  TLR_UINT32 ulPhysicalAddress;
  TLR_UINT32 ulAccessType;
} __TLR_PACKED_POST RCX_PHYSMEM_WRITE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_PHYSMEM_WRITE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                tHead;
  RCX_PHYSMEM_WRITE_REQ_DATA_T       tData;
} __TLR_PACKED_POST RCX_PHYSMEM_WRITE_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_PHYSMEM_WRITE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
} __TLR_PACKED_POST RCX_PHYSMEM_WRITE_CNF_T;

/******************************************************************************
 * Packet: RCX_MODULE_INSTANTIATE_REQ/RCX_MODULE_INSTANTIATE_CNF
 *
 *          This packet allows starting of a firmware module for a given channel
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_MODULE_INSTANTIATE_REQ_DATA_Ttag
{
  TLR_TASK_UID_T                        tModuleUuid;            /* packet header */
  TLR_UINT32                            ulInst;                 /* packet data */
} __TLR_PACKED_POST RCX_MODULE_INSTANTIATE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_MODULE_INSTANTIATE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_MODULE_INSTANTIATE_REQ_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_MODULE_INSTANTIATE_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_MODULE_INSTANTIATE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_MODULE_INSTANTIATE_CNF_T;


/******************************************************************************
 * Packet: RCX_MODULE_CHANNEL_REQ/RCX_MODULE_CHANNEL_CNF
 *
 *          This packet allows starting of a previously downloaded firmware module for a given channel
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_CHANNEL_INSTANTIATE_REQ_DATA_Ttag
{
  TLR_UINT32                            ulChannelNo;            /* channel number */
} __TLR_PACKED_POST RCX_CHANNEL_INSTANTIATE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_CHANNEL_INSTANTIATE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_CHANNEL_INSTANTIATE_REQ_DATA_T    tData;                  /* packet data */
} __TLR_PACKED_POST RCX_CHANNEL_INSTANTIATE_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_CHANNEL_INSTANTIATE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_CHANNEL_INSTANTIATE_CNF_T;


/******************************************************************************
 * Packet: RCX_MODULE_GET_INFO_IDX_REQ/RCX_MODULE_GET_INFO_IDX_CNF
 *
 *          This packet reads out the current available module information from the
 *          module table
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_MODULE_GET_INFO_IDX_REQ_DATA_Ttag
{
  TLR_UINT32                            ulIdx;                  /* module table index */
} __TLR_PACKED_POST RCX_MODULE_GET_INFO_IDX_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_MODULE_GET_INFO_IDX_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_MODULE_GET_INFO_IDX_REQ_DATA_T    tData;                  /* packet data */
} __TLR_PACKED_POST RCX_MODULE_GET_INFO_IDX_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_MODULE_GET_INFO_IDX_CNF_DATA_Ttag
{
  /* index in module table */
  TLR_UINT32                            ulIdx;
  /* module uuid */
  TLR_UUID_T                            tModuleUuid;
  /* init table address */
  TLR_UINT32                            ulInitTableAddress;
  /* code block start address */
  TLR_UINT32                            ulCodeBlockStart;
  /* data block start address */
  TLR_UINT32                            ulDataBlockStart;
  /* bss block start address */
  TLR_UINT32                            ulBssBlockStart;
  /* GOT start address */
  TLR_UINT32                            ulGOT;
  /* PLT start address */
  TLR_UINT32                            ulPLT;
  /* task associated with module */
  TLR_UINT32                            ulNumTasks;
  /* static task table start */
  TLR_UINT32                            ulStaticTaskTableStart;
  /* debug table start */
  TLR_UINT32                            ulDebugTableStart;
  TLR_UINT32                            ulDebugTableSize;
  /* export table start */
  TLR_UINT32                            ulExportTableStart;
  TLR_UINT32                            ulExportTableEntries;
} __TLR_PACKED_POST RCX_MODULE_GET_INFO_IDX_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_MODULE_GET_INFO_IDX_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_MODULE_GET_INFO_IDX_CNF_DATA_T    tData;                  /* packet data */
} __TLR_PACKED_POST RCX_MODULE_GET_INFO_IDX_CNF_T;


/******************************************************************************
 * Packet: RCX_TSK_GET_STATUS_ARRAY_REQ/RCX_TSK_GET_STATUS_ARRAY_CNF
 *
 *          This function reads out the task status' in an indexed way
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STATUS_ARRAY_REQ_DATA_Ttag
{
  TLR_UINT32                            ulStartIndex;           /* start index of requested list */
} __TLR_PACKED_POST RCX_TSK_GET_STATUS_ARRAY_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STATUS_ARRAY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_TSK_GET_STATUS_ARRAY_REQ_DATA_T   tData;                  /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_STATUS_ARRAY_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STATUS_ARRAY_CNF_DATA_Ttag
{
  TLR_UINT32                            ulStartIndex;           /* start index */
  TLR_UINT32                            ulNumberOfEntries;      /* number of entries (declaring range of start to start+count-1) */
  TLR_UINT32                            ulCurrentTskCount;      /* current number of tasks */
  TLR_UINT32                            aulStatusCodes[1];      /* ATTENTION: This is a placeholder for the status codes
                                                                  The packet must be allocated in correct size*/
} __TLR_PACKED_POST RCX_TSK_GET_STATUS_ARRAY_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_TSK_GET_STATUS_ARRAY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_TSK_GET_STATUS_ARRAY_CNF_DATA_T   tData;                  /* packet data */
} __TLR_PACKED_POST RCX_TSK_GET_STATUS_ARRAY_CNF_T;


/******************************************************************************
 * Packet: RCX_DPM_GET_BLOCK_INFO_REQ/RCX_DPM_GET_BLOCK_INFO_CNF
 *
 *          This function retrieves the DPM Channel Block information
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_BLOCK_INFO_REQ_DATA_Ttag
{
  TLR_UINT32                            ulAreaIndex;            /* area index */
  TLR_UINT32                            ulSubblockIndex;        /* subblock index */
} __TLR_PACKED_POST RCX_DPM_GET_BLOCK_INFO_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_BLOCK_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_DPM_GET_BLOCK_INFO_REQ_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_DPM_GET_BLOCK_INFO_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_BLOCK_INFO_CNF_DATA_Ttag
{
  TLR_UINT32                            ulAreaIndex;            /* area index */
  TLR_UINT32                            ulSubblockIndex;        /* number of subblock to request data of */
  TLR_UINT32                            ulType;                 /* Type of subblock */
  TLR_UINT32                            ulOffset;               /* Relative Offset of this Subblock within the Area */
  TLR_UINT32                            ulSize;                 /* Size of the Subblock */
  TLR_UINT16                            usFlags;                /* flags of the subblock */
  TLR_UINT16                            usHandshakeMode;        /* Handshake Mode */
  TLR_UINT16                            usHandshakeBit;         /* Bit position in the Handshake register */
  TLR_UINT16                            usReserved;             /* res */
} __TLR_PACKED_POST RCX_DPM_GET_BLOCK_INFO_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_BLOCK_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_DPM_GET_BLOCK_INFO_CNF_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_DPM_GET_BLOCK_INFO_CNF_T;


/******************************************************************************
 * Packet: RCX_DPM_GET_COMFLAG_INFO_REQ/RCX_DPM_GET_COMFLAG_INFO_CNF
 *
 *          This packet retrieves the currently set COM Flags
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_COMFLAG_INFO_REQ_DATA_Ttag
{
  TLR_UINT32                            ulAreaIndex;            /* area index */
} __TLR_PACKED_POST RCX_DPM_GET_COMFLAG_INFO_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_COMFLAG_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                  /* packet header */
  RCX_DPM_GET_COMFLAG_INFO_REQ_DATA_T   tData;                  /* packet data */
} __TLR_PACKED_POST RCX_DPM_GET_COMFLAG_INFO_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_COMFLAG_INFO_CNF_DATA_Ttag
{
  TLR_UINT32                            ulAreaIndex;              /* area index */
  TLR_UINT32                            ulNetxComFlag;
  TLR_UINT32                            ulHostComFlag;
} __TLR_PACKED_POST RCX_DPM_GET_COMFLAG_INFO_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_COMFLAG_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                    /* packet header */
  RCX_DPM_GET_COMFLAG_INFO_CNF_DATA_T   tData;                    /* packet data */
} __TLR_PACKED_POST RCX_DPM_GET_COMFLAG_INFO_CNF_T;


/******************************************************************************
 * Packet: RCX_LISTS_GET_NUM_ENTRIES_REQ/RCX_LISTS_GET_NUM_ENTRIES_CNF
 *
 *          This function retrieves the number of tasks and queues available on
 *          the system.
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_LISTS_GET_NUM_ENTRIES_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                    /* packet header */
} __TLR_PACKED_POST RCX_LISTS_GET_NUM_ENTRIES_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_LISTS_GET_NUM_ENTRIES_CNF_DATA_Ttag
{
  TLR_UINT32                            ulNumTasks;               /* number of tasks */
  TLR_UINT32                            ulNumQueues;              /* number of queues */
} __TLR_PACKED_POST RCX_LISTS_GET_NUM_ENTRIES_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_LISTS_GET_NUM_ENTRIES_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                    /* packet header */
  RCX_LISTS_GET_NUM_ENTRIES_CNF_DATA_T  tData;                    /* packet data */
} __TLR_PACKED_POST RCX_LISTS_GET_NUM_ENTRIES_CNF_T;


/******************************************************************************
 * Packet: RCX_FIRMWARE_IDENTIFY_REQ/RCX_FIRMWARE_IDENTIFY_CNF
 *
 *          This function identifies the currently running firmware on a given channel
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FIRMWARE_IDENTIFY_REQ_DATA_Ttag
{
  TLR_UINT32                            ulChannelId;              /* channel id */
} __TLR_PACKED_POST RCX_FIRMWARE_IDENTIFY_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FIRMWARE_IDENTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                    /* packet header */
  RCX_FIRMWARE_IDENTIFY_REQ_DATA_T      tData;                    /* packet data */
} __TLR_PACKED_POST RCX_FIRMWARE_IDENTIFY_REQ_T;

#define RCX_FIRMWARE_IDENTIFY_SYSTEM  0xFFFFFFFF

/***** confirmation packet *****/

/*****************************************************************************/
/*! Firmware Identification Structure                                        */
/*****************************************************************************/

typedef __TLR_PACKED_PRE struct RCX_FW_VERSION_Ttag
{
  unsigned short                        usMajor;
  unsigned short                        usMinor;
  unsigned short                        usBuild;
  unsigned short                        usRevision;
} __TLR_PACKED_POST RCX_FW_VERSION_T;

typedef __TLR_PACKED_PRE struct RCX_FW_NAME_Ttag
{
  unsigned char                         bNameLength;
  unsigned char                         abName[63];
} __TLR_PACKED_POST RCX_FW_NAME_T;

typedef __TLR_PACKED_PRE struct RCX_FW_DATE_Ttag
{
  unsigned short                        usYear;
  unsigned char                         bMonth;
  unsigned char                         bDay;
} __TLR_PACKED_POST RCX_FW_DATE_T;

typedef __TLR_PACKED_PRE struct RCX_FW_IDENTIFICATION_Ttag
{
  RCX_FW_VERSION_T                      tFwVersion;               /* !< firmware version */
  RCX_FW_NAME_T                         tFwName;                  /* !< firmware name    */
  RCX_FW_DATE_T                         tFwDate;                  /* !< firmware date    */
} __TLR_PACKED_POST RCX_FW_IDENTIFICATION_T;

typedef __TLR_PACKED_PRE struct RCX_FIRMWARE_IDENTIFY_CNF_DATA_Ttag
{
  RCX_FW_IDENTIFICATION_T               tFirmwareIdentification;  /* firmware identification */
} __TLR_PACKED_POST RCX_FIRMWARE_IDENTIFY_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FIRMWARE_IDENTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                   tHead;                    /* packet header */
  RCX_FIRMWARE_IDENTIFY_CNF_DATA_T      tData;                    /* packet data */
} __TLR_PACKED_POST RCX_FIRMWARE_IDENTIFY_CNF_T;


/******************************************************************************
 * Packet: RCX_HW_IDENTIFY_REQ/RCX_HW_IDENTIFY_CNF
 *
 *          This function retrieves the hardware identification
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_HW_IDENTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_HW_IDENTIFY_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_HW_IDENTIFY_CNF_DATA_Ttag
{
  TLR_UINT32                              ulDeviceNumber;         /* device number */
  TLR_UINT32                              ulSerialNumber;         /* serial number */
  TLR_UINT16                              ausHwOptions[4];        /* hardware options */
  TLR_UINT16                              usDeviceClass;          /* device class */
  TLR_UINT8                               bHwRevision;            /* hardware revision */
  TLR_UINT8                               bHwCompatibility;       /* hardware compatibility */
  TLR_UINT32                              ulBootType;             /* how did the device boot up */
  TLR_UINT32                              ulChipTyp;              /* chip typ */
  TLR_UINT32                              ulChipStep;             /* chip step */
  TLR_UINT32                              ulRomcodeRevision;      /* romcode revision */
} __TLR_PACKED_POST RCX_HW_IDENTIFY_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_HW_IDENTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_HW_IDENTIFY_CNF_DATA_T              tData;                  /* packet data */
} __TLR_PACKED_POST RCX_HW_IDENTIFY_CNF_T;






/**************************************************************************************************
 * file transfer packets
 */

#define RCX_FILE_XFER_INVALID                   0
#define RCX_FILE_XFER_FILESYSTEM                1           /* transfer is related to the Filesystem installed in the Firmware (i.e. 2nd stage bootloader etc.) */
#define RCX_FILE_XFER_FILE RCX_FILE_XFER_FILESYSTEM
#define RCX_FILE_XFER_MODULE                    2           /* will be directly loaded into ram and relocated to be integrated in the running firmware */
#define RCX_FILE_XFER_PARALLEL_FLASH            3           /* flasher interface */
#define RCX_FILE_XFER_SERIAL_FLASH              4           /* flasher interface */
#define RCX_FILE_XFER_LICENSE_CODE              5           /* license code interface */

#define RCX_FILE_CHANNEL_0 (0)
#define RCX_FILE_CHANNEL_1 (1)
#define RCX_FILE_CHANNEL_2 (2)
#define RCX_FILE_CHANNEL_3 (3)
#define RCX_FILE_CHANNEL_4 (4)
#define RCX_FILE_CHANNEL_5 (5)

#define RCX_FILE_SYSTEM (0xFFFFFFFF)


/******************************************************************************
 * Packet: RCX_FILE_UPLOAD_REQ/RCX_FILE_UPLOAD_CNF
 *
 *          This packet starts a file upload
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_REQ_DATA_Ttag
{
  TLR_UINT32                              ulXferType;
  TLR_UINT32                              ulMaxBlockSize;
  TLR_UINT32                              ulChannelNo;            /* 0 = Channel 0, ..., 3 = Channel 3, 0xFFFFFFFF = System, see RCX_FILE_xxxx */
  TLR_UINT16                              usFileNameLength;       /* length of NUL-terminated file name that will follow */
  /* a NUL-terminated file name will follow here */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_UPLOAD_REQ_DATA_T              tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_CNF_DATA_Ttag
{
  TLR_UINT32                              ulMaxBlockSize;         /* maximum block size possible */
  TLR_UINT32                              ulFileLength;           /* file size to transfer */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_UPLOAD_CNF_DATA_T              tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_CNF_T;


/******************************************************************************
 * Packet: RCX_FILE_UPLOAD_DATA_REQ/RCX_FILE_UPLOAD_DATA_CNF
 *
 *          This packet requests the data from a previously successful RCX_FILE_UPLOAD_REQ
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_DATA_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_DATA_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_DATA_CNF_DATA_Ttag
{
  TLR_UINT32                              ulBlockNo;              /* block number starting from 0 in a download sequence */
  TLR_UINT32                              ulChksum;               /* cumulative CRC-32 checksum */
  /* data block follows here */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_DATA_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_DATA_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_UPLOAD_DATA_CNF_DATA_T         tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_DATA_CNF_T;


/******************************************************************************
 * Packet: RCX_FILE_UPLOAD_ABORT_REQ/RCX_FILE_UPLOAD_ABORT_CNF
 *
 *          This packet aborts a currently running file upload
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_ABORT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_ABORT_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_UPLOAD_ABORT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_FILE_UPLOAD_ABORT_CNF_T;



/******************************************************************************
 * Packet: RCX_FORMAT_REQ/RCX_FORMAT_CNF_T
 *
 *          Formats the default volume
 */
#define RCX_FORMAT_REQ_DATA_FLAGS_QUICKFORMAT 0x00000000
#define RCX_FORMAT_REQ_DATA_FLAGS_FULLFORMAT  0x00000001

typedef __TLR_PACKED_PRE struct RCX_FORMAT_REQ_DATA_Ttag
{
  TLR_UINT32  ulFlags;
  TLR_UINT32  ulReserved;
  /* Future version may have the volume name starting here as NUL terminated string,
     Currently unsupported */
} __TLR_PACKED_POST RCX_FORMAT_REQ_DATA_T;

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_FORMAT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FORMAT_REQ_DATA_T                   tData;
} __TLR_PACKED_POST RCX_FORMAT_REQ_T;


/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_FORMAT_CNF_DATA_Ttag
{
  /* Valid if format has failed during a full format with an error during
     erase / verify (ulSta = TLR_E_RCX_FORMAT_ERASE_FAILED or TLR_E_RCX_FORMAT_VERIFY_FAILED */
  TLR_UINT32  ulExtendedErrorInfo; 
  TLR_UINT32  ulErrorOffset;
} __TLR_PACKED_POST RCX_FORMAT_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FORMAT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FORMAT_CNF_DATA_T                   tData;
} __TLR_PACKED_POST RCX_FORMAT_CNF_T;

/******************************************************************************
 * Packet: RCX_FILE_DOWNLOAD_REQ/RCX_FILE_DOWNLOAD_CNF
 *
 *          This packet starts a file download
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_REQ_DATA_Ttag
{
  TLR_UINT32                              ulXferType;             /* transfer type */
  TLR_UINT32                              ulMaxBlockSize;         /* maximum possible download size by requestor */
  TLR_UINT32                              ulFileLength;           /* file size to download */
  TLR_UINT32                              ulChannelNo;            /* 0 = Channel 0, ..., 3 = Channel 3, 0xFFFFFFFF = System, see RCX_FILE_xxxx */
  TLR_UINT16                              usFileNameLength;       /* length of NUL-terminated file name that will follow */
  /* a NUL-terminated file name will follow here */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_DOWNLOAD_REQ_DATA_T            tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_CNF_DATA_Ttag
{
  TLR_UINT32                              ulMaxBlockSize;         /* download block size selected */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_DOWNLOAD_CNF_DATA_T            tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_CNF_T;


/******************************************************************************
 * Packet: RCX_FILE_DOWNLOAD_DATA_REQ/RCX_FILE_DOWNLOAD_DATA_CNF
 *
 *          This packet transfers the file data of a previously successful RCX_DOWNLOAD_REQ
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_DATA_REQ_DATA_Ttag
{
  TLR_UINT32                              ulBlockNo;              /* block number */
  TLR_UINT32                              ulChksum;               /* cumulative CRC-32 checksum */
  /* data block follows here */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_DATA_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_DATA_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_DOWNLOAD_DATA_REQ_DATA_T       tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_DATA_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_DATA_CNF_DATA_Ttag
{
  TLR_UINT32                              ulExpectedCrc32;        /* expected CRC-32 checksum */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_DATA_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_DATA_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_DOWNLOAD_DATA_CNF_DATA_T       tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_DATA_CNF_T;


/******************************************************************************
 * Packet: RCX_FILE_DOWNLOAD_ABORT_REQ/RCX_FILE_DOWNLOAD_ABORT_CNF
 *
 *          This packet aborts a currently running file download
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_ABORT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_ABORT_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_DOWNLOAD_ABORT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_FILE_DOWNLOAD_ABORT_CNF_T;


/******************************************************************************
 * Packet: RCX_FILE_GET_MD5_REQ/RCX_FILE_GET_MD5_CNF
 *
 *          This packet retrieves the MD5 sum of a given file
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_GET_MD5_REQ_DATA_Ttag
{
  TLR_UINT32                              ulChannelNo;            /* 0 = Channel 0, ..., 3 = Channel 3, 0xFFFFFFFF = System, see RCX_FILE_xxxx */
  TLR_UINT16                              usFileNameLength;       /* length of NUL-terminated file name that will follow */
  /* a NUL-terminated file name will follow here */
} __TLR_PACKED_POST RCX_FILE_GET_MD5_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_GET_MD5_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_GET_MD5_REQ_DATA_T             tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_GET_MD5_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_GET_MD5_CNF_DATA_Ttag
{
  TLR_UINT8                               abMD5[16];              /* MD5 checksum */
} __TLR_PACKED_POST RCX_FILE_GET_MD5_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_GET_MD5_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_GET_MD5_CNF_DATA_T             tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_GET_MD5_CNF_T;

/* This packet has the same structure, so we are using a typedef here instead of copy and paste */
typedef RCX_FILE_GET_MD5_REQ_T  RCX_FILE_GET_HEADER_MD5_REQ_T;
typedef RCX_FILE_GET_MD5_CNF_T  RCX_FILE_GET_HEADER_MD5_CNF_T;

/******************************************************************************
 * Packet: RCX_FILE_DELETE_REQ/RCX_FILE_DELETE_CNF
 *
 *          This packet allows deleting a file on the system
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_DELETE_REQ_DATA_Ttag
{
  TLR_UINT32                              ulChannelNo;            /* 0 = Channel 0, ..., 3 = Channel 3, 0xFFFFFFFF = System, see RCX_FILE_xxxx */
  TLR_UINT16                              usFileNameLength;       /* length of NUL-terminated file name that will follow */
  /* a NUL-terminated file name will follow here */
} __TLR_PACKED_POST RCX_FILE_DELETE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_DELETE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_DELETE_REQ_DATA_T              tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_DELETE_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_DELETE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_FILE_DELETE_CNF_T;

/******************************************************************************
 * Packet: RCX_FILE_RENAME_REQ/RCX_FILE_RENAME_CNF
 *
 *          This packet allows renaming a file on the system
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_RENAME_REQ_DATA_Ttag
{
  TLR_UINT32                              ulChannelNo;            /* 0 = Channel 0, ..., 3 = Channel 3, 0xFFFFFFFF = System, see RCX_FILE_xxxx */
  TLR_UINT16                              usOldNameLength;        /* length of NUL-terminated old file name that will follow */
  TLR_UINT16                              usNewNameLength;        /* length of NUL-terminated new file name that will follow */
  /* a NUL-terminated file name will follow here */
} __TLR_PACKED_POST RCX_FILE_RENAME_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_FILE_RENAME_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_FILE_RENAME_REQ_DATA_T              tData;                  /* packet data */
} __TLR_PACKED_POST RCX_FILE_RENAME_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_FILE_RENAME_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_FILE_RENAME_CNF_T;

/******************************************************************************
 * Packet: RCX_DIR_LIST_REQ/RCX_DIR_LIST_CNF
 *
 *          This packet retrieves a Directory Listing of a given directory
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_DIR_LIST_REQ_DATA_Ttag
{
  TLR_UINT32                              ulChannelNo;            /* 0 = Channel 0, ..., 3 = Channel 3, 0xFFFFFFFF = System, see RCX_FILE_xxxx */
  TLR_UINT16                              usDirNameLength;        /* length of NUL-terminated file name that will follow */
  /* a NUL-terminated dir name will follow here */
} __TLR_PACKED_POST RCX_DIR_LIST_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DIR_LIST_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_DIR_LIST_REQ_DATA_T                 tData;
} __TLR_PACKED_POST RCX_DIR_LIST_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_DIR_LIST_CNF_DATA_Ttag
{
  TLR_STR                                 szName[16];             /* file name */
  TLR_UINT32                              ulFileSize;             /* file size */
  TLR_UINT8                               bFileType;              /* file type */
  TLR_UINT8                               bReserved;              /* reserved */
  TLR_UINT16                              bReserved2;             /* reserved */
} __TLR_PACKED_POST RCX_DIR_LIST_CNF_DATA_T;

#define RCX_DIR_LIST_CNF_FILE_TYPE_DIRECTORY      1
#define RCX_DIR_LIST_CNF_FILE_TYPE_FILE           2

typedef __TLR_PACKED_PRE struct RCX_DIR_LIST_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_DIR_LIST_CNF_DATA_T                 tData;                  /* packet data */
} __TLR_PACKED_POST RCX_DIR_LIST_CNF_T;

/******************************************************************************
 * Packet: RCX_VOLUME_GET_ENTRY_REQ/RCX_VOLUME_GET_ENTRY_CNF
 *
 *          This packet retrieves the volume information from the system by index
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_VOLUME_GET_ENTRY_REQ_DATA_Ttag
{
  TLR_UINT32                              ulVolumeIndex;          /* volume entry table index */
} __TLR_PACKED_POST RCX_VOLUME_GET_ENTRY_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_VOLUME_GET_ENTRY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_VOLUME_GET_ENTRY_REQ_DATA_T         tData;                  /* packet data */
} __TLR_PACKED_POST RCX_VOLUME_GET_ENTRY_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_VOLUME_GET_ENTRY_CNF_DATA_Ttag
{
  TLR_UINT32                              ulVolumeCount;          /* count of volumes */
  TLR_STR                                 szName[16];             /* name of currently requested volume entry */
} __TLR_PACKED_POST RCX_VOLUME_GET_ENTRY_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_VOLUME_GET_ENTRY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_VOLUME_GET_ENTRY_CNF_DATA_T         tData;                  /* packet data */
} __TLR_PACKED_POST RCX_VOLUME_GET_ENTRY_CNF_T;


/******************************************************************************
 * Packet: RCX_GET_COMMON_STATE_REQ/RCX_GET_COMMON_STATE_CNF
 *
 *          This packet retrieves the Common State Block of a given Channel in the DPM
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_READ_COMMON_STS_BLOCK_REQ_DATA_Ttag
{
  TLR_UINT32                              ulChannelId;
} __TLR_PACKED_POST RCX_READ_COMMON_STS_BLOCK_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_COMMON_STS_BLOCK_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_READ_COMMON_STS_BLOCK_REQ_DATA_T    tData;
} __TLR_PACKED_POST RCX_READ_COMMON_STS_BLOCK_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_COMMON_STS_BLOCK_CNF_DATA_Ttag
{
  NETX_COMMON_STATUS_BLOCK                tCommonStatus;
} __TLR_PACKED_POST RCX_READ_COMMON_STS_BLOCK_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_COMMON_STS_BLOCK_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_READ_COMMON_STS_BLOCK_CNF_DATA_T    tData;
} __TLR_PACKED_POST RCX_READ_COMMON_STS_BLOCK_CNF_T;


/**************************************
 * legacy definitions of RCX_READ_COMMON_STS_BLOCK_REQ_T packet for compatibility reasons
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_GET_COMMON_STATE_REQ_DATA_Ttag
{
  TLR_UINT32                              ulChannelIndex;         /* channel number */
} __TLR_PACKED_POST RCX_DPM_GET_COMMON_STATE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_COMMON_STATE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_DPM_GET_COMMON_STATE_REQ_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_DPM_GET_COMMON_STATE_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_COMMON_STATE_CNF_DATA_Ttag
{
  TLR_UINT8                               abData[64];             /* common status block data */
} __TLR_PACKED_POST RCX_DPM_GET_COMMON_STATE_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_COMMON_STATE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_DPM_GET_COMMON_STATE_CNF_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_DPM_GET_COMMON_STATE_CNF_T;



/******************************************************************************
 * Packet: RCX_GET_EXTENDED_STATE_REQ/RCX_GET_EXTENDED_STATE_CNF
 *
 *          This packet retrieves the Extended State Block of a given Channel in the DPM
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_EXTENDED_STATE_REQ_DATA_Ttag
{
  TLR_UINT32                              ulOffset;               /* offset to start the reading from the extended status block */
  TLR_UINT32                              ulDataLen;              /* size of block to be read from extended status block */
  TLR_UINT32                              ulChannelIndex;         /* channel number from which to read the extended status block */
} __TLR_PACKED_POST RCX_DPM_GET_EXTENDED_STATE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_EXTENDED_STATE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_DPM_GET_EXTENDED_STATE_REQ_DATA_T   tData;                  /* packet data */
} __TLR_PACKED_POST RCX_DPM_GET_EXTENDED_STATE_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_EXTENDED_STATE_CNF_DATA_Ttag
{
  TLR_UINT32                              ulOffset;               /* offset to start the reading from the extended status block */
  TLR_UINT32                              ulDataLen;              /* size of block to be read from extended status block */
  TLR_UINT8                               abData[432];            /* data block */
} __TLR_PACKED_POST RCX_DPM_GET_EXTENDED_STATE_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_DPM_GET_EXTENDED_STATE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_DPM_GET_EXTENDED_STATE_CNF_DATA_T   tData;                  /* packet data */
} __TLR_PACKED_POST RCX_DPM_GET_EXTENDED_STATE_CNF_T;


/******************************************************************************
 * Packet: RCX_SECURITY_EEPROM_READ_REQ/RCX_SECURITY_EEPROM_READ_CNF
 *
 *          This packet allows reading the security eeprom
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_SECURITY_EEPROM_READ_REQ_DATA_Ttag
{
  TLR_UINT32                              ulZoneId;               /* zone id */
} __TLR_PACKED_POST RCX_SECURITY_EEPROM_READ_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_SECURITY_EEPROM_READ_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_SECURITY_EEPROM_READ_REQ_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_SECURITY_EEPROM_READ_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_SECURITY_EEPROM_READ_CNF_DATA_Ttag
{
  TLR_UINT8                               abZoneData[32];         /* zone data */
} __TLR_PACKED_POST RCX_SECURITY_EEPROM_READ_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_SECURITY_EEPROM_READ_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_SECURITY_EEPROM_READ_CNF_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_SECURITY_EEPROM_READ_CNF_T;

#define RCX_SECURITY_EEPROM_ZONE_0      0
#define RCX_SECURITY_EEPROM_ZONE_1      1
#define RCX_SECURITY_EEPROM_ZONE_2      2
#define RCX_SECURITY_EEPROM_ZONE_3      3


/******************************************************************************
 * Packet: RCX_SECURITY_EEPROM_WRITE_REQ/RCX_SECURITY_EEPROM_WRITE_CNF
 *
 *          This packet allows writing of the user zones in the security eeprom
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_SECURITY_EEPROM_WRITE_REQ_DATA_Ttag
{
  TLR_UINT32                              ulZoneId;               /* zone id , see RCX_SECURITY_EEPROM_ZONE_* defines */
  TLR_UINT8                               abZoneData[32];         /* zone data */
} __TLR_PACKED_POST RCX_SECURITY_EEPROM_WRITE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_SECURITY_EEPROM_WRITE_REQ_Ttag
{
  /* Packet header */
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_SECURITY_EEPROM_WRITE_REQ_DATA_T    tData;                  /* packet data */
} __TLR_PACKED_POST RCX_SECURITY_EEPROM_WRITE_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_SECURITY_EEPROM_WRITE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
} __TLR_PACKED_POST RCX_SECURITY_EEPROM_WRITE_CNF_T;


/******************************************************************************
 * Packet: RCX_GET_LIB_VERSION_INFO_REQ/RCX_GET_LIB_VERSION_INFO_CNF
 *
 *          This packet allows retrieving the version information of libraries integrated
 *          into the firmware
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_GET_LIB_VERSION_INFO_REQ_DATA_Ttag
{
  TLR_UINT32                              ulVersionIndex;         /* version table index */
} __TLR_PACKED_POST RCX_GET_LIB_VERSION_INFO_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_LIB_VERSION_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_GET_LIB_VERSION_INFO_REQ_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_GET_LIB_VERSION_INFO_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_LIB_VERSION_Ttag
{
  unsigned short                        usMajor;
  unsigned short                        usMinor;
  unsigned short                        usBuild;
  unsigned short                        usRevision;
} __TLR_PACKED_POST RCX_LIB_VERSION_T;

typedef __TLR_PACKED_PRE struct RCX_LIB_NAME_Ttag
{
  unsigned char                         bNameLength;
  unsigned char                         abName[63];
} __TLR_PACKED_POST RCX_LIB_NAME_T;

typedef __TLR_PACKED_PRE struct RCX_LIB_DATE_Ttag
{
  unsigned short                        usYear;
  unsigned char                         bMonth;
  unsigned char                         bDay;
} __TLR_PACKED_POST RCX_LIB_DATE_T;

typedef __TLR_PACKED_PRE struct RCX_GET_LIB_VERSION_INFO_CNF_DATA_Ttag
{
  RCX_LIB_VERSION_T                       tLibVersion;            /* !< library version */
  RCX_LIB_NAME_T                          tLibName;               /* !< library name    */
  RCX_LIB_DATE_T                          tLibDate;               /* !< library date    */
  TLR_UINT32                              ulType;                 /* type of library */
} __TLR_PACKED_POST RCX_GET_LIB_VERSION_INFO_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_LIB_VERSION_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;                  /* packet header */
  RCX_GET_LIB_VERSION_INFO_CNF_DATA_T     tData;                  /* packet data */
} __TLR_PACKED_POST RCX_GET_LIB_VERSION_INFO_CNF_T;



/******************************************************************************
 * Packet: RCX_GET_WATCHDOG_TIME_REQ/RCX_GET_WATCHDOG_TIME_CNF
 *
 *          This packet allows retrieving the actual watchdog time
 */

/***** request packet *****/

typedef TLR_EMPTY_PACKET_T RCX_GET_WATCHDOG_TIME_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_GET_WATCHDOG_TIME_CNF_DATA_Ttag
{
  /** watchdog time in us */
  TLR_UINT32 ulWdgTime;
} __TLR_PACKED_POST RCX_GET_WATCHDOG_TIME_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_WATCHDOG_TIME_CNF_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_GET_WATCHDOG_TIME_CNF_DATA_T  tData;
} __TLR_PACKED_POST RCX_GET_WATCHDOG_TIME_CNF_T;

/******************************************************************************
 * Packet: RCX_SET_WATCHDOG_TIME_REQ/RCX_SET_WATCHDOG_TIME_CNF
 *
 *          This packet allows setting the actual watchdog time
 */

/***** request packet *****/
typedef __TLR_PACKED_PRE  struct RCX_SET_WATCHDOG_TIME_REQ_DATA_Ttag
{
  /** watchdog time in us */
  TLR_UINT32 ulWdgTime;
} __TLR_PACKED_POST RCX_SET_WATCHDOG_TIME_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_SET_WATCHDOG_TIME_REQ_Ttag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_SET_WATCHDOG_TIME_REQ_DATA_T  tData;
} __TLR_PACKED_POST RCX_SET_WATCHDOG_TIME_REQ_T;

/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T RCX_SET_WATCHDOG_TIME_CNF_T;

/******************************************************************************
 * Packet: RCX_PACKET_GET_SLAVE_HANDLE_REQ/RCX_PACKET_GET_SLAVE_HANDLE_CNF
 *
 *          This packet allows retrieving diagnostic information of the
 *          connected devices
 */

/***** request packet *****/
typedef __TLR_PACKED_PRE  struct RCX_PACKET_GET_SLAVE_HANDLE_REQ_DATA_Tag
{
  TLR_UINT32 ulParam;
} __TLR_PACKED_POST  RCX_PACKET_GET_SLAVE_HANDLE_REQ_DATA_T;

#define RCX_LIST_CONF_SLAVES                0x00000001
#define RCX_LIST_ACTV_SLAVES                0x00000002
#define RCX_LIST_FAULTED_SLAVES             0x00000003

typedef __TLR_PACKED_PRE struct RCX_PACKET_GET_SLAVE_HANDLE_REQ_Tag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_PACKET_GET_SLAVE_HANDLE_REQ_DATA_T  tData;
} __TLR_PACKED_POST RCX_PACKET_GET_SLAVE_HANDLE_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE  struct RCX_PACKET_GET_SLAVE_HANDLE_CNF_DATA_Tag
{
  TLR_UINT32 ulParam;
  TLR_UINT32 aulHandle[1];
} __TLR_PACKED_POST  RCX_PACKET_GET_SLAVE_HANDLE_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_PACKET_GET_SLAVE_HANDLE_CNF_Tag
{
  TLR_PACKET_HEADER_T                     tHead;
  RCX_PACKET_GET_SLAVE_HANDLE_CNF_DATA_T  tData;
} __TLR_PACKED_POST RCX_PACKET_GET_SLAVE_HANDLE_CNF_T;

/******************************************************************************
 * Packet: RCX_PACKET_GET_SLAVE_CONN_INFO_REQ/RCX_PACKET_GET_SLAVE_CONN_INFO_CNF
 *
 *          This packet allows retrieving detail information of a slave
 */

/***** request packet *****/

typedef __TLR_PACKED_PRE  struct RCX_PACKET_GET_SLAVE_CONN_INFO_REQ_DATA_Tag
{
  TLR_UINT32 ulHandle;
} __TLR_PACKED_POST  RCX_PACKET_GET_SLAVE_CONN_INFO_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_PACKET_GET_SLAVE_CONN_INFO_REQ_Tag
{
  TLR_PACKET_HEADER_T                        tHead;
  RCX_PACKET_GET_SLAVE_CONN_INFO_REQ_DATA_T  tData;
} __TLR_PACKED_POST RCX_PACKET_GET_SLAVE_CONN_INFO_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE  struct RCX_PACKET_GET_SLAVE_CONN_INFO_CNF_DATA_Tag
{
  TLR_UINT32 ulHandle;
  TLR_UINT32 ulStructID;
  /*
    Feldbus specific structure
  */
} __TLR_PACKED_POST RCX_PACKET_GET_SLAVE_CONN_INFO_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_PACKET_GET_SLAVE_CONN_INFO_CNF_Tag
{
  TLR_PACKET_HEADER_T                        tHead;
  RCX_PACKET_GET_SLAVE_CONN_INFO_CNF_DATA_T  tData;
} __TLR_PACKED_POST  RCX_PACKET_GET_SLAVE_CONN_INFO_CNF_T;


/******************************************************************************
 * Packet: RCX_GET_DPM_IO_INFO__REQ/RCX_GET_DPM_IO_INFO__CNF
 *
 *          This packet allows retrieving the used I/O length
 */

/***** request packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_GET_DPM_IO_INFO_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_DPM_IO_BLOCK_INFO_Ttag
{
  TLR_UINT32    ulSubblockIndex;        /* number of sub block  */
  TLR_UINT32    ulType;                 /* type of sub block    */
  TLR_UINT16    usFlags;                  /* flags of the sub block */
  TLR_UINT16    usReserved;           /* reserved */
  TLR_UINT32    ulOffset;               /* start offset of the IO data  */
  TLR_UINT32    ulLength;               /* length of used IO data   */
} __TLR_PACKED_POST RCX_DPM_IO_BLOCK_INFO_T;

typedef __TLR_PACKED_PRE struct RCX_GET_DPM_IO_INFO_CNF_DATA_Ttag
{
  TLR_UINT32    ulNumIOBlockInfo;                   /* Number of IO Block Info  */
  RCX_DPM_IO_BLOCK_INFO_T atIOBlockInfo[2]; /* Array of I/O Block information */
} __TLR_PACKED_POST RCX_GET_DPM_IO_INFO_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_DPM_IO_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T   tHead;  /* packer header    */
  RCX_GET_DPM_IO_INFO_CNF_DATA_T    tData;  /* packet header    */
} __TLR_PACKED_POST RCX_GET_DPM_IO_INFO_CNF_T;



/******************************************************************************
 * Packet: RCX_REGISTER_APP_REQ/RCX_REGISTER_APP_CNF
 *
 *          This packet allows to register a application
 */

/***** request packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_REGISTER_APP_REQ_T;

/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_REGISTER_APP_CNF_T;


/******************************************************************************
 * Packet: RCX_UNREGISTER_APP_REQ/RCX_UNREGISTER_APP_CNF
 *
 *          This packet allows to unregister a application
 */

/***** request packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_UNREGISTER_APP_REQ_T;

/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_UNREGISTER_APP_CNF_T;


/******************************************************************************
 * Packet: RCX_DELETE_CONFIG_REQ/RCX_DELETE_CONFIG_CNF
 *
 *          This packet allows to delete the actual configuration
 */

/***** request packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_DELETE_CONFIG_REQ_T;

/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_DELETE_CONFIG_CNF_T;




/******************************************************************************
 * Packet: RCX_START_STOP_COMM_REQ/RCX_START_STOP_COMM_CNF
 *
 *          This packet allows start and stop bus communication
 */

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_START_STOP_COMM_REQ_DATA_Ttag
{
  TLR_UINT32    ulParam;                    /* Boolean to set Start(1) or Stop(2) Communication */
} __TLR_PACKED_POST RCX_START_STOP_COMM_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_START_STOP_COMM_REQ_Ttag
{
  TLR_PACKET_HEADER_T   tHead;  /* packer header    */
  RCX_START_STOP_COMM_REQ_DATA_T    tData;  /* packet header    */
} __TLR_PACKED_POST RCX_START_STOP_COMM_REQ_T;


/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_START_STOP_COMM_CNF_T;

/******************************************************************************
 * Packet: RCX_LOCK_UNLOCK_CONFIG_REQ/RCX_LOCK_UNLOCK_CONFIG_CNF
 *
 *          This packet allows lock and unlock the configuration settings
 */

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_LOCK_UNLOCK_CONFIG_REQ_DATA_Ttag
{
  TLR_UINT32    ulParam;                    /* Boolean to set Lock(1) or Unlock(2) config */
} __TLR_PACKED_POST RCX_LOCK_UNLOCK_CONFIG_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_LOCK_UNLOCK_CONFIG_REQ_Ttag
{
  TLR_PACKET_HEADER_T   tHead;  /* packer header    */
  RCX_LOCK_UNLOCK_CONFIG_REQ_DATA_T tData;  /* packet header    */
} __TLR_PACKED_POST RCX_LOCK_UNLOCK_CONFIG_REQ_T;


/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_LOCK_UNLOCK_CONFIG_CNF_T;

/******************************************************************************
 * Packet: RCX_CHANNEL_INIT_REQ/RCX_CHANNEL_INIT_CNF
 *
 *          This packet allows retrieving the used I/O length
 */

/***** request packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_CHANNEL_INIT_REQ_T;

/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T          RCX_CHANNEL_INIT_CNF_T;


/******************************************************************************
 * Packet: RCX_VERIFY_DATABASE_REQ /RCX_VERIFY_DATABASE_CNF
 *
 *          This packet adds new slaves to the database
 */
 /***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_VERIFY_DATABASE_REQ_Ttag
{
  TLR_PACKET_HEADER_T tHead;                    /* packet header */
} __TLR_PACKED_POST RCX_VERIFY_DATABASE_REQ_T;

#define RCX_VERIFY_DATABASE_REQ_SIZE 0


/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_VERIFY_SLAVE_DATABASE_LIST_Ttag
{
    TLR_UINT32  ulLen;
    TLR_UINT8  abData[16];
} __TLR_PACKED_POST RCX_VERIFY_SLAVE_DATABASE_LIST_T;

typedef __TLR_PACKED_PRE struct RCX_VERIFY_MASTER_DATABASE_Ttag
{
  TLR_UINT32  ulMasterSettings;   /* field bus independent changes */
  TLR_UINT32  ulMasterStatus;     /* field bus specific status */
  TLR_UINT32  ulReserved[2];
} __TLR_PACKED_POST RCX_VERIFY_MASTER_DATABASE_T;


#define RCX_VERIFY_SLAVE_DATABASE_LIST_SIZE sizeof(RCX_VERIFY_SLAVE_DATABASE_LIST_T)
#define RCX_CIR_MST_SET_STARTUP       0x00000001
#define RCX_CIR_MST_SET_WATCHDOG      0x00000002
#define RCX_CIR_MST_SET_STATUSOFFSET  0x00000004
#define RCX_CIR_MST_SET_BUSPARAMETER  0x00000008

typedef __TLR_PACKED_PRE struct RCX_VERIFY_DATABASE_CNF_DATA_Ttag
{
    RCX_VERIFY_SLAVE_DATABASE_LIST_T                tNewSlaves;
    RCX_VERIFY_SLAVE_DATABASE_LIST_T                tDeactivatedSlaves;
    RCX_VERIFY_SLAVE_DATABASE_LIST_T                tChangedSlaves;
    RCX_VERIFY_SLAVE_DATABASE_LIST_T                tUnchangedSlaves;
    RCX_VERIFY_SLAVE_DATABASE_LIST_T                tImpossibleSlaveChanges;
    RCX_VERIFY_MASTER_DATABASE_T                    tMasterChanges;
} __TLR_PACKED_POST RCX_VERIFY_DATABASE_CNF_DATA_T;

#define RCX_VERIFY_DATABASE_CNF_DATA_SIZE sizeof(RCX_VERIFY_DATABASE_CNF_DATA_T)

typedef __TLR_PACKED_PRE struct RCX_VERIFY_DATABASE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                       tHead;    /* packet header  */
  RCX_VERIFY_DATABASE_CNF_DATA_T            tData;    /* packet data    */
} __TLR_PACKED_POST RCX_VERIFY_DATABASE_CNF_T;

#define RCX_VERFIY_DATABASE_CNF_PACKET_SIZE sizeof(RCX_VERIFY_DATABASE_CNF_T)



/******************************************************************************
 * Packet: RCX_CHANNEL_ACTIVATE_REQ/RCX_CHANNEL_NEW_DATABASE_CNF
 *
 *          This packet activates the new configured slaves
  */
 /***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_ACTIVATE_DATABASE_REQ_Ttag
{
  TLR_PACKET_HEADER_T tHead;                    /* packet header */
} __TLR_PACKED_POST RCX_ACTIVATE_DATABASE_REQ_T;



 /***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_ACTIVATE_DATABASE_CNF_DATA_Ttag
{
  TLR_UINT8                 abSlvSt[16];                    /* State of the slaves after configuration */
} __TLR_PACKED_POST RCX_ACTIVATE_DATABASE_CNF_DATA_T;

#define RCX_ACTIVATE_DATABASE_CNF_DATA_SIZE sizeof(RCX_ACTIVATE_DATABASE_CNF_DATA_T)


typedef __TLR_PACKED_PRE struct RCX_ACTIVATE_DATABASE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                       tHead;                   /* packet header */
  RCX_ACTIVATE_DATABASE_CNF_DATA_T          tData;
} __TLR_PACKED_POST RCX_ACTIVATE_DATABASE_CNF_T;

#define RCX_ACTIVATE_DATABASE_CNF_PACKET_SIZE sizeof(RCX_ACTIVATE_DATABASE_CNF_T)



/******************************************************************************
 * Packet: RCX_HW_LICENSE_INFO_REQ/RCX_HW_LICENSE_INFO_CNF
 *
 *          This packet allows retrieving the license information from the security memory
 */

/* request packet */
typedef __TLR_PACKED_PRE struct RCX_HW_LICENSE_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T               tHead;
} __TLR_PACKED_POST RCX_HW_LICENSE_INFO_REQ_T;

/* confirmation packet */
typedef __TLR_PACKED_PRE struct RCX_HW_LICENSE_INFO_CNF_DATA_Ttag
{
  TLR_UINT32                        ulLicenseFlags1;
  TLR_UINT32                        ulLicenseFlags2;
  TLR_UINT16                        usNetxLicenseID;
  TLR_UINT16                        usNetxLicenseFlags;
} __TLR_PACKED_POST RCX_HW_LICENSE_INFO_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_HW_LICENSE_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T               tHead;
  RCX_HW_LICENSE_INFO_CNF_DATA_T    tData;
} __TLR_PACKED_POST RCX_HW_LICENSE_INFO_CNF_T;

/******************************************************************************
 * Packet: RCX_HW_HARDWARE_INFO_REQ/RCX_HW_HARDWARE_INFO_CNF
 *
 *          This packet allows retrieving hardware information
 */

/* request packet */
typedef __TLR_PACKED_PRE struct RCX_HW_HARDWARE_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T               tHead;
} __TLR_PACKED_POST RCX_HW_HARDWARE_INFO_REQ_T;

/* confirmation packet */
typedef __TLR_PACKED_PRE struct RCX_HW_HARDWARE_INFO_CNF_DATA_Ttag
{
  /* device number */
  TLR_UINT32                        ulDeviceNumber;
  /* serial number */
  TLR_UINT32                        ulSerialNumber;
  /* hardware options */
  TLR_UINT16                        ausHwOptions[4];
  /* manufacturer code */
  TLR_UINT16                        usManufacturer;
  /* production date */
  TLR_UINT16                        usProductionDate;
  /* license info */
  TLR_UINT32                        ulLicenseFlags1;
  TLR_UINT32                        ulLicenseFlags2;
  TLR_UINT16                        usNetxLicenseID;
  TLR_UINT16                        usNetxLicenseFlags;
  /* device class */
  TLR_UINT16                        usDeviceClass;
  /* hardware revision */
  TLR_UINT8                         bHwRevision;
  /* hardware compatibility */
  TLR_UINT8                         bHwCompatibility;
  /* hardware features 1 */
  TLR_UINT32                        ulHardwareFeatures1;
  /* hardware features 2 */
  TLR_UINT32                        ulHardwareFeatures2;
  /* boot option */
  TLR_UINT8                         bBootOption;
  /* reserved */
  TLR_UINT8                         bReserved[11];
} __TLR_PACKED_POST RCX_HW_HARDWARE_INFO_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_HW_HARDWARE_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T               tHead;
  RCX_HW_HARDWARE_INFO_CNF_DATA_T   tData;
} __TLR_PACKED_POST RCX_HW_HARDWARE_INFO_CNF_T;

/*****************************************************************************
 * RCX_BACKUP_REQ/RCX_BACKUP_CNF
*****************************************************************************/

/*****************************************************************************
 *  This packet initiates a backup of the SYSVOLUME onto the given device
*****************************************************************************/
typedef __TLR_PACKED_PRE struct RCX_BACKUP_REQ_DATA_Ttag
{
  TLR_CHAR    szBackupPoint[1]; /*!< NULL terminated string containing the path
                                                                              to backup to. This is just a placeholder, and the strucure needs to
                                                                              be extended by the number of characters of the backup point,
                                                                              e.g.  "SDMMC:/backup" */
} __TLR_PACKED_POST RCX_BACKUP_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_BACKUP_REQ_Ttag
{
  TLR_PACKET_HEADER_T   tHead; /* packet header */
  RCX_BACKUP_REQ_DATA_T tData; /* packet data */
} __TLR_PACKED_POST RCX_BACKUP_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_BACKUP_CNF_Ttag
{
  TLR_PACKET_HEADER_T tHead; /* packet header */
} __TLR_PACKED_POST RCX_BACKUP_CNF_T;

/*****************************************************************************
 * RCX_RESTORE_REQ/RCX_RESTORE_CNF
*****************************************************************************/

/*****************************************************************************
 *  This packet initiates a restore of the SYSVOLUME from the given device / path
*****************************************************************************/
typedef __TLR_PACKED_PRE struct RCX_RESTORE_REQ_DATA_Ttag
{
  TLR_CHAR    szRestorePoint[1]; /*!< NULL terminated string containing the path
                                                                                 to restore from. This is just a placeholder, and the strucure needs to
                                                                                 be extended by the number of characters of the restore point
                                                                                 e.g.  "SDMMC:/backup" */
} __TLR_PACKED_POST RCX_RESTORE_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_RESTORE_REQ_Ttag
{
  TLR_PACKET_HEADER_T    tHead; /* packet header */
  RCX_RESTORE_REQ_DATA_T tData; /* packet data */
} __TLR_PACKED_POST RCX_RESTORE_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_RESTORE_CNF_Ttag
{
  TLR_PACKET_HEADER_T tHead; /* packet header */
} __TLR_PACKED_POST RCX_RESTORE_CNF_T;


/******************************************************************************
 * RCX_SYSTEM_INFORMATION_BLOCK_REQ/RCX_SYSTEM_INFORMATION_BLOCK_CNF
 ******************************************************************************/

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_SYS_INFO_BLOCK_REQ_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
} __TLR_PACKED_POST RCX_READ_SYS_INFO_BLOCK_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_SYS_INFO_BLOCK_CNF_DATA_Ttag
{
  NETX_SYSTEM_INFO_BLOCK                      tSystemInfo;
} __TLR_PACKED_POST RCX_READ_SYS_INFO_BLOCK_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_SYS_INFO_BLOCK_CNF_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
  RCX_READ_SYS_INFO_BLOCK_CNF_DATA_T          tData;
} __TLR_PACKED_POST RCX_READ_SYS_INFO_BLOCK_CNF_T;


/******************************************************************************
 * RCX_CHANNEL_INFORMATION_BLOCK_REQ/RCX_CHANNEL_INFORMATION_BLOCK_CNF
 ******************************************************************************/

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_CHNL_INFO_BLOCK_REQ_DATA_Ttag
{
  TLR_UINT32                                  ulChannelId;
} __TLR_PACKED_POST RCX_READ_CHNL_INFO_BLOCK_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_CHNL_INFO_BLOCK_REQ_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
  RCX_READ_CHNL_INFO_BLOCK_REQ_DATA_T         tData;
} __TLR_PACKED_POST RCX_READ_CHNL_INFO_BLOCK_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_CHNL_INFO_BLOCK_CNF_DATA_Ttag
{
  NETX_CHANNEL_INFO_BLOCK                     tChannelInfo;
} RCX_READ_CHNL_INFO_BLOCK_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_CHNL_INFO_BLOCK_CNF_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
  RCX_READ_CHNL_INFO_BLOCK_CNF_DATA_T         tData;
} __TLR_PACKED_POST RCX_READ_CHNL_INFO_BLOCK_CNF_T;


/******************************************************************************
 * RCX_SYSTEM_CONTROL_BLOCK_REQ/RCX_SYSTEM_CONTROL_BLOCK_CNF
 ******************************************************************************/

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_SYS_CNTRL_BLOCK_REQ_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
} __TLR_PACKED_POST RCX_READ_SYS_CNTRL_BLOCK_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_SYS_CNTRL_BLOCK_CNF_DATA_Ttag
{
  NETX_SYSTEM_CONTROL_BLOCK                   tSystemControl;
} __TLR_PACKED_POST RCX_READ_SYS_CNTRL_BLOCK_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_SYS_CNTRL_BLOCK_CNF_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
  RCX_READ_SYS_CNTRL_BLOCK_CNF_DATA_T         tData;
} __TLR_PACKED_POST RCX_READ_SYS_CNTRL_BLOCK_CNF_T;

/******************************************************************************
 * RCX_SYSTEM_STATUS_BLOCK_REQ/RCX_SYSTEM_STATUS_BLOCK_CNF
 ******************************************************************************/

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_SYS_STATUS_BLOCK_REQ_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
} __TLR_PACKED_POST RCX_READ_SYS_STATUS_BLOCK_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_SYS_STATUS_BLOCK_CNF_DATA_Ttag
{
  NETX_SYSTEM_STATUS_BLOCK                    tSystemState;
} __TLR_PACKED_POST RCX_READ_SYS_STATUS_BLOCK_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_SYS_STATUS_BLOCK_CNF_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
  RCX_READ_SYS_STATUS_BLOCK_CNF_DATA_T        tData;
} __TLR_PACKED_POST RCX_READ_SYS_STATUS_BLOCK_CNF_T;


/******************************************************************************
 * RCX_CONTROL_BLOCK_REQ/RCX_CONTROL_BLOCK_CNF
 ******************************************************************************/

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_COMM_CNTRL_BLOCK_REQ_DATA_Ttag
{
  TLR_UINT32                                  ulChannelId;
} __TLR_PACKED_POST RCX_READ_COMM_CNTRL_BLOCK_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_COMM_CNTRL_BLOCK_REQ_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
  RCX_READ_COMM_CNTRL_BLOCK_REQ_DATA_T        tData;
} __TLR_PACKED_POST RCX_READ_COMM_CNTRL_BLOCK_REQ_T;

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_READ_COMM_CNTRL_BLOCK_CNF_DATA_Ttag
{
  NETX_CONTROL_BLOCK                          tControl;
} __TLR_PACKED_POST RCX_READ_COMM_CNTRL_BLOCK_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_READ_COMM_CNTRL_BLOCK_CNF_Ttag
{
  TLR_PACKET_HEADER_T                         tHead;
  RCX_READ_COMM_CNTRL_BLOCK_CNF_DATA_T        tData;
} __TLR_PACKED_POST RCX_READ_COMM_CNTRL_BLOCK_CNF_T;


/******************************************************************************
 * RCX_BUSSCAN_REQ
 ******************************************************************************/
#define RCX_BUSSCAN_CMD_START    0x01
#define RCX_BUSSCAN_CMD_STATUS   0x02
#define RCX_BUSSCAN_CMD_ABORT    0x03

/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_BUSSCAN_REQ_DATA_Ttag
{
  TLR_UINT32 ulAction;
} __TLR_PACKED_POST RCX_BUSSCAN_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_BUSSCAN_REQ_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  RCX_BUSSCAN_REQ_DATA_T tData;
} __TLR_PACKED_POST RCX_BUSSCAN_REQ_T;

#define RCX_BUSSCAN_REQ_SIZE     (sizeof(RCX_BUSSCAN_REQ_DATA_T))

/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_BUSSCAN_CNF_DATA_Ttag
{
  TLR_UINT32 ulMaxProgress;
  TLR_UINT32 ulActProgress;
  TLR_UINT8  abDeviceList[4];
} __TLR_PACKED_POST RCX_BUSSCAN_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_BUSSCAN_CNF_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  RCX_BUSSCAN_CNF_DATA_T tData;
} __TLR_PACKED_POST RCX_BUSSCAN_CNF_T;

#define RCX_BUSSCAN_CNF_SIZE     (sizeof(RCX_BUSSCAN_CNF_DATA_T) - 4)


/******************************************************************************
 * RCX_GET_DEVICE_INFO_REQ
 ******************************************************************************/
/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_GET_DEVICE_INFO_REQ_DATA_Ttag
{
  TLR_UINT32 ulDeviceIdx;
} __TLR_PACKED_POST RCX_GET_DEVICE_INFO_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_DEVICE_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T            tHead;
  RCX_GET_DEVICE_INFO_REQ_DATA_T tData;
} __TLR_PACKED_POST RCX_GET_DEVICE_INFO_REQ_T;

#define RCX_GET_DEVICE_INFO_REQ_SIZE     (sizeof(RCX_GET_DEVICE_INFO_REQ_DATA_T))

/***** confirmation packet *****/
typedef __TLR_PACKED_PRE struct RCX_GET_DEVICE_INFO_CNF_DATA_Ttag
{
  TLR_UINT32 ulDeviceIdx;
  TLR_UINT32 ulStructId;
  /* TLR_UINT8  tStruct; Fieldbus specific structure */
} __TLR_PACKED_POST RCX_GET_DEVICE_INFO_CNF_DATA_T;

typedef struct RCX_GET_DEVICE_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T            tHead;
  RCX_GET_DEVICE_INFO_CNF_DATA_T tData;
} __TLR_PACKED_POST RCX_GET_DEVICE_INFO_CNF_T;

#define RCX_GET_DEVICE_INFO_CNF_SIZE     (sizeof(RCX_GET_DEVICE_INFO_CNF_DATA_T))


/******************************************************************************
 * RCX_SET_HANDSHAKE_CONFIG_REQ
 ******************************************************************************/
/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_SET_HANDSHAKE_CONFIG_REQ_DATA_Ttag
{
  /* Input process data handshake mode */
  TLR_UINT8                           bPDInHskMode;
  /* Input process data trigger source. Currently unused, set to zero. */
  TLR_UINT8                           bPDInSource;
  /* Threshold for input process data handshake handling errors */
  TLR_UINT16                          usPDInErrorTh;

  /* Output process data handshake mode */
  TLR_UINT8                           bPDOutHskMode;
  /* Output process data trigger source. Currently unused, set to zero. */
  TLR_UINT8                           bPDOutSource;
  /* Threshold for output process data handshake handling errors */
  TLR_UINT16                          usPDOutErrorTh;

  /* Synchronization handshake mode */
  TLR_UINT8                           bSyncHskMode;
  /* Synchronization source */
  TLR_UINT8                           bSyncSource;
  /* Threshold for synchronization handshake handling errors */
  TLR_UINT16                          usSyncErrorTh;

  /* Reserved for future use. Set to zero. */
  TLR_UINT32                          aulReserved[2];
} __TLR_PACKED_POST RCX_SET_HANDSHAKE_CONFIG_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_SET_HANDSHAKE_CONFIG_REQ_Ttag
{
  TLR_PACKET_HEADER_T                 tHead;
  RCX_SET_HANDSHAKE_CONFIG_REQ_DATA_T tData;
} __TLR_PACKED_POST RCX_SET_HANDSHAKE_CONFIG_REQ_T;

#define RCX_SET_HANDSHAKE_CONFIG_REQ_SIZE     (sizeof(RCX_SET_HANDSHAKE_CONFIG_REQ_DATA_T))

/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T  RCX_SET_HANDSHAKE_CONFIG_CNF_T;

#define RCX_SET_HANDSHAKE_CONFIG_CNF_SIZE     (0)


/******************************************************************************
 * RCX_MALLINFO_REQ
 ******************************************************************************/
/***** request packet *****/
typedef __TLR_PACKED_PRE struct RCX_MALLINFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T tHead;
} __TLR_PACKED_POST RCX_MALLINFO_REQ_T;


/***** confirmation packet *****/

typedef __TLR_PACKED_PRE struct RCX_MALLINFO_CNF_DATA_Ttag
{
  /* values reported by mallinfo() call, see malloc documentation for further description */
  TLR_INT32  arena;       /* total space allocated from system */
  TLR_INT32  ordblks;     /* number of non-inuse chunks */
  TLR_INT32  hblks;       /* number of mmapped regions */
  TLR_INT32  hblkhd;      /* total space in mmapped regions */
  TLR_INT32  uordblks;    /* total allocated space */
  TLR_INT32  fordblks;    /* total non-inuse space */
  TLR_INT32  keepcost;    /* top-most, releasable (via malloc_trim) space */
  TLR_UINT32 ulTotalHeap; /* Total Heap area size in bytes */
} __TLR_PACKED_POST RCX_MALLINFO_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_MALLINFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  RCX_MALLINFO_CNF_DATA_T tData;
} __TLR_PACKED_POST RCX_MALLINFO_CNF_T;


/******************************************************************************
 * RCX_SET_FW_PARAMETER_REQ
 ******************************************************************************/

/***** PID defines    *****/

#define PID_STATION_ADDRESS     0x30000001 /* Station address of device*/
#define PID_BAUDRATE            0x30000002 /* Baudrate of device */
#define PID_PN_NAME_OF_STATION  0x30015001 /* PROFINET Name of Station String */


/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_SET_FW_PARAMETER_REQ_DATA_Ttag
{
  TLR_UINT32 ulParameterID;
  TLR_UINT32 ulParameterLen;
  TLR_UINT8  abParameter[4];  /* padded to DWORD boundary*/
} __TLR_PACKED_POST RCX_SET_FW_PARAMETER_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_SET_FW_PARAMETER_REQ_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  RCX_SET_FW_PARAMETER_REQ_DATA_T tData;
} __TLR_PACKED_POST RCX_SET_FW_PARAMETER_REQ_T;

#define RCX_SET_FW_PARAMETER_REQ_SIZE (sizeof(RCX_SET_FW_PARAMETER_REQ_DATA_T) - 4)


/***** confirmation packet *****/
typedef TLR_EMPTY_PACKET_T  RCX_SET_FW_PARAMETER_CNF_T;

#define RCX_SET_FW_PARAMETER_CNF_SIZE     (0)


/******************************************************************************
 * RCX_GET_FW_PARAMETER_REQ
 ******************************************************************************/

/***** request packet *****/

typedef __TLR_PACKED_PRE struct RCX_GET_FW_PARAMETER_REQ_DATA_Ttag
{
  TLR_UINT32 ulParameterID;
} __TLR_PACKED_POST RCX_GET_FW_PARAMETER_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_GET_FW_PARAMETER_REQ_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  RCX_GET_FW_PARAMETER_REQ_DATA_T tData;
} __TLR_PACKED_POST RCX_GET_FW_PARAMETER_REQ_T;

#define RCX_GET_FW_PARAMETER_REQ_SIZE (sizeof(RCX_GET_FW_PARAMETER_REQ_DATA_T))


/***** confirmation packet *****/

typedef RCX_SET_FW_PARAMETER_REQ_T   RCX_GET_FW_PARAMETER_CNF_T;

#define RCX_GET_FW_PARAMETER_CNF_SIZE RCX_SET_FW_PARAMETER_REQ_SIZE

/******************************************************************************
 * RCX_LINK_STATUS_CHANGE_IND
 ******************************************************************************/

/***** indication packet *****/

typedef __TLR_PACKED_PRE struct RCX_LINK_STATUS_Ttag
{

  TLR_UINT32  ulPort;           /*!< Port the link status is for */

  TLR_BOOLEAN fIsFullDuplex;    /*!< If a full duplex link is available on this port */

  TLR_BOOLEAN fIsLinkUp;        /*!< If a link is available on this port */

  TLR_UINT32  ulSpeed;          /*!< Speed of the link \n\n

                                     \valueRange
                                     0:   No link \n
                                     10:  10MBit  \n
                                     100: 100MBit \n */

} __TLR_PACKED_POST RCX_LINK_STATUS_T;


typedef __TLR_PACKED_PRE struct RCX_LINK_STATUS_CHANGE_IND_DATA_Ttag
{
  RCX_LINK_STATUS_T  atLinkData[2];
} __TLR_PACKED_POST RCX_LINK_STATUS_CHANGE_IND_DATA_T;

typedef __TLR_PACKED_PRE struct RCX_LINK_STATUS_CHANGE_IND_Ttag
{
  TLR_PACKET_HEADER_T               tHead;
  RCX_LINK_STATUS_CHANGE_IND_DATA_T tData;
} __TLR_PACKED_POST RCX_LINK_STATUS_CHANGE_IND_T;

#define RCX_LINK_STATUS_CHANGE_IND_SIZE (sizeof(RCX_LINK_STATUS_CHANGE_IND_DATA_T))

/***** response packet *****/

typedef TLR_EMPTY_PACKET_T      RCX_LINK_STATUS_CHANGE_RES_T;

#define RCX_LINK_STATUS_CHANGE_RES_SIZE   (0)


/* pragma unpack */
#ifdef PRAGMA_PACK_ENABLE
#pragma PRAGMA_UNPACK_1(RCX_PUBLIC)
#endif

/***************************************************************************************/

#endif /* #ifndef __RCX_PUBLIC_H */
