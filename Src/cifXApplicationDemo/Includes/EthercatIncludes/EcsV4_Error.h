#ifndef __ECSV4_ERROR_H
#define __ECSV4_ERROR_H

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 ESM diagnostic codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_DIAG_S_ECSV4_ESM_STATE_INIT
//
// MessageText:
//
//  Slave is in state INIT.
//
#define TLR_DIAG_S_ECSV4_ESM_STATE_INIT  ((TLR_RESULT)0x00AF0001L)

//
// MessageId: TLR_DIAG_S_ECSV4_ESM_STATE_PREOP
//
// MessageText:
//
//  Slave is in state PREOP.
//
#define TLR_DIAG_S_ECSV4_ESM_STATE_PREOP ((TLR_RESULT)0x00AF0002L)

//
// MessageId: TLR_DIAG_S_ECSV4_ESM_STATE_SAFEOP
//
// MessageText:
//
//  Slave is in state SAFEOP.
//
#define TLR_DIAG_S_ECSV4_ESM_STATE_SAFEOP ((TLR_RESULT)0x00AF0003L)

//
// MessageId: TLR_DIAG_S_ECSV4_ESM_STATE_OP
//
// MessageText:
//
//  Slave is in state OP.
//
#define TLR_DIAG_S_ECSV4_ESM_STATE_OP    ((TLR_RESULT)0x00AF0004L)

//
// MessageId: TLR_DIAG_W_ECSV4_ESM_STATE_ERR_INIT
//
// MessageText:
//
//  Slave is in state ERR INIT.
//
#define TLR_DIAG_W_ECSV4_ESM_STATE_ERR_INIT ((TLR_RESULT)0x80AF0005L)

//
// MessageId: TLR_DIAG_W_ECSV4_ESM_STATE_ERR_PREOP
//
// MessageText:
//
//  Slave is in state ERR PREOP.
//
#define TLR_DIAG_W_ECSV4_ESM_STATE_ERR_PREOP ((TLR_RESULT)0x80AF0006L)

//
// MessageId: TLR_DIAG_W_ECSV4_ESM_STATE_ERR_SAFEOP
//
// MessageText:
//
//  Slave is in state ERR SAFEOP.
//
#define TLR_DIAG_W_ECSV4_ESM_STATE_ERR_SAFEOP ((TLR_RESULT)0x80AF0007L)

//
// MessageId: TLR_DIAG_W_ECSV4_ESM_STATE_ERR_OP
//
// MessageText:
//
//  Slave is in state ERR OP.
//
#define TLR_DIAG_W_ECSV4_ESM_STATE_ERR_OP ((TLR_RESULT)0x80AF0008L)

//
// MessageId: TLR_DIAG_S_ECSV4_ESM_STATE_BOOTING
//
// MessageText:
//
//  Slave is booting.
//
#define TLR_DIAG_S_ECSV4_ESM_STATE_BOOTING ((TLR_RESULT)0x00AF0009L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 ESM error codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_ECSV4_ESM_TOO_MANY_APPLICATIONS_ALREADY_REGISTERED
//
// MessageText:
//
//  Too many applications already registered for indications.
//
#define TLR_E_ECSV4_ESM_TOO_MANY_APPLICATIONS_ALREADY_REGISTERED ((TLR_RESULT)0xC0AF000AL)

//
// MessageId: TLR_E_ECSV4_ESM_OUTPUTSIZE_EXCEEDS_MAX
//
// MessageText:
//
//  Invalid I/O size: output size exceeds maximum (depends on chip type).
//
#define TLR_E_ECSV4_ESM_OUTPUTSIZE_EXCEEDS_MAX ((TLR_RESULT)0xC0AF000CL)

//
// MessageId: TLR_E_ECSV4_ESM_INPUTSIZE_EXCEEDS_MAX
//
// MessageText:
//
//  Invalid I/O size: input size exceeds maximum (depends on chip type).
//
#define TLR_E_ECSV4_ESM_INPUTSIZE_EXCEEDS_MAX ((TLR_RESULT)0xC0AF000DL)

//
// MessageId: TLR_E_ECSV4_ESM_SUM_OF_INPUTSIZE_AND_OUTPUSIZE_EXCEEDS_MAX
//
// MessageText:
//
//  Invalid I/O size: sum of input size and output size exceeds maximum (depends on chip type).
//
#define TLR_E_ECSV4_ESM_SUM_OF_INPUTSIZE_AND_OUTPUSIZE_EXCEEDS_MAX ((TLR_RESULT)0xC0AF000EL)

//
// MessageId: TLR_E_ECSV4_ESM_FUNCTION_NOT_SUPPORTED
//
// MessageText:
//
//  Function not supported.
//
#define TLR_E_ECSV4_ESM_FUNCTION_NOT_SUPPORTED ((TLR_RESULT)0xC0AF000FL)

//
// MessageId: TLR_E_ECSV4_ESM_FUNCTION_NOT_ALLOWED
//
// MessageText:
//
//  Function not allowed.
//
#define TLR_E_ECSV4_ESM_FUNCTION_NOT_ALLOWED ((TLR_RESULT)0xC0AF0010L)

//
// MessageId: TLR_E_ECSV4_ESM_SM_LENGTH_NOT_ALIGNED
//
// MessageText:
//
//  Function not allowed.
//
#define TLR_E_ECSV4_ESM_SM_LENGTH_NOT_ALIGNED ((TLR_RESULT)0xC0AF0011L)

