/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: HilPCIDefs.h 6598 2014-10-02 08:57:18Z stephans $:

  Description:
    cifX PCI definitions file

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2010-10-02  netJACK 100 added
    2009-09-04  PCI information for PLX based devices added
    2009-07-15  created

**************************************************************************************/

/* prevent multiple inclusion */
#ifndef __CIFX_PCI_DEFS_H
#define __CIFX_PCI_DEFS_H

#if _MSC_VER >= 1000
  #define __CIFx_PACKED_PRE
  #define __CIFx_PACKED_POST
  #pragma once
  #pragma pack(1)            /* Always align structures to 1Byte boundery */
  #ifndef STRICT             /* Check Typedefinition */
    #define STRICT
  #endif
#endif /* _MSC_VER >= 1000 */

/* support for GNU compiler */
#ifdef __GNUC__
  #define __CIFx_PACKED_PRE
  #define __CIFx_PACKED_POST   __attribute__((packed))
#endif

/*****************************************************************************/
/*! CIFX PCI information                                                     */
/*****************************************************************************/
/* Default Hilscher PCI Information (netX chip only) */
#define HILSCHER_PCI_VENDOR_ID              0x15CF
#define HILSCHER_PCI_SUBSYSTEM_VENDOR_ID    0x15CF

#define NETX_CHIP_PCI_DEVICE_ID             0x0000
#define NETX_CHIP_PCI_SUBYSTEM_ID           0x0000

/* PCI Information for CIFX50-FB and CIFX50-RE cards */
#define CIFX50_PCI_DEVICE_ID                0x0000
#define CIFX50_PCI_SUBYSTEM_ID              0x0000

/* PCI Information for NETPLC100C-FB and NETPLC100C-RE cards */
#define NETPLC100C_PCI_DEVICE_ID            0x0010
#define NETPLC100C_PCI_SUBYSTEM_ID_RAM      0x0000
#define NETPLC100C_PCI_SUBYSTEM_ID_FLASH    0x0001

/* PCI Information for netJACK100 cards */
#define NETJACK100_PCI_DEVICE_ID            0x0020
#define NETJACK100_PCI_SUBYSTEM_ID_RAM      0x0000
#define NETJACK100_PCI_SUBYSTEM_ID_FLASH    0x0001

/* PLX Technology PCI Information */
#define PLX_PCI_VENDOR_ID                   0x10B5
#define PCI9030_DEVICE_ID                   0x9030

/* PCI Information for NXSB-PCA / NX-PCA-PCI cards */
#define NXPCAPCI_REV2_SUBSYS_ID             0x3235
#define NXPCAPCI_REV3_SUBSYS_ID             0x3335

/***************************************************************************/

#if _MSC_VER >= 1000
  #pragma pack()            /* Always align structures to default boundery */
#endif /* _MSC_VER >= 1000 */

#undef __CIFx_PACKED_PRE
#undef __CIFx_PACKED_POST

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/

#endif  /* __CIFX_PCI_DEFS_H */
