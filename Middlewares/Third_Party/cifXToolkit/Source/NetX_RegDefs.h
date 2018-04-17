/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: NetX_RegDefs.h 6598 2014-10-02 08:57:18Z stephans $:

  Description:
    netX register definitions for DPM/DMA access

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2010-04-21  DMA Triple Buffer definition updated (was an error in manual)
    2006-12-06  obsoleted #pragma once removed
    2006-08-08  created

**************************************************************************************/

/*****************************************************************************/
/*! \file
*    netX register definitions for DPM/DMA access                            */
/*****************************************************************************/

/*****************************************************************************/
/*! \addtogroup CIFX_TK_DPMSTRUCTURE DPM Structure Definition
*   \{                                                                       */
/*****************************************************************************/

#ifndef __NETX_REGDEFS__H
#define __NETX_REGDEFS__H

#if _MSC_VER >= 1000
  #pragma pack(4)
#endif

/*****************************************************************************/
/* NETX loacal memory definitions                                            */
/*****************************************************************************/

#define NETX_LOCAL_MEMORY_SIZE        0x20000
#define NETX_DPM_MEMORY_SIZE          0x10000
#define NETX_DPM_REGBLOCK_SIZE        0x200

#define NET_BOOTLOADER_RESET_TIME     500
#define NET_BOOTLOADER_STARTUP_CYCLES 50
#define NET_BOOTLOADER_STARTUP_WAIT   100
#define NET_BOOTLOADER_STARTUP_TIME   2000

/*****************************************************************************/
/* Structures and Basic DPM Layout structures                                */
/*****************************************************************************/

#define NETX_MAX_DMA_CHANNELS   8

/*****************************************************************************/
/*! Single DMA Channel Configuration Area                                    */
/*****************************************************************************/
typedef struct NETX_DMA_CHANNEL_CONFIGtag
{
  volatile uint32_t ulPCIStartAddr;      /*!< Start Address of DMA on PCI Bus                                      */
  volatile uint32_t ulNetXMemStartAddr;  /*!< Address inside netX where the transfer comes from/goes to            */
  volatile uint32_t ulDMACtrl;           /*!< Control register for starting a transfer or acquiring state          */
  volatile uint32_t ulMbxBase;           /*!< Mailbox Base address                                                 */
  volatile uint32_t ulBufCtrl;           /*!< Control register for buffered transfers (Acknowledge, Buffer Select) */
  volatile uint32_t aulMemBaseBuffer[3]; /*!< Base Addresses of Buffers                                            */
} NETX_DMA_CHANNEL_CONFIG;

/*****************************************************************************/
/*! netX Host Register Block, always located at Offset DPMSize - 0x200       */
/*****************************************************************************/
typedef struct NETX_GLOBAL_REG_BLOCKtag
{
  /* 0xFE00, start of the DMA channel data (8Channels * 8DWords * 4Bytes/DWord = 0x100 Bytes) */
  NETX_DMA_CHANNEL_CONFIG atDmaCtrl[NETX_MAX_DMA_CHANNELS]; /*!< Configuration Register for all 8 DMA Channels */

  /* 0xFF00, start of the netX Host control block */
  volatile uint32_t reserved[47];                      /*!< unused/reserved */

  /* 0xFFBC, start of the defined registers */
  volatile uint32_t ulPCIBaseAddress;                  /*!< PCI Base address of 2nd Memory Window        */
  volatile uint32_t ulWatchDogTimeoutHost;             /*!< Host Watchdog Timeout value                  */
  volatile uint32_t ulWatchDogTrigger;                 /*!< Host Watchdog triggering cell                */
  volatile uint32_t ulWatchDogTimeoutNetx;             /*!< NetX Watchdog Timeout value                  */
  volatile uint32_t reserved2;                         /*!< unused/reserved                              */
  volatile uint32_t ulCyclicTimerControl;              /*!< Control of cyclic timer (repeat/single,
                                                                 timer resolution, up/down)                   */
  volatile uint32_t ulCyclicTimerStart;                /*!< Timer start value                            */
  volatile uint32_t ulSystemState;                     /*!< System state register                        */
  volatile uint32_t ulHostReset;                       /*!< Host reset for initiating a hard reset of
                                                                 the netX chip                                */
  volatile uint32_t ulIRQState_0;                      /*!< IRQ State 0                                  */
  volatile uint32_t ulIRQState_1;                      /*!< IRQ State 1                                  */
  volatile uint32_t reserved3;                         /*!< unused/reserved                              */
  volatile uint32_t reserved4;                         /*!< unused/reserved                              */
  volatile uint32_t ulIRQEnable_0;                     /*!< IRQ enable register 0                        */
  volatile uint32_t ulIRQEnable_1;                     /*!< IRQ enable register 1                        */
  volatile uint32_t reserved5;                         /*!< unused/reserved                              */
  volatile uint32_t reserved6;                         /*!< unused/reserved                              */
} NETX_GLOBAL_REG_BLOCK,*PNETX_GLOBAL_REG_BLOCK;

#if _MSC_VER >= 1000
  #pragma pack()
#endif

/*****************************************************************************/
/* Registers and Masks                                                       */
/*****************************************************************************/

/*****************************************************************************/
/* DMA Host Start Address register                                           */
/*****************************************************************************/
/* DPMHS_CHx_HOST_START Bits [31:2] */
#define MSK_HOST_START_DMA_ADDR               0xFFFFFFFC  /*!< Bitmask indicating DMA start address in host memory*/
#define SRT_HOST_START_DMA_ADDR               2           /*!< Shift right term for DMA start address in host     */
/* DPMHS_CHx_NETX_START Bits [1:0] */
#define MSK_HOST_START_DMA_ADDR_RES0          0x00000003  /*!< Bitmask indicating DMA start address reserved      */
#define SRT_HOST_START_DMA_ADDR_RES0          0           /*!< Shift right term for DMA start address reserved    */
/*****************************************************************************/

/*****************************************************************************/
/* DMA netX Start Address register                                           */
/*****************************************************************************/
/* DPMHS_CHx_NETX_START Bits [31:2] */
#define MSK_NETX_START_DMA_ADDR               0xFFFFFFFC  /*!< Bitmask indicating DMA start address in netX memory*/
#define SRT_NETX_START_DMA_ADDR               2           /*!< Shift right term for DMA start address in netX     */
/* DPMHS_CHx_NETX_START Bits [1:0] */
#define MSK_NETX_START_DMA_ADDR_RES0          0x00000003  /*!< Bitmask indicating DMA start address reserved      */
#define SRT_NETX_START_DMA_ADDR_RES0          0           /*!< Shift right term for DMA start address reserved    */
/*****************************************************************************/

/*****************************************************************************/
/* DMA CTRL register                                                         */
/*****************************************************************************/
/* DPMHS_CHx_HOST_DMA_CTRL Bits [31] */
#define MSK_DMA_CTRL_DONE                     0x80000000  /*!< Bitmask indicating Transfer finished               */
#define SRT_DMA_CTRL_DONE                     31          /*!< Shift right term for Transfer finished flag        */
/* DPMHS_CHx_HOST_DMA_CTRL Bits [30:28] */
#define MSK_DMA_CTRL_STATUS                   0x70000000  /*!< Bitmask for Status code of last Transfer           */
#define SRT_DMA_CTRL_STATUS                   28          /*!< Shift right term for Status code of last transfer  */
    /* DMA control state definition */
  #define DMA_CTRL_STATUS_NOERROR               0           /*!< No Error during transfer         */
  #define DMA_CTRL_STATUS_SEL_TIMEOUT           1           /*!< Device select timeout            */
  #define DMA_CTRL_STATUS_TRDY_TIMEOUT          2           /*!< target nTRDY timeout             */
  #define DMA_CTRL_STATUS_ABORT                 3           /*!< target abort error               */
  #define DMA_CTRL_STATUS_PARITY_ERROR          4           /*!< parity error                     */
  #define DMA_CTRL_STATUS_MBX_ERROR             7           /*!< Mailbox error (MBX not enabled)  */