//
// MessageId: TLR_E_ECSV4_ESM_SM_LENGTH_NOT_ALIGNED
//
// MessageText:
//
//  Function not allowed.
//
#define TLR_E_ECSV4_ESM_SUMM_OF_SM_LENGTH_EXCEED_MAX_SIZE ((TLR_RESULT)0xC0AF0012L)

//
// MessageId: TLR_E_ECSV4_ESM_WRONG_SM_STARTADRESS
//
// MessageText:
//
//  Function not allowed.
//
#define TLR_E_ECSV4_ESM_WRONG_SM_STARTADRESS ((TLR_RESULT)0xC0AF0013L)

//
// MessageId: TLR_E_ECSV4_ESM_FOE_TIMEOUT_TOO_SMALL
//
// MessageText:
//
//  Function not allowed.
//
#define TLR_E_ECSV4_ESM_FOE_TIMEOUT_TOO_SMALL ((TLR_RESULT)0xC0AF00A0L)

//
// MessageId: TLR_E_ECSV4_ESM_OBJECTDICTIONARY_INDICATION_TIMEOUT_TOO_SMALL
//
// MessageText:
//
//  Function not allowed.
//
#define TLR_E_ECSV4_ESM_OBJECTDICTIONARY_INDICATION_TIMEOUT_TOO_SMALL ((TLR_RESULT)0xC0AF00B0L)



/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 MBX error codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_ECSV4_MBX_INITIALIZATION_INVALID
//
// MessageText:
//
//  Mailbox initialization invalid.
//
#define TLR_E_ECSV4_MBX_INITIALIZATION_INVALID ((TLR_RESULT)0xC0B00001L)

