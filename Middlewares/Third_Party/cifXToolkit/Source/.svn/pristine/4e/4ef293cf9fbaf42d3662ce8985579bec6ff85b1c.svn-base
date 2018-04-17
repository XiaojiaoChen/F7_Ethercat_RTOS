/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: WarmstartFile.h 6598 2014-10-02 08:57:18Z stephans $:

  Description:
    Read/Write access functions for warm start parameter files

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2006-10-13  Changed to be usable in the toolkit
    2006-06-08  initial version

**************************************************************************************/

/*****************************************************************************/
/*!\file WarmstartFile.h
*   Read/Write access functions for warm start parameter files                */
/*****************************************************************************/

#ifndef __WARMSTART_FILE__H
#define __WARMSTART_FILE__H

#include "cifXToolkit.h"

#define CIFX_WS_FIELDBUS_INVALID    0xFFFFFFFFUL  /**< Content of fieldbus header element, when data is not validated */
#define CIFX_WS_FIELDBUS_CAN_OPEN   0UL           /**< Content of fieldbus header element for CANOpen slaves          */
#define CIFX_WS_FIELDBUS_PROFIBUS   1UL           /**< Content of fieldbus header element for Profibus slaves         */
#define CIFX_WS_FIELDBUS_DEVICENET  2UL           /**< Content of fieldbus header element for Devicenet slaves        */
#define CIFX_WS_FIELDBUS_ETHERNETIP 3UL           /**< Content of fieldbus header element for Ethernet/IP slaves      */
#define CIFX_WS_FIELDBUS_ETHERCAT   4UL           /**< Content of fieldbus header element for Ethercat slaves         */
#define CIFX_WS_FIELDBUS_SERCOS3    5UL           /**< Content of fieldbus header element for Sercos III slaves       */
#define CIFX_WS_FIELDBUS_PROFINET   6UL           /**< Content of fieldbus header element for Profinet slaves         */

#define CIFX_WS_WARMSTART_FILE_COOKIE     0x12345678 /* First DWORD of a warmstart file, identifying it as such     */

/*****************************************************************************/
/* File header structure (prepends every warm start file)                    */
/*****************************************************************************/
typedef struct CIFX_WS_FILEHEADERtag
{
  uint32_t ulCookie;       /**< identifier                       */
  uint32_t ulCRC32;        /**< CRC of data portion              */
  uint32_t ulFieldbus;     /**< fieldbus the data is for         */
  uint32_t ulDataLen;      /**< length of the following data     */
  uint8_t  abReserved[16]; /**< reserved values                  */

} CIFX_WS_FILEHEADER, *PCIFX_WS_FILEHEADER;

#endif /* __WARMSTART_FILE__H */
