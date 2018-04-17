#ifndef __CO_OBJDICT_ERROR_H
#define __CO_OBJDICT_ERROR_H

/////////////////////////////////////////////////////////////////////////////////////
// Object Dictionary (revised) error codes
// 0x0000-0x7FFF are used for error codes directly mappable to SDO abort codes by using a translation table
// 0x8000-0xFFFF are used for additional error codes which relate to specific functions within the ObjDict
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_CO_OBJDICT_PROTOCOL_TIMEOUT
//
// MessageText:
//
//  SDO Protocol Timeout.
//
#define TLR_E_CO_OBJDICT_PROTOCOL_TIMEOUT ((TLR_RESULT)0xC09B0001L)

//
// MessageId: TLR_E_CO_OBJDICT_UNSUPPORTED_ACCESS
//
// MessageText:
//
//  Unsupported access.
//
#define TLR_E_CO_OBJDICT_UNSUPPORTED_ACCESS ((TLR_RESULT)0xC09B0002L)

//
// MessageId: TLR_E_CO_OBJDICT_OBJECT_IS_WRITE_ONLY
//
// MessageText:
//
//  Object is write only.
//
#define TLR_E_CO_OBJDICT_OBJECT_IS_WRITE_ONLY ((TLR_RESULT)0xC09B0003L)

//
// MessageId: TLR_E_CO_OBJDICT_OBJECT_IS_READ_ONLY
//
// MessageText:
//
//  Object is read only.
//
#define TLR_E_CO_OBJDICT_OBJECT_IS_READ_ONLY ((TLR_RESULT)0xC09B0004L)

//
// MessageId: TLR_E_CO_OBJDICT_OBJECT_DOES_NOT_EXIST
//
// MessageText:
//
//  Object does not exist.
//
#define TLR_E_CO_OBJDICT_OBJECT_DOES_NOT_EXIST ((TLR_RESULT)0xC09B0005L)

//
// MessageId: TLR_E_CO_OBJDICT_OBJECT_CANNOT_BE_PDO_MAPPED
//
// MessageText:
//
//  Object cannot be mapped into PDO.
//
#define TLR_E_CO_OBJDICT_OBJECT_CANNOT_BE_PDO_MAPPED ((TLR_RESULT)0xC09B0006L)

//
// MessageId: TLR_E_CO_OBJDICT_OBJECTS_WOULD_EXCEED_PDO_LENGTH
//
// MessageText:
//
//  The number and length of the objects to be mapped would exceed the PDO length.
//
#define TLR_E_CO_OBJDICT_OBJECTS_WOULD_EXCEED_PDO_LENGTH ((TLR_RESULT)0xC09B0007L)

//
// MessageId: TLR_E_CO_OBJDICT_GENERAL_PARAMETER_INCOMPATIBILITY
//
// MessageText:
//
//  General parameter incompatibility.
//
#define TLR_E_CO_OBJDICT_GENERAL_PARAMETER_INCOMPATIBILITY ((TLR_RESULT)0xC09B0008L)

//
// MessageId: TLR_E_CO_OBJDICT_ACCESS_FAILED_DUE_TO_HW_ERROR
//
// MessageText:
//
//  Access failed due to hardware error.
//
#define TLR_E_CO_OBJDICT_ACCESS_FAILED_DUE_TO_HW_ERROR ((TLR_RESULT)0xC09B0009L)

//
// MessageId: TLR_E_CO_OBJDICT_DATATYPE_DOES_NOT_MATCH
//
// MessageText:
//
//  Data type does not match, length of service parameter does not match.
//
#define TLR_E_CO_OBJDICT_DATATYPE_DOES_NOT_MATCH ((TLR_RESULT)0xC09B000AL)

//
// MessageId: TLR_E_CO_OBJDICT_DATATYPE_LENGTH_IS_TOO_LONG
//
// MessageText:
//
//  Data type does not match, length of service parameter too high.
//
#define TLR_E_CO_OBJDICT_DATATYPE_LENGTH_IS_TOO_LONG ((TLR_RESULT)0xC09B000BL)

//
// MessageId: TLR_E_CO_OBJDICT_DATATYPE_LENGTH_IS_TOO_SHORT
//
// MessageText:
//
//  Data type does not match, length of service parameter too short.
//
#define TLR_E_CO_OBJDICT_DATATYPE_LENGTH_IS_TOO_SHORT ((TLR_RESULT)0xC09B000CL)

