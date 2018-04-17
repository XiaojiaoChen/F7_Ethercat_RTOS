#ifndef __CIFXERRORS_H__
#define __CIFXERRORS_H__

/*******************************************************************************
* CIF Device Driver Errors
*******************************************************************************/
/*  */
/*   Values are 32 bit values laid out as follows: */
/*  */
/*    3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 */
/*    1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 */
/*   +---+-+-+-----------------------+-------------------------------+ */
/*   |Sev|C|R|     Facility          |               Code            | */
/*   +---+-+-+-----------------------+-------------------------------+ */
/*  */
/*   where */
/*  */
/*       Sev - is the severity code */
/*  */
/*           00 - Success */
/*           01 - Informational */
/*           10 - Warning */
/*           11 - Error */
/*  */
/*       C - is the Customer code flag */
/*  */
/*       R - is a reserved bit */
/*  */
/*       Facility - is the facility code */
/*  */
/*       Code - is the facility's status code */
/*  */
/*  */
/*  Define the facility codes */
/*  */


/*  */
/*  Define the severity codes */
/*  */


/*  */
/*  MessageId: CIFX_NO_ERROR */
/*  */
/*  MessageText: */
/*  */
/*  No Error */
/*  */
#define CIFX_NO_ERROR                    ((int32_t)0x00000000L)

/*******************************************************************************
* Generic Errors
*******************************************************************************/
/*  */
/*  MessageId: CIFX_INVALID_POINTER */
/*  */
/*  MessageText: */
/*  */
/*  Invalid pointer (e.g. NULL) passed to driver */
/*  */
#define CIFX_INVALID_POINTER             ((int32_t)0x800A0001L)

/*  */
/*  MessageId: CIFX_INVALID_BOARD */
/*  */
/*  MessageText: */
/*  */
/*  No board with the given name / index available */
/*  */
#define CIFX_INVALID_BOARD               ((int32_t)0x800A0002L)

/*  */
/*  MessageId: CIFX_INVALID_CHANNEL */
/*  */
/*  MessageText: */
/*  */
/*  No channel with the given index available */
/*  */
#define CIFX_INVALID_CHANNEL             ((int32_t)0x800A0003L)

/*  */
/*  MessageId: CIFX_INVALID_HANDLE */
/*  */
/*  MessageText: */
/*  */
/*  Invalid handle passed to driver */
/*  */
#define CIFX_INVALID_HANDLE              ((int32_t)0x800A0004L)

/*  */
/*  MessageId: CIFX_INVALID_PARAMETER */
/*  */
/*  MessageText: */
/*  */
/*  Invalid parameter */
/*  */
#define CIFX_INVALID_PARAMETER           ((int32_t)0x800A0005L)

/*  */
/*  MessageId: CIFX_INVALID_COMMAND */
/*  */
/*  MessageText: */
/*  */
/*  Invalid command */
/*  */
#define CIFX_INVALID_COMMAND             ((int32_t)0x800A0006L)

/*  */
/*  MessageId: CIFX_INVALID_BUFFERSIZE */
/*  */
/*  MessageText: */
/*  */
/*  Invalid buffer size */
/*  */
#define CIFX_INVALID_BUFFERSIZE          ((int32_t)0x800A0007L)

/*  */
/*  MessageId: CIFX_INVALID_ACCESS_SIZE */
/*  */
/*  MessageText: */
/*  */
/*  Invalid access size */
/*  */
#define CIFX_INVALID_ACCESS_SIZE         ((int32_t)0x800A0008L)

/*  */
/*  MessageId: CIFX_FUNCTION_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  Function failed */
/*  */
#define CIFX_FUNCTION_FAILED             ((int32_t)0x800A0009L)

/*  */
/*  MessageId: CIFX_FILE_OPEN_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  File could not be opened */
/*  */
#define CIFX_FILE_OPEN_FAILED            ((int32_t)0x800A000AL)

/*  */
/*  MessageId: CIFX_FILE_SIZE_ZERO */
/*  */
/*  MessageText: */
/*  */
/*  File size is zero */
/*  */
#define CIFX_FILE_SIZE_ZERO              ((int32_t)0x800A000BL)

