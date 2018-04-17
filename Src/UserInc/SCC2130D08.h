/*
 * SCC2130D08.h
 *
 *  Created on: Dec 27, 2017
 *      Author: 402072495
 */

#ifndef USER_INC_SCC2130D08_H_
#define USER_INC_SCC2130D08_H_
#include "stm32f7xx_hal.h"
//#define RSOK(dat) ((uint8_t)(((uint32_t)((dat)<<6))>>24) == 1)


#define  SCC2130_CMD_READ_RATE             			 0x040000F7
#define  SCC2130_CMD_READ_ACC_X           			 0X100000E9
#define  SCC2130_CMD_READ_ACC_Y  		  			 0x140000EF
#define  SCC2130_CMD_READ_ACC_Z    		  			 0x180000E5
#define  SCC2130_CMD_READ_TEMP            			 0x1C0000E3
#define  SCC2130_CMD_READ_RATE_STATUS1    			 0x240000C7
#define  SCC2130_CMD_READ_RATE_STATUS2               0x280000CD
#define  SCC2130_CMD_READ_ACC_STATUS                 0x3C0000D3
#define  SCC2130_CMD_WRITE_RESET_CONTROL_HARD        0xD8000431
#define  SCC2130_CMD_WRITE_RESET_CONTROL_MONITOR     0xD80008AD
#define  SCC2130_CMD_READ_SERIAL_ID0 		   		 0x600000A1
#define  SCC2130_CMD_READ_SERIAL_ID1              	 0x640000A7
#define  SCC2130_CMD_READ_COMMON_STATUS 			 0X6C0000AB
#define  SCC2130_CMD_READ_STATUS_SUMMARY        	 0x7C0000B3
#define  SCC2130_CMD_SET_FILTER_60HZ            	 0xFC200006
#define  SCC2130_CMD_SET_FILTER_10HZ          		 0xFC1000C7

typedef struct {
	uint16_t GyroStatus1;
	uint16_t GyroStatus2;
	uint16_t AcceStatus;
	uint16_t RWStatus;
	uint16_t ResetTriggerStatus;
	uint16_t SerialNumLSB;
	uint16_t SerialNumMSB;
	uint16_t CommonStatus;
	uint16_t ProductTypeIdentification;
	uint16_t OverviewStatus;
	uint32_t RawGyroStatus1;
	uint32_t RawGyroStatus2;
	uint32_t RawAcceStatus;
	uint32_t RawRWStatus;
	uint32_t RawResetTriggerStatus;
	uint32_t RawSerialNumLSB;
	uint32_t RawSerialNumMSB;
	uint32_t RawCommonStatus;
	uint32_t RawProductTypeIdentification;
	uint32_t RawOverviewStatus;
}SCC2130_STATE;

typedef struct
{
	float RateX;
	float AccX;
	float AccY;
	float AccZ;
	float AngleAbsoluteStatic;
	float AngleAccel;
}ACCDATA;


typedef struct IMU_DEVICE_STRUCT
{
	ACCDATA AccData;
	SCC2130_STATE scc2130_state;
	SPI_HandleTypeDef *IMU_spi;
	void (*getIMU)(struct IMU_DEVICE_STRUCT *);
}IMU_DEVICE;


void Init_IMU();

#endif /* USER_INC_SCC2130D08_H_ */