//
// MessageId: TLR_E_CO_OBJDICT_SUBINDEX_DOES_NOT_EXIST
//
// MessageText:
//
//  Subindex does not exist.
//
#define TLR_E_CO_OBJDICT_SUBINDEX_DOES_NOT_EXIST ((TLR_RESULT)0xC09B000DL)

//
// MessageId: TLR_E_CO_OBJDICT_RANGE_OF_PARAMETER_EXCEEDED
//
// MessageText:
//
//  Value range of parameter exceeded.
//
#define TLR_E_CO_OBJDICT_RANGE_OF_PARAMETER_EXCEEDED ((TLR_RESULT)0xC09B000EL)

//
// MessageId: TLR_E_CO_OBJDICT_VALUE_OF_PARAMETER_WRITTEN_TOO_HIGH
//
// MessageText:
//
//  Value of parameter written too high.
//
#define TLR_E_CO_OBJDICT_VALUE_OF_PARAMETER_WRITTEN_TOO_HIGH ((TLR_RESULT)0xC09B000FL)

//
// MessageId: TLR_E_CO_OBJDICT_VALUE_OF_PARAMETER_WRITTEN_TOO_LOW
//
// MessageText:
//
//  Value of parameter written too low.
//
#define TLR_E_CO_OBJDICT_VALUE_OF_PARAMETER_WRITTEN_TOO_LOW ((TLR_RESULT)0xC09B0010L)

//
// MessageId: TLR_E_CO_OBJDICT_MAXIMUM_VALUE_IS_LESS_THAN_MINIMUM_VALUE
//
// MessageText:
//
//  Maximum value is less than minimum value.
//
#define TLR_E_CO_OBJDICT_MAXIMUM_VALUE_IS_LESS_THAN_MINIMUM_VALUE ((TLR_RESULT)0xC09B0011L)

//
// MessageId: TLR_E_CO_OBJDICT_GENERAL_ERROR
//
// MessageText:
//
//  General error.
//
#define TLR_E_CO_OBJDICT_GENERAL_ERROR   ((TLR_RESULT)0xC09B0012L)

//
// MessageId: TLR_E_CO_OBJDICT_DATA_CANNOT_BE_TRANSFERRED_OR_STORED_TO_THE_APP
//
// MessageText:
//
//  Data cannot be transferred or stored to the application.
//
#define TLR_E_CO_OBJDICT_DATA_CANNOT_BE_TRANSFERRED_OR_STORED_TO_THE_APP ((TLR_RESULT)0xC09B0013L)

//
// MessageId: TLR_E_CO_OBJDICT_DATA_NO_TRANSFER_DUE_TO_LOCAL_CONTROL
//
// MessageText:
//
//  Data cannot be transferred or stored to the application because of local control.
//
#define TLR_E_CO_OBJDICT_DATA_NO_TRANSFER_DUE_TO_LOCAL_CONTROL ((TLR_RESULT)0xC09B0014L)

//
// MessageId: TLR_E_CO_OBJDICT_DATA_NO_TRANSFER_DUE_TO_PRESENT_DEVICE_STATE
//
// MessageText:
//
//  Data cannot be transferred or stored to the application because of present device state.
//
#define TLR_E_CO_OBJDICT_DATA_NO_TRANSFER_DUE_TO_PRESENT_DEVICE_STATE ((TLR_RESULT)0xC09B0015L)

//
// MessageId: TLR_E_CO_OBJDICT_NO_OBJECT_DICTIONARY_PRESENT
//
// MessageText:
//
//  Object dictionary dynamic generation fails or no object dictionary present.
//
#define TLR_E_CO_OBJDICT_NO_OBJECT_DICTIONARY_PRESENT ((TLR_RESULT)0xC09B0016L)

//
// MessageId: TLR_E_CO_OBJDICT_GENERAL_INTERNAL_INCOMPATIBILITY
//
// MessageText:
//
//  General internal incompatibility.
//
#define TLR_E_CO_OBJDICT_GENERAL_INTERNAL_INCOMPATIBILITY ((TLR_RESULT)0xC09B0017L)

