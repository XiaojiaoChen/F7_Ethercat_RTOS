/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: cifXDownload.c 7477 2015-12-22 07:16:47Z Robert $:

  Description:
    cifX download functionality

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2015-12-22  Changed md5.h to hilmd5.h
    2015-07-21  Fixed compiler warnings created by implicit data conversion on 64bit systems
    2012-12-11  Zero'ing local variables now done using OS_Memset to prevent compiler from
                creating constants for initialization (memory usage optimization)
    2012-08-08  Added casts needed when compiling with C++ compiler
    2012-02-20  Checking pvDat/File length in DEV_DownloadFile()
    2010-06-09  Larger loadable modules (.NXO) failed to download, as the last packet
                starts relocation on the target and the confirmation may take longer
                as the internal timeout.
    2010-05-11  DEV_DownloadFile(), uses twice the timeout for the last packet if
                modules are loaded because relocation of modules are done with the
                receiving the last packet
    2010-05-07  DEV_DeleteFile() OS_Strncpy() size of copied data must include
                the necessary 0 character
    2010-04-29  Get MD5 Request may not copy complete filename into request,
                depending on implementation of OS_Strncpy
    2010-04-21  Fixed GCC compiler warning (dereferencing pointer breaks strict-aliasing rules)
    2009-08-05  DEV_Download returned CIFX_BUFFER_TOO_SHORT, if another packet arrived
                in the mailbox, instead of calling pfnRecvCallback, due to internal
                buffer size limitation
    2009-04-28  Added Function DEV_ProcessFWDownload()
    2009-01-20  Added Big endian host support added (set #define CIFX_TOOLKIT_BIGENDIAN)
    2009-01-16  DEV_CheckForDownload() changed, because rcX still calculates
                the MD5 over the whole file. So it must be also calculated
    2008-11-18  - HilFileHeaderV3 included
                - DEV_CheckForDownload() now checks the file header version.
                  If < V3 than MD5 is calculated otherwise just compared
    2007-05-02  Comment fixed (line 96)
    2007-04-23  Checking of valid firmware file and Delete file included
    2007-04-19  Checking of valid file extensions for firmware files included
    2007-04-17  - Parameters for pfnTransferPacket() extended
                - Parameters for DEV_UploadFile()/DownloadFile() extended
    2007-04-13  Upload/Download, send abort detection and application progress,changed
    2007-04-12  Number of bytes read from file fixed
    2007-04-05  Size calculation of maximum block size in Download/Upload fixed
    2007-04-03  Download/Upload finished fixed, checking now for
                packet extension LAST and NONE
    2007-03-30  - Using now RCX_Public.h instead of MidSys_Public.h
                - Send packets completely initialized
                - MID_SYS definition changed to RCX_
    2007-03-29  Timeout values for transfer packet taken from cifXUser.h
    2007-03-28  DEV_DownloadFile/UploadFile changed to be useable in cifx32dll project.
                - Packet transfer function passed as function pointer
                - Parameter definitions changed
    2007-03-20  Added DEV_Upload
    2006-07-11  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file cifXDownload.c
*   cifX download functionality                                              */
/*****************************************************************************/

#include "cifXToolkit.h"
#include "HilFileHeaderV3.h"
#include "cifXErrors.h"
#include "rcX_Public.h"
#include "rcX_User.h"
#include "OS_Dependent.h"
#include "Hilmd5.h"
#include "cifXEndianess.h"
#include "ModuleLoader_Public.h"

/*****************************************************************************/
/*!  \addtogroup CIFX_TK_HARDWARE Hardware Access
*    \{                                                                      */
/*****************************************************************************/

/*****************************************************************************/
/*! Delete all existing files in a channel, from the file system.
*   \param ptChannel          Channel instance
*   \param ulChannel          Channel number
*   \param pfnTransferPacket  Function used for transferring packets
*   \param pfnRecvPacket      User callback for unsolicited receive packets
*   \param pvUser             User parameter passed on callback
*   \param szExceptFile       File extension to ignore while deleting files
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int DEV_RemoveChannelFiles(PCHANNELINSTANCE ptChannel, uint32_t ulChannel,
                           PFN_TRANSFER_PACKET    pfnTransferPacket,
                           PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                           void*                  pvUser,
                           char*                  szExceptFile)
{
  /* Try to find file with the extension *.nxm, *.nxf, *.mod and remove it */
  CIFX_DIRECTORYENTRY tDirectoryEntry;
  int32_t             lRet            = CIFX_NO_ERROR;
  int                 fFindFirst      = 1;

  OS_Memset(&tDirectoryEntry, 0, sizeof(tDirectoryEntry));

  /* Search for all firmware files. If one is found. delete it an start with find first again, */
  /* because we can't store a directory list in here */
  do
  {
    if ( fFindFirst)
    {
      /* Search first file */
      if ( !(CIFX_NO_ERROR == (lRet = xSysdeviceFindFirstFile( ptChannel, ulChannel, &tDirectoryEntry, pfnRecvPacket, pvUser))))
      {
        /* No more files, or error during find first */
        break;
      } else
      {
        /* Is this a valid file name */
        int iStrlen = OS_Strlen(tDirectoryEntry.szFilename);
        if( iStrlen >= CIFX_MIN_FILE_NAME_LENGTH)  /* At least x.abc */
        {
          if( !((NULL != szExceptFile)                                                          &&
                (4 == OS_Strlen(szExceptFile))                                                  &&
                (0 == OS_Strnicmp( szExceptFile, &tDirectoryEntry.szFilename[iStrlen - 4], 4)))   )
          {
            /* Delete file and continue with find first file again */
            DEV_DeleteFile( ptChannel, ulChannel, tDirectoryEntry.szFilename, pfnTransferPacket, pfnRecvPacket, pvUser);
          }
        } else
        {
          /* Not a valid file, search next file */
          fFindFirst = 0;
        }
      }
    } else
    {
      /* Search for more files */
      if ( !(CIFX_NO_ERROR == (lRet = xSysdeviceFindNextFile( ptChannel, ulChannel, &tDirectoryEntry, pfnRecvPacket, pvUser))))
      {
        /* No more files, or error during find next */
        break;
      } else
      {
        /* Is this a valid file name */
        int iStrlen = OS_Strlen(tDirectoryEntry.szFilename);
        if( iStrlen >= CIFX_MIN_FILE_NAME_LENGTH)  /* At least x.abc */
        {
          /* If firmware file, delete it, else search until all files checked */
          if( !((NULL != szExceptFile)                                            &&
                (4 == OS_Strlen(szExceptFile))                                    &&
                (0 == OS_Strnicmp( szExceptFile, &tDirectoryEntry.szFilename[iStrlen - 4], 4)))   )
          {
            /* Delete the file and start with find first again */
            DEV_DeleteFile( ptChannel, ulChannel, tDirectoryEntry.szFilename, pfnTransferPacket, pfnRecvPacket, pvUser);
            fFindFirst = 1;
          }
        }
      }
    }
  } while ( CIFX_NO_ERROR == lRet);

  return 1;
}

/*****************************************************************************/
/*! Check if we have a firmware file
*   \param pszFileName      Input file name
*   \return 1 on success                                                     */
/*****************************************************************************/
int DEV_IsFWFile( char* pszFileName)
{
  /* Check if we have a .NXO, .NXF,.NXM or .MOD extension */
  int fRet    = 0;
  int iStrlen = OS_Strlen(pszFileName);

  if( iStrlen >= CIFX_MIN_FILE_NAME_LENGTH)  /* At least x.abc */
  {
    if ( (0 == OS_Strnicmp( HIL_FILE_EXTENSION_FIRMWARE, &pszFileName[iStrlen - 4], 4) ) ||
         (0 == OS_Strnicmp( HIL_FILE_EXTENSION_MODULE, &pszFileName[iStrlen - 4], 4) )   ||
         (0 == OS_Strnicmp( HIL_FILE_EXTENSION_OPTION, &pszFileName[iStrlen - 4], 4) )   ||
         (0 == OS_Strnicmp( ".MOD", &pszFileName[iStrlen - 4], 4) )  )
    {
      fRet = 1;
    }
  }

  return fRet;
}

/*****************************************************************************/
/*! Check if we have a NXO file
*   \param pszFileName      Input file name
*   \return 1 on success                                                     */
/*****************************************************************************/
int DEV_IsNXOFile( char* pszFileName)
{
  /* Check if we have a .NXO, .NXF,.NXM or .MOD extension */
  int fRet    = 0;
  int iStrlen = OS_Strlen(pszFileName);

  if( iStrlen >= CIFX_MIN_FILE_NAME_LENGTH)  /* At least x.abc */
  {
    if ( 0 == OS_Strnicmp( HIL_FILE_EXTENSION_OPTION, &pszFileName[iStrlen - 4], 4) )
    {
      fRet = 1;
    }
  }

  return fRet;
}

