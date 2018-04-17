/**************************************************************************************
 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
$Id: OdV3_Public.h 63358 2016-08-19 09:31:05Z Sven $:


Changes:
 Date          Description
 -----------------------------------------------------------------------------------
 2010-07-28    Created
**************************************************************************************/

#ifndef __ODV3_PUBLIC_H
#define __ODV3_PUBLIC_H

#include "OdV3_Defines.h"

/* pragma pack */
#ifdef PRAGMA_PACK_ENABLE
#pragma PRAGMA_PACK_1(ODV3_PUBLIC)
#endif

/******************************************************************************
 * Indication flags
 * bIndicationFlags field
 */
#define ODV3_INDICATION_FLAGS_ON_READ                     0x01
#define ODV3_INDICATION_FLAGS_ON_WRITE                    0x02
#define ODV3_INDICATION_FLAGS_ON_RW_UNDEFINED_SUBOBJ      0x04      /* only on object level (one indication listener) */
#define ODV3_INDICATION_FLAGS_ON_INFO_UNDEFINED_SUBOBJ    0x08      /* only on object level (one indication listener) */
#define ODV3_INDICATION_FLAGS_SUPPORTED                   0x1F
#define ODV3_INDICATION_FLAGS_ALLOWED_ON_OBJ              0x0F
#define ODV3_INDICATION_FLAGS_ALLOWED_ON_SUBOBJ           0x03

/*============================================================================*/
/* basic services */
#define ODV3_READ_OBJECT_REQ                              0x6A00
#define ODV3_READ_OBJECT_CNF                              0x6A01

#define ODV3_READ_OBJECT_IND                              0x6A00
#define ODV3_READ_OBJECT_RES                              0x6A01


#define ODV3_WRITE_OBJECT_REQ                             0x6A02
#define ODV3_WRITE_OBJECT_CNF                             0x6A03

#define ODV3_WRITE_OBJECT_IND                             0x6A02
#define ODV3_WRITE_OBJECT_RES                             0x6A03


#define ODV3_GET_OBJECT_LIST_REQ                          0x6A10
#define ODV3_GET_OBJECT_LIST_CNF                          0x6A11

#define ODV3_GET_OBJECT_LIST_IND                          0x6A10
#define ODV3_GET_OBJECT_LIST_RES                          0x6A11


#define ODV3_GET_OBJECT_INFO_REQ                          0x6A12
#define ODV3_GET_OBJECT_INFO_CNF                          0x6A13

#define ODV3_GET_OBJECT_INFO_IND                          0x6A12
#define ODV3_GET_OBJECT_INFO_RES                          0x6A13


#define ODV3_GET_SUBOBJECT_INFO_REQ                       0x6A14
#define ODV3_GET_SUBOBJECT_INFO_CNF                       0x6A15

#define ODV3_GET_SUBOBJECT_INFO_IND                       0x6A14
#define ODV3_GET_SUBOBJECT_INFO_RES                       0x6A15


#define ODV3_GET_OBJECT_ACCESS_INFO_REQ                   0x6A16
#define ODV3_GET_OBJECT_ACCESS_INFO_CNF                   0x6A17

#define ODV3_GET_OBJECT_ACCESS_INFO_IND                   0x6A16
#define ODV3_GET_OBJECT_ACCESS_INFO_RES                   0x6A17


#define ODV3_GET_OBJECT_SIZE_REQ                          0x6A18
#define ODV3_GET_OBJECT_SIZE_CNF                          0x6A19

#define ODV3_GET_OBJECT_SIZE_IND                          0x6A18
#define ODV3_GET_OBJECT_SIZE_RES                          0x6A19



/* special access type: only allowed on locally created objects / no virtual mode */
#define ODV3_READ_OBJECT_NO_IND_REQ                       0x6A1C
#define ODV3_READ_OBJECT_NO_IND_CNF                       0x6A1D


#define ODV3_GET_OBJECT_COUNT_REQ                         0x6A1E
#define ODV3_GET_OBJECT_COUNT_CNF                         0x6A1F

#define ODV3_GET_OBJECT_COUNT_IND                         0x6A1E
#define ODV3_GET_OBJECT_COUNT_RES                         0x6A1F

#define ODV3_REQUEST_ABORTED_IND                          0x6A2E
#define ODV3_REQUEST_ABORTED_RES                          0x6A2F

#define ODV3_ABORT_REQUEST_REQ                            0x6A2E
#define ODV3_ABORT_REQUEST_CNF                            0x6A2F

#define ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_IND         0x6A2A
#define ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_RES         0x6A2B

#define ODV3_GET_OBJECT_PROPERTIES_IND                    0x6A30
#define ODV3_GET_OBJECT_PROPERTIES_RES                    0x6A31

/*============================================================================*/
/* compound services */
#define ODV3_WRITE_ALL_BY_INDEX_REQ                       0x6A20
#define ODV3_WRITE_ALL_BY_INDEX_CNF                       0x6A21


#define ODV3_READ_ALL_BY_INDEX_REQ                        0x6A22
#define ODV3_READ_ALL_BY_INDEX_CNF                        0x6A23


#define ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ        0x6A24
#define ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF        0x6A25


#define ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ         0x6A26
#define ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF         0x6A27


#define ODV3_RESET_OBJECTS_REQ                            0x6A28
#define ODV3_RESET_OBJECTS_CNF                            0x6A29

#define ODV3_RESET_OBJECTS_IND                            0x6A28
#define ODV3_RESET_OBJECTS_RES                            0x6A29

/*============================================================================*/
/* management services */
#define ODV3_CREATE_OBJECT_REQ                            0x6A80
#define ODV3_CREATE_OBJECT_CNF                            0x6A81


#define ODV3_CREATE_SUBOBJECT_REQ                         0x6A82
#define ODV3_CREATE_SUBOBJECT_CNF                         0x6A83


#define ODV3_DELETE_OBJECT_REQ                            0x6A84
#define ODV3_DELETE_OBJECT_CNF                            0x6A85


#define ODV3_DELETE_SUBOBJECT_REQ                         0x6A86
#define ODV3_DELETE_SUBOBJECT_CNF                         0x6A87


#define ODV3_REGISTER_OBJECT_NOTIFY_REQ                   0x6A90
#define ODV3_REGISTER_OBJECT_NOTIFY_CNF                   0x6A91


#define ODV3_UNREGISTER_OBJECT_NOTIFY_REQ                 0x6A92
#define ODV3_UNREGISTER_OBJECT_NOTIFY_CNF                 0x6A93


#define ODV3_REGISTER_SUBOBJECT_NOTIFY_REQ                0x6A94
#define ODV3_REGISTER_SUBOBJECT_NOTIFY_CNF                0x6A95


#define ODV3_UNREGISTER_SUBOBJECT_NOTIFY_REQ              0x6A96
#define ODV3_UNREGISTER_SUBOBJECT_NOTIFY_CNF              0x6A97


#define ODV3_REGISTER_UNDEFINED_NOTIFY_REQ                0x6AA0
#define ODV3_REGISTER_UNDEFINED_NOTIFY_CNF                0x6AA1


#define ODV3_UNREGISTER_UNDEFINED_NOTIFY_REQ              0x6AA2
#define ODV3_UNREGISTER_UNDEFINED_NOTIFY_CNF              0x6AA3


#define ODV3_REGISTER_OBJINFO_NOTIFY_REQ                  0x6AA4
#define ODV3_REGISTER_OBJINFO_NOTIFY_CNF                  0x6AA5


#define ODV3_UNREGISTER_OBJINFO_NOTIFY_REQ                0x6AA6
#define ODV3_UNREGISTER_OBJINFO_NOTIFY_CNF                0x6AA7


#define ODV3_LOCK_OBJECT_DELETION_REQ                     0x6AB0
#define ODV3_LOCK_OBJECT_DELETION_CNF                     0x6AB1


#define ODV3_UNLOCK_OBJECT_DELETION_REQ                   0x6AB2
#define ODV3_UNLOCK_OBJECT_DELETION_CNF                   0x6AB3


#define ODV3_SET_OBJECT_NAME_REQ                          0x6AB4
#define ODV3_SET_OBJECT_NAME_CNF                          0x6AB5


#define ODV3_SET_SUBOBJECT_NAME_REQ                       0x6AB6
#define ODV3_SET_SUBOBJECT_NAME_CNF                       0x6AB7


/* internal request for stack use */
#define ODV3_RESET_OBJECT_DICTIONARY_REQ                  0x6AB8
#define ODV3_RESET_OBJECT_DICTIONARY_CNF                  0x6AB9


/******************************************************************************
 * Data type management
 */

#define ODV3_CREATE_DATATYPE_REQ                          0x6AC0
#define ODV3_CREATE_DATATYPE_CNF                          0x6AC1


#define ODV3_DELETE_DATATYPE_REQ                          0x6AC2
#define ODV3_DELETE_DATATYPE_CNF                          0x6AC3


/******************************************************************************
 * Timeout setup
 */

