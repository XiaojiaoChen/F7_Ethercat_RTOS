/**************************************************************************************

   Copyright (c) Hilscher GmbH. All Rights Reserved.

 **************************************************************************************

    @version $Id: EcatFoE_Public.h 43169 2014-02-21 10:47:19Z Sven $

**************************************************************************************/

#ifndef __ECATFOE_PUBLIC_H
#define __ECATFOE_PUBLIC_H

#define ECAT_FOE_PROCESS_QUEUE_NAME "ECAT_FOE_QUE"

#define ECAT_FOE_REGISTER_FILE_INDICATIONS_REQ 0x9500
#define ECAT_FOE_REGISTER_FILE_INDICATIONS_CNF 0x9501

#define ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ 0x9502
#define ECAT_FOE_UNREGISTER_FILE_INDICATIONS_CNF 0x9503

#define ECAT_FOE_WRITE_FILE_IND 0x9510
#define ECAT_FOE_WRITE_FILE_RES 0x9511

#define ECAT_FOE_READ_FILE_IND 0x9512
#define ECAT_FOE_READ_FILE_RES 0x9513

#define ECAT_FOE_FILE_WRITTEN_IND 0x9520
#define ECAT_FOE_FILE_WRITTEN_RES 0x9521

#define ECAT_FOE_FILE_WRITE_ABORTED_IND 0x9530
#define ECAT_FOE_FILE_WRITE_ABORTED_RES 0x9531

#define ECAT_FOE_MAX_FILE_NAME_LENGTH 256

/******************************************************************************
 * Packet:  ECAT_FOE_REGISTER_FILE_INDICATIONS_REQ/ECAT_FOE_REGISTER_FILE_INDICATIONS_CNF
 */

#define ECAT_FOE_INDICATION_TYPE_FILE_WRITTEN 1
#define ECAT_FOE_INDICATION_TYPE_ANY_FILE_WRITTEN 2
#define ECAT_FOE_INDICATION_TYPE_VIRTUAL_FILE 3
#define ECAT_FOE_INDICATION_TYPE_ANY_VIRTUAL_FILE 4 /* used for rcX File Handler */
#define ECAT_FOE_INDICATION_TYPE_ANY_FILE_WRITE_ABORTED 5

/* request packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_REGISTER_FILE_INDICATIONS_REQ_DATA_Ttag
{
  TLR_UINT8 bIndicationType;
  TLR_STR abFilename[ECAT_FOE_MAX_FILE_NAME_LENGTH];
} __TLR_PACKED_POST ECAT_FOE_REGISTER_FILE_INDICATIONS_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_REGISTER_FILE_INDICATIONS_REQ_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_REGISTER_FILE_INDICATIONS_REQ_DATA_T tData;
} __TLR_PACKED_POST ECAT_FOE_REGISTER_FILE_INDICATIONS_REQ_T;


/* confirmation packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_REGISTER_FILE_INDICATIONS_CNF_DATA_Ttag
{
  TLR_UINT8 bIndicationType;
  TLR_STR abFilename[ECAT_FOE_MAX_FILE_NAME_LENGTH];
} __TLR_PACKED_POST ECAT_FOE_REGISTER_FILE_INDICATIONS_CNF_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_REGISTER_FILE_INDICATIONS_CNF_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_REGISTER_FILE_INDICATIONS_CNF_DATA_T tData;
} __TLR_PACKED_POST ECAT_FOE_REGISTER_FILE_INDICATIONS_CNF_T;


/* packet union */
typedef union ECAT_FOE_REGISTER_FILE_INDICATIONS_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_REGISTER_FILE_INDICATIONS_REQ_T tReq;
  ECAT_FOE_REGISTER_FILE_INDICATIONS_CNF_T tCnf;
} ECAT_FOE_REGISTER_FILE_INDICATIONS_PCK_T;


/******************************************************************************
 * Packet:  ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ/ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ
 */

/* request packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ_DATA_Ttag
{
  TLR_UINT8 bIndicationType;
  TLR_STR abFilename[ECAT_FOE_MAX_FILE_NAME_LENGTH];
} __TLR_PACKED_POST ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ_DATA_T tData;
} __TLR_PACKED_POST ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ_T;


/* confirmation packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_UNREGISTER_FILE_INDICATIONS_CNF_Ttag
{
  TLR_PACKET_HEADER_T tHead;
} __TLR_PACKED_POST ECAT_FOE_UNREGISTER_FILE_INDICATIONS_CNF_T;


/* packet union */
typedef union ECAT_FOE_UNREGISTER_FILE_INDICATIONS_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_UNREGISTER_FILE_INDICATIONS_REQ_T tReq;
  ECAT_FOE_UNREGISTER_FILE_INDICATIONS_CNF_T tCnf;
} ECAT_FOE_UNREGISTER_FILE_INDICATIONS_PCK_T;


/******************************************************************************
 * Packet:  ECAT_FOE_WRITE_FILE_IND/ECAT_FOE_WRITE_FILE_RES
 */

/* request packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_WRITE_FILE_IND_DATA_Ttag
{
  TLR_UINT8 abData[1024]; /* may be larger depending on foreign queue size */
  /* first packet contains password and filename in abData, following packets have data */
  /* last segment is signaled when ulExt.Seq is set to LAST, can have zero bytes of data */
  /* middle segment is signaled when ulExt.Seq is set to MIDDLE */
} __TLR_PACKED_POST ECAT_FOE_WRITE_FILE_IND_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_WRITE_FILE_IND_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_WRITE_FILE_IND_DATA_T tData;
} __TLR_PACKED_POST ECAT_FOE_WRITE_FILE_IND_T;


