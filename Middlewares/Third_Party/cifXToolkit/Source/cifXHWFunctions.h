/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: cifXHWFunctions.h 6614 2014-10-08 13:24:44Z stephans $:

  Description:
    cifX API Hardware handling functions declaration

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2014-10-08  Added separate identifier for netX52 (eCHIP_TYPE_NETX52)
    2014-07-03  PFN_HWIF_MEMCPY: replaced address parameter (uint32_t) by void pointer
                (skips address calculation for memory mapped devices on 64bit systems)
    2012-02-07  Removed ulCOMState from NETX_COM_STATE_T
    2012-01-31  Added NETX_COM_STATE_T -> CHANNELINSTANCEtag (COM-State notification)
    2011-09-13  - Added eCIFX_DEVICE_DONT_TOUCH
                - Added DEV_DoSystemBootstart()
    2011-03-02  Macros HWIF_READ8/16/32 now routed to read wrapper functions
    2011-02-28  Declarations for cifX hardware functions separated from cifXToolkit.h

**************************************************************************************/

/*****************************************************************************/
/*!  \file                                                                   *
*     cifX API Hardware handling functions declaration                       */
/*****************************************************************************/

#ifndef CIFX_HWFUNCTIONS__H
#define CIFX_HWFUNCTIONS__H

