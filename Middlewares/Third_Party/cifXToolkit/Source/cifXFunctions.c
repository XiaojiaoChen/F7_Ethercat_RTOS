/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: cifXFunctions.c 7388 2015-11-18 16:10:53Z Robert $:

  Description:
    cifX API function implementation

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2015-11-18  xChannelIORead()/xChannelIOWrite() does not return COM flag state in "uncontrolled mode"
    2015-10-20  Fixed xSysdeviceInfo()/CIFX_INFO_CMD_SYSTEM_CHANNEL_BLOCK for use with SPM,
                because data access via the "DPM pointer" not possible, using the internal buffer instead
    2015-07-21  Fixed compiler warnings created by implicit data conversion on 64bit systems
    2014-09-23  Function xChannelDMAState() now always present and
                returns CIFX_FUNCTION_NOT_AVAILABLE if CIFX_TOOLKIT_DMA is not defined
                /CIFX_NOTIFY_COM_STATE now calls
    2014-08-19  xChannelRegisterNotification/CIFX_NOTIFY_COM_STATE now calls
                always the user callback to signal the actual COM flag state
                xChannelCommonStatusBlock(), conversion structure s_atCommonStatusBlock
                adapted to actual rcX structure
    2012-12-11  Zero'ing local variables now done using OS_Memset to prevent compiler from
                creating constants for initialization (memory usage optimization)
    2012-08-08  Added casts needed when compiling with C++ compiler
    2012-02-20  Lint warnings removed
    2012-01-31  Added COM-State notification (CIFX_NOTIFY_COM_STATE)
    2011-12-14  Added xSysdeviceExtendedMemory()
    2011-04-18  Optional validation of pointers and handles passed
                to toolkit functions (CIFX_TOOLKIT_PARAMETER_CHECK)
    2011-01-31  Hardware interface layer added to support serial DPM access (e.g. via SPI)
    2010-08-12  xChannelDMAState() comments fixed
    2010-04-30  xChannelPLCActivateRead/Write did not lock access to handshake flags
    2010-04-28  xChannelPLCMemoryPointer may not work correctly due to
                an invalid parameter passed to OS_MapUserPointer / UnmapUserPointer
    2010-04-21  Fixed GCC compiler warning (dereferencing pointer breaks strict-aliasing rules)
    2010-04-15  - Added timeout to xChannelSyncState function
                - Added CIFX_SYNC_WAIT_CMD to be able to wait for sync signalling by firmware
    2010-03-29  IOMode / HandshakeBitState is now read from common status block if available
                Fallback is to use the modes read at startup during channel enumeration
    2010-03-05  Sync function and event handling added
    2009-11-02  - Definition CIFX_TOOLKIT_DMA to enable DMA function included
                - Definition CIFX_TOOLKIT_NO_ERRORLOOKUP included to
                  prevent error text table creation included
    2009-10-30  - xChannelDMAState() added
                - DMA handling in IORead and IOWrite added
    2009-10-01  Host COS flag handling moved to internal function DEV_DoHostCOSChange
    2009-07-07  xChannelBusState()
                - Handling moved to DEV_HostState() function to be callable
                  as a low level function
                - Handling of COM_FLAG in conjunction with timeout settings fixed/improved
    2009-06-04  Bugfix:
                - xChannelBusState(), command BUS_ON, DEV_WaitforBitStat()
                  RCX_FLAG_SET changed to RCX_FLAGS_SET
    2009-05-18  Big Endian problems fixed in
                - xChannelInfo (ulChannelError was not converted from little to big endian)
                - xChannelConfigLock (CIFX_CONFIGURATION_GETLOCKSTATE could result in invalid
                  locking state)
    2009-04-28  - New download type module included and xSysdeviceDownload()/
                  xChanneldDownload() changed / extended
                - Error lookup table extended
    2009-03-17  xChannelBusState and xChannelConfigLock did not work on Big Endian machines
    2009-01-20  Big endian host support added (set #define CIFX_TOOLKIT_BIGENDIAN)
    2008-07-31  C++ comments changed to C comments
    2008-06-17  OS_MapUserPointer() and OS_UnmapUserPointer() now
                have a new parameter pvOSDependent
    2008-05-16  xChannelOpen() now returns either CIFX_INVALID_BOARD or CIFX_INVALID_CHANNEL
    2008-05-06  xDriverErrorDescripton did not return error description,
                due to internal array size miscalculation
    2008-04-28  PLC Functions did not return NO_COMFLAG error.
    2008-02-21  Error return for xDriverMemoryPointer() and xChannelPLCMemoryPtr() fixed
    2007-04-24  DEV_BusState() now checks for COM-Flag if timeout is given
    2007-04-19  Download chooses now the transfer type by checking the extension
    2007-04-17  - Parameters of DEV_TransferPacket() extended
                - Parameters of DEV_UploadFile()/DownloadFile()extended
    2007-04-17  - xSysdeviceDownload(),
                - DEV_UploadFile() parameters extended
                - PFN_DOWNLOAD_PROGRESS renamed into DEV_PROGRESS_CALLBACK
    2007-04-10  Changed name of WARMSTART and COLDSTART to SYSTEM_START and CHANNEL_INIT
    2007-04-02  Changed COS flags to new definition
                - DEV_SetHostState()
                - DEV_DoWarmstart()/DEV_DoColdstart()
    2007-03-28  - xDriverEnumChannels() returns CIFX_NO_MORE_ENTRIES instead of CIFX_INVALID_CHANNEL.
                - xChannelPLCMemory(), check DEV_IsRunning() removed
                - xChannelPLCMemory(), check DEV_IsRunning() removed
    2007-03-27  Mutex added into I/O and Packet functions, to prevent multiple access
    2007-03-20  Added:
                - readout of Directory listing
                - xChannelFindFirstFile
                - xChannelFindNextFile
                - xChannelUpload
                - xSysdeviceFindFirstFile
                - xSysdeviceFindNextFile
                - xSysdeviceUpload
                - xChannelIOInfo
    2007-01-09  Missing function declarations for
                xChannelGetSendPacket
                xChannelConfigLock
                xChannelReset
                inserted
    2006-07-07  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file cifXFunctions.c
*   cifX API function implementation                                         */
/*****************************************************************************/

#include "cifXToolkit.h"
#include "cifXErrors.h"
#include "OS_Dependent.h"
#include "rcX_Public.h"
#include "cifXEndianess.h"

/* Commonly used function from cifXInit.c, not exposed to the user interface */
int32_t cifXStartModule      ( PDEVICEINSTANCE ptDevInstance, uint32_t ulChannelNumber, char* pszModuleName,
                               uint32_t ulFileSize, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);
int32_t cifXReadFirmwareIdent( PDEVICEINSTANCE ptDevInstance, uint32_t ulChannel,
                               PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser);

#ifdef CIFX_TOOLKIT_TIME
void    cifXInitTime         ( PDEVICEINSTANCE ptDevInstance);
#endif

/*****************************************************************************/
/*!  \addtogroup CIFX_DRIVER_API cifX Driver API implementation
*    \{                                                                      */
/*****************************************************************************/

/*****************************************************************************/
/*! Errorcode to Errordescription lookup table (english only)                */
/*****************************************************************************/
static struct CIFX_ERROR_TO_DESCRtag
{
  int32_t  lError;
  char* szErrorDescr;

} s_atErrorToDescrTable[] =
{
#ifndef CIFX_TOOLKIT_NO_ERRORLOOKUP
  /*******************************************************************************
  * cifX Device Driver Errors (Global)
  *******************************************************************************/
  {CIFX_INVALID_POINTER              ,"Invalid pointer (e.g. NULL) passed to driver"  },
  {CIFX_INVALID_BOARD                ,"No board with the given name / index available"},
  {CIFX_INVALID_CHANNEL              ,"No channel with the given index available"     },
  {CIFX_INVALID_HANDLE               ,"Invalid handle passed to driver"               },
  {CIFX_INVALID_PARAMETER            ,"Invalid parameter"                             },
  {CIFX_INVALID_COMMAND              ,"Invalid command"                               },
  {CIFX_INVALID_BUFFERSIZE           ,"Invalid buffer size"                           },
  {CIFX_INVALID_ACCESS_SIZE          ,"Invalid access size"                           },
  {CIFX_FUNCTION_FAILED              ,"Function failed"                               },
  {CIFX_FILE_OPEN_FAILED             ,"File could not be opened"                      },
  {CIFX_FILE_SIZE_ZERO               ,"File size is zero"                             },
  {CIFX_FILE_LOAD_INSUFF_MEM         ,"Insufficient memory to load file"              },
  {CIFX_FILE_READ_ERROR              ,"Error reading from file"                       },
  {CIFX_FILE_TYPE_INVALID            ,"Invalid file type"                             },
  {CIFX_FILE_NAME_INVALID            ,"Invalid file name"                             },
  {CIFX_FUNCTION_NOT_AVAILABLE       ,"Driver function not available"                 },
  {CIFX_BUFFER_TOO_SHORT             ,"Given buffer is too short"                     },
  {CIFX_MEMORY_MAPPING_FAILED        ,"Failed to map the memory"                      },
  {CIFX_NO_MORE_ENTRIES              ,"No more entries available"                     },
  {CIFX_CALLBACK_MODE_UNKNOWN        ,"Unkown callback handling mode"                 },
  {CIFX_CALLBACK_CREATE_EVENT_FAILED ,"Failed to create callback events"              },
  {CIFX_CALLBACK_CREATE_RECV_BUFFER  ,"Failed to create callback receive buffer"      },
  /*******************************************************************************
  * Generic Driver Errors
  *******************************************************************************/
  {CIFX_DRV_NOT_INITIALIZED          ,"Driver not initialized"                           },
  {CIFX_DRV_INIT_STATE_ERROR         ,"Driver init state error"                          },
  {CIFX_DRV_READ_STATE_ERROR         ,"Driver read state error"                          },
  {CIFX_DRV_CMD_ACTIVE               ,"Command is active on device"                      },
  {CIFX_DRV_DOWNLOAD_FAILED          ,"General error during download"                    },
  {CIFX_DRV_WRONG_DRIVER_VERSION     ,"Wrong driver version"                             },
  {CIFX_DRV_DRIVER_NOT_LOADED        ,"CIFx driver is not running"                       },
  {CIFX_DRV_INIT_ERROR               ,"Failed to initialize the device"                  },
  {CIFX_DRV_CHANNEL_NOT_INITIALIZED  ,"Channel not initialized (xChannelOpen not called)"},
  {CIFX_DRV_IO_CONTROL_FAILED        ,"IOControl call failed"                            },
  {CIFX_DRV_NOT_OPENED               ,"Driver was not opened"                            },
  {CIFX_DRV_DOWNLOAD_STORAGE_UNKNOWN ,"Unknown download storage type (RAM/FLASH based) found"},
  {CIFX_DRV_DOWNLOAD_FW_WRONG_CHANNEL,"Channel number for a firmware download not supported" },
  {CIFX_DRV_DOWNLOAD_MODULE_NO_BASEOS,"Modules are not allowed without a Base OS firmware"   },
  /*******************************************************************************
  * Generic Device Errors
  *******************************************************************************/
  {CIFX_DEV_DPM_ACCESS_ERROR         ,"Dual port memory not accessable (board not found)"},
  {CIFX_DEV_NOT_READY                ,"Device not ready (ready flag failed)"             },
  {CIFX_DEV_NOT_RUNNING              ,"Device not running (running flag failed)"         },
  {CIFX_DEV_WATCHDOG_FAILED          ,"Watchdog test failed"                             },
  {CIFX_DEV_SYSERR                   ,"Error in handshake flags"                         },
  {CIFX_DEV_MAILBOX_FULL             ,"Send mailbox is full"                             },
  {CIFX_DEV_PUT_TIMEOUT              ,"Send packet timeout"                              },
  {CIFX_DEV_GET_TIMEOUT              ,"Receive packet timeout"                           },
  {CIFX_DEV_GET_NO_PACKET            ,"No packet available"                              },
  {CIFX_DEV_RESET_TIMEOUT            ,"Reset command timeout"                            },
  {CIFX_DEV_NO_COM_FLAG              ,"COM-flag not set"                                 },
  {CIFX_DEV_EXCHANGE_FAILED          ,"I/O data exchange failed"                         },
  {CIFX_DEV_EXCHANGE_TIMEOUT         ,"I/O data exchange timeout"                        },
  {CIFX_DEV_COM_MODE_UNKNOWN         ,"Unknown I/O exchange mode "                       },
  {CIFX_DEV_FUNCTION_FAILED          ,"Device function failed "                          },
  {CIFX_DEV_DPMSIZE_MISMATCH         ,"DPM size differs from configuration"              },
  {CIFX_DEV_STATE_MODE_UNKNOWN       ,"Unknown state mode"                               },
  {CIFX_DEV_HW_PORT_IS_USED          ,"Output port already in use"                       },
  {CIFX_DEV_CONFIG_LOCK_TIMEOUT      ,"Configuration locking timeout"                    },
  {CIFX_DEV_CONFIG_UNLOCK_TIMEOUT    ,"Configuration unlocking timeout"                  },
  {CIFX_DEV_HOST_STATE_SET_TIMEOUT   ,"Set HOST state timeout"                           },
  {CIFX_DEV_HOST_STATE_CLEAR_TIMEOUT ,"Clear HOST state timeout"                         },
  {CIFX_DEV_INITIALIZATION_TIMEOUT   ,"Timeout during channel initialization"            },
  {CIFX_DEV_BUS_STATE_ON_TIMEOUT     ,"Set Bus ON timeout"                               },
  {CIFX_DEV_BUS_STATE_OFF_TIMEOUT    ," Set Bus OFF timeout"                             },
  {CIFX_DEV_MODULE_ALREADY_RUNNING   ,"Module already running"                           },
  {CIFX_DEV_MODULE_ALREADY_EXISTS    ,"Module already exists"                            },
  {CIFX_DEV_DMA_INSUFF_BUFFER_COUNT  ,"Number of configured DMA buffers insufficient"    },
  {CIFX_DEV_DMA_BUFFER_TOO_SMALL     ,"DMA buffers size too small (min size 256Byte)"    },
  {CIFX_DEV_DMA_BUFFER_TOO_BIG       ,"DMA buffers size too big (max size 63,75KByte)"   },
  {CIFX_DEV_DMA_BUFFER_NOT_ALIGNED   ,"DMA buffer alignment failed (must be 256Byte)"    },
  {CIFX_DEV_DMA_HANSHAKEMODE_NOT_SUPPORTED ,"I/O data uncontrolled handshake mode not supported"    },
  {CIFX_DEV_DMA_IO_AREA_NOT_SUPPORTED,"I/O area in DMA mode not supported (only area 0 possible)"   },
  {CIFX_DEV_DMA_STATE_ON_TIMEOUT     ,"Set DMA ON timeout"                               },
  {CIFX_DEV_DMA_STATE_OFF_TIMEOUT    ,"Set DMA OFF timeout"                              },

  /*******************************************************************************/
#else
  {CIFX_NO_ERROR, ""},
#endif
};

/*****************************************************************************/
/*! Structure description of NETX_SYSTEM_CHANNEL_INFO                        */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atSystemChannelInfo[] =
{
  /* Offset, Width,                       Elements */
  { 0x04, eCIFX_ENDIANESS_WIDTH_32BIT, 1}, /* ulSizeOfChannel                */
  { 0x08, eCIFX_ENDIANESS_WIDTH_16BIT, 2}, /* usSizeOfMailbox
                                              usMailboxStartOffset           */
};

/*****************************************************************************/
/*! Structure description of NETX_HANDSHAKE_CHANNEL_INFO                     */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atHandshakeChannelInfo[] =
{
  /* Offset, Width,                       Elements */
  { 0x04, eCIFX_ENDIANESS_WIDTH_32BIT, 1}, /* ulSizeOfChannel                */
};

/*****************************************************************************/
/*! Structure description of NETX_COMMUNICATION_CHANNEL_INFO                 */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atCommChannelInfo[] =
{
  /* Offset, Width,                       Elements */
  { 0x04, eCIFX_ENDIANESS_WIDTH_32BIT, 1}, /* ulSizeOfChannel                */
  { 0x08, eCIFX_ENDIANESS_WIDTH_16BIT, 3}, /* usCommunicationClass
                                              usProtocolClass
                                              usProtocolConformanceClass     */
};

/*****************************************************************************/
/*! Structure description of NETX_APPLICATION_CHANNEL_INFO                   */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atAppChannelInfo[] =
{
  /* Offset, Width,                       Elements */
  { 0x04, eCIFX_ENDIANESS_WIDTH_32BIT, 1}, /* ulSizeOfChannel                */
};

/*****************************************************************************/
/*! Structure description of NETX_SYSTEM_INFO_BLOCK                          */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atSystemInfoBlock[] =
{
  /* Offset, Width,                       Elements */
  { 0x04, eCIFX_ENDIANESS_WIDTH_32BIT, 3}, /* DpmTotalSize, DevNr, SerNr     */
  { 0x10, eCIFX_ENDIANESS_WIDTH_16BIT, 6}, /* ausHwOptions, usMfg, usProdDat */
  { 0x1C, eCIFX_ENDIANESS_WIDTH_32BIT, 2}, /* ulLicenseFlags1/2              */
  { 0x24, eCIFX_ENDIANESS_WIDTH_16BIT, 3}, /* LicenseId/flags, DeviceClass   */
  { 0x2C, eCIFX_ENDIANESS_WIDTH_16BIT, 2}, /* ausReserved                    */
};

/*****************************************************************************/
/*! Structure description of NETX_SYSTEM_CONTROL_BLOCK                       */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atSystemControlBlock[] =
{
  /* Offset, Width,                       Elements */
  { 0x00, eCIFX_ENDIANESS_WIDTH_32BIT, 2}, /* ulSystemCmdCOS, ulReserved     */
};

/*****************************************************************************/
/*! Structure description of NETX_SYSTEM_STATUS_BLOCK                        */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atSystemStatusBlock[] =
{
  /* Offset, Width,                       Elements */
  { 0x00, eCIFX_ENDIANESS_WIDTH_32BIT, 5}, /* ulSystem-COS/Status/Error
                                              ulReserved1                    */
  { 0x14, eCIFX_ENDIANESS_WIDTH_16BIT, 1}, /* usCpuLoad                      */
};

/*****************************************************************************/
/*! Structure description of NETX_CONTROL_BLOCK                              */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atControlBlock[] =
{
  /* Offset, Width,                       Elements */
  { 0x00, eCIFX_ENDIANESS_WIDTH_32BIT, 2}, /* ulApplCos, ulWatchdog          */
};

/*****************************************************************************/
/*! Structure description of NETX_COMMON_STATUS_BLOCK                        */
/*****************************************************************************/
static const CIFX_ENDIANESS_ENTRY_T s_atCommonStatusBlock[] =
{
  /* Offset, Width,                       Elements */
  { 0x00, eCIFX_ENDIANESS_WIDTH_32BIT, 3}, /* ulCommCos,ulCommState,
                                              ulCommError                    */
  { 0x0C, eCIFX_ENDIANESS_WIDTH_16BIT, 2}, /* usVersion,usWatchDogTime
                                                                             */
  { 0x14, eCIFX_ENDIANESS_WIDTH_32BIT, 2}, /* ulHostWatchDog, ulErrorCount,
                                                                             */
  { 0x22, eCIFX_ENDIANESS_WIDTH_16BIT, 3}, /* ausReserved[3]
                                                                             */
  { 0x28, eCIFX_ENDIANESS_WIDTH_32BIT, 6}, /* ulSlaveState, ulSlaveErrLogInd
                                              ulNumOfConfigSlaves,ulNumOfActiveSlaves
                                              ulNumOfDiagSlaves, ulReserved  */
};

extern uint32_t           g_ulDeviceCount; /*!< Number of available device (Array size of g_pptDevices) */
extern PDEVICEINSTANCE*        g_pptDevices;    /*!< Array containing all handled device instances           */
extern TKIT_DRIVER_INFORMATION g_tDriverInfo;   /*!< Global driver information                               */

#ifdef CIFX_TOOLKIT_PARAMETER_CHECK
/*****************************************************************************/
/*! Checks if the given sysdevice handle is valid
*   \param hDriver      Sysdevice handle
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
static int32_t CheckSysdeviceHandle(CIFXHANDLE hChannel)
{
  int32_t  lRet  = CIFX_INVALID_HANDLE;
  uint32_t ulDev = 0;

  for(ulDev = 0; ulDev < g_ulDeviceCount; ++ulDev)
  {
    if (hChannel == &g_pptDevices[ulDev]->tSystemDevice)
    {
      lRet = CIFX_NO_ERROR;
      break;
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Checks if the given channel handle is valid
*   \param hDriver      Channel handle
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
static int32_t CheckChannelHandle(CIFXHANDLE hChannel)
{
  int32_t  lRet  = CIFX_INVALID_HANDLE;
  uint32_t ulDev = 0;

  for(ulDev = 0; ulDev < g_ulDeviceCount; ++ulDev)
  {
    uint32_t ulChannel = 0;
    for(ulChannel = 0; ulChannel < g_pptDevices[ulDev]->ulCommChannelCount; ++ulChannel)
    {
      if (hChannel == g_pptDevices[ulDev]->pptCommChannels[ulChannel])
      {
        lRet = CIFX_NO_ERROR;
        break;
      }
    }
  }

  return lRet;
}
#endif

#ifdef CIFX_TOOLKIT_PARAMETER_CHECK
  #define CHECK_POINTER(param) if ((void*)NULL == param) return CIFX_INVALID_POINTER;
  #define CHECK_DRIVERHANDLE(handle) if (&g_tDriverInfo != handle) return CIFX_INVALID_HANDLE;
  #define CHECK_SYSDEVICEHANDLE(handle) if (CIFX_NO_ERROR != CheckSysdeviceHandle(handle)) return CIFX_INVALID_HANDLE;
  #define CHECK_CHANNELHANDLE(handle) if (CIFX_NO_ERROR != CheckChannelHandle(handle)) return CIFX_INVALID_HANDLE;
#else
  #define CHECK_POINTER(param)
  #define CHECK_DRIVERHANDLE(handle) UNREFERENCED_PARAMETER(handle)
  #define CHECK_SYSDEVICEHANDLE(handle) 
  #define CHECK_CHANNELHANDLE(handle) 
#endif

/*****************************************************************************/
/*! Opens the System device on the given board
*   \param hDriver      Driver handle
*   \param szBoard      Name of the board to open
*   \param phSysdevice  Returned handle to the System device area
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceOpen(CIFXHANDLE hDriver, char* szBoard, CIFXHANDLE* phSysdevice)
{
  int32_t  lRet = CIFX_INVALID_BOARD;
  uint32_t ulIdx;

  if(0 == g_tDriverInfo.ulOpenCount)
    return CIFX_DRV_NOT_OPENED;

  CHECK_DRIVERHANDLE(hDriver);
  CHECK_POINTER(szBoard);
  CHECK_POINTER(phSysdevice); 

  for(ulIdx = 0; ulIdx < g_ulDeviceCount; ++ulIdx)
  {
    if( (OS_Strcmp(g_pptDevices[ulIdx]->szName,  szBoard) == 0) ||
        (OS_Strcmp(g_pptDevices[ulIdx]->szAlias, szBoard) == 0) )
    {
      ++g_pptDevices[ulIdx]->tSystemDevice.ulOpenCount;
      *phSysdevice = (CIFXHANDLE)(&g_pptDevices[ulIdx]->tSystemDevice);
      lRet = CIFX_NO_ERROR;
      break;
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Closes an open System device
*   \param hSysdevice  Handle to the System device to close
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceClose(CIFXHANDLE hSysdevice)
{
  PCHANNELINSTANCE ptSysDevice = (PCHANNELINSTANCE)hSysdevice;

  CHECK_SYSDEVICEHANDLE(hSysdevice);

  --ptSysDevice->ulOpenCount;

  return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! Gets the Mailbox state of an open system device
*   \param hSysdevice      Handle to the System device
*   \param pulRecvPktCount Number of packets in receive mailbox
*   \param pulSendPktCount Number of packets the application is able to send
*                          at once
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceGetMBXState(CIFXHANDLE hSysdevice, uint32_t* pulRecvPktCount, uint32_t* pulSendPktCount)
{
  PCHANNELINSTANCE ptSysDevice = (PCHANNELINSTANCE)hSysdevice;

  return DEV_GetMBXState(ptSysDevice, pulRecvPktCount, pulSendPktCount);
}

/*****************************************************************************/
/*! Inserts a packet into the System Mailbox
*   \param hSysdevice      Handle to the System device
*   \param ptSendPkt       Packet to send to device
*   \param ulTimeout       maximum time to wait for packet to be accepted
*                          by device (in ms)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdevicePutPacket(CIFXHANDLE hSysdevice, CIFX_PACKET* ptSendPkt, uint32_t ulTimeout)
{
  int32_t          lRet        = CIFX_NO_ERROR;
  PCHANNELINSTANCE ptSysDevice = (PCHANNELINSTANCE)hSysdevice;

  if( !OS_WaitMutex( ptSysDevice->tSendMbx.pvSendMBXMutex, ulTimeout))
    return CIFX_DRV_CMD_ACTIVE;

  lRet = DEV_PutPacket(ptSysDevice, ptSendPkt, ulTimeout);

  OS_ReleaseMutex( ptSysDevice->tSendMbx.pvSendMBXMutex);

  return lRet;
}

/*****************************************************************************/
/*! Retrieves a packet from the System Mailbox
*   \param hSysdevice      Handle to the System device
*   \param ulSize          Size of the buffer to retrieve the packet
*   \param ptRecvPkt       Pointer to buffer for received packet
*   \param ulTimeout       maximum time to wait for packet to be delivered
*                          by device (in ms)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceGetPacket(CIFXHANDLE hSysdevice, uint32_t ulSize, CIFX_PACKET* ptRecvPkt, uint32_t ulTimeout)
{
  int32_t          lRet        = CIFX_NO_ERROR;
  PCHANNELINSTANCE ptSysDevice = (PCHANNELINSTANCE)hSysdevice;

  if( !OS_WaitMutex( ptSysDevice->tRecvMbx.pvRecvMBXMutex, ulTimeout))
    return CIFX_DRV_CMD_ACTIVE;

  lRet = DEV_GetPacket(ptSysDevice, ptRecvPkt, ulSize, ulTimeout);

  OS_ReleaseMutex( ptSysDevice->tRecvMbx.pvRecvMBXMutex);

  return lRet;
}

/*****************************************************************************/
/*! Download a file (Firmware, Configuratio, etc) to the device
*   \param hSysdevice         Handle to the system device
*   \param ulChannel          Channel number to load the file to
*   \param ulMode             Download mode (DOWNLOAD_MODE_FIRMWARE, etc)
*   \param pszFileName        Name of the file
*   \param pabFileData        Pointer to the file data
*   \param ulFileSize         Length of the file data
*   \param pfnCallback        Callback for progress indication
*                             (NULL for no callback)
*   \param pfnRecvPktCallback Callback Callback pointer for unsolicited receive packets
*                             (NULL for no callback)
*   \param pvUser             User parameter passed to callback
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceDownload( CIFXHANDLE            hSysdevice,
                                     uint32_t              ulChannel,
                                     uint32_t              ulMode,
                                     char*                 pszFileName,
                                     uint8_t*              pabFileData,
                                     uint32_t              ulFileSize,
                                     PFN_PROGRESS_CALLBACK pfnCallback,
                                     PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,
                                     void*                 pvUser)
{
  PCHANNELINSTANCE ptSysDevice    = (PCHANNELINSTANCE)hSysdevice;
  uint32_t         ulTransferType = 0;
  int32_t          lRet           = CIFX_NO_ERROR;

  CHECK_SYSDEVICEHANDLE(hSysdevice);
  CHECK_POINTER(pszFileName);
  CHECK_POINTER(pabFileData);

  switch(ulMode)
  {
  case DOWNLOAD_MODE_FIRMWARE:
    if( CIFX_NO_ERROR != (lRet = DEV_GetFWTransferTypeFromFileName( pszFileName, &ulTransferType)))
      return lRet;

    lRet = DEV_DownloadFile(ptSysDevice,
                            ulChannel,
                            ptSysDevice->tSendMbx.ulSendMailboxLength,
                            ulTransferType,
                            pszFileName,
                            ulFileSize,
                            pabFileData,
                            DEV_TransferPacket,
                            pfnCallback,
                            pfnRecvPktCallback,
                            pvUser);

    break;

  case DOWNLOAD_MODE_CONFIG:
  case DOWNLOAD_MODE_FILE:
      ulTransferType = RCX_FILE_XFER_FILE;
      lRet = DEV_DownloadFile(ptSysDevice,
                              ulChannel,
                              ptSysDevice->tSendMbx.ulSendMailboxLength,
                              ulTransferType,
                              pszFileName,
                              ulFileSize,
                              pabFileData,
                              DEV_TransferPacket,
                              pfnCallback,
                              pfnRecvPktCallback,
                              pvUser);
    break;

  case DOWNLOAD_MODE_LICENSECODE:
      ulTransferType = RCX_FILE_XFER_LICENSE_CODE;

      lRet = DEV_DownloadFile(ptSysDevice,
                              ulChannel,
                              ptSysDevice->tSendMbx.ulSendMailboxLength,
                              ulTransferType,
                              pszFileName,
                              ulFileSize,
                              pabFileData,
                              DEV_TransferPacket,
                              pfnCallback,
                              pfnRecvPktCallback,
                              pvUser);

    break;

  case DOWNLOAD_MODE_MODULE:
    {
      /* We downloading a NXO file */
      PDEVICEINSTANCE   ptDevInstance = (PDEVICEINSTANCE)ptSysDevice->pvDeviceInstance;
      PCHANNELINSTANCE  ptChannelInst = NULL;

      /* Check if we have a NXO module file */
      if ( !DEV_IsNXOFile( pszFileName))
      {
        lRet = CIFX_FILE_NAME_INVALID;
      } else if(ulChannel >= ptDevInstance->ulCommChannelCount)
      {
        /* Invalid channel nummer */
        lRet = CIFX_INVALID_CHANNEL;
      } else
      {
        /* Check if a the channel is READY and somthing is already loaded */
        ptChannelInst = ptDevInstance->pptCommChannels[ulChannel];

        /* Check if we are supporting modules */
        if( !ptDevInstance->fModuleLoad)
        {
          lRet = CIFX_DRV_DOWNLOAD_MODULE_NO_BASEOS;
        } else if( DEV_IsReady(ptChannelInst))
        {
          /* Channel already READY */
          lRet = CIFX_DEV_MODULE_ALREADY_RUNNING;
        } else
        {
          uint8_t bLoadState = CIFXTKIT_DOWNLOAD_NONE;
          if ( CIFX_NO_ERROR == (lRet = DEV_ProcessFWDownload( ptDevInstance,
                                                               ulChannel,
                                                               NULL,
                                                               pszFileName,
                                                               ulFileSize,
                                                               pabFileData,
                                                               &bLoadState,
                                                               DEV_TransferPacket,
                                                               pfnCallback,
                                                               pfnRecvPktCallback,
                                                               pvUser)))
          {
            /* Start module */
            if (CIFX_NO_ERROR == (lRet = cifXStartModule( ptDevInstance, ulChannel, pszFileName,
                                         ulFileSize, pfnRecvPktCallback, pvUser)))
            {
              if ( CIFX_NO_ERROR == (lRet = cifXReadFirmwareIdent( ptDevInstance, ulChannel,
                                                                   pfnRecvPktCallback, pvUser)))
              {
                if ( 0 == (bLoadState & CIFXTKIT_DOWNLOAD_EXECUTED))
                {
                  /* Return download skipped, file exists */
                  lRet = CIFX_DEV_MODULE_ALREADY_EXISTS;
                }
              }
            }
          }
        }
      }
    }
    break;

  default:
    return CIFX_INVALID_PARAMETER;
  }


  return lRet;
}