#define ODV3_SET_TIMEOUT_REQ                              0x6AD0
#define ODV3_SET_TIMEOUT_CNF                              0x6AD1


#define ODV3_GET_TIMEOUT_REQ                              0x6AD2
#define ODV3_GET_TIMEOUT_CNF                              0x6AD3


/******************************************************************************
 * Version Info Request
 */

#define ODV3_GET_VERSION_REQ                              0x6AF0
#define ODV3_GET_VERSION_CNF                              0x6AF1


/******************************************************************************
 * Packet:  ODV3_CREATE_OBJECT_REQ/ODV3_CREATE_OBJECT_CNF
 *
 * Fragmentation:
 *                            Request             Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request, otherwise it is considered an abort.
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_CREATE_OBJECT_REQ_DATA_Ttag
{
  /* non-fragmentable part */
  uint16_t                                                usIndex;
  uint8_t                                                 bMaxNumOfSubObjs;
  uint8_t                                                 bObjectCode;
  uint16_t                                                usAccessFlags;      /* object-wise flag set, not related to access rights */
  uint8_t                                                 bValueInfo;
  uint8_t                                                 bIndicationFlags;
  uint16_t                                                usDatatype;
  /* following two are only evaluated on SimpleVar */
  uint16_t                                                usAccessRights;
  uint32_t                                                ulMaxFieldUnits;

  uint32_t                                                ulTotalDataBytes;
  /* fragmentable part */
  /* bValueInfo determines what gets appended here */
  uint8_t                                                 abData[1024];
  /* order of fields: (no padding between)
   * - Unit (TLR_UINT32)
   * - Name (TLR_UINT32 ulNameLength, TLR_STR abName[ulNameLength]
   * - Minimum Value (TLR_UINT32 ulMinimumValueLength, TLR_UINT8 abData[ulMinimumValueLength])
   * - Maximum Value (TLR_UINT32 ulMaximumValueLength, TLR_UINT8 abData[ulMaximumValueLength])
   * - Initial Value (TLR_UINT32 ulInitialValueLength, TLR_UINT8 abData[ulInitialValueLength])
   * - Default Value (TLR_UINT32 ulDefaultValueLength, TLR_UINT8 abData[ulDefaultValueLength])
   */
} __PACKED_POST ODV3_CREATE_OBJECT_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_CREATE_OBJECT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_OBJECT_REQ_DATA_T                           tData;
} __PACKED_POST ODV3_CREATE_OBJECT_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_CREATE_OBJECT_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_CREATE_OBJECT_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_CREATE_OBJECT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_OBJECT_CNF_DATA_T                           tData;
} __PACKED_POST ODV3_CREATE_OBJECT_CNF_T;


/* packet union */
typedef union ODV3_CREATE_OBJECT_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_OBJECT_REQ_T                                tReq;
  ODV3_CREATE_OBJECT_CNF_T                                tCnf;
} ODV3_CREATE_OBJECT_PCK_T;


/******************************************************************************
 * Packet:  ODV3_CREATE_SUBOBJECT_REQ/ODV3_CREATE_SUBOBJECT_CNF
 *
 * Fragmentation:
 *                            Request             Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request, otherwise it is considered an abort.
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_CREATE_SUBOBJECT_REQ_DATA_Ttag
{
  /* non-fragmentable part */
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint8_t                                                 bValueInfo;
  uint8_t                                                 bIndicationFlags;
  uint16_t                                                usAccessRights;
  uint16_t                                                usDatatype;
  uint32_t                                                ulMaxFieldUnits;
  uint32_t                                                ulTotalDataBytes;
  /* fragmentable part */
  uint8_t                                                 abData[1024];
  /* order of fields: (no padding between)
   * - Unit (TLR_UINT32)
   * - Name (TLR_UINT32 ulNameLength, TLR_STR abName[ulNameLength]
   * - Minimum Value (TLR_UINT32 ulMinimumValueLength, TLR_UINT8 abData[ulMinimumValueLength])
   * - Maximum Value (TLR_UINT32 ulMaximumValueLength, TLR_UINT8 abData[ulMaximumValueLength])
   * - Initial Value (TLR_UINT32 ulInitialValueLength, TLR_UINT8 abData[ulInitialValueLength])
   * - Default Value (TLR_UINT32 ulDefaultValueLength, TLR_UINT8 abData[ulDefaultValueLength])
   */
} __PACKED_POST ODV3_CREATE_SUBOBJECT_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_CREATE_SUBOBJECT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_SUBOBJECT_REQ_DATA_T                        tData;
} __PACKED_POST ODV3_CREATE_SUBOBJECT_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_CREATE_SUBOBJECT_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_CREATE_SUBOBJECT_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_CREATE_SUBOBJECT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_SUBOBJECT_CNF_DATA_T                        tData;
} __PACKED_POST ODV3_CREATE_SUBOBJECT_CNF_T;


/* packet union */
typedef union ODV3_CREATE_SUBOBJECT_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_SUBOBJECT_REQ_T                             tReq;
  ODV3_CREATE_SUBOBJECT_CNF_T                             tCnf;
} ODV3_CREATE_SUBOBJECT_PCK_T;


/******************************************************************************
 * Packet:  ODV3_DELETE_OBJECT_REQ/ODV3_DELETE_OBJECT_CNF
 */
/* request packet */
typedef __PACKED_PRE struct ODV3_DELETE_OBJECT_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_DELETE_OBJECT_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_DELETE_OBJECT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_OBJECT_REQ_DATA_T                           tData;
} __PACKED_POST ODV3_DELETE_OBJECT_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_DELETE_OBJECT_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_DELETE_OBJECT_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_DELETE_OBJECT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_OBJECT_CNF_DATA_T                           tData;
} __PACKED_POST ODV3_DELETE_OBJECT_CNF_T;


/* packet union */
typedef union ODV3_DELETE_OBJECT_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_OBJECT_REQ_T                                tReq;
  ODV3_DELETE_OBJECT_CNF_T                                tCnf;
} ODV3_DELETE_OBJECT_PCK_T;


/******************************************************************************
 * Packet:  ODV3_DELETE_SUBOBJECT_REQ/ODV3_DELETE_SUBOBJECT_CNF
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_DELETE_SUBOBJECT_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_DELETE_SUBOBJECT_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_DELETE_SUBOBJECT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_SUBOBJECT_REQ_DATA_T                        tData;
} __PACKED_POST ODV3_DELETE_SUBOBJECT_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_DELETE_SUBOBJECT_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_DELETE_SUBOBJECT_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_DELETE_SUBOBJECT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_SUBOBJECT_CNF_DATA_T                        tData;
} __PACKED_POST ODV3_DELETE_SUBOBJECT_CNF_T;


/* packet union */
typedef union ODV3_DELETE_SUBOBJECT_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_SUBOBJECT_REQ_T                             tReq;
  ODV3_DELETE_SUBOBJECT_CNF_T                             tCnf;
} ODV3_DELETE_SUBOBJECT_PCK_T;

/******************************************************************************
 * Packet:  ODV3_READ_OBJECT_REQ/ODV3_READ_OBJECT_CNF
 * Packet:  ODV3_READ_OBJECT_IND/ODV3_READ_OBJECT_RES
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request/indication, otherwise it is considered an abort.
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 */

/* request/indication packet */
typedef __PACKED_PRE struct ODV3_READ_OBJECT_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint16_t                                                usMaxSegLength;     /* max seg length in bytes or 0 for field not used */
} __PACKED_POST ODV3_READ_OBJECT_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_READ_OBJECT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_OBJECT_REQ_DATA_T                             tData;
} __PACKED_POST ODV3_READ_OBJECT_REQ_T;

typedef ODV3_READ_OBJECT_REQ_DATA_T ODV3_READ_OBJECT_IND_DATA_T;
typedef ODV3_READ_OBJECT_REQ_T ODV3_READ_OBJECT_IND_T;


/* response/confirmation packet */
typedef __PACKED_PRE struct ODV3_READ_OBJECT_CNF_DATA_Ttag
{
  /* unfragmentable part, part of every fragment */
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint16_t                                                usMaxSegLength;     /* max seg length in bytes or 0 for field not used */
  uint32_t                                                ulTotalDataBytes;   /* needed for fragmentation support */

  /* fragmentable part */
  uint8_t                                                 abData[1024];
} __PACKED_POST ODV3_READ_OBJECT_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_READ_OBJECT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_OBJECT_CNF_DATA_T                             tData;
} __PACKED_POST ODV3_READ_OBJECT_CNF_T;

typedef ODV3_READ_OBJECT_CNF_DATA_T ODV3_READ_OBJECT_RES_DATA_T;
typedef ODV3_READ_OBJECT_CNF_T ODV3_READ_OBJECT_RES_T;


/* packet union */
typedef union ODV3_READ_OBJECT_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_OBJECT_REQ_T                                  tReq;
  ODV3_READ_OBJECT_IND_T                                  tInd;
  ODV3_READ_OBJECT_RES_T                                  tRes;
  ODV3_READ_OBJECT_CNF_T                                  tCnf;
} ODV3_READ_OBJECT_PCK_T;


