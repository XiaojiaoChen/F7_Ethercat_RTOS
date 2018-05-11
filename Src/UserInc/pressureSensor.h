/*
 * pressureSensor.h
 *
 *  Created on: Mar 29, 2018
 *      Author: 402072495
 */

#ifndef USER_INC_PRESSURESENSOR_H_
#define USER_INC_PRESSURESENSOR_H_

#include <Central.h>
#include "stm32f7xx_hal.h"
#include "ADS8588.h"

typedef struct PRESSURE_DEVICE_STRUCT{
	float pressure;
	struct PRESSURE_HUB_STRUCT *pParent;
	float (*getPressure)(struct PRESSURE_DEVICE_STRUCT *);
	float (*setZero)(struct PRESSURE_DEVICE_STRUCT *);
	uint16_t jointNum;
	uint16_t position;
}PRESSURE_DEVICE;

typedef struct PRESSURESPI_DEVICE_STRUCT{
	PRESSURE_DEVICE base;
	uint16_t rawData;
	int16_t rawSPIPressure;
	int16_t rawSPITemperature;
	float Pressure;
	float Temperature;
	int16_t uOutMin;
	int16_t uOutMax;
	float PMin;
	float PMax;
	SPI_HandleTypeDef *pressure_spi;
    GPIO_TypeDef *CS_Port;
    uint16_t	CS_Pin;
}HW060GAUGE_DEVICE;

typedef struct PRESSUREANA_DEVICE_STRUCT{
	PRESSURE_DEVICE base;
	AD_DEVICE *ptADDevice;
	uint16_t ADPort;
	float PMax;
	float PMin;
	float VMin;
	float VMax;
}HW060ABSOLUTE_DEVICE;

typedef struct PRESSURE_HUB_STRUCT{
	struct CENTRAL_STRUCT *pParent;
	PRESSURE_DEVICE *pressureDevices[JOINT_NUM_MAX][2];
	float Pressure[JOINT_NUM_MAX][2];
	float Temperature[JOINT_NUM_MAX][2];
	uint16_t Num;
	uint16_t DMAnum;
	int32_t DMAStartTime;
	int32_t DMAEndTime;
	int32_t LastDMATime;
	uint16_t DMACompleted;
	float (*getPressure)(struct PRESSURE_HUB_STRUCT *,uint16_t ,uint16_t );
	void (*attach)(struct PRESSURE_HUB_STRUCT *ptPressureHub,PRESSURE_DEVICE *ptPressureDev);
	uint16_t (*getPressureAll)(struct PRESSURE_HUB_STRUCT *);
	void (*getPressureAll_DMA)(struct PRESSURE_HUB_STRUCT *);
}PRESSURE_HUB;


PRESSURE_HUB *PRESSUREHUB(struct CENTRAL_STRUCT *ptCentral);
HW060ABSOLUTE_DEVICE *HW060PAAA5(AD_DEVICE *,uint16_t,uint16_t,uint16_t);
HW060GAUGE_DEVICE *HWPGSA3(uint16_t,uint16_t);
void pressure_SPICallback(PRESSURE_HUB *ptPressureHub);
#endif /* USER_INC_PRESSURESENSOR_H_ */