/*****************************************************************************/
/*! Gets the information of a system device
*   \param hSysdevice   Handle to the system device
*   \param ulCmd        Information to fetch (see defines CIFX_INFO_CMD_SYSTEM_XXX)
*   \param ulSize       Size of the passed structure
*   \param pvInfo       Pointer to the structure for returned data
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceInfo(CIFXHANDLE hSysdevice, uint32_t ulCmd, uint32_t ulSize, void* pvInfo)
{
  int32_t              lRet         = CIFX_NO_ERROR;
  PCHANNELINSTANCE     ptSysDevice  = (PCHANNELINSTANCE)hSysdevice;
  NETX_SYSTEM_CHANNEL* ptSysChannel = NULL;
  
  CHECK_SYSDEVICEHANDLE(hSysdevice);
  CHECK_POINTER(pvInfo);

  ptSysChannel = (NETX_SYSTEM_CHANNEL*)ptSysDevice->pbDPMChannelStart;

  switch(ulCmd)
  {
    case CIFX_INFO_CMD_SYSTEM_INFORMATION:
      if( ulSize < (uint32_t)sizeof(SYSTEM_CHANNEL_SYSTEM_INFORMATION))
      {
        lRet = CIFX_INVALID_BUFFERSIZE;
      } else
      {
        /* Insert global system channel information */
        SYSTEM_CHANNEL_SYSTEM_INFORMATION* ptInfo = (SYSTEM_CHANNEL_SYSTEM_INFORMATION*)pvInfo;

        /* These values are directly read from DPM, so they need to be converted to host endianess */
        ptInfo->ulSystemError   = LE32_TO_HOST(HWIF_READ32(ptSysDevice->pvDeviceInstance, ptSysChannel->tSystemState.ulSystemError));
        ptInfo->ulDpmTotalSize  = LE32_TO_HOST(HWIF_READ32(ptSysDevice->pvDeviceInstance, ptSysChannel->tSystemInfo.ulDpmTotalSize));
        ptInfo->ulDeviceNumber  = LE32_TO_HOST(HWIF_READ32(ptSysDevice->pvDeviceInstance, ptSysChannel->tSystemInfo.ulDeviceNumber));
        ptInfo->ulSerialNumber  = LE32_TO_HOST(HWIF_READ32(ptSysDevice->pvDeviceInstance, ptSysChannel->tSystemInfo.ulSerialNumber));

        ptInfo->ulMBXSize       = ptSysDevice->tRecvMbx.ulRecvMailboxLength;
        ptInfo->ulOpenCnt       = ptSysDevice->ulOpenCount;
      }
    break;

    case CIFX_INFO_CMD_SYSTEM_INFO_BLOCK:
      if( ulSize < (uint32_t)sizeof(SYSTEM_CHANNEL_SYSTEM_INFO_BLOCK))
      {
        lRet = CIFX_INVALID_BUFFERSIZE;
      } else
      {
        uint32_t ulCopyLen = min( ulSize,
                                  (uint32_t)sizeof(SYSTEM_CHANNEL_SYSTEM_INFO_BLOCK));

        HWIF_READN(ptSysDevice->pvDeviceInstance, pvInfo, &ptSysChannel->tSystemInfo, ulCopyLen);

        cifXConvertEndianess(pvInfo,
                             ulCopyLen,
                             s_atSystemInfoBlock,
                             sizeof(s_atSystemInfoBlock) / sizeof(s_atSystemInfoBlock[0]));
      }
    break;

    case CIFX_INFO_CMD_SYSTEM_CHANNEL_BLOCK:
      if( ulSize < (uint32_t)sizeof(SYSTEM_CHANNEL_CHANNEL_INFO_BLOCK))
      {
        lRet = CIFX_INVALID_BUFFERSIZE;
      } else
      {
        SYSTEM_CHANNEL_CHANNEL_INFO_BLOCK* ptInfoBuffer = (SYSTEM_CHANNEL_CHANNEL_INFO_BLOCK*) pvInfo; /* use the read buffer for data conversion */

        uint32_t ulCopyLen = min( ulSize,
                                  (uint32_t)sizeof(SYSTEM_CHANNEL_CHANNEL_INFO_BLOCK));
        int iChannel;

        HWIF_READN(ptSysDevice->pvDeviceInstance, pvInfo, &ptSysChannel->atChannelInfo[0], ulCopyLen);

        /* Convert channel information structure. This depends on the first byte (bChannelType),
           so we need to parse the whole array */
        for(iChannel = 0;
            iChannel < (int) (sizeof(ptSysChannel->atChannelInfo) / sizeof(ptSysChannel->atChannelInfo[0]));
            ++iChannel)
        {
          uint32_t ulBlockLength = (uint32_t)sizeof(ptSysChannel->atChannelInfo[0]);
          uint32_t ulOffset      = (uint32_t)(iChannel * ulBlockLength);

          if( ulOffset > ulCopyLen)
            break;

          if( (ulOffset + sizeof(ptSysChannel->atChannelInfo[0])) > ulCopyLen)
          {
            /* part of block copied, so calculate restlen */
            ulBlockLength = ulCopyLen - ulOffset;
          }

          /* Convert endianess */
          switch(ptInfoBuffer->abInfoBlock[iChannel][0])
          {
          case RCX_CHANNEL_TYPE_SYSTEM:
            cifXConvertEndianess(&ptInfoBuffer->abInfoBlock[iChannel],
                                 ulBlockLength,
                                 s_atSystemChannelInfo,
                                 sizeof(s_atSystemChannelInfo) / sizeof(s_atSystemChannelInfo[0]));
            break;

          case RCX_CHANNEL_TYPE_HANDSHAKE:
            cifXConvertEndianess(&ptInfoBuffer->abInfoBlock[iChannel],
                                 ulBlockLength,
                                 s_atHandshakeChannelInfo,
                                 sizeof(s_atHandshakeChannelInfo) / sizeof(s_atHandshakeChannelInfo[0]));
            break;

          case RCX_CHANNEL_TYPE_COMMUNICATION:
            cifXConvertEndianess(&ptInfoBuffer->abInfoBlock[iChannel],
                                 ulBlockLength,
                                 s_atCommChannelInfo,
                                 sizeof(s_atCommChannelInfo) / sizeof(s_atCommChannelInfo[0]));
            break;

          case RCX_CHANNEL_TYPE_APPLICATION:
            cifXConvertEndianess(&ptInfoBuffer->abInfoBlock[iChannel],
                                 ulBlockLength,
                                 s_atAppChannelInfo,
                                 sizeof(s_atAppChannelInfo) / sizeof(s_atAppChannelInfo[0]));
            break;

          default:
            /* This should never happen */
            break;
          }
        }
      }
    break;

    case CIFX_INFO_CMD_SYSTEM_CONTROL_BLOCK:
      if( ulSize < (uint32_t)sizeof(SYSTEM_CHANNEL_SYSTEM_CONTROL_BLOCK))
      {
        lRet = CIFX_INVALID_BUFFERSIZE;
      } else
      {
        uint32_t ulCopyLen = min(ulSize,
                                      (uint32_t)sizeof(SYSTEM_CHANNEL_SYSTEM_CONTROL_BLOCK));
        HWIF_READN(ptSysDevice->pvDeviceInstance, pvInfo, &ptSysChannel->tSystemControl, ulCopyLen);

        cifXConvertEndianess(pvInfo,
                             ulCopyLen,
                             s_atSystemControlBlock,
                             sizeof(s_atSystemControlBlock) / sizeof(s_atSystemControlBlock[0]));
      }
    break;

    case CIFX_INFO_CMD_SYSTEM_STATUS_BLOCK:
      if( ulSize < (uint32_t)sizeof(SYSTEM_CHANNEL_SYSTEM_STATUS_BLOCK))
      {
        lRet = CIFX_INVALID_BUFFERSIZE;
      } else
      {
        uint32_t ulCopyLen = min(ulSize,
                                      (uint32_t)sizeof(SYSTEM_CHANNEL_SYSTEM_STATUS_BLOCK));

        HWIF_READN(ptSysDevice->pvDeviceInstance, pvInfo, &ptSysChannel->tSystemState, ulCopyLen);

        cifXConvertEndianess(pvInfo,
                             ulCopyLen,
                             s_atSystemStatusBlock,
                             sizeof(s_atSystemStatusBlock) / sizeof(s_atSystemStatusBlock[0]));
      }
    break;

    default:
      lRet = CIFX_INVALID_COMMAND;
    break;

  } /* end switch */

  return lRet;
}