/* DPMHS_CHx_HOST_DMA_CTRL Bits [27] */
#define MSK_DMA_CTRL_START                    0x08000000  /*!< Bitmask for starting DMA transfer              */
#define SRT_DMA_CTRL_START                    27          /*!< shift right term for starting DMA transfer     */
/* DPMHS_CHx_HOST_DMA_CTRL Bits [26] */
#define MSK_DMA_CTRL_ACTIVE                   0x04000000  /*!< Bitmask showing an active DMA transfer (busy)  */
#define SRT_DMA_CTRL_ACTIVE                   26          /*!< Shift right term for active transfer flag      */
/* DPMHS_CHx_HOST_DMA_CTRL Bits [25] */
#define MSK_DMA_CTRL_IRQ_EN                   0x02000000  /*!< Bitmask for requesting IRQ after transfer      */
#define SRT_DMA_CTRL_IRQ_EN                   25          /*!< Shift right term for IRQ Enable flag           */
/* DPMHS_CHx_HOST_DMA_CTRL Bits [24] */
#define MSK_DMA_CTRL_MBX                      0x01000000  /*!< Bitmask for enabling Mailbox for channel       */
#define SRT_DMA_CTRL_MBX                      24          /*!< Shift right term for Mailbox enable flag       */
/* DPMHS_CHx_HOST_DMA_CTRL Bits [23:21] */
#define MSK_DMA_CTRL_TYPE                     0x00E00000  /*!< Bitmask for DMA transfer type                  */
#define SRT_DMA_CTRL_TYPE                     21          /*!< Shift right term for DMA transfer type         */
  /* DMA type definition */
  #define DMA_CTRL_TYPE_SPECIAL                 0           /*!< Special Cycle (e.g.IRQ Ack)                    */
  #define DMA_CTRL_TYPE_IO                      1           /*!< I/O Cycle                                      */
  #define DMA_CTRL_TYPE_MEMORY                  3           /*!< Memory Cycle                                   */
  #define DMA_CTRL_TYPE_CONFIGURATION           5           /*!< Configuration Cycle                            */
  #define DMA_CTRL_TYPE_MULTIPLEMEMORY          6           /*!< Multiple Memory reads (Host to netX only)      */
/* DPMHS_CHx_HOST_DMA_CTRL Bits [20] */
#define MSK_DMA_CTRL_DIRECTION                0x00100000  /*!< Bitmask for transfer direction (0=Host to netX)*/
#define SRT_DMA_CTRL_DIRECTION                20          /*!< Shift right term for direction                 */
/* DPMHS_CHx_HOST_DMA_CTRL Bits [19:2] */
#define MSK_DMA_CTRL_TRANSFERLENGTH           0x000FFFFF  /*!< Bitmask for transfer length (multiple of DWORD)*/
#define SRT_DMA_CTRL_TRANSFERLENGTH           0           /*!< Shift right term for transfer length           */
/*****************************************************************************/

/*****************************************************************************/
/* Buffer control register                                                   */
/*****************************************************************************/
#define MSK_BUF_CTRL_BUFFERSIZE               0xFF000000  /*!< Bitmask for buffer size                              */
#define SRT_BUF_CTRL_BUFFERSIZE               24          /*!< Shift right term for buffer size                     */
#define MSK_BUF_CTRL_NETX_TO_HOST_ACK         0x00080000  /*!< Bitmask for netX to host buffer acknowledge          */
#define SRT_BUF_CTRL_NETX_TO_HOST_ACK         19          /*!< Shift right term netX to host buffer ack.            */
#define MSK_BUF_CTRL_NETX_TO_HOST_BUF         0x00070000  /*!< Bitmask for netX to Host buffer number               */
#define SRT_BUF_CTRL_NETX_TO_HOST_BUF         16          /*!< Shift right term for Host to netX buffer number      */
#define MSK_BUF_CTRL_HOST_TO_NETX_ACK         0x00000008  /*!< Bitmask for host to netX buffer acknowledge          */
#define SRT_BUF_CTRL_HOST_TO_NETX_ACK         3           /*!< Shift right term for host to netx buffer acknowledge */
#define MSK_BUF_CTRL_HOST_TO_NETX_BUF         0x00000007  /*!< Bitmask for host to netx buffer number               */
#define SRT_BUF_CTRL_HOST_TO_NETX_BUF         0           /*!< Shift right term for host to netx buffer number      */
/*****************************************************************************/

/*****************************************************************************/
/* Mailbox base address register                                             */
/*****************************************************************************/
/* DPMHS_CHx_HOST_MBX_BASE Bits [31:8] */
#define MSK_MBX_BASE_BUFFER_ADDR              0xFFFFFF00  /*!< Bitmask for Mailbox buffer base address              */
#define SRT_MBX_BASE_BUFFER_ADDR              8           /*!< Shift right term for Mailbox buffer base address     */
/* DPMHS_CHx_HOST_MBX_BASE Bits [7:1] */
#define MSK_MBX_BASE_MBX_SIZE                 0x000000FE  /*!< Bitmask for Mailbox size                             */
#define SRT_MBX_BASE_MBX_SIZE                 1           /*!< Shift right term for Mailbox size                    */
  /* Size definition */
  #define MSK_MBX_BASE_MBX_SIZE_256             0x00000000  /*!< Bitmask for 256 Byte Mailbox                         */
  #define MBX_BASE_MBX_SIZE_256                 0           /*!< Value for 256  Byte Mailbox                          */
  #define MSK_MBX_BASE_MBX_SIZE_512             0x00000002  /*!< Bitmask for 512 Byte Mailbox                         */
  #define MBX_BASE_MBX_SIZE_512                 1           /*!< Value for 512 Byte Mailbox                           */
  #define MSK_MBX_BASE_MBX_SIZE_1K              0x00000006  /*!< Bitmask for 1 KByte Mailbox                          */
  #define MBX_BASE_MBX_SIZE_1K                  3           /*!< Value for 1 KByte Mailbox                            */
  #define MSK_MBX_BASE_MBX_SIZE_2K              0x0000000E  /*!< Bitmask for 2 KByte Mailbox                          */
  #define MBX_BASE_MBX_SIZE_2K                  7           /*!< Value for 2 KByte Mailbox                            */
  #define MSK_MBX_BASE_MBX_SIZE_4K              0x0000001E  /*!< Bitmask for 4 KByte Mailbox                          */
  #define MBX_BASE_MBX_SIZE_4K                  15          /*!< Value for 4 KByte Mailbox                            */
  #define MSK_MBX_BASE_MBX_SIZE_8K              0x0000003E  /*!< Bitmask for 8 KByte Mailbox                          */
  #define MBX_BASE_MBX_SIZE_8K                  31          /*!< Value for 8 KByte Mailbox                            */
  #define MSK_MBX_BASE_MBX_SIZE_16K             0x0000007E  /*!< Bitmask for 16 KByte Mailbox                         */
  #define MBX_BASE_MBX_SIZE_16K                 63          /*!< Value for 16 KByte Mailbox                           */
  #define MSK_MBX_BASE_MBX_SIZE_32K             0x000000FE  /*!< Bitmask for 32 KByte Mailbox                         */
  #define MBX_BASE_MBX_SIZE_32K                 127         /*!< Value for 32 KByte Mailbox                           */
