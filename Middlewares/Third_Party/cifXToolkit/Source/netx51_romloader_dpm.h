/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: netx51_romloader_dpm.h 6614 2014-10-08 13:24:44Z stephans $:

  Description:
    netX51 ROM Loader DPM layout

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2014-01-10  initial version

**************************************************************************************/

#ifndef __NETX51_ROMLOADER_DPM__H
#define __NETX51_ROMLOADER_DPM__H

#define NETX51_DETECT_OFFSET1        (0xD9)
#define NETX51_DETECT_VALUE1         (0xF2)
#define NETX51_DETECT_OFFSET2        (0xCC)
#define NETX51_DETECT_VALUE2         (0xF2)

#define NETX51_BOOTID_OFFSET         (0x100)
#define NETX51_BOOTID_DPM             0x4C42584E  /*!< 'NXBL' DPM boot identifier ('NXBL') */
#define NETX51_BOOTID_DPM_STRING      "NXBL"      /*!< 'NXBL' DPM boot identifier ('NXBL') */

#define NETX51_DPM_TONETXMBX_MSK      0x01
#define NETX51_DPM_TOHOSTMBX_MSK      0x02

typedef struct NETX51_HBOOT_HSK_AREA_Ttag
{
  volatile uint32_t   ulHandshakeFlag;
  uint32_t            aulReserved[31];
} NETX51_HBOOT_HSK_AREA_T;

typedef struct NETX51_HBOOT_CFG_AREA_Ttag
{
  volatile uint32_t     ulDpmBootId;
  volatile uint32_t     ulDpmByteSize;
  volatile uint32_t     ulSdramGeneralCtrl;
  volatile uint32_t     ulSdramTimingCtrl;
  volatile uint32_t     ulSdramByteSize;
  volatile uint32_t     aulReserved[25];
  volatile uint32_t     ulNetXToHostDataSize;
  volatile uint32_t     ulHostToNetxDataSize;
} NETX51_HBOOT_CFG_AREA_T;

#define MSK_NX56_dpm_rdy_cfg_rdy_pol        (0x00000001)
#define SRT_NX56_dpm_rdy_cfg_rdy_drv_mode   (1)

#define MSK_NX56_dpm_netx_version_step      (0x000000FF)
#define SRT_NX56_dpm_netx_version_step      (0)
#define MSK_NX56_dpm_netx_version_license   (0x00000100)
#define SRT_NX56_dpm_netx_version_license   (8)
#define MSK_NX56_dpm_netx_version_valid     (0x00000200)
#define SRT_NX56_dpm_netx_version_valid     (9)
#define MSK_NX56_dpm_netx_version_chiptype  (0x00000c00)
#define SRT_NX56_dpm_netx_version_chiptype  (10)

typedef struct NETX51_DPM_CONFIG_AREA_Ttag
{
  volatile uint32_t ulDpmCfg0x0;
  volatile uint32_t ulDpmIfCfg;
  volatile uint32_t ulDpmPioCfg0;
  volatile uint32_t ulDpmPioCfg1;
  volatile uint32_t ulDpmAddrCfg;
  volatile uint32_t ulDpmTimingCfg;
  volatile uint32_t ulDpmRdyCfg;
  volatile uint32_t ulDpmStatus;
  volatile uint32_t ulDpmStatusErrReset;
  volatile uint32_t ulDpmStatusErrAddr;
  volatile uint32_t ulDpmMiscCfg;
  volatile uint32_t ulDpmIoCfgMisc;
  uint32_t          aulReserved1[2];
  volatile uint32_t ulDpmTunnelCfg;
  volatile uint32_t ulDpmItbaddr;
  volatile uint32_t ulDpmWin1End;
  volatile uint32_t ulDpmWin1Map;
  volatile uint32_t ulDpmWin2End;
  volatile uint32_t ulDpmWin2Map;
  volatile uint32_t ulDpmWin3End;
  volatile uint32_t ulDpmWin3Map;
  volatile uint32_t ulDpmWin4End;
  volatile uint32_t ulDpmWin4Map;
  uint32_t          aulReserved2[8];
  volatile uint32_t ulDpmIrqRaw;
  volatile uint32_t ulDpmIrqArmMaskSet;
  volatile uint32_t ulDpmIrqArmMaskReset;
  volatile uint32_t ulDpmIrqArmMasked;
  volatile uint32_t ulDpmIrqXpicMaskSet;
  volatile uint32_t ulDpmIrqXpicMaskReset;
  volatile uint32_t ulDpmIrqXpicMasked;
  volatile uint32_t ulDpmIrqFiqMaskSet;
  volatile uint32_t ulDpmIrqFiqMaskReset;
  volatile uint32_t ulDpmIrqFiqMasked;
  volatile uint32_t ulDpmIrqIrqMaskSet;
  volatile uint32_t ulDpmIrqIrqMaskReset;
  volatile uint32_t ulDpmIrqIrqMasked;
  uint32_t          ulReserved3;
  volatile uint32_t ulDpmSwIrq;
  uint32_t          ulReserved4;
  volatile uint32_t ulDpmReservedNetx50WgdHostTimeout;
  volatile uint32_t ulDpmReservedNetx50WgdHostTrigger;
  volatile uint32_t ulDpmReservedNetx50WgdNetxTimeout;
  volatile uint32_t ulDpmSysStaBigend16;
  volatile uint32_t ulDpmReservedNetx50TimerCtrl;
  volatile uint32_t ulDpmReservedNetx50TimerStartVal;
  volatile uint32_t ulDpmSysSta;
  volatile uint32_t ulDpmResetRequest;
  volatile uint32_t ulDpmFirmwareIrqRaw;
  uint32_t          ulReserved5;
  volatile uint32_t ulDpmFirmwareIrqRaw2;
  uint32_t          ulReserved6;
  volatile uint32_t ulDpmFirmwareIrqMask;
  volatile uint32_t ulDpmNetxVersionBigend16;
  volatile uint32_t ulDpmFirmwareIrqMask2;
  volatile uint32_t ulDpmNetxVersion;
}NETX51_DPM_CONFIG_AREA_T;

typedef struct NETX51_ROMLOADER_DPMtag
{
  NETX51_DPM_CONFIG_AREA_T tDpmConfig;
  NETX51_HBOOT_CFG_AREA_T  tHBootConfig;
  NETX51_HBOOT_HSK_AREA_T  tHandshake;
  volatile uint8_t         abNetxToHostData[512];
  volatile uint8_t         abHostToNetxData[1024];

} NETX51_ROMLOADER_DPM, *PNETX51_ROMLOADER_DPM;

#endif /* __NETX51_ROMLOADER_DPM__H */