/*****************************************************************************/
/*! Hard resets a complete device via system channel
*   \param hSysdevice Handle to system device
*   \param ulTimeout  Timeout to wait for card to finish reset
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceReset(CIFXHANDLE hSysdevice, uint32_t ulTimeout)
{
  int32_t          lRet;
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hSysdevice;

  CHECK_SYSDEVICEHANDLE(hSysdevice);

  lRet = DEV_DoSystemStart(ptChannel, ulTimeout);
  
  #ifdef CIFX_TOOLKIT_TIME
    if (CIFX_NO_ERROR == lRet)
      cifXInitTime((PDEVICEINSTANCE)ptChannel->pvDeviceInstance); 
  #endif
  
  return lRet;
}

/*****************************************************************************/
/*! Boot start reset to via system channel
*   \param hSysdevice Handle to system device
*   \param ulTimeout  Timeout to wait for card to finish reset
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceBootstart(CIFXHANDLE hSysdevice, uint32_t ulTimeout)
{
  int32_t          lRet;
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hSysdevice;

  CHECK_SYSDEVICEHANDLE(hSysdevice);

  lRet = DEV_DoSystemBootstart(ptChannel, ulTimeout);

  return lRet;
}

/*****************************************************************************/
/*! Get/Return a memory pointer to an extended board memory if available
*   \param hSysdevice   Handle to system device
*   \param ulCmd        Command for get/free
*   \param ptExtMemInfo Pointer to a user buffer to return the information
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceExtendedMemory(CIFXHANDLE hSysdevice, uint32_t ulCmd, CIFX_EXTENDED_MEMORY_INFORMATION* ptExtMemInfo)
{
  int32_t               lRet         = CIFX_NO_ERROR;
  PCHANNELINSTANCE      ptSysDevice  = (PCHANNELINSTANCE)hSysdevice;
  PDEVICEINSTANCE       ptDevInst    = (PDEVICEINSTANCE)ptSysDevice->pvDeviceInstance;
  NETX_SYSTEM_CHANNEL*  ptSysChannel = NULL;
  
  CHECK_SYSDEVICEHANDLE(hSysdevice);
  CHECK_POINTER(pvInfo);

  ptSysChannel = (NETX_SYSTEM_CHANNEL*)ptSysDevice->pbDPMChannelStart;
  
  
  if(0 == g_tDriverInfo.ulOpenCount)
    return CIFX_DRV_NOT_OPENED;

  CHECK_SYSDEVICEHANDLE(hSysdevice);
  CHECK_POINTER(ptExtMemInfo);

  switch(ulCmd)
  {
    case CIFX_GET_EXTENDED_MEMORY_POINTER:
      {
        void* pvMemoryPtr           = NULL;
        
        if( (NULL == ptDevInst->pbExtendedMemory)    ||
            (0    == ptDevInst->ulExtendedMemorySize))

        {
          lRet = CIFX_MEMORY_MAPPING_FAILED;
        }else
        {

          ptExtMemInfo->pvMemoryID    = NULL;
          ptExtMemInfo->pvMemoryPtr   = NULL;
          ptExtMemInfo->ulMemorySize  = 0;
          ptExtMemInfo->ulMemoryType  = 0;


          /* Return global memory information */
          if(NULL == (ptExtMemInfo->pvMemoryID = OS_MapUserPointer(ptDevInst->pbExtendedMemory,
                                                                   ptDevInst->ulExtendedMemorySize,
                                                                   &pvMemoryPtr,
                                                                   ptDevInst->pvOSDependent)))
          {
            lRet = CIFX_MEMORY_MAPPING_FAILED;
          } else
          {
            ptExtMemInfo->pvMemoryPtr  = pvMemoryPtr;
            ptExtMemInfo->ulMemorySize = ptDevInst->ulExtendedMemorySize;
            ptExtMemInfo->ulMemoryType = LE32_TO_HOST(HWIF_READ32( ptDevInst, ptSysChannel->tSystemState.ulHWFeatures)) & (RCX_SYSTEM_EXTMEM_ACCESS_MSK | RCX_SYSTEM_EXTMEM_TYPE_MSK);
            
            if( RCX_SYSTEM_EXTMEM_ACCESS_BOTH == (ptExtMemInfo->ulMemoryType & RCX_SYSTEM_EXTMEM_ACCESS_MSK))
              ptExtMemInfo->ulMemorySize = ptDevInst->ulExtendedMemorySize  / 2;
            else if( RCX_SYSTEM_EXTMEM_ACCESS_INTERNAL == (ptExtMemInfo->ulMemoryType & RCX_SYSTEM_EXTMEM_ACCESS_MSK))
              ptExtMemInfo->ulMemorySize = 0;
          }
        }
      }
      break;

    case CIFX_FREE_EXTENDED_MEMORY_POINTER:
      {
        /* Clear user area */
        if(!OS_UnmapUserPointer(ptExtMemInfo->pvMemoryID, ptDevInst->pvOSDependent))
        {
          lRet = CIFX_INVALID_HANDLE;
        } else
        {
          ptExtMemInfo->pvMemoryID    = NULL;
          ptExtMemInfo->pvMemoryPtr   = NULL;
          ptExtMemInfo->ulMemorySize  = 0;
          ptExtMemInfo->ulMemoryType  = 0;
        }
      }
      break;

    case CIFX_GET_EXTENDED_MEMORY_INFO:
      {
        ptExtMemInfo->pvMemoryID    = NULL;
        ptExtMemInfo->pvMemoryPtr   = NULL;
        ptExtMemInfo->ulMemorySize  = ptDevInst->ulExtendedMemorySize;
        ptExtMemInfo->ulMemoryType  = LE32_TO_HOST(HWIF_READ32( ptDevInst, ptSysChannel->tSystemState.ulHWFeatures)) & (RCX_SYSTEM_EXTMEM_ACCESS_MSK | RCX_SYSTEM_EXTMEM_TYPE_MSK);

        if( RCX_SYSTEM_EXTMEM_ACCESS_BOTH == (ptExtMemInfo->ulMemoryType & RCX_SYSTEM_EXTMEM_ACCESS_MSK))
          ptExtMemInfo->ulMemorySize = ptDevInst->ulExtendedMemorySize  / 2;
        else if( RCX_SYSTEM_EXTMEM_ACCESS_INTERNAL == (ptExtMemInfo->ulMemoryType & RCX_SYSTEM_EXTMEM_ACCESS_MSK))
          ptExtMemInfo->ulMemorySize = 0;
      }
      break;

    default:
      lRet = CIFX_INVALID_COMMAND;
      break;
  } /* end switch */

  return lRet;
}

/*****************************************************************************/
/*! Opens a channel by name (Name can be obtained when enumerating Channels)
*   \param hDriver    Driver handle
*   \param szBoard    DOS Device Name of the Board to open
*   \param ulChannel  Channel number to open (0..n)
*   \param phChannel  Returned handle to the channel (Needed for all channel
*                     specific operations)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelOpen(CIFXHANDLE hDriver, char* szBoard, uint32_t ulChannel, CIFXHANDLE* phChannel)
{
  int32_t  lRet = CIFX_INVALID_BOARD;
  uint32_t ulIdx;

  if(0 == g_tDriverInfo.ulOpenCount)
    return CIFX_DRV_NOT_OPENED;

  CHECK_DRIVERHANDLE(hDriver);
  CHECK_POINTER(szBoard);
  CHECK_POINTER(phChannel);

  for(ulIdx = 0; ulIdx < g_ulDeviceCount; ++ulIdx)
  {
    /* Try to find the requested board */
    if( (OS_Strcmp(g_pptDevices[ulIdx]->szName,  szBoard) == 0) ||
        (OS_Strcmp(g_pptDevices[ulIdx]->szAlias, szBoard) == 0) )
    {
      /* Try to open the given channel */
      lRet = CIFX_INVALID_CHANNEL;
      if(ulChannel < g_pptDevices[ulIdx]->ulCommChannelCount)
      {
        /* We found the channel */
        PCHANNELINSTANCE ptChannel = g_pptDevices[ulIdx]->pptCommChannels[ulChannel];
        ++ptChannel->ulOpenCount;
        *phChannel = (CIFXHANDLE)ptChannel;
        lRet = CIFX_NO_ERROR;
      }
      break;
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Closes a previously opened channel
*   \param hChannel Channel handle acquired by xChannelOpen
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelClose(CIFXHANDLE hChannel)
{
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);

  --ptChannel->ulOpenCount;

  return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! Download a file (Firmware, Configuration, etc) to the device
*   \param hChannel           Handle to the channel
*   \param ulMode             Download mode (DOWNLOAD_MODE_FIRMWARE, etc)
*   \param pszFileName        Name of the file
*   \param pabFileData        Pointer to the file data
*   \param ulFileSize         Length of the file data
*   \param pfnCallback        Callback for progress indication
*                             (NULL for no callback)
*   \param pfnRecvPktCallback Callback Callback pointer for unsolicited receive packets
*                             (NULL for no callback)
*   \param pvUser             User parameter passed to callback
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelDownload(CIFXHANDLE hChannel,    uint32_t   ulMode,
                                  char*      pszFileName, uint8_t*  pabFileData, uint32_t ulFileSize,
                                  PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser)
{
  PCHANNELINSTANCE ptChannel      = (PCHANNELINSTANCE)hChannel;
  uint32_t         ulTransferType = 0;
  int32_t          lRet           = CIFX_NO_ERROR;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pszFileName);
  CHECK_POINTER(pabFileData);

  switch(ulMode)
  {
  case DOWNLOAD_MODE_FIRMWARE:
    if( CIFX_NO_ERROR != (lRet = DEV_GetFWTransferTypeFromFileName( pszFileName, &ulTransferType)))
      return lRet;
    break;

  case DOWNLOAD_MODE_CONFIG:
  case DOWNLOAD_MODE_FILE:
    ulTransferType = RCX_FILE_XFER_FILE;
    break;

  case DOWNLOAD_MODE_LICENSECODE:
    ulTransferType = RCX_FILE_XFER_LICENSE_CODE;
    break;

  default:
    return CIFX_INVALID_PARAMETER;
  }

  lRet = DEV_DownloadFile(ptChannel,
                          ptChannel->ulChannelNumber,
                          ptChannel->tSendMbx.ulSendMailboxLength,
                          ulTransferType,
                          pszFileName,
                          ulFileSize,
                          pabFileData,
                          DEV_TransferPacket,
                          pfnCallback,
                          pfnRecvPktCallback,
                          pvUser);

  return lRet;
}

/*****************************************************************************/
/*! Returns the Mailbox state from a specific channel
*   \param hChannel         Channel handle acquired by xChannelOpen
*   \param pulRecvPktCount  Number of Messages waiting in receive mailbox
*   \param pulSendPktCount  State of the Send Mailbox
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelGetMBXState(CIFXHANDLE hChannel, uint32_t* pulRecvPktCount, uint32_t* pulSendPktCount)
{
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;

  return DEV_GetMBXState(ptChannel, pulRecvPktCount, pulSendPktCount);
}

/*****************************************************************************/
/*! Inserts a packet into the channels mailbox
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ptSendPkt  Packet to send to channel
*   \param ulTimeout  Time in ms to wait for card to accept the packet
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelPutPacket(CIFXHANDLE hChannel, CIFX_PACKET*  ptSendPkt, uint32_t ulTimeout)
{
  int32_t          lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;

  /* Check if another command is active */
  if ( 0 == OS_WaitMutex( ptChannel->tSendMbx.pvSendMBXMutex, ulTimeout))
    return CIFX_DRV_CMD_ACTIVE;

  lRet = DEV_PutPacket(ptChannel, ptSendPkt, ulTimeout);

  /* Release command */
  OS_ReleaseMutex(ptChannel->tSendMbx.pvSendMBXMutex);

  return lRet;
}