//
// MessageId: TLR_E_ECSV4_MBX_MAILBOX_NOT_ACTIVE
//
// MessageText:
//
//  Mailbox is not active.
//
#define TLR_E_ECSV4_MBX_MAILBOX_NOT_ACTIVE ((TLR_RESULT)0xC0B00002L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 CoE SDO abort codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_TOGGLE_BIT_NOT_CHANGED
//
// MessageText:
//
//  Toggle bit was not changed.
//
#define TLR_E_ECSV4_COE_SDOABORT_TOGGLE_BIT_NOT_CHANGED ((TLR_RESULT)0xC0B10001L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_SDO_PROTOCOL_TIMEOUT
//
// MessageText:
//
//  SDO protocol timeout.
//
#define TLR_E_ECSV4_COE_SDOABORT_SDO_PROTOCOL_TIMEOUT ((TLR_RESULT)0xC0B10002L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_CLIENT_SERVER_COMMAND_SPECIFIER_NOT_VALID
//
// MessageText:
//
//  Client/Server command specifier not valid or unknown.
//
#define TLR_E_ECSV4_COE_SDOABORT_CLIENT_SERVER_COMMAND_SPECIFIER_NOT_VALID ((TLR_RESULT)0xC0B10003L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_OUT_OF_MEMORY
//
// MessageText:
//
//  Out of memory.
//
#define TLR_E_ECSV4_COE_SDOABORT_OUT_OF_MEMORY ((TLR_RESULT)0xC0B10004L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_UNSUPPORTED_ACCESS_TO_AN_OBJECT
//
// MessageText:
//
//  Unsupported access to an object.
//
#define TLR_E_ECSV4_COE_SDOABORT_UNSUPPORTED_ACCESS_TO_AN_OBJECT ((TLR_RESULT)0xC0B10005L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_ATTEMPT_TO_READ_A_WRITE_ONLY_OBJECT
//
// MessageText:
//
//  Attempt to read a write only object.
//
#define TLR_E_ECSV4_COE_SDOABORT_ATTEMPT_TO_READ_A_WRITE_ONLY_OBJECT ((TLR_RESULT)0xC0B10006L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_ATTEMPT_TO_WRITE_TO_A_READ_ONLY_OBJECT
//
// MessageText:
//
//  Attempt to write to a read only object.
//
#define TLR_E_ECSV4_COE_SDOABORT_ATTEMPT_TO_WRITE_TO_A_READ_ONLY_OBJECT ((TLR_RESULT)0xC0B10007L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_OBJECT_DOES_NOT_EXIST
//
// MessageText:
//
//  The object does not exist in the object dictionary.
//
#define TLR_E_ECSV4_COE_SDOABORT_OBJECT_DOES_NOT_EXIST ((TLR_RESULT)0xC0B10008L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_OBJECT_CAN_NOT_BE_MAPPED_INTO_THE_PDO
//
// MessageText:
//
//  The object can not be mapped into the PDO.
//
#define TLR_E_ECSV4_COE_SDOABORT_OBJECT_CAN_NOT_BE_MAPPED_INTO_THE_PDO ((TLR_RESULT)0xC0B10009L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_NUMBER_AND_LENGTH_OF_OBJECTS_WOULD_EXCEED_PDO_LENGTH
//
// MessageText:
//
//  The number and length of the objects to be mapped would exceed the PDO length.
//
#define TLR_E_ECSV4_COE_SDOABORT_NUMBER_AND_LENGTH_OF_OBJECTS_WOULD_EXCEED_PDO_LENGTH ((TLR_RESULT)0xC0B1000AL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_GENERAL_PARAMETER_INCOMPATIBILITY_REASON
//
// MessageText:
//
//  General parameter incompatibility reason.
//
#define TLR_E_ECSV4_COE_SDOABORT_GENERAL_PARAMETER_INCOMPATIBILITY_REASON ((TLR_RESULT)0xC0B1000BL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_GENERAL_INTERNAL_INCOMPATIBILITY_IN_DEVICE
//
// MessageText:
//
//  General internal incompatibility in the device.
//
#define TLR_E_ECSV4_COE_SDOABORT_GENERAL_INTERNAL_INCOMPATIBILITY_IN_DEVICE ((TLR_RESULT)0xC0B1000CL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_ACCESS_FAILED_DUE_TO_A_HARDWARE_ERROR
//
// MessageText:
//
//  Access failed due to a hardware error.
//
#define TLR_E_ECSV4_COE_SDOABORT_ACCESS_FAILED_DUE_TO_A_HARDWARE_ERROR ((TLR_RESULT)0xC0B1000DL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_DATA_TYPE_DOES_NOT_MATCH_LEN_OF_SRV_PARAM_DOES_NOT_MATCH
//
// MessageText:
//
//  Data type does not match, length of service parameter does not match.
//
#define TLR_E_ECSV4_COE_SDOABORT_DATA_TYPE_DOES_NOT_MATCH_LEN_OF_SRV_PARAM_DOES_NOT_MATCH ((TLR_RESULT)0xC0B1000EL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_DATA_TYPE_DOES_NOT_MATCH_LEN_OF_SRV_PARAM_TOO_HIGH
//
// MessageText:
//
//  Data type does not match, length of service parameter too high.
//
#define TLR_E_ECSV4_COE_SDOABORT_DATA_TYPE_DOES_NOT_MATCH_LEN_OF_SRV_PARAM_TOO_HIGH ((TLR_RESULT)0xC0B1000FL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_DATA_TYPE_DOES_NOT_MATCH_LEN_OF_SRV_PARAM_TOO_LOW
//
// MessageText:
//
//  Data type does not match, length of service parameter too low.
//
#define TLR_E_ECSV4_COE_SDOABORT_DATA_TYPE_DOES_NOT_MATCH_LEN_OF_SRV_PARAM_TOO_LOW ((TLR_RESULT)0xC0B10010L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_SUBINDEX_DOES_NOT_EXIST
//
// MessageText:
//
//  Subindex does not exist.
//
#define TLR_E_ECSV4_COE_SDOABORT_SUBINDEX_DOES_NOT_EXIST ((TLR_RESULT)0xC0B10011L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_VALUE_RANGE_OF_PARAMETER_EXCEEDED
//
// MessageText:
//
//  Value range of parameter exceeded (only for write access).
//
#define TLR_E_ECSV4_COE_SDOABORT_VALUE_RANGE_OF_PARAMETER_EXCEEDED ((TLR_RESULT)0xC0B10012L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_VALUE_OF_PARAMETER_WRITTEN_TOO_HIGH
//
// MessageText:
//
//  Value of parameter written too high.
//
#define TLR_E_ECSV4_COE_SDOABORT_VALUE_OF_PARAMETER_WRITTEN_TOO_HIGH ((TLR_RESULT)0xC0B10013L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_VALUE_OF_PARAMETER_WRITTEN_TOO_LOW
//
// MessageText:
//
//  Value of parameter written too low.
//
#define TLR_E_ECSV4_COE_SDOABORT_VALUE_OF_PARAMETER_WRITTEN_TOO_LOW ((TLR_RESULT)0xC0B10014L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_MAXIMUM_VALUE_IS_LESS_THAN_MINIMUM_VALUE
//
// MessageText:
//
//  Maximum value is less than minimum value.
//
#define TLR_E_ECSV4_COE_SDOABORT_MAXIMUM_VALUE_IS_LESS_THAN_MINIMUM_VALUE ((TLR_RESULT)0xC0B10015L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_GENERAL_ERROR
//
// MessageText:
//
//  General error.
//
#define TLR_E_ECSV4_COE_SDOABORT_GENERAL_ERROR ((TLR_RESULT)0xC0B10016L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_DATA_CANNOT_BE_TRANSFERRED_OR_STORED_TO_THE_APP
//
// MessageText:
//
//  Data cannot be transferred or stored to the application.
//
#define TLR_E_ECSV4_COE_SDOABORT_DATA_CANNOT_BE_TRANSFERRED_OR_STORED_TO_THE_APP ((TLR_RESULT)0xC0B10017L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_DATA_CANNOT_BE_TRANSFERRED_OR_STORED_DUE_TO_LOCAL_CONTROL
//
// MessageText:
//
//  Data cannot be transferred or stored to the application because of local control.
//
#define TLR_E_ECSV4_COE_SDOABORT_DATA_CANNOT_BE_TRANSFERRED_OR_STORED_DUE_TO_LOCAL_CONTROL ((TLR_RESULT)0xC0B10018L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_DATA_CANNOT_BE_TRANSFERRED_OR_STORED_DUE_TO_PRESENT_DEVICE_STATE
//
// MessageText:
//
//  Data cannot be transferred or stored to the application because of the present device state.
//
#define TLR_E_ECSV4_COE_SDOABORT_DATA_CANNOT_BE_TRANSFERRED_OR_STORED_DUE_TO_PRESENT_DEVICE_STATE ((TLR_RESULT)0xC0B10019L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_NO_OBJECT_DICTIONARY_PRESENT
//
// MessageText:
//
//  Object dictionary dynamic generation fails or no object dictionary is present.
//
#define TLR_E_ECSV4_COE_SDOABORT_NO_OBJECT_DICTIONARY_PRESENT ((TLR_RESULT)0xC0B1001AL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_UNKNOWN_ABORT_CODE
//
// MessageText:
//
//  Unknown SDO abort code.
//
#define TLR_E_ECSV4_COE_SDOABORT_UNKNOWN_ABORT_CODE ((TLR_RESULT)0xC0B1001BL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_SUBINDEX_CANNOT_BE_WRITTEN_SI0_MUST_BE_0
//
// MessageText:
//
//  Subindex cannot be written, Subindex 0 must be 0 for write access.
//
#define TLR_E_ECSV4_COE_SDOABORT_SUBINDEX_CANNOT_BE_WRITTEN_SI0_MUST_BE_0 ((TLR_RESULT)0xC0B1001EL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_COMPLETE_ACCESS_NOT_SUPPORTED
//
// MessageText:
//
//  Complete Access not supported.
//
#define TLR_E_ECSV4_COE_SDOABORT_COMPLETE_ACCESS_NOT_SUPPORTED ((TLR_RESULT)0xC0B1001FL)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_OBJECT_MAPPED_TO_RXPDO_DOWNLOAD_BLOCKED
//
// MessageText:
//
//  Object mapped to RxPDO. SDO Download blocked.
//
#define TLR_E_ECSV4_COE_SDOABORT_OBJECT_MAPPED_TO_RXPDO_DOWNLOAD_BLOCKED ((TLR_RESULT)0xC0B10020L)