/* DPMHS_CHx_HOST_MBX_BASE Bits [0] */
#define MSK_MBX_BASE_TRANSFER_ENABLE          0x00000001  /*!< Bitmask for enabling Mailbox                         */
#define SRT_MBX_BASE_TRANSFER_ENABLE          0           /*!< Shift right term for enabling Mailbox                */
/*****************************************************************************/

/*****************************************************************************/
/* DPM host handshake register (8Bit)                                        */
/*****************************************************************************/
/* DPMHS_DPM_HOST_HANDSHAKE8 Bits [31:24] */
#define MSK_DPM_HSK_HOST_TO_NETX_DATA8        0xFF000000  /*!< Bitmask indicating DPM host to netX handshake data   */
#define SRT_DPM_HSK_HOST_TO_NETX_DATA8        24          /*!< Shift right term for DPM host to netX handshake data */
/* DPMHS_DPM_HOST_HANDSHAKE8 Bits [23:16] */
#define MSK_DPM_HSK_NETX_TO_HOST_DATA8        0x0000FFFF  /*!< Bitmask indicating DPM netX to host handshake data   */
#define SRT_DPM_HSK_NETX_TO_HOST_DATA8        16          /*!< Shift right term for DPM netX to host handshake data */
/* DPMHS_DPM_HOST_HANDSHAKE8 Bits [15:8] */
#define MSK_DPM_HSK_DATA_MEMORY_HIGH          0x0000FF00  /*!< Bitmask indicating DPM handshake data memory high    */
#define SRT_DPM_HSK_DATA_MEMORY_HIGH          8           /*!< Shift right term for DPM handshake data memory high  */
/* DPMHS_DPM_HOST_HANDSHAKE8 Bits [15:8] */
#define MSK_DPM_HSK_DATA_MEMORY_LOW           0x000000FF  /*!< Bitmask indicating DPM handshake data memory low     */
#define SRT_DPM_HSK_DATA_MEMORY_LOW           0           /*!< Shift right term for DPM handshake data memory low   */

/*****************************************************************************/
/* DPM host handshake register (16Bit)                                       */
/*****************************************************************************/
/* DPMHS_DPM_HOST_HANDSHAKE16 Bits [31:16] */
#define MSK_DPM_HSK_HOST_TO_NETX_DATA16       0xFFFF0000  /*!< Bitmask indicating DPM host to netX handshake data   */
#define SRT_DPM_HSK_HOST_TO_NETX_DATA16       16          /*!< Shift right term for DPM host to netX handshake data */
/* DPMHS_DPM_HOST_HANDSHAKE16 Bits [15:0] */
#define MSK_DPM_HSK_NETX_TO_HOST_DATA16       0x0000FFFF  /*!< Bitmask indicating DPM netX to host handshake data   */
#define SRT_DPM_HSK_NETX_TO_HOST_DATA16       0           /*!< Shift right term for DPM netX to host handshake data */

/*****************************************************************************/
/* Watchdog HOST timeout register                                            */
/*****************************************************************************/
/* DPMHS_WDG_HOST_TIMEOUT Bits [31:16] */
#define MSK_WDG_HOST_TIMEOUT_RES0             0xFFFF0000  /*!< Bitmask indicating watchdog host timeout reserved    */
#define SRT_WDG_HOST_TIMEOUT_RES0             16          /*!< Shift right term for watchdog host timeout reserved  */
/* DPMHS_WDG_HOST_TIMEOUT Bits [15:0] */
#define MSK_WDG_HOST_TIMEOUT_VALUE            0x0000FFFF  /*!< Bitmask indicating watchdog host timeout value       */
#define SRT_WDG_HOST_TIMEOUT_VALUE            0           /*!< Shift right term for watchdog host timeout value     */

/*****************************************************************************/
/* Watchdog HOST trigger register                                            */
/*****************************************************************************/
/* DPMHS_WDG_HOST_TRIG Bits [31:16] */
#define MSK_WDG_HOST_TRIGGER_RES0             0xFFFF0000  /*!< Bitmask indicating watchdog host trigger reserved    */
#define SRT_WDG_HOST_TRIGGER_RES0             16          /*!< Shift right term for watchdog host trigger reserved  */
/* DPMHS_WDG_HOST_TRIG Bits [15:0] */
#define MSK_WDG_HOST_TRIGGER_CODE             0x0000FFFF  /*!< Bitmask indicating watchdog host trigger code        */
#define SRT_WDG_HOST_TRIGGER_CODE             0           /*!< Shift right term for watchdog host trigger code      */

/*****************************************************************************/
/* Watchdog ARM timeout register                                             */
/*****************************************************************************/
/* DPMHS_WDG_ARM_TIMEOUT Bits [31:16] */
#define MSK_WDG_ARM_RES0                      0xFFFF0000  /*!< Bitmask indicating watchdog ARM timeout reserved     */
#define SRT_WDG_ARM_RES0                      16          /*!< Shift right term for watchdog ARM timeout reserved   */
/* DPMHS_WDG_ARM_TIMEOUT Bits [15:0] */
#define MSK_WDG_ARM_TIMEOUT_VAL               0x0000FFFF  /*!< Bitmask indicating watchdog ARM timeout value        */
#define SRT_WDG_ARM_TIMEOUT_VAL               0           /*!< Shift right term for watchdog ARM timeout value      */

/*****************************************************************************/
/* Timer control register                                                    */
/*****************************************************************************/
/* DPMHS_TMR_CTRL Bits [31:16] */
#define MSK_TIMER_CTRL_RES1                   0xFFFF0000  /*!< Bitmask timer control reserved                       */
#define SRT_TIMER_CTRL_RES1                   16          /*!< Shift right term for timer control reserved          */
/* DPMHS_TMR_CTRL Bits [15] */
#define MSK_TIMER_CTRL_START                  0x00008000  /*!< Bitmask for starting timer                           */
#define SRT_TIMER_CTRL_START                  15          /*!< Shift right term for start flag                      */
/* DPMHS_TMR_CTRL Bits [14:5] */
#define MSK_TIMER_CTRL_RES0                   0x00007FE0  /*!< Bitmask timer control reserved                       */
#define SRT_TIMER_CTRL_RES0                   5           /*!< Shift right term for timer control reserved          */
/* DPMHS_TMR_CTRL Bits [4] */
#define MSK_TIMER_CTRL_SERR_EN                0x00000010  /*!< Bitmask for enabling system error on timer elapse    */
#define SRT_TIMER_CTRL_SERR_EN                4           /*!< Shift right term for system error enabling flag      */
/* DPMHS_TMR_CTRL Bits [3] */
#define MSK_TIMER_CTRL_FNCT_RELOAD            0x00000008  /*!< Bitmask for enabling cyclic timer                    */
#define SRT_TIMER_CTRL_FNCT_RELOAD            3           /*!< Shift right term for cyclic timer enable flag        */
/* DPMHS_TMR_CTRL Bits [2:0] */
#define MSK_TIMER_CTRL_CLKDIV                 0x00000007  /*!< Bitmask for clock divider (which counts timer value) */
#define SRT_TIMER_CTRL_CLKDIV                 0           /*!< Shift right term for clock divider settings          */
  /* Definiton of the timer clock divider */
  #define MSK_TIMER_CTRL_CLKDIV_100US           0x00000000  /*!< Set Clock divider to 100 us */
  #define MSK_TIMER_CTRL_CLKDIV_10US            0x00000001  /*!< Set Clock divider to  10 us */
  #define MSK_TIMER_CTRL_CLKDIV_1US             0x00000002  /*!< Set Clock divider to   1 us */
  #define MSK_TIMER_CTRL_CLKDIV_100NS           0x00000003  /*!< Set Clock divider to 100 ns */