/*****************************************************************************/
/*! Gets a packet from the channels mailbox
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ulSize     Size of the return packet buffer
*   \param ptRecvPkt  Returned packet
*   \param ulTimeout  Time in ms to wait for available message
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelGetPacket(CIFXHANDLE hChannel, uint32_t ulSize, CIFX_PACKET* ptRecvPkt, uint32_t ulTimeout)
{
  int32_t          lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;

  /* Check if another command is active */
  if ( 0 == OS_WaitMutex( ptChannel->tRecvMbx.pvRecvMBXMutex, ulTimeout))
    return CIFX_DRV_CMD_ACTIVE;

  lRet = DEV_GetPacket(ptChannel, ptRecvPkt, ulSize, ulTimeout);

  /* Release command */
  OS_ReleaseMutex(ptChannel->tRecvMbx.pvRecvMBXMutex);

  return lRet;
}

/*****************************************************************************/
/*! Gets send packet from the channels mailbox
*   \param hChannel   Channel handle acquired by xChannelOpen
*   \param ulSize     Size of the return packet buffer
*   \param ptRecvPkt  Returned packet
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelGetSendPacket(CIFXHANDLE hChannel, uint32_t ulSize, CIFX_PACKET* ptRecvPkt)
{
  int32_t           lRet        = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel   = (PCHANNELINSTANCE)hChannel;
  CIFX_PACKET*      ptPacket    = (CIFX_PACKET*)ptChannel->tSendMbx.ptSendMailboxStart->abSendMailbox;
  uint32_t          ulCopySize  = 0;

  ulCopySize  = HWIF_READ32(ptChannel->pvDeviceInstance, ptPacket->tHeader.ulLen) + RCX_PACKET_HEADER_SIZE;

  if( ulCopySize > ulSize)
  {
    /* Use the user buffer length if packet does not fit in the user buffer */
    ulCopySize = ulSize;
    lRet = CIFX_BUFFER_TOO_SHORT;
  }

  /* Just copy the available data into the user buffer */
  HWIF_READN(ptChannel->pvDeviceInstance, ptRecvPkt, ptPacket, ulCopySize);

  return lRet;
}

/*****************************************************************************/
/*! Lock the configuration on a communication channel
*   \param hChannel         Channel handle
*   \param ulCmd            CIFX_CONFIGURATION_XXX defines
*   \param pulState         Return locking state
*   \param ulTimeout        Timeout in [ms]
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelConfigLock(CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pulState);

  /* Check if we are in interrupt mode */
  if(!((PDEVICEINSTANCE)(ptChannel->pvDeviceInstance))->fIrqEnabled)
    DEV_ReadHandshakeFlags(ptChannel, 0, 1);

  /* TODO: WAIT until card has recognized the LOCK command */
  UNREFERENCED_PARAMETER(ulTimeout);

  switch (ulCmd)
  {
    case CIFX_CONFIGURATION_LOCK:
    {
      /* Check if the configuration is already LOCKED */
      if( ptChannel->ulDeviceCOSFlags & RCX_COMM_COS_CONFIG_LOCKED)
      {
        /* Configuration already locked */
        *pulState = CIFX_CONFIGURATION_LOCK;
      } else
      {
        lRet = DEV_DoHostCOSChange(ptChannel,
                                   RCX_APP_COS_LOCK_CONFIGURATION | RCX_APP_COS_LOCK_CONFIGURATION_ENABLE,
                                   0,
                                   RCX_APP_COS_LOCK_CONFIGURATION_ENABLE,
                                   CIFX_DEV_CONFIG_LOCK_TIMEOUT,
                                   ulTimeout);

        if(CIFX_NO_ERROR == lRet)
        {
          /* Set actual state */
          *pulState = CIFX_CONFIGURATION_LOCK;
        }
      }
    }
    break;

    case CIFX_CONFIGURATION_UNLOCK:
    {
      /* Check if the configuration is NOT LOCKED  */
      if( !(ptChannel->ulDeviceCOSFlags & RCX_COMM_COS_CONFIG_LOCKED))
      {
        /* Configuration is NOT locked */
        *pulState = CIFX_CONFIGURATION_UNLOCK;
      } else
      {
        lRet = DEV_DoHostCOSChange(ptChannel,
                                   RCX_APP_COS_LOCK_CONFIGURATION_ENABLE,
                                   RCX_APP_COS_LOCK_CONFIGURATION,
                                   RCX_APP_COS_LOCK_CONFIGURATION_ENABLE,
                                   CIFX_DEV_CONFIG_UNLOCK_TIMEOUT,
                                   ulTimeout);

        if(CIFX_NO_ERROR == lRet)
        {
          /* Set actual state */
          *pulState = CIFX_CONFIGURATION_UNLOCK;
        }
      }
    }
    break;

    case CIFX_CONFIGURATION_GETLOCKSTATE:
      /* Get the actual state of the config lock bit */
      if( 0 == (LE32_TO_HOST(HWIF_READ32(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->ulCommunicationCOS)) & RCX_COMM_COS_CONFIG_LOCKED))
      {
        /* Configuration is not locked */
        *pulState = CIFX_CONFIGURATION_UNLOCK;
      } else
      {
        /* Configuration is locked */
        *pulState = CIFX_CONFIGURATION_LOCK;
      }
    break;

    default:
      /* Unknown command */
      lRet = CIFX_INVALID_COMMAND;
    break;

  }

  return lRet;
}

/*****************************************************************************/
/*! Set BUS state off a communication channel
*   \param hChannel         Channel handle
*   \param ulCmd            CIFX_CONFIGURATION_XXX defines
*   \param pulState         Return actual state on CIFX_GET_BUS_STATE
*   \param ulTimeout        Timeout in [ms]
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelBusState(CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout)
{
  int32_t lRet = CIFX_INVALID_PARAMETER;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pulState);

  lRet = DEV_BusState( (PCHANNELINSTANCE)hChannel,
                        ulCmd,
                        pulState,
                        ulTimeout);

  return lRet;
}

/*****************************************************************************/
/*! Reset a communication channel
*   \param hChannel        Channel handle
*   \param ulResetMode     Reset Mode
*   \param ulTimeout       Timeout to wait for reset complete in [ms]
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelReset(CIFXHANDLE  hChannel, uint32_t ulResetMode, uint32_t ulTimeout)
{
  int32_t          lRet;
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);

  /* TODO: Get packet and I/O mutexe before processing a channel init */
  /* TODO: System start via channel ? */
  switch(ulResetMode)
  {
  case CIFX_SYSTEMSTART:
    lRet = DEV_DoSystemStart(ptChannel, ulTimeout);
    #ifdef CIFX_TOOLKIT_TIME
      if (CIFX_NO_ERROR == lRet)
        cifXInitTime((PDEVICEINSTANCE)ptChannel->pvDeviceInstance); 
    #endif
    break;

  case CIFX_CHANNELINIT:
    lRet = DEV_DoChannelInit(ptChannel, ulTimeout);
    break;

  default:
    lRet = CIFX_INVALID_PARAMETER;
    break;
  }

  return lRet;
}

/*****************************************************************************/
/*! Reads I/O Area information for the given Channel
*   \param hChannel         Channel handle
*   \param ulCmd
*   \param ulAreaNumber     Number of area to get information for
*   \param ulSize           Size of returned data structure
*   \param pvData           Pointer to returned data
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelIOInfo(CIFXHANDLE hChannel, uint32_t ulCmd, uint32_t ulAreaNumber, uint32_t ulSize, void* pvData)
{
  int32_t                 lRet            = CIFX_NO_ERROR;
  PCHANNELINSTANCE        ptChannel       = (PCHANNELINSTANCE)hChannel;
  CHANNEL_IO_INFORMATION* ptIoInformation = (CHANNEL_IO_INFORMATION*)pvData;
  
  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pvData);

  if(ulSize != sizeof(*ptIoInformation))
    return CIFX_INVALID_BUFFERSIZE;

  if(!DEV_IsRunning(ptChannel))
  {
    lRet = CIFX_DEV_NOT_RUNNING;
  }

  switch(ulCmd)
  {
    case CIFX_IO_INPUT_AREA:
      {
        if(0 == ptChannel->ulIOInputAreas)
        {
          lRet = CIFX_FUNCTION_NOT_AVAILABLE;

        } else if(ulAreaNumber >= ptChannel->ulIOInputAreas)
        {
          lRet = CIFX_INVALID_PARAMETER;
        } else
        {
          PIOINSTANCE ptIoArea = ptChannel->pptIOInputAreas[ulAreaNumber];

          if(RCX_IO_MODE_DEFAULT != HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bPDInHskMode))
            ptIoInformation->ulIOMode    = HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bPDInHskMode);
          else
            ptIoInformation->ulIOMode    = ptIoArea->usHandshakeMode;

          ptIoInformation->ulTotalSize   = ptIoArea->ulDPMAreaLength;
        }
      }
      break;

    case CIFX_IO_OUTPUT_AREA:
      {
        if(0 == ptChannel->ulIOOutputAreas)
        {
          lRet = CIFX_FUNCTION_NOT_AVAILABLE;

        } else if(ulAreaNumber >= ptChannel->ulIOOutputAreas)
        {
          lRet = CIFX_INVALID_PARAMETER;
        } else
        {
          PIOINSTANCE ptIoArea = ptChannel->pptIOOutputAreas[ulAreaNumber];

          if(RCX_IO_MODE_DEFAULT != HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bPDOutHskMode))
            ptIoInformation->ulIOMode    = HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bPDOutHskMode);
          else
            ptIoInformation->ulIOMode    = ptIoArea->usHandshakeMode;
          ptIoInformation->ulTotalSize   = ptIoArea->ulDPMAreaLength;
        }
      }
      break;

    default:
        lRet = CIFX_INVALID_COMMAND;
      break;
  }

  return lRet;
}

/*****************************************************************************/
/*! Reads the Input data from the channel
*   \param hChannel     Channel handle acquired by xChannelOpen
*   \param ulAreaNumber Number of the I/O Area (0..n)
*   \param ulOffset     Data offset in Input area
*   \param ulDataLen    Length of data to read
*   \param pvData       Buffer to place returned data
*   \param ulTimeout    Timeout in ms to wait for finished I/O Handshake
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelIORead(CIFXHANDLE hChannel, uint32_t ulAreaNumber, uint32_t ulOffset, uint32_t ulDataLen, void* pvData, uint32_t ulTimeout)
{
  PCHANNELINSTANCE ptChannel   = (PCHANNELINSTANCE)hChannel;
  int32_t          lRet        = CIFX_NO_ERROR;
  PIOINSTANCE      ptIOArea    = NULL;
  uint8_t          bIOBitState = RCX_FLAGS_NONE;

  if(!DEV_IsRunning(ptChannel))
    return CIFX_DEV_NOT_RUNNING;

  if(ulAreaNumber >= ptChannel->ulIOInputAreas)
    return CIFX_INVALID_PARAMETER;

  ptIOArea    = ptChannel->pptIOInputAreas[ulAreaNumber];
  bIOBitState = DEV_GetIOBitstate(ptChannel, ptIOArea, 0);

#ifdef CIFX_TOOLKIT_DMA
  /* Check for DMA transfer */
  if( ptChannel->ulDeviceCOSFlags & RCX_COMM_COS_DMA)
  {
    /*------------------------------*/
    /* This is DMA IO data transfer */
    /*------------------------------*/
    /* This is DMACh n */
    PDEVICEINSTANCE   ptDevInst   = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;
    uint32_t          ulDMChIdx   = ptChannel->ulChannelNumber * 2 + eDMA_INPUT_BUFFER_IDX;
    PCIFX_DMABUFFER_T ptDmaInfo   = &ptDevInst->atDmaBuffers[ulDMChIdx];

    if(0 != ulAreaNumber )                                  /* Only support for area 0 in DMA mode */
      return CIFX_DEV_DMA_IO_AREA_NOT_SUPPORTED;

    if( (ulOffset + ulDataLen) > ptDmaInfo->ulSize)
      return CIFX_INVALID_ACCESS_SIZE; /* read size too long */

    /* Check if another command is active */
    if ( !OS_WaitMutex( ptIOArea->pvMutex, ulTimeout))
      return CIFX_DRV_CMD_ACTIVE;

    /* TODO: define read procedure ??Toggle -> Read or READ->Toggle */
    if(RCX_FLAGS_NONE == bIOBitState)
    {
      /* Read data without handshake does not work in DMA operation*/
      lRet = CIFX_DEV_DMA_HANSHAKEMODE_NOT_SUPPORTED;

    } else
    {
      /* Read data */
      if(!DEV_WaitForBitState(ptChannel, ptIOArea->bHandshakeBit, bIOBitState, ulTimeout))
      {
        lRet = CIFX_DEV_EXCHANGE_FAILED;
      } else
      {
        /* Read data */
        OS_Memcpy(  pvData,
                    ((uint8_t*)(ptDmaInfo->pvBuffer)) + ulOffset,
                    ulDataLen);

        /* Lock flag access */
        OS_EnterLock(ptChannel->pvLock);

        /* Read data done */
        DEV_ToggleBit(ptChannel, (uint32_t)(1UL << ptIOArea->bHandshakeBit));

        /* Unlock flag access */
        OS_LeaveLock(ptChannel->pvLock);

        /* Check COMM Flag for return value */
        DEV_IsCommunicating(ptChannel, &lRet);
      }
    }

    /* Release command */
    OS_ReleaseMutex( ptIOArea->pvMutex);

  } else
#endif
  {
    /*---------------------------*/
    /* This is DPM data transfer */
    /*---------------------------*/
    if( (ulOffset + ulDataLen) > ptIOArea->ulDPMAreaLength)
      return CIFX_INVALID_ACCESS_SIZE; /* read size too long */

    /* Check if another command is active */
    if ( !OS_WaitMutex( ptIOArea->pvMutex, ulTimeout))
      return CIFX_DRV_CMD_ACTIVE;

    /* Read data */
    if(RCX_FLAGS_NONE == bIOBitState)
    {
      /* Read data */
      HWIF_READN( ptChannel->pvDeviceInstance,
                  pvData,
                  &ptIOArea->pbDPMAreaStart[ulOffset],
                  ulDataLen);

      /* Check COMM Flag for return value */
      DEV_IsCommunicating(ptChannel, &lRet);

    } else if(!DEV_WaitForBitState(ptChannel, ptIOArea->bHandshakeBit, bIOBitState, ulTimeout))
    {
      lRet = CIFX_DEV_EXCHANGE_FAILED;
    } else
    {
      /* Read data */
      HWIF_READN( ptChannel->pvDeviceInstance,
                  pvData,
                  &ptIOArea->pbDPMAreaStart[ulOffset],
                  ulDataLen);

      /* Lock flag access */
      OS_EnterLock(ptChannel->pvLock);

      /* Read data done */
      DEV_ToggleBit(ptChannel, (uint32_t)(1UL << ptIOArea->bHandshakeBit));

      /* Unlock flag access */
      OS_LeaveLock(ptChannel->pvLock);

      /* Check COMM Flag for return value */
      DEV_IsCommunicating(ptChannel, &lRet);
    }

    /* Release command */
    OS_ReleaseMutex( ptIOArea->pvMutex);
  }

  return lRet;
}

/*****************************************************************************/
/*! Writes the Output data to the channel
*   \param hChannel     Channel handle acquired by xChannelOpen
*   \param ulAreaNumber Number of the I/O Area (0..n)
*   \param ulOffset     Data offset in Output area
*   \param ulDataLen    Length of data to send
*   \param pvData       Buffer containing send data
*   \param ulTimeout    Timeout in ms to wait for handshake completion
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelIOWrite(CIFXHANDLE hChannel, uint32_t ulAreaNumber, uint32_t ulOffset, uint32_t ulDataLen, void* pvData, uint32_t ulTimeout)
{
  PCHANNELINSTANCE ptChannel   = (PCHANNELINSTANCE)hChannel;
  int32_t          lRet        = CIFX_NO_ERROR;
  PIOINSTANCE      ptIOArea    = NULL;
  uint8_t          bIOBitState = RCX_FLAGS_NONE;

  if(!DEV_IsRunning(ptChannel))
    return CIFX_DEV_NOT_RUNNING;
  if(ulAreaNumber >= ptChannel->ulIOOutputAreas)
    return CIFX_INVALID_PARAMETER;

  ptIOArea    = ptChannel->pptIOOutputAreas[ulAreaNumber];
  bIOBitState = DEV_GetIOBitstate(ptChannel, ptIOArea, 1);

#ifdef CIFX_TOOLKIT_DMA
  /* Check for DMA transfer */
  if( ptChannel->ulDeviceCOSFlags & RCX_COMM_COS_DMA)
  {
    /*------------------------------*/
    /* This is DMA IO data transfer */
    /*------------------------------*/
    /* This is DMACh n+1 */
    PDEVICEINSTANCE   ptDevInst   = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;
    uint32_t          ulDMChIdx   = ptChannel->ulChannelNumber * 2 + eDMA_OUTPUT_BUFFER_IDX;
    PCIFX_DMABUFFER_T ptDmaInfo   = &ptDevInst->atDmaBuffers[ulDMChIdx];

    if(0 != ulAreaNumber )                                  /* Only support for area 0 in DMA mode */
      return CIFX_DEV_DMA_IO_AREA_NOT_SUPPORTED;

    if( (ulOffset + ulDataLen) > ptDmaInfo->ulSize)
      return CIFX_INVALID_ACCESS_SIZE; /* read size too long */

    /* Check if another command is active */
    if ( !OS_WaitMutex( ptIOArea->pvMutex, ulTimeout))
      return CIFX_DRV_CMD_ACTIVE;

    /* Read data */
    /* TODO: define read procedure ??Toggle -> Read or READ->Toggle */
    if(RCX_FLAGS_NONE == bIOBitState)
    {
      /* Read data without handshake does not work in DMA operation*/
      lRet = CIFX_DEV_DMA_HANSHAKEMODE_NOT_SUPPORTED;

    } else
    {
      if(!DEV_WaitForBitState(ptChannel, ptIOArea->bHandshakeBit, bIOBitState, ulTimeout))
      {
        lRet = CIFX_DEV_EXCHANGE_FAILED;
      } else
      {
        /* Read data */
        OS_Memcpy( (((uint8_t*)(ptDmaInfo->pvBuffer)) + ulOffset),
                   pvData,
                   ulDataLen);

        /* Lock flag access */
        OS_EnterLock(ptChannel->pvLock);

        /* Read data done */
        DEV_ToggleBit(ptChannel, (uint32_t)(1UL << ptIOArea->bHandshakeBit));

        /* Unlock flag access */
        OS_LeaveLock(ptChannel->pvLock);

        /* Check COMM Flag for return value */
        DEV_IsCommunicating(ptChannel, &lRet);
      }
    }

    /* Release command */
    OS_ReleaseMutex( ptIOArea->pvMutex);

  } else