//
// MessageId: TLR_E_CO_OBJDICT_ALL_BY_INDEX_UNSUPPORTED
//
// MessageText:
//
//  Access via AllByIndex unsupported.
//
#define TLR_E_CO_OBJDICT_ALL_BY_INDEX_UNSUPPORTED ((TLR_RESULT)0xC09B0018L)

// 0x8000-0xFFFF ObjDict range
//
// MessageId: TLR_E_CO_OBJDICT_DELETION_LOCKED
//
// MessageText:
//
//  Deletion is locked.
//
#define TLR_E_CO_OBJDICT_DELETION_LOCKED ((TLR_RESULT)0xC09B8000L)

//
// MessageId: TLR_E_CO_OBJDICT_OTHER_TASK_HAS_LOCKED_DELETION
//
// MessageText:
//
//  Other task has locked deletion.
//
#define TLR_E_CO_OBJDICT_OTHER_TASK_HAS_LOCKED_DELETION ((TLR_RESULT)0xC09B8001L)

//
// MessageId: TLR_E_CO_OBJDICT_ONLY_ONE_READ_NOTIFY_ALLOWED
//
// MessageText:
//
//  Only one read notify allowed.
//
#define TLR_E_CO_OBJDICT_ONLY_ONE_READ_NOTIFY_ALLOWED ((TLR_RESULT)0xC09B8002L)

//
// MessageId: TLR_E_CO_OBJDICT_APPLICATION_NOT_REGISTERED
//
// MessageText:
//
//  Application task is not registered.
//
#define TLR_E_CO_OBJDICT_APPLICATION_NOT_REGISTERED ((TLR_RESULT)0xC09B8003L)

//
// MessageId: TLR_E_CO_OBJDICT_UNFRAGMENTABLE_PART_DOES_NOT_MATCH_SRCID
//
// MessageText:
//
//  Unfragmentable part of packet does not match SrcId.
//
#define TLR_E_CO_OBJDICT_UNFRAGMENTABLE_PART_DOES_NOT_MATCH_SRCID ((TLR_RESULT)0xC09B8004L)

//
// MessageId: TLR_E_CO_OBJDICT_UNFRAGMENTABLE_PART_DOES_NOT_MATCH_DESTID
//
// MessageText:
//
//  Unfragmentable part of packet does not match DestId.
//
#define TLR_E_CO_OBJDICT_UNFRAGMENTABLE_PART_DOES_NOT_MATCH_DESTID ((TLR_RESULT)0xC09B8005L)

//
// MessageId: TLR_E_CO_OBJDICT_SRCID_DOES_NOT_MATCH_ANY_FRAGMENTATION_BUFFER
//
// MessageText:
//
//  SrcId does not match any fragmentation buffer.
//
#define TLR_E_CO_OBJDICT_SRCID_DOES_NOT_MATCH_ANY_FRAGMENTATION_BUFFER ((TLR_RESULT)0xC09B8006L)

//
// MessageId: TLR_E_CO_OBJDICT_DESTID_DOES_NOT_MATCH_ANY_FRAGMENTATION_BUFFER
//
// MessageText:
//
//  DestId does not match any fragmentation buffer.
//
#define TLR_E_CO_OBJDICT_DESTID_DOES_NOT_MATCH_ANY_FRAGMENTATION_BUFFER ((TLR_RESULT)0xC09B8007L)

//
// MessageId: TLR_E_CO_OBJDICT_OBJECT_WAS_DELETED_IN_ACTION
//
// MessageText:
//
//  Object was deleted in action.
//
#define TLR_E_CO_OBJDICT_OBJECT_WAS_DELETED_IN_ACTION ((TLR_RESULT)0xC09B8008L)

//
// MessageId: TLR_E_CO_OBJDICT_SUBOBJECT_WAS_DELETED_IN_ACTION
//
// MessageText:
//
//  Subobject was deleted in action.
//
#define TLR_E_CO_OBJDICT_SUBOBJECT_WAS_DELETED_IN_ACTION ((TLR_RESULT)0xC09B8009L)

//
// MessageId: TLR_E_CO_OBJDICT_REQUEST_ABORTED
//
// MessageText:
//
//  Request aborted.
//
#define TLR_E_CO_OBJDICT_REQUEST_ABORTED ((TLR_RESULT)0xC09B800AL)