/*  */
/*  MessageId: CIFX_FILE_LOAD_INSUFF_MEM */
/*  */
/*  MessageText: */
/*  */
/*  Insufficient memory to load file */
/*  */
#define CIFX_FILE_LOAD_INSUFF_MEM        ((int32_t)0x800A000CL)

/*  */
/*  MessageId: CIFX_FILE_CHECKSUM_ERROR */
/*  */
/*  MessageText: */
/*  */
/*  File checksum compare failed */
/*  */
#define CIFX_FILE_CHECKSUM_ERROR         ((int32_t)0x800A000DL)

/*  */
/*  MessageId: CIFX_FILE_READ_ERROR */
/*  */
/*  MessageText: */
/*  */
/*  Error reading from file */
/*  */
#define CIFX_FILE_READ_ERROR             ((int32_t)0x800A000EL)

/*  */
/*  MessageId: CIFX_FILE_TYPE_INVALID */
/*  */
/*  MessageText: */
/*  */
/*  Invalid file type */
/*  */
#define CIFX_FILE_TYPE_INVALID           ((int32_t)0x800A000FL)

/*  */
/*  MessageId: CIFX_FILE_NAME_INVALID */
/*  */
/*  MessageText: */
/*  */
/*  Invalid file name */
/*  */
#define CIFX_FILE_NAME_INVALID           ((int32_t)0x800A0010L)

/*  */
/*  MessageId: CIFX_FUNCTION_NOT_AVAILABLE */
/*  */
/*  MessageText: */
/*  */
/*  Driver function not available */
/*  */
#define CIFX_FUNCTION_NOT_AVAILABLE      ((int32_t)0x800A0011L)

/*  */
/*  MessageId: CIFX_BUFFER_TOO_SHORT */
/*  */
/*  MessageText: */
/*  */
/*  Given buffer is too short */
/*  */
#define CIFX_BUFFER_TOO_SHORT            ((int32_t)0x800A0012L)

/*  */
/*  MessageId: CIFX_MEMORY_MAPPING_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  Failed to map the memory */
/*  */
#define CIFX_MEMORY_MAPPING_FAILED       ((int32_t)0x800A0013L)

/*  */
/*  MessageId: CIFX_NO_MORE_ENTRIES */
/*  */
/*  MessageText: */
/*  */
/*  No more entries available */
/*  */
#define CIFX_NO_MORE_ENTRIES             ((int32_t)0x800A0014L)

/*  */
/*  MessageId: CIFX_CALLBACK_MODE_UNKNOWN */
/*  */
/*  MessageText: */
/*  */
/*  Unkown callback handling mode */
/*  */
#define CIFX_CALLBACK_MODE_UNKNOWN       ((int32_t)0x800A0015L)

/*  */
/*  MessageId: CIFX_CALLBACK_CREATE_EVENT_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  Failed to create callback events */
/*  */
#define CIFX_CALLBACK_CREATE_EVENT_FAILED ((int32_t)0x800A0016L)

/*  */
/*  MessageId: CIFX_CALLBACK_CREATE_RECV_BUFFER */
/*  */
/*  MessageText: */
/*  */
/*  Failed to create callback receive buffer */
/*  */
#define CIFX_CALLBACK_CREATE_RECV_BUFFER ((int32_t)0x800A0017L)

/*  */
/*  MessageId: CIFX_CALLBACK_ALREADY_USED */
/*  */
/*  MessageText: */
/*  */
/*  Callback already used */
/*  */
#define CIFX_CALLBACK_ALREADY_USED       ((int32_t)0x800A0018L)

/*  */
/*  MessageId: CIFX_CALLBACK_NOT_REGISTERED */
/*  */
/*  MessageText: */
/*  */
/*  Callback was not registerd before */
/*  */
#define CIFX_CALLBACK_NOT_REGISTERED     ((int32_t)0x800A0019L)

/*  */
/*  MessageId: CIFX_INTERRUPT_DISABLED */
/*  */
/*  MessageText: */
/*  */
/*  Interrupt is disabled */
/*  */
#define CIFX_INTERRUPT_DISABLED          ((int32_t)0x800A001AL)

/*******************************************************************************
* Generic Driver Errors
*******************************************************************************/
/*  */
/*  MessageId: CIFX_DRV_NOT_INITIALIZED */
/*  */
/*  MessageText: */
/*  */
/*  Driver not initialized */
/*  */
#define CIFX_DRV_NOT_INITIALIZED         ((int32_t)0x800B0001L)

