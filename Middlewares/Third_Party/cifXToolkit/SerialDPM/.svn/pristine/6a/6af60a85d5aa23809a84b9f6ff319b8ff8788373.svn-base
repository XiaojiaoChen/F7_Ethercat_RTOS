/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: SerialDPMInterface.c 6603 2014-10-02 14:57:53Z stephans $:

  Description:
    Serial DPM Interface

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2014-08-01  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file SerialDPMInterface.c
*   Serial DPM protocol implementation                                       */
/*****************************************************************************/

#include "OS_Spi.h"
#include "SerialDPMInterface.h"

#define MAX_CNT(array)       (sizeof((array))/sizeof((array)[0]))
#define MIN(a,b)             (((a)<(b))?(a):(b))

#define MAX_TRANSFER_LEN     124
#define CMD_READ_NX50(len)   (0x80 | len)
#define CMD_READ_NX10(len)   ((len > 127)? 0x80:(0x80 | len))
#define CMD_WRITE_NX10(len)  ((len > 127)? 0x00:len)
#define CMD_READ_NX51(addr)  (0x80 | ((addr>>16)&0xF))
#define CMD_WRITE_NX51(addr) ((addr>>16)&0xF)
#define CMD_LEN_NX51(len)    ((len > 255)? 0x00:len)

#ifndef CIFX_TOOLKIT_HWIF
  #error "CIFX_TOOLKIT_HWIF must be explicitly enabled to support serial DPM!"
#endif

/*****************************************************************************/
/*! Read a number of bytes from SPI interface (netX50 Slave)
*   \param ulDpmAddr Address offset in DPM to read data from
*   \param pabData   Buffer to store read data
*   \param ulLen     Number of bytes to read                                 */
/*****************************************************************************/
static void* Read_NX50( void* pvOSDependent, void* pvAddr, void* pvData, uint32_t ulLen)
{
  uint8_t   bUnused       = 0x00;
  uint32_t  ulByteTimeout = 100;
  uint32_t  ulDpmAddr     = (uint32_t)pvAddr;
  uint8_t*  pabData       = (uint8_t*)pvData;

  while (ulLen > 0)
  {
    uint8_t  abSend[3];
    uint32_t ulChunkLen = MIN(MAX_TRANSFER_LEN, ulLen);

    ulLen -= ulChunkLen;

    /* Assemble command */
    abSend[0] = (uint8_t)((ulDpmAddr >> 8) & 0xFF);
    abSend[1] = (uint8_t)((ulDpmAddr >> 0) & 0xFF);
    abSend[2] = (uint8_t)(CMD_READ_NX50(ulChunkLen));

    OS_SpiAssert(pvOSDependent);
    OS_SpiTransfer(pvOSDependent, abSend, NULL, MAX_CNT(abSend));

    do
    {
      if(ulByteTimeout == 0)
      {
          OS_SpiDeassert(pvOSDependent);
          return pvData;
      }
      --ulByteTimeout;

      /* get the idle bytes done */
      OS_SpiTransfer(pvOSDependent, NULL, &bUnused, 1);

    } while((bUnused & 0xFF) != 0xA5);

    while(ulChunkLen--)
    {
      OS_SpiTransfer(pvOSDependent, &bUnused, pabData++, 1);
    }

    OS_SpiDeassert(pvOSDependent);

    ulDpmAddr += MAX_TRANSFER_LEN;
  }
  return pvData;
}

/*****************************************************************************/
/*! Read a number of bytes from SPI interface (netX50 Slave)
*   \param ulDpmAddr Address offset in DPM to read data from
*   \param pabData   Buffer to store read data
*   \param ulLen     Number of bytes to read                                 */
/*****************************************************************************/
static void* Write_NX50( void* pvOSDependent, void* pvAddr, void* pvData, uint32_t ulLen)
{
  uint32_t ulDpmAddr     = (uint32_t)pvAddr;
  uint8_t* pabData       = (uint8_t*)pvData;

  while (ulLen > 0)
  {
    uint8_t  abSend[3];
    uint32_t ulChunkLen = MIN(MAX_TRANSFER_LEN, ulLen);

    ulLen -= ulChunkLen;

    /* Assemble command */
    abSend[0] = (uint8_t)((ulDpmAddr >> 8) & 0xFF);
    abSend[1] = (uint8_t)((ulDpmAddr >> 0) & 0xFF);
    abSend[2] = (uint8_t)ulChunkLen;

    OS_SpiAssert(pvOSDependent);
    OS_SpiTransfer(pvOSDependent, abSend, NULL, MAX_CNT(abSend));
    OS_SpiTransfer(pvOSDependent, pabData, NULL, ulChunkLen);
    OS_SpiDeassert(pvOSDependent);

    ulDpmAddr += MAX_TRANSFER_LEN;
    pabData   += MAX_TRANSFER_LEN;
  }
  return pvAddr;
}

