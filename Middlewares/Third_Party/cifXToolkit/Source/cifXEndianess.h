/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: cifXEndianess.h 6598 2014-10-02 08:57:18Z stephans $:

  Description:
    Little/Big Endian conversion

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2010-01-25  added additional braces to the macros
    2009-01-20  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file cifXEndianess.h
*   Little/Big Endian conversion                                             */
/*****************************************************************************/

#ifndef __CIFX_ENDIANESS__H
#define __CIFX_ENDIANESS__H

/* Give the user the possibility to use own macros for
   endianess conversion */
#ifndef BIGENDIAN_MACROS_PROVIDED
  #ifndef CIFX_TOOLKIT_BIGENDIAN
    /* Little endian, so we don't need a conversion */
    #define LE16_TO_HOST(a)   (a)
    #define LE32_TO_HOST(a)   (a)
    #define LE64_TO_HOST(a)   (a)
    #define HOST_TO_LE16(a)   (a)
    #define HOST_TO_LE32(a)   (a)
    #define HOST_TO_LE64(a)   (a)
  #else
    /* BIG endian, so we DO need a conversion */
    #define LE16_TO_HOST(a)   ( (((a) & 0x00FF) << 8) | \
                                (((a) & 0xFF00) >> 8) )

    #define LE32_TO_HOST(a)   ( (((a) & 0x000000FFUL) << 24) | \
                                (((a) & 0x0000FF00UL) << 8)  | \
                                (((a) & 0x00FF0000UL) >> 8)  | \
                                (((a) & 0xFF000000UL) >> 24) )

    #define LE64_TO_HOST(a)   ( (((a) & 0x00000000000000FFULL) << 56) | \
                                (((a) & 0x000000000000FF00ULL) << 40) | \
                                (((a) & 0x0000000000FF0000ULL) << 24) | \
                                (((a) & 0x00000000FF000000ULL) << 8)  | \
                                (((a) & 0x000000FF00000000ULL) >> 8)  | \
                                (((a) & 0x0000FF0000000000ULL) >> 24) | \
                                (((a) & 0x00FF000000000000ULL) >> 40) | \
                                (((a) & 0xFF00000000000000ULL) >> 56) )

    #define HOST_TO_LE16(a)   LE16_TO_HOST(a)
    #define HOST_TO_LE32(a)   LE32_TO_HOST(a)
    #define HOST_TO_LE64(a)   LE64_TO_HOST(a)
  #endif
#endif

typedef enum
{
  eCIFX_ENDIANESS_WIDTH_8BIT,
  eCIFX_ENDIANESS_WIDTH_16BIT,
  eCIFX_ENDIANESS_WIDTH_32BIT,
  eCIFX_ENDIANESS_WIDTH_64BIT

} CIFX_ENDIANESS_WIDTH;

/*****************************************************************************/
/*! Structure definition for endianess conversion function. An array of this
*   this structure is used for automatically transforming a structure (which
*   is described by this structure) from/to host endianess                   */
/*****************************************************************************/
typedef struct CIFX_ENDIANESS_ENTRY_Ttag
{
  int                  iOffset;      /*!< Offset inside the buffer      */
  CIFX_ENDIANESS_WIDTH eWidth;       /*!< Data width of structure       */
  int                  iElementCnt;  /*!< Number of elements to convert */

} CIFX_ENDIANESS_ENTRY_T, *PCIFX_ENDIANESS_ENTRY_T;

void cifXConvertEndianess(void* pvBuffer, int iBufferLen,
                          const CIFX_ENDIANESS_ENTRY_T* atConv, int iConvLen);

#endif /* __CIFX_ENDIANESS__H */