/*  */
/*  MessageId: CIFX_DRV_INIT_STATE_ERROR */
/*  */
/*  MessageText: */
/*  */
/*  Driver init state error */
/*  */
#define CIFX_DRV_INIT_STATE_ERROR        ((int32_t)0x800B0002L)

/*  */
/*  MessageId: CIFX_DRV_READ_STATE_ERROR */
/*  */
/*  MessageText: */
/*  */
/*  Driver read state error */
/*  */
#define CIFX_DRV_READ_STATE_ERROR        ((int32_t)0x800B0003L)

/*  */
/*  MessageId: CIFX_DRV_CMD_ACTIVE */
/*  */
/*  MessageText: */
/*  */
/*  Command is active on device */
/*  */
#define CIFX_DRV_CMD_ACTIVE              ((int32_t)0x800B0004L)

/*  */
/*  MessageId: CIFX_DRV_DOWNLOAD_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  General error during download */
/*  */
#define CIFX_DRV_DOWNLOAD_FAILED         ((int32_t)0x800B0005L)

/*  */
/*  MessageId: CIFX_DRV_WRONG_DRIVER_VERSION */
/*  */
/*  MessageText: */
/*  */
/*  Wrong driver version */
/*  */
#define CIFX_DRV_WRONG_DRIVER_VERSION    ((int32_t)0x800B0006L)

/*  */
/*  MessageId: CIFX_DRV_DRIVER_NOT_LOADED */
/*  */
/*  MessageText: */
/*  */
/*  CIFx driver is not running */
/*  */
#define CIFX_DRV_DRIVER_NOT_LOADED       ((int32_t)0x800B0030L)

/*  */
/*  MessageId: CIFX_DRV_INIT_ERROR */
/*  */
/*  MessageText: */
/*  */
/*  Failed to initialize the device */
/*  */
#define CIFX_DRV_INIT_ERROR              ((int32_t)0x800B0031L)

/*  */
/*  MessageId: CIFX_DRV_CHANNEL_NOT_INITIALIZED */
/*  */
/*  MessageText: */
/*  */
/*  Channel not initialized (xOpenChannel not called) */
/*  */
#define CIFX_DRV_CHANNEL_NOT_INITIALIZED ((int32_t)0x800B0032L)

/*  */
/*  MessageId: CIFX_DRV_IO_CONTROL_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  IOControl call failed */
/*  */
#define CIFX_DRV_IO_CONTROL_FAILED       ((int32_t)0x800B0033L)

/*  */
/*  MessageId: CIFX_DRV_NOT_OPENED */
/*  */
/*  MessageText: */
/*  */
/*  Driver was not opened */
/*  */
#define CIFX_DRV_NOT_OPENED              ((int32_t)0x800B0034L)

/*  */
/*  MessageId: CIFX_DRV_DOWNLOAD_STORAGE_UNKNOWN */
/*  */
/*  MessageText: */
/*  */
/*  Unknown download storage type (RAM/FLASH based) found */
/*  */
#define CIFX_DRV_DOWNLOAD_STORAGE_UNKNOWN ((int32_t)0x800B0040L)

/*  */
/*  MessageId: CIFX_DRV_DOWNLOAD_FW_WRONG_CHANNEL */
/*  */
/*  MessageText: */
/*  */
/*  Channel number for a firmware download not supported */
/*  */
#define CIFX_DRV_DOWNLOAD_FW_WRONG_CHANNEL ((int32_t)0x800B0041L)

/*  */
/*  MessageId: CIFX_DRV_DOWNLOAD_MODULE_NO_BASEOS */
/*  */
/*  MessageText: */
/*  */
/*  Modules are not allowed without a Base OS firmware */
/*  */
#define CIFX_DRV_DOWNLOAD_MODULE_NO_BASEOS ((int32_t)0x800B0042L)

/*******************************************************************************
* Generic Device Errors
*******************************************************************************/
/*  */
/*  MessageId: CIFX_DEV_DPM_ACCESS_ERROR */
/*  */
/*  MessageText: */
/*  */
/*  Dual port memory not accessable (board not found) */
/*  */
#define CIFX_DEV_DPM_ACCESS_ERROR        ((int32_t)0x800C0010L)

