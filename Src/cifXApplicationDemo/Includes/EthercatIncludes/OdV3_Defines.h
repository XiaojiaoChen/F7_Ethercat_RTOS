/**************************************************************************************
 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
$Id: OdV3_Defines.h 62201 2016-07-14 09:45:18Z Sven $:


Changes:
 Date          Description
 -----------------------------------------------------------------------------------
 yyyy-mm-dd    created
**************************************************************************************/

#ifndef _ODV3_DEFINES_H
#define _ODV3_DEFINES_H


/******************************************************************************
 * Access flags
 * usAccessFlags field
 */
#define ODV3_ACCESS_FLAGS_SUBINDEX_0_WRITE_0_FIRST        0x0200      /* on writing all subindexes starting from subindex 0, write 0 to subindex 0 first */
#define ODV3_ACCESS_FLAGS_CREATE_SUBINDEX_0               0x0400      /* only on indexed objects, uses simple var bValueInfo fields (uses data type ODV3_DATATYPE_UNSIGNED8) */
#define ODV3_ACCESS_FLAGS_FORCE_INDEXED                   0x0800
#define ODV3_ACCESS_FLAGS_RXPDO_MAPPABLE                  0x1000
#define ODV3_ACCESS_FLAGS_TXPDO_MAPPABLE                  0x2000
#define ODV3_ACCESS_FLAGS_BACKUP                          0x4000
#define ODV3_ACCESS_FLAGS_SETTINGS                        0x8000

/******************************************************************************
 * Value Info
 * bValueInfo field
 */
#define ODV3_VALUE_INFO_NAME                              0x01
#define ODV3_VALUE_INFO_INITIAL_VALUE                     0x02
#define ODV3_VALUE_INFO_VIRTUAL                           0x04      /* make object/subobject virtual */
#define ODV3_VALUE_INFO_ECAT_UNIT                         0x08      /* EtherCAT only */
#define ODV3_VALUE_INFO_DEFAULT_VALUE                     0x10
#define ODV3_VALUE_INFO_MINIMUM                           0x20
#define ODV3_VALUE_INFO_MAXIMUM                           0x40
#define ODV3_VALUE_INFO_VARIABLE_SIZE_VALUE               0x80

/******************************************************************************
 * Needed Data type definitions
 */
#define ODV3_DATATYPE_UNSIGNED8                           0x0005

/******************************************************************************
 * Object Code definitions
 */
#define ODV3_OBJCODE_DOMAIN                               0x02
#define ODV3_OBJCODE_DEFTYPE                              0x05
#define ODV3_OBJCODE_DEFSTRUCT                            0x06
#define ODV3_OBJCODE_VAR                                  0x07
#define ODV3_OBJCODE_ARRAY                                0x08
#define ODV3_OBJCODE_RECORD                               0x09

/******************************************************************************
 * Multiple Parameter read/write access flags
 * bMultipleParaAccessFlags field
 */
#define ODV3_MULTIPLE_PARA_ACCESS_ALL_INDEXES               0x01    /* access all index starting at bSubIndex (0 or 1 allowed) (reserved for read/write multiple parameter) */
#define ODV3_MULTIPLE_PARA_ACCESS_BIT_TYPES_BIT_ALIGNED     0x02    /* access to bit types will be placed at bit boundaries */
#define ODV3_MULTIPLE_PARA_ACCESS_WRITE_SI0_TO_0_FIRST      0x04    /* write subindex 0 to zero first and final value as last transfer, object properties can enable it without having been set here */
#define ODV3_MULTIPLE_PARA_ACCESS_SUBINDEX_0_PADDED_TO_U16  0x08    /* on reading and writing all indexes, the subindex 0 is padded to 16bit integer (when object is not SimpleVar) */
#define ODV3_MULTIPLE_PARA_ACCESS_USE_NUM_SUBOBJS_ON_READ   0x10    /* read objects based on number of sub objects instead max of sub objects */
#define ODV3_MULTIPLE_PARA_ACCESS_EVAL_SUBINDEX_0_ON_WRITE  0x10    /* on writing all by indexes, subindex 0 will be evaluated if transferred */
#define ODV3_MULTIPLE_PARA_ACCESS_CHECK_ACCESS_RIGHTS       0x20    /* check access rights */
#define ODV3_MULTIPLE_PARA_ACCESS_REQUIRE_ALL_ACCESSIBLE    0x40    /* require all to be accessible by access rights when ODV3_MULTIPLE_PARA_ACCESS_CHECK_ACCESS_RIGHTS is set */

/******************************************************************************
 * GetSubObjectInfo.ValueInfo
 */
#define ODV3_GET_SUBOBJECT_INFO_VALUE_INFO_NAME           0x01
#define ODV3_GET_SUBOBJECT_INFO_VALUE_INFO_ECAT_UNIT      0x10
#define ODV3_GET_SUBOBJECT_INFO_VALUE_INFO_DEFAULT_VALUE  0x20
#define ODV3_GET_SUBOBJECT_INFO_VALUE_INFO_MINIMUM_VALUE  0x40  /* always uses max length */
#define ODV3_GET_SUBOBJECT_INFO_VALUE_INFO_MAXIMUM_VALUE  0x80  /* always uses max length */

/******************************************************************************
 * GetObjectProperties.Flags
 */
#define ODV3_OBJECT_PROP_FLAG_ALL_INDEXES_ARE_FIXED_SIZE    0x00000001
#define ODV3_OBJECT_PROP_FLAG_IS_INDEXED                    0x00000002  /* is not a simple variable */
#define ODV3_OBJECT_PROP_FLAG_WRITE_SI0_TO_0_FIRST_REQUIRED 0x00000004  /* require ODV3_MULTIPLE_PARA_ACCESS_WRITE_SI0_TO_0_FIRST, setting this bit will set the actual transfer control bit */

/******************************************************************************
 * special value for ulTotalDataBytes in Write Requests
 */
#define ODV3_WRITE_OBJECT_TOTAL_DATA_BYTES_NOT_SPECIFIED    0xFFFFFFFF

#endif
