/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: HilFileHeaderV3.h 6827 2015-03-31 15:23:50Z Robert $:

  Description:
    Hilscher File Header V3.0

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2015-03-31  Added support of IAR (ARM core only)
                Added __HIL_PACKED_PRE/__HIL_PACKED_POST for structures in structures
    2010-03-23  File created.

**************************************************************************************/


#ifndef __HilFileHeaderV3_h
#define __HilFileHeaderV3_h

#include <stdint.h>

/*****************************************************************************/
/* Set byte alignment for structure members. */

/* support for MS Visual C++ compiler */
#ifdef _MSC_VER
  #if _MSC_VER >= 1000
    #define __HIL_PACKED_PRE
    #define __HIL_PACKED_POST
    #pragma once
    #pragma pack(1)
    #ifndef STRICT
      #define STRICT
    #endif
  #endif /* _MSC_VER >= 1000 */
#endif /* _MSC_VER */

/* support for GNU compiler */
#ifdef __GNUC__
  #define __HIL_PACKED_PRE
  #define __HIL_PACKED_POST    __attribute__((__packed__))
#endif

/* support for REALVIEW ARM and IAR compiler (ARM cores only) */
#if defined (__ADS__) || defined (__REALVIEW__) || defined (__CC_ARM) || defined (__ICCARM__)
  #define __HIL_PACKED_PRE   __packed
  #define __HIL_PACKED_POST
#endif
/*****************************************************************************/



/*****************************************************************************/
/* Constant Definitions for Hilscher File Headers                            */
/*****************************************************************************/

/* file header cookies (low order byte is first byte in memory) */
#define HIL_FILE_HEADER_FIRMWARE_COOKIE     0xF8BEAF00 /**< used in NXF or custom loadables */
#define HIL_FILE_HEADER_FIRMWARE_8_COOKIE   0xF8BEAF08 /**< used in NXF or custom loadables */
#define HIL_FILE_HEADER_FIRMWARE_16_COOKIE  0xF8BEAF16 /**< used in NXF or custom loadables */
#define HIL_FILE_HEADER_FIRMWARE_32_COOKIE  0xF8BEAF32 /**< used in NXF or custom loadables */

#define HIL_FILE_HEADER_MODULE_COOKIE       0x4D584E2E /**< ".NXM" */
#define HIL_FILE_HEADER_OPTION_COOKIE       0x4F584E2E /**< ".NXO" */
#define HIL_FILE_HEADER_DATABASE_COOKIE     0x44584E2E /**< ".NXD" */
#define HIL_FILE_HEADER_LICENSE_COOKIE      0x4C584E2E /**< ".NXL" */
#define HIL_FILE_HEADER_BINARY_COOKIE       0x42584E2E /**< ".NXB" */

/* valid Hilscher file extensions */
#define HIL_FILE_EXTENSION_FIRMWARE         ".NXF"
#define HIL_FILE_EXTENSION_MODULE           ".NXM"
#define HIL_FILE_EXTENSION_OPTION           ".NXO"
#define HIL_FILE_EXTENSION_LICENSE          ".NXL"
#define HIL_FILE_EXTENSION_DATABASE         ".NXD"
#define HIL_FILE_EXTENSION_BINARY           ".NXB"

/* Common Header version constants */
#define HIL_VERSION_COMMON_HEADER_0_0       0x00000000 /**< V0.0, default initialization value */
#define HIL_VERSION_COMMON_HEADER_1_0       0x00010000 /**< V1.0, initial version */
#define HIL_VERSION_COMMON_HEADER_2_0       0x00020000 /**< V2.0, usManufacturer included in Common Header */
#define HIL_VERSION_COMMON_HEADER_3_0       0x00030000 /**< V3.0, usManufacturer moved to Device Info, additional sizes and offsets */

/* Device Info structure version constants */
#define HIL_VERSION_DEVICE_INFO_V1_0        0x00010000 /**< V1.0, initial version used with Common Header V3.0 */

/* Module Info structure version constants */
#define HIL_VERSION_MODULE_INFO_V1_0        0x00010000 /**< V1.0, initial version used with Common Header V3.0 */