/******************************************************************************
 * Packet:  ODV3_READ_OBJECT_NO_IND_REQ/ODV3_READ_OBJECT_NO_IND_CNF
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * This service does not trigger indication and is therefore only useful on objects that exists locally and do not use virtual mode
 *
 * ulSta must be TLR_S_OK on request, otherwise it is considered an abort.
 *
 * Remarks: this request must be identical in structure to ODV3_READ_OBJECT_REQ
 */

/* request packet */
typedef ODV3_READ_OBJECT_REQ_DATA_T ODV3_READ_OBJECT_NO_IND_REQ_DATA_T;
typedef ODV3_READ_OBJECT_REQ_T ODV3_READ_OBJECT_NO_IND_REQ_T;

/* confirmation packet */
typedef ODV3_READ_OBJECT_CNF_DATA_T ODV3_READ_OBJECT_NO_IND_CNF_DATA_T;
typedef ODV3_READ_OBJECT_CNF_T ODV3_READ_OBJECT_NO_IND_CNF_T;


/* packet union */
typedef union ODV3_READ_OBJECT_NO_IND_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_OBJECT_NO_IND_REQ_T                           tReq;
  ODV3_READ_OBJECT_NO_IND_CNF_T                           tCnf;
} ODV3_READ_OBJECT_NO_IND_PCK_T;


/******************************************************************************
 * Packet:  ODV3_WRITE_OBJECT_REQ/ODV3_WRITE_OBJECT_CNF
 * Packet:  ODV3_WRITE_OBJECT_IND/ODV3_WRITE_OBJECT_RES
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request/indication, otherwise it is considered an abort.
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 *
 */

/* request/indication packet */
typedef __PACKED_PRE struct ODV3_WRITE_OBJECT_REQ_DATA_Ttag
{
  /* unfragmentable part, part of every fragment */
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  /* needed for fragmentation support */
  uint32_t                                                ulTotalDataBytes;
  /* used on indication to signal that the receiver is implicitly receiveing the ODV3_WRITE_OBJECT_VALIDATED_IND
   * so, it will not get an indication of that type anymore.
   */
  uint32_t                                                fValidationIsImplicit;
  /* fragmentable part */
  uint8_t                                                 abData[1024];
} __PACKED_POST ODV3_WRITE_OBJECT_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_WRITE_OBJECT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_OBJECT_REQ_DATA_T                            tData;
} __PACKED_POST ODV3_WRITE_OBJECT_REQ_T;

typedef ODV3_WRITE_OBJECT_REQ_DATA_T ODV3_WRITE_OBJECT_IND_DATA_T;
typedef ODV3_WRITE_OBJECT_REQ_T ODV3_WRITE_OBJECT_IND_T;

/* special value for ulTotalDataBytes */
#define ODV3_WRITE_OBJECT_REQ_TOTAL_DATA_BYTES_NOT_SPECIFIED      0xFFFFFFFF

#define ODV3_WRITE_OBJECT_IND_TOTAL_DATA_BYTES_NOT_SPECIFIED      0xFFFFFFFF

/* response/confirmation packet */
typedef __PACKED_PRE struct ODV3_WRITE_OBJECT_CNF_DATA_Ttag
{
  /* unfragmentable part, part of every fragment */
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_WRITE_OBJECT_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_WRITE_OBJECT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_OBJECT_CNF_DATA_T                            tData;
} __PACKED_POST ODV3_WRITE_OBJECT_CNF_T;

typedef ODV3_WRITE_OBJECT_CNF_DATA_T ODV3_WRITE_OBJECT_RES_DATA_T;
typedef ODV3_WRITE_OBJECT_CNF_T ODV3_WRITE_OBJECT_RES_T;


/* packet union */
typedef union ODV3_WRITE_OBJECT_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_OBJECT_REQ_T                                 tReq;
  ODV3_WRITE_OBJECT_IND_T                                 tInd;
  ODV3_WRITE_OBJECT_RES_T                                 tRes;
  ODV3_WRITE_OBJECT_CNF_T                                 tCnf;
} ODV3_WRITE_OBJECT_PCK_T;


/******************************************************************************
 * Packet:  ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_IND/ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_RES
 *
 * ulSta must be TLR_S_OK on request/indication, otherwise it is considered an abort.
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 *
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_IND_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint8_t                                                 fSuccessful;
} __PACKED_POST ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_IND_DATA_T;

typedef __PACKED_PRE struct ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_IND_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_IND_DATA_T        tData;
} __PACKED_POST ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_IND_T;

/* confirmation packet */
typedef __PACKED_PRE struct ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_RES_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_RES_DATA_T;

typedef __PACKED_PRE struct ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_RES_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_RES_DATA_T        tData;
} __PACKED_POST ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_RES_T;


/* packet union */
typedef union ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_IND_T             tInd;
  ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_RES_T             tRes;
} ODV3_WRITE_OBJECT_VALIDATION_COMPLETE_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_OBJECT_ACCESS_INFO_REQ/ODV3_GET_OBJECT_ACCESS_INFO_CNF
 * Packet:  ODV3_GET_OBJECT_ACCESS_INFO_IND/ODV3_GET_OBJECT_ACCESS_INFO_RES
 *
 * ulSta must be TLR_S_OK on request/indication
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 */

/* request/indication packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_ACCESS_INFO_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex;
  uint8_t                                                 bNumSubIndex; /* 0 ~ 256 entries */
} __PACKED_POST ODV3_GET_OBJECT_ACCESS_INFO_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_ACCESS_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_ACCESS_INFO_REQ_DATA_T                  tData;
} __PACKED_POST ODV3_GET_OBJECT_ACCESS_INFO_REQ_T;

typedef ODV3_GET_OBJECT_ACCESS_INFO_REQ_DATA_T ODV3_GET_OBJECT_ACCESS_INFO_IND_DATA_T;
typedef ODV3_GET_OBJECT_ACCESS_INFO_REQ_T ODV3_GET_OBJECT_ACCESS_INFO_IND_T;

/* response/confirmation packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_ACCESS_INFO_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex;
  /* bNumSubIndex can be lowered by requestee if the packet cannot be transferred otherwise (i.e. DPM),
   * the requestor has to issue a follow-up request if bMaxSubIndex + 1 > bNumSubIndex + bStartSubIndex.
   */
  uint8_t                                                 bNumSubIndex;
  /* up to bNumSubIndex, the confirmation must match its request */
  uint8_t                                                 bMaxSubIndex;
  uint8_t                                                 abReserved[3];
  uint16_t                                                ausAccessRights[256];  /* actual amount of elements controlled by MAX(bNumSubIndex) */
} __PACKED_POST ODV3_GET_OBJECT_ACCESS_INFO_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_ACCESS_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_ACCESS_INFO_CNF_DATA_T                  tData;
} __PACKED_POST ODV3_GET_OBJECT_ACCESS_INFO_CNF_T;

#define ODV3_GET_OBJECT_ACCESS_INFO_RES_MIN_DATA_SIZE     (1 * sizeof(TLR_UINT16) + 4 * sizeof(TLR_UINT8))

typedef ODV3_GET_OBJECT_ACCESS_INFO_CNF_DATA_T ODV3_GET_OBJECT_ACCESS_INFO_RES_DATA_T;
typedef ODV3_GET_OBJECT_ACCESS_INFO_CNF_T ODV3_GET_OBJECT_ACCESS_INFO_RES_T;

/* packet union */
typedef union ODV3_GET_OBJECT_ACCESS_INFO_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_ACCESS_INFO_REQ_T                       tReq;
  ODV3_GET_OBJECT_ACCESS_INFO_IND_T                       tInd;
  ODV3_GET_OBJECT_ACCESS_INFO_RES_T                       tRes;
  ODV3_GET_OBJECT_ACCESS_INFO_CNF_T                       tCnf;
} ODV3_GET_OBJECT_ACCESS_INFO_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_OBJECT_SIZE_REQ/ODV3_GET_OBJECT_SIZE_CNF
 * Packet:  ODV3_GET_OBJECT_SIZE_IND/ODV3_GET_OBJECT_SIZE_RES
 *
 * ulSta must be TLR_S_OK on request/indication
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 */

/* request/indication packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_SIZE_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex;
  uint8_t                                                 bNumSubIndex;
} __PACKED_POST ODV3_GET_OBJECT_SIZE_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_SIZE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_SIZE_REQ_DATA_T                         tData;
} __PACKED_POST ODV3_GET_OBJECT_SIZE_REQ_T;

typedef ODV3_GET_OBJECT_SIZE_REQ_DATA_T ODV3_GET_OBJECT_SIZE_IND_DATA_T;
typedef ODV3_GET_OBJECT_SIZE_REQ_T ODV3_GET_OBJECT_SIZE_IND_T;


/* response/confirmation packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_SIZE_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex;
  /* bNumSubIndex can be lowered by requestee if the packet cannot be transferred otherwise (i.e. DPM),
   * the requestor has to issue a follow-up request then.
   *
   * If there are no more subobjects, the value of bNumSubIndex has to be 0.
   */
  uint8_t                                                 bNumSubIndex;
  uint32_t                                                aulSubObjDataBitSize[256];    /* only actual size defined by bNumSubIndex needs to be used */
} __PACKED_POST ODV3_GET_OBJECT_SIZE_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_SIZE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_SIZE_CNF_DATA_T                         tData;
} __PACKED_POST ODV3_GET_OBJECT_SIZE_CNF_T;