//
// MessageId: TLR_E_CO_OBJDICT_VALUE_INFO_ONLY_SUPPORTED_ON_SIMPLE_VAR
//
// MessageText:
//
//  Given bValueInfo is only supported on SimpleVar.
//
#define TLR_E_CO_OBJDICT_VALUE_INFO_ONLY_SUPPORTED_ON_SIMPLE_VAR ((TLR_RESULT)0xC09B800BL)

//
// MessageId: TLR_E_CO_OBJDICT_DATATYPE_UNDEFINED
//
// MessageText:
//
//  Data type is undefined.
//
#define TLR_E_CO_OBJDICT_DATATYPE_UNDEFINED ((TLR_RESULT)0xC09B800CL)

//
// MessageId: TLR_E_CO_OBJDICT_OTHER_APPLICATION_REGISTERED
//
// MessageText:
//
//  Other application is already registered.
//
#define TLR_E_CO_OBJDICT_OTHER_APPLICATION_REGISTERED ((TLR_RESULT)0xC09B800DL)

//
// MessageId: TLR_E_CO_OBJDICT_DATATYPE_ALREADY_EXISTS
//
// MessageText:
//
//  CANopen Datatype already exists.
//
#define TLR_E_CO_OBJDICT_DATATYPE_ALREADY_EXISTS ((TLR_RESULT)0xC09B800EL)

//
// MessageId: TLR_E_CO_OBJDICT_DATATYPE_DOES_NOT_EXIST
//
// MessageText:
//
//  CANopen Datatype does not exist.
//
#define TLR_E_CO_OBJDICT_DATATYPE_DOES_NOT_EXIST ((TLR_RESULT)0xC09B800FL)

//
// MessageId: TLR_E_CO_OBJDICT_VIRTUAL_OBJECT_CANNOT_BE_ACCESSED_WITHOUT_INDICATION
//
// MessageText:
//
//  Virtual object cannot be accessed without indication.
//
#define TLR_E_CO_OBJDICT_VIRTUAL_OBJECT_CANNOT_BE_ACCESSED_WITHOUT_INDICATION ((TLR_RESULT)0xC09B8010L)

//
// MessageId: TLR_E_CO_OBJDICT_FRAGMENTATION_IMPOSSIBLE
//
// MessageText:
//
//  Fragmentation impossible.
//
#define TLR_E_CO_OBJDICT_FRAGMENTATION_IMPOSSIBLE ((TLR_RESULT)0xC09B8011L)

//
// MessageId: TLR_E_CO_OBJDICT_ACCESS_VIA_UNDEFINED_NOTIFY_DENIED
//
// MessageText:
//
//  Access via undefined notify denied.
//
#define TLR_E_CO_OBJDICT_ACCESS_VIA_UNDEFINED_NOTIFY_DENIED ((TLR_RESULT)0xC09B8012L)

//
// MessageId: TLR_E_CO_OBJDICT_OBJECT_ALREADY_EXISTS
//
// MessageText:
//
//  Object already exists.
//
#define TLR_E_CO_OBJDICT_OBJECT_ALREADY_EXISTS ((TLR_RESULT)0xC09B8013L)

//
// MessageId: TLR_E_CO_OBJDICT_SUBOBJECT_ALREADY_EXISTS
//
// MessageText:
//
//  Subobject already exists.
//
#define TLR_E_CO_OBJDICT_SUBOBJECT_ALREADY_EXISTS ((TLR_RESULT)0xC09B8014L)

//
// MessageId: TLR_E_CO_OBJDICT_CANNOT_BE_DELETED_NOT_OWNER
//
// MessageText:
//
//  Object/Subobject cannot be deleted. Requestor is not owner.
//
#define TLR_E_CO_OBJDICT_CANNOT_BE_DELETED_NOT_OWNER ((TLR_RESULT)0xC09B8015L)

//
// MessageId: TLR_E_CO_OBJDICT_MAX_NUMBER_OF_SUBOBJECTS_EXCEEDED
//
// MessageText:
//
//  Maximum number of subobjects exceeded.
//
#define TLR_E_CO_OBJDICT_MAX_NUMBER_OF_SUBOBJECTS_EXCEEDED ((TLR_RESULT)0xC09B8016L)