/*****************************************************************************/
/*! Read a number of bytes from SPI interface (netX500 Slave)
*   \param ulDpmAddr Address offset in DPM to read data from
*   \param pabData   Buffer to store read data
*   \param ulLen     Number of bytes to read                                 */
/*****************************************************************************/
static void* Read_NX500( void* pvOSDependent, void* pvAddr, void* pvData, uint32_t ulLen)
{
  uint8_t  bUnused       = 0x00;
  uint32_t ulByteTimeout = 100;
  uint32_t ulDpmAddr     = (uint32_t)pvAddr;
  uint8_t* pabData       = (uint8_t*)pvData;
  uint32_t ulPreLen      = ulDpmAddr&0x3;

  /* Align offset and length */
  ulDpmAddr &= ~0x3;

  while (ulLen > 0)
  {
    uint8_t  abSend[3];
    uint32_t ulChunkLen   = MIN(MAX_TRANSFER_LEN, ulLen);
    uint32_t ulAlignedLen = (ulChunkLen+3)&~0x3;

    ulLen -= ulChunkLen;

    /* Assemble command */
    abSend[0] = (uint8_t)((ulDpmAddr >> 8) & 0xFF);
    abSend[1] = (uint8_t)((ulDpmAddr >> 0) & 0xFF);
    abSend[2] = (uint8_t)(CMD_READ_NX50(ulAlignedLen));

    /* assert chip select */
    OS_SpiAssert(pvOSDependent);
    OS_SpiTransfer(pvOSDependent, abSend, NULL, MAX_CNT(abSend));

    do
    {
      if(ulByteTimeout == 0)
      {
          OS_SpiDeassert(pvOSDependent);
          return pvData;
      }
      --ulByteTimeout;

      /* get the idle bytes done */
      OS_SpiTransfer(pvOSDependent, NULL, &bUnused, 1);

    } while((bUnused & 0xFF) != 0xA5);

    if (ulPreLen)
    {
      OS_SpiTransfer(pvOSDependent, NULL, NULL, ulPreLen);
      ulPreLen = 0;
    }

    OS_SpiTransfer(pvOSDependent, NULL, pabData, ulChunkLen);

    if (0 != (ulAlignedLen - ulChunkLen))
    {
      OS_SpiTransfer(pvOSDependent, NULL, NULL, ulAlignedLen - ulChunkLen);
    }

    OS_SpiDeassert(pvOSDependent);

    ulDpmAddr += MAX_TRANSFER_LEN;
    pabData   += MAX_TRANSFER_LEN;
  }
  return pvData;
}

/*****************************************************************************/
/*! Read and modify number of bytes from SPI interface (netX500 Slave)
*   \param ulDpmAddr Address offset in DPM to read data from
*   \param pabData   Buffer to store read data
*   \param ulLen     Number of bytes to read                                 */
/*****************************************************************************/
static void* ReadModifyWrite_NX500( void* pvOSDependent, void* pvAddr, void* pvData, uint32_t ulLen)
{
  uint32_t ulDpmAddr = (uint32_t)pvAddr;
  uint8_t* pabData   = (uint8_t*)pvData;
  uint8_t  abRead[4];

  if (ulDpmAddr&0x3)
  {
    uint32_t ulAlignedAddr = ulDpmAddr&~0x3;
    uint8_t* pabRead       = &abRead[ulDpmAddr&0x3];
    uint32_t ulPartLen     = MIN(ulLen, (4 - (ulDpmAddr&0x3)));

    ulLen     -= ulPartLen;
    ulDpmAddr += ulPartLen;

    Read_NX50( pvOSDependent, (void*)ulAlignedAddr, abRead, 4);
    while (ulPartLen--)
    {
      *pabRead++ = *pabData++;
    }
    Write_NX50( pvOSDependent, (void*)ulAlignedAddr, abRead, 4);
  }

  if (ulLen&~0x3)
  {
    uint32_t ulAlignedLen = ulLen&~0x3;
    Write_NX50( pvOSDependent, (void*)ulDpmAddr, pabData, ulAlignedLen);
    pabData   += ulAlignedLen;
    ulDpmAddr += ulAlignedLen;
    ulLen     -= ulAlignedLen;
  }

  if (ulLen&0x3)
  {
    uint8_t* pabRead = &abRead[0];

    Read_NX50( pvOSDependent, (void*)ulDpmAddr, abRead, 4);
    while (ulLen--)
    {
      *pabRead++ = *pabData++;
    }
    Write_NX50( pvOSDependent, (void*)ulDpmAddr, abRead, 4);
  }
  return pvAddr;
}