/*  */
/*  MessageId: CIFX_DEV_NOT_READY */
/*  */
/*  MessageText: */
/*  */
/*  Device not ready (ready flag failed) */
/*  */
#define CIFX_DEV_NOT_READY               ((int32_t)0x800C0011L)

/*  */
/*  MessageId: CIFX_DEV_NOT_RUNNING */
/*  */
/*  MessageText: */
/*  */
/*  Device not running (running flag failed) */
/*  */
#define CIFX_DEV_NOT_RUNNING             ((int32_t)0x800C0012L)

/*  */
/*  MessageId: CIFX_DEV_WATCHDOG_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  Watchdog test failed */
/*  */
#define CIFX_DEV_WATCHDOG_FAILED         ((int32_t)0x800C0013L)

/*  */
/*  MessageId: CIFX_DEV_SYSERR */
/*  */
/*  MessageText: */
/*  */
/*  Error in handshake flags */
/*  */
#define CIFX_DEV_SYSERR                  ((int32_t)0x800C0015L)

/*  */
/*  MessageId: CIFX_DEV_MAILBOX_FULL */
/*  */
/*  MessageText: */
/*  */
/*  Send mailbox is full */
/*  */
#define CIFX_DEV_MAILBOX_FULL            ((int32_t)0x800C0016L)

/*  */
/*  MessageId: CIFX_DEV_PUT_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Send packet timeout */
/*  */
#define CIFX_DEV_PUT_TIMEOUT             ((int32_t)0x800C0017L)

/*  */
/*  MessageId: CIFX_DEV_GET_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Receive packet timeout */
/*  */
#define CIFX_DEV_GET_TIMEOUT             ((int32_t)0x800C0018L)

/*  */
/*  MessageId: CIFX_DEV_GET_NO_PACKET */
/*  */
/*  MessageText: */
/*  */
/*  No packet available */
/*  */
#define CIFX_DEV_GET_NO_PACKET           ((int32_t)0x800C0019L)

/*  */
/*  MessageId: CIFX_DEV_MAILBOX_TOO_SHORT */
/*  */
/*  MessageText: */
/*  */
/*  Mailbox too short */
/*  */
#define CIFX_DEV_MAILBOX_TOO_SHORT       ((int32_t)0x800C001AL)

/*  */
/*  MessageId: CIFX_DEV_RESET_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Reset command timeout */
/*  */
#define CIFX_DEV_RESET_TIMEOUT           ((int32_t)0x800C0020L)

/*  */
/*  MessageId: CIFX_DEV_NO_COM_FLAG */
/*  */
/*  MessageText: */
/*  */
/*  COM-flag not set */
/*  */
#define CIFX_DEV_NO_COM_FLAG             ((int32_t)0x800C0021L)

/*  */
/*  MessageId: CIFX_DEV_EXCHANGE_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  I/O data exchange failed */
/*  */
#define CIFX_DEV_EXCHANGE_FAILED         ((int32_t)0x800C0022L)

/*  */
/*  MessageId: CIFX_DEV_EXCHANGE_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  I/O data exchange timeout */
/*  */
#define CIFX_DEV_EXCHANGE_TIMEOUT        ((int32_t)0x800C0023L)

/*  */
/*  MessageId: CIFX_DEV_COM_MODE_UNKNOWN */
/*  */
/*  MessageText: */
/*  */
/*  Unknown I/O exchange mode  */
/*  */
#define CIFX_DEV_COM_MODE_UNKNOWN        ((int32_t)0x800C0024L)

/*  */
/*  MessageId: CIFX_DEV_FUNCTION_FAILED */
/*  */
/*  MessageText: */
/*  */
/*  Device function failed */
/*  */
#define CIFX_DEV_FUNCTION_FAILED         ((int32_t)0x800C0025L)

/*  */
/*  MessageId: CIFX_DEV_DPMSIZE_MISMATCH */
/*  */
/*  MessageText: */
/*  */
/*  DPM size differs from configuration */
/*  */
#define CIFX_DEV_DPMSIZE_MISMATCH        ((int32_t)0x800C0026L)