/*****************************************************************************/

/*****************************************************************************/
/* Timer start value register                                                */
/*****************************************************************************/
/* DPMHS_TMR_START_VALUE Bits [31:16] */
#define MSK_TMR_START_RES0                    0xFFFF0000  /*!< Bitmask indicating timer start reserved            */
#define SRT_TMR_START_RES0                    16          /*!< Shift right term for timer start reserved          */
/* DPMHS_CHx_NETX_START Bits [15:0] */
#define MSK_TMR_START_VALUE                   0x0000FFFF  /*!< Bitmask indicating timer start value               */
#define SRT_TMR_START_VALUE                   0           /*!< Shift right term for timer start value             */

/*****************************************************************************/
/* Systen Status register                                                    */
/*****************************************************************************/
/* DPMHS_SYS_STA Bits [31:16] */
#define MSK_SYS_STA_RES0                      0xFFFF0000  /*!< Bitmask for system state reserved                    */
#define SRT_SYS_STA_RES0                      16          /*!< Shift right term system state reserved               */
/* DPMHS_SYS_STA Bits [15:8] */
#define MSK_SYS_STA_NETX_STATE_CODE           0x0000FF00  /*!< Bitmask for system state netx state code             */
#define SRT_SYS_STA_NETX_STATE_CODE           8           /*!< Shift right term system state netx state code        */
/* DPMHS_SYS_STA Bits [7:4] */
#define MSK_SYS_STA_HOST_STATE                0x000000F0  /*!< Bitmask for system state host state                  */
#define SRT_SYS_STA_HOST_STATE                4           /*!< Shift right term system state host state             */
/* DPMHS_SYS_STA Bits [3:2] */
#define MSK_SYS_STA_NEXT_STATE                0x0000000C  /*!< Bitmask for system state netX state                  */
#define SRT_SYS_STA_NEXT_STATE                2           /*!< Shift right term system state netX state             */
/* DPMHS_SYS_STA Bits [1] */
#define MSK_SYS_STA_RUN                       0x00000002  /*!< Bitmask for system state run                         */
#define SRT_SYS_STA_RUN                       1           /*!< Shift right term system state run                    */
/* DPMHS_SYS_STA Bits [0] */
#define MSK_SYS_STA_READY                     0x00000001  /*!< Bitmask for system state ready                       */
#define SRT_SYS_STA_READY                     0           /*!< Shift right term system state ready                  */
/*****************************************************************************/

/*****************************************************************************/
/* DPM Host side reset register                                              */
/*****************************************************************************/
/* DPMHS_RES_REQ Bits [31:17] */
#define MSK_RES_REQ_RES0                      0xFFFE0000  /*!< Bitmask for reset request reserved                   */
#define SRT_RES_REQ_RES0                      17          /*!< Shift right term request reserved                    */
/* DPMHS_RES_REQ Bits [16:8] */
#define MSK_RES_REQ_COUNT                     0x0001FF00  /*!< Bitmask for reset request counter                    */
#define SRT_RES_REQ_COUNT                     8           /*!< Shift right term request counter                     */
/* DPMHS_RES_REQ Bits [7:0] */
#define MSK_RES_REQ_CTRL                      0x000000FF  /*!< Bitmask for reset request control                    */
#define SRT_RES_REQ_CTRL                      0           /*!< Shift right term request control                     */
/*****************************************************************************/