/* source device type constants used in Default Header */
#define HIL_SRC_DEVICE_TYPE_PAR_FLASH_SRAM  1          /**< parallel flash on SRAM bus      */
#define HIL_SRC_DEVICE_TYPE_SER_FLASH       2          /**< serial flash on SPI bus         */
#define HIL_SRC_DEVICE_TYPE_EEPROM          3          /**< serial EEPROM on I2C bus        */
#define HIL_SRC_DEVICE_TYPE_SD_MMC          4          /**< boot image on MMC/SD card       */
#define HIL_SRC_DEVICE_TYPE_DPM             5          /**< DPM boot mode                   */
#define HIL_SRC_DEVICE_TYPE_DPM_EXT         6          /**< extended DPM boot mode          */
#define HIL_SRC_DEVICE_TYPE_PAR_FLASH_EXT   7          /**< parallel flash on extension bus */

/* chip type constants */
#define HIL_LICENSE_CHIPTYPE_NETX500        0x01       /**< ARM code  for netX500 */
#define HIL_LICENSE_CHIPTYPE_NETX100        0x02       /**< ARM code  for netX100 */
#define HIL_LICENSE_CHIPTYPE_NETX50         0x03       /**< ARM code  for netX50  */
#define HIL_LICENSE_CHIPTYPE_NETX51         0x04       /**< ARM code  for netX51  */
#define HIL_LICENSE_CHIPTYPE_NETX52         0x05       /**< ARM code  for netX52  */
#define HIL_LICENSE_CHIPTYPE_XPEC500        0x40       /**< XPEC code for netX500 */
#define HIL_LICENSE_CHIPTYPE_XPEC100        0x41       /**< XPEC code for netX100 */
#define HIL_LICENSE_CHIPTYPE_XPEC50         0x42       /**< XPEC code for netX50  */
#define HIL_LICENSE_CHIPTYPE_XPEC51         0x43       /**< XPEC code for netX51  */
#define HIL_LICENSE_CHIPTYPE_XPEC52         0x44       /**< XPEC code for netX52  */


/*****************************************************************************/
/* File Header Substructures for Hilscher Downloadable Files                 */
/*****************************************************************************/

/* BOOT header (64 bytes, used for NXF) */
typedef __HIL_PACKED_PRE struct HIL_FILE_BOOT_HEADER_V1_0tag
{
  /* boot block identification and bus width (8/16/32 bits) in case of a parallel flash source device  */
  uint32_t     ulMagicCookie;              /**< see HIL_FILE_HEADER_FIRMWARE_xxx_COOKIE           */
  /* boot image source device configuration value (either parallel or serial flash) */
  __HIL_PACKED_PRE union
  { uint32_t   ulSramBusTiming;            /**< parallel flash on SRAM bus: bus timing value      */
    uint32_t   ulSpiClockSpeed;            /**< serial flash on SPI:        clock speed value     */
  } __HIL_PACKED_POST unSrcMemCtrl;
  /* application data description values                                                               */
  uint32_t     ulAppEntryPoint;            /**< app. entry point, netX code execution starts here */
  uint32_t     ulAppChecksum;              /**< app. checksum starting from byte offset 64        */
  uint32_t     ulAppFileSize;              /**< app. size in DWORDs starting from byte offset 64  */
  uint32_t     ulAppStartAddress;          /**< app. relocation start address for binary image    */
  uint32_t     ulSignature;                /**< app. signature, always 0x5854454E = "NETX"        */
  /* destination device control values */
  __HIL_PACKED_PRE union
  { /* SDRAM */
    __HIL_PACKED_PRE struct
    { uint32_t ulSdramGeneralCtrl;         /**< value for SDRAM General Control register          */
      uint32_t ulSdramTimingCtrl;          /**< value for SDRAM Timing register                   */
      uint32_t aulReserved[3];
    } __HIL_PACKED_POST tSDRAMCtrl;
    /* Extension Bus */
    __HIL_PACKED_PRE struct
    { uint32_t ulExtConfigCS0;             /**< value for EXT_CONFIG_CS0 register                 */
      uint32_t ulIoRegMode0;               /**< value for DPMAS_IO_MODE0 register                 */
      uint32_t ulIoRegMode1;               /**< value for DPMAS_IO_MODE1 register                 */
      uint32_t ulIfConf0;                  /**< value for DPMAS_IF_CONF0 register                 */
      uint32_t ulIfConf1;                  /**< value for DPMAS_IF_CONF1 register                 */
    } __HIL_PACKED_POST tExtBusCtrl;
    /* SRAM */
    __HIL_PACKED_PRE struct
    { uint32_t ulExtConfigSRAMn;           /**< value for EXT_SRAMn_CTRL register                 */
      uint32_t aulReserved[4];
    } __HIL_PACKED_POST tSRAMCtrl;
  } __HIL_PACKED_POST unDstMemCtrl;
  uint32_t     ulMiscAsicCtrl;             /**< internal ASIC control register value (set to 1)   */
  uint32_t     ulSerialNumber;             /**< serial no. or user param. (ignored by ROM loader) */
  uint32_t     ulSrcDeviceType;            /**< HIL_SRC_DEVICE_TYPE_xxx                           */
  uint32_t     ulBootHeaderChecksum;       /**< sums up all 16 DWORDs and multiplies result by -1 */
} __HIL_PACKED_POST HIL_FILE_BOOT_HEADER_V1_0, *PHIL_FILE_BOOT_HEADER_V1_0;