typedef ODV3_GET_OBJECT_SIZE_CNF_DATA_T ODV3_GET_OBJECT_SIZE_RES_DATA_T;
typedef ODV3_GET_OBJECT_SIZE_CNF_T ODV3_GET_OBJECT_SIZE_RES_T;

#define ODV3_GET_OBJECT_SIZE_RES_DATA_MIN_REQ_SIZE        (sizeof(TLR_UINT16) + 2 * sizeof(TLR_UINT8))
#define ODV3_GET_OBJECT_SIZE_CNF_DATA_MIN_REQ_SIZE        (sizeof(TLR_UINT16) + 2 * sizeof(TLR_UINT8))


/* packet union */
typedef union ODV3_GET_OBJECT_SIZE_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_SIZE_REQ_T                              tReq;
  ODV3_GET_OBJECT_SIZE_IND_T                              tInd;
  ODV3_GET_OBJECT_SIZE_RES_T                              tRes;
  ODV3_GET_OBJECT_SIZE_CNF_T                              tCnf;
} ODV3_GET_OBJECT_SIZE_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_OBJECT_LIST_REQ/ODV3_GET_OBJECT_LIST_CNF
 * Packet:  ODV3_GET_OBJECT_LIST_IND/ODV3_GET_OBJECT_LIST_RES
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request/indication, otherwise it is considered an abort.
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 */

/* request/indication packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_LIST_REQ_DATA_Ttag
{
  uint16_t                                                usObjAccessMask;
  uint16_t                                                usObjAccessCompare;
} __PACKED_POST ODV3_GET_OBJECT_LIST_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_LIST_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_LIST_REQ_DATA_T                         tData;
} __PACKED_POST ODV3_GET_OBJECT_LIST_REQ_T;

typedef ODV3_GET_OBJECT_LIST_REQ_DATA_T ODV3_GET_OBJECT_LIST_IND_DATA_T;
typedef ODV3_GET_OBJECT_LIST_REQ_T ODV3_GET_OBJECT_LIST_IND_T;


/* response/confirmation packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_LIST_CNF_DATA_Ttag
{
  /* unfragmentable part */
  uint16_t                                                usObjAccessMask;
  uint16_t                                                usObjAccessCompare;
  uint32_t                                                ulTotalDataBytes;

  /* fragmentable part */
  uint16_t                                                ausIndexes[512];
} __PACKED_POST ODV3_GET_OBJECT_LIST_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_LIST_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_LIST_CNF_DATA_T                         tData;
} __PACKED_POST ODV3_GET_OBJECT_LIST_CNF_T;

typedef ODV3_GET_OBJECT_LIST_CNF_DATA_T ODV3_GET_OBJECT_LIST_RES_DATA_T;
typedef ODV3_GET_OBJECT_LIST_CNF_T ODV3_GET_OBJECT_LIST_RES_T;


/* packet union */
typedef union ODV3_GET_OBJECT_LIST_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_LIST_REQ_T                              tReq;
  ODV3_GET_OBJECT_LIST_IND_T                              tInd;
  ODV3_GET_OBJECT_LIST_RES_T                              tRes;
  ODV3_GET_OBJECT_LIST_CNF_T                              tCnf;
} ODV3_GET_OBJECT_LIST_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_OBJECT_COUNT_REQ/ODV3_GET_OBJECT_COUNT_CNF
 * Packet:  ODV3_GET_OBJECT_COUNT_IND/ODV3_GET_OBJECT_COUNT_RES
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request/indication, otherwise it is considered an abort.
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 */

#define ODV3_GET_OBJECT_COUNT_MAX_ENTRIES     20

/* request/indication packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_COUNT_REQ_DATA_ENTRY_Ttag
{
  uint16_t                                                usObjAccessMask;
  uint16_t                                                usObjAccessCompare;
} __PACKED_POST ODV3_GET_OBJECT_COUNT_REQ_DATA_ENTRY_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_COUNT_REQ_DATA_Ttag
{
  ODV3_GET_OBJECT_COUNT_REQ_DATA_ENTRY_T                  atEntries[20];
} __PACKED_POST ODV3_GET_OBJECT_COUNT_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_COUNT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_COUNT_REQ_DATA_T                        tData;
} __PACKED_POST ODV3_GET_OBJECT_COUNT_REQ_T;

typedef ODV3_GET_OBJECT_COUNT_REQ_DATA_ENTRY_T ODV3_GET_OBJECT_COUNT_IND_DATA_ENTRY_T;
typedef ODV3_GET_OBJECT_COUNT_REQ_DATA_T ODV3_GET_OBJECT_COUNT_IND_DATA_T;
typedef ODV3_GET_OBJECT_COUNT_REQ_T ODV3_GET_OBJECT_COUNT_IND_T;


/* response/confirmation packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_COUNT_CNF_DATA_Ttag
{
  uint16_t                                                ausCounts[20];
} __PACKED_POST ODV3_GET_OBJECT_COUNT_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_COUNT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_COUNT_CNF_DATA_T                        tData;
} __PACKED_POST ODV3_GET_OBJECT_COUNT_CNF_T;

typedef ODV3_GET_OBJECT_COUNT_CNF_DATA_T ODV3_GET_OBJECT_COUNT_RES_DATA_T;
typedef ODV3_GET_OBJECT_COUNT_CNF_T ODV3_GET_OBJECT_COUNT_RES_T;


/* packet union */
typedef union ODV3_GET_OBJECT_COUNT_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_COUNT_REQ_T                             tReq;
  ODV3_GET_OBJECT_COUNT_IND_T                             tInd;
  ODV3_GET_OBJECT_COUNT_RES_T                             tRes;
  ODV3_GET_OBJECT_COUNT_CNF_T                             tCnf;
} ODV3_GET_OBJECT_COUNT_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_OBJECT_INFO_REQ/ODV3_GET_OBJECT_INFO_CNF
 * Packet:  ODV3_GET_OBJECT_INFO_IND/ODV3_GET_OBJECT_INFO_RES
 *
 * Description: Determine information about object
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request/indication, otherwise it is considered an abort.
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 */

/* request/indication packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_INFO_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_GET_OBJECT_INFO_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_INFO_REQ_DATA_T                         tData;
} __PACKED_POST ODV3_GET_OBJECT_INFO_REQ_T;

typedef ODV3_GET_OBJECT_INFO_REQ_DATA_T ODV3_GET_OBJECT_INFO_IND_DATA_T;
typedef ODV3_GET_OBJECT_INFO_REQ_T ODV3_GET_OBJECT_INFO_IND_T;


/* confirmation/response packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_INFO_CNF_DATA_Ttag
{
  /* unfragmentable part */
  uint16_t                                                usIndex;
  uint16_t                                                usDatatype;
  uint16_t                                                usAccessFlags;
  uint8_t                                                 bMaxNumOfSubObjs;
  uint8_t                                                 bObjectCode;
  uint32_t                                                ulTotalDataBytes;   /* needed for fragmentation support */
  /* fragmentable part */
  uint8_t                                                 abName[1024];
} __PACKED_POST ODV3_GET_OBJECT_INFO_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_INFO_CNF_DATA_T                         tData;
} __PACKED_POST ODV3_GET_OBJECT_INFO_CNF_T;

typedef ODV3_GET_OBJECT_INFO_CNF_DATA_T ODV3_GET_OBJECT_INFO_RES_DATA_T;
typedef ODV3_GET_OBJECT_INFO_CNF_T ODV3_GET_OBJECT_INFO_RES_T;


/* packet union */
typedef union ODV3_GET_OBJECT_INFO_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_INFO_REQ_T                              tReq;
  ODV3_GET_OBJECT_INFO_IND_T                              tInd;
  ODV3_GET_OBJECT_INFO_RES_T                              tRes;
  ODV3_GET_OBJECT_INFO_CNF_T                              tCnf;
} ODV3_GET_OBJECT_INFO_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_SUBOBJECT_INFO_REQ/ODV3_GET_SUBOBJECT_INFO_CNF
 * Packet:  ODV3_GET_SUBOBJECT_INFO_IND/ODV3_GET_SUBOBJECT_INFO_RES
 *
 * Description: Determine information about subobject
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request/indication, otherwise it is considered an abort.
 *
 * indication receivers have to check ulSta whether, it is an abort on a fragmentation.
 */

/* request/indication packet */
typedef __PACKED_PRE struct ODV3_GET_SUBOBJECT_INFO_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint8_t                                                 bRequestedValueInfo;
} __PACKED_POST ODV3_GET_SUBOBJECT_INFO_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_SUBOBJECT_INFO_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_SUBOBJECT_INFO_REQ_DATA_T                      tData;
} __PACKED_POST ODV3_GET_SUBOBJECT_INFO_REQ_T;