/*****************************************************************************/
/* Interrupt status 0 register                                               */
/*****************************************************************************/
/* DPMHS_INT_STA0 Bits [31:25] */
#define MSK_IRQ_STA0_INT_REQ                  0x80000000  /*!< Global Interrupt bitmask                 */
#define SRT_IRQ_STA0_INT_REQ                  31          /*!< Shift right term for global interrupt    */
#define MSK_IRQ_STA0_MEM_LOCK                 0x40000000  /*!< Memory lock interrupt bitmask            */
#define SRT_IRQ_STA0_MEM_LOCK                 30          /*!< Shift right term for memory lock irq     */
#define MSK_IRQ_STA0_WATCHDOG                 0x20000000  /*!< Watchdog interrupt bitmask               */
#define SRT_IRQ_STA0_WATCHDOG                 29          /*!< Shift right term for watchdog irq        */
/* DPMHS_INT_STA0 Bits [28:27] */
#define MSK_IRQ_STA0_RES1                     0x18000000  /*!< Interrupt STA0 reserved bitmask          */
#define SRT_IRQ_STA0_RES1                     27          /*!< Shift right term for reserved bitmask    */
/* DPMHS_INT_STA0 Bits [26:25] */
#define MSK_IRQ_STA0_SYSSTA                   0x04000000  /*!< System state change interrupt bitmask    */
#define SRT_IRQ_STA0_SYSSTA                   26          /*!< Shift right term for System state change */
#define MSK_IRQ_STA0_TIMER                    0x02000000  /*!< Timer interrupt bitmask                  */
#define SRT_IRQ_STA0_TIMER                    25          /*!< Shift right term for timer irq           */
/* DPMHS_INT_STA0 Bits [24] */
#define MSK_IRQ_STA0_RES0                     0x01000000  /*!< Interrupt STA0 reserved bitmask          */
#define SRT_IRQ_STA0_RES0                     24          /*!< Shift right term for reserved bitmask    */
/* DPMHS_INT_STA0 Bits [23:16] */
#define MSK_IRQ_STA0_VECTOR                   0x00FF0000  /*!< Interrupt vector bitmask                 */
#define SRT_IRQ_STA0_VECTOR                   16          /*!< Shift right term for interrupt vector    */
  /* Interrupt vector */
  #define MSK_IRQ_STA0_VECTOR_HS0               0x00100000  /*!< Handshake cell  0 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS0                   0x10        /*!< Handshake cell  0 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS1               0x00110000  /*!< Handshake cell  1 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS1                   0x11        /*!< Handshake cell  1 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS2               0x00120000  /*!< Handshake cell  2 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS2                   0x12        /*!< Handshake cell  2 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS3               0x00130000  /*!< Handshake cell  3 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS3                   0x13        /*!< Handshake cell  3 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS4               0x00140000  /*!< Handshake cell  4 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS4                   0x14        /*!< Handshake cell  4 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS5               0x00150000  /*!< Handshake cell  5 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS5                   0x15        /*!< Handshake cell  5 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS6               0x00160000  /*!< Handshake cell  6 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS6                   0x16        /*!< Handshake cell  6 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS7               0x00170000  /*!< Handshake cell  7 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS7                   0x17        /*!< Handshake cell  7 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS8               0x00180000  /*!< Handshake cell  8 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS8                   0x18        /*!< Handshake cell  8 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS9               0x00190000  /*!< Handshake cell  9 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS9                   0x19        /*!< Handshake cell  9 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS10              0x001A0000  /*!< Handshake cell 10 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS10                  0x1A        /*!< Handshake cell 10 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS11              0x001B0000  /*!< Handshake cell 11 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS11                  0x1B        /*!< Handshake cell 11 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS12              0x001C0000  /*!< Handshake cell 12 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS12                  0x1C        /*!< Handshake cell 12 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS13              0x001D0000  /*!< Handshake cell 13 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS13                  0x1D        /*!< Handshake cell 13 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS14              0x001E0000  /*!< Handshake cell 14 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS14                  0x1E        /*!< Handshake cell 14 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_HS15              0x001F0000  /*!< Handshake cell 15 interrupt bitmask           */
  #define IRQ_STA0_VECTOR_HS15                  0x1F        /*!< Handshake cell 15 interrupt value             */
  #define MSK_IRQ_STA0_VECTOR_NETXC_DATA_CH0    0x00200000  /*!< netX controlled DMA Ch#0 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_NETXC_DATA_CH0        0x20        /*!< netX controlled DMA Ch#0 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_NETXC_DATA_CH1    0x00210000  /*!< netX controlled DMA Ch#1 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_NETXC_DATA_CH1        0x21        /*!< netX controlled DMA Ch#1 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_NETXC_DATA_CH2    0x00220000  /*!< netX controlled DMA Ch#2 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_NETXC_DATA_CH2        0x22        /*!< netX controlled DMA Ch#2 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_NETXC_DATA_CH3    0x00230000  /*!< netX controlled DMA Ch#3 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_NETXC_DATA_CH3        0x23        /*!< netX controlled DMA Ch#3 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_NETXC_DATA_CH4    0x00240000  /*!< netX controlled DMA Ch#4 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_NETXC_DATA_CH4        0x24        /*!< netX controlled DMA Ch#4 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_NETXC_DATA_CH5    0x00250000  /*!< netX controlled DMA Ch#5 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_NETXC_DATA_CH5        0x25        /*!< netX controlled DMA Ch#5 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_NETXC_DATA_CH6    0x00260000  /*!< netX controlled DMA Ch#6 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_NETXC_DATA_CH6        0x26        /*!< netX controlled DMA Ch#6 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_NETXC_DATA_CH7    0x00270000  /*!< netX controlled DMA Ch#7 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_NETXC_DATA_CH7        0x27        /*!< netX controlled DMA Ch#7 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_NETXC_MBX_CH0     0x00300000  /*!< netX controlled DMA Ch#0 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_NETXC_MBX_CH0         0x30        /*!< netX controlled DMA Ch#0 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_NETXC_MBX_CH1     0x00310000  /*!< netX controlled DMA Ch#1 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_NETXC_MBX_CH1         0x31        /*!< netX controlled DMA Ch#1 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_NETXC_MBX_CH2     0x00320000  /*!< netX controlled DMA Ch#2 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_NETXC_MBX_CH2         0x32        /*!< netX controlled DMA Ch#2 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_NETXC_MBX_CH3     0x00330000  /*!< netX controlled DMA Ch#3 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_NETXC_MBX_CH3         0x33        /*!< netX controlled DMA Ch#3 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_NETXC_MBX_CH4     0x00340000  /*!< netX controlled DMA Ch#4 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_NETXC_MBX_CH4         0x34        /*!< netX controlled DMA Ch#4 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_NETXC_MBX_CH5     0x00350000  /*!< netX controlled DMA Ch#5 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_NETXC_MBX_CH5         0x35        /*!< netX controlled DMA Ch#5 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_NETXC_MBX_CH6     0x00360000  /*!< netX controlled DMA Ch#6 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_NETXC_MBX_CH6         0x36        /*!< netX controlled DMA Ch#6 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_NETXC_MBX_CH7     0x00370000  /*!< netX controlled DMA Ch#7 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_NETXC_MBX_CH7         0x37        /*!< netX controlled DMA Ch#7 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_DATA_CH0    0x00400000  /*!< Host controlled DMA Ch#0 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_HOSTC_DATA_CH0        0x40        /*!< Host controlled DMA Ch#0 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_DATA_CH1    0x00410000  /*!< Host controlled DMA Ch#1 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_HOSTC_DATA_CH1        0x41        /*!< Host controlled DMA Ch#1 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_DATA_CH2    0x00420000  /*!< Host controlled DMA Ch#2 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_HOSTC_DATA_CH2        0x42        /*!< Host controlled DMA Ch#2 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_DATA_CH3    0x00430000  /*!< Host controlled DMA Ch#3 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_HOSTC_DATA_CH3        0x43        /*!< Host controlled DMA Ch#3 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_DATA_CH4    0x00440000  /*!< Host controlled DMA Ch#4 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_HOSTC_DATA_CH4        0x44        /*!< Host controlled DMA Ch#4 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_DATA_CH5    0x00450000  /*!< Host controlled DMA Ch#5 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_HOSTC_DATA_CH5        0x45        /*!< Host controlled DMA Ch#5 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_DATA_CH6    0x00460000  /*!< Host controlled DMA Ch#6 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_HOSTC_DATA_CH6        0x46        /*!< Host controlled DMA Ch#6 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_DATA_CH7    0x00470000  /*!< Host controlled DMA Ch#7 irq (data) bitmask   */
  #define IRQ_STA0_VECTOR_HOSTC_DATA_CH7        0x47        /*!< Host controlled DMA Ch#7 irq (data) value     */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_MBX_CH0     0x00500000  /*!< Host controlled DMA Ch#0 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_HOSTC_MBX_CH0         0x50        /*!< Host controlled DMA Ch#0 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_MBX_CH1     0x00510000  /*!< Host controlled DMA Ch#1 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_HOSTC_MBX_CH1         0x51        /*!< Host controlled DMA Ch#1 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_MBX_CH2     0x00520000  /*!< Host controlled DMA Ch#2 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_HOSTC_MBX_CH2         0x52        /*!< Host controlled DMA Ch#2 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_MBX_CH3     0x00530000  /*!< Host controlled DMA Ch#3 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_HOSTC_MBX_CH3         0x53        /*!< Host controlled DMA Ch#3 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_MBX_CH4     0x00540000  /*!< Host controlled DMA Ch#4 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_HOSTC_MBX_CH4         0x54        /*!< Host controlled DMA Ch#4 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_MBX_CH5     0x00550000  /*!< Host controlled DMA Ch#5 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_HOSTC_MBX_CH5         0x55        /*!< Host controlled DMA Ch#5 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_MBX_CH6     0x00560000  /*!< Host controlled DMA Ch#6 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_HOSTC_MBX_CH6         0x56        /*!< Host controlled DMA Ch#6 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_HOSTC_MBX_CH7     0x00570000  /*!< Host controlled DMA Ch#7 irq (mbx) bitmask    */
  #define IRQ_STA0_VECTOR_HOSTC_MBX_CH7         0x57        /*!< Host controlled DMA Ch#7 irq (mbx) value      */
  #define MSK_IRQ_STA0_VECTOR_MEMLOCK           0x00600000  /*!< Memory lock interrupt bitmask                 */
  #define IRQ_STA0_VECTOR_MEMLOCK               0x60        /*!< Memory lock interrupt value                   */
  #define MSK_IRQ_STA0_VECTOR_WDGTIMEOUT        0x00610000  /*!< Watchdog timeout bitmask                      */
  #define IRQ_STA0_VECTOR_WDGTIMEOUT            0x61        /*!< Watchdog timeout value                        */
  #define MSK_IRQ_STA0_VECTOR_SYSSTA            0x00700000  /*!< System state change intterupt bitmask         */
  #define IRQ_STA0_VECTOR_SYSSTA                0x70        /*!< System state change intterupt value           */
  #define MSK_IRQ_STA0_VECTOR_TIMER             0x00710000  /*!< Timer interrupt bitmask                       */
  #define IRQ_STA0_VECTOR_TIMER                 0x71        /*!< Timer interrupt value                         */
