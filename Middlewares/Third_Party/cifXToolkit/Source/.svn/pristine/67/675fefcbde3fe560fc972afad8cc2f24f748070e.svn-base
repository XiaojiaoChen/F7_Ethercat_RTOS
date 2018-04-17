/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: NetX_ROMLoader.h 6598 2014-10-02 08:57:18Z stephans $:

  Description:
    netX romloader bootblock definitions

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2006-12-06  obsoleted #pragma once removed
    2006-03-06  created

**************************************************************************************/

/*****************************************************************************/
/*! \file
*     netX romloader bootblock definitions                                   */
/*****************************************************************************/

/*****************************************************************************/
/*! \addtogroup CIFX_TK_DPMSTRUCTURE DPM Structure Definition
*   \{                                                                       */
/*****************************************************************************/

#ifndef __NETX_ROMLOADER_H
#define __NETX_ROMLOADER_H

#define MSK_SYSSTA_LED_READY     0x00000001UL /*!< Bitmask for the system state READY LED */
#define MSK_SYSSTA_LED_RUN       0x00000002UL /*!< Bitmask for the system state RUN LED */

#define MSK_SYSSTA_BOOT_ACTIVE   0x00000008UL /*!< Bitmask for bootloader is active */
#define MSK_SYSSTA_BOOT_START    0x00000080UL /*!< Bitmask to toggle/xor when requesting bootloader to start image */

#define BOOTBLOCK_COOKIE_PCI     0xF8BEAF00UL /*!< Bootblock cookie used for PCI mode     */
#define BOOTBLOCK_COOKIE_8BIT    0xF8BEAF08UL /*!< Bootblock cookie used for 8Bit Memory  */
#define BOOTBLOCK_COOKIE_16BIT   0xF8BEAF16UL /*!< Bootblock cookie used for 16Bit Memory */
#define BOOTBLOCK_COOKIE_32BIT   0xF8BEAF32UL /*!< Bootblock cookie used for 32Bit Memory */

#define BOOTBLOCK_FILE_SIGNATURE 0x5854454EUL /*!< Bootblock signature ('NETX')           */

#pragma pack(4)

/*****************************************************************************/
/*! Bootblock expected by netX Romloader                                     */
/*****************************************************************************/
typedef struct NETX_BOOTBLOCK_Ttag
{
  uint32_t ulCookie;           /*!< Cookie identifying bus width and valid bootblock               */

  union
  {
    uint32_t ulMemCtrl;        /*!< Parallel/Serial Flash Mode for setting up timing parameters    */
    uint32_t ulSpeed;          /*!< I2C/SPI Mode for identifying speed of device                   */
    uint32_t ulReserved;       /*!< PCI/DPM mode                                                   */
  } unCtrl;

  uint32_t ulApplEntrypoint;   /*!< Entrypoint to application after relocation                     */
  uint32_t ulApplChecksum;     /*!< Checksum of application                                        */
  uint32_t ulApplSize;         /*!< size of application in DWORDs                                  */
  uint32_t ulApplStartAddr;    /*!< Relocation address of application                              */
  uint32_t ulSignature;        /*!< Bootblock signature ('NETX')                                   */

  union {
    uint32_t ulSdramGeneralCtrl;      /*!< SDRam General control value                             */
    uint32_t ulExpBusReg;             /*!< Expension bus register value (EXPBus Bootmode)          */
  } unCtrl0;

  union {
    uint32_t ulSdramTimingCtrl;       /*!< SDRam Timing control register value                     */
    uint32_t ulIoRegMode0;            /*!< IORegmode0 register value (EXPBus Bootmode)             */
  } unCtrl1;

  union {
    uint32_t ulIoRegMode1;            /*!< IORegmode1 register value (EXPBus Bootmode)             */
    uint32_t ulRes0;                  /*!< unused/reserved                                         */
  } unCtrl2;

  union {
    uint32_t ulIfConf1;               /*!< IfConfig1 register value (EXPBus Bootmode)              */
    uint32_t ulRes0;                  /*!< unused/reserved                                         */
  } unCtrl3;

  union {
    uint32_t ulIfConf2;               /*!< IfConfig2 register value (EXPBus Bootmode)              */
    uint32_t ulRes0;                  /*!< unused/reserved                                         */
  } unCtrl4;

  uint32_t ulMiscAsicCtrl;            /*!< ASIC CTRL register value                                */
  uint32_t ulRes[2];                  /*!< unused/reserved                                         */
  uint32_t ulBootChecksum;            /*!< Bootblock checksum                                      */
} NETX_BOOTBLOCK_T, *PNETX_BOOTBLOCK_T;

#pragma pack()

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/

#endif