/* DEFAULT header (64 bytes, used for NXM, NXO, NXD, NXL, NXB) */
typedef __HIL_PACKED_PRE struct HIL_FILE_DEFAULT_HEADER_V1_0tag
{
  uint32_t   ulMagicCookie;                /**< see HIL_FILE_HEADER_xxx_COOKIE definitions        */
  uint32_t   aulReserved[15];              /**< reserved, set to zero                             */
} __HIL_PACKED_POST HIL_FILE_DEFAULT_HEADER_V1_0, *PHIL_FILE_DEFAULT_HEADER_V1_0;


/* COMMON header (64 bytes) */
typedef __HIL_PACKED_PRE struct HIL_FILE_COMMON_HEADER_V3_0tag
{
  uint32_t   ulHeaderVersion;              /**< structure version (major, minor), 0x00030000      */
  uint32_t   ulHeaderLength;               /**< Default+Common Header+Device Info+Module Info(s)  */
  uint32_t   ulDataSize;                   /**< from ulDataStartOffset to ulTagListStartOffset    */
  uint32_t   ulDataStartOffset;            /**< offset of binary data (from beginning of file)    */
  uint8_t    bNumModuleInfos;              /**< number of Module Info structures in file header   */
  uint8_t    bReserved;                    /**< reserved, set to zero                             */
  uint16_t   usReserved;                   /**< reserved, set to zero                             */
  uint32_t   aulMD5[4];                    /**< MD5 checksum for the whole firmware file          */
  uint32_t   ulTagListSize;                /**< tag list length in bytes (0 = no tag list)        */
  uint32_t   ulTagListOffset;              /**< offset of tag list (from beginning of file)       */
  uint32_t   ulTagListSizeMax;             /**< maximum tag list length in bytes (reserved space) */
  uint32_t   aulReserved[3];               /**< reserved, set to zero                             */
  uint32_t   ulHeaderCRC32;                /**< Default+Common Header+Device Info+Module Info(s)  */
} __HIL_PACKED_POST HIL_FILE_COMMON_HEADER_V3_0, *PHIL_FILE_COMMON_HEADER_V3_0;


/* DEVICE-specific information (64 bytes) */
typedef __HIL_PACKED_PRE struct HIL_FILE_DEVICE_INFO_V1_0tag
{
  uint32_t  ulStructVersion;              /**< structure version (major, minor), 0x00010000      */
  uint16_t  usManufacturer;               /**< manufacturer ID (see DPM Manual)                  */
  uint16_t  usDeviceClass;                /**< netX device class                                 */
  uint8_t   bHwCompatibility;             /**< hardware compatibility ID                         */
  uint8_t   bChipType;                    /**< see HIL_LICENSE_CHIPTYPE_xxx definitions          */
  uint16_t  usReserved;                   /**< reserved, set to zero                             */
  uint16_t  ausHwOptions[4];              /**< required hardware assembly options (0=not used)   */
  uint32_t  ulLicenseFlags1;              /**< netX license flags 1                              */
  uint32_t  ulLicenseFlags2;              /**< netX license flags 2                              */
  uint16_t  usNetXLicenseID;              /**< netX license id                                   */
  uint16_t  usNetXLicenseFlags;           /**< netX license flags                                */
  uint16_t  ausFwVersion[4];              /**< FW version (major, minor, build, revision)        */
  uint32_t  ulFwNumber;                   /**< FW product code (order number) or project code    */
  uint32_t  ulDeviceNumber;               /**< target device product code (order number)         */
  uint32_t  ulSerialNumber;               /**< target device serial number                       */
  uint32_t  aulReserved[3];               /**< reserved, set to zero                             */
} __HIL_PACKED_POST HIL_FILE_DEVICE_INFO_V1_0, *PHIL_FILE_DEVICE_INFO_V1_0;


