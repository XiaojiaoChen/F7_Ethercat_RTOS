/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: TLR_Types.h 6827 2015-03-31 15:23:50Z Robert $:

  Description:
    TLR type definitions

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2015-03-31  Added guard for _MSC_VER to allow compilation using -wundef
    2015-01-15  Undo packing of TLR_PACKET_HEADER_T/TLR_UUID_T to avoid alignment issues
    2014-07-07  Added support for IAR C/C++ Compiler (ARM Cores only)
    2014-04-28  Added support for armcc compiler,
                packed TLR_PACKET_HEADER_T and TLR_UUID_T to handle
                strict packing rules of armcc compiler
    2010-06-14  Added __PACKED_PRE / POST macros (as old header
                files might illegally contain them. Theses files
                should be changed to use __TLR_PACKED_PRE / POST)
    2010-04-27  Re-added all TLR_TASK_UID_xx from TLR_Common.h
                Re-added TLR_TASK_UID_T from TLR_Common.h
    2010-04-14  Added Logical Queue defines TLR_PACKET_DEST_xx
    2010-04-07  Added TLR_TBF_BUFFERPOOL_T, TLR_TBF_CALLBACK
    2010-03-23  File created.

**************************************************************************************/


#ifndef __TLR_TYPES_H
#define __TLR_TYPES_H