/*  */
/*  MessageId: CIFX_DEV_STATE_MODE_UNKNOWN */
/*  */
/*  MessageText: */
/*  */
/*  Unknown state mode */
/*  */
#define CIFX_DEV_STATE_MODE_UNKNOWN      ((int32_t)0x800C0027L)

/*  */
/*  MessageId: CIFX_DEV_HW_PORT_IS_USED */
/*  */
/*  MessageText: */
/*  */
/*  Device is still accessed */
/*  */
#define CIFX_DEV_HW_PORT_IS_USED         ((int32_t)0x800C0028L)

/*  */
/*  MessageId: CIFX_DEV_CONFIG_LOCK_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Configuration locking timeout */
/*  */
#define CIFX_DEV_CONFIG_LOCK_TIMEOUT     ((int32_t)0x800C0029L)

/*  */
/*  MessageId: CIFX_DEV_CONFIG_UNLOCK_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Configuration unlocking timeout */
/*  */
#define CIFX_DEV_CONFIG_UNLOCK_TIMEOUT   ((int32_t)0x800C002AL)

/*  */
/*  MessageId: CIFX_DEV_HOST_STATE_SET_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Set HOST state timeout */
/*  */
#define CIFX_DEV_HOST_STATE_SET_TIMEOUT  ((int32_t)0x800C002BL)

/*  */
/*  MessageId: CIFX_DEV_HOST_STATE_CLEAR_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Clear HOST state timeout */
/*  */
#define CIFX_DEV_HOST_STATE_CLEAR_TIMEOUT ((int32_t)0x800C002CL)

/*  */
/*  MessageId: CIFX_DEV_INITIALIZATION_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Timeout during channel initialization */
/*  */
#define CIFX_DEV_INITIALIZATION_TIMEOUT  ((int32_t)0x800C002DL)

/*  */
/*  MessageId: CIFX_DEV_BUS_STATE_ON_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Set Bus ON Timeout */
/*  */
#define CIFX_DEV_BUS_STATE_ON_TIMEOUT    ((int32_t)0x800C002EL)

/*  */
/*  MessageId: CIFX_DEV_BUS_STATE_OFF_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Set Bus OFF Timeout */
/*  */
#define CIFX_DEV_BUS_STATE_OFF_TIMEOUT   ((int32_t)0x800C002FL)

/*  */
/*  MessageId: CIFX_DEV_MODULE_ALREADY_RUNNING */
/*  */
/*  MessageText: */
/*  */
/*  Module already running */
/*  */
#define CIFX_DEV_MODULE_ALREADY_RUNNING  ((int32_t)0x800C0040L)

/*  */
/*  MessageId: CIFX_DEV_MODULE_ALREADY_EXISTS */
/*  */
/*  MessageText: */
/*  */
/*  Module already exists */
/*  */
#define CIFX_DEV_MODULE_ALREADY_EXISTS   ((int32_t)0x800C0041L)

/*  */
/*  MessageId: CIFX_DEV_DMA_INSUFF_BUFFER_COUNT */
/*  */
/*  MessageText: */
/*  */
/*  Number of configured DMA buffers insufficient */
/*  */
#define CIFX_DEV_DMA_INSUFF_BUFFER_COUNT ((int32_t)0x800C0050L)

/*  */
/*  MessageId: CIFX_DEV_DMA_BUFFER_TOO_SMALL */
/*  */
/*  MessageText: */
/*  */
/*  DMA buffers size too small (min size 256Byte) */
/*  */
#define CIFX_DEV_DMA_BUFFER_TOO_SMALL    ((int32_t)0x800C0051L)

/*  */
/*  MessageId: CIFX_DEV_DMA_BUFFER_TOO_BIG */
/*  */
/*  MessageText: */
/*  */
/*  DMA buffers size too big (max size 63,75KByte) */
/*  */
#define CIFX_DEV_DMA_BUFFER_TOO_BIG      ((int32_t)0x800C0052L)

/*  */
/*  MessageId: CIFX_DEV_DMA_BUFFER_NOT_ALIGNED */
/*  */
/*  MessageText: */
/*  */
/*  DMA buffer alignment failed (must be 256Byte) */
/*  */
#define CIFX_DEV_DMA_BUFFER_NOT_ALIGNED  ((int32_t)0x800C0053L)