/* confirmation packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_WRITE_FILE_RES_DATA_Ttag
{
  TLR_UINT8 abText[1024]; /* only valid when packet status != 0 */
} __TLR_PACKED_POST ECAT_FOE_WRITE_FILE_RES_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_WRITE_FILE_RES_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_WRITE_FILE_RES_DATA_T tData;
} __TLR_PACKED_POST ECAT_FOE_WRITE_FILE_RES_T;


/* packet union */
typedef union ECAT_FOE_WRITE_FILE_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_WRITE_FILE_IND_T tInd;
  ECAT_FOE_WRITE_FILE_RES_T tRes;
} ECAT_FOE_WRITE_FILE_PCK_T;


/******************************************************************************
 * Packet:  ECAT_FOE_READ_FILE_IND/ECAT_FOE_READ_FILE_RES
 */

/* indication packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_READ_FILE_IND_DATA_Ttag
{
  TLR_UINT32 ulMaximumByteSizeOfFragment; /* each packet fragment that is not marked LAST has to use this amount of data in its response handling */
  /* on MIDDLE segments, the packet will have ulLen set to 4 */
  TLR_UINT32 ulPassword;  /* only valid on first fragment */
  TLR_UINT8 abFilename[ECAT_FOE_MAX_FILE_NAME_LENGTH]; /* only valid on first fragment */
} __TLR_PACKED_POST ECAT_FOE_READ_FILE_IND_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_READ_FILE_IND_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_READ_FILE_IND_DATA_T tData; /* only valid on first fragment, following fragments have ulLen set to 0 */
} __TLR_PACKED_POST ECAT_FOE_READ_FILE_IND_T;


/* response packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_READ_FILE_RES_DATA_Ttag
{
  TLR_UINT8 abData[1600]; /* actual size depends on ulLen */
  /* last segment is signaled when length is smaller than ulMaximumByteSizeOfFragment and it is expected to have ulExt.Seq set to LAST */
  /* middle segment is signaled when length is equal to ulMaximumByteSizeOfFragment and it is expected to have ulExt.Seq set to MIDDLE */

  /* in case of error, this field is used for communicating the error string */
} __TLR_PACKED_POST ECAT_FOE_READ_FILE_RES_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_READ_FILE_RES_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_READ_FILE_RES_DATA_T tData;
} __TLR_PACKED_POST ECAT_FOE_READ_FILE_RES_T;


/* packet union */
typedef union ECAT_FOE_READ_FILE_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_READ_FILE_IND_T tInd;
  ECAT_FOE_READ_FILE_RES_T tRes;
} ECAT_FOE_READ_FILE_PCK_T;


/******************************************************************************
 * Packet:  ECAT_FOE_FILE_WRITTEN_IND/ECAT_FOE_FILE_WRITTEN_RES
 */

/* indication packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_FILE_WRITTEN_IND_DATA_Ttag
{
  TLR_UINT8 abFilename[ECAT_FOE_MAX_FILE_NAME_LENGTH];
} __TLR_PACKED_POST ECAT_FOE_FILE_WRITTEN_IND_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_FILE_WRITTEN_IND_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_FILE_WRITTEN_IND_DATA_T tData;
} __TLR_PACKED_POST ECAT_FOE_FILE_WRITTEN_IND_T;


/* response packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_FILE_WRITTEN_RES_Ttag
{
  TLR_PACKET_HEADER_T tHead;
} __TLR_PACKED_POST ECAT_FOE_FILE_WRITTEN_RES_T;


/* packet union */
typedef union ECAT_FOE_FILE_WRITTEN_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_FILE_WRITTEN_IND_T tInd;
  ECAT_FOE_FILE_WRITTEN_RES_T tRes;
} ECAT_FOE_FILE_WRITTEN_PCK_T;

/******************************************************************************
 * Packet:  ECAT_FOE_FILE_WRITTE_ABORTED_IND/ECAT_FOE_FILE_WRITTE_ABORTED_RES
 */

/* indication packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_FILE_WRITE_ABORTED_IND_DATA_Ttag
{
  TLR_UINT8 abFilename[ECAT_FOE_MAX_FILE_NAME_LENGTH];
} __TLR_PACKED_POST ECAT_FOE_FILE_WRITE_ABORTED_IND_DATA_T;

typedef __TLR_PACKED_PRE struct ECAT_FOE_FILE_WRITE_ABORTED_IND_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_FILE_WRITE_ABORTED_IND_DATA_T tData;
} __TLR_PACKED_POST ECAT_FOE_FILE_WRITE_ABORTED_IND_T;


/* response packet */
typedef __TLR_PACKED_PRE struct ECAT_FOE_FILE_WRITE_ABORTED_RES_Ttag
{
  TLR_PACKET_HEADER_T tHead;
} __TLR_PACKED_POST ECAT_FOE_FILE_WRITE_ABORTED_RES_T;


/* packet union */
typedef union ECAT_FOE_FILE_WRITE_ABORTED_PCK_Ttag
{
  TLR_PACKET_HEADER_T tHead;
  ECAT_FOE_FILE_WRITE_ABORTED_IND_T tInd;
  ECAT_FOE_FILE_WRITE_ABORTED_RES_T tRes;
} ECAT_FOE_FILE_WRITE_ABORTED_PCK_T;


#endif //__ECATFOE_PUBLIC_H