#ifdef __cplusplus
  extern "C" {
#endif  /* __cplusplus */



/*****************************************************************************/
/* Include Files Required                                                    */
/*****************************************************************************/

#if defined( __RX_INCLUDES_H )
  #error Problem with include order. Please include TLR_Includes.h before rX_Includes.h.
#endif

#if defined (__TLR_USE_CUSTOM_TYPES__)
  #include "TLR_CustomTypes.h"
#else
  #include <stdint.h> /* ISO/IEC 9899:1999 fixed width data types */
#endif



/*****************************************************************************/
/* Symbol Definitions                                                        */
/*****************************************************************************/


/************************ General Symbol Definitions *************************/

/* boolean evaluation */
#define TLR_FALSE  (0)
#define TLR_TRUE   (1)

/* pointer types */
#ifndef FAR
  #define FAR
#endif  /* FAR */

/* storage classes */
#ifndef CONST
  #define CONST  const
#endif  /* CONST */

#ifndef EXTERN
  #define EXTERN extern
#endif  /* EXTERN */

#ifndef STATIC
  #define STATIC static
#endif  /* STATIC */


/******************* Compiler Specific Symbol Definitions ********************/

/* MSVC defines a version rather than a key symbol. Prepare standard key symbol handling. */
#if defined(_MSC_VER)
  #if _MSC_VER >= 1000
    #define __MSVC__
  #endif  /* _MSC_VER >= 1000 */
#endif /* _MSC_VER */


/* check for known compilers using the key symbols of which one should be defined */
#if !defined (__GNUC__) && !defined (__MSVC__) && !defined (__ADS__) && !defined (__REALVIEW__) && !defined (__CC_ARM) && !defined (__ICCARM__) && !defined(__TLR_USE_CUSTOM_COMPILER__)
  #error Unknown compiler type. (Check definitions in TLR_Types.h.)
#endif  /* __MSVC__, __GNUC__, __ADS__, __REALVIEW__ */


/* specific definitions for GNU C compiler */
#if defined (__GNUC__)
  /* tight packing of structure members */
  #define __TLR_PACKED_PRE
  #define __TLR_PACKED_POST  __attribute__ ((packed))
  /* redefinition for inline */
  #ifndef INLINE
    #define INLINE static inline
  #endif  /* INLINE */
#endif  /* __GNUC__ */


/* specific definitions for Microsoft C compiler */
#if defined (__MSVC__)
  /* tight packing of structure members */
  #define __TLR_PACKED_PRE
  #define __TLR_PACKED_POST
  #define PRAGMA_PACK_ENABLE
  #define PRAGMA_PACK_1(label) pack(push, label, 1)
  #define PRAGMA_UNPACK_1(label) pack(pop, label)
  /* redefinition for inline */
  #ifndef INLINE
    #define INLINE static
  #endif  /* INLINE */
  /* strict data type checking */
  #ifndef STRICT
    #define STRICT
  #endif
#endif  /* _MSC_VER >= 1000 */


/* specific definitions for REALVIEW ARM and IAR compiler (ARM cores only) */
#if defined (__ADS__) || defined (__REALVIEW__) || defined (__CC_ARM) || defined (__ICCARM__)
  /* tight packing of structure members */
  #define __TLR_PACKED_PRE  __packed
  #define __TLR_PACKED_POST
  /* redefinition for inline */
  #ifndef INLINE
    #define INLINE static
  #endif  /* INLINE */
#endif  /* __ADS__, __REALVIEW__ */

#if defined(__TLR_USE_CUSTOM_COMPILER__)
  #include <TLR_CustomCompiler.h>
#endif /* __TLR_USE_CUSTOM_COMPILER__ */

#ifndef __RCX__ 
  #ifndef __PACKED_PRE
    #define __PACKED_PRE  __TLR_PACKED_PRE
  #endif

  #ifndef __PACKED_POST
    #define __PACKED_POST __TLR_PACKED_POST
  #endif
#endif

/************************ General Packet Definitions *************************/

/* total packet size definition */
#define TLR_MAX_PACKET_SIZE     (1596)


/* Logical Queue defines */
#define TLR_PACKET_DEST_MID_SYS        (0)
#define TLR_PACKET_DEST_CHANNEL_0      (1)
#define TLR_PACKET_DEST_CHANNEL_1      (2)
#define TLR_PACKET_DEST_CHANNEL_2      (3)
#define TLR_PACKET_DEST_CHANNEL_3      (4)

#define TLR_PACKET_DEST_DEFAULT_CHANNEL (32)


/*** Definitions for the Packet Extension Field ***/

/* mask for sequence number and sequence control portions */
#define TLR_PACKET_SEQ_NR_MASK          (0x0000003F)    /* used for filtering the sequence number */
#define TLR_PACKET_SEQ_MASK             (0x000000C0)    /* used for filtering the sequence control code */

/* sequence control codes */
#define TLR_PACKET_SEQ_NONE             (0x00000000)    /* packet is not part of a packet sequence */
#define TLR_PACKET_SEQ_LAST             (0x00000040)    /* last packet of a packet sequence */
#define TLR_PACKET_SEQ_FIRST            (0x00000080)    /* first packet of a packet sequence */
#define TLR_PACKET_SEQ_MIDDLE           (0x000000C0)    /* packet in the middle of a packet sequence */

/* packet handling flags */
#define TLR_PACKET_NOT_DELETE           (0x00000100)    /* packet must not be returned to a packet pool */
#define TLR_PACKET_RETRY                (0x00000200)    /* packet will be resent based on a predefined retry mechanism */

/* router flags */
#define TLR_PACKET_NO_CNF_THRU_ROUTER   (0x00000400)    /* router must not send response/confirmation packet back */


/*********************** Task Types for TLR_TASK_UID_T ***********************/

/* task type not set */
#define TLR_TASK_UID_TASK_TYPE_INVALID          (0x0000)
/* user application task */
#define TLR_TASK_UID_TASK_TYPE_USER             (0x0001)
/* task belonging to a communication protocol stack */
#define TLR_TASK_UID_TASK_TYPE_PROTOCOL_STACK   (0x0002)
/* task belonging to the rcX operating system */
#define TLR_TASK_UID_TASK_TYPE_RCX              (0x0003)
/* task belonging to the Windows CE operating system */
#define TLR_TASK_UID_TASK_TYPE_WINCE            (0x0004)
/* XPEC channel that has not yet been allocated by a protocol stack */
#define TLR_TASK_UID_TASK_TYPE_XPEC             (0x0005)


/********************* Protocol Types for TLR_TASK_UID_T *********************/

/* protocol type IDs for TLR_TASK_UID_TASK_TYPE_PROTOCOL_STACK */
#define TLR_TASK_UID_STACK_PROFINET_SLAVE       (0x00000001)
#define TLR_TASK_UID_STACK_PROFINET_MASTER      (0x00000002)
#define TLR_TASK_UID_STACK_PROFIBUS_SLAVE       (0x00000003)
#define TLR_TASK_UID_STACK_PROFIBUS_MASTER      (0x00000004)
#define TLR_TASK_UID_STACK_POWERLINK_SLAVE      (0x00000005)
#define TLR_TASK_UID_STACK_ETHERNETIP_MASTER    (0x00000006)
#define TLR_TASK_UID_STACK_ETHERNETIP_SLAVE     (0x00000007)
#define TLR_TASK_UID_STACK_ETHERCAT_SLAVE       (0x00000008)
#define TLR_TASK_UID_STACK_TCPIP                (0x00000009)
#define TLR_TASK_UID_STACK_ASI_MASTER           (0x0000000A)
#define TLR_TASK_UID_STACK_PROFIBUS             (0x0000000B)
#define TLR_TASK_UID_STACK_SERCOSIII_SLAVE      (0x0000000C)
#define TLR_TASK_UID_STACK_ETHERCAT_MASTER      (0x0000000D)

/* protocol type IDs for TLR_TASK_UID_TASK_TYPE_RCX */
#define TLR_TASK_UID_RCX_MID_SYS                (0x00000001)
#define TLR_TASK_UID_RCX_MID_DBG                (0x00000002)



/*****************************************************************************/
/* Class, Type, and Structure Definitions                                    */
/*****************************************************************************/

#if !defined (__TLR_USE_CUSTOM_TYPES__)
  /* signed integers with defined length */
  typedef int8_t              TLR_INT8;
  typedef int16_t             TLR_INT16;
  typedef int32_t             TLR_INT32;
  typedef int64_t             TLR_INT64;
  /* unsigned integers with defined length */
  typedef uint8_t             TLR_UINT8;
  typedef uint16_t            TLR_UINT16;
  typedef uint32_t            TLR_UINT32;
  typedef uint64_t            TLR_UINT64;
  /* 8-bit ANSI characters */
  typedef char                TLR_CHAR;
  typedef char                TLR_STR;
  /* data types with machine word length (avoid use in structures) */
  typedef int                 TLR_INT;
  typedef unsigned int        TLR_UINT;
  typedef unsigned int        TLR_BOOLEAN;
#endif

/* simply nothing */
typedef void                  TLR_VOID;

/* boolean values with defined length */
typedef TLR_UINT8             TLR_BOOLEAN8;
typedef TLR_UINT32            TLR_BOOLEAN32;

/* context specific data types */
typedef TLR_UINT32            TLR_RESULT;
typedef TLR_UINT32            TLR_STATUS;
typedef void*                 TLR_HANDLE;


/******************** Other Basic Structure Definitions **********************/

/* UUID */
typedef __TLR_PACKED_PRE struct
{
  TLR_UINT32  ulData1;
  TLR_UINT16  usData2;
  TLR_UINT16  usData3;
  TLR_UINT8   abData4[8];
} __TLR_PACKED_POST TLR_UUID_T;


/* task UUID with special meaning of the elements */
typedef __TLR_PACKED_PRE struct
{
  TLR_UINT32        ulProtocolType;         /* see TLR_TASK_UID_STACK_xxx */
  TLR_UINT16        usMajorVersion;         /* major number of the task (or stack) version */
  TLR_UINT16        usTaskType;             /* see TLR_TASK_UID_TASK_TYPE_xxx */
  TLR_UINT32        ulLayerLevel;           /* layer number (per the OSI model) */
  TLR_UINT32        ulLayerSubTask;         /* subtask number, e.g. in case of multiple channels */
} __TLR_PACKED_POST TLR_TASK_UID_T;


/* destination queue link (used for routing support) */
typedef struct
{
  TLR_HANDLE  hQue;     /* handle of the queue to send the packets to */
  TLR_UINT32  ulDest;   /* ulDest value for the packets to send */
  TLR_UINT32  ulDestId; /* ulDestId value for the packets to send */
  TLR_UINT32  ulMTU;    /* maximum transfer unit to be sent unfragmented */
} TLR_QUE_LINK_T;


/* source queue link (used for routing support) */
typedef struct
{
  TLR_UINT32  ulSrc;    /* ulSrc value for the packets to send back */
  TLR_UINT32  ulSrcId;  /* ulSrcId value for the packets to send back */
} TLR_QUE_LINK_SOURCE_T;


/* packed access */
__TLR_PACKED_PRE struct TLR_PACKED_UINT16_Ttag {
  TLR_UINT16  usData;
} __TLR_PACKED_POST;
typedef struct TLR_PACKED_UINT16_Ttag TLR_PACKED_UINT16_T;


__TLR_PACKED_PRE struct TLR_PACKED_UINT32_Ttag {
  TLR_UINT32  ulData;
} __TLR_PACKED_POST;
typedef struct TLR_PACKED_UINT32_Ttag TLR_PACKED_UINT32_T;


/* buffer pointer set (Triple buffer - TBF) */
typedef struct
{
  TLR_UINT8*  pabBufA;
  TLR_UINT8*  pabBufB;
  TLR_UINT8*  pabBufC;
} TLR_BUFFERPOOL_T;

typedef TLR_BUFFERPOOL_T  TLR_TBF_BUFFERPOOL_T;
typedef TLR_VOID (*TLR_TBF_CALLBACK)(TLR_HANDLE hTripleBuffer, TLR_VOID* pvParam);


/*********************** Packet Structure Definitions ************************/

/* packet header definition */
typedef __TLR_PACKED_PRE struct
{
  TLR_UINT32  ulDest;   /* destination of the packet (task message queue reference) */
  TLR_UINT32  ulSrc;    /* source of the packet (task message queue reference) */
  TLR_UINT32  ulDestId; /* destination reference (internal use for message routing) */
  TLR_UINT32  ulSrcId;  /* source reference (internal use for message routing) */
  TLR_UINT32  ulLen;    /* length of packet data (starting from the end of the header) */
  TLR_UINT32  ulId;     /* identification reference (internal use by the sender) */
  TLR_UINT32  ulSta;    /* operation status code (error code, initialize with 0) */
  TLR_UINT32  ulCmd;    /* operation command code */
  TLR_UINT32  ulExt;    /* extension count (nonzero in multi-packet transfers) */
  TLR_UINT32  ulRout;   /* router reference (internal use for message routing) */
} __TLR_PACKED_POST TLR_PACKET_HEADER_T;


/* definition of a packet with maximum size */
typedef __TLR_PACKED_PRE struct
{
  TLR_PACKET_HEADER_T   tHead;
  TLR_UINT8             abData[TLR_MAX_PACKET_SIZE - sizeof (TLR_PACKET_HEADER_T)];
} __TLR_PACKED_POST TLR_PACKET_T;


/* definition of a packet with minimum size */
typedef __TLR_PACKED_PRE struct
{
  TLR_PACKET_HEADER_T   tHead;
} __TLR_PACKED_POST TLR_EMPTY_PACKET_T;



/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/


/* none */



/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/


/* none */



/*****************************************************************************/
/* Functions                                                                 */
/*****************************************************************************/


/* none */



#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __TLR_TYPES_H */