/*  */
/*  MessageId: CIFX_DEV_DMA_HANSHAKEMODE_NOT_SUPPORTED */
/*  */
/*  MessageText: */
/*  */
/*  I/O data uncontrolled handshake mode not supported */
/*  */
#define CIFX_DEV_DMA_HANSHAKEMODE_NOT_SUPPORTED ((int32_t)0x800C0054L)

/*  */
/*  MessageId: CIFX_DEV_DMA_IO_AREA_NOT_SUPPORTED */
/*  */
/*  MessageText: */
/*  */
/*  I/O area in DMA mode not supported (only area 0 possible) */
/*  */
#define CIFX_DEV_DMA_IO_AREA_NOT_SUPPORTED ((int32_t)0x800C0055L)

/*  */
/*  MessageId: CIFX_DEV_DMA_STATE_ON_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Set DMA ON Timeout */
/*  */
#define CIFX_DEV_DMA_STATE_ON_TIMEOUT    ((int32_t)0x800C0056L)

/*  */
/*  MessageId: CIFX_DEV_DMA_STATE_OFF_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Set DMA OFF Timeout */
/*  */
#define CIFX_DEV_DMA_STATE_OFF_TIMEOUT   ((int32_t)0x800C0057L)

/*  */
/*  MessageId: CIFX_DEV_SYNC_STATE_INVALID_MODE */
/*  */
/*  MessageText: */
/*  */
/*  Device is in invalid mode for this operation */
/*  */
#define CIFX_DEV_SYNC_STATE_INVALID_MODE ((int32_t)0x800C0058L)

/*  */
/*  MessageId: CIFX_DEV_SYNC_STATE_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Waiting for synchronization event bits timed out */
/*  */
#define CIFX_DEV_SYNC_STATE_TIMEOUT      ((int32_t)0x800C0059L)

/*******************************************************************************
* CIFX API Transport Errors
*******************************************************************************/
/*  */
/*  MessageId: CIFX_TRANSPORT_SEND_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Time out while sending data */
/*  */
#define CIFX_TRANSPORT_SEND_TIMEOUT      ((int32_t)0x800D0001L)

/*  */
/*  MessageId: CIFX_TRANSPORT_RECV_TIMEOUT */
/*  */
/*  MessageText: */
/*  */
/*  Time out waiting for incoming data */
/*  */
#define CIFX_TRANSPORT_RECV_TIMEOUT      ((int32_t)0x800D0002L)

/*  */
/*  MessageId: CIFX_TRANSPORT_CONNECT */
/*  */
/*  MessageText: */
/*  */
/*  Unable to communicate to the device / no answer */
/*  */
#define CIFX_TRANSPORT_CONNECT           ((int32_t)0x800D0003L)

/*  */
/* MessageId: CIFX_TRANSPORT_ABORTED */
/*  */
/* MessageText: */
/*  */
/* Transfer has been aborted due to keep alive timeout or interface detachment */
/*  */
#define CIFX_TRANSPORT_ABORTED           ((long)0x800D0004L)

/*  */
/* MessageId: CIFX_TRANSPORT_INVALID_RESPONSE */
/*  */
/* MessageText: */
/*  */
/* The packet response was rejected due to invalid packet data */
/*  */
#define CIFX_TRANSPORT_INVALID_RESPONSE  ((long)0x800D0005L)

/*  */
/* MessageId: CIFX_TRANSPORT_UNKNOWN_DATALAYER */
/*  */
/* MessageText: */
/*  */
/* The data layer provided by the device is not supported */
/*  */
#define CIFX_TRANSPORT_UNKNOWN_DATALAYER ((long)0x800D0006L)

/*  */
/* MessageId: CIFX_CONNECTOR_FUNCTIONS_READ_ERROR */
/*  */
/* MessageText: */
/*  */
/* Error reading the connector functions from the DLL */
/*  */
#define CIFX_CONNECTOR_FUNCTIONS_READ_ERROR ((long)0x800D0010L)

/*  */
/* MessageId: CIFX_CONNECTOR_IDENTIFIER_TOO_LONG */
/*  */
/* MessageText: */
/*  */
/* Connector delivers an identifier longer than 6 characters */
/*  */
#define CIFX_CONNECTOR_IDENTIFIER_TOO_LONG ((long)0x800D0011L)