#ifdef __cplusplus
extern "C"
{
#endif

#include "OS_Dependent.h"
#include <OS_Includes.h>
#include "cifXUser.h"
#include "TLR_Types.h"
#include "rcX_User.h"
#include "NetX_RegDefs.h"

/*****************************************************************************/
/*!  \addtogroup CIFX_TK_STRUCTURE Toolkit Structure Definitions
*    \{                                                                      */
/*****************************************************************************/

#define CIFX_TKIT_IRQ_OTHERDEVICE   0   /*!< cifXTKitISRHandler return, if the IRQ
                                             is a shared PCI irq and was not from
                                             the cifX device */
#define CIFX_TKIT_IRQ_HANDLED       1   /*!< cifXTKitISRHandler return, if the IRQ
                                             was handled directly inside ISR */
#define CIFX_TKIT_IRQ_DSR_REQUESTED 2   /*!< cifXTKitISRHandler return, if the IRQ
                                             requires deferred processing. The toolkit
                                             then expects the DSRHandler to be called. */

typedef int32_t (*PFN_TRANSFER_PACKET)     (void* pvChannel, CIFX_PACKET* ptSendPkt, CIFX_PACKET* ptRecvPkt, uint32_t ulRecvBufferSize, uint32_t ulTimeout, PFN_RECV_PKT_CALLBACK pfnPktCallback, void*);

/*****************************************************************************/
/*! Structure defining an User Block                                         */
/*****************************************************************************/
typedef struct USERINSTANCEtag
{
  uint8_t* pbUserBlockStart;            /*!< Pointer to user block start in DPM */
  uint32_t  ulUserBlockLength;          /*!< Length of user block               */

} USERINSTANCE, *PUSERINSTANCE;

/*****************************************************************************/
/*! Structure defining an I/O Block                                          */
/*****************************************************************************/
typedef struct IOINSTANCEtag
{
  uint8_t*            pbDPMAreaStart;      /*!< DPM Pointer to start of IO Instance        */
  uint32_t            ulDPMAreaLength;     /*!< Length of IO Instance                      */
  uint8_t             bHandshakeBit;       /*!< Handshake bit associated with IO Instance  */
  uint16_t            usHandshakeMode;     /*!< Handshake mode for this IO instance        */
  uint8_t             bHandshakeBitState;  /*!< Handshake bit to wait for (depending on Handshake mode */
  void*               pvMutex;             /*!< Synchronistation object                    */
  uint32_t            ulNotifyEvent;       /*!< Event that is signalled via callback             */
  PFN_NOTIFY_CALLBACK pfnCallback;         /*!< Notification callback                            */
  void*               pvUser;              /*!< User pointer for callback                        */

} IOINSTANCE, *PIOINSTANCE;

/*****************************************************************************/
/*! Structure defining the send mailbox                                      */
/*****************************************************************************/
typedef struct NETX_TX_MAILBOX_Ttag
{
  NETX_SEND_MAILBOX_BLOCK* ptSendMailboxStart;        /*!< virtual start address of send mailbox            */
  uint32_t                 ulSendMailboxLength;       /*!< Length of send mailbox in bytes                  */
  uint32_t                 ulSendCMDBitmask;          /*!< Bitmask for Handshakeflags to send packet        */
  uint8_t                  bSendCMDBitoffset;         /*!< Bitnumber for send packet flag (used for notification array indexing) */
  void*                    pvSendMBXMutex;            /*!< Synchronistation object for the send mailbox     */
  uint32_t                 ulSendPacketCnt;           /*!< Number of packets sent on this mailbox           */
  PFN_NOTIFY_CALLBACK      pfnCallback;               /*!< Notification callback                            */
  void*                    pvUser;                    /*!< User pointer for callback                        */
  
} NETX_TX_MAILBOX_T;

/*****************************************************************************/
/*! Structure defining the receive mailbox                                   */
/*****************************************************************************/
typedef struct NETX_RX_MAILBOX_Ttag
{
  NETX_RECV_MAILBOX_BLOCK* ptRecvMailboxStart;        /*!< virtual start address of receive mailbox         */
  uint32_t                 ulRecvMailboxLength;       /*!< Length of receive mailbox in bytes               */
  uint32_t                 ulRecvACKBitmask;          /*!< Bitmask for Handshakeflags to ack recv. packet   */
  uint8_t                  bRecvACKBitoffset;         /*!< Bitnumber for recv packet ack flag (used for notification array indexing) */
  void*                    pvRecvMBXMutex;            /*!< Synchronistation object for the receive mailbox  */
  uint32_t                 ulRecvPacketCnt;           /*!< Number of packets recevied on this mailbox       */  
  PFN_NOTIFY_CALLBACK      pfnCallback;               /*!< Notification callback                            */
  void*                    pvUser;                    /*!< User pointer for callback                        */
  
} NETX_RX_MAILBOX_T;

/*****************************************************************************/
/*! Structure used for COM-state notification                                */
/*****************************************************************************/
typedef struct NETX_COM_STATE_Ttag
{
  PFN_NOTIFY_CALLBACK      pfnCallback;               /*!< Notification callback                            */
  void*                    pvUser;                    /*!< User pointer for callback                        */
} NETX_COM_STATE_T;

/*****************************************************************************/
/*! Structure defining the sync data                                         */
/*****************************************************************************/
typedef struct NETX_SYNC_DATA_Ttag
{
  PFN_NOTIFY_CALLBACK      pfnCallback;               /*!< Notification callback                            */
  void*                    pvUser;                    /*!< User pointer for callback                        */
} NETX_SYNC_DATA_T;

/*****************************************************************************/
/*! Structure defining a channel instance                                    */
/*****************************************************************************/
typedef struct CHANNELINSTANCEtag
{
  void*                 pvDeviceInstance;           /*!< Pointer to the device instance belonging to this channel */

  void*                 pvInitMutex;                /*!< Device is currently initializing, e.g. while doing a reset       */

  uint8_t*              pbDPMChannelStart;          /*!< virtual start address of channel block          */
  uint32_t              ulDPMChannelLength;         /*!< length of channel block                         */
  uint32_t              ulChannelNumber;            /*!< Number of the Channel                           */
  uint32_t              ulBlockID;                  /*!< Block ID                                        */

  void*                 pvLock;                     /*!< Lock for synchronizing interrupt accesses to flags   */
  uint32_t              ulOpenCount;                /*!< Number of open device function called for channel    */

  int                   fIsSysDevice;               /*!< !=0 if the channel instance belong to a systemdevice */
  int                   fIsChannel;                 /*!< !=0 this is a real channel                           */

  NETX_FW_IDENTIFICATION tFirmwareIdent;            /*!< Firmware Identification                         */
  
  /*-----------------------------------------
  --- Mailbox specific data               ---
  -----------------------------------------*/
  NETX_TX_MAILBOX_T     tSendMbx;                   /*!< Send mailbox administration structure   */  
  NETX_RX_MAILBOX_T     tRecvMbx;                   /*!< Receive mailbox administration structure*/  
  /*---------------------------------------*/

  NETX_COM_STATE_T      tComState;                  /*!< defining resources for com-state notification */

  uint16_t              usHostFlags;                /*!< Copy of the last actual command flags   */
  uint16_t              usNetxFlags;                /*!< Copy of the last read status flags      */

  uint32_t              ulDeviceCOSFlags;           /*!< Device COS flags (copy, updated when COS Handshake is recognized) */
  uint32_t              ulDeviceCOSFlagsChanged;    /*!< Bitmask of changed bits since last COS Handshake                  */
  uint32_t              ulHostCOSFlags;             /*!< Host COS flags (copy)                      */

  NETX_CONTROL_BLOCK*         ptControlBlock;       /*!< Pointer to channel's control block         */
  uint8_t                     bControlBlockBit;     /*!< Handshake bit associated with control block*/
  uint32_t                    ulControlBlockSize;   /*!< Size of the control block in bytes         */

  NETX_COMMON_STATUS_BLOCK*   ptCommonStatusBlock;  /*!< Pointer to channel's common status block   */
  uint8_t                     bCommonStatusBit;     /*!< Handshake bit associated with Common status block*/
  uint32_t                    ulCommonStatusSize;   /*!< Size of the common status block in bytes   */

  NETX_EXTENDED_STATUS_BLOCK* ptExtendedStatusBlock;/*!< Pointer to channel's extended status block */
  uint8_t                     bExtendedStatusBit;   /*!< Handshake bit associated with Extended status block*/
  uint32_t                    ulExtendedStatusSize; /*!< Size of the extended status block in bytes */

  uint8_t               bHandshakeWidth;            /*!< Width of the handshake cell        */
  NETX_HANDSHAKE_CELL*  ptHandshakeCell;            /*!< pointer to channels handshake cell */

  void*                 ahHandshakeBitEvents[NETX_HANDSHAKE_PAIRS]; /*!< Event handle for each handshake bit pair. (used in interrupt mode) */

  PIOINSTANCE*          pptIOInputAreas;            /*!< Input Areas array for this channel                   */
  uint32_t              ulIOInputAreas;             /*!< Number of Input areas                                */

  PIOINSTANCE*          pptIOOutputAreas;           /*!< Output Areas array for this channel                  */
  uint32_t              ulIOOutputAreas;            /*!< Number of Output areas                               */

  PUSERINSTANCE*        pptUserAreas;               /*!< User areas for this channel                          */
  uint32_t              ulUserAreas;                /*!< Number of user areas                                 */

  NETX_SYNC_DATA_T      tSynch;                     /*!< Sync handling                                        */
  
} CHANNELINSTANCE, *PCHANNELINSTANCE;

/*****************************************************************************/
/*! Enumeration for different netX chip types                                */
/*****************************************************************************/
typedef enum CIFX_TOOLKIT_CHIPTYPE_Etag
{
  eCHIP_TYPE_UNKNOWN, /*!< Chip cannot be identified */
  eCHIP_TYPE_NETX500, /*!< netX500 */
  eCHIP_TYPE_NETX100, /*!< netX100, can currently only be detected when FW is already running */
  eCHIP_TYPE_NETX50,  /*!< netX 50 */
  eCHIP_TYPE_NETX10,  /*!< netX 10 */
  eCHIP_TYPE_NETX51,  /*!< netX 51 */
  eCHIP_TYPE_NETX52   /*!< netX 52 */

} CIFX_TOOLKIT_CHIPTYPE_E;

typedef enum CIFX_TOOLKIT_DEVICETYPE_Etag
{
  eCIFX_DEVICE_AUTODETECT = 0,    /*!< Autodetection of device. Default: PCI = RAM and DPM = Flash
                                       For DPM: If no 'netX' or 'BOOT' cookie is present RAM based
                                                device will be used                                         */
  eCIFX_DEVICE_AUTODETECT_ERROR,  /*!< Unable to autodetect device type                                     */
  eCIFX_DEVICE_RAM_BASED,         /*!< Always perform a reset on startup and re-download all files          */
  eCIFX_DEVICE_FLASH_BASED,       /*!< Assume a running bootloader/FW from flash                            */
  eCIFX_DEVICE_DONT_TOUCH         /*!< Leave the device in the current state and try to connect to it       */

} CIFX_TOOLKIT_DEVICETYPE_E;


/*****************************************************************************/
/*! Notification events that can be signalled during cifXTKitAddDevice       */
/*****************************************************************************/
typedef enum CIFX_TOOLKIT_NOTIFY_Etag
{
  eCIFX_TOOLKIT_EVENT_PRERESET        = 0, /*!< Event signalled, before device is reset (HW Reset) */
  eCIFX_TOOLKIT_EVENT_POSTRESET,           /*!< Called after HW reset has been executed            */
  eCIFX_TOOLKIT_EVENT_PRE_BOOTLOADER,      /*!< Called before bootloader is downloaded             */
  eCIFX_TOOLKIT_EVENT_POST_BOOTLOADER      /*!< Called after bootloader was downloaded and started */

} CIFX_TOOLKIT_NOTIFY_E;

typedef void(*PFN_CIFXTK_NOTIFY)(void* pvDeviceInstance, CIFX_TOOLKIT_NOTIFY_E eEvent);

typedef struct IRQ_TO_DSR_BUFFER_Ttag
{
  NETX_HANDSHAKE_ARRAY tHandshakeBuffer;
  int                  fValid;

} IRQ_TO_DSR_BUFFER_T;

/*****************************************************************************/
/*! DMA buffer structure.
*   In DMA mode, passing the physical and virtual pointers to pre-defined
*   to the toolkit.                                                          */
/*****************************************************************************/
#ifdef CIFX_TOOLKIT_DMA

  /*****************************************************************************/
  /*! Definition of the DMA channel numbers                                    */
  /*****************************************************************************/
  typedef enum
  {
    eDMA_CHANNEL_0 = 0,
    eDMA_CHANNEL_1 = 1,
    eDMA_CHANNEL_2 = 2,
    eDMA_CHANNEL_3 = 3,
    eDMA_CHANNEL_4 = 4,
    eDMA_CHANNEL_5 = 5,
    eDMA_CHANNEL_6 = 6,
    eDMA_CHANNEL_7 = 7
  } CIFX_DMA_CHANNEL;

  /*****************************************************************************/
  /*! Definition of the DMA buffers and direction                              */
  /*****************************************************************************/
  typedef enum
  {
    eDMA_INPUT_BUFFER_IDX   = 0,          /* Input buffer index */
    eDMA_OUTPUT_BUFFER_IDX  = 1           /* Output buffer index */
  } CIFX_DMA_DIRECTION;

  /*****************************************************************************/
  /*! Definition of the DMA                                                    */
  /*****************************************************************************/
  typedef enum CIFX_TOOLKIT_DMA_MODE_Etag
  {
    eDMA_MODE_LEAVE,      /*!< Leave communication channels in actual mode */
    eDMA_MODE_ON,         /*!< Switch channels into DMA mode if possible */
    eDMA_MODE_OFF         /*!< Switch OFF DMA mode for all channels */
  } CIFX_TOOLKIT_DMA_MODE_E;

  /*****************************************************************************/
  /*! Default definitions and DMA buffer structure                             */
  /*****************************************************************************/
  /* ATTENTION: - Buffer size must be a multiple of 256 Byte */
  /*            - Maximum supported DMA buffer size is 63,75 KByte */
  #define CIFX_DMA_MODULO_SIZE             256
  #define CIFX_DMA_MAX_BUFFER_SIZE         (255 * CIFX_DMA_MODULO_SIZE)   /*!< Max configureable DMA buffer size */
  #define CIFX_DMA_BUFFER_COUNT            8                              /*!< Number of DMA buffers */
  #define CIFX_DEFAULT_DMA_BUFFER_SIZE     8*1024                         /*!< DMA buffer size in KByte */

  typedef struct CIFX_DMABUFFER_Ttag
  {
    uint32_t   ulSize;                                               /*!< DMA buffer size  */
    uint32_t   ulPhysicalAddress;                                    /*!< Physical address of the buffer */
    void*      pvBuffer;                                             /*!< Pointer to the buffer */
    void*      pvUser;                                               /*!< User parameter */
  } CIFX_DMABUFFER_T, *PCIFX_DMABUFFER_T;
  
#endif /* CIFX_TOOLKIT_DMA */

/*****************************************************************************/
/*! Synchronisation structure
*   If synchronisation is supported, these structure is used to hold the
*   necessary data. Synch information in device global.                      
*   Synch-Flags are located in the handshake channel and 16 bit by default   */
/*****************************************************************************/
#define NETX_HSK_SYNCH_FLAG_POS   1                                       /*!< Position of the sync flahs in the HSK channel */
#define NETX_NUM_OF_SYNCH_FLAGS   4                                       /*!< Number of supported sync flags */

typedef struct CIFX_SYNCH_DATA_Ttag
{
  void*     pvLock;                                       /*!< Lock for synchronizing interrupt accesses to flags   */
  uint16_t  usSyncMode;                                   /*!< Synchronistation mode */
  uint16_t  usHSyncFlags;                                 /*!< Host synchronistation flags */
  uint16_t  usNSyncFlags;                                 /*!< netX synchronistation flags */
  void*     ahSyncBitEvents[NETX_HANDSHAKE_PAIRS];        /*!< netX synchronistation flags */
 
} CIFX_SYNCH_DATA_T;

#ifdef CIFX_TOOLKIT_HWIF
  typedef void*    (*PFN_HWIF_MEMCPY)  ( void* pvDevInstance, void* pvAddr, void* pvData, uint32_t ulLen);

  #define HWIF_READ8(ptDev,  Src)  HwIfRead8(ptDev,  (void*)&(Src))
  #define HWIF_READ16(ptDev, Src)  HwIfRead16(ptDev, (void*)&(Src))
  #define HWIF_READ32(ptDev, Src)  HwIfRead32(ptDev, (void*)&(Src))
  #define HWIF_READN(ptDev, Dst, Src, Len) ((PDEVICEINSTANCE)ptDev)->pfnHwIfRead(ptDev, (void*)(Src), Dst, Len)
  #define HWIF_WRITE8(ptDev, Dst,  Src)                       \
  do {                                                        \
    uint8_t bData = Src;                                      \
    ((PDEVICEINSTANCE)ptDev)->pfnHwIfWrite(ptDev, (void*)&(Dst), (void*)&bData, 1);  \
  } while (0);
  #define HWIF_WRITE16(ptDev, Dst, Src)                       \
  do {                                                        \
    uint16_t uiData = Src;                                    \
    ((PDEVICEINSTANCE)ptDev)->pfnHwIfWrite(ptDev, (void*)&(Dst), (void*)&uiData, 2); \
  } while (0);
  #define HWIF_WRITE32(ptDev, Dst, Src)                       \
  do {                                                        \
    uint32_t ulData = Src;                                    \
    ((PDEVICEINSTANCE)ptDev)->pfnHwIfWrite(ptDev, (void*)&(Dst), (void*)&ulData, 4); \
  } while (0);
  #define HWIF_WRITEN(ptDev, Dst, Src, Len) ((PDEVICEINSTANCE)ptDev)->pfnHwIfWrite(ptDev, (void*)(Dst), Src, Len)

#else
  #define HWIF_READ8(ptDev,  Src) Src
  #define HWIF_READ16(ptDev, Src) Src
  #define HWIF_READ32(ptDev, Src) Src
  #define HWIF_READN(ptDev, Dst, Src, Len) OS_Memcpy(Dst, Src, Len)
  #define HWIF_WRITE8(ptDev,  Dst,  Src) (Dst) = (Src);
  #define HWIF_WRITE16(ptDev, Dst, Src)  (Dst) = (Src);
  #define HWIF_WRITE32(ptDev, Dst, Src)  (Dst) = (Src);
  #define HWIF_WRITEN(ptDev, Dst, Src, Len) OS_Memcpy(Dst, Src, Len)
#endif /* CIFX_TOOLKIT_HWIF */

/*****************************************************************************/
/*! Structure defining a physical device passed to the toolkit. Passing it,
*   will create all logical device associated with this instance             */
/*****************************************************************************/
typedef struct DEVICEINSTANCEtag
{
  uint32_t                  ulPhysicalAddress;      /*!< Physical address of the cifX card                        */
  uint8_t                   bIrqNumber;             /*!< IRQ number assigned to card                              */
  int                       fIrqEnabled;            /*!< !=0 if the IRQ is used on this device                    */

  int                       fPCICard;               /*!< !=0 if the card is a PCI card (netX directly connected to PCI)
                                                           ,this will reset the netX if eDeviceType is AUTODETECT or RAMBASE */
  int                       fModuleLoad;            /*!< This devices works with modules */

  CIFX_TOOLKIT_DEVICETYPE_E eDeviceType;            /*!< Type of the device. If set to AUTODETECT it will be updated during
                                                         cifXAddDevice                                                       */
  PFN_CIFXTK_NOTIFY         pfnNotify;              /*!< Function to notify user of different states in the toolkit, to allow
                                                         memory controller reconfiguration, etc. */
  void*                     pvOSDependent;          /*!< OS dependent pointer to device identification (used for PCI read/write request). This parameter must allow the OS/User to identify the card and access it's PCI registers */
  uint8_t*                  pbDPM;                  /*!< Virtual/usable pointer to the cards DPM              */
  uint32_t                  ulDPMSize;              /*!< Size of the cards DPM                                */
  CIFX_TOOLKIT_CHIPTYPE_E   eChipType;              /*!< Type of chip */

  char                      szName[CIFx_MAX_INFO_NAME_LENTH]; /*!< Default name of the card, must be inserted by user */
  char                      szAlias[CIFx_MAX_INFO_NAME_LENTH];/*!< Alias name of the card (must be inserted by user   */

  int32_t                   lInitError;             /*!< Initialization error of the card                         */

  PNETX_GLOBAL_REG_BLOCK    ptGlobalRegisters;      /*!< Pointer to the global host registers (only available on PCI)  */
  uint32_t                  ulSerialNumber;         /*!< Serial number of the card (read on startup)        */
  uint32_t                  ulDeviceNumber;         /*!< Device number of the card (read on startup)        */
  uint32_t                  ulSlotNumber;           /*!< Slot number on card (read on startup)              */

  uint8_t*                  pbHandshakeBlock;       /*!< Pointer to start of Handshake block (NULL if no handshake block was found */
  int                       iIrqToDsrBuffer;        /*!< IRQ to DSR Buffer number to use               */
  IRQ_TO_DSR_BUFFER_T       atIrqToDsrBuffer[2];    /*!< IRQ to DSR Buffers                            */
  uint32_t                  ulIrqCounter;           /*!< Number of interrupts processed on this device */

  CHANNELINSTANCE           tSystemDevice;          /*!< Every card has at least one SystemDevice             */
  uint32_t                  ulCommChannelCount;     /*!< Number of fount communication channels on the card   */
  CHANNELINSTANCE**         pptCommChannels;        /*!< Array of all found channels                          */

#ifdef CIFX_TOOLKIT_DMA
  /* DMA Buffer Structure */
  uint32_t                  ulDMABufferCount;                     /*!< Number of available DMA buffers  */
  CIFX_DMABUFFER_T          atDmaBuffers[CIFX_DMA_BUFFER_COUNT];  /*!< DMA buffer definition for the device */
#endif /* CIFX_TOOLKIT_DMA */

  /* Synch handling */
  CIFX_SYNCH_DATA_T         tSyncData;              /*!< Synchronisation structure */

  int                       fResetActive;           /*!< !=0 if a reset is pending on device (DEV_DoSystemStart) */

  /* Extended memory (additional target memory) */
  uint8_t*                  pbExtendedMemory;       /*!< Virtual/usable pointer to an extended memory area       */
  uint32_t                  ulExtendedMemorySize;   /*!< Size of the extended memory area                        */

#ifdef CIFX_TOOLKIT_HWIF
  PFN_HWIF_MEMCPY        pfnHwIfRead;
  PFN_HWIF_MEMCPY        pfnHwIfWrite;
#endif /* CIFX_TOOLKIT_HWIF */

} DEVICEINSTANCE, *PDEVICEINSTANCE;

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/

int  cifXTKitISRHandler   (PDEVICEINSTANCE ptDevInstance, int fPCIIgnoreGlobalIntFlag);
void cifXTKitDSRHandler   (PDEVICEINSTANCE ptDevInstance);

/* Toolkit Internal Functions */
void    DEV_WriteHandshakeFlags  (PCHANNELINSTANCE ptChannel);
void    DEV_ReadHostFlags        (PCHANNELINSTANCE ptChannel, int fReadHostCOS);
void    DEV_ReadHandshakeFlags   (PCHANNELINSTANCE ptChannel, int fReadSyncFlags, int fLockNeeded);

uint8_t DEV_GetIOBitstate        (PCHANNELINSTANCE ptChannel, PIOINSTANCE ptIOInstance, int fOutput);

int     DEV_WaitForBitState      (PCHANNELINSTANCE ptChannel, uint32_t ulBitNumber, uint8_t bState, uint32_t ulTimeout);
void    DEV_ToggleBit            (PCHANNELINSTANCE ptChannel, uint32_t ulBitMask);

int     DEV_WaitForSyncState     (PCHANNELINSTANCE ptChannel, uint8_t bState, uint32_t ulTimeout);
void    DEV_ToggleSyncBit        (PDEVICEINSTANCE  ptDevInstance, uint32_t ulBitMask);

int32_t DEV_PutPacket            (PCHANNELINSTANCE ptChannel, CIFX_PACKET* ptSendPkt, uint32_t ulTimeout);
int32_t DEV_GetPacket            (PCHANNELINSTANCE ptChannel, CIFX_PACKET* ptRecvPkt, uint32_t ulRecvBufferSize, uint32_t ulTimeout);
int32_t DEV_GetMBXState          (PCHANNELINSTANCE ptChannel, uint32_t* pulRecvPktCnt, uint32_t* pulSendPktCnt);


int32_t DEV_TransferPacket    (void*                  pvChannel,        CIFX_PACKET* ptSendPkt,   CIFX_PACKET*           ptRecvPkt,
                               uint32_t               ulRecvBufferSize, uint32_t     ulTimeout,
                               PFN_RECV_PKT_CALLBACK  pfnRecvPacket,    void*        pvUser);

int DEV_IsReady               (PCHANNELINSTANCE ptChannel);
int DEV_IsRunning             (PCHANNELINSTANCE ptChannel);
int DEV_IsCommunicating       (PCHANNELINSTANCE ptChannel, int32_t* plError);
int DEV_WaitForReady_Poll     (PCHANNELINSTANCE ptChannel, uint32_t ulTimeout);
int DEV_WaitForNotReady_Poll  (PCHANNELINSTANCE ptChannel, uint32_t ulTimeout);
int DEV_WaitForRunning_Poll   (PCHANNELINSTANCE ptChannel, uint32_t ulTimeout);
int DEV_WaitForNotRunning_Poll(PCHANNELINSTANCE ptChannel, uint32_t ulTimeout);

int32_t DEV_TriggerWatchdog      (PCHANNELINSTANCE ptChannel, uint32_t ulTriggerCmd, uint32_t* pulTriggerValue);
int32_t DEV_GetHostState         (PCHANNELINSTANCE ptChannel, uint32_t* pulState);
int32_t DEV_SetHostState         (PCHANNELINSTANCE ptChannel, uint32_t ulNewState, uint32_t ulTimeout);
int32_t DEV_ReadWriteBlock       (PCHANNELINSTANCE ptChannel, void* pvBlock, uint32_t ulOffset, uint32_t ulBlockLen, void* pvDest, uint32_t ulDestLen, uint32_t ulCmd, int fWriteAllowed);
int32_t DEV_DoChannelInit        (PCHANNELINSTANCE ptChannel, uint32_t ulTimeout);
int32_t DEV_DoSystemStart        (PCHANNELINSTANCE ptChannel, uint32_t ulTimeout);
int32_t DEV_DoSystemBootstart    (PCHANNELINSTANCE ptChannel, uint32_t ulTimeout);
int32_t DEV_BusState             (PCHANNELINSTANCE ptChannel, uint32_t ulCmd, uint32_t* pulState, uint32_t ulTimeout);
int32_t DEV_DoHostCOSChange      (PCHANNELINSTANCE ptChannel, uint32_t ulSetCOSMask, uint32_t ulClearCOSMask,
                               uint32_t ulPostClearCOSMask, int32_t lSignallingError, uint32_t ulTimeout);
void DEV_CheckCOSFlags        (PDEVICEINSTANCE ptDevInstance);

uint8_t DEV_GetHandshakeBitState(PCHANNELINSTANCE ptChannel, uint32_t ulBitMsk);

#ifdef CIFX_TOOLKIT_DMA
  int32_t DEV_DMAState             (PCHANNELINSTANCE ptChannel, uint32_t ulCmd, uint32_t* pulState);
  int32_t DEV_SetupDMABuffers      (PCHANNELINSTANCE ptChannel);
#endif

#ifdef CIFX_TOOLKIT_HWIF
  uint8_t  HwIfRead8  (PDEVICEINSTANCE ptDev, void* pvSrc);
  uint16_t HwIfRead16 (PDEVICEINSTANCE ptDev, void* pvSrc);
  uint32_t HwIfRead32 (PDEVICEINSTANCE ptDev, void* pvSrc);
#endif /* CIFX_TOOLKIT_HWIF */

/******************************************************************************
* Functions to be implemented by USER                                         *
******************************************************************************/

void      USER_Trace                    (PDEVICEINSTANCE ptDevInstance, uint32_t ulTraceLevel,
                                         const char* szFormat, ...);

#define TRACE_LEVEL_DEBUG   0x00000001
#define TRACE_LEVEL_INFO    0x00000002
#define TRACE_LEVEL_WARNING 0x00000004
#define TRACE_LEVEL_ERROR   0x00000008

extern uint32_t g_ulTraceLevel;


#ifdef __cplusplus
}
#endif

#endif /* CIFX_HWFUNCTIONS__H */