typedef ODV3_GET_SUBOBJECT_INFO_REQ_DATA_T ODV3_GET_SUBOBJECT_INFO_IND_DATA_T;
typedef ODV3_GET_SUBOBJECT_INFO_REQ_T ODV3_GET_SUBOBJECT_INFO_IND_T;

#define ODV3_GET_SUBOBJECT_INFO_REQ_VALUE_INFO_NAME           0x01
#define ODV3_GET_SUBOBJECT_INFO_REQ_VALUE_INFO_ECAT_UNIT      0x10
#define ODV3_GET_SUBOBJECT_INFO_REQ_VALUE_INFO_DEFAULT_VALUE  0x20
#define ODV3_GET_SUBOBJECT_INFO_REQ_VALUE_INFO_MINIMUM_VALUE  0x40  /* always uses max length */
#define ODV3_GET_SUBOBJECT_INFO_REQ_VALUE_INFO_MAXIMUM_VALUE  0x80  /* always uses max length */



/* confirmation/response packet */
typedef __PACKED_PRE struct ODV3_GET_SUBOBJECT_INFO_CNF_DATA_Ttag
{
  /* unfragmentable part */
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint8_t                                                 bValueInfo;
  uint32_t                                                ulTotalDataBytes;   /* needed for fragmentation support */
  uint16_t                                                usAccessRights;
  uint16_t                                                usDatatype;
  uint32_t                                                ulDataBitLen;
  uint16_t                                                usFieldLen;
  /* fragmentable part */
  uint8_t                                                 abData[1024];
  /* order of fragmentable part is Unit Type, Default Value, Minimum Value, Maximum Value, Name */
} __PACKED_POST ODV3_GET_SUBOBJECT_INFO_CNF_DATA_T;

#define ODV3_GET_SUBOBJECT_INFO_CNF_VALUE_INFO_NAME           0x01
#define ODV3_GET_SUBOBJECT_INFO_CNF_VALUE_INFO_ECAT_UNIT      0x10
#define ODV3_GET_SUBOBJECT_INFO_CNF_VALUE_INFO_DEFAULT_VALUE  0x20
#define ODV3_GET_SUBOBJECT_INFO_CNF_VALUE_INFO_MINIMUM_VALUE  0x40  /* always uses max length */
#define ODV3_GET_SUBOBJECT_INFO_CNF_VALUE_INFO_MAXIMUM_VALUE  0x80  /* always uses max length */

typedef __PACKED_PRE struct ODV3_GET_SUBOBJECT_INFO_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_SUBOBJECT_INFO_CNF_DATA_T                      tData;
} __PACKED_POST ODV3_GET_SUBOBJECT_INFO_CNF_T;

typedef ODV3_GET_SUBOBJECT_INFO_CNF_DATA_T ODV3_GET_SUBOBJECT_INFO_RES_DATA_T;
typedef ODV3_GET_SUBOBJECT_INFO_CNF_T ODV3_GET_SUBOBJECT_INFO_RES_T;


/* packet union */
typedef union ODV3_GET_SUBOBJECT_INFO_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_SUBOBJECT_INFO_REQ_T                           tReq;
  ODV3_GET_SUBOBJECT_INFO_IND_T                           tInd;
  ODV3_GET_SUBOBJECT_INFO_RES_T                           tRes;
  ODV3_GET_SUBOBJECT_INFO_CNF_T                           tCnf;
} ODV3_GET_SUBOBJECT_INFO_PCK_T;


/******************************************************************************
 * Packet:  ODV3_REQUEST_ABORTED_IND/ODV3_REQUEST_ABORTED_RES
 *
 * ulSta contains the reason for abort
 *
 * This indication is sent to the requestor if no active Request packet is contained within fragmentation.
 *
 * The following relationship between ulSrcId/ulDestId exists:
 * ODV3_READ_OBJECT_REQ           ODV3_REQUEST_ABORTED_IND
 * ulSrcId                        ulDestId
 * ulDestId                       ulSrcId
 *
 * ODV3_READ_OBJECT_REQ is a placeholder for all fragmented request services here since
 * the same rules applies to all those requests.
 */

/* indication packet */
typedef __PACKED_PRE struct ODV3_REQUEST_ABORTED_IND_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_REQUEST_ABORTED_IND_T;


/* response packet */
typedef __PACKED_PRE struct ODV3_REQUEST_ABORTED_RES_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_REQUEST_ABORTED_RES_T;

/* packet union */
typedef __PACKED_PRE union ODV3_REQUEST_ABORTED_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REQUEST_ABORTED_IND_T                              tInd;
  ODV3_REQUEST_ABORTED_RES_T                              tRes;
} __PACKED_POST ODV3_REQUEST_ABORTED_PCK_T;


/******************************************************************************
 * Packet:  ODV3_ABORT_REQUEST_REQ/ODV3_ABORT_REQUEST_CNF
 *
 * ulSta contains the reason for abort
 *
 * This indication is sent to the requestor if no active Request packet is contained within fragmentation.
 *
 * The following relationship between ulSrcId/ulDestId exists:
 * ODV3_READ_OBJECT_REQ           ODV3_ABORT_REQUEST_REQ
 * ulSrcId                        ulSrcId
 * ulDestId                       ulDestId
 *
 * ODV3_READ_OBJECT_REQ is a placeholder for all fragmented request services here since
 * the same rules applies to all those requests.
 */

/* indication packet */
typedef __PACKED_PRE struct ODV3_ABORT_REQUEST_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_ABORT_REQUEST_REQ_T;


/* response packet */
typedef __PACKED_PRE struct ODV3_ABORT_REQUEST_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_ABORT_REQUEST_CNF_T;

/* packet union */
typedef __PACKED_PRE union ODV3_ABORT_REQUEST_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_ABORT_REQUEST_REQ_T                                tInd;
  ODV3_ABORT_REQUEST_CNF_T                                tRes;
} __PACKED_POST ODV3_ABORT_REQUEST_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_OBJECT_PROPERTIES_IND/ODV3_GET_OBJECT_PROPERTIES_RES
 *
 */

/* indication packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_PROPERTIES_IND_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_GET_OBJECT_PROPERTIES_IND_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_PROPERTIES_IND_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_PROPERTIES_IND_DATA_T                   tData;
} __PACKED_POST ODV3_GET_OBJECT_PROPERTIES_IND_T;


/* response packet */
typedef __PACKED_PRE struct ODV3_GET_OBJECT_PROPERTIES_RES_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint32_t                                                ulFlags;
} __PACKED_POST ODV3_GET_OBJECT_PROPERTIES_RES_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_OBJECT_PROPERTIES_RES_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_PROPERTIES_RES_DATA_T                   tData;
} __PACKED_POST ODV3_GET_OBJECT_PROPERTIES_RES_T;

/* packet union */
typedef __PACKED_PRE union ODV3_GET_OBJECT_PROPERTIES_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_OBJECT_PROPERTIES_IND_T                        tInd;
  ODV3_GET_OBJECT_PROPERTIES_RES_T                        tRes;
} __PACKED_POST ODV3_GET_OBJECT_PROPERTIES_PCK_T;


/******************************************************************************
 * Packet:  ODV3_REGISTER_OBJECT_NOTIFY_REQ/ODV3_REGISTER_OBJECT_NOTIFY_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_REGISTER_OBJECT_NOTIFY_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bIndicationFlags;
} __PACKED_POST ODV3_REGISTER_OBJECT_NOTIFY_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_REGISTER_OBJECT_NOTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REGISTER_OBJECT_NOTIFY_REQ_DATA_T                  tData;
} __PACKED_POST ODV3_REGISTER_OBJECT_NOTIFY_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_REGISTER_OBJECT_NOTIFY_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_REGISTER_OBJECT_NOTIFY_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_REGISTER_OBJECT_NOTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REGISTER_OBJECT_NOTIFY_CNF_DATA_T                  tData;
} __PACKED_POST ODV3_REGISTER_OBJECT_NOTIFY_CNF_T;


/* packet union */
typedef union ODV3_REGISTER_OBJECT_NOTIFY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REGISTER_OBJECT_NOTIFY_REQ_T                       tReq;
  ODV3_REGISTER_OBJECT_NOTIFY_CNF_T                       tCnf;
} ODV3_REGISTER_OBJECT_NOTIFY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_UNREGISTER_OBJECT_NOTIFY_REQ/ODV3_UNREGISTER_OBJECT_NOTIFY_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_UNREGISTER_OBJECT_NOTIFY_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_UNREGISTER_OBJECT_NOTIFY_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_UNREGISTER_OBJECT_NOTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNREGISTER_OBJECT_NOTIFY_REQ_DATA_T                tData;
} __PACKED_POST ODV3_UNREGISTER_OBJECT_NOTIFY_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_UNREGISTER_OBJECT_NOTIFY_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_UNREGISTER_OBJECT_NOTIFY_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_UNREGISTER_OBJECT_NOTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNREGISTER_OBJECT_NOTIFY_CNF_DATA_T                tData;
} __PACKED_POST ODV3_UNREGISTER_OBJECT_NOTIFY_CNF_T;