//
// MessageId: TLR_E_ECSV4_COE_SDOABORT_OBJECT_LENGTH_EXCEEDS_MAILBOX_SIZE
//
// MessageText:
//
//  Object length exceeds mailbox size.
//
#define TLR_E_ECSV4_COE_SDOABORT_OBJECT_LENGTH_EXCEEDS_MAILBOX_SIZE ((TLR_RESULT)0xC0B10021L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 CoE error codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_ECSV4_COE_EMERGENCY_MESSAGE_COULD_NOT_BE_SENT
//
// MessageText:
//
//  CoE emergency message could not be sent.
//
#define TLR_E_ECSV4_COE_EMERGENCY_MESSAGE_COULD_NOT_BE_SENT ((TLR_RESULT)0xC0B1001CL)

//
// MessageId: TLR_E_ECSV4_COE_EMERGENCY_MESSAGE_HAS_INVALID_PRIORITY
//
// MessageText:
//
//  CoE emergency message has invalid priority.
//
#define TLR_E_ECSV4_COE_EMERGENCY_MESSAGE_HAS_INVALID_PRIORITY ((TLR_RESULT)0xC0B1001DL)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 EoE error codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_ECSV4_EOE_INVALID_TIMEOUT_PARAMS
//
// MessageText:
//
//  Invalid timeout parameters.
//
#define TLR_E_ECSV4_EOE_INVALID_TIMEOUT_PARAMS ((TLR_RESULT)0xC0B20001L)

//
// MessageId: TLR_E_ECSV4_EOE_PARAM_UNSUPPORTED_FRAME_TYPE
//
// MessageText:
//
//  Unsupported frame type.
//
#define TLR_E_ECSV4_EOE_PARAM_UNSUPPORTED_FRAME_TYPE ((TLR_RESULT)0xC0B20002L)

//
// MessageId: TLR_E_ECSV4_EOE_PARAM_NO_IP_SUPPORT
//
// MessageText:
//
//  No IP Support.
//
#define TLR_E_ECSV4_EOE_PARAM_NO_IP_SUPPORT ((TLR_RESULT)0xC0B20003L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 EoE diagnostic codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_DIAG_E_ECSV4_EOE_FAILED_TO_IDENTIFY_TCPIP_QUEUE
//
// MessageText:
//
//  Failed to identify TCP/IP queue.
//
#define TLR_DIAG_E_ECSV4_EOE_FAILED_TO_IDENTIFY_TCPIP_QUEUE ((TLR_RESULT)0xC0B20004L)

//
// MessageId: TLR_DIAG_E_ECSV4_EOE_FAILED_TO_GET_PACKET
//
// MessageText:
//
//  Failed to get a packet from pool.
//
#define TLR_DIAG_E_ECSV4_EOE_FAILED_TO_GET_PACKET ((TLR_RESULT)0xC0B20005L)

//
// MessageId: TLR_DIAG_E_ECSV4_EOE_FAILED_TO_EXCHANGE_PACKET
//
// MessageText:
//
//  Failed to exchange packet.
//
#define TLR_DIAG_E_ECSV4_EOE_FAILED_TO_EXCHANGE_PACKET ((TLR_RESULT)0xC0B20006L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 FoE error codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_ECSV4_FOE_INVALID_TIMEOUT_PARAMS
//
// MessageText:
//
//  Invalid timeout parameters.
//
#define TLR_E_ECSV4_FOE_INVALID_TIMEOUT_PARAMS ((TLR_RESULT)0xC0B30001L)