//
// MessageId: TLR_E_CO_OBJDICT_HAS_NO_DEFAULT_VALUE
//
// MessageText:
//
//  Has no default value.
//
#define TLR_E_CO_OBJDICT_HAS_NO_DEFAULT_VALUE ((TLR_RESULT)0xC09B8017L)

//
// MessageId: TLR_E_CO_OBJDICT_INDICATION_FLAGS_NOT_ALLOWED
//
// MessageText:
//
//  Indication flags not allowed.
//
#define TLR_E_CO_OBJDICT_INDICATION_FLAGS_NOT_ALLOWED ((TLR_RESULT)0xC09B8018L)

//
// MessageId: TLR_E_CO_OBJDICT_INDICATION_FLAGS_NOT_SUPPORTED
//
// MessageText:
//
//  Indication flags not supported.
//
#define TLR_E_CO_OBJDICT_INDICATION_FLAGS_NOT_SUPPORTED ((TLR_RESULT)0xC09B8019L)

//
// MessageId: TLR_E_CO_OBJDICT_ONLY_ONE_RW_UNDEFINED_SUBOBJ_NOTIFY_ALLOWED
//
// MessageText:
//
//  Only one read/write notify for non-existing subobject notify allowed.
//
#define TLR_E_CO_OBJDICT_ONLY_ONE_RW_UNDEFINED_SUBOBJ_NOTIFY_ALLOWED ((TLR_RESULT)0xC09B801AL)

//
// MessageId: TLR_E_CO_OBJDICT_ONLY_ONE_INFO_UNDEFINED_SUBOBJ_NOTIFY_ALLOWED
//
// MessageText:
//
//  Only one info notify for non-existing subobject notify allowed.
//
#define TLR_E_CO_OBJDICT_ONLY_ONE_INFO_UNDEFINED_SUBOBJ_NOTIFY_ALLOWED ((TLR_RESULT)0xC09B801BL)

//
// MessageId: TLR_E_CO_OBJDICT_CREATION_NOT_COMPLETED
//
// MessageText:
//
//  Running creation of object/subobjects not yet completed.
//
#define TLR_E_CO_OBJDICT_CREATION_NOT_COMPLETED ((TLR_RESULT)0xC09B801CL)

//
// MessageId: TLR_E_CO_OBJDICT_TOTAL_DATA_BYTES_AND_PKT_LEN_MISMATCH
//
// MessageText:
//
//  Dependency of total data bytes and packet length not fulfilled.
//
#define TLR_E_CO_OBJDICT_TOTAL_DATA_BYTES_AND_PKT_LEN_MISMATCH ((TLR_RESULT)0xC09B801DL)

//
// MessageId: TLR_E_CO_OBJDICT_NO_MORE_SUBINDEXES
//
// MessageText:
//
//  No more subindexes.
//
#define TLR_E_CO_OBJDICT_NO_MORE_SUBINDEXES ((TLR_RESULT)0xC09B801EL)

//
// MessageId: TLR_E_CO_OBJDICT_VIRTUAL_CANNOT_BE_COMBINED_WITH_INITIAL_VALUE
//
// MessageText:
//
//  Virtual cannot be combined with initial value.
//
#define TLR_E_CO_OBJDICT_VIRTUAL_CANNOT_BE_COMBINED_WITH_INITIAL_VALUE ((TLR_RESULT)0xC09B801FL)

 /* Unexpected Errors (if happening, notify support) */