/* DPMHS_INT_STA0 Bits [15:0] */
#define MSK_IRQ_STA0_HANDSHAKE                0x0000FFFF  /*!< Handshake interrupt mask (Each bit = 1 cell)  */
#define SRT_IRQ_STA0_HANDSHAKE                0           /*!< Shift right term for handshake interrupt      */
/*****************************************************************************/

/*****************************************************************************/
/* Interrupt status 1 register                                               */
/*****************************************************************************/
/* DPMHS_INT_STA1 Bits [31:24] */
#define MSK_IRQ_STA1_NETXC_DATA_CH7           0x80000000  /*!< netX controlled DMA Ch#7 irq (data) bitmask   */
#define SRT_IRQ_STA1_NETXC_DATA_CH7           31          /*!< netX controlled DMA Ch#7 irq (data) srt       */
#define MSK_IRQ_STA1_NETXC_DATA_CH6           0x40000000  /*!< netX controlled DMA Ch#6 irq (data) bitmask   */
#define SRT_IRQ_STA1_NETXC_DATA_CH6           30          /*!< netX controlled DMA Ch#6 irq (data) srt       */
#define MSK_IRQ_STA1_NETXC_DATA_CH5           0x20000000  /*!< netX controlled DMA Ch#5 irq (data) bitmask   */
#define SRT_IRQ_STA1_NETXC_DATA_CH5           29          /*!< netX controlled DMA Ch#5 irq (data) srt       */
#define MSK_IRQ_STA1_NETXC_DATA_CH4           0x10000000  /*!< netX controlled DMA Ch#4 irq (data) bitmask   */
#define SRT_IRQ_STA1_NETXC_DATA_CH4           28          /*!< netX controlled DMA Ch#4 irq (data) srt       */
#define MSK_IRQ_STA1_NETXC_DATA_CH3           0x08000000  /*!< netX controlled DMA Ch#3 irq (data) bitmask   */
#define SRT_IRQ_STA1_NETXC_DATA_CH3           27          /*!< netX controlled DMA Ch#3 irq (data) srt       */
#define MSK_IRQ_STA1_NETXC_DATA_CH2           0x04000000  /*!< netX controlled DMA Ch#2 irq (data) bitmask   */
#define SRT_IRQ_STA1_NETXC_DATA_CH2           26          /*!< netX controlled DMA Ch#2 irq (data) srt       */
#define MSK_IRQ_STA1_NETXC_DATA_CH1           0x02000000  /*!< netX controlled DMA Ch#1 irq (data) bitmask   */
#define SRT_IRQ_STA1_NETXC_DATA_CH1           25          /*!< netX controlled DMA Ch#1 irq (data) srt       */
#define MSK_IRQ_STA1_NETXC_DATA_CH0           0x01000000  /*!< netX controlled DMA Ch#0 irq (data) bitmask   */
#define SRT_IRQ_STA1_NETXC_DATA_CH0           24          /*!< netX controlled DMA Ch#0 irq (data) srt       */
/* DPMHS_INT_STA1 Bits [23:16] */
#define MSK_IRQ_STA1_NETXC_MBX_CH7            0x00800000  /*!< netX controlled DMA Ch#7 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_NETXC_MBX_CH7            23          /*!< netX controlled DMA Ch#7 irq (mbx) srt        */
#define MSK_IRQ_STA1_NETXC_MBX_CH6            0x00400000  /*!< netX controlled DMA Ch#6 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_NETXC_MBX_CH6            22          /*!< netX controlled DMA Ch#6 irq (mbx) srt        */
#define MSK_IRQ_STA1_NETXC_MBX_CH5            0x00200000  /*!< netX controlled DMA Ch#5 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_NETXC_MBX_CH5            21          /*!< netX controlled DMA Ch#5 irq (mbx) srt        */
#define MSK_IRQ_STA1_NETXC_MBX_CH4            0x00100000  /*!< netX controlled DMA Ch#4 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_NETXC_MBX_CH4            20          /*!< netX controlled DMA Ch#4 irq (mbx) srt        */
#define MSK_IRQ_STA1_NETXC_MBX_CH3            0x00080000  /*!< netX controlled DMA Ch#3 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_NETXC_MBX_CH3            19          /*!< netX controlled DMA Ch#3 irq (mbx) srt        */
#define MSK_IRQ_STA1_NETXC_MBX_CH2            0x00040000  /*!< netX controlled DMA Ch#2 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_NETXC_MBX_CH2            18          /*!< netX controlled DMA Ch#2 irq (mbx) srt        */
#define MSK_IRQ_STA1_NETXC_MBX_CH1            0x00020000  /*!< netX controlled DMA Ch#1 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_NETXC_MBX_CH1            17          /*!< netX controlled DMA Ch#1 irq (mbx) srt        */
#define MSK_IRQ_STA1_NETXC_MBX_CH0            0x00010000  /*!< netX controlled DMA Ch#0 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_NETXC_MBX_CH0            16          /*!< netX controlled DMA Ch#0 irq (mbx) srt        */
/* DPMHS_INT_STA1 Bits [15:8] */
#define MSK_IRQ_STA1_HOSTC_DATA_CH7           0x00008000  /*!< Host controlled DMA Ch#7 irq (data) bitmask   */
#define SRT_IRQ_STA1_HOSTC_DATA_CH7           15          /*!< Host controlled DMA Ch#7 irq (data) srt       */
#define MSK_IRQ_STA1_HOSTC_DATA_CH6           0x00004000  /*!< Host controlled DMA Ch#6 irq (data) bitmask   */
#define SRT_IRQ_STA1_HOSTC_DATA_CH6           14          /*!< Host controlled DMA Ch#6 irq (data) srt       */
#define MSK_IRQ_STA1_HOSTC_DATA_CH5           0x00002000  /*!< Host controlled DMA Ch#5 irq (data) bitmask   */
#define SRT_IRQ_STA1_HOSTC_DATA_CH5           13          /*!< Host controlled DMA Ch#5 irq (data) srt       */
#define MSK_IRQ_STA1_HOSTC_DATA_CH4           0x00001000  /*!< Host controlled DMA Ch#4 irq (data) bitmask   */
#define SRT_IRQ_STA1_HOSTC_DATA_CH4           12          /*!< Host controlled DMA Ch#4 irq (data) srt       */
#define MSK_IRQ_STA1_HOSTC_DATA_CH3           0x00000800  /*!< Host controlled DMA Ch#3 irq (data) bitmask   */
#define SRT_IRQ_STA1_HOSTC_DATA_CH3           11          /*!< Host controlled DMA Ch#3 irq (data) srt       */
#define MSK_IRQ_STA1_HOSTC_DATA_CH2           0x00000400  /*!< Host controlled DMA Ch#2 irq (data) bitmask   */
#define SRT_IRQ_STA1_HOSTC_DATA_CH2           10          /*!< Host controlled DMA Ch#2 irq (data) srt       */
#define MSK_IRQ_STA1_HOSTC_DATA_CH1           0x00000200  /*!< Host controlled DMA Ch#1 irq (data) bitmask   */
#define SRT_IRQ_STA1_HOSTC_DATA_CH1           9           /*!< Host controlled DMA Ch#1 irq (data) srt       */
#define MSK_IRQ_STA1_HOSTC_DATA_CH0           0x00000100  /*!< Host controlled DMA Ch#0 irq (data) bitmask   */
#define SRT_IRQ_STA1_HOSTC_DATA_CH0           8           /*!< Host controlled DMA Ch#0 irq (data) srt       */
/* DPMHS_INT_STA1 Bits [7:0] */
#define MSK_IRQ_STA1_HOSTC_MBX_CH7            0x00000080  /*!< Host controlled DMA Ch#7 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_HOSTC_MBX_CH7            7           /*!< Host controlled DMA Ch#7 irq (mbx) srt        */
#define MSK_IRQ_STA1_HOSTC_MBX_CH6            0x00000040  /*!< Host controlled DMA Ch#6 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_HOSTC_MBX_CH6            6           /*!< Host controlled DMA Ch#6 irq (mbx) srt        */
#define MSK_IRQ_STA1_HOSTC_MBX_CH5            0x00000020  /*!< Host controlled DMA Ch#5 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_HOSTC_MBX_CH5            5           /*!< Host controlled DMA Ch#5 irq (mbx) srt        */
#define MSK_IRQ_STA1_HOSTC_MBX_CH4            0x00000010  /*!< Host controlled DMA Ch#4 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_HOSTC_MBX_CH4            4           /*!< Host controlled DMA Ch#4 irq (mbx) srt        */
#define MSK_IRQ_STA1_HOSTC_MBX_CH3            0x00000008  /*!< Host controlled DMA Ch#3 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_HOSTC_MBX_CH3            3           /*!< Host controlled DMA Ch#3 irq (mbx) srt        */
#define MSK_IRQ_STA1_HOSTC_MBX_CH2            0x00000004  /*!< Host controlled DMA Ch#2 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_HOSTC_MBX_CH2            2           /*!< Host controlled DMA Ch#2 irq (mbx) srt        */
#define MSK_IRQ_STA1_HOSTC_MBX_CH1            0x00000002  /*!< Host controlled DMA Ch#1 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_HOSTC_MBX_CH1            1           /*!< Host controlled DMA Ch#1 irq (mbx) srt        */
#define MSK_IRQ_STA1_HOSTC_MBX_CH0            0x00000001  /*!< Host controlled DMA Ch#0 irq (mbx) bitmask    */
#define SRT_IRQ_STA1_HOSTC_MBX_CH0            0           /*!< Host controlled DMA Ch#0 irq (mbx) srt        */
/*****************************************************************************/