#endif
  {
    /*---------------------------*/
    /* This is DPM data transfer */
    /*---------------------------*/
    if( (ulOffset + ulDataLen) > ptIOArea->ulDPMAreaLength)
      return CIFX_INVALID_ACCESS_SIZE; /* read size too long */

    /* Check if another command is active */
    if ( !OS_WaitMutex( ptIOArea->pvMutex, ulTimeout))
      return CIFX_DRV_CMD_ACTIVE;

    /* Read data */
    /* TODO: define write procedure ??Toggle -> Write or Write->Toggle */
    if(RCX_FLAGS_NONE == bIOBitState)
    {
      /* Read data without handshake */
      HWIF_WRITEN(  ptChannel->pvDeviceInstance,
                   &ptIOArea->pbDPMAreaStart[ulOffset],
                    pvData,
                    ulDataLen);

      /* Check COMM Flag for return value */
      DEV_IsCommunicating(ptChannel, &lRet);

    } else
    {
      if(!DEV_WaitForBitState(ptChannel, ptIOArea->bHandshakeBit, bIOBitState, ulTimeout))
      {
        lRet = CIFX_DEV_EXCHANGE_FAILED;
      } else
      {
        /* Read data */
        HWIF_WRITEN(  ptChannel->pvDeviceInstance,
                     &ptIOArea->pbDPMAreaStart[ulOffset],
                      pvData,
                      ulDataLen);

        /* Lock flag access */
        OS_EnterLock(ptChannel->pvLock);

        /* Read data done */
        DEV_ToggleBit(ptChannel, (uint32_t)(1UL << ptIOArea->bHandshakeBit));

        /* Unlock flag access */
        OS_LeaveLock(ptChannel->pvLock);

        /* Check COMM Flag for return value */
        DEV_IsCommunicating(ptChannel, &lRet);
      }
    }

    /* Release command */
    OS_ReleaseMutex( ptIOArea->pvMutex);
  }

  return lRet;
}

/*****************************************************************************/
/*! Read back Send Data Area from channel
*   \param hChannel     Channel handle acquired by xChannelOpen
*   \param ulAreaNumber Number of the I/O Area (0..n)
*   \param ulOffset     Data start offset
*   \param ulDataLen    Data length to read
*   \param pvData       Data buffer
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelIOReadSendData(CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulOffset, uint32_t ulDataLen, void* pvData)
{
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;
  int32_t          lRet      = CIFX_NO_ERROR;

#ifdef CIFX_TOOLKIT_DMA

  /* Check for DMA transfer */
  if( ptChannel->ulDeviceCOSFlags & RCX_COMM_COS_DMA)
  {
    /* This is DMACh n */
    PDEVICEINSTANCE   ptDevInst   = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;
    uint32_t          ulDMChIdx   = ptChannel->ulChannelNumber * 2 + eDMA_OUTPUT_BUFFER_IDX;  /* We reading the Output buffer */
    PCIFX_DMABUFFER_T ptDmaInfo   = &ptDevInst->atDmaBuffers[ulDMChIdx];

    if(0 != ulAreaNumber )                                  /* Only support for area 0 in DMA mode */
      return CIFX_DEV_DMA_IO_AREA_NOT_SUPPORTED;

    if( (ulOffset + ulDataLen) > ptDmaInfo->ulSize)
      return CIFX_INVALID_ACCESS_SIZE;                      /* read size too long */

    /* Read data */
    OS_Memcpy(  pvData,
                ((uint8_t*)(ptDmaInfo->pvBuffer)) + ulOffset,
                ulDataLen);
  } else

#endif

  {
    PIOINSTANCE ptIOArea  = NULL;

    if(ulAreaNumber >= ptChannel->ulIOOutputAreas)
      return CIFX_INVALID_PARAMETER;

    ptIOArea = ptChannel->pptIOOutputAreas[ulAreaNumber];

    if( (ulOffset + ulDataLen) > ptIOArea->ulDPMAreaLength)
      return CIFX_INVALID_ACCESS_SIZE; /* read size too long */

    /* Read data */
    HWIF_READN(ptChannel->pvDeviceInstance,
               pvData,
               &ptIOArea->pbDPMAreaStart[ulOffset],
               ulDataLen);
  }

  return lRet;
}

/*****************************************************************************/
/*! Read/Write Control block
*   \param hChannel       Handle to the channel
*   \param ulCmd          CIFX_CMD_READ_DATA/CIFX_CMD_WRITE_DATA
*   \param ulOffset       Start offset of read/write
*   \param ulDataLen      Length of data to read/write
*   \param pvData         Buffer to copy from/to
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelControlBlock(CIFXHANDLE hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pvData);

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;

    /* Check if CONTROL block is available */
  } else if(NULL == ptChannel->ptControlBlock)
  {
    lRet = CIFX_FUNCTION_NOT_AVAILABLE;
  } else
  {
    lRet = DEV_ReadWriteBlock(ptChannel,
                              (void*)ptChannel->ptControlBlock,
                              ulOffset,
                              ptChannel->ulControlBlockSize,
                              pvData,
                              ulDataLen,
                              ulCmd,
                              1);

    cifXConvertEndianess(pvData,
                         ulDataLen,
                         s_atControlBlock,
                         sizeof(s_atControlBlock) / sizeof(s_atControlBlock[0]));
  }

  return lRet;
}

/*****************************************************************************/
/*! Read/Write Common status block
*   \param hChannel       Handle to the channel
*   \param ulCmd          CIFX_CMD_READ_DATA
*   \param ulOffset       Start offset of read
*   \param ulDataLen      Length of data to read
*   \param pvData         Buffer to copy to
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelCommonStatusBlock(CIFXHANDLE hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pvData);

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;

    /* Check if CONTROL block is available */
  } else if(NULL == ptChannel->ptCommonStatusBlock)
  {
    lRet = CIFX_FUNCTION_NOT_AVAILABLE;
  } else
  {
    lRet = DEV_ReadWriteBlock(ptChannel,
                              (void*)ptChannel->ptCommonStatusBlock,
                              ulOffset,
                              ptChannel->ulCommonStatusSize,
                              pvData,
                              ulDataLen,
                              ulCmd,
                              0);
  }

  cifXConvertEndianess(pvData,
                       ulDataLen,
                       s_atCommonStatusBlock,
                       sizeof(s_atCommonStatusBlock) / sizeof(s_atCommonStatusBlock[0]));

  return lRet;
}

/*****************************************************************************/
/*! Read Extended status block
*   \param hChannel       Handle to the channel
*   \param ulCmd          CIFX_CMD_READ_DATA
*   \param ulOffset       Start offset of read
*   \param ulDataLen      Length of data to read
*   \param pvData         Buffer to copy to
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelExtendedStatusBlock(CIFXHANDLE hChannel, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pvData);

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;

    /* Check if CONTROL block is available */
  } else if(NULL == ptChannel->ptExtendedStatusBlock)
  {
    lRet = CIFX_FUNCTION_NOT_AVAILABLE;
  } else
  {
    lRet = DEV_ReadWriteBlock(ptChannel,
                              (void*)ptChannel->ptExtendedStatusBlock,
                              ulOffset,
                              ptChannel->ulExtendedStatusSize,
                              pvData,
                              ulDataLen,
                              ulCmd,
                              0);
  }

  return lRet;
}

/*****************************************************************************/
/*! Read a user block
*   \param hChannel       Handle to the channel
*   \param ulCmd          CIFX_CMD_READ_DATA
*   \param ulAreaNumber   Userblock number
*   \param ulOffset       Start offset of read
*   \param ulDataLen      Length of data to read
*   \param pvData         Buffer to copy to
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelUserBlock(CIFXHANDLE  hChannel, uint32_t ulAreaNumber, uint32_t ulCmd, uint32_t ulOffset, uint32_t ulDataLen, void* pvData)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pvData);

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;

    /* Check if CONTROL block is available */
  } else if( (ulAreaNumber >= ptChannel->ulUserAreas) ||
             (NULL == ptChannel->pptUserAreas[ulAreaNumber]) )
  {
    lRet = CIFX_FUNCTION_NOT_AVAILABLE;
  } else
  {
    PUSERINSTANCE ptUserInstance = ptChannel->pptUserAreas[ulAreaNumber];

    lRet = DEV_ReadWriteBlock(ptChannel,
                              (void*)ptUserInstance->pbUserBlockStart,
                              ulOffset,
                              ptUserInstance->ulUserBlockLength,
                              pvData,
                              ulDataLen,
                              ulCmd,
                              1);
  }

  return lRet;
}

/*****************************************************************************/
/*! Gets a pointer to an IO Area
*   \param hChannel       Handle to the channel
*   \param ulCmd          CIFX_MEM_PTR_OPEN/CIFX_MEM_PTR_CLOSE
*   \param pvMemoryInfo   Pointer to requested memory structure
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelPLCMemoryPtr(CIFXHANDLE hChannel, uint32_t ulCmd, void* pvMemoryInfo)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pvMemoryInfo);

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
    return CIFX_DRV_CHANNEL_NOT_INITIALIZED;

  if( (0 == ptChannel->ulIOInputAreas) ||
      (0 == ptChannel->ulIOOutputAreas)  )
    /* No IO blocks defined */
    return CIFX_FUNCTION_NOT_AVAILABLE;

#ifdef CIFX_TOOLKIT_DMA

  /* Check for DMA transfer */
  if( ptChannel->ulDeviceCOSFlags & RCX_COMM_COS_DMA)
  {
    /*------------------------------*/
    /* This is DMA IO data transfer */
    /*------------------------------*/
    /* This is DMACh n */
    PDEVICEINSTANCE         ptDevInst       = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;
    PLC_MEMORY_INFORMATION* ptMemory        = (PLC_MEMORY_INFORMATION*)pvMemoryInfo;
    PCIFX_DMABUFFER_T       ptDmaInfo       = NULL;
    void*                   pvDMABuffer     = NULL;
    uint32_t                ulDMChIdx       = 0;

    if(0 != ptMemory->ulAreaNumber)
    {
      /* Invalid IO area */
      lRet = CIFX_DEV_DMA_IO_AREA_NOT_SUPPORTED;  /* Only support for area 0 in DMA mode */
    } else
    {
      if(ptMemory->ulAreaDefinition == CIFX_IO_INPUT_AREA)
      {
        ulDMChIdx    = ptChannel->ulChannelNumber * 2 + eDMA_INPUT_BUFFER_IDX;
        ptDmaInfo    = &ptDevInst->atDmaBuffers[ulDMChIdx];
        pvDMABuffer  = ptDmaInfo->pvBuffer;
      } else
      {
        ulDMChIdx    = ptChannel->ulChannelNumber * 2 + eDMA_OUTPUT_BUFFER_IDX;
        ptDmaInfo    = &ptDevInst->atDmaBuffers[ulDMChIdx];
        pvDMABuffer  = ptDmaInfo->pvBuffer;
      }

      /* Check user command */
      switch(ulCmd)
      {
        case CIFX_MEM_PTR_OPEN:
        {
          void*     pvMappedDPM = NULL;
          void*     pvDPM       = pvDMABuffer;
          uint32_t  ulDPMSize   = ptDmaInfo->ulSize;

          /* Return global memory information */
          if(NULL == (ptMemory->pvMemoryID = OS_MapUserPointer(pvDPM, ulDPMSize, &pvMappedDPM, ptDevInst->pvOSDependent)))
          {
            lRet = CIFX_MEMORY_MAPPING_FAILED;
          } else
          {
            *(ptMemory->ppvMemoryPtr)         = (void*)pvMappedDPM;
            *(ptMemory->pulIOAreaStartOffset) = 0;                    /* In DMA mode, we don't have a DPM start offeset */
            *(ptMemory->pulIOAreaSize)        = ulDPMSize;
          }
        }
        break;

        case CIFX_MEM_PTR_CLOSE:
        {
          if(!OS_UnmapUserPointer(ptMemory->pvMemoryID, ptDevInst->pvOSDependent))
          {
            lRet = CIFX_INVALID_HANDLE;
          } else
          {
            ptMemory->pvMemoryID              = NULL;
            *(ptMemory->ppvMemoryPtr)         = NULL;
            *(ptMemory->pulIOAreaStartOffset) = 0;
            *(ptMemory->pulIOAreaSize)        = 0;
          }
        }
        break;

        default:
          lRet = CIFX_INVALID_COMMAND;
        break;
      } /* end switch */
    }
  } else

#endif

  {
    PDEVICEINSTANCE         ptDevInst       = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;
    PLC_MEMORY_INFORMATION* ptMemory        = (PLC_MEMORY_INFORMATION*)pvMemoryInfo;
    PIOINSTANCE*            pptIOInstances  = NULL;
    uint32_t                ulAreaCount     = 0;

    if(ptMemory->ulAreaDefinition == CIFX_IO_INPUT_AREA)
    {
      ulAreaCount = ptChannel->ulIOInputAreas;
      pptIOInstances = ptChannel->pptIOInputAreas;

    } else
    {
      ulAreaCount = ptChannel->ulIOOutputAreas;
      pptIOInstances = ptChannel->pptIOOutputAreas;
    }

    /* Check if IO area is avaliable */
    if(ptMemory->ulAreaNumber >= ulAreaCount)
    {
      /* Invalid IO area */
      lRet = CIFX_INVALID_PARAMETER;
    } else
    {
      /* Check user command */
      switch(ulCmd)
      {
        case CIFX_MEM_PTR_OPEN:
        {
          void*    pvMappedDPM  = NULL;
          void*    pvDPM        = pptIOInstances[ptMemory->ulAreaNumber]->pbDPMAreaStart;
          uint32_t ulDPMSize    = pptIOInstances[ptMemory->ulAreaNumber]->ulDPMAreaLength;

          /* Return global memory information */
          if(NULL == (ptMemory->pvMemoryID = OS_MapUserPointer(pvDPM, ulDPMSize, &pvMappedDPM, ptDevInst->pvOSDependent)))
          {
            lRet = CIFX_MEMORY_MAPPING_FAILED;
          } else
          {
            *(ptMemory->ppvMemoryPtr)         = (void*)pvMappedDPM;
            *(ptMemory->pulIOAreaStartOffset) = (uint32_t)(pptIOInstances[ptMemory->ulAreaNumber]->pbDPMAreaStart -
                                                                ptChannel->pbDPMChannelStart);
            *(ptMemory->pulIOAreaSize)        = ulDPMSize;
          }
        }
        break;

        case CIFX_MEM_PTR_CLOSE:
        {
          if(!OS_UnmapUserPointer(ptMemory->pvMemoryID, ptDevInst->pvOSDependent))
          {
            lRet = CIFX_INVALID_HANDLE;
          } else
          {
            ptMemory->pvMemoryID              = NULL;
            *(ptMemory->ppvMemoryPtr)         = NULL;
            *(ptMemory->pulIOAreaStartOffset) = 0;
            *(ptMemory->pulIOAreaSize)        = 0;
          }
        }
        break;

        default:
          lRet = CIFX_INVALID_COMMAND;
        break;
      } /* end switch */
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Checks if the given IO Area is ready for the next handshake
*   \param hChannel       Handle to the channel
*   \param ulAreaNumber   Area to check
*   \param pulReadState   Returned state of the area (!=0 means area is ready)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelPLCIsReadReady(CIFXHANDLE hChannel, uint32_t ulAreaNumber, uint32_t* pulReadState)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;
  } else if(0 == ptChannel->ulIOInputAreas)
  {
    lRet = CIFX_FUNCTION_NOT_AVAILABLE;
  } else
  {
    /* Check if IO area is avaliable */
    if(ulAreaNumber >= ptChannel->ulIOInputAreas)
    {
      lRet = CIFX_INVALID_PARAMETER;
    } else
    {
      /* Check if the device is communication. If only the COM flag is missing, we return the current bit state */
      DEV_IsCommunicating(ptChannel, &lRet);

      if( (lRet != CIFX_DEV_NOT_READY) &&
          (lRet != CIFX_DEV_NOT_RUNNING) )
      {
        /* Read back the send data area */
        PIOINSTANCE ptIOInst    = ptChannel->pptIOInputAreas[ulAreaNumber];
        uint8_t     bIOBitState = DEV_GetIOBitstate(ptChannel, ptIOInst, 0);

        *pulReadState = 0;

        if( (RCX_FLAGS_NONE == bIOBitState)  ||
            (DEV_GetHandshakeBitState(ptChannel, (uint32_t)(1UL << ptIOInst->bHandshakeBit)) == bIOBitState) )
        {
          *pulReadState = 1;
        }
      }
    }
  }

  /* Assuming that the request was handled */
  return lRet;
}