/*****************************************************************************/
/*! Check if we have a NXF file
*   \param pszFileName      Input file name
*   \return 1 on success                                                     */
/*****************************************************************************/
int DEV_IsNXFFile( char* pszFileName)
{
  /* Check if we have a .NXO, .NXF,.NXM or .MOD extension */
  int fRet    = 0;
  int iStrlen = OS_Strlen(pszFileName);

  if( iStrlen >= CIFX_MIN_FILE_NAME_LENGTH)  /* At least x.abc */
  {
    if ( 0 == OS_Strnicmp( HIL_FILE_EXTENSION_FIRMWARE, &pszFileName[iStrlen - 4], 4) )
    {
      fRet = 1;
    }
  }

  return fRet;
}

/*****************************************************************************/
/*! Delete existing firmware file from file system.
* This should prevent multiple firmware files in the file system, where
* only the first one is usable.
*   \param ptChannel          Channel instance
*   \param ulChannel          Channel number
*   \param pfnTransferPacket  Function used for transferring packets
*   \param pfnRecvPacket      User callback for unsolicited receive packets
*   \param pvUser             User parameter passed on callback
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int DEV_RemoveFWFiles(PCHANNELINSTANCE ptChannel, uint32_t ulChannel,
                      PFN_TRANSFER_PACKET    pfnTransferPacket,
                      PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                      void*                  pvUser)
{
  /* Try to find file with the extension *.nxm, *.nxf, *.mod and remove it */
  CIFX_DIRECTORYENTRY tDirectoryEntry;
  int32_t             lRet            = CIFX_NO_ERROR;
  int                 fFindFirst      = 1;

  OS_Memset(&tDirectoryEntry, 0, sizeof(tDirectoryEntry));

  /* Search for all firmware files. If one is found. delete it an start with find first again, */
  /* because we can't store a directory list in here */
  do
  {
    if ( fFindFirst)
    {
      /* Search first file */
      if ( !(CIFX_NO_ERROR == (lRet = xSysdeviceFindFirstFile( ptChannel, ulChannel, &tDirectoryEntry, pfnRecvPacket, pvUser))))
      {
        /* No more files, or error during find first */
        break;
      } else
      {
        /* Check for firmware file */
        if( DEV_IsFWFile( tDirectoryEntry.szFilename))
        {
          /* Delete file and continue with find first file again */
          DEV_DeleteFile( ptChannel, ulChannel, tDirectoryEntry.szFilename, pfnTransferPacket, pfnRecvPacket, pvUser);
        } else
        {
          /* Not a firmware, search next file */
          fFindFirst = 0;
        }
      }
    } else
    {
      /* Search for more files */
      if ( !(CIFX_NO_ERROR == (lRet = xSysdeviceFindNextFile( ptChannel, ulChannel, &tDirectoryEntry, pfnRecvPacket, pvUser))))
      {
        /* No more files, or error during find next */
        break;
      } else
      {
        /* If firmware file, delete it, else search until all files checked */
        if (DEV_IsFWFile( tDirectoryEntry.szFilename))
        {
          /* Delete file and continue with find first file again */
          DEV_DeleteFile( ptChannel, ulChannel, tDirectoryEntry.szFilename, pfnTransferPacket, pfnRecvPacket, pvUser);
          fFindFirst = 1;
        }
      }
    }
  } while ( CIFX_NO_ERROR == lRet);

  return 1;
}

/*****************************************************************************/
/*! Delete the given file
*   \param pvChannel          Channel instance
*   \param ulChannelNumber    Channel number
*   \param pszFileName        Input file name
*   \param pfnTransferPacket  Function used for transferring packets
*   \param pfnRecvPacket      User callback for unsolicited receive packets
*   \param pvUser             User parameter passed on callback
*   \return 1 on success                                                     */
/*****************************************************************************/
int32_t DEV_DeleteFile(void* pvChannel, uint32_t ulChannelNumber, char* pszFileName,
                       PFN_TRANSFER_PACKET    pfnTransferPacket,
                       PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                       void*                  pvUser)
{
  /* Create delete packet */
  union
  {
    CIFX_PACKET           tPacket;
    RCX_FILE_DELETE_REQ_T tFileDelete;
    
  }                       uSendPkt;
  CIFX_PACKET             tConf;
  uint16_t                usFileNameLen = (uint16_t)OS_Strlen(pszFileName);
  int32_t                 lRet          = CIFX_NO_ERROR;
  uint32_t                ulSrc         = OS_GetMilliSecCounter(); /* Early versions used pvChannel as ulSrc,
                                                                      but this won't work on 64 Bit machines.
                                                                      As we need something unique we use the current system time */


  OS_Memset(&uSendPkt, 0, sizeof(uSendPkt));
  OS_Memset(&tConf,    0, sizeof(tConf));

  /* Initialize the message */
  uSendPkt.tFileDelete.tHead.ulSrc    = HOST_TO_LE32(ulSrc);
  uSendPkt.tFileDelete.tHead.ulDest   = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
  uSendPkt.tFileDelete.tHead.ulCmd    = HOST_TO_LE32(RCX_FILE_DELETE_REQ);
  uSendPkt.tFileDelete.tHead.ulExt    = HOST_TO_LE32(RCX_PACKET_SEQ_NONE);
  uSendPkt.tFileDelete.tHead.ulLen    = HOST_TO_LE32((uint32_t)(sizeof(uSendPkt.tFileDelete.tData) + 
                                                                usFileNameLen + 1));

  /* Insert file data */
  uSendPkt.tFileDelete.tData.ulChannelNo      = HOST_TO_LE32(ulChannelNumber);
  uSendPkt.tFileDelete.tData.usFileNameLength = HOST_TO_LE16( (uint16_t)(usFileNameLen + 1) );

  /* Insert file name */
  OS_Strncpy( (char*)(&uSendPkt.tFileDelete.tData + 1), 
              pszFileName, 
              (uint32_t)(sizeof(uSendPkt.tPacket.abData) - sizeof(uSendPkt.tFileDelete.tData)));

  /* Send delete packet */
  lRet = pfnTransferPacket( pvChannel,
                            &uSendPkt.tPacket,
                            (CIFX_PACKET*)&tConf,
                            (uint32_t)sizeof(tConf),
                            CIFX_TO_FIRMWARE_START,       /* Could take a little while */
                            pfnRecvPacket,
                            pvUser);

  if(CIFX_NO_ERROR == lRet)
    lRet = LE32_TO_HOST(tConf.tHeader.ulState);

  return lRet;
}

