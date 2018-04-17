/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: OS_Spi.h 6603 2014-10-02 14:57:53Z stephans $:

  Description:
    SPI abstraction

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2014-08-01  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file OS_Spi.h
*   SPI abstraction layer                                                    */
/*****************************************************************************/

#ifndef OS_SPI__H
#define OS_SPI__H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/*! Assert chip select
*   \param pvOSDependent OS Dependent parameter                              */
/*****************************************************************************/
void OS_SpiAssert(void* pvOSDependent);

/*****************************************************************************/
/*! Deassert chip select
*   \param pvOSDependent OS Dependent parameter                              */
/*****************************************************************************/
void OS_SpiDeassert(void* pvOSDependent);

/*****************************************************************************/
/*! Transfer byte stream via SPI. As send and receive buffer are optional,
*   the routine must be capable of sending dummy bytes (in case pbSend == NULL)
*   and discard receive bytes (if pbRecv == NULL). If caller does not pass
*   any buffer at all, we are dealing with an idle transfer to waste some time.
*   \param pvOSDependent OS Dependent parameter
*   \param pbSend        Send buffer (Can be NULL for polling data from slave)
*   \param pbRecv        Receive buffer (Can be NULL if slaves received data
                         is discarded by caller)
*   \param ulLen         Length of SPI transfer                              */
/*****************************************************************************/
void OS_SpiTransfer(void* pvOSDependent, uint8_t* pbSend, uint8_t* pbRecv, uint32_t ulLen);

#ifdef __cplusplus
}
#endif

#endif /* OS_SPI__H */