//
// MessageId: TLR_E_ECSV4_FOE_INVALID_OPCODE
//
// MessageText:
//
//  Invalid opcode.
//
#define TLR_E_ECSV4_FOE_INVALID_OPCODE   ((TLR_RESULT)0xC0B30002L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 SoE error codes
/////////////////////////////////////////////////////////////////////////////////////
//Range 0x1000-0x7FFF is reserved for SSC error mapping
//Range 0x8000-0x8FFF is reserved for default value error codes
//
// MessageId: TLR_E_ECSV4_SOE_IDN_ALREADY_EXISTS
//
// MessageText:
//
//  IDN already exists.
//
#define TLR_E_ECSV4_SOE_IDN_ALREADY_EXISTS ((TLR_RESULT)0xC0B40001L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_ATTRIBUTE_INVALID
//
// MessageText:
//
//  Attribute invalid.
//
#define TLR_E_ECSV4_SOE_IDN_ATTRIBUTE_INVALID ((TLR_RESULT)0xC0B40002L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_INVALID_MAX_DATA_SIZE_SPECIFIED
//
// MessageText:
//
//  Invalid maximal data size specified.
//
#define TLR_E_ECSV4_SOE_IDN_INVALID_MAX_DATA_SIZE_SPECIFIED ((TLR_RESULT)0xC0B40003L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_DRIVE_NUMBER_INVALID
//
// MessageText:
//
//  Drive number invalid.
//
#define TLR_E_ECSV4_SOE_IDN_DRIVE_NUMBER_INVALID ((TLR_RESULT)0xC0B40004L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_UNDEFINED_NOTIFY_ALREADY_IN_USE
//
// MessageText:
//
//  Undefined notify already in use.
//
#define TLR_E_ECSV4_SOE_IDN_UNDEFINED_NOTIFY_ALREADY_IN_USE ((TLR_RESULT)0xC0B40005L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_INVALID_ELEMENT_ID
//
// MessageText:
//
//  Invalid element id.
//
#define TLR_E_ECSV4_SOE_IDN_INVALID_ELEMENT_ID ((TLR_RESULT)0xC0B40006L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_APP_PACKET_RESPONSE_INVALID
//
// MessageText:
//
//  Application's packet response invalid.
//
#define TLR_E_ECSV4_SOE_IDN_APP_PACKET_RESPONSE_INVALID ((TLR_RESULT)0xC0B40007L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_APP_SSC_TRANSFER_TOO_LONG
//
// MessageText:
//
//  Application's transfer too long.
//
#define TLR_E_ECSV4_SOE_IDN_APP_SSC_TRANSFER_TOO_LONG ((TLR_RESULT)0xC0B40008L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_APP_SSC_TRANSFER_LENGTH_WRONG
//
// MessageText:
//
//  Application's transfer length wrong.
//
#define TLR_E_ECSV4_SOE_IDN_APP_SSC_TRANSFER_LENGTH_WRONG ((TLR_RESULT)0xC0B40009L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_APP_MTU_TOO_LOW
//
// MessageText:
//
//  Application's MTU is too low.
//
#define TLR_E_ECSV4_SOE_IDN_APP_MTU_TOO_LOW ((TLR_RESULT)0xC0B4000AL)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_INVALID_DEST_ID
//
// MessageText:
//
//  Invalid destination ID.
//
#define TLR_E_ECSV4_SOE_IDN_INVALID_DEST_ID ((TLR_RESULT)0xC0B4000BL)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_LISTS_CANNOT_HAVE_A_MINIMUM_VALUE
//
// MessageText:
//
//  Lists cannot have a minimum value.
//
#define TLR_E_ECSV4_SOE_IDN_LISTS_CANNOT_HAVE_A_MINIMUM_VALUE ((TLR_RESULT)0xC0B4000CL)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_LISTS_CANNOT_HAVE_A_MAXIMUM_VALUE
//
// MessageText:
//
//  Lists cannot have a maximum value.
//
#define TLR_E_ECSV4_SOE_IDN_LISTS_CANNOT_HAVE_A_MAXIMUM_VALUE ((TLR_RESULT)0xC0B4000DL)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_NAME_EXCEEDS_ALLOCATED_LENGTH
//
// MessageText:
//
//  Name exceeds allocated length.
//
#define TLR_E_ECSV4_SOE_IDN_NAME_EXCEEDS_ALLOCATED_LENGTH ((TLR_RESULT)0xC0B4000EL)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_UNIT_EXCEEDS_ALLOCATED_LENGTH
//
// MessageText:
//
//  Unit exceeds allocated length.
//
#define TLR_E_ECSV4_SOE_IDN_UNIT_EXCEEDS_ALLOCATED_LENGTH ((TLR_RESULT)0xC0B4000FL)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_OPDATA_EXCEEDS_ALLOCATED_LENGTH
//
// MessageText:
//
//  OpData exceeds allocated length.
//
#define TLR_E_ECSV4_SOE_IDN_OPDATA_EXCEEDS_ALLOCATED_LENGTH ((TLR_RESULT)0xC0B40010L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_INVALID_MAX_LIST_LENGTH
//
// MessageText:
//
//  Invalid maximal list length.
//
#define TLR_E_ECSV4_SOE_IDN_INVALID_MAX_LIST_LENGTH ((TLR_RESULT)0xC0B40011L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_MINIMUM_AND_MAXIMUM_VALUE_MUST_BE_USED_TOGETHER
//
// MessageText:
//
//  Minimum and maximum value must be used together.
//
#define TLR_E_ECSV4_SOE_IDN_MINIMUM_AND_MAXIMUM_VALUE_MUST_BE_USED_TOGETHER ((TLR_RESULT)0xC0B40012L)