/*****************************************************************************/
/*! Get the firmware transfer type from file name
*   \param pszFileName      Input file name
*   \param pulTransferType  Buffer for transfer type
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t DEV_GetFWTransferTypeFromFileName( char*          pszFileName,
                                        uint32_t* pulTransferType)
{
  /* Check if we have a NXF or .NXM / .MOD extension */
  int32_t lRet = CIFX_NO_ERROR;

  int iStrlen = OS_Strlen(pszFileName);
  if( iStrlen < CIFX_MIN_FILE_NAME_LENGTH)  /* At least x.abc */
  {
    lRet = CIFX_FILE_NAME_INVALID;
  } else
  {
    /* Check if we have a valid firmware file */
    if (!DEV_IsFWFile( pszFileName))
    {
      lRet = CIFX_FILE_TYPE_INVALID;
    } else
    {
      /* We have a firmware file, choose the correct download type */
      if ( (0 == OS_Strnicmp( HIL_FILE_EXTENSION_MODULE, &pszFileName[iStrlen - 4], 4) ) ||
           (0 == OS_Strnicmp( HIL_FILE_EXTENSION_OPTION, &pszFileName[iStrlen - 4], 4) ) ||
           (0 == OS_Strnicmp( ".MOD", &pszFileName[iStrlen - 4], 4) )  )
      {
        /* We are using the module file transfer type */
        *pulTransferType = RCX_FILE_XFER_MODULE;
      } else
      {
        /* All other files are downloaded via the file transfer type */
        *pulTransferType = RCX_FILE_XFER_FILE;
      }
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! Check if we have to download a file
*   \param pvChannel          Channel instance
*   \param ulChannelNumber    Channel number
*   \param pfDownload         Download flag
*   \param pszFileName        File name
*   \param pvFileData         File data buffer
*   \param ulFileSize         File size
*   \param pfnTransferPacket  Transfer packet function
*   \param pfnRecvPacket      Receive packet callback for unhandled packets
*   \param pvUser             User data for callback functions
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t DEV_CheckForDownload( void* pvChannel, uint32_t ulChannelNumber, int* pfDownload,
                           char* pszFileName, void* pvFileData, uint32_t ulFileSize,
                           PFN_TRANSFER_PACKET   pfnTransferPacket,
                           PFN_RECV_PKT_CALLBACK pfnRecvPacket,
                           void*                 pvUser)
{
  int32_t          lRet          = CIFX_NO_ERROR;
  PCHANNELINSTANCE ptChannel     = (PCHANNELINSTANCE)pvChannel;
  PDEVICEINSTANCE  ptDevInstance = (PDEVICEINSTANCE)ptChannel->pvDeviceInstance;

  /* Read the MD5 from the system */
  union
  {
    CIFX_PACKET            tPacket;
    RCX_FILE_GET_MD5_REQ_T tRequest;
  }                       uSendPkt;
  union
  {
    CIFX_PACKET            tPacket;
    RCX_FILE_GET_MD5_CNF_T tConf;
  }                       uConf;
  uint16_t                usFileNameLen = (uint16_t)OS_Strlen(pszFileName);
  uint32_t                ulSrc         = OS_GetMilliSecCounter(); /* Early versions used pvChannel as ulSrc,
                                                                      but this won't work on 64 Bit machines.
                                                                      As we need something unique we use the current system time */

  OS_Memset(&uSendPkt, 0, sizeof(uSendPkt));
  OS_Memset(&uConf,    0, sizeof(uConf));

  /* Set flag to download always neccessary */
  *pfDownload = 1;

  /* Initialize the message */
  uSendPkt.tRequest.tHead.ulSrc              = HOST_TO_LE32(ulSrc);
  uSendPkt.tRequest.tHead.ulDest             = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
  uSendPkt.tRequest.tHead.ulCmd              = HOST_TO_LE32(RCX_FILE_GET_MD5_REQ);
  uSendPkt.tRequest.tHead.ulExt              = HOST_TO_LE32(RCX_PACKET_SEQ_NONE);
  uSendPkt.tRequest.tHead.ulLen              = HOST_TO_LE32((uint32_t)(sizeof(uSendPkt.tRequest.tData) + usFileNameLen + 1));
  uSendPkt.tRequest.tData.usFileNameLength   = HOST_TO_LE16( (uint16_t)(usFileNameLen + 1) );
  uSendPkt.tRequest.tData.ulChannelNo        = HOST_TO_LE32(ulChannelNumber);

  OS_Strncpy( (char*)(&uSendPkt.tRequest.tData + 1), 
              pszFileName, 
              (uint32_t)(sizeof(uSendPkt.tPacket.abData) - sizeof(uSendPkt.tRequest.tData)) );

  /* Read the MD5 from the system */
  lRet = pfnTransferPacket( pvChannel,
                            &uSendPkt.tPacket,
                            &uConf.tPacket,
                            (uint32_t)sizeof(uConf.tPacket),
                            CIFX_TO_FIRMWARE_START,       /* Could take a little while */
                            pfnRecvPacket,
                            pvUser);
  
  if(CIFX_NO_ERROR != lRet)
  {
    /* Error reading MD5 checksum */
    if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
    {
      USER_Trace(ptDevInstance,
                 TRACE_LEVEL_ERROR,
                 "Failed to send MD5 request, lRet = 0x%08x", lRet);
    }
  } else if(RCX_S_OK != LE32_TO_HOST(uConf.tConf.tHead.ulSta))
  {
    /* Error reading MD5 checksum */
    if(g_ulTraceLevel & TRACE_LEVEL_INFO)
    {
      USER_Trace(ptDevInstance,
                 TRACE_LEVEL_INFO,
                 "No MD5 Information available. Probably the file does not exist on device. (ulState = 0x%08x)", 
                 uConf.tConf.tHead.ulSta);
    }
  } else
  {
    /* We got an MD5 from the rcX, test it */
    /* Calculate MD5 */
    md5_state_t tMd5State;
    md5_byte_t  abMd5[16];

    OS_Memset(abMd5, 0, sizeof(abMd5));

    md5_init(&tMd5State);
    md5_append(&tMd5State, (md5_byte_t*)pvFileData, ulFileSize);
    md5_finish(&tMd5State, abMd5);

    if(OS_Memcmp(abMd5, uConf.tConf.tData.abMD5, sizeof(abMd5)) == 0)
    {
      /* same file already on device, suppress download */
      *pfDownload = 0;

      /* MD5 checksum is equal, no download necessary */
      if(g_ulTraceLevel & TRACE_LEVEL_INFO)
      {
        USER_Trace(ptDevInstance,
                  TRACE_LEVEL_INFO,
                  "MD5 checksum is identical, download not necessary");
      }
      
    } else
    {
      /* MD5 checksum is not identical, download necessary */
      if(g_ulTraceLevel & TRACE_LEVEL_INFO)
      {
        USER_Trace(ptDevInstance,
                  TRACE_LEVEL_INFO,
                  "MD5 not identical, process file download");
      }
    }
  }

  return lRet;
}

/*****************************************************************************/
/*! CRC 32 lookup table                                                      */
/*****************************************************************************/
static uint32_t Crc32Table[256]=
{
  0x00000000UL, 0x77073096UL, 0xee0e612cUL, 0x990951baUL, 0x076dc419UL,
  0x706af48fUL, 0xe963a535UL, 0x9e6495a3UL, 0x0edb8832UL, 0x79dcb8a4UL,
  0xe0d5e91eUL, 0x97d2d988UL, 0x09b64c2bUL, 0x7eb17cbdUL, 0xe7b82d07UL,
  0x90bf1d91UL, 0x1db71064UL, 0x6ab020f2UL, 0xf3b97148UL, 0x84be41deUL,
  0x1adad47dUL, 0x6ddde4ebUL, 0xf4d4b551UL, 0x83d385c7UL, 0x136c9856UL,
  0x646ba8c0UL, 0xfd62f97aUL, 0x8a65c9ecUL, 0x14015c4fUL, 0x63066cd9UL,
  0xfa0f3d63UL, 0x8d080df5UL, 0x3b6e20c8UL, 0x4c69105eUL, 0xd56041e4UL,
  0xa2677172UL, 0x3c03e4d1UL, 0x4b04d447UL, 0xd20d85fdUL, 0xa50ab56bUL,
  0x35b5a8faUL, 0x42b2986cUL, 0xdbbbc9d6UL, 0xacbcf940UL, 0x32d86ce3UL,
  0x45df5c75UL, 0xdcd60dcfUL, 0xabd13d59UL, 0x26d930acUL, 0x51de003aUL,
  0xc8d75180UL, 0xbfd06116UL, 0x21b4f4b5UL, 0x56b3c423UL, 0xcfba9599UL,
  0xb8bda50fUL, 0x2802b89eUL, 0x5f058808UL, 0xc60cd9b2UL, 0xb10be924UL,
  0x2f6f7c87UL, 0x58684c11UL, 0xc1611dabUL, 0xb6662d3dUL, 0x76dc4190UL,
  0x01db7106UL, 0x98d220bcUL, 0xefd5102aUL, 0x71b18589UL, 0x06b6b51fUL,
  0x9fbfe4a5UL, 0xe8b8d433UL, 0x7807c9a2UL, 0x0f00f934UL, 0x9609a88eUL,
  0xe10e9818UL, 0x7f6a0dbbUL, 0x086d3d2dUL, 0x91646c97UL, 0xe6635c01UL,
  0x6b6b51f4UL, 0x1c6c6162UL, 0x856530d8UL, 0xf262004eUL, 0x6c0695edUL,
  0x1b01a57bUL, 0x8208f4c1UL, 0xf50fc457UL, 0x65b0d9c6UL, 0x12b7e950UL,
  0x8bbeb8eaUL, 0xfcb9887cUL, 0x62dd1ddfUL, 0x15da2d49UL, 0x8cd37cf3UL,
  0xfbd44c65UL, 0x4db26158UL, 0x3ab551ceUL, 0xa3bc0074UL, 0xd4bb30e2UL,
  0x4adfa541UL, 0x3dd895d7UL, 0xa4d1c46dUL, 0xd3d6f4fbUL, 0x4369e96aUL,
  0x346ed9fcUL, 0xad678846UL, 0xda60b8d0UL, 0x44042d73UL, 0x33031de5UL,
  0xaa0a4c5fUL, 0xdd0d7cc9UL, 0x5005713cUL, 0x270241aaUL, 0xbe0b1010UL,
  0xc90c2086UL, 0x5768b525UL, 0x206f85b3UL, 0xb966d409UL, 0xce61e49fUL,
  0x5edef90eUL, 0x29d9c998UL, 0xb0d09822UL, 0xc7d7a8b4UL, 0x59b33d17UL,
  0x2eb40d81UL, 0xb7bd5c3bUL, 0xc0ba6cadUL, 0xedb88320UL, 0x9abfb3b6UL,
  0x03b6e20cUL, 0x74b1d29aUL, 0xead54739UL, 0x9dd277afUL, 0x04db2615UL,
  0x73dc1683UL, 0xe3630b12UL, 0x94643b84UL, 0x0d6d6a3eUL, 0x7a6a5aa8UL,
  0xe40ecf0bUL, 0x9309ff9dUL, 0x0a00ae27UL, 0x7d079eb1UL, 0xf00f9344UL,
  0x8708a3d2UL, 0x1e01f268UL, 0x6906c2feUL, 0xf762575dUL, 0x806567cbUL,
  0x196c3671UL, 0x6e6b06e7UL, 0xfed41b76UL, 0x89d32be0UL, 0x10da7a5aUL,
  0x67dd4accUL, 0xf9b9df6fUL, 0x8ebeeff9UL, 0x17b7be43UL, 0x60b08ed5UL,
  0xd6d6a3e8UL, 0xa1d1937eUL, 0x38d8c2c4UL, 0x4fdff252UL, 0xd1bb67f1UL,
  0xa6bc5767UL, 0x3fb506ddUL, 0x48b2364bUL, 0xd80d2bdaUL, 0xaf0a1b4cUL,
  0x36034af6UL, 0x41047a60UL, 0xdf60efc3UL, 0xa867df55UL, 0x316e8eefUL,
  0x4669be79UL, 0xcb61b38cUL, 0xbc66831aUL, 0x256fd2a0UL, 0x5268e236UL,
  0xcc0c7795UL, 0xbb0b4703UL, 0x220216b9UL, 0x5505262fUL, 0xc5ba3bbeUL,
  0xb2bd0b28UL, 0x2bb45a92UL, 0x5cb36a04UL, 0xc2d7ffa7UL, 0xb5d0cf31UL,
  0x2cd99e8bUL, 0x5bdeae1dUL, 0x9b64c2b0UL, 0xec63f226UL, 0x756aa39cUL,
  0x026d930aUL, 0x9c0906a9UL, 0xeb0e363fUL, 0x72076785UL, 0x05005713UL,
  0x95bf4a82UL, 0xe2b87a14UL, 0x7bb12baeUL, 0x0cb61b38UL, 0x92d28e9bUL,
  0xe5d5be0dUL, 0x7cdcefb7UL, 0x0bdbdf21UL, 0x86d3d2d4UL, 0xf1d4e242UL,
  0x68ddb3f8UL, 0x1fda836eUL, 0x81be16cdUL, 0xf6b9265bUL, 0x6fb077e1UL,
  0x18b74777UL, 0x88085ae6UL, 0xff0f6a70UL, 0x66063bcaUL, 0x11010b5cUL,
  0x8f659effUL, 0xf862ae69UL, 0x616bffd3UL, 0x166ccf45UL, 0xa00ae278UL,
  0xd70dd2eeUL, 0x4e048354UL, 0x3903b3c2UL, 0xa7672661UL, 0xd06016f7UL,
  0x4969474dUL, 0x3e6e77dbUL, 0xaed16a4aUL, 0xd9d65adcUL, 0x40df0b66UL,
  0x37d83bf0UL, 0xa9bcae53UL, 0xdebb9ec5UL, 0x47b2cf7fUL, 0x30b5ffe9UL,
  0xbdbdf21cUL, 0xcabac28aUL, 0x53b39330UL, 0x24b4a3a6UL, 0xbad03605UL,
  0xcdd70693UL, 0x54de5729UL, 0x23d967bfUL, 0xb3667a2eUL, 0xc4614ab8UL,
  0x5d681b02UL, 0x2a6f2b94UL, 0xb40bbe37UL, 0xc30c8ea1UL, 0x5a05df1bUL,
  0x2d02ef8d
};

/*****************************************************************************/
/*! Create a CRC32 value from the given buffer data
*   \param ulCRC Continued CRC32 value
*   \param pabBuffer Buffer to create the CRC from
*   \param ulLength Buffer length
*   \return CRC32 value                                                      */
/*****************************************************************************/
static uint32_t CreateCRC32(uint32_t ulCRC, uint8_t* pabBuffer, uint32_t ulLength)
{
  if( (0 == pabBuffer) || (0 == ulLength) ) return ulCRC;
  ulCRC = ulCRC ^ 0xffffffff;
  for(;ulLength > 0; --ulLength)
  {
    ulCRC = (Crc32Table[((ulCRC) ^ (*(pabBuffer++)) ) & 0xff] ^ ((ulCRC) >> 8));
  }
  return ulCRC ^ 0xffffffff;
}

/*****************************************************************************/
/*! Process firmware download
*   \param ptDevInstance      Instance to start up
*   \param ulChannel          Channel number
*   \param pszFullFileName    Full file name (used for opening file)
*   \param pszFileName        Short file name (used on device)
*   \param ulFileLength       Length of the file
*   \param pbBuffer           File buffer
*   \param pbLoadState        Returned action of download (see CIFXTKIT_DOWNLOAD_XXX)
*   \param pfnTransferPacket  Function to used for exchanging packets
*   \param pfnCallback        Progress callback
*   \param pfnRecvPktCallback Callback for unexpected packets
*   \param pvUser             Callback user parameter
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t DEV_ProcessFWDownload( PDEVICEINSTANCE       ptDevInstance,
                               uint32_t              ulChannel,
                               char*                 pszFullFileName,
                               char*                 pszFileName,
                               uint32_t              ulFileLength,
                               uint8_t*              pbBuffer,
                               uint8_t*              pbLoadState,
                               PFN_TRANSFER_PACKET   pfnTransferPacket,
                               PFN_PROGRESS_CALLBACK pfnCallback,
                               PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,
                               void*                 pvUser)
{
  PCHANNELINSTANCE ptSysDevice = &ptDevInstance->tSystemDevice;
  int32_t          lRet        = CIFX_NO_ERROR;

  *pbLoadState  =  CIFXTKIT_DOWNLOAD_NONE;

  /*------------------------------------------------------------*/
  /* Process the firmware download depending on the eDeviceType */
  /*------------------------------------------------------------*/
  switch (ptDevInstance->eDeviceType)
  {
    /*----------------------------*/
    /* This is a RAM based device */
    /*----------------------------*/
    /* - RAM based devices are started by a RESET and therefore it is not necessary to delete a file */
    /* - Firmware files (NXF) and/or Modules (NXO) are loaded into RAM and not into the file system */
    case eCIFX_DEVICE_RAM_BASED:
    {
      /* We have not to delete files but we have to change the "transfer type" of the file */
      uint32_t ulTransfertype = RCX_FILE_XFER_MODULE;

      /* Check if we have a NXF*/
      if( DEV_IsNXFFile(pszFileName) &&
          (0 != ulChannel) )
      {
        /* Downloading an NXF to a channel other than 0 is not supported */
        if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
        {
          USER_Trace(ptDevInstance,
                      TRACE_LEVEL_ERROR,
                      "Error channel number %u for a firmware is not supported",
                      ulChannel);
        }

      /* Check if we have an NXO file */
      } else if( DEV_IsNXOFile(pszFileName) &&
                 (!ptDevInstance->fModuleLoad))
      {
        /* Downloading an NXO without a running Base OS is not allowed */
        if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
        {
          USER_Trace(ptDevInstance,
                      TRACE_LEVEL_ERROR,
                      "Error NXO files are not allowed without a Base OS firmware");
        }
      } else
      {
        /* Download the file stored in the buffer */
        lRet = DEV_DownloadFile(ptSysDevice,
                                ulChannel,
                                ptDevInstance->tSystemDevice.tSendMbx.ulSendMailboxLength,
                                ulTransfertype,
                                pszFileName,
                                ulFileLength,
                                pbBuffer,
                                pfnTransferPacket,
                                pfnCallback,
                                pfnRecvPktCallback,
                                pvUser);

        if(CIFX_NO_ERROR != lRet)
        {
          if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
          {
            USER_Trace(ptDevInstance,
                      TRACE_LEVEL_ERROR,
                      "Error downloading firmware to device '%s'\r\n"\
                      " - (lRet=0x%08X)!",
                      pszFullFileName,
                      lRet);
          }
        } else
        {
          /*-----------------------*/
          /* We have loaded a file */
          /*-----------------------*/

          /* Check if we have a NXF */
          if ( DEV_IsNXFFile( pszFileName))
          {
            /* NXF loaded, store information for startup handling */
            *pbLoadState = CIFXTKIT_DOWNLOAD_FIRMWARE | CIFXTKIT_DOWNLOAD_EXECUTED; /* we have a firmware loaded */
          }

          /* Check if we have a NXO */
          if ( DEV_IsNXOFile( pszFileName))
          {
            /* NXO loaded, store information for startup handling */
            *pbLoadState = CIFXTKIT_DOWNLOAD_MODULE  | CIFXTKIT_DOWNLOAD_EXECUTED;  /* we have a module loaded */
          }

          if(g_ulTraceLevel & TRACE_LEVEL_DEBUG)
          {
            USER_Trace(ptDevInstance,
                      TRACE_LEVEL_DEBUG,
                      "Successfully downloaded the firmware to device '%s'!",
                      pszFullFileName);
          }
        }
      }
    }
    break;

    /*------------------------------*/
    /* This is a FLASH based device */
    /*------------------------------*/
    /* - FLASH based devices are not reseted on the beginning */
    /* - Files are checked if they are already existing to prevent a download into FLASH */
    /* - If a new firmware files (NXF) is loaded, all other files (NXD/NXO etc) are deleted in all "PORTs" */
    /* - Firmware files are only allowed for PORT0 */
    /* - If an NXO is downloaded, all files (NXO/NXD) are deleted first. An existing NXF must be protected, because it is the base module! */
    case eCIFX_DEVICE_FLASH_BASED:
    {
      /* We have not to delete files but we have to change the "transfer type" of the file */
      uint32_t ulTransfertype  = RCX_FILE_XFER_FILE;
      int      fDownload       = 0;

      /* Does the file exist on the hardware, if so, skip the download */
      if ( CIFX_NO_ERROR != (lRet = DEV_CheckForDownload( ptSysDevice,
                                                          ulChannel,
                                                          &fDownload,
                                                          pszFileName,
                                                          pbBuffer,
                                                          ulFileLength,
                                                          pfnTransferPacket,
                                                          NULL,
                                                          NULL)))
      {
        /* Display an error */
        if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
        {
          USER_Trace(ptDevInstance,
                      TRACE_LEVEL_ERROR,
                      "Error checking for download '%s'!",
                      pszFullFileName);
        }

      /* Check if we have to download the file */
      } else if(!fDownload)
      {
        /*-----------------------------------*/
        /* Download not necessary            */
        /*-----------------------------------*/
        /* Store NXO Information for startup */
        if(DEV_IsNXOFile(pszFileName))
        {
          if( !ptDevInstance->fModuleLoad)
          {
            /* Downloading an NXO without a running Base OS is not allowed */
            if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
            {
              USER_Trace(ptDevInstance,
                          TRACE_LEVEL_ERROR,
                          "Error NXO files are not allowed without a Base OS firmware");
            }

            lRet = CIFX_FILE_TYPE_INVALID;

          } else
          {
            if(g_ulTraceLevel & TRACE_LEVEL_DEBUG)
            {
              USER_Trace(ptDevInstance,
                        TRACE_LEVEL_DEBUG,
                        "Skipping download for file '%s'\r\n" \
                        "[checksum identical]!",
                        pszFullFileName);
            }

            *pbLoadState = CIFXTKIT_DOWNLOAD_MODULE;
          }
        } else if(DEV_IsNXFFile(pszFileName))
        {
          *pbLoadState = CIFXTKIT_DOWNLOAD_FIRMWARE;
        } else
        {
          lRet = CIFX_FILE_TYPE_INVALID;
        }
      } else
      {

        /*-----------------------------------*/
        /* Download is necessary             */
        /*-----------------------------------*/
        /* Check if we have a NXF*/
        if( DEV_IsNXFFile(pszFileName))
        {
          if (0 != ulChannel)
          {
            /* Downloading an NXF to a channel other than 0 is not supported */
            if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
            {
              USER_Trace(ptDevInstance,
                          TRACE_LEVEL_ERROR,
                          "Error channel number %u for a firmware is not supported",
                          ulChannel);
            }
            lRet = CIFX_INVALID_PARAMETER;
            fDownload = 0;

          } else
          {
            /* ATTENTION: If we are downloading an "NXF" file, we have a complete firmware.     */
            /*            In this case all other files should be deleted!                       */
            /*            NXF are stored under channel 0                                        */

            /* Files for a flash based device are always transfered into the FLASH file system */
            /* We have to delete existing files, depending of a NXF/NXO */
            uint32_t ulChNum = 0;

            /* Remove ALL files */
            for ( ulChNum = 0; ulChNum < CIFX_MAX_NUMBER_OF_CHANNELS; ulChNum++)
            {
              DEV_RemoveChannelFiles(ptSysDevice, ulChannel, pfnTransferPacket, NULL, NULL, NULL);
            }

            /* We have loaded a new firmware file */
            *pbLoadState = CIFXTKIT_DOWNLOAD_FIRMWARE;
          }

         /* Check if we have an NXO file */
        } else if( DEV_IsNXOFile(pszFileName))
        {
          if( !ptDevInstance->fModuleLoad)
          {
            /* Downloading an NXO without a running Base OS is not allowed */
            if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
            {
              USER_Trace(ptDevInstance,
                          TRACE_LEVEL_ERROR,
                          "Error NXO files are not allowed without a Base OS firmware");
            }

            lRet = CIFX_FILE_TYPE_INVALID;
            fDownload = 0;

          } else
          {
            /* ATTENTION: If the file is an "NXO", we have to delete all files EXCEPT the "NXF" */
            /*            because this is our BASE OS file!                                     */
            /*            NXF are stored under channel 0, NXOs are storeable in each channel    */

            /* Files for a flash based device are always transfered into the FLASH file system */
            /* We have to delete existing files, depending of a NXF/NXO */
            /* Leave NXF file */
            DEV_RemoveChannelFiles( ptSysDevice, ulChannel, pfnTransferPacket, NULL, NULL, HIL_FILE_EXTENSION_FIRMWARE);

            /* We have loaded a new module */
            *pbLoadState = CIFXTKIT_DOWNLOAD_MODULE;
          }
        } else
        {
          /* TODO: Unsupported file , do we need to check this???*/
          fDownload = 0;
        }

        if(fDownload)
        {
          /* Download the file stored in the buffer */
          lRet = DEV_DownloadFile(ptSysDevice,
                                  ulChannel,
                                  ptDevInstance->tSystemDevice.tSendMbx.ulSendMailboxLength,
                                  ulTransfertype,
                                  pszFileName,
                                  ulFileLength,
                                  pbBuffer,
                                  pfnTransferPacket,
                                  NULL,
                                  NULL,
                                  NULL);

          if(CIFX_NO_ERROR != lRet)
          {
            if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
            {
              USER_Trace(ptDevInstance,
                        TRACE_LEVEL_ERROR,
                        "Error downloading firmware to device '%s'\r\n"\
                        " - (lRet=0x%08X)!",
                        pszFullFileName,
                        lRet);
            }

          } else
          {
            if(g_ulTraceLevel & TRACE_LEVEL_DEBUG)
            {
              USER_Trace(ptDevInstance,
                        TRACE_LEVEL_DEBUG,
                        "Successfully downloaded the firmware to device '%s'!",
                        pszFullFileName);
            }

            *pbLoadState |= CIFXTKIT_DOWNLOAD_EXECUTED;
          }
        }
      }
    }
    break;

    default:
      /* Unknown device type */
      if(g_ulTraceLevel & TRACE_LEVEL_ERROR)
      {
        USER_Trace(ptDevInstance,
                    TRACE_LEVEL_ERROR,
                    "Error unsupported device type %u found for download handling!",
                    ptDevInstance->eDeviceType);
      }
    break;

  } /* end switch */

  return lRet;
}

/*****************************************************************************/
/*! Download a file to the hardware
*   \param pvChannel          Channel instance the download is performed on
*   \param ulChannel          Channel number the download is for
*   \param ulMailboxSize      Size of the mailbox
*   \param ulTransferType     Type of transfer (see RCX_FILE_XFER_XXX defines)
*   \param szFileName         Short file name (needed by firmware to create the file by name)
*   \param ulFileLength       Length of the file to download
*   \param pvData             File data being downloaded
*   \param pfnTransferPacket  Function used for transferring packets
*   \param pfnCallback        User callback for download progress indications
*   \param pfnRecvPktCallback User callback for unsolicited receive packets
*   \param pvUser             User parameter passed on callback
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t DEV_DownloadFile(void*                 pvChannel,
                         uint32_t              ulChannel,
                         uint32_t              ulMailboxSize,
                         uint32_t              ulTransferType,
                         char*                 szFileName,
                         uint32_t              ulFileLength,
                         void*                 pvData,
                         PFN_TRANSFER_PACKET   pfnTransferPacket,
                         PFN_PROGRESS_CALLBACK pfnCallback,
                         PFN_RECV_PKT_CALLBACK pfnRecvPktCallback,
                         void*                 pvUser)
{
  union
  {
    CIFX_PACKET                   tPacket;
    RCX_FILE_DOWNLOAD_REQ_T       tDownloadReq;
    RCX_FILE_DOWNLOAD_DATA_REQ_T  tDownloadDataReq;
    RCX_FILE_DOWNLOAD_ABORT_REQ_T tAbortReq;
  }          uSendPkt;
  union
  {
    CIFX_PACKET                   tPacket;
    RCX_FILE_DOWNLOAD_CNF_T       tDownloadCnf;
    RCX_FILE_DOWNLOAD_DATA_CNF_T  tDownloadDataCnf;    
    RCX_FILE_DOWNLOAD_ABORT_CNF_T tAbortCnf;
  }          uRecvPkt;

  /* Set download state informations */
  uint32_t   ulMaxDataLength     = ulMailboxSize -  /* Maximum possible user data length */
                                   (uint32_t)sizeof(RCX_FILE_DOWNLOAD_DATA_REQ_T);
                                        
  uint32_t   ulSendLen           = 0;
  uint32_t   ulTransferedLength  = 0;
  uint8_t*   pabActData          = NULL;
  uint32_t   ulCRC               = 0;
  uint32_t   ulBlockNumber       = 0;
  uint32_t   ulState             = RCX_FILE_DOWNLOAD_REQ;
  uint32_t   ulCmdDataState      = RCX_PACKET_SEQ_NONE;
  int        fStopDownload       = 0;
  int32_t    lRetAbort           = CIFX_NO_ERROR;
  int32_t    lRet                = CIFX_NO_ERROR;
  uint32_t   ulCurrentId         = 0;
  uint32_t   ulSrc               = OS_GetMilliSecCounter(); /* Early versions used pvChannel as ulSrc,
                                                               but this won't work on 64 Bit machines.
                                                               As we need something unique we use the current system time */
  uint32_t   ulTransferTimeout   = CIFX_TO_SEND_PACKET;

  OS_Memset(&uSendPkt, 0, sizeof(uSendPkt));
  OS_Memset(&uRecvPkt, 0, sizeof(uRecvPkt));

  /* Check parameters */
  if( NULL == pvData)
    return CIFX_INVALID_POINTER;
  
  if( 0 == ulFileLength)
    return CIFX_INVALID_PARAMETER; 
   
  pabActData = (uint8_t*)pvData;
  
  /* Performce download */
  do
  {
    switch (ulState)
    {
      /* Send download request */
      case RCX_FILE_DOWNLOAD_REQ:
      {
        /* Validate filename length to fit mailbox/packet */
        uint32_t ulFileNameLength = min( (uint32_t)OS_Strlen(szFileName) + 1,
                                          ulMailboxSize - (uint32_t)sizeof(RCX_FILE_DOWNLOAD_REQ_T));

        /* Insert packet data */
        ++ulCurrentId;
        uSendPkt.tDownloadReq.tHead.ulDest   = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
        uSendPkt.tDownloadReq.tHead.ulSrc    = HOST_TO_LE32(ulSrc);
        uSendPkt.tDownloadReq.tHead.ulDestId = HOST_TO_LE32(0);
        uSendPkt.tDownloadReq.tHead.ulSrcId  = HOST_TO_LE32(0);
        uSendPkt.tDownloadReq.tHead.ulLen    = HOST_TO_LE32((uint32_t)(sizeof(RCX_FILE_DOWNLOAD_REQ_DATA_T) +
                                                                       ulFileNameLength));
        uSendPkt.tDownloadReq.tHead.ulId     = HOST_TO_LE32(ulCurrentId);
        uSendPkt.tDownloadReq.tHead.ulSta    = HOST_TO_LE32(0);
        uSendPkt.tDownloadReq.tHead.ulCmd    = HOST_TO_LE32(RCX_FILE_DOWNLOAD_REQ);
        uSendPkt.tDownloadReq.tHead.ulExt    = HOST_TO_LE32(ulCmdDataState);
        uSendPkt.tDownloadReq.tHead.ulRout   = HOST_TO_LE32(0);

        /* Insert command data (extended data) */
        uSendPkt.tDownloadReq.tData.ulFileLength     = HOST_TO_LE32(ulFileLength);
        uSendPkt.tDownloadReq.tData.ulMaxBlockSize   = HOST_TO_LE32(ulMaxDataLength);
        uSendPkt.tDownloadReq.tData.ulXferType       = HOST_TO_LE32(ulTransferType);
        uSendPkt.tDownloadReq.tData.ulChannelNo      = HOST_TO_LE32(ulChannel);
        uSendPkt.tDownloadReq.tData.usFileNameLength = HOST_TO_LE16((uint16_t)ulFileNameLength);
        OS_Strncpy( (char*)(&uSendPkt.tDownloadReq.tData + 1),
                    szFileName,
                    ulFileNameLength) ;

        /* Transfer packet */
        lRet = pfnTransferPacket(pvChannel,
                                 &uSendPkt.tPacket,
                                 &uRecvPkt.tPacket,
                                 (uint32_t)sizeof(uRecvPkt.tPacket),
                                 ulTransferTimeout,
                                 pfnRecvPktCallback,
                                 pvUser);

        if( (CIFX_NO_ERROR != lRet)                                 ||
            (RCX_S_OK      != (lRet = LE32_TO_HOST((int32_t)uRecvPkt.tDownloadCnf.tHead.ulSta))) )
        {
          /* Error during first packet, end download */
          /* Send progress notification */
          if(pfnCallback)
            pfnCallback(ulTransferedLength, ulFileLength, pvUser, CIFX_CALLBACK_FINISHED, lRet);

          /* Send abort request on unusable data */
          ulState = RCX_FILE_DOWNLOAD_ABORT_REQ;
        } else if( LE32_TO_HOST(uRecvPkt.tDownloadCnf.tData.ulMaxBlockSize) == 0)
        {
          /* Error in device information, stop download (Device returned illegal block size */
          lRet = CIFX_INVALID_ACCESS_SIZE;

          /* Send progress notification */
          if(pfnCallback)
            pfnCallback(ulTransferedLength, ulFileLength, pvUser, CIFX_CALLBACK_FINISHED, lRet);

          /* Send abort request on unusable data */
          ulState = RCX_FILE_DOWNLOAD_ABORT_REQ;
        } else
        {
          /* Everything went ok, so start transmitting file data now */
          /* Get download packet size from the device confirmation.
             If the devices packet size is smaller than our size, use the length from the device.
             Otherwise use our length. */
          if( ulMaxDataLength > LE32_TO_HOST(uRecvPkt.tDownloadCnf.tData.ulMaxBlockSize))
            ulMaxDataLength = LE32_TO_HOST(uRecvPkt.tDownloadCnf.tData.ulMaxBlockSize);

          /* Check if the file fits into one packet or if we have to send multiple packets */
          ulSendLen = ulMaxDataLength;
          if(ulFileLength <= ulSendLen)
          {
            /* We have only one packet to send */
            ulSendLen       = ulFileLength;
            ulCmdDataState  = RCX_PACKET_SEQ_NONE;
          } else
          {
            /* We have to send multiple packets */
            ulCmdDataState  = RCX_PACKET_SEQ_FIRST;
          }

          /* Goto next state */
          ulState = RCX_FILE_DOWNLOAD_DATA_REQ;
        }
      }
      break;

      /* Data download packets */
      case RCX_FILE_DOWNLOAD_DATA_REQ:
      {
        ++ulCurrentId;
        uSendPkt.tDownloadDataReq.tHead.ulDest     = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
        uSendPkt.tDownloadDataReq.tHead.ulSrc      = HOST_TO_LE32(ulSrc);
        uSendPkt.tDownloadDataReq.tHead.ulCmd      = HOST_TO_LE32(RCX_FILE_DOWNLOAD_DATA_REQ);
        uSendPkt.tDownloadDataReq.tHead.ulId       = HOST_TO_LE32(ulCurrentId);
        uSendPkt.tDownloadDataReq.tHead.ulExt      = HOST_TO_LE32(ulCmdDataState);

        /* Copy file data to packet */
        OS_Memcpy( &uSendPkt.tDownloadDataReq.tData + 1, pabActData, ulSendLen);

        /* Adjust packet length */
        uSendPkt.tDownloadDataReq.tHead.ulLen      = HOST_TO_LE32((uint32_t)(sizeof(RCX_FILE_DOWNLOAD_DATA_REQ_DATA_T) +
                                                                             ulSendLen));

        /* Create continued CRC */
        ulCRC = CreateCRC32( ulCRC, pabActData, ulSendLen);
        uSendPkt.tDownloadDataReq.tData.ulChksum   = HOST_TO_LE32(ulCRC);
        uSendPkt.tDownloadDataReq.tData.ulBlockNo  = HOST_TO_LE32(ulBlockNumber);
        ++ulBlockNumber;

        /* Transfer packet */
        lRet = pfnTransferPacket(pvChannel,
                                &uSendPkt.tPacket,
                                &uRecvPkt.tPacket,
                                (uint32_t)sizeof(uRecvPkt.tPacket),
                                ulTransferTimeout,
                                pfnRecvPktCallback,
                                pvUser);

        if( (CIFX_NO_ERROR != lRet)                                   ||
            (RCX_S_OK      != (lRet = LE32_TO_HOST((int32_t)(uRecvPkt.tDownloadDataCnf.tHead.ulSta)))) )
        {
          /* Driver error during transfer packet, end download */
          /* Always try to send an abort request */
          if(pfnCallback)
            pfnCallback(ulTransferedLength, ulFileLength, pvUser, CIFX_CALLBACK_FINISHED, lRet);

          ulState = RCX_FILE_DOWNLOAD_ABORT_REQ;
        } else
        {
          /* Add send size to transfered size */
          ulTransferedLength += ulSendLen;

          /* Indicate progress, if user wants a notification */
          if(pfnCallback)
            pfnCallback(ulTransferedLength, ulFileLength, pvUser,
                        (ulTransferedLength == ulFileLength) ? CIFX_CALLBACK_FINISHED : CIFX_CALLBACK_ACTIVE,
                        lRet);

          /* Check if we are done with the download */
          if( (RCX_PACKET_SEQ_LAST == ulCmdDataState) ||
              (RCX_PACKET_SEQ_NONE == ulCmdDataState) )
          {
            /* No more packets to send, end download */
            fStopDownload = 1;
          } else
          {
            /* Move data pointer to next data */
            pabActData += ulSendLen;

            /* Calculate next message length */
            if ( ulFileLength <= (ulSendLen + ulTransferedLength))
            {
              /* Set the send length to rest of data,
                 This will be the last packet */
              ulSendLen = ulFileLength - ulTransferedLength;
              ulCmdDataState = RCX_PACKET_SEQ_LAST;
              
              /* ATTENTION: Check the transfer type */
              if ( RCX_FILE_XFER_MODULE == ulTransferType)
              {
                /* Module loading will relocate the module with the last packet.
                   So the confirmation packet takes longer, depending on the 
                   file size (and contained firmware).
                   Measurements showed that for every 100kB the module needs 
                   one additional second for relocation */
                ulTransferTimeout += (ulFileLength / (100 * 1024)) * 1000;
              }
            } else
            {
              ulCmdDataState = RCX_PACKET_SEQ_MIDDLE;
            }

            /* Goto next state */
            ulState = RCX_FILE_DOWNLOAD_DATA_REQ;
          }
        }
      }
      break;

      /* Abort active download */
      case RCX_FILE_DOWNLOAD_ABORT_REQ:
      {
        ++ulCurrentId;
        uSendPkt.tAbortReq.tHead.ulDest   = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
        uSendPkt.tAbortReq.tHead.ulSrc    = HOST_TO_LE32(ulSrc);
        uSendPkt.tAbortReq.tHead.ulDestId = HOST_TO_LE32(0);
        uSendPkt.tAbortReq.tHead.ulSrcId  = HOST_TO_LE32(0);
        uSendPkt.tAbortReq.tHead.ulLen    = HOST_TO_LE32(0);
        uSendPkt.tAbortReq.tHead.ulId     = HOST_TO_LE32(ulCurrentId);
        uSendPkt.tAbortReq.tHead.ulSta    = HOST_TO_LE32(0);
        uSendPkt.tAbortReq.tHead.ulCmd    = HOST_TO_LE32(RCX_FILE_DOWNLOAD_ABORT_REQ);
        uSendPkt.tAbortReq.tHead.ulExt    = HOST_TO_LE32(RCX_PACKET_SEQ_NONE);
        uSendPkt.tAbortReq.tHead.ulRout   = HOST_TO_LE32(0);

        /* Transfer packet */
        lRetAbort = pfnTransferPacket(pvChannel,
                                      &uSendPkt.tPacket,
                                      &uRecvPkt.tPacket,
                                      (uint32_t)sizeof(uRecvPkt.tPacket),
                                      ulTransferTimeout,
                                      pfnRecvPktCallback,
                                      pvUser);

        if( lRetAbort == CIFX_NO_ERROR)
        {
          /* Return packet state if function succeeded */
          lRetAbort = LE32_TO_HOST((int32_t)uRecvPkt.tAbortCnf.tHead.ulSta);
        }

        /* End download */
        fStopDownload = 1;
      }
      break;

      default:
        /* unkonwn, leave command */
        lRet = CIFX_FUNCTION_FAILED;

        /* End download */
        fStopDownload = 1;
        break;
    }

  } while(!fStopDownload);

  /* Always return lRet first, thean abort error */
  if( CIFX_NO_ERROR != lRet)
    return lRet;
  else if( CIFX_NO_ERROR != lRetAbort)
    return lRetAbort;
  else
    return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! Uploads a file from the hardware. It is required to list the files
* on the hardware, to know the file length for creating the buffer.
*   \param pvChannel          Channel instance the upload is performed on
*   \param ulChannel          Channel number the upload made is for
*   \param ulMailboxSize      Size of the mailbox
*   \param ulTransferType     Type of transfer (see RCX_FILE_XFER_XXX defines)
*   \param szFileName         Short file name
*   \param pulDataBufferLen   Length of the provided buffer, returned length of data
*   \param pvData             Buffer for storing upload. This buffer must be allocated by the caller.
*   \param pfnTransferPacket  Function used for transferring packets
*   \param pfnCallback        User callback for upload progress indications
*   \param pfnRecvPktCallback User callback for unsolicited receive packets
*   \param pvUser             User parameter passed on callback
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
int32_t DEV_UploadFile(void*                   pvChannel,
                       uint32_t                ulChannel,
                       uint32_t                ulMailboxSize,
                       uint32_t                ulTransferType,
                       char*                   szFileName,
                       uint32_t*               pulDataBufferLen,
                       void*                   pvData,
                       PFN_TRANSFER_PACKET     pfnTransferPacket,
                       PFN_PROGRESS_CALLBACK   pfnCallback,
                       PFN_RECV_PKT_CALLBACK   pfnRecvPktCallback,
                       void*                   pvUser)
{
  /* Usually one brace should be enough, but GNU wants to have a second brace
     to initialize the structure. On GCC 4.0.3 the whole structure is initialized
     as described in ISOC90 */
  union
  {
    CIFX_PACKET                   tPacket;
    RCX_FILE_UPLOAD_REQ_T         tUploadReq;
    RCX_FILE_UPLOAD_DATA_REQ_T    tUploadDataReq;
    RCX_FILE_DOWNLOAD_ABORT_REQ_T tAbortReq;
  }                             uSendPkt;

  union
  {
    CIFX_PACKET                   tPacket;
    RCX_FILE_UPLOAD_CNF_T         tUploadCnf;
    RCX_FILE_UPLOAD_DATA_CNF_T    tUploadDataCnf;
  }                             uRecvPkt;

  uint16_t                      usFilenameLen     = (uint16_t)(OS_Strlen(szFileName) + 1); /*Firmware expects length including terminating NULL */
  uint32_t                      ulBlockSize       = ulMailboxSize -
                                                    (uint32_t)sizeof(uRecvPkt.tUploadDataCnf); /* maximum size of each file block */
  int                           fSendAbort        = 0;
  int32_t                       lRetAbort         = CIFX_NO_ERROR;
  int32_t                       lRet              = CIFX_NO_ERROR;
  uint32_t                      ulCurrentId       = 0;
  uint32_t                      ulSrc             = OS_GetMilliSecCounter(); /* Early versions used pvChannel as ulSrc,
                                                                                but this won't work on 64 Bit machines.
                                                                                As we need something unique we use the current system time */

  OS_Memset(&uSendPkt, 0, sizeof(uSendPkt));
  OS_Memset(&uRecvPkt, 0, sizeof(uRecvPkt));

  /* Check parameters */
  if( (NULL == pvData) || (NULL == pulDataBufferLen) )
    return CIFX_INVALID_POINTER;

  if( ulMailboxSize < NETX_SYSTEM_MAILBOX_MIN_SIZE)
    return CIFX_DEV_MAILBOX_TOO_SHORT;

  ++ulCurrentId;
  uSendPkt.tUploadReq.tHead.ulDest             = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
  uSendPkt.tUploadReq.tHead.ulSrc              = HOST_TO_LE32(ulSrc);
  uSendPkt.tUploadReq.tHead.ulDestId           = HOST_TO_LE32(0);
  uSendPkt.tUploadReq.tHead.ulSrcId            = HOST_TO_LE32(0);
  uSendPkt.tUploadReq.tHead.ulLen              = HOST_TO_LE32((uint32_t)(sizeof(uSendPkt.tUploadReq.tData) + usFilenameLen));
  uSendPkt.tUploadReq.tHead.ulId               = HOST_TO_LE32(ulCurrentId);
  uSendPkt.tUploadReq.tHead.ulSta              = HOST_TO_LE32(0);
  uSendPkt.tUploadReq.tHead.ulCmd              = HOST_TO_LE32(RCX_FILE_UPLOAD_REQ);
  uSendPkt.tUploadReq.tHead.ulExt              = HOST_TO_LE32(RCX_PACKET_SEQ_NONE);
  uSendPkt.tUploadReq.tHead.ulRout             = HOST_TO_LE32(0);

  uSendPkt.tUploadReq.tData.usFileNameLength   = HOST_TO_LE16(usFilenameLen);
  uSendPkt.tUploadReq.tData.ulXferType         = HOST_TO_LE32(ulTransferType);
  uSendPkt.tUploadReq.tData.ulMaxBlockSize     = HOST_TO_LE32(ulBlockSize);
  uSendPkt.tUploadReq.tData.ulChannelNo        = HOST_TO_LE32(ulChannel);

  OS_Strncpy((char*)(&uSendPkt.tUploadReq.tData + 1), szFileName, usFilenameLen);

  lRet = pfnTransferPacket(pvChannel,
                           &uSendPkt.tPacket,
                           &uRecvPkt.tPacket,
                           (uint32_t)sizeof(uRecvPkt.tPacket),
                           CIFX_TO_SEND_PACKET,
                           pfnRecvPktCallback,
                           pvUser);
  if( (CIFX_NO_ERROR != lRet)                               ||
      (RCX_S_OK      != (lRet = LE32_TO_HOST(uRecvPkt.tPacket.tHeader.ulState))) )
  {
    /* Send progress notification */
    if(pfnCallback)
      pfnCallback( 0, 0, pvUser, CIFX_CALLBACK_FINISHED, lRet);

    fSendAbort = 1;
  } else
  {
    uint32_t ulFileLength = LE32_TO_HOST(uRecvPkt.tUploadCnf.tData.ulFileLength);

    if(ulFileLength > *pulDataBufferLen)
    {
      fSendAbort = 1;
      lRet = CIFX_INVALID_BUFFERSIZE;
    } else
    {
      uint32_t  ulCRC              = 0;
      uint8_t* pbData             = (uint8_t*)pvData; /* pointer to return buffer */
      uint32_t  ulTransferredBytes = 0;
      uint32_t  ulTotalBytes       = ulFileLength;

      /* Set user file read data to 0 */
      *pulDataBufferLen = 0;

      /* Create upload data packet */
      ++ulCurrentId;
      OS_Memset( &uSendPkt.tUploadDataReq, 0, sizeof(uSendPkt.tUploadDataReq));
      uSendPkt.tUploadDataReq.tHead.ulDest     = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
      uSendPkt.tUploadDataReq.tHead.ulSrc      = HOST_TO_LE32(ulSrc);
      uSendPkt.tUploadDataReq.tHead.ulDestId   = HOST_TO_LE32(0);
      uSendPkt.tUploadDataReq.tHead.ulSrcId    = HOST_TO_LE32(0);
      uSendPkt.tUploadDataReq.tHead.ulLen      = HOST_TO_LE32(0);
      uSendPkt.tUploadDataReq.tHead.ulId       = HOST_TO_LE32(ulCurrentId);
      uSendPkt.tUploadDataReq.tHead.ulSta      = HOST_TO_LE32(0);
      uSendPkt.tUploadDataReq.tHead.ulCmd      = HOST_TO_LE32(RCX_FILE_UPLOAD_DATA_REQ);
      uSendPkt.tUploadDataReq.tHead.ulExt      = HOST_TO_LE32(RCX_PACKET_SEQ_NONE);
      uSendPkt.tUploadDataReq.tHead.ulRout     = HOST_TO_LE32(0);

      /* Adjust block size to the size of the system */
      if( LE32_TO_HOST(uRecvPkt.tUploadCnf.tData.ulMaxBlockSize) < ulBlockSize)
         ulBlockSize = LE32_TO_HOST(uRecvPkt.tUploadCnf.tData.ulMaxBlockSize);

      /* Check size we have to send */
      /* If this is only one packet, set extension to NONE */
      uSendPkt.tUploadDataReq.tHead.ulExt = HOST_TO_LE32(RCX_PACKET_SEQ_FIRST);
      if( ulTotalBytes <= ulBlockSize)
        uSendPkt.tUploadDataReq.tHead.ulExt = HOST_TO_LE32(RCX_PACKET_SEQ_NONE);    /* We can send all in one packet */

      /* Perform upload */
      while( (ulFileLength > 0) && (CIFX_NO_ERROR == lRet) )
      {
        /* Send and receive data */
        lRet = pfnTransferPacket(pvChannel,
                                 &uSendPkt.tPacket,
                                 &uRecvPkt.tPacket,
                                 (uint32_t)sizeof(uRecvPkt.tPacket),
                                 CIFX_TO_SEND_PACKET,
                                 pfnRecvPktCallback,
                                 pvUser);
        /* Check for errors */
        if( (CIFX_NO_ERROR != lRet)                                ||
            (RCX_S_OK      != (lRet = LE32_TO_HOST(uRecvPkt.tPacket.tHeader.ulState))) )
        {
          /* This is a packet error from the hardware */
          /* - Inform application */
          /* - Leave upload and send abort */
          if(pfnCallback)
            pfnCallback(ulTransferredBytes, ulTotalBytes, pvUser, CIFX_CALLBACK_FINISHED, lRet);

          fSendAbort = 1;
          break;
        } else
        {
          uint32_t  ulCurrentDataLen = LE32_TO_HOST(uRecvPkt.tUploadDataCnf.tHead.ulLen) - 
                                                    (uint32_t)sizeof(uRecvPkt.tUploadDataCnf.tData);
          uint8_t*  pbRecvData       = (uint8_t*)(&uRecvPkt.tUploadDataCnf.tData + 1);
          uint32_t  ulPacketCrc      = LE32_TO_HOST(uRecvPkt.tUploadDataCnf.tData.ulChksum);

          /* Create own checksum and compare with it */
          ulCRC = CreateCRC32( ulCRC, pbRecvData, ulCurrentDataLen);

          if(ulCRC != ulPacketCrc)
          {
            /* Abort, as a CRC32 error occured */
            lRet = CIFX_FILE_CHECKSUM_ERROR;

            /* Send progress notification */
            if(pfnCallback)
              pfnCallback(ulTransferredBytes, ulTotalBytes, pvUser, CIFX_CALLBACK_FINISHED, lRet);

            fSendAbort = 1;
            break;
          } else
          {
            /* Next packet */
            ++ulCurrentId;
            uSendPkt.tUploadDataReq.tHead.ulId = HOST_TO_LE32(ulCurrentId);

            /* Calculate outstanding size */
            ulFileLength        -= ulCurrentDataLen;
            OS_Memcpy(pbData, pbRecvData, ulCurrentDataLen);
            pbData              += ulCurrentDataLen;
            ulTransferredBytes  += ulCurrentDataLen;
            *pulDataBufferLen   = ulTransferredBytes;

            /* Send progress notification */
            if(pfnCallback)
              pfnCallback(ulTransferredBytes, ulTotalBytes, pvUser,
                          (ulTransferredBytes == ulTotalBytes)? CIFX_CALLBACK_FINISHED : CIFX_CALLBACK_ACTIVE,
                          lRet);

            /* Calculate next packet length and packet extension */
            if(ulFileLength != 0)
            {
              if(ulFileLength <= ulBlockSize)
                uSendPkt.tUploadDataReq.tHead.ulExt = HOST_TO_LE32(RCX_PACKET_SEQ_LAST);
              else
                uSendPkt.tUploadDataReq.tHead.ulExt = HOST_TO_LE32(RCX_PACKET_SEQ_MIDDLE);
            }
          }
        }
      }
    }
  }

  /* If anything failed during upload, send an abort request */
  if( fSendAbort)
  {
    ++ulCurrentId;
    uSendPkt.tAbortReq.tHead.ulDest   = HOST_TO_LE32(RCX_PACKET_DEST_SYSTEM);
    uSendPkt.tAbortReq.tHead.ulSrc    = HOST_TO_LE32(ulSrc);
    uSendPkt.tAbortReq.tHead.ulDestId = HOST_TO_LE32(0);
    uSendPkt.tAbortReq.tHead.ulSrcId  = HOST_TO_LE32(0);
    uSendPkt.tAbortReq.tHead.ulLen    = HOST_TO_LE32(0);
    uSendPkt.tAbortReq.tHead.ulId     = HOST_TO_LE32(ulCurrentId);
    uSendPkt.tAbortReq.tHead.ulSta    = HOST_TO_LE32(0);
    uSendPkt.tAbortReq.tHead.ulCmd    = HOST_TO_LE32(RCX_FILE_UPLOAD_ABORT_REQ);
    uSendPkt.tAbortReq.tHead.ulExt    = HOST_TO_LE32(RCX_PACKET_SEQ_NONE);
    uSendPkt.tAbortReq.tHead.ulRout   = HOST_TO_LE32(0);

    /* Transfer packet */
    lRetAbort = pfnTransferPacket(pvChannel,
                                  &uSendPkt.tPacket,
                                  &uRecvPkt.tPacket,
                                  (uint32_t)sizeof(uRecvPkt.tPacket),
                                  CIFX_TO_SEND_PACKET,
                                  pfnRecvPktCallback,
                                  pvUser);

    if( lRetAbort == CIFX_NO_ERROR)
    {
      /* Return packet state if function succeeded */
      lRetAbort = LE32_TO_HOST((int32_t)uRecvPkt.tPacket.tHeader.ulState);
    }
  }

  /* Always return lRet first, thean abort error */
  if( CIFX_NO_ERROR != lRet)
    return lRet;
  else if( CIFX_NO_ERROR != lRetAbort)
    return lRetAbort;
  else
    return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/