/* packet union */
typedef union ODV3_UNREGISTER_OBJECT_NOTIFY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNREGISTER_OBJECT_NOTIFY_REQ_T                     tReq;
  ODV3_UNREGISTER_OBJECT_NOTIFY_CNF_T                     tCnf;
} ODV3_UNREGISTER_OBJECT_NOTIFY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_REGISTER_SUBOBJECT_NOTIFY_REQ/ODV3_REGISTER_SUBOBJECT_NOTIFY_CNF
 *
 * ulSta must be TLR_S_OK on request
 *
 * on simple variables use ODV3_REGISTER_OBJECT_NOTIFY_REQ
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_REGISTER_SUBOBJECT_NOTIFY_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint8_t                                                 bIndicationFlags;
} __PACKED_POST ODV3_REGISTER_SUBOBJECT_NOTIFY_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_REGISTER_SUBOBJECT_NOTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REGISTER_SUBOBJECT_NOTIFY_REQ_DATA_T               tData;
} __PACKED_POST ODV3_REGISTER_SUBOBJECT_NOTIFY_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_REGISTER_SUBOBJECT_NOTIFY_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_REGISTER_SUBOBJECT_NOTIFY_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_REGISTER_SUBOBJECT_NOTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REGISTER_SUBOBJECT_NOTIFY_CNF_DATA_T               tData;
} __PACKED_POST ODV3_REGISTER_SUBOBJECT_NOTIFY_CNF_T;


/* packet union */
typedef union ODV3_REGISTER_SUBOBJECT_NOTIFY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REGISTER_SUBOBJECT_NOTIFY_REQ_T                    tReq;
  ODV3_REGISTER_SUBOBJECT_NOTIFY_CNF_T                    tCnf;
} ODV3_REGISTER_SUBOBJECT_NOTIFY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_UNREGISTER_SUBOBJECT_NOTIFY_REQ/ODV3_UNREGISTER_SUBOBJECT_NOTIFY_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_UNREGISTER_SUBOBJECT_NOTIFY_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_UNREGISTER_SUBOBJECT_NOTIFY_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_UNREGISTER_SUBOBJECT_NOTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNREGISTER_SUBOBJECT_NOTIFY_REQ_DATA_T             tData;
} __PACKED_POST ODV3_UNREGISTER_SUBOBJECT_NOTIFY_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_UNREGISTER_SUBOBJECT_NOTIFY_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_UNREGISTER_SUBOBJECT_NOTIFY_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_UNREGISTER_SUBOBJECT_NOTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNREGISTER_SUBOBJECT_NOTIFY_CNF_DATA_T             tData;
} __PACKED_POST ODV3_UNREGISTER_SUBOBJECT_NOTIFY_CNF_T;


/* packet union */
typedef union ODV3_UNREGISTER_SUBOBJECT_NOTIFY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNREGISTER_SUBOBJECT_NOTIFY_REQ_T                  tReq;
  ODV3_UNREGISTER_SUBOBJECT_NOTIFY_CNF_T                  tCnf;
} ODV3_UNREGISTER_SUBOBJECT_NOTIFY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_REGISTER_UNDEFINED_NOTIFY_REQ/ODV3_REGISTER_UNDEFINED_NOTIFY_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_REGISTER_UNDEFINED_NOTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_REGISTER_UNDEFINED_NOTIFY_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_REGISTER_UNDEFINED_NOTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_REGISTER_UNDEFINED_NOTIFY_CNF_T;


/* packet union */
typedef union ODV3_REGISTER_UNDEFINED_NOTIFY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REGISTER_UNDEFINED_NOTIFY_REQ_T                    tReq;
  ODV3_REGISTER_UNDEFINED_NOTIFY_CNF_T                    tCnf;
} ODV3_REGISTER_UNDEFINED_NOTIFY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_UNREGISTER_UNDEFINED_NOTIFY_REQ/ODV3_UNREGISTER_UNDEFINED_NOTIFY_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_UNREGISTER_UNDEFINED_NOTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_UNREGISTER_UNDEFINED_NOTIFY_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_UNREGISTER_UNDEFINED_NOTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_UNREGISTER_UNDEFINED_NOTIFY_CNF_T;


/* packet union */
typedef union ODV3_UNREGISTER_UNDEFINED_NOTIFY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNREGISTER_UNDEFINED_NOTIFY_REQ_T                  tReq;
  ODV3_UNREGISTER_UNDEFINED_NOTIFY_CNF_T                  tCnf;
} ODV3_UNREGISTER_UNDEFINED_NOTIFY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_REGISTER_OBJINFO_NOTIFY_REQ/ODV3_REGISTER_OBJINFO_NOTIFY_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_REGISTER_OBJINFO_NOTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_REGISTER_OBJINFO_NOTIFY_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_REGISTER_OBJINFO_NOTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_REGISTER_OBJINFO_NOTIFY_CNF_T;


/* packet union */
typedef union ODV3_REGISTER_OBJINFO_NOTIFY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_REGISTER_OBJINFO_NOTIFY_REQ_T                      tReq;
  ODV3_REGISTER_OBJINFO_NOTIFY_CNF_T                      tCnf;
} ODV3_REGISTER_OBJINFO_NOTIFY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_UNREGISTER_OBJINFO_NOTIFY_REQ/ODV3_UNREGISTER_OBJINFO_NOTIFY_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_UNREGISTER_OBJINFO_NOTIFY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_UNREGISTER_OBJINFO_NOTIFY_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_UNREGISTER_OBJINFO_NOTIFY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_UNREGISTER_OBJINFO_NOTIFY_CNF_T;


/* packet union */
typedef union ODV3_UNREGISTER_OBJINFO_NOTIFY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNREGISTER_OBJINFO_NOTIFY_REQ_T                    tReq;
  ODV3_UNREGISTER_OBJINFO_NOTIFY_CNF_T                    tCnf;
} ODV3_UNREGISTER_OBJINFO_NOTIFY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_LOCK_OBJECT_DELETION_REQ/ODV3_LOCK_OBJECT_DELETION_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_LOCK_OBJECT_DELETION_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_LOCK_OBJECT_DELETION_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_LOCK_OBJECT_DELETION_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_LOCK_OBJECT_DELETION_CNF_T;


/* packet union */
typedef union ODV3_LOCK_OBJECT_DELETION_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_LOCK_OBJECT_DELETION_REQ_T                         tReq;
  ODV3_LOCK_OBJECT_DELETION_CNF_T                         tCnf;
} ODV3_LOCK_OBJECT_DELETION_PCK_T;


/******************************************************************************
 * Packet:  ODV3_UNLOCK_OBJECT_DELETION_REQ/ODV3_UNLOCK_OBJECT_DELETION_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_UNLOCK_OBJECT_DELETION_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_UNLOCK_OBJECT_DELETION_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_UNLOCK_OBJECT_DELETION_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_UNLOCK_OBJECT_DELETION_CNF_T;


/* packet union */
typedef union ODV3_UNLOCK_OBJECT_DELETION_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_UNLOCK_OBJECT_DELETION_REQ_T                       tReq;
  ODV3_UNLOCK_OBJECT_DELETION_CNF_T                       tCnf;
} ODV3_UNLOCK_OBJECT_DELETION_PCK_T;


/******************************************************************************
 * Packet:  ODV3_WRITE_ALL_BY_INDEX_REQ/ODV3_WRITE_ALL_BY_INDEX_CNF
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request, otherwise it is considered an abort.
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_WRITE_ALL_BY_INDEX_REQ_DATA_Ttag
{
  /* unfragmentable part */
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex; /* 0 or 1 valid */
  uint8_t                                                 bMultipleParaAccessFlags; /* access flags for multiple parameter access */
  uint32_t                                                ulTotalDataBytes;
  /* fragmentable part */
  uint8_t                                                 abData[1024];
} __PACKED_POST ODV3_WRITE_ALL_BY_INDEX_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_WRITE_ALL_BY_INDEX_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_ALL_BY_INDEX_REQ_DATA_T                      tData;
} __PACKED_POST ODV3_WRITE_ALL_BY_INDEX_REQ_T;

/* special value for ulTotalDataBytes */
#define ODV3_WRITE_ALL_BY_INDEX_REQ_TOTAL_DATA_BYTES_NOT_SPECIFIED      0xFFFFFFFF


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_WRITE_ALL_BY_INDEX_CNF_DATA_Ttag
{
  /* unfragmentable part */
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex; /* 0 or 1 valid */
} __PACKED_POST ODV3_WRITE_ALL_BY_INDEX_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_WRITE_ALL_BY_INDEX_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_ALL_BY_INDEX_CNF_DATA_T                      tData;
} __PACKED_POST ODV3_WRITE_ALL_BY_INDEX_CNF_T;