//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_000
//
// MessageText:
//
//  Unexpected Error (0xF000)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_000 ((TLR_RESULT)0xC09BF000L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_001
//
// MessageText:
//
//  Unexpected Error (0xF001)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_001 ((TLR_RESULT)0xC09BF001L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_002
//
// MessageText:
//
//  Unexpected Error (0xF002)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_002 ((TLR_RESULT)0xC09BF002L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_003
//
// MessageText:
//
//  Unexpected Error (0xF003)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_003 ((TLR_RESULT)0xC09BF003L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_004
//
// MessageText:
//
//  Unexpected Error (0xF004)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_004 ((TLR_RESULT)0xC09BF004L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_005
//
// MessageText:
//
//  Unexpected Error (0xF005)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_005 ((TLR_RESULT)0xC09BF005L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_006
//
// MessageText:
//
//  Unexpected Error (0xF006)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_006 ((TLR_RESULT)0xC09BF006L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_007
//
// MessageText:
//
//  Unexpected Error (0xF007)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_007 ((TLR_RESULT)0xC09BF007L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_008
//
// MessageText:
//
//  Unexpected Error (0xF008)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_008 ((TLR_RESULT)0xC09BF008L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_009
//
// MessageText:
//
//  Unexpected Error (0xF009)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_009 ((TLR_RESULT)0xC09BF009L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00A
//
// MessageText:
//
//  Unexpected Error (0xF00A)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00A ((TLR_RESULT)0xC09BF00AL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00B
//
// MessageText:
//
//  Unexpected Error (0xF00B)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00B ((TLR_RESULT)0xC09BF00BL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00C
//
// MessageText:
//
//  Unexpected Error (0xF00C)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00C ((TLR_RESULT)0xC09BF00CL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00D
//
// MessageText:
//
//  Unexpected Error (0xF00D)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00D ((TLR_RESULT)0xC09BF00DL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00E
//
// MessageText:
//
//  Unexpected Error (0xF00E)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00E ((TLR_RESULT)0xC09BF00EL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00F
//
// MessageText:
//
//  Unexpected Error (0xF00F)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_00F ((TLR_RESULT)0xC09BF00FL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_010
//
// MessageText:
//
//  Unexpected Error (0xF010)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_010 ((TLR_RESULT)0xC09BF010L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_011
//
// MessageText:
//
//  Unexpected Error (0xF011)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_011 ((TLR_RESULT)0xC09BF011L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_012
//
// MessageText:
//
//  Unexpected Error (0xF012)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_012 ((TLR_RESULT)0xC09BF012L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_013
//
// MessageText:
//
//  Unexpected Error (0xF013)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_013 ((TLR_RESULT)0xC09BF013L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_014
//
// MessageText:
//
//  Unexpected Error (0xF014)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_014 ((TLR_RESULT)0xC09BF014L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_015
//
// MessageText:
//
//  Unexpected Error (0xF015)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_015 ((TLR_RESULT)0xC09BF015L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_016
//
// MessageText:
//
//  Unexpected Error (0xF016)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_016 ((TLR_RESULT)0xC09BF016L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_017
//
// MessageText:
//
//  Unexpected Error (0xF017)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_017 ((TLR_RESULT)0xC09BF017L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_018
//
// MessageText:
//
//  Unexpected Error (0xF018)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_018 ((TLR_RESULT)0xC09BF018L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_019
//
// MessageText:
//
//  Unexpected Error (0xF019)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_019 ((TLR_RESULT)0xC09BF019L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01A
//
// MessageText:
//
//  Unexpected Error (0xF01A)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01A ((TLR_RESULT)0xC09BF01AL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01B
//
// MessageText:
//
//  Unexpected Error (0xF01B)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01B ((TLR_RESULT)0xC09BF01BL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01C
//
// MessageText:
//
//  Unexpected Error (0xF01C)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01C ((TLR_RESULT)0xC09BF01CL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01D
//
// MessageText:
//
//  Unexpected Error (0xF01D)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01D ((TLR_RESULT)0xC09BF01DL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01E
//
// MessageText:
//
//  Unexpected Error (0xF01E)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01E ((TLR_RESULT)0xC09BF01EL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01F
//
// MessageText:
//
//  Unexpected Error (0xF01F)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_01F ((TLR_RESULT)0xC09BF01FL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_020
//
// MessageText:
//
//  Unexpected Error (0xF020)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_020 ((TLR_RESULT)0xC09BF020L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_021
//
// MessageText:
//
//  Unexpected Error (0xF021)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_021 ((TLR_RESULT)0xC09BF021L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_022
//
// MessageText:
//
//  Unexpected Error (0xF022)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_022 ((TLR_RESULT)0xC09BF022L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_023
//
// MessageText:
//
//  Unexpected Error (0xF023)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_023 ((TLR_RESULT)0xC09BF023L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_024
//
// MessageText:
//
//  Unexpected Error (0xF024)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_024 ((TLR_RESULT)0xC09BF024L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_025
//
// MessageText:
//
//  Unexpected Error (0xF025)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_025 ((TLR_RESULT)0xC09BF025L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_026
//
// MessageText:
//
//  Unexpected Error (0xF026)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_026 ((TLR_RESULT)0xC09BF026L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_027
//
// MessageText:
//
//  Unexpected Error (0xF027)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_027 ((TLR_RESULT)0xC09BF027L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_028
//
// MessageText:
//
//  Unexpected Error (0xF028)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_028 ((TLR_RESULT)0xC09BF028L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_029
//
// MessageText:
//
//  Unexpected Error (0xF029)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_029 ((TLR_RESULT)0xC09BF029L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02A
//
// MessageText:
//
//  Unexpected Error (0xF02A)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02A ((TLR_RESULT)0xC09BF02AL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02B
//
// MessageText:
//
//  Unexpected Error (0xF02B)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02B ((TLR_RESULT)0xC09BF02BL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02C
//
// MessageText:
//
//  Unexpected Error (0xF02C)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02C ((TLR_RESULT)0xC09BF02CL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02D
//
// MessageText:
//
//  Unexpected Error (0xF02D)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02D ((TLR_RESULT)0xC09BF02DL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02E
//
// MessageText:
//
//  Unexpected Error (0xF02E)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02E ((TLR_RESULT)0xC09BF02EL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02F
//
// MessageText:
//
//  Unexpected Error (0xF02F)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_02F ((TLR_RESULT)0xC09BF02FL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_030
//
// MessageText:
//
//  Unexpected Error (0xF030)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_030 ((TLR_RESULT)0xC09BF030L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_031
//
// MessageText:
//
//  Unexpected Error (0xF031)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_031 ((TLR_RESULT)0xC09BF031L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_032
//
// MessageText:
//
//  Unexpected Error (0xF032)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_032 ((TLR_RESULT)0xC09BF032L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_033
//
// MessageText:
//
//  Unexpected Error (0xF033)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_033 ((TLR_RESULT)0xC09BF033L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_034
//
// MessageText:
//
//  Unexpected Error (0xF034)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_034 ((TLR_RESULT)0xC09BF034L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_035
//
// MessageText:
//
//  Unexpected Error (0xF035)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_035 ((TLR_RESULT)0xC09BF035L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_036
//
// MessageText:
//
//  Unexpected Error (0xF036)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_036 ((TLR_RESULT)0xC09BF036L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_037
//
// MessageText:
//
//  Unexpected Error (0xF037)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_037 ((TLR_RESULT)0xC09BF037L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_038
//
// MessageText:
//
//  Unexpected Error (0xF038)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_038 ((TLR_RESULT)0xC09BF038L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_039
//
// MessageText:
//
//  Unexpected Error (0xF039)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_039 ((TLR_RESULT)0xC09BF039L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03A
//
// MessageText:
//
//  Unexpected Error (0xF03A)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03A ((TLR_RESULT)0xC09BF03AL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03B
//
// MessageText:
//
//  Unexpected Error (0xF03B)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03B ((TLR_RESULT)0xC09BF03BL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03C
//
// MessageText:
//
//  Unexpected Error (0xF03C)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03C ((TLR_RESULT)0xC09BF03CL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03D
//
// MessageText:
//
//  Unexpected Error (0xF03D)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03D ((TLR_RESULT)0xC09BF03DL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03E
//
// MessageText:
//
//  Unexpected Error (0xF03E)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03E ((TLR_RESULT)0xC09BF03EL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03F
//
// MessageText:
//
//  Unexpected Error (0xF03F)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_03F ((TLR_RESULT)0xC09BF03FL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_040
//
// MessageText:
//
//  Unexpected Error (0xF040)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_040 ((TLR_RESULT)0xC09BF040L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_041
//
// MessageText:
//
//  Unexpected Error (0xF041)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_041 ((TLR_RESULT)0xC09BF041L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_042
//
// MessageText:
//
//  Unexpected Error (0xF042)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_042 ((TLR_RESULT)0xC09BF042L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_043
//
// MessageText:
//
//  Unexpected Error (0xF043)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_043 ((TLR_RESULT)0xC09BF043L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_044
//
// MessageText:
//
//  Unexpected Error (0xF044)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_044 ((TLR_RESULT)0xC09BF044L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_045
//
// MessageText:
//
//  Unexpected Error (0xF045)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_045 ((TLR_RESULT)0xC09BF045L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_046
//
// MessageText:
//
//  Unexpected Error (0xF046)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_046 ((TLR_RESULT)0xC09BF046L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_047
//
// MessageText:
//
//  Unexpected Error (0xF047)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_047 ((TLR_RESULT)0xC09BF047L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_048
//
// MessageText:
//
//  Unexpected Error (0xF048)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_048 ((TLR_RESULT)0xC09BF048L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_049
//
// MessageText:
//
//  Unexpected Error (0xF049)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_049 ((TLR_RESULT)0xC09BF049L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04A
//
// MessageText:
//
//  Unexpected Error (0xF04A)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04A ((TLR_RESULT)0xC09BF04AL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04B
//
// MessageText:
//
//  Unexpected Error (0xF04B)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04B ((TLR_RESULT)0xC09BF04BL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04C
//
// MessageText:
//
//  Unexpected Error (0xF04C)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04C ((TLR_RESULT)0xC09BF04CL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04D
//
// MessageText:
//
//  Unexpected Error (0xF04D)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04D ((TLR_RESULT)0xC09BF04DL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04E
//
// MessageText:
//
//  Unexpected Error (0xF04E)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04E ((TLR_RESULT)0xC09BF04EL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04F
//
// MessageText:
//
//  Unexpected Error (0xF04F)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_04F ((TLR_RESULT)0xC09BF04FL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_050
//
// MessageText:
//
//  Unexpected Error (0xF050)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_050 ((TLR_RESULT)0xC09BF050L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_051
//
// MessageText:
//
//  Unexpected Error (0xF051)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_051 ((TLR_RESULT)0xC09BF051L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_052
//
// MessageText:
//
//  Unexpected Error (0xF052)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_052 ((TLR_RESULT)0xC09BF052L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_053
//
// MessageText:
//
//  Unexpected Error (0xF053)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_053 ((TLR_RESULT)0xC09BF053L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_054
//
// MessageText:
//
//  Unexpected Error (0xF054)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_054 ((TLR_RESULT)0xC09BF054L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_055
//
// MessageText:
//
//  Unexpected Error (0xF055)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_055 ((TLR_RESULT)0xC09BF055L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_056
//
// MessageText:
//
//  Unexpected Error (0xF056)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_056 ((TLR_RESULT)0xC09BF056L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_057
//
// MessageText:
//
//  Unexpected Error (0xF057)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_057 ((TLR_RESULT)0xC09BF057L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_058
//
// MessageText:
//
//  Unexpected Error (0xF058)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_058 ((TLR_RESULT)0xC09BF058L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_059
//
// MessageText:
//
//  Unexpected Error (0xF059)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_059 ((TLR_RESULT)0xC09BF059L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05A
//
// MessageText:
//
//  Unexpected Error (0xF05A)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05A ((TLR_RESULT)0xC09BF05AL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05B
//
// MessageText:
//
//  Unexpected Error (0xF05B)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05B ((TLR_RESULT)0xC09BF05BL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05C
//
// MessageText:
//
//  Unexpected Error (0xF05C)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05C ((TLR_RESULT)0xC09BF05CL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05D
//
// MessageText:
//
//  Unexpected Error (0xF05D)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05D ((TLR_RESULT)0xC09BF05DL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05E
//
// MessageText:
//
//  Unexpected Error (0xF05E)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05E ((TLR_RESULT)0xC09BF05EL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05F
//
// MessageText:
//
//  Unexpected Error (0xF05F)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_05F ((TLR_RESULT)0xC09BF05FL)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_060
//
// MessageText:
//
//  Unexpected Error (0xF060)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_060 ((TLR_RESULT)0xC09BF060L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_061
//
// MessageText:
//
//  Unexpected Error (0xF061)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_061 ((TLR_RESULT)0xC09BF061L)

//
// MessageId: TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_062
//
// MessageText:
//
//  Unexpected Error (0xF062)
//
#define TLR_E_CO_OBJDICT_UNEXPECTED_ERROR_062 ((TLR_RESULT)0xC09BF062L)




#endif  //__CO_OBJDICT_ERROR_H