/* MODULE-specific information (32 bytes) */
typedef __HIL_PACKED_PRE struct HIL_FILE_MODULE_INFO_V1_0tag
{
  uint32_t  ulStructVersion;              /**< structure version (major, minor), 0x00010000      */
  uint16_t  usCommunicationClass;         /**< communication class                               */
  uint16_t  usProtocolClass;              /**< protocol class                                    */
  uint32_t  ulDBVersion;                  /**< database version (major, minor)                   */
  uint16_t  ausChannelSizes[4];           /**< required DPM channel sizes, 0=end of list         */
  uint16_t  ausHwOptions[4];              /**< required hardware assembly options (0=not used)   */
  uint8_t   abHwAssignments[4];           /**< xC numbers for HW options (0xFF=free choice)      */
} __HIL_PACKED_POST HIL_FILE_MODULE_INFO_V1_0, *PHIL_FILE_MODULE_INFO_V1_0;



/*****************************************************************************/
/* File Header Subtructures Instantiated as Global Variables in the Firmware */
/*****************************************************************************/

/* !!!! The structure version of the Common Header determines the version of the whole structure !!!!  */

/* basic file header (without Default Header as included in ELF files used to create NXFs, 320 bytes)  */
typedef __HIL_PACKED_PRE struct HIL_FILE_BASIC_HEADER_V3_0tag
{
  HIL_FILE_COMMON_HEADER_V3_0   tCommonHeader;       /**< common header                                */
  HIL_FILE_DEVICE_INFO_V1_0     tDeviceInfo;         /**< device-specific information                  */
  HIL_FILE_MODULE_INFO_V1_0     tModuleInfo[6];      /**< module-specific info for up to 6 modules     */
} __HIL_PACKED_POST HIL_FILE_BASIC_HEADER_V3_0, *PHIL_FILE_BASIC_HEADER_V3_0;


/* basic file header (without Default Header as included in ELF files used to create NXOs, 160 bytes)  */
typedef __HIL_PACKED_PRE struct HIL_FILE_MODULE_HEADER_V3_0tag
{
  HIL_FILE_COMMON_HEADER_V3_0   tCommonHeader;       /**< common header                                */
  HIL_FILE_DEVICE_INFO_V1_0     tDeviceInfo;         /**< device-specific information                  */
  HIL_FILE_MODULE_INFO_V1_0     tModuleInfo;         /**< module-specific info for 1 module            */
} __HIL_PACKED_POST HIL_FILE_MODULE_HEADER_V3_0, *PHIL_FILE_MODULE_HEADER_V3_0;



/*****************************************************************************/
/* Minimal File Header Subset for all NX* Files (Usable with Older Versions) */
/*****************************************************************************/

/* MIN file header (common subset for all complete NX* files, 128 bytes)                               */
typedef __HIL_PACKED_PRE struct HIL_FILE_MIN_HEADER_V3_0tag
{
  HIL_FILE_BOOT_HEADER_V1_0     tBootHeader;         /**< boot header with chip settings               */
  HIL_FILE_COMMON_HEADER_V3_0   tCommonHeader;       /**< common header                                */
} __HIL_PACKED_POST HIL_FILE_MIN_HEADER_V3_0, *PHIL_FILE_MIN_HEADER_V3_0;



/*****************************************************************************/
/* File Header Structures for Hilscher Downloadable Files (V3.0, netX)       */
/*****************************************************************************/