/* packet union */
typedef union ODV3_WRITE_ALL_BY_INDEX_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_ALL_BY_INDEX_REQ_T                           tReq;
  ODV3_WRITE_ALL_BY_INDEX_CNF_T                           tCnf;
} ODV3_WRITE_ALL_BY_INDEX_PCK_T;


/******************************************************************************
 * Packet:  ODV3_READ_ALL_BY_INDEX_REQ/ODV3_READ_ALL_BY_INDEX_CNF
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * ulSta must be TLR_S_OK on request, otherwise it is considered an abort.
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_READ_ALL_BY_INDEX_REQ_DATA_Ttag
{
  /* unfragmentable part */
  /* first five bytes must be identical to ODV3_READ_OBJECT_REQ_DATA_T */
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex; /* 0 or 1 valid */
  uint8_t                                                 bMultipleParaAccessFlags; /* access flags for multiple parameter access */
  uint16_t                                                usMaxSegLength;     /* max seg length in bytes or 0 for field not used */
} __PACKED_POST ODV3_READ_ALL_BY_INDEX_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_READ_ALL_BY_INDEX_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_ALL_BY_INDEX_REQ_DATA_T                       tData;
} __PACKED_POST ODV3_READ_ALL_BY_INDEX_REQ_T;


/* request packet (when enabling access mask check) */
typedef __PACKED_PRE struct ODV3_READ_ALL_BY_INDEX_ACCESS_MASK_REQ_DATA_Ttag
{
  /* unfragmentable part */
  /* first five bytes must be identical to ODV3_READ_OBJECT_REQ_DATA_T */
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex; /* 0 or 1 valid */
  uint8_t                                                 bMultipleParaAccessFlags; /* access flags for multiple parameter access */
  uint16_t                                                usMaxSegLength;     /* max seg length in bytes or 0 for field not used */
  uint16_t                                                usAccessMask;
} __PACKED_POST ODV3_READ_ALL_BY_INDEX_ACCESS_MASK_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_READ_ALL_BY_INDEX_ACCESS_MASK_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_ALL_BY_INDEX_ACCESS_MASK_REQ_DATA_T           tData;
} __PACKED_POST ODV3_READ_ALL_BY_INDEX_ACCESS_MASK_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_READ_ALL_BY_INDEX_CNF_DATA_Ttag
{
  /* unfragmentable part (must be identical to ODV3_READ_OBJECT_CNF_DATA_T) */
  uint16_t                                                usIndex;
  uint8_t                                                 bStartSubIndex; /* 0 or 1 valid */
  uint32_t                                                ulTotalDataBytes;

  /* fragmentable part */
  uint8_t                                                 abData[1024];
} __PACKED_POST ODV3_READ_ALL_BY_INDEX_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_READ_ALL_BY_INDEX_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_ALL_BY_INDEX_CNF_DATA_T                       tData;
} __PACKED_POST ODV3_READ_ALL_BY_INDEX_CNF_T;


/* packet union */
typedef union ODV3_READ_ALL_BY_INDEX_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_ALL_BY_INDEX_REQ_T                            tReq;
  ODV3_READ_ALL_BY_INDEX_ACCESS_MASK_REQ_T                tReqAccessMask;
  ODV3_READ_ALL_BY_INDEX_CNF_T                            tCnf;
} ODV3_READ_ALL_BY_INDEX_PCK_T;


/******************************************************************************
 * Packet:  ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ/ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * Attention! fragmenting may happen in both directions
 *
 * ulSta must be TLR_S_OK on request, otherwise it is considered an abort.
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_ENTRY_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint8_t                                                 bMultipleParaAccessFlags; /* access flags for multiple parameter access */
  uint32_t                                                ulDataByteSize;   /* if ulDataByteSize is not a multiple of 4, abData is padded to 4 byte border */
  uint8_t                                                 abData[1];        /* variable size */
} __PACKED_POST ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_ENTRY_T;

typedef __PACKED_PRE struct ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_DATA_Ttag
{
  uint32_t                                                ulTotalDataBytes;
  ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_ENTRY_T      atEntries[1];
} __PACKED_POST ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_DATA_T       tData;
} __PACKED_POST ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_ENTRY_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint32_t                                                ulAbortcode;
} __PACKED_POST ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_ENTRY_T;

typedef __PACKED_PRE struct ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_DATA_Ttag
{
  uint32_t                                                ulTotalDataBytes;
  ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_ENTRY_T      atEntries[1];
} __PACKED_POST ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_DATA_T       tData;
} __PACKED_POST ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_T;


/* packet union */
typedef union ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_REQ_T            tReq;
  ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_CNF_T            tCnf;
} ODV3_WRITE_MULTIPLE_PARAMETER_BY_INDEX_PCK_T;


/******************************************************************************
 * Packet:  ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ/ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF
 *
 * Fragmentation:
 *                            Request/Indication  Response/Confirmation
 * TLR_PACKET_SEQ_FIRST       ulDestId = 0        ulDestId = X
 * TLR_PACKET_SEQ_MIDDLE      ulDestId = X        ulDestId == X
 * TLR_PACKET_SEQ_LAST        ulDestId = X        ulDestId == X
 *
 * X is a handle to the running transfer
 *
 * Attention! fragmenting may happen in both directions
 *
 * ulSta must be TLR_S_OK on request, otherwise it is considered an abort.
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_ENTRY_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint8_t                                                 bMultipleParaAccessFlags; /* access flags for multiple parameter access */
} __PACKED_POST ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_ENTRY_T;

typedef __PACKED_PRE struct ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_DATA_Ttag
{
  uint32_t                                                ulTotalDataBytes;
  ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_ENTRY_T       atEntries[1];
} __PACKED_POST ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_DATA_T        tData;
} __PACKED_POST ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_ENTRY_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint32_t                                                ulAbortcode;      /* if != 0, ulDataByteSize = 0 */
  uint32_t                                                ulDataByteSize;   /* if ulDataByteSize is not a multiple of 4, abData is padded to 4 byte border */
  uint8_t                                                 abData[1];        /* variable size */
} __PACKED_POST ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_ENTRY_T;

typedef __PACKED_PRE struct ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_DATA_Ttag
{
  uint32_t                                                ulTotalDataBytes;
  ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_ENTRY_T       atEntries[1];
} __PACKED_POST ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_DATA_T        tData;
} __PACKED_POST ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_T;


/* packet union */
typedef union ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_REQ_T             tReq;
  ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_CNF_T             tCnf;
} ODV3_READ_MULTIPLE_PARAMETER_BY_INDEX_PCK_T;


/******************************************************************************
 * Packet:  ODV3_RESET_OBJECTS_REQ/ODV3_RESET_OBJECTS_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_RESET_OBJECTS_REQ_RANGE_ENTRIES_Ttag
{
  uint16_t                                                usRangeStart;
  uint16_t                                                usRangeCount;   /* 0 = 65536 objects */
} __PACKED_POST ODV3_RESET_OBJECTS_REQ_RANGE_ENTRIES_T;

typedef __PACKED_PRE struct ODV3_RESET_OBJECTS_REQ_DATA_Ttag
{
  ODV3_RESET_OBJECTS_REQ_RANGE_ENTRIES_T                  atEntries[1];
} __PACKED_POST ODV3_RESET_OBJECTS_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_RESET_OBJECTS_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_RESET_OBJECTS_REQ_DATA_T                           tData;
} __PACKED_POST ODV3_RESET_OBJECTS_REQ_T;


/* indication packet */
typedef ODV3_RESET_OBJECTS_REQ_RANGE_ENTRIES_T ODV3_RESET_OBJECTS_IND_RANGE_ENTRIES_T;
typedef ODV3_RESET_OBJECTS_REQ_DATA_T ODV3_RESET_OBJECTS_IND_DATA_T;
typedef ODV3_RESET_OBJECTS_REQ_T ODV3_RESET_OBJECTS_IND_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_RESET_OBJECTS_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_RESET_OBJECTS_CNF_T;


/* response packet */
typedef ODV3_RESET_OBJECTS_CNF_T ODV3_RESET_OBJECTS_RES_T;


/* packet union */
typedef union ODV3_RESET_OBJECTS_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_RESET_OBJECTS_REQ_T                                tReq;
  ODV3_RESET_OBJECTS_IND_T                                tInd;
  ODV3_RESET_OBJECTS_RES_T                                tRes;
  ODV3_RESET_OBJECTS_CNF_T                                tCnf;
} ODV3_RESET_OBJECTS_PCK_T;


/******************************************************************************
 * Packet:  ODV3_SET_OBJECT_NAME_REQ/ODV3_SET_OBJECT_NAME_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_SET_OBJECT_NAME_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 szName[200];  /* must be NUL-terminated */
} __PACKED_POST ODV3_SET_OBJECT_NAME_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_SET_OBJECT_NAME_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_SET_OBJECT_NAME_REQ_DATA_T                         tData;
} __PACKED_POST ODV3_SET_OBJECT_NAME_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_SET_OBJECT_NAME_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
} __PACKED_POST ODV3_SET_OBJECT_NAME_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_SET_OBJECT_NAME_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_SET_OBJECT_NAME_CNF_DATA_T                         tData;
} __PACKED_POST ODV3_SET_OBJECT_NAME_CNF_T;