/*****************************************************************************/
/*! Checks if the given IO Area is ready for the next handshake
*   \param hChannel       Handle to the channel
*   \param ulAreaNumber   Area to check
*   \param pulWriteState  Returned state of the area (!=0 means area is ready)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelPLCIsWriteReady(CIFXHANDLE hChannel, uint32_t ulAreaNumber, uint32_t* pulWriteState)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;
  } else if(0 == ptChannel->ulIOOutputAreas)
  {
    lRet = CIFX_FUNCTION_NOT_AVAILABLE;
  } else
  {
    /* Check if IO area is avaliable */
    if(ulAreaNumber >= ptChannel->ulIOOutputAreas)
    {
      lRet = CIFX_INVALID_PARAMETER;
    } else
    {
      /* Check if the device is communication. If only the COM flag is missing, we return the current bit state */
      DEV_IsCommunicating(ptChannel, &lRet);

      if( (lRet != CIFX_DEV_NOT_READY) &&
          (lRet != CIFX_DEV_NOT_RUNNING) )
      {
        /* Read back the send data area */
        PIOINSTANCE ptIOInst    = ptChannel->pptIOOutputAreas[ulAreaNumber];
        uint8_t     bIOBitState = DEV_GetIOBitstate(ptChannel, ptIOInst, 1);

        *pulWriteState = 0;

        if( (RCX_FLAGS_NONE == bIOBitState)  ||
            (DEV_GetHandshakeBitState(ptChannel, (uint32_t)(1UL << ptIOInst->bHandshakeBit)) == bIOBitState) )
        {
          *pulWriteState = 1;
        }
      }
    }
  }

  /* Assuming that the request was handled */
  return lRet;
}