//
// MessageId: TLR_E_ECSV4_SOE_IDN_USER_APPLICATION_TRANSFER_ERROR
//
// MessageText:
//
//  User application transfer error.
//
#define TLR_E_ECSV4_SOE_IDN_USER_APPLICATION_TRANSFER_ERROR ((TLR_RESULT)0xC0B40013L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NO_IDN
//
// MessageText:
//
//  No IDN.
//
#define TLR_E_ECSV4_SOE_SSC_NO_IDN       ((TLR_RESULT)0xC0B41001L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_INVALID_ACCESS_TO_ELEMENT_1
//
// MessageText:
//
//  Invalid access to element 1.
//
#define TLR_E_ECSV4_SOE_SSC_INVALID_ACCESS_TO_ELEMENT_1 ((TLR_RESULT)0xC0B41009L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NO_NAME
//
// MessageText:
//
//  No Name.
//
#define TLR_E_ECSV4_SOE_SSC_NO_NAME      ((TLR_RESULT)0xC0B42001L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NAME_TRANSMISSION_IS_TOO_SHORT
//
// MessageText:
//
//  Name transmission is too short.
//
#define TLR_E_ECSV4_SOE_SSC_NAME_TRANSMISSION_IS_TOO_SHORT ((TLR_RESULT)0xC0B42002L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NAME_TRANSMISSION_IS_TOO_LONG
//
// MessageText:
//
//  Name transmission is too long.
//
#define TLR_E_ECSV4_SOE_SSC_NAME_TRANSMISSION_IS_TOO_LONG ((TLR_RESULT)0xC0B42003L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NAME_CANNOT_BE_CHANGED
//
// MessageText:
//
//  Name cannot be changed (read only).
//
#define TLR_E_ECSV4_SOE_SSC_NAME_CANNOT_BE_CHANGED ((TLR_RESULT)0xC0B42004L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NAME_IS_WRITE_PROTECTED_AT_THIS_TIME
//
// MessageText:
//
//  Name is write-protected at this time.
//
#define TLR_E_ECSV4_SOE_SSC_NAME_IS_WRITE_PROTECTED_AT_THIS_TIME ((TLR_RESULT)0xC0B42005L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_ATTRIBUTE_TRANSMISSION_IS_TOO_SHORT
//
// MessageText:
//
//  Attribute transmission is too short.
//
#define TLR_E_ECSV4_SOE_SSC_ATTRIBUTE_TRANSMISSION_IS_TOO_SHORT ((TLR_RESULT)0xC0B43002L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_ATTRIBUTE_TRANSMISSION_IS_TOO_LONG
//
// MessageText:
//
//  Attribute transmission is too long.
//
#define TLR_E_ECSV4_SOE_SSC_ATTRIBUTE_TRANSMISSION_IS_TOO_LONG ((TLR_RESULT)0xC0B43003L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_ATTRIBUTE_CANNOT_BE_CHANGED
//
// MessageText:
//
//  Attribute cannot be changed (read only).
//
#define TLR_E_ECSV4_SOE_SSC_ATTRIBUTE_CANNOT_BE_CHANGED ((TLR_RESULT)0xC0B43004L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_ATTRIBUTE_IS_WRITE_PROTECTED_AT_THIS_TIME
//
// MessageText:
//
//  Attribute is write-protected at this time.
//
#define TLR_E_ECSV4_SOE_SSC_ATTRIBUTE_IS_WRITE_PROTECTED_AT_THIS_TIME ((TLR_RESULT)0xC0B43005L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NO_UNITS
//
// MessageText:
//
//  No units.
//
#define TLR_E_ECSV4_SOE_SSC_NO_UNITS     ((TLR_RESULT)0xC0B44001L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_UNIT_TRANSMISSION_IS_TOO_SHORT
//
// MessageText:
//
//  Unit transmission is too short.
//
#define TLR_E_ECSV4_SOE_SSC_UNIT_TRANSMISSION_IS_TOO_SHORT ((TLR_RESULT)0xC0B44002L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_UNIT_TRANSMISSION_IS_TOO_LONG
//
// MessageText:
//
//  Unit transmission is too long.
//
#define TLR_E_ECSV4_SOE_SSC_UNIT_TRANSMISSION_IS_TOO_LONG ((TLR_RESULT)0xC0B44003L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_UNIT_CANNOT_BE_CHANGED
//
// MessageText:
//
//  Unit cannot be changed (read only).
//
#define TLR_E_ECSV4_SOE_SSC_UNIT_CANNOT_BE_CHANGED ((TLR_RESULT)0xC0B44004L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_UNIT_IS_WRITE_PROTECTED_AT_THIS_TIME
//
// MessageText:
//
//  Unit is write-protected at this time.
//
#define TLR_E_ECSV4_SOE_SSC_UNIT_IS_WRITE_PROTECTED_AT_THIS_TIME ((TLR_RESULT)0xC0B44005L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NO_MINIMUM_INPUT_VALUE
//
// MessageText:
//
//  No minimum input value.
//
#define TLR_E_ECSV4_SOE_SSC_NO_MINIMUM_INPUT_VALUE ((TLR_RESULT)0xC0B45001L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_MINIMUM_INPUT_VALUE_TRANSMISSION_IS_TOO_SHORT
//
// MessageText:
//
//  Minimum input value transmission is too short.
//
#define TLR_E_ECSV4_SOE_SSC_MINIMUM_INPUT_VALUE_TRANSMISSION_IS_TOO_SHORT ((TLR_RESULT)0xC0B45002L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_MINIMUM_INPUT_VALUE_TRANSMISSION_IS_TOO_LONG
//
// MessageText:
//
//  Minimum input value transmission is too long.
//
#define TLR_E_ECSV4_SOE_SSC_MINIMUM_INPUT_VALUE_TRANSMISSION_IS_TOO_LONG ((TLR_RESULT)0xC0B45003L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_MINIMUM_INPUT_VALUE_CANNOT_BE_CHANGED
//
// MessageText:
//
//  Minimum input value cannot be changed (read only).
//
#define TLR_E_ECSV4_SOE_SSC_MINIMUM_INPUT_VALUE_CANNOT_BE_CHANGED ((TLR_RESULT)0xC0B45004L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_MINIMUM_INPUT_VALUE_IS_WRITE_PROTECTED_AT_THIS_TIME
//
// MessageText:
//
//  Minimum input value is write-protected at this time.
//
#define TLR_E_ECSV4_SOE_SSC_MINIMUM_INPUT_VALUE_IS_WRITE_PROTECTED_AT_THIS_TIME ((TLR_RESULT)0xC0B45005L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NO_MAXIMUM_INPUT_VALUE
//
// MessageText:
//
//  No maximum input value.
//
#define TLR_E_ECSV4_SOE_SSC_NO_MAXIMUM_INPUT_VALUE ((TLR_RESULT)0xC0B46001L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_MAXIMUM_INPUT_VALUE_TRANSMISSION_IS_TOO_SHORT
//
// MessageText:
//
//  Maximum input value transmission is too short.
//
#define TLR_E_ECSV4_SOE_SSC_MAXIMUM_INPUT_VALUE_TRANSMISSION_IS_TOO_SHORT ((TLR_RESULT)0xC0B46002L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_MAXIMUM_INPUT_VALUE_TRANSMISSION_IS_TOO_LONG
//
// MessageText:
//
//  Maximum input value transmission is too long.
//
#define TLR_E_ECSV4_SOE_SSC_MAXIMUM_INPUT_VALUE_TRANSMISSION_IS_TOO_LONG ((TLR_RESULT)0xC0B46003L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_MAXIMUM_INPUT_VALUE_CANNOT_BE_CHANGED
//
// MessageText:
//
//  Maximum input value cannot be changed (read only).
//
#define TLR_E_ECSV4_SOE_SSC_MAXIMUM_INPUT_VALUE_CANNOT_BE_CHANGED ((TLR_RESULT)0xC0B46004L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_MAXIMUM_INPUT_VALUE_IS_WRITE_PROTECTED_AT_THIS_TIME
//
// MessageText:
//
//  Maximum input value is write-protected at this time.
//
#define TLR_E_ECSV4_SOE_SSC_MAXIMUM_INPUT_VALUE_IS_WRITE_PROTECTED_AT_THIS_TIME ((TLR_RESULT)0xC0B46005L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_TRANSMISSION_IS_TOO_SHORT
//
// MessageText:
//
//  Operation data transmission is too short.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_TRANSMISSION_IS_TOO_SHORT ((TLR_RESULT)0xC0B47002L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_TRANSMISSION_IS_TOO_LONG
//
// MessageText:
//
//  Operation data transmission is too long.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_TRANSMISSION_IS_TOO_LONG ((TLR_RESULT)0xC0B47003L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_CANNOT_BE_CHANGED
//
// MessageText:
//
//  Operation data cannot be changed (read only).
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_CANNOT_BE_CHANGED ((TLR_RESULT)0xC0B47004L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_AT_THIS_TIME
//
// MessageText:
//
//  Operation data is write-protected at this time.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_AT_THIS_TIME ((TLR_RESULT)0xC0B47005L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_LOWER_THAN_MINIMUM_VALUE
//
// MessageText:
//
//  Operation data is lower than minimum input value.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_LOWER_THAN_MINIMUM_VALUE ((TLR_RESULT)0xC0B47006L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_HIGHER_THAN_MAXIMUM_VALUE
//
// MessageText:
//
//  Operation data is higher than maximum input value.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_HIGHER_THAN_MAXIMUM_VALUE ((TLR_RESULT)0xC0B47007L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_INVALID
//
// MessageText:
//
//  Invalid operation data.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_INVALID ((TLR_RESULT)0xC0B47008L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_BY_PASSWORD
//
// MessageText:
//
//  Operation data is write-protected by a password.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_BY_PASSWORD ((TLR_RESULT)0xC0B47009L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_DUE_CYCLICALLY_CONFIGURED
//
// MessageText:
//
//  Operation data is write-protected, it is configured cyclically.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_DUE_CYCLICALLY_CONFIGURED ((TLR_RESULT)0xC0B4700AL)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_INVALID_INDIRECT_ADDRESSING
//
// MessageText:
//
//  Invalid indirect addressing.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_INVALID_INDIRECT_ADDRESSING ((TLR_RESULT)0xC0B4700BL)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_DUE_TO_OTHER_SETTINGS
//
// MessageText:
//
//  Operation data is write-protected due to other settings.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_DUE_TO_OTHER_SETTINGS ((TLR_RESULT)0xC0B4700CL)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_INVALID_FLOATING_POINT_NUMBER
//
// MessageText:
//
//  Invalid floating point number.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_INVALID_FLOATING_POINT_NUMBER ((TLR_RESULT)0xC0B4700DL)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_AT_PARAMETERIZATION_LEVEL
//
// MessageText:
//
//  Operation data is write-protected at parameterization level.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_AT_PARAMETERIZATION_LEVEL ((TLR_RESULT)0xC0B4700EL)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_AT_OPERATION_LEVEL
//
// MessageText:
//
//  Operation data is write-protected at operation level.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_IS_WRITE_PROTECTED_AT_OPERATION_LEVEL ((TLR_RESULT)0xC0B4700FL)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_PROCEDURE_COMMAND_ALREADY_ACTIVE
//
// MessageText:
//
//  Procedure command already active.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_PROCEDURE_COMMAND_ALREADY_ACTIVE ((TLR_RESULT)0xC0B47010L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_PROCEDURE_COMMAND_NOT_INTERRUPTIBLE
//
// MessageText:
//
//  Procedure command not interruptible.
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_PROCEDURE_COMMAND_NOT_INTERRUPTIBLE ((TLR_RESULT)0xC0B47011L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_PROCEDURE_COMMAND_NOT_EXECUTABLE_AT_THIS_TIME
//
// MessageText:
//
//  Procedure command at this time not executable (e.g. in this phase the procedure command can not be activated).
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_PROCEDURE_COMMAND_NOT_EXECUTABLE_AT_THIS_TIME ((TLR_RESULT)0xC0B47012L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_OPDATA_PROCEDURE_COMMAND_NOT_EXECUTABLE_INVALID_PARAM
//
// MessageText:
//
//  Procedure command not executable (invalid or false parameters).
//
#define TLR_E_ECSV4_SOE_SSC_OPDATA_PROCEDURE_COMMAND_NOT_EXECUTABLE_INVALID_PARAM ((TLR_RESULT)0xC0B47013L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_NO_DEFAULT_VALUE
//
// MessageText:
//
//  No default value.
//
#define TLR_E_ECSV4_SOE_SSC_NO_DEFAULT_VALUE ((TLR_RESULT)0xC0B48001L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_DEFAULT_VALUE_TRANSMISSION_IS_TOO_SHORT
//
// MessageText:
//
//  Default value transmission is too short.
//
#define TLR_E_ECSV4_SOE_SSC_DEFAULT_VALUE_TRANSMISSION_IS_TOO_SHORT ((TLR_RESULT)0xC0B48002L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_DEFAULT_VALUE_TRANSMISSION_IS_TOO_LONG
//
// MessageText:
//
//  Default value transmission is too long.
//
#define TLR_E_ECSV4_SOE_SSC_DEFAULT_VALUE_TRANSMISSION_IS_TOO_LONG ((TLR_RESULT)0xC0B48003L)

//
// MessageId: TLR_E_ECSV4_SOE_SSC_DEFAULT_VALUE_CANNOT_BE_CHANGED
//
// MessageText:
//
//  Default value cannot be changed (read only).
//
#define TLR_E_ECSV4_SOE_SSC_DEFAULT_VALUE_CANNOT_BE_CHANGED ((TLR_RESULT)0xC0B48004L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 DPM diagnostic codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_DIAG_E_ECSV4_DPM_WATCHDOG_TRIGGERED
//
// MessageText:
//
//  DPM watchdog triggered.
//
#define TLR_DIAG_E_ECSV4_DPM_WATCHDOG_TRIGGERED ((TLR_RESULT)0xC0AE0001L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 DPM error codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_ECSV4_DPM_REQUEST_ABORTED
//
// MessageText:
//
//  Request has been aborted.
//
#define TLR_E_ECSV4_DPM_REQUEST_ABORTED  ((TLR_RESULT)0xC0AE0002L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_GENERAL_ERROR
//
// MessageText:
//
//  Unknown error while parsing database.
//
#define TLR_E_ECSV4_DPM_NXD_GENERAL_ERROR ((TLR_RESULT)0xC0AE0003L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_NOT_AVAILABLE
//
// MessageText:
//
//  No database available.
//
#define TLR_E_ECSV4_DPM_NXD_NOT_AVAILABLE ((TLR_RESULT)0xC0AE0004L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_NXD_TYPE
//
// MessageText:
//
//  Not an EtherCAT slave database.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_NXD_TYPE ((TLR_RESULT)0xC0AE0005L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_STRUCTURE
//
// MessageText:
//
//  Invalid database structure.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_STRUCTURE ((TLR_RESULT)0xC0AE0006L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_NXD_VERSION
//
// MessageText:
//
//  Invalid database version.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_NXD_VERSION ((TLR_RESULT)0xC0AE0007L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_ECS_CONFIG
//
// MessageText:
//
//  Invalid EtherCAT slave stack configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_ECS_CONFIG ((TLR_RESULT)0xC0AE0008L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM_CONFIG ((TLR_RESULT)0xC0AE0009L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM0_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 0 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM0_CONFIG ((TLR_RESULT)0xC0AE000AL)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM1_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 1 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM1_CONFIG ((TLR_RESULT)0xC0AE000BL)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM2_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 2 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM2_CONFIG ((TLR_RESULT)0xC0AE000CL)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM3_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 3 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM3_CONFIG ((TLR_RESULT)0xC0AE000DL)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM4_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 4 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM4_CONFIG ((TLR_RESULT)0xC0AE000EL)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM5_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 5 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM5_CONFIG ((TLR_RESULT)0xC0AE000FL)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM6_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 6 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM6_CONFIG ((TLR_RESULT)0xC0AE0010L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM7_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 7 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM7_CONFIG ((TLR_RESULT)0xC0AE0011L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_SM8_CONFIG
//
// MessageText:
//
//  Invalid Sync Manager 8 configuration.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_SM8_CONFIG ((TLR_RESULT)0xC0AE0012L)

//
// MessageId: TLR_E_ECSV4_DPM_NXD_INVALID_HSK_CONFIG
//
// MessageText:
//
//  Invalid configuration of process data handshakes.
//
#define TLR_E_ECSV4_DPM_NXD_INVALID_HSK_CONFIG ((TLR_RESULT)0xC0AE0013L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 AoE_General error code for ETG5001 Annex.K
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: TLR_E_ECSV4_AOE_MDP_GENERAL_ERROR
//
// MessageText:
//
//  High word is general error low word comming from MDP profile devices like IOLink master
//
#define TLR_E_ECSV4_AOE_MDP_GENERAL_ERROR ((TLR_RESULT)0xC0F00001L)


#endif  //__ECSV4_ERROR_H