/* packet union */
typedef union ODV3_SET_OBJECT_NAME_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_SET_OBJECT_NAME_REQ_T                              tReq;
  ODV3_SET_OBJECT_NAME_CNF_T                              tCnf;
} ODV3_SET_OBJECT_NAME_PCK_T;


/******************************************************************************
 * Packet:  ODV3_SET_SUBOBJECT_NAME_REQ/ODV3_SET_SUBOBJECT_NAME_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_SET_SUBOBJECT_NAME_REQ_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
  uint8_t                                                 szName[200];  /* must be NUL-terminated */
} __PACKED_POST ODV3_SET_SUBOBJECT_NAME_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_SET_SUBOBJECT_NAME_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_SET_SUBOBJECT_NAME_REQ_DATA_T                      tData;
} __PACKED_POST ODV3_SET_SUBOBJECT_NAME_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_SET_SUBOBJECT_NAME_CNF_DATA_Ttag
{
  uint16_t                                                usIndex;
  uint8_t                                                 bSubIndex;
} __PACKED_POST ODV3_SET_SUBOBJECT_NAME_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_SET_SUBOBJECT_NAME_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_SET_SUBOBJECT_NAME_CNF_DATA_T                      tData;
} __PACKED_POST ODV3_SET_SUBOBJECT_NAME_CNF_T;


/* packet union */
typedef union ODV3_SET_SUBOBJECT_NAME_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_SET_SUBOBJECT_NAME_REQ_T                           tReq;
  ODV3_SET_SUBOBJECT_NAME_CNF_T                           tCnf;
} ODV3_SET_SUBOBJECT_NAME_PCK_T;


/******************************************************************************
 * Packet:  ODV3_CREATE_DATATYPE_REQ/ODV3_CREATE_DATATYPE_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_CREATE_DATATYPE_REQ_DATA_Ttag
{
  uint16_t                                                usDatatype;
  uint32_t                                                ulDatatypeBitLength;
} __PACKED_POST ODV3_CREATE_DATATYPE_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_CREATE_DATATYPE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_DATATYPE_REQ_DATA_T                         tData;
} __PACKED_POST ODV3_CREATE_DATATYPE_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_CREATE_DATATYPE_CNF_DATA_Ttag
{
  uint16_t                                                usDatatype;
} __PACKED_POST ODV3_CREATE_DATATYPE_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_CREATE_DATATYPE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_DATATYPE_CNF_DATA_T                         tData;
} __PACKED_POST ODV3_CREATE_DATATYPE_CNF_T;


/* packet union */
typedef union ODV3_CREATE_DATATYPE_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_CREATE_DATATYPE_REQ_T                              tReq;
  ODV3_CREATE_DATATYPE_CNF_T                              tCnf;
} ODV3_CREATE_DATATYPE_PCK_T;


/******************************************************************************
 * Packet:  ODV3_DELETE_DATATYPE_REQ/ODV3_DELETE_DATATYPE_CNF
 *
 * ulSta must be TLR_S_OK on request
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_DELETE_DATATYPE_REQ_DATA_Ttag
{
  uint16_t                                                usDatatype;
} __PACKED_POST ODV3_DELETE_DATATYPE_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_DELETE_DATATYPE_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_DATATYPE_REQ_DATA_T                         tData;
} __PACKED_POST ODV3_DELETE_DATATYPE_REQ_T;


/* confirmation packet */
typedef __PACKED_PRE struct ODV3_DELETE_DATATYPE_CNF_DATA_Ttag
{
  uint16_t                                                usDatatype;
} __PACKED_POST ODV3_DELETE_DATATYPE_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_DELETE_DATATYPE_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_DATATYPE_CNF_DATA_T                         tData;
} __PACKED_POST ODV3_DELETE_DATATYPE_CNF_T;


/* packet union */
typedef union ODV3_DELETE_DATATYPE_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_DELETE_DATATYPE_REQ_T                              tReq;
  ODV3_DELETE_DATATYPE_CNF_T                              tCnf;
} ODV3_DELETE_DATATYPE_PCK_T;

/******************************************************************************
 * Packet:  ODV3_RESET_OBJECT_DICTIONARY_REQ/ODV3_RESET_OBJECT_DICTIONARY_CNF
 *
 * internal request for stack use
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_RESET_OBJECT_DICTIONARY_REQ_DATA_Ttag
{
  uint16_t                                                ausIndexes[500];
  /*
   * ausIndexes: dynamic list => tHead.ulLen = numentries * sizeof(TLR_UINT16)
   * list must be sorted
   */
} __PACKED_POST ODV3_RESET_OBJECT_DICTIONARY_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_RESET_OBJECT_DICTIONARY_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_RESET_OBJECT_DICTIONARY_REQ_DATA_T                 tData;
} __PACKED_POST ODV3_RESET_OBJECT_DICTIONARY_REQ_T;

/* confirmation packet */
typedef __PACKED_PRE struct ODV3_RESET_OBJECT_DICTIONARY_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_RESET_OBJECT_DICTIONARY_CNF_T;


/* packet union */
typedef union ODV3_RESET_OBJECT_DICTIONARY_PCK_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_RESET_OBJECT_DICTIONARY_REQ_T                      tReq;
  ODV3_RESET_OBJECT_DICTIONARY_CNF_T                      tCnf;
} ODV3_RESET_OBJECT_DICTIONARY_PCK_T;


/******************************************************************************
 * Packet:  ODV3_SET_TIMEOUT_REQ/ODV3_SET_TIMEOUT_CNF
 *
 * internal request for stack use
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_SET_TIMEOUT_REQ_DATA_Ttag
{
  uint32_t ulTimeoutMs;
} __PACKED_POST ODV3_SET_TIMEOUT_REQ_DATA_T;

typedef __PACKED_PRE struct ODV3_SET_TIMEOUT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_SET_TIMEOUT_REQ_DATA_T                             tData;
} __PACKED_POST ODV3_SET_TIMEOUT_REQ_T;

/* confirmation packet */
typedef __PACKED_PRE struct ODV3_SET_TIMEOUT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_SET_TIMEOUT_CNF_T;

/* packet union */
typedef union ODV3_SET_TIMEOUT_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ODV3_SET_TIMEOUT_REQ_T tReq;
  ODV3_SET_TIMEOUT_CNF_T tCnf;
} ODV3_SET_TIMEOUT_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_TIMEOUT_REQ/ODV3_GET_TIMEOUT_CNF
 *
 * internal request for stack use
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_GET_TIMEOUT_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_GET_TIMEOUT_REQ_T;

/* confirmation packet */
typedef __PACKED_PRE struct ODV3_GET_TIMEOUT_CNF_DATA_Ttag
{
  uint32_t ulTimeoutMs;
} __PACKED_POST ODV3_GET_TIMEOUT_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_TIMEOUT_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_TIMEOUT_CNF_DATA_T                             tData;
} __PACKED_POST ODV3_GET_TIMEOUT_CNF_T;

/* packet union */
typedef union ODV3_GET_TIMEOUT_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ODV3_GET_TIMEOUT_REQ_T tReq;
  ODV3_GET_TIMEOUT_CNF_T tCnf;
} ODV3_GET_TIMEOUT_PCK_T;


/******************************************************************************
 * Packet:  ODV3_GET_VERSION_REQ/ODV3_GET_VERSION_CNF
 */

/* request packet */
typedef __PACKED_PRE struct ODV3_GET_VERSION_REQ_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
} __PACKED_POST ODV3_GET_VERSION_REQ_T;

/* confirmation packet */
typedef __PACKED_PRE struct ODV3_GET_VERSION_CNF_DATA_ENTRY_Ttag
{
  uint16_t usMajor;
  uint16_t usMinor;
  uint16_t usBuild;
  uint16_t usRevision;
} __PACKED_POST ODV3_GET_VERSION_CNF_DATA_ENTRY_T;

typedef __PACKED_PRE struct ODV3_GET_VERSION_CNF_DATA_Ttag
{
  ODV3_GET_VERSION_CNF_DATA_ENTRY_T tApi;
  ODV3_GET_VERSION_CNF_DATA_ENTRY_T tPacketIf;
} __PACKED_POST ODV3_GET_VERSION_CNF_DATA_T;

typedef __PACKED_PRE struct ODV3_GET_VERSION_CNF_Ttag
{
  TLR_PACKET_HEADER_T                                     tHead;
  ODV3_GET_VERSION_CNF_DATA_T                             tData;
} __PACKED_POST ODV3_GET_VERSION_CNF_T;

/* packet union */
typedef union ODV3_GET_VERSION_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ODV3_GET_VERSION_REQ_T tReq;
  ODV3_GET_VERSION_CNF_T tCnf;
} ODV3_GET_VERSION_PCK_T;


/* pragma unpack */
#ifdef PRAGMA_PACK_ENABLE
#pragma PRAGMA_UNPACK_1(ODV3_PUBLIC)
#endif


#endif