/*****************************************************************************/
/* Interrupt enable 0 register                                               */
/*****************************************************************************/
/* DPMHS_INT_EN0 Bits [31:29] */
#define MSK_IRQ_EN0_INT_REQ                   0x80000000  /*!< Global Interrupt bitmask                 */
#define SRT_IRQ_EN0_INT_REQ                   31          /*!< Shift right term for global interrupt    */
#define MSK_IRQ_EN0_MEM_LOCK                  0x40000000  /*!< Memory lock interrupt bitmask            */
#define SRT_IRQ_EN0_MEM_LOCK                  30          /*!< Shift right term for memory lock irq     */
#define MSK_IRQ_EN0_WATCHDOG                  0x20000000  /*!< Watchdog interrupt bitmask               */
#define SRT_IRQ_EN0_WATCHDOG                  29          /*!< Shift right term for watchdog irq        */
/* DPMHS_INT_EN0 Bits [28:27] */
#define MSK_IRQ_EN0_RES_1                     0x18000000  /*!< Reserved bitmask                         */
#define SRT_IRQ_EN0_RES_1                     27          /*!< Shift right term reserved bitmask        */
/* DPMHS_INT_EN0 Bits [26:25] */
#define MSK_IRQ_EN0_SYSSTA                    0x04000000  /*!< System state change interrupt bitmask    */
#define SRT_IRQ_EN0_SYSSTA                    26          /*!< Shift right term for System state change */
#define MSK_IRQ_EN0_TIMER                     0x02000000  /*!< Timer interrupt bitmask                  */
#define SRT_IRQ_EN0_TIMER                     25          /*!< Shift right term for timer irq           */
/* DPMHS_INT_EN0 Bits [24:16] */
#define MSK_IRQ_EN0_RES_0                     0x01FF0000  /*!< Reserved bitmask                         */
#define SRT_IRQ_EN0_RES_0                     16          /*!< Shift right term reserved bitmask        */
/* DPMHS_INT_EN0 Bits [15:0] */
#define MSK_IRQ_EN0_HANDSHAKE                 0x0000FFFF  /*!< Handshake interrupt mask (Each bit = 1 cell)  */
#define SRT_IRQ_EN0_HANDSHAKE                 0           /*!< Shift right term for handshake interrupt      */
/*****************************************************************************/