/*****************************************************************************/
/*! Read a number of bytes from SPI interface (netX10 Slave)
*   \param ulDpmAddr Address offset in DPM to read data from
*   \param pabData   Buffer to store read data
*   \param ulLen     Number of bytes to read                                 */
/*****************************************************************************/
static void* Read_NX10( void* pvOSDependent, void* pvAddr, void* pvData, uint32_t ulLen)
{
  uint8_t abSend[3];

  /* Assemble command */
  abSend[0] = (uint8_t)(((uint32_t)pvAddr >> 8) & 0xFF);
  abSend[1] = (uint8_t)(((uint32_t)pvAddr >> 0) & 0xFF);
  abSend[2] = (uint8_t)(CMD_READ_NX10(ulLen));

  OS_SpiAssert(pvOSDependent);
  OS_SpiTransfer(pvOSDependent, abSend, NULL, MAX_CNT(abSend));
  OS_SpiTransfer(pvOSDependent, NULL, (uint8_t*)pvData, ulLen);
  OS_SpiDeassert(pvOSDependent);
  return pvData;
}

/*****************************************************************************/
/*! Read a number of bytes from SPI interface (netX10 Slave)
*   \param ulDpmAddr Address offset in DPM to read data from
*   \param pabData   Buffer to store read data
*   \param ulLen     Number of bytes to read                                 */
/*****************************************************************************/
static void* Write_NX10( void* pvOSDependent, void* pvAddr, void* pvData, uint32_t ulLen)
{
  uint8_t abSend[3];

  /* Assemble command */
  abSend[0] = (uint8_t)(((uint32_t)pvAddr >> 8) & 0xFF);
  abSend[1] = (uint8_t)(((uint32_t)pvAddr >> 0) & 0xFF);
  abSend[2] = (uint8_t)(CMD_WRITE_NX10(ulLen));

  OS_SpiAssert(pvOSDependent);
  OS_SpiTransfer(pvOSDependent, abSend, NULL, MAX_CNT(abSend));
  OS_SpiTransfer(pvOSDependent, (uint8_t*)pvData, NULL, ulLen);
  OS_SpiDeassert(pvOSDependent);
  return pvAddr;
}

/*****************************************************************************/
/*! Read a number of bytes from SPI interface (netX51 Slave)
*   \param ulDpmAddr Address offset in DPM to read data from
*   \param pabData   Buffer to store read data
*   \param ulLen     Number of bytes to read                                 */
/*****************************************************************************/
static void* Read_NX51( void* pvOSDependent, void* pvAddr, void* pvData, uint32_t ulLen)
{
  uint8_t abSend[4];

  /* Assemble command */
  abSend[0] = (uint8_t)(CMD_READ_NX51((uint32_t)pvAddr));
  abSend[1] = (uint8_t)(((uint32_t)pvAddr >> 8) & 0xFF);
  abSend[2] = (uint8_t)(((uint32_t)pvAddr >> 0) & 0xFF);
  abSend[3] = (uint8_t)(CMD_LEN_NX51(ulLen));

  OS_SpiAssert(pvOSDependent);
  OS_SpiTransfer(pvOSDependent, abSend, NULL, MAX_CNT(abSend));
  OS_SpiTransfer(pvOSDependent, NULL, (uint8_t*)pvData, ulLen);
  OS_SpiDeassert(pvOSDependent);
  return pvData;
}