/*  */
/* MessageId: CIFX_CONNECTOR_IDENTIFIER_EMPTY */
/*  */
/* MessageText: */
/*  */
/* Connector delivers an empty dentifier */
/*  */
#define CIFX_CONNECTOR_IDENTIFIER_EMPTY  ((long)0x800D0012L)

/*  */
/* MessageId: CIFX_CONNECTOR_DUPLICATE_IDENTIFIER */
/*  */
/* MessageText: */
/*  */
/* Connector identifier already used */
/*  */
#define CIFX_CONNECTOR_DUPLICATE_IDENTIFIER ((long)0x800D0013L)

/*******************************************************************************
* CIFX API Transport Header State Errors
*******************************************************************************/
/*  */
/*  MessageId: CIFX_TRANSPORT_ERROR_UNKNOWN */
/*  */
/*  MessageText: */
/*  */
/*  Unknown error code in transport header */
/*  */
#define CIFX_TRANSPORT_ERROR_UNKNOWN     ((int32_t)0x800E0001L)

/*  */
/*  MessageId: CIFX_TRANSPORT_CHECKSUM_ERROR */
/*  */
/*  MessageText: */
/*  */
/*  CRC16 checksum failed */
/*  */
#define CIFX_TRANSPORT_CHECKSUM_ERROR    ((int32_t)0x800E0002L)

/*  */
/*  MessageId: CIFX_TRANSPORT_LENGTH_INCOMPLETE */
/*  */
/*  MessageText: */
/*  */
/*  Transaction with inclomplete length detected */
/*  */
#define CIFX_TRANSPORT_LENGTH_INCOMPLETE ((int32_t)0x800E0003L)

/*  */
/*  MessageId: CIFX_TRANSPORT_DATA_TYPE_UNKOWN */
/*  */
/*  MessageText: */
/*  */
/*  Device does not support requested data type */
/*  */
#define CIFX_TRANSPORT_DATA_TYPE_UNKOWN  ((int32_t)0x800E0004L)

/*  */
/*  MessageId: CIFX_TRANSPORT_DEVICE_UNKNOWN */
/*  */
/*  MessageText: */
/*  */
/*  Device not available/unknown */
/*  */
#define CIFX_TRANSPORT_DEVICE_UNKNOWN    ((int32_t)0x800E0005L)

/*  */
/*  MessageId: CIFX_TRANSPORT_CHANNEL_UNKNOWN */
/*  */
/*  MessageText: */
/*  */
/*  Channel not available/unknown */
/*  */
#define CIFX_TRANSPORT_CHANNEL_UNKNOWN   ((int32_t)0x800E0006L)

/*  */
/*  MessageId: CIFX_TRANSPORT_SEQUENCE */
/*  */
/*  MessageText: */
/*  */
/*  Sequence error detected */
/*  */
#define CIFX_TRANSPORT_SEQUENCE          ((int32_t)0x800E0007L)

/*  */
/*  MessageId: CIFX_TRANSPORT_BUFFEROVERFLOW */
/*  */
/*  MessageText: */
/*  */
/*  Buffer overflow detected */
/*  */
#define CIFX_TRANSPORT_BUFFEROVERFLOW    ((int32_t)0x800E0008L)

/*  */
/*  MessageId: CIFX_TRANSPORT_RESOURCE */
/*  */
/*  MessageText: */
/*  */
/*  Device signals out of resources */
/*  */
#define CIFX_TRANSPORT_RESOURCE          ((int32_t)0x800E0009L)

/*  */
/*  MessageId: CIFX_TRANSPORT_KEEPALIVE */
/*  */
/*  MessageText: */
/*  */
/*  Device connection monitoring error (Keep alive) */
/*  */
#define CIFX_TRANSPORT_KEEPALIVE         ((int32_t)0x800E000AL)

/*  */
/*  MessageId: CIFX_TRANSPORT_DATA_TOO_SHORT */
/*  */
/*  MessageText: */
/*  */
/*  Received transaction data too short */
/*  */
#define CIFX_TRANSPORT_DATA_TOO_SHORT    ((int32_t)0x800E000BL)

/*******************************************************************************/

#endif  /*__CIFXERRORS_H__ */