/*****************************************************************************/
/* Interrupt enable 1 register                                               */
/*****************************************************************************/
/* DPMHS_INT_EN1 Bits [31:24] */
#define MSK_IRQ_EN1_NETXC_DATA_CH7            0x80000000  /*!< netX controlled DMA Ch#7 irq (data) bitmask   */
#define SRT_IRQ_EN1_NETXC_DATA_CH7            31          /*!< netX controlled DMA Ch#7 irq (data) srt       */
#define MSK_IRQ_EN1_NETXC_DATA_CH6            0x40000000  /*!< netX controlled DMA Ch#6 irq (data) bitmask   */
#define SRT_IRQ_EN1_NETXC_DATA_CH6            30          /*!< netX controlled DMA Ch#6 irq (data) srt       */
#define MSK_IRQ_EN1_NETXC_DATA_CH5            0x20000000  /*!< netX controlled DMA Ch#5 irq (data) bitmask   */
#define SRT_IRQ_EN1_NETXC_DATA_CH5            29          /*!< netX controlled DMA Ch#5 irq (data) srt       */
#define MSK_IRQ_EN1_NETXC_DATA_CH4            0x10000000  /*!< netX controlled DMA Ch#4 irq (data) bitmask   */
#define SRT_IRQ_EN1_NETXC_DATA_CH4            28          /*!< netX controlled DMA Ch#4 irq (data) srt       */
#define MSK_IRQ_EN1_NETXC_DATA_CH3            0x08000000  /*!< netX controlled DMA Ch#3 irq (data) bitmask   */
#define SRT_IRQ_EN1_NETXC_DATA_CH3            27          /*!< netX controlled DMA Ch#3 irq (data) srt       */
#define MSK_IRQ_EN1_NETXC_DATA_CH2            0x04000000  /*!< netX controlled DMA Ch#2 irq (data) bitmask   */
#define SRT_IRQ_EN1_NETXC_DATA_CH2            26          /*!< netX controlled DMA Ch#2 irq (data) srt       */
#define MSK_IRQ_EN1_NETXC_DATA_CH1            0x02000000  /*!< netX controlled DMA Ch#1 irq (data) bitmask   */
#define SRT_IRQ_EN1_NETXC_DATA_CH1            25          /*!< netX controlled DMA Ch#1 irq (data) srt       */
#define MSK_IRQ_EN1_NETXC_DATA_CH0            0x01000000  /*!< netX controlled DMA Ch#0 irq (data) bitmask   */
#define SRT_IRQ_EN1_NETXC_DATA_CH0            24          /*!< netX controlled DMA Ch#0 irq (data) srt       */
/* DPMHS_INT_EN1 Bits [23:16] */
#define MSK_IRQ_EN1_NETXC_MBX_CH7             0x00800000  /*!< netX controlled DMA Ch#7 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_NETXC_MBX_CH7             23          /*!< netX controlled DMA Ch#7 irq (mbx) srt        */
#define MSK_IRQ_EN1_NETXC_MBX_CH6             0x00400000  /*!< netX controlled DMA Ch#6 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_NETXC_MBX_CH6             22          /*!< netX controlled DMA Ch#6 irq (mbx) srt        */
#define MSK_IRQ_EN1_NETXC_MBX_CH5             0x00200000  /*!< netX controlled DMA Ch#5 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_NETXC_MBX_CH5             21          /*!< netX controlled DMA Ch#5 irq (mbx) srt        */
#define MSK_IRQ_EN1_NETXC_MBX_CH4             0x00100000  /*!< netX controlled DMA Ch#4 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_NETXC_MBX_CH4             20          /*!< netX controlled DMA Ch#4 irq (mbx) srt        */
#define MSK_IRQ_EN1_NETXC_MBX_CH3             0x00080000  /*!< netX controlled DMA Ch#3 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_NETXC_MBX_CH3             19          /*!< netX controlled DMA Ch#3 irq (mbx) srt        */
#define MSK_IRQ_EN1_NETXC_MBX_CH2             0x00040000  /*!< netX controlled DMA Ch#2 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_NETXC_MBX_CH2             18          /*!< netX controlled DMA Ch#2 irq (mbx) srt        */
#define MSK_IRQ_EN1_NETXC_MBX_CH1             0x00020000  /*!< netX controlled DMA Ch#1 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_NETXC_MBX_CH1             17          /*!< netX controlled DMA Ch#1 irq (mbx) srt        */
#define MSK_IRQ_EN1_NETXC_MBX_CH0             0x00010000  /*!< netX controlled DMA Ch#0 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_NETXC_MBX_CH0             16          /*!< netX controlled DMA Ch#0 irq (mbx) srt        */
/* DPMHS_INT_EN1 Bits [15:8] */
#define MSK_IRQ_EN1_HOSTC_DATA_CH7            0x00008000  /*!< Host controlled DMA Ch#7 irq (data) bitmask   */
#define SRT_IRQ_EN1_HOSTC_DATA_CH7            15          /*!< Host controlled DMA Ch#7 irq (data) srt       */
#define MSK_IRQ_EN1_HOSTC_DATA_CH6            0x00004000  /*!< Host controlled DMA Ch#6 irq (data) bitmask   */
#define SRT_IRQ_EN1_HOSTC_DATA_CH6            14          /*!< Host controlled DMA Ch#6 irq (data) srt       */
#define MSK_IRQ_EN1_HOSTC_DATA_CH5            0x00002000  /*!< Host controlled DMA Ch#5 irq (data) bitmask   */
#define SRT_IRQ_EN1_HOSTC_DATA_CH5            13          /*!< Host controlled DMA Ch#5 irq (data) srt       */
#define MSK_IRQ_EN1_HOSTC_DATA_CH4            0x00001000  /*!< Host controlled DMA Ch#4 irq (data) bitmask   */
#define SRT_IRQ_EN1_HOSTC_DATA_CH4            12          /*!< Host controlled DMA Ch#4 irq (data) srt       */
#define MSK_IRQ_EN1_HOSTC_DATA_CH3            0x00000800  /*!< Host controlled DMA Ch#3 irq (data) bitmask   */
#define SRT_IRQ_EN1_HOSTC_DATA_CH3            11          /*!< Host controlled DMA Ch#3 irq (data) srt       */
#define MSK_IRQ_EN1_HOSTC_DATA_CH2            0x00000400  /*!< Host controlled DMA Ch#2 irq (data) bitmask   */
#define SRT_IRQ_EN1_HOSTC_DATA_CH2            10          /*!< Host controlled DMA Ch#2 irq (data) srt       */
#define MSK_IRQ_EN1_HOSTC_DATA_CH1            0x00000200  /*!< Host controlled DMA Ch#1 irq (data) bitmask   */
#define SRT_IRQ_EN1_HOSTC_DATA_CH1            9           /*!< Host controlled DMA Ch#1 irq (data) srt       */
#define MSK_IRQ_EN1_HOSTC_DATA_CH0            0x00000100  /*!< Host controlled DMA Ch#0 irq (data) bitmask   */
#define SRT_IRQ_EN1_HOSTC_DATA_CH0            8           /*!< Host controlled DMA Ch#0 irq (data) srt       */
/* DPMHS_INT_EN1 Bits [7:0] */
#define MSK_IRQ_EN1_HOSTC_MBX_CH7             0x00000080  /*!< Host controlled DMA Ch#7 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_HOSTC_MBX_CH7             7           /*!< Host controlled DMA Ch#7 irq (mbx) srt        */
#define MSK_IRQ_EN1_HOSTC_MBX_CH6             0x00000040  /*!< Host controlled DMA Ch#6 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_HOSTC_MBX_CH6             6           /*!< Host controlled DMA Ch#6 irq (mbx) srt        */
#define MSK_IRQ_EN1_HOSTC_MBX_CH5             0x00000020  /*!< Host controlled DMA Ch#5 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_HOSTC_MBX_CH5             5           /*!< Host controlled DMA Ch#5 irq (mbx) srt        */
#define MSK_IRQ_EN1_HOSTC_MBX_CH4             0x00000010  /*!< Host controlled DMA Ch#4 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_HOSTC_MBX_CH4             4           /*!< Host controlled DMA Ch#4 irq (mbx) srt        */
#define MSK_IRQ_EN1_HOSTC_MBX_CH3             0x00000008  /*!< Host controlled DMA Ch#3 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_HOSTC_MBX_CH3             3           /*!< Host controlled DMA Ch#3 irq (mbx) srt        */
#define MSK_IRQ_EN1_HOSTC_MBX_CH2             0x00000004  /*!< Host controlled DMA Ch#2 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_HOSTC_MBX_CH2             2           /*!< Host controlled DMA Ch#2 irq (mbx) srt        */
#define MSK_IRQ_EN1_HOSTC_MBX_CH1             0x00000002  /*!< Host controlled DMA Ch#1 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_HOSTC_MBX_CH1             1           /*!< Host controlled DMA Ch#1 irq (mbx) srt        */
#define MSK_IRQ_EN1_HOSTC_MBX_CH0             0x00000001  /*!< Host controlled DMA Ch#0 irq (mbx) bitmask    */
#define SRT_IRQ_EN1_HOSTC_MBX_CH0             0           /*!< Host controlled DMA Ch#0 irq (mbx) srt        */
/*****************************************************************************/

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/

#endif /* __NETX_REGDEFS__H */