/*****************************************************************************/
/*! Toggles the Handshake bit for the given IO Output Area
*   \param hChannel       Handle to the channel
*   \param ulAreaNumber   Areanumber
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelPLCActivateWrite(CIFXHANDLE hChannel, uint32_t ulAreaNumber)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;
  } else if(0 == ptChannel->ulIOOutputAreas)
  {
    lRet = CIFX_FUNCTION_NOT_AVAILABLE;
  } else
  {
    /* Check if IO area is avaliable */
    if(ulAreaNumber >= ptChannel->ulIOOutputAreas)
    {
      lRet = CIFX_INVALID_PARAMETER;
    } else
    {
      /* Check if the device is communication. If only the COM flag is missing, we toggle the bits */
      DEV_IsCommunicating(ptChannel, &lRet);

      if( (lRet != CIFX_DEV_NOT_READY) &&
          (lRet != CIFX_DEV_NOT_RUNNING) )
      {
        PIOINSTANCE ptIOInst = ptChannel->pptIOOutputAreas[ulAreaNumber];

        /* Lock flag access */
        OS_EnterLock(ptChannel->pvLock);

        DEV_ToggleBit(ptChannel, (uint32_t)(1UL << ptIOInst->bHandshakeBit));

        /* Unlock flag access */
        OS_LeaveLock(ptChannel->pvLock);
      }
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Toggles the Handshake bit for the given IO Input Area
*   \param hChannel       Handle to the channel
*   \param ulAreaNumber   Areanumber
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelPLCActivateRead(CIFXHANDLE hChannel, uint32_t ulAreaNumber)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;
  } else if(0 == ptChannel->ulIOInputAreas)
  {
    lRet = CIFX_FUNCTION_NOT_AVAILABLE;
  } else
  {
    /* Check if IO area is avaliable */
    if(ulAreaNumber >= ptChannel->ulIOInputAreas)
    {
      lRet = CIFX_INVALID_PARAMETER;
    } else
    {
      /* Check if the device is communication. If only the COM flag is missing, we toggle the bits */
      DEV_IsCommunicating(ptChannel, &lRet);

      if( (lRet != CIFX_DEV_NOT_READY) &&
          (lRet != CIFX_DEV_NOT_RUNNING) )
      {
        PIOINSTANCE ptIOInst = ptChannel->pptIOInputAreas[ulAreaNumber];

        /* Lock flag access */
        OS_EnterLock(ptChannel->pvLock);

        DEV_ToggleBit(ptChannel, (uint32_t)(1UL << ptIOInst->bHandshakeBit));

        /* Unlock flag access */
        OS_LeaveLock(ptChannel->pvLock);
      }
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Open a connection to the driver
*   \param phDriver     Returned handle to the driver
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xDriverOpen(CIFXHANDLE* phDriver)
{
  if(!g_tDriverInfo.fInitialized)
    return CIFX_DRV_DRIVER_NOT_LOADED;

  CHECK_POINTER(phDriver);

  *phDriver = &g_tDriverInfo;

  ++g_tDriverInfo.ulOpenCount;

  return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! Close a connection to the driver
*   \param hDriver     Handle to connection, that is being closed
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xDriverClose(CIFXHANDLE hDriver)
{
  if(!g_tDriverInfo.fInitialized)
    return CIFX_DRV_DRIVER_NOT_LOADED;

  if(g_tDriverInfo.ulOpenCount == 0)
    return CIFX_DRV_NOT_OPENED;
  
  CHECK_DRIVERHANDLE(hDriver);

  --g_tDriverInfo.ulOpenCount;

  return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! Query Driver information
*   \param hDriver      Handle to the driver
*   \param ulSize       Size of the passed DRIVER_INFORMATION Structure
*   \param pvDriverInfo Pointer to returned data (DRIVER_INFORMATION
*                       structure)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xDriverGetInformation(CIFXHANDLE hDriver, uint32_t ulSize, void* pvDriverInfo)
{
  DRIVER_INFORMATION* ptDriverInfo = (DRIVER_INFORMATION*)pvDriverInfo;

  if(g_tDriverInfo.ulOpenCount == 0)
    return CIFX_DRV_NOT_OPENED;

  CHECK_DRIVERHANDLE(hDriver);
  CHECK_POINTER(pvDriverInfo);

  if(ulSize < (uint32_t)sizeof(*ptDriverInfo))
    return CIFX_INVALID_BUFFERSIZE;

  ptDriverInfo->ulBoardCnt = g_ulDeviceCount;
  OS_Strncpy(ptDriverInfo->abDriverVersion, TOOLKIT_VERSION, sizeof(ptDriverInfo->abDriverVersion));

  return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! Query human readable error description
*   \param lError       Error to look up
*   \param szBuffer     Pointer to return data
*   \param ulBufferLen  Length of return buffer
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xDriverGetErrorDescription(int32_t lError, char* szBuffer, uint32_t ulBufferLen)
{
  int32_t lRet = CIFX_FUNCTION_FAILED;
  int     iIdx = 0;

  CHECK_POINTER(szBuffer);
  
  for(iIdx = 0; iIdx < (int)(sizeof(s_atErrorToDescrTable) / sizeof(s_atErrorToDescrTable[0])); ++iIdx)
  {
    if(s_atErrorToDescrTable[iIdx].lError == lError)
    {
      OS_Strncpy(szBuffer, s_atErrorToDescrTable[iIdx].szErrorDescr, ulBufferLen);
      lRet = CIFX_NO_ERROR;
      break;
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Enumerate over all handled boards/devices
*   \param hDriver      Driver handle
*   \param ulBoard      Board number (incremented from 0 up)
*   \param ulSize       Size of return buffer
*   \param pvBoardInfo  Return buffer (BOARD_INFORMATION structure)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xDriverEnumBoards(CIFXHANDLE hDriver, uint32_t ulBoard, uint32_t ulSize, void* pvBoardInfo)
{
  BOARD_INFORMATION*    ptBoardInfo   = (BOARD_INFORMATION*)pvBoardInfo;
  PDEVICEINSTANCE       ptDevInstance = NULL;
  NETX_SYSTEM_CHANNEL*  ptSysChannel  = NULL;

  if(g_tDriverInfo.ulOpenCount == 0)
    return CIFX_DRV_NOT_OPENED;

  CHECK_DRIVERHANDLE(hDriver);
  CHECK_POINTER(pvBoardInfo);

  if(ulSize < (uint32_t)sizeof(*ptBoardInfo))
    return CIFX_INVALID_BUFFERSIZE;

  if(ulBoard >= g_ulDeviceCount)
    return CIFX_INVALID_BOARD;

  ptDevInstance = g_pptDevices[ulBoard];
  ptSysChannel  = (NETX_SYSTEM_CHANNEL*)ptDevInstance->pbDPM;

  OS_Strncpy(ptBoardInfo->abBoardName,  ptDevInstance->szName,  sizeof(ptBoardInfo->abBoardName));
  OS_Strncpy(ptBoardInfo->abBoardAlias, ptDevInstance->szAlias, sizeof(ptBoardInfo->abBoardAlias));
  ptBoardInfo->ulBoardID         = ulBoard;

  {
    ptBoardInfo->ulSystemError     = LE32_TO_HOST(HWIF_READ32(ptDevInstance, ptSysChannel->tSystemState.ulSystemError));

    ptBoardInfo->ulPhysicalAddress = ptDevInstance->ulPhysicalAddress;
    ptBoardInfo->ulIrqNumber       = (uint32_t)ptDevInstance->bIrqNumber;
    ptBoardInfo->bIrqEnabled       = ptDevInstance->fIrqEnabled? 1 : 0;
    ptBoardInfo->ulDpmTotalSize    = ptDevInstance->ulDPMSize;
    ptBoardInfo->ulChannelCnt      = ptDevInstance->ulCommChannelCount;

    HWIF_READN(ptDevInstance, &ptBoardInfo->tSystemInfo, &ptSysChannel->tSystemInfo, sizeof(ptBoardInfo->tSystemInfo));
  }

  cifXConvertEndianess(&ptBoardInfo->tSystemInfo,
                       sizeof(ptBoardInfo->tSystemInfo),
                       s_atSystemInfoBlock,
                       sizeof(s_atSystemInfoBlock) / sizeof(s_atSystemInfoBlock[0]));

  return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! Enumerate over all channels on the given boards
*   \param hDriver        Driver handle
*   \param ulBoard        Board number
*   \param ulChannel      Channel number (incremented from 0 up)
*   \param ulSize         Size of return buffer
*   \param pvChannelInfo  Return buffer (CHANNEL_INFORMATION structure)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xDriverEnumChannels(CIFXHANDLE  hDriver, uint32_t ulBoard, uint32_t ulChannel, uint32_t ulSize, void* pvChannelInfo)
{
  CHANNEL_INFORMATION*  ptChannelInfo = (CHANNEL_INFORMATION*)pvChannelInfo;
  PDEVICEINSTANCE       ptDevInstance = NULL;
  PCHANNELINSTANCE      ptChannel     = NULL;
  int32_t               lRet          = CIFX_NO_ERROR;

  if(g_tDriverInfo.ulOpenCount == 0)
    return CIFX_DRV_NOT_OPENED;

  CHECK_DRIVERHANDLE(hDriver);
  CHECK_POINTER(pvChannelInfo);

  if(ulSize < (uint32_t)sizeof(*ptChannelInfo))
    return CIFX_INVALID_BUFFERSIZE;

  if(ulBoard >= g_ulDeviceCount)
    return CIFX_INVALID_BOARD;

  ptDevInstance = g_pptDevices[ulBoard];

  if(ulChannel >= ptDevInstance->ulCommChannelCount)
    return CIFX_NO_MORE_ENTRIES;

  ptChannel = ptDevInstance->pptCommChannels[ulChannel];

  /* Read the channel information */
  lRet = xChannelInfo( ptChannel, ulSize, ptChannelInfo);

  return lRet;
}

/*! **************************************************************************
* Get/Return a memory pointer to the boards dual-port memory
*   \param hDriver      Driver handle
*   \param ulBoard      The board number (0)
*   \param ulCmd        Function command (CIFX_MEM_PTR_OPEN/CIFX_MEM_PTR_CLOSE)
*   \param pvMemoryInfo Memory information structure
*   \return CIFX_NO_ERROR on success
******************************************************************************/
int32_t APIENTRY xDriverMemoryPointer(CIFXHANDLE hDriver, uint32_t ulBoard, uint32_t ulCmd,void* pvMemoryInfo)
{
  int32_t             lRet     = CIFX_NO_ERROR;
  MEMORY_INFORMATION* ptMemory = (MEMORY_INFORMATION*)pvMemoryInfo;

  if(0 == g_tDriverInfo.ulOpenCount)
    return CIFX_DRV_NOT_OPENED;

  CHECK_DRIVERHANDLE(hDriver);
  CHECK_POINTER(pvMemoryInfo);

  /* We only support 1 board */
  if(ulBoard >= g_ulDeviceCount)
  {
    lRet = CIFX_INVALID_BOARD;
  } else
  {
    /* Get the device instance */
    PDEVICEINSTANCE ptDevInst = g_pptDevices[ulBoard];
    switch(ulCmd)
    {
      case CIFX_MEM_PTR_OPEN:
        {
          void* pvMappedDPM       = NULL;

          *(ptMemory->pulMemorySize) = 0;
          *(ptMemory->ppvMemoryPtr)  = NULL;

          /* Return global memory information */
          if(NULL == (ptMemory->pvMemoryID = OS_MapUserPointer(ptDevInst->pbDPM, ptDevInst->ulDPMSize, &pvMappedDPM, ptDevInst->pvOSDependent)))
          {
            lRet = CIFX_MEMORY_MAPPING_FAILED;
          } else
          {
            *(ptMemory->ppvMemoryPtr)  = (void*)pvMappedDPM;
            *(ptMemory->pulMemorySize) = ptDevInst->ulDPMSize;
          }

          /* Check requested channel */
          if(ptMemory->ulChannel != CIFX_NO_CHANNEL)
          {
            /* Process channel information */
            if(ptMemory->ulChannel >= ptDevInst->ulCommChannelCount)
            {
              *(ptMemory->pulChannelStartOffset) = 0;
              *(ptMemory->pulChannelSize)        = 0;
              lRet = CIFX_INVALID_CHANNEL;
            } else
            {
              PCHANNELINSTANCE ptChannel = ptDevInst->pptCommChannels[ptMemory->ulChannel];
              uint32_t    ulOffset  = (uint32_t)(ptChannel->pbDPMChannelStart -
                                                           ptDevInst->pbDPM);

              /* Get Channel information */
              *(ptMemory->pulChannelSize)        = ptChannel->ulDPMChannelLength;
              *(ptMemory->pulChannelStartOffset) = ulOffset;
            }
          }
        }
        break;

      case CIFX_MEM_PTR_CLOSE:
        /* Clear user area */
        if(!OS_UnmapUserPointer(ptMemory->pvMemoryID, ptDevInst->pvOSDependent))
        {
          lRet = CIFX_INVALID_HANDLE;
        } else
        {
          ptMemory->pvMemoryID       = NULL;
          *(ptMemory->ppvMemoryPtr)  = NULL;
          *(ptMemory->pulMemorySize) = 0;
          *(ptMemory->ppvMemoryPtr)  = NULL;
        }
        break;

      default:
        lRet = CIFX_INVALID_COMMAND;
        break;
    } /* end switch */
  }

  return lRet;
}

/*****************************************************************************/
/*! Get Channel information on an open channel
*   \param hChannel       Handle to the channel
*   \param ulSize         Size of return buffer
*   \param pvChannelInfo  Return buffer (CHANNEL_INFORMATION structure)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelInfo(CIFXHANDLE hChannel, uint32_t ulSize, void* pvChannelInfo)
{
  CHANNEL_INFORMATION*  ptChannelInfo = (CHANNEL_INFORMATION*)pvChannelInfo;
  PCHANNELINSTANCE      ptChannel     = (PCHANNELINSTANCE)hChannel;
  PDEVICEINSTANCE       ptDevInstance = NULL;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pvChannelInfo);

  ptDevInstance = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;

  if(ulSize < (uint32_t)sizeof(*ptChannelInfo))
    return CIFX_INVALID_BUFFERSIZE;

  OS_Strncpy(ptChannelInfo->abBoardName,
             ptDevInstance->szName,
             (uint32_t)sizeof(ptChannelInfo->abBoardName));
  OS_Strncpy(ptChannelInfo->abBoardAlias,
             ptDevInstance->szAlias,
             (uint32_t)sizeof(ptChannelInfo->abBoardAlias));

  ptChannelInfo->ulDeviceNumber   = ptDevInstance->ulDeviceNumber;
  ptChannelInfo->ulSerialNumber   = ptDevInstance->ulSerialNumber;

  ptChannelInfo->usFWMajor        = ptChannel->tFirmwareIdent.tFwVersion.usMajor;
  ptChannelInfo->usFWMinor        = ptChannel->tFirmwareIdent.tFwVersion.usMinor;
  ptChannelInfo->usFWRevision     = ptChannel->tFirmwareIdent.tFwVersion.usRevision;
  ptChannelInfo->usFWBuild        = ptChannel->tFirmwareIdent.tFwVersion.usBuild;
  ptChannelInfo->bFWNameLength    = ptChannel->tFirmwareIdent.tFwName.bNameLength;

  OS_Memcpy(ptChannelInfo->abFWName,
            ptChannel->tFirmwareIdent.tFwName.abName,
            sizeof(ptChannelInfo->abFWName));

  ptChannelInfo->usFWYear         = ptChannel->tFirmwareIdent.tFwDate.usYear;
  ptChannelInfo->bFWMonth         = ptChannel->tFirmwareIdent.tFwDate.bMonth;
  ptChannelInfo->bFWDay           = ptChannel->tFirmwareIdent.tFwDate.bDay;

  ptChannelInfo->ulChannelError   = 0;
  if(0 != ptChannel->ptCommonStatusBlock)
  {
    ptChannelInfo->ulChannelError = LE32_TO_HOST(HWIF_READ32(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->ulCommunicationError));
  }

  ptChannelInfo->ulOpenCnt        = ptChannel->ulOpenCount;
  ptChannelInfo->ulPutPacketCnt   = ptChannel->tSendMbx.ulSendPacketCnt;
  ptChannelInfo->ulGetPacketCnt   = ptChannel->tRecvMbx.ulRecvPacketCnt;
  ptChannelInfo->ulMailboxSize    = ptChannel->tSendMbx.ulSendMailboxLength;
  ptChannelInfo->ulIOInAreaCnt    = ptChannel->ulIOInputAreas;
  ptChannelInfo->ulIOOutAreaCnt   = ptChannel->ulIOOutputAreas;
  ptChannelInfo->ulHskSize        = ptChannel->bHandshakeWidth;

  /* Check if we are in interrupt mode */
  if(!((PDEVICEINSTANCE)(ptChannel->pvDeviceInstance))->fIrqEnabled)
    DEV_ReadHandshakeFlags(ptChannel, 0, 1);

  ptChannelInfo->ulNetxFlags      = ptChannel->usNetxFlags;
  ptChannelInfo->ulHostFlags      = ptChannel->usHostFlags;
  ptChannelInfo->ulHostCOSFlags   = ptChannel->ulHostCOSFlags;
  ptChannelInfo->ulDeviceCOSFlags = ptChannel->ulDeviceCOSFlags;

  return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! Trigger channels watchdog
*   \param hChannel       Handle to the channel
*   \param ulCmd          Trigger command (CIFX_WATCHDOG_START to
*                         trigger/start, CIFX_WATCHDOG_STOP to end watchdog)
*   \param pulTrigger     Old trigger value from device
*                         (informational use only)
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelWatchdog(CIFXHANDLE hChannel, uint32_t ulCmd, uint32_t* pulTrigger)
{
  return DEV_TriggerWatchdog( (PCHANNELINSTANCE)hChannel, ulCmd, pulTrigger);
}

/*****************************************************************************/
/*! Set/Get Host state of the card
*   \param hChannel       Handle to the channel
*   \param ulCmd          Host state command (CIFX_HOST_STATE_NOT_READY,
*                         CIFX_HOST_STATE_READY, CIFX_HOST_STATE_READ)
*   \param pulState       Returned state if command is CIFX_HOST_STATE_READ
*   \param ulTimeout      Time in ms to wait for start/stop communication
*                         flag
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelHostState(CIFXHANDLE hChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout)
{
  int32_t lRet = CIFX_INVALID_PARAMETER;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pulState);

  switch(ulCmd)
  {
  case CIFX_HOST_STATE_READ:
    lRet = DEV_GetHostState( (PCHANNELINSTANCE)hChannel,
                             pulState);
    break;

  case CIFX_HOST_STATE_READY:
  case CIFX_HOST_STATE_NOT_READY:
    lRet = DEV_SetHostState( (PCHANNELINSTANCE)hChannel,
                             ulCmd,
                             ulTimeout);
    break;

  default:
    lRet = CIFX_INVALID_COMMAND;
    break;
  }

  return lRet;
}

/*****************************************************************************/
/*! Starts directory enumeration on the given channel
*   \param hChannel           Handle to the channel
*   \param ptDirectoryInfo    Pointer to enumeration result.
*                             (Will be initialized inside function)
*   \param pfnRecvPktCallback Callback for unhandled packets
*   \param pvUser             User data for callback function
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelFindFirstFile(CIFXHANDLE            hChannel,           CIFX_DIRECTORYENTRY* ptDirectoryInfo,
                                    PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void*                pvUser)
{
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;
  
  CHECK_CHANNELHANDLE(hChannel);  
  
  return xSysdeviceFindFirstFile(hChannel, ptChannel->ulChannelNumber, ptDirectoryInfo, pfnRecvPktCallback, pvUser);
}

/*****************************************************************************/
/*! Enumerate next entry in directoy on the given channel
*   \param hChannel         Handle to the channel
*   \param ptDirectoryInfo  Pointer to enumeration result.
*   \param pfnRecvPktCallback Callback for unhandled packets
*   \param pvUser             User data for callback function
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelFindNextFile(CIFXHANDLE            hChannel,            CIFX_DIRECTORYENTRY* ptDirectoryInfo,
                                   PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,  void*                pvUser)
{
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;
  
  CHECK_CHANNELHANDLE(hChannel);  

  return xSysdeviceFindNextFile(hChannel, ptChannel->ulChannelNumber, ptDirectoryInfo, pfnRecvPktCallback, pvUser);
}

/*****************************************************************************/
/*! Starts directory enumeration on the given channel
*   \param hSysdevice       Handle to the system device
*   \param ulChannel        Channel number to get directory from
*   \param ptDirectoryInfo  Pointer to enumeration result.
*                           (Will be initialized inside function)
*   \param pfnRecvPktCallback Callback for unhandled packets
*   \param pvUser             User data for callback function
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceFindFirstFile(CIFXHANDLE hSysdevice, uint32_t ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo,
                                      PFN_RECV_PKT_CALLBACK  pfnRecvPktCallback, void* pvUser)
{
  int32_t             lRet         = CIFX_NO_ERROR;
  PCHANNELINSTANCE    ptChannel    = (PCHANNELINSTANCE)hSysdevice;
  union
  {
    CIFX_PACKET        tPacket;
    RCX_DIR_LIST_REQ_T tDirListReq;
    
  }                   uSendPacket;
  RCX_DIR_LIST_CNF_T  tDirListCnf;
  
  OS_Memset(&uSendPacket, 0, sizeof(uSendPacket));
  OS_Memset(&tDirListCnf, 0, sizeof(tDirListCnf));

#ifdef CIFX_TOOLKIT_PARAMETER_CHECK
  if ( (CIFX_NO_ERROR != CheckSysdeviceHandle(hSysdevice)) &&
       (CIFX_NO_ERROR != CheckChannelHandle(hSysdevice))     )
       return CIFX_INVALID_HANDLE;
#endif

  CHECK_POINTER(ptDirectoryInfo);

  if(OS_Strlen(ptDirectoryInfo->szFilename) > 0)
  {
    uint16_t usDirNameLength = (uint16_t)(OS_Strlen(ptDirectoryInfo->szFilename) + 1);

    uSendPacket.tDirListReq.tData.usDirNameLength = HOST_TO_LE16(usDirNameLength);
    OS_Strncpy( (char*)((&uSendPacket.tDirListReq.tData) + 1),
                ptDirectoryInfo->szFilename,
                usDirNameLength);
  }

  uSendPacket.tDirListReq.tHead.ulDest      = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
  uSendPacket.tDirListReq.tHead.ulSrc       = HOST_TO_LE32(((PDEVICEINSTANCE)(ptChannel->pvDeviceInstance))->ulPhysicalAddress);
  uSendPacket.tDirListReq.tHead.ulCmd       = HOST_TO_LE32(RCX_DIR_LIST_REQ);
  uSendPacket.tDirListReq.tHead.ulLen       = HOST_TO_LE32( ((uint32_t)sizeof(uSendPacket.tDirListReq.tData) +
                                                            uSendPacket.tDirListReq.tData.usDirNameLength) );
  uSendPacket.tDirListReq.tData.ulChannelNo = HOST_TO_LE32(ulChannel);


  lRet = DEV_TransferPacket(ptChannel,
                            &uSendPacket.tPacket,
                            (CIFX_PACKET*)&tDirListCnf,
                            sizeof(tDirListCnf),
                            CIFX_TO_SEND_PACKET,
                            pfnRecvPktCallback,
                            pvUser);

  if( CIFX_NO_ERROR == lRet)
  {
    if( RCX_S_OK == (lRet = LE32_TO_HOST(tDirListCnf.tHead.ulSta)) )
    {
      /* TODO: Store handle for directory list, which needs to be set by firmware */
      *((int*)&(ptDirectoryInfo->hList)) = 1;
      OS_Strncpy(ptDirectoryInfo->szFilename,
                tDirListCnf.tData.szName,
                sizeof(ptDirectoryInfo->szFilename));

      ptDirectoryInfo->bFiletype  = tDirListCnf.tData.bFileType;
      ptDirectoryInfo->ulFilesize = LE32_TO_HOST(tDirListCnf.tData.ulFileSize);
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Enumerate next entry in directoy on the given channel
*   \param hSysdevice       Handle to the system device
*   \param ulChannel        Channel number to get directory from
*   \param ptDirectoryInfo  Pointer to enumeration result
*   \param pfnRecvPktCallback Callback for unhandled packets
*   \param pvUser             User data for callback function
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceFindNextFile(CIFXHANDLE hSysdevice, uint32_t ulChannel, CIFX_DIRECTORYENTRY* ptDirectoryInfo,
                                     PFN_RECV_PKT_CALLBACK  pfnRecvPktCallback, void* pvUser)
{
  int32_t             lRet         = CIFX_NO_ERROR;
  PCHANNELINSTANCE    ptChannel    = (PCHANNELINSTANCE)hSysdevice;
  union
  {
    CIFX_PACKET         tPacket;
    RCX_DIR_LIST_REQ_T  tDirListReq;
    
  }                   uSendPacket;
  RCX_DIR_LIST_CNF_T  tDirListCnf;
  uint16_t            usDirNameLen = 0;

  OS_Memset(&uSendPacket, 0, sizeof(uSendPacket));
  OS_Memset(&tDirListCnf, 0, sizeof(tDirListCnf));

#ifdef CIFX_TOOLKIT_PARAMETER_CHECK
  if ( (CIFX_NO_ERROR != CheckSysdeviceHandle(hSysdevice)) &&
       (CIFX_NO_ERROR != CheckChannelHandle(hSysdevice))     )
       return CIFX_INVALID_HANDLE;
#endif

  CHECK_POINTER(ptDirectoryInfo);

  usDirNameLen = (uint16_t)(OS_Strlen(ptDirectoryInfo->szFilename) + 1);
  uSendPacket.tDirListReq.tData.usDirNameLength = HOST_TO_LE16(usDirNameLen);
  OS_Strncpy( (char*)((&uSendPacket.tDirListReq.tData) + 1),
              ptDirectoryInfo->szFilename,
              usDirNameLen);

  uSendPacket.tDirListReq.tHead.ulDest      = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
  uSendPacket.tDirListReq.tHead.ulSrc       = HOST_TO_LE32(((PDEVICEINSTANCE)(ptChannel->pvDeviceInstance))->ulPhysicalAddress);
  uSendPacket.tDirListReq.tHead.ulCmd       = HOST_TO_LE32(RCX_DIR_LIST_REQ);
  uSendPacket.tDirListReq.tHead.ulLen       = HOST_TO_LE32( ((uint32_t)sizeof(uSendPacket.tDirListReq.tData) + usDirNameLen) );
  uSendPacket.tDirListReq.tHead.ulExt       = HOST_TO_LE32(RCX_PACKET_SEQ_MIDDLE);

  uSendPacket.tDirListReq.tData.ulChannelNo = HOST_TO_LE32(ulChannel);

  lRet = DEV_TransferPacket(ptChannel,
                            &uSendPacket.tPacket,
                            (CIFX_PACKET*)&tDirListCnf,
                            sizeof(tDirListCnf),
                            CIFX_TO_SEND_PACKET,
                            pfnRecvPktCallback,
                            pvUser);

  if(CIFX_NO_ERROR == lRet)
  {
    if( RCX_S_OK == (lRet = (LE32_TO_HOST(tDirListCnf.tHead.ulSta))) )
    {
      if(( LE32_TO_HOST(tDirListCnf.tHead.ulExt) & RCX_PACKET_SEQ_MASK) == RCX_PACKET_SEQ_LAST)
      {
        /* this is the last packet */
        lRet = CIFX_NO_MORE_ENTRIES;

        /* invalidate handle */
        *((int*)&(ptDirectoryInfo->hList)) = 0;

      } else
      {
        OS_Strncpy(ptDirectoryInfo->szFilename,
                  tDirListCnf.tData.szName,
                  sizeof(tDirListCnf.tData.szName));

        ptDirectoryInfo->bFiletype  = tDirListCnf.tData.bFileType;
        ptDirectoryInfo->ulFilesize = LE32_TO_HOST(tDirListCnf.tData.ulFileSize);
      }
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Uploads a file via system channel
*   \param hSysdevice         Handle to the System device
*   \param ulChannel          Channel number to get directory from
*   \param ulMode             Transfer Mode
*   \param pszFileName        Filename to upload
*   \param pabFileData        Pointer to buffer receiving upload
*   \param pulFileSize        [in]Length of buffer, [out] Bytes copied to buffer
*   \param pfnCallback        Callback pointer for progress
*                             (NULL for no callback)
*   \param pfnRecvPktCallback Callback pointer for unsolicited receive packets
*                             (NULL for no callback)
*   \param pvUser             User parameter on callback.
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xSysdeviceUpload(CIFXHANDLE     hSysdevice, uint32_t ulChannel,
                               uint32_t  ulMode,     char*         pszFileName, uint8_t* pabFileData, uint32_t* pulFileSize,
                               PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser)
{
  PCHANNELINSTANCE ptSysDevice    = (PCHANNELINSTANCE)hSysdevice;
  uint32_t         ulTransferType = 0;
  int32_t          lRet           = CIFX_NO_ERROR;

#ifdef CIFX_TOOLKIT_PARAMETER_CHECK
  if ( (CIFX_NO_ERROR != CheckSysdeviceHandle(hSysdevice)) &&
       (CIFX_NO_ERROR != CheckChannelHandle(hSysdevice))     )
       return CIFX_INVALID_HANDLE;
#endif

  CHECK_POINTER(pszFileName);
  CHECK_POINTER(pabFileData);
  CHECK_POINTER(pulFileSize);

  switch(ulMode)
  {
  case DOWNLOAD_MODE_FIRMWARE:
    if( CIFX_NO_ERROR != (lRet = DEV_GetFWTransferTypeFromFileName( pszFileName, &ulTransferType)))
      return lRet;
    break;

  case DOWNLOAD_MODE_CONFIG:
  case DOWNLOAD_MODE_FILE:
    ulTransferType = RCX_FILE_XFER_FILE;
    break;

  default:
    return CIFX_INVALID_PARAMETER;
  }

  lRet = DEV_UploadFile(ptSysDevice,
                        ulChannel,
                        ptSysDevice->tRecvMbx.ulRecvMailboxLength,
                        ulTransferType,
                        pszFileName,
                        pulFileSize,
                        pabFileData,
                        DEV_TransferPacket,
                        pfnCallback,
                        pfnRecvPktCallback,
                        pvUser);

  return lRet;
}

/*****************************************************************************/
/*! Uploads a file via Communication channel
*   \param hChannel           Handle to the Channel
*   \param ulMode             Transfer Mode
*   \param pszFileName        Filename to upload
*   \param pabFileData        Pointer to buffer receiving upload
*   \param pulFileSize        [in]Length of buffer, [out] Bytes copied to buffer
*   \param pfnCallback        Callback pointer for progress
*                             (NULL for no callback)
*   \param pfnRecvPktCallback Callback pointer for unsolicited receive packets
*                             (NULL for no callback)
*   \param pvUser             User parameter on callback.
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelUpload(CIFXHANDLE   hChannel,    uint32_t ulMode,
                             char*        pszFileName, uint8_t* pabFileData, uint32_t* pulFileSize,
                             PFN_PROGRESS_CALLBACK pfnCallback, PFN_RECV_PKT_CALLBACK pfnRecvPktCallback, void* pvUser)
{
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);  

  return xSysdeviceUpload(hChannel,
                          ptChannel->ulChannelNumber,
                          ulMode,
                          pszFileName,
                          pabFileData,
                          pulFileSize,
                          pfnCallback,
                          pfnRecvPktCallback,
                          pvUser);

}

/*****************************************************************************/
/*! Set DMA state of a communication channel
*   \param hChannel         Channel handle
*   \param ulCmd            Command CIFX_DMA_STATE_xxx
*   \param pulState         Return actual state on CIFX_GET_DMA_STATE
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelDMAState(CIFXHANDLE  hChannel, uint32_t ulCmd, uint32_t* pulState)
{
#ifdef CIFX_TOOLKIT_DMA

  int32_t          lRet          = CIFX_INVALID_PARAMETER;
  PCHANNELINSTANCE ptChannel     = (PCHANNELINSTANCE)hChannel;
  PDEVICEINSTANCE  ptDevInstance = NULL;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pulState);

  ptDevInstance = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;

  /* Only possible on PCI devices */
  if( !ptDevInstance->fPCICard)
    return CIFX_FUNCTION_NOT_AVAILABLE;

  /* Only possible if user provid DMA buffers */
  if(0 == ptDevInstance->ulDMABufferCount)
    return CIFX_DEV_DMA_INSUFF_BUFFER_COUNT;

  /* Check if firmware supports DMA functions */

  /*TODO: Check this */
  /*if( !ptChannel->ptCommonStatusBlock->ulCommunicationCOS->fPCICard) */
  /*  return CIFX_FUNCTION_NOT_AVAILABLE; */

  lRet = DEV_DMAState( (PCHANNELINSTANCE)hChannel,
                        ulCmd,
                        pulState);

  return lRet;

#else

  UNREFERENCED_PARAMETER(hChannel);
  UNREFERENCED_PARAMETER(ulCmd);
  UNREFERENCED_PARAMETER(pulState);
  return CIFX_FUNCTION_NOT_AVAILABLE;

#endif
}

/*****************************************************************************/
/*! Register a callback notification
*   \param hChannel           Handle to the Channel
*   \param ulNotification     Notification
*   \param pfnCallback        Callback function
*   \param pvUser             User data pointer
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelRegisterNotification(CIFXHANDLE           hChannel,
                                              uint32_t             ulNotification,
                                              PFN_NOTIFY_CALLBACK  pfnCallback,
                                              void*                pvUser)
{
  int32_t          lRet             = CIFX_NO_ERROR;
  PCHANNELINSTANCE ptChannel        = (PCHANNELINSTANCE)hChannel;
  PDEVICEINSTANCE  ptDevInst        = NULL;
  
  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pfnCallback);
  
  ptDevInst = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;

  if(!ptDevInst->fIrqEnabled)
    return CIFX_INTERRUPT_DISABLED;

  switch (ulNotification)
  {
    case CIFX_NOTIFY_RX_MBX_FULL:
      /* Check if already registered */
      if( NULL != ptChannel->tRecvMbx.pfnCallback)
      {
        /* Already registered */
        lRet = CIFX_CALLBACK_ALREADY_USED;
      } else
      {        
        ptChannel->tRecvMbx.pvUser      = pvUser;
        ptChannel->tRecvMbx.pfnCallback = pfnCallback;
        
        if(DEV_WaitForBitState(ptChannel, 
                               ptChannel->tRecvMbx.bRecvACKBitoffset,
                               RCX_FLAGS_NOT_EQUAL,
                               0))
        {
          CIFX_NOTIFY_RX_MBX_FULL_DATA_T tData;
          tData.ulRecvCount = ptChannel->tRecvMbx.ptRecvMailboxStart->usWaitingPackages;
          
          pfnCallback(CIFX_NOTIFY_RX_MBX_FULL, sizeof(tData), &tData, pvUser);
        }
      }
    break;
  
    case CIFX_NOTIFY_TX_MBX_EMPTY:
      /* Check if already registered */
      if( NULL != ptChannel->tSendMbx.pfnCallback)
      {
        /* Already registered */
        lRet = CIFX_CALLBACK_ALREADY_USED;
      } else
      {
        ptChannel->tSendMbx.pvUser      = pvUser;
        ptChannel->tSendMbx.pfnCallback = pfnCallback;
        
        if(DEV_WaitForBitState(ptChannel, 
                               ptChannel->tSendMbx.bSendCMDBitoffset,
                               RCX_FLAGS_EQUAL,
                               0))
        {
          CIFX_NOTIFY_TX_MBX_EMPTY_DATA_T tData;
          tData.ulMaxSendCount = ptChannel->tSendMbx.ptSendMailboxStart->usPackagesAccepted;
          
          pfnCallback(CIFX_NOTIFY_TX_MBX_EMPTY, sizeof(tData), &tData, pvUser);
        }
        
      }
    break;

    case CIFX_NOTIFY_PD0_IN:
    case CIFX_NOTIFY_PD0_OUT:
    {
      IOINSTANCE* ptIOArea    = ptChannel->pptIOInputAreas[0];
      uint32_t    ulAreaCount = ptChannel->ulIOInputAreas;
      uint8_t     bIOBitState = DEV_GetIOBitstate(ptChannel, ptIOArea, 0);
      
      if( CIFX_NOTIFY_PD0_OUT == ulNotification)
      {
        ptIOArea    = ptChannel->pptIOOutputAreas[0];
        ulAreaCount = ptChannel->ulIOOutputAreas;
        bIOBitState = DEV_GetIOBitstate(ptChannel, ptIOArea, 1);
      }
        
      /* Check if we have one input area */
      if( 0 == ulAreaCount)
      {
        /* No input area */
        lRet = CIFX_INVALID_PARAMETER;
        
      } else if( NULL != ptIOArea->pfnCallback)
      {
        /* Already registered */
        lRet = CIFX_CALLBACK_ALREADY_USED;
      } else
      {
        /* Add the callback */
        ptIOArea->pvUser      = pvUser;
        ptIOArea->pfnCallback = pfnCallback;

        if(DEV_WaitForBitState(ptChannel, 
                               ptIOArea->bHandshakeBit,
                               bIOBitState,
                               0))
        {
          pfnCallback(ulNotification, 0, NULL, pvUser);
        }
        
        lRet = CIFX_NO_ERROR;
      }
    }
    break;

    case CIFX_NOTIFY_PD1_IN:
    case CIFX_NOTIFY_PD1_OUT:
    {
      IOINSTANCE* ptIOArea    = ptChannel->pptIOInputAreas[1];
      uint32_t    ulAreaCount = ptChannel->ulIOInputAreas;
      uint8_t     bIOBitState = DEV_GetIOBitstate(ptChannel, ptIOArea, 0);
      
      if( CIFX_NOTIFY_PD1_OUT == ulNotification)
      {
        ptIOArea    = ptChannel->pptIOOutputAreas[1];
        ulAreaCount = ptChannel->ulIOOutputAreas;
        bIOBitState = DEV_GetIOBitstate(ptChannel, ptIOArea, 1);
      }

      /* Check if we have two input areas */
      if( 1 <= ulAreaCount)
      {
        /* No input area */
        lRet = CIFX_INVALID_PARAMETER;
        
      } else if( NULL != ptIOArea->pfnCallback)
      {
        /* Already registered */
        lRet = CIFX_CALLBACK_ALREADY_USED;
      } else
      {
        /* Add the callback */
        ptIOArea->pvUser      = pvUser;
        ptIOArea->pfnCallback = pfnCallback;

        if(DEV_WaitForBitState(ptChannel, 
                               ptIOArea->bHandshakeBit,
                               bIOBitState,
                               0))
        {
          pfnCallback(ulNotification, 0, NULL, pvUser);
        }
      }
    }
    break;

    case CIFX_NOTIFY_SYNC:
      if( NULL != ptChannel->tSynch.pfnCallback)
      {
        /* Already registered */
        lRet = CIFX_CALLBACK_ALREADY_USED;
      } else
      {
        /* Add the callback */
        uint8_t bState = RCX_FLAGS_NOT_EQUAL;

        ptChannel->tSynch.pvUser      = pvUser;
        ptChannel->tSynch.pfnCallback = pfnCallback;
        
        /* Add callback for sync on startup */
        if( RCX_SYNC_MODE_HST_CTRL == HWIF_READ8(ptDevInst, ptChannel->ptCommonStatusBlock->bSyncHskMode))
          bState = RCX_FLAGS_EQUAL;  
        
        if(DEV_WaitForSyncState(ptChannel, 
                                bState,
                                0))
        {
          pfnCallback(ulNotification, 0, NULL, pvUser);
        }
        
      }
    break;

    case CIFX_NOTIFY_COM_STATE:
      /* Check if already registered */
      if( NULL != ptChannel->tComState.pfnCallback)
      {
        /* Already registered */
        lRet = CIFX_CALLBACK_ALREADY_USED;
      } else
      {
        CIFX_NOTIFY_COM_STATE_T tData;

        ptChannel->tComState.pvUser      = pvUser;
        ptChannel->tComState.pfnCallback = pfnCallback;

        /* Just update the actual flag state by reading it once */
        DEV_WaitForBitState(ptChannel,
                            NCF_COMMUNICATING_BIT_NO,
                            RCX_FLAGS_SET,
                            0);

        tData.ulComState = ptChannel->usNetxFlags & NCF_COMMUNICATING;
        pfnCallback(CIFX_NOTIFY_COM_STATE, sizeof(tData), &tData, pvUser);
      }
    break;

    default:
      lRet = CIFX_INVALID_COMMAND;
    break;
  }
  
  return lRet;
}                                             

/*****************************************************************************/
/*! Unregister a callback notification
*   \param hChannel           Handle to the Channel
*   \param ulNotification     Notification
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelUnregisterNotification( CIFXHANDLE hChannel,
                                                 uint32_t   ulNotification)
{
  int32_t lRet = CIFX_NO_ERROR;
  
  PCHANNELINSTANCE ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);

  switch (ulNotification)
  {
    case CIFX_NOTIFY_RX_MBX_FULL:
      /* Check if already registered */
      if( NULL == ptChannel->tRecvMbx.pfnCallback)
      {
        /* Not registered */
        lRet = CIFX_CALLBACK_NOT_REGISTERED;
      } else
      {
        ptChannel->tRecvMbx.pfnCallback = NULL;
      }
    break;
  
    case CIFX_NOTIFY_TX_MBX_EMPTY:
      /* Check if already registered */
      if( NULL == ptChannel->tSendMbx.pfnCallback)
      {
        /* Already registered */
        lRet = CIFX_CALLBACK_NOT_REGISTERED;
      } else
      {
        ptChannel->tSendMbx.pfnCallback = NULL;
      }
    break;

    case CIFX_NOTIFY_PD0_IN:
    case CIFX_NOTIFY_PD0_OUT:
    {
      IOINSTANCE* ptIOArea    = ptChannel->pptIOInputAreas[0];
      uint32_t    ulAreaCount = ptChannel->ulIOInputAreas;
      
      if( CIFX_NOTIFY_PD0_OUT == ulNotification)
      {
        ptIOArea    = ptChannel->pptIOOutputAreas[0];
        ulAreaCount = ptChannel->ulIOOutputAreas;
      }
        
      /* Check if we have one input area */
      if( 0 == ulAreaCount)
      {
        /* No input area */
        lRet = CIFX_INVALID_PARAMETER;
        
      } else if( NULL == ptIOArea->pfnCallback)
      {
        /* Not registered before */
        lRet = CIFX_CALLBACK_NOT_REGISTERED;
      } else
      {
        /* Add the callback */
        ptIOArea->pfnCallback = NULL;
        ptIOArea->pvUser      = NULL;
        lRet = CIFX_NO_ERROR;
      }
    }
    break;

    case CIFX_NOTIFY_PD1_IN:
    case CIFX_NOTIFY_PD1_OUT:
    {
      IOINSTANCE* ptIOArea    = ptChannel->pptIOInputAreas[1];
      uint32_t    ulAreaCount = ptChannel->ulIOInputAreas;
      
      if( CIFX_NOTIFY_PD1_OUT == ulNotification)
      {
        ptIOArea    = ptChannel->pptIOOutputAreas[1];
        ulAreaCount = ptChannel->ulIOOutputAreas;
      }

      /* Check if we have two input areas */
      if( 1 <= ulAreaCount)
      {
        /* No input area */
        lRet = CIFX_INVALID_PARAMETER;
        
      } else if( NULL == ptIOArea->pfnCallback)
      {
        /* Not registered before */
        lRet = CIFX_CALLBACK_NOT_REGISTERED;
      } else
      {
        /* Add the callback */
        ptIOArea->pfnCallback = NULL;
        ptIOArea->pvUser      = NULL;
      }
    }
    break;

    case CIFX_NOTIFY_SYNC:
      if( NULL == ptChannel->tSynch.pfnCallback)
      {
        /* Not registered before */
        lRet = CIFX_CALLBACK_NOT_REGISTERED;
      } else
      {
        /* Add the callback */
        ptChannel->tSynch.pfnCallback = NULL;
        ptChannel->tSynch.pvUser      = NULL;
      }
    break;

    case CIFX_NOTIFY_COM_STATE:
      if( NULL == ptChannel->tComState.pfnCallback)
      {
        /* Not registered before */
        lRet = CIFX_CALLBACK_NOT_REGISTERED;
      } else
      {
        /* delete the callback */
        ptChannel->tComState.pfnCallback = NULL;
        ptChannel->tComState.pvUser      = NULL;
      }
    break;

    default:
      lRet = CIFX_INVALID_COMMAND;
    break;
  }
  
  return lRet;
}                                             

/*****************************************************************************/
/*! Signal a sync state, either a sync command or acknowledge
*   \param hChannel           Handle to the Channel
*   \param ulCmd              Sync command
*   \param ulTimeout          Timeout to wait for sync / sync signalling
*   \param pulErrorCount      Actual sync error counter
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t APIENTRY xChannelSyncState( CIFXHANDLE  hChannel,
                                    uint32_t    ulCmd,
                                    uint32_t    ulTimeout,
                                    uint32_t*   pulErrorCount)
{
  int32_t           lRet      = CIFX_NO_ERROR;
  PCHANNELINSTANCE  ptChannel = (PCHANNELINSTANCE)hChannel;

  CHECK_CHANNELHANDLE(hChannel);
  CHECK_POINTER(pulErrorCount);

  /* Check if device installed and active */
  if(ptChannel->ulOpenCount == 0)
  {
    lRet = CIFX_DRV_CHANNEL_NOT_INITIALIZED;
  } else
  {  
    switch (ulCmd)
    {
      case CIFX_SYNC_SIGNAL_CMD:
        /* Check if SYNC mode is host controlled */
        if(RCX_SYNC_MODE_HST_CTRL != HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bSyncHskMode))
        {
          /* Invalid Device mode */
          lRet = CIFX_DEV_SYNC_STATE_INVALID_MODE;

        } else if(!DEV_WaitForSyncState(ptChannel, RCX_FLAGS_EQUAL, ulTimeout))
        {
          /* Sync cannot be signalled as bits are in wrong state */
          lRet = CIFX_DEV_SYNC_STATE_TIMEOUT;
        } else
        {
          /* Signal new sync */
          DEV_ToggleSyncBit( (PDEVICEINSTANCE)ptChannel->pvDeviceInstance, (1 << ptChannel->ulChannelNumber));

          /* Return actual error counter */
          *pulErrorCount = HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bErrorSyncCnt);

          /* Check if the device is communication */
          DEV_IsCommunicating(ptChannel, &lRet);
        }
      break;
    
      case CIFX_SYNC_ACKNOWLEDGE_CMD:
        /* Check if SYNC mode is device controlled */
        if(RCX_SYNC_MODE_DEV_CTRL != HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bSyncHskMode))
        {
          /* Invalid Device mode */
          lRet = CIFX_DEV_SYNC_STATE_INVALID_MODE;

        } else if(!DEV_WaitForSyncState(ptChannel, RCX_FLAGS_NOT_EQUAL, ulTimeout))
        {
          /* Sync cannot be signalled as bits are in wrong state */
          lRet = CIFX_DEV_SYNC_STATE_TIMEOUT;
        } else
        {
          /* Acknowlege an device sys */
          DEV_ToggleSyncBit( (PDEVICEINSTANCE)ptChannel->pvDeviceInstance, (1 << ptChannel->ulChannelNumber));
          
          /* Return actual error counter */
          *pulErrorCount = HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bErrorSyncCnt);

          /* Check if the device is communication */
          DEV_IsCommunicating(ptChannel, &lRet);
        }
      break;
    
      case CIFX_SYNC_WAIT_CMD:
        {
          if( (HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bSyncHskMode) != RCX_SYNC_MODE_HST_CTRL) &&
              (HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bSyncHskMode) != RCX_SYNC_MODE_DEV_CTRL) )
          {
            /* Invalid Device mode */
            lRet = CIFX_DEV_SYNC_STATE_INVALID_MODE;
          } else
          {
            uint8_t bState = RCX_FLAGS_NOT_EQUAL;

            if( RCX_SYNC_MODE_HST_CTRL == HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bSyncHskMode))
              bState = RCX_FLAGS_EQUAL;  

            /* Wait for sync */
            if(!DEV_WaitForSyncState(ptChannel, bState, ulTimeout))
            {
              /* Sync timeout */
              lRet = CIFX_DEV_SYNC_STATE_TIMEOUT;
            } else
            {
              /* Return actual error counter */
              *pulErrorCount = HWIF_READ8(ptChannel->pvDeviceInstance, ptChannel->ptCommonStatusBlock->bErrorSyncCnt);

              /* Check if the device is communication */
              DEV_IsCommunicating(ptChannel, &lRet);
            }
          }
        }
      break;
    
      default:
        lRet = CIFX_INVALID_COMMAND;
      break;
    }
  }

  return lRet;
}
 
/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/