/*****************************************************************************/
/*! Read a number of bytes from SPI interface (netX51 Slave)
*   \param ulDpmAddr Address offset in DPM to read data from
*   \param pabData   Buffer to store read data
*   \param ulLen     Number of bytes to read                                 */
/*****************************************************************************/
static void* Write_NX51( void* pvOSDependent, void* pvAddr, void* pvData, uint32_t ulLen)
{
  uint8_t abSend[3];

  /* Assemble command */
  abSend[0] = (uint8_t)(CMD_WRITE_NX51((uint32_t)pvAddr));
  abSend[1] = (uint8_t)(((uint32_t)pvAddr >> 8) & 0xFF);
  abSend[2] = (uint8_t)(((uint32_t)pvAddr >> 0) & 0xFF);

  OS_SpiAssert(pvOSDependent);
  OS_SpiTransfer(pvOSDependent, abSend, NULL, MAX_CNT(abSend));
  OS_SpiTransfer(pvOSDependent, (uint8_t*)pvData, NULL, ulLen);
  OS_SpiDeassert(pvOSDependent);
  return pvAddr;
}

/*****************************************************************************/
/*! Initialize serial DPM interface
*   \param szSpiName  Name of assigned SPI interface
*   \param uInstance  Instance of assigned SPI interface
*   \return protocol type identifier                                         */
/*****************************************************************************/
int SerialDPM_Init(DEVICEINSTANCE* ptDevice)
{
  uint8_t bUnused;
  int     iSerDpmType = -1;
  int     iPrevious   = -1;

  do
  {
    uint32_t ulDetect  = 0;
    uint8_t  abSend[]  = {CMD_READ_NX51(0xFF), 0xFF, CMD_READ_NX50(4)};

    iPrevious          = iSerDpmType;

    OS_SpiAssert(ptDevice->pvOSDependent);
    OS_SpiTransfer(ptDevice->pvOSDependent, abSend, (unsigned char*)&ulDetect, MAX_CNT(abSend));

    if (0 == ulDetect)
    {
      iSerDpmType = SERDPM_NETX10;
    } else if (0x00FFFFFF == ulDetect)
    {
      iSerDpmType = SERDPM_NETX50;
    } else if (0x64 == (0xFF&ulDetect))
    {
      iSerDpmType = SERDPM_NETX100;
    } else if (0x11 == (0x1F&ulDetect))
    {
      iSerDpmType = SERDPM_NETX51;
    } else
    {
      iSerDpmType = SERDPM_UNKNOWN;
    }

    OS_SpiDeassert(ptDevice->pvOSDependent);
  } while (iPrevious != iSerDpmType);

  switch (iSerDpmType)
  {
    case SERDPM_NETX100:
      ptDevice->pfnHwIfRead  = Read_NX500;
      ptDevice->pfnHwIfWrite = ReadModifyWrite_NX500;
      break;

    case SERDPM_NETX50:
      ptDevice->pfnHwIfRead  = Read_NX50;
      ptDevice->pfnHwIfWrite = Write_NX50;
      break;
    case SERDPM_NETX10:
      ptDevice->pfnHwIfRead  = Read_NX10;
      ptDevice->pfnHwIfWrite = Write_NX10;
      /* Initialize SPI unit of slave by making 2 dummy reads */
      Read_NX10(ptDevice->pvOSDependent, 0, &bUnused, 1);
      Read_NX10(ptDevice->pvOSDependent, 0, &bUnused, 1);
      break;
    case SERDPM_NETX51:
      ptDevice->pfnHwIfRead  = Read_NX51;
      ptDevice->pfnHwIfWrite = Write_NX51;
      /* Initialize SPI unit of slave by making 2 dummy reads */
      Read_NX51(ptDevice->pvOSDependent, 0, &bUnused, 1);
      Read_NX51(ptDevice->pvOSDependent, 0, &bUnused, 1);
      break;
    default:
      /* Protocol type detection failed */
      break;
  }

  /* This is a SPI connection, not PCI! */
  ptDevice->fPCICard       = 0;
  /* The DPM address must be zero, as we only transfer address offsets via the SPI interface. */
  ptDevice->pbDPM          = NULL;

  return iSerDpmType;
}