/* NXF file header (for relocated base firmware or complete firmware with linked stacks, 384 bytes)    */
typedef __HIL_PACKED_PRE struct HIL_FILE_NXF_HEADER_V3_0tag
{
  HIL_FILE_BOOT_HEADER_V1_0     tBootHeader;         /**< boot header with chip settings               */
  HIL_FILE_COMMON_HEADER_V3_0   tCommonHeader;       /**< common header                                */
  HIL_FILE_DEVICE_INFO_V1_0     tDeviceInfo;         /**< device-specific information                  */
  HIL_FILE_MODULE_INFO_V1_0     tModuleInfo[6];      /**< module-specific info for 6 comm. channels    */
} __HIL_PACKED_POST HIL_FILE_NXF_HEADER_V3_0, *PHIL_FILE_NXF_HEADER_V3_0;


/* NXO file header (for unrelocated optional firmware modules, 224 bytes)                              */
typedef __HIL_PACKED_PRE struct HIL_FILE_NXO_HEADER_V3_0tag
{
  HIL_FILE_DEFAULT_HEADER_V1_0  tDefaultHeader;      /**< default header                               */
  HIL_FILE_COMMON_HEADER_V3_0   tCommonHeader;       /**< common header                                */
  HIL_FILE_DEVICE_INFO_V1_0     tDeviceInfo;         /**< device-specific information                  */
  HIL_FILE_MODULE_INFO_V1_0     tModuleInfo;         /**< module-specific info for 1 comm. channel     */
} __HIL_PACKED_POST HIL_FILE_NXO_HEADER_V3_0, *PHIL_FILE_NXO_HEADER_V3_0;


/* NXD file header (for database file download, 224 bytes)                                             */
typedef __HIL_PACKED_PRE struct HIL_FILE_NXD_HEADER_V3_0tag
{
  HIL_FILE_DEFAULT_HEADER_V1_0  tDefaultHeader;      /**< default header                               */
  HIL_FILE_COMMON_HEADER_V3_0   tCommonHeader;       /**< common header                                */
  HIL_FILE_DEVICE_INFO_V1_0     tDeviceInfo;         /**< device-specific information                  */
  HIL_FILE_MODULE_INFO_V1_0     tModuleInfo;         /**< module-specific info for 1 comm. channel     */
} __HIL_PACKED_POST HIL_FILE_NXD_HEADER_V3_0, *PHIL_FILE_NXD_HEADER_V3_0;


/* NXL file header (for license file download, 192 bytes)                                              */
typedef __HIL_PACKED_PRE struct HIL_FILE_NXL_HEADER_V3_0tag
{
  HIL_FILE_DEFAULT_HEADER_V1_0  tDefaultHeader;      /**< default header                               */
  HIL_FILE_COMMON_HEADER_V3_0   tCommonHeader;       /**< common header                                */
  HIL_FILE_DEVICE_INFO_V1_0     tDeviceInfo;         /**< device-specific information                  */
} __HIL_PACKED_POST HIL_FILE_NXL_HEADER_V3_0, *PHIL_FILE_NXL_HEADER_V3_0;


/* NXB file header (for binary file download, 192 bytes)                                               */
typedef __HIL_PACKED_PRE struct HIL_FILE_NXB_HEADER_V3_0tag
{
  HIL_FILE_DEFAULT_HEADER_V1_0  tDefaultHeader;      /**< default header                               */
  HIL_FILE_COMMON_HEADER_V3_0   tCommonHeader;       /**< common header                                */
  HIL_FILE_DEVICE_INFO_V1_0     tDeviceInfo;         /**< device-specific information                  */
} __HIL_PACKED_POST HIL_FILE_NXB_HEADER_V3_0, *PHIL_FILE_NXB_HEADER_V3_0;



/*****************************************************************************/
/* Support for MS Visual C++ compiler: Restore default alignment. */
#ifdef _MSC_VER
  #if _MSC_VER >= 1000
    #pragma pack()
  #endif /* _MSC_VER >= 1000 */
#endif /* _MSC_VER */
/*****************************************************************************/

#undef __HIL_PACKED_PRE
#undef __HIL_PACKED_POST



#endif /*  __HilFileHeaderV3_h */
