/*
 * IMUs.c
 *
 *  Created on: Dec 27, 2017
 *      Author: 402072495
 */
#include <IMUs.h>
#include "main.h"
#include "math.h"
#include "string.h"
#include "Central.h"
#include "string.h"
#include "stdlib.h"
#include "spi.h"
#include "arm_math.h"


GPIO_TypeDef *IMU_CS_GPIO_Ports[JOINT_NUM_MAX] = {IMU_0_CS_GPIO_Port,IMU_1_CS_GPIO_Port,IMU_2_CS_GPIO_Port,IMU_3_CS_GPIO_Port};
uint16_t	IMU_CS_Pins[JOINT_NUM_MAX] = {IMU_0_CS_Pin,IMU_1_CS_Pin,IMU_2_CS_Pin,IMU_3_CS_Pin};

static void IMU_CS_LOW(IMU_DEVICE *ptIMUDev)
{
	ptIMUDev->CS_Port->BSRR=(uint32_t)ptIMUDev->CS_Pin<<16U;
}

static void IMU_CS_HIGH(IMU_DEVICE *ptIMUDev)
{
	ptIMUDev->CS_Port->BSRR=(uint32_t)ptIMUDev->CS_Pin;
}




static uint32_t getRawSCC2130(IMU_DEVICE *ptIMUDev,uint32_t cmd)
{
	uint16_t AccReceiveBuf[2];
	uint16_t cmd16[2];
	uint32_t ret;
	cmd16[0]=(uint16_t)(cmd>>16);
	cmd16[1]=(uint16_t)cmd;

	IMU_CS_LOW(ptIMUDev);
	HAL_SPI_TransmitReceive(ptIMUDev->hspi,(uint8_t *)cmd16,(uint8_t *)AccReceiveBuf,2,1);
	IMU_CS_HIGH(ptIMUDev);

	ret=((uint32_t)AccReceiveBuf[0])<<16 | ((uint32_t)AccReceiveBuf[1]);
	return ret;
}
static uint16_t extractData(uint32_t data)
{
	return (uint16_t)((data & 0x00FFFF00)>>8);
}

static uint16_t getDatSCC2130(IMU_DEVICE *ptIMUDev, uint32_t cmd)
{
	uint32_t data;
	data = getRawSCC2130(ptIMUDev,cmd);
    return extractData(data);
}

void getSCC2130(IMU_DEVICE *ptIMUDev)
{
	int16_t data;


	getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_RATE);
	delay_ns(300);

	data = (int16_t) getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_X);
	ptIMUDev->AccData.RateX = data/50.0f*3.1415926f/180.0f;
	delay_ns(300);

	data = (int16_t) getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_Y);
	ptIMUDev->AccData.AccX = data/1962.0f;
	delay_ns(300);

	data = (int16_t) getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_Z);
	ptIMUDev->AccData.AccY = data/1962.0f;
	delay_ns(300);

	data = (int16_t) getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_RATE);
	ptIMUDev->AccData.AccZ = data/1962.0f;

	ptIMUDev->AccData.AngleAccel =  (ptIMUDev->AccData.AccZ - cos(ptIMUDev->AccData.AngleAbsoluteStatic + ptCentral->ptSensorData->angle[0]))
									*9.8/ptIMUDev->radius;

}

static void warmup_IMU(IMU_DEVICE * ptIMUDev)
{
	uint16_t AccReceiveBuf[2];
	// let the SLK Polarity be low
	HAL_SPI_TransmitReceive(ptIMUDev->hspi,(uint8_t *)AccReceiveBuf,(uint8_t *)AccReceiveBuf,1,1);
	HAL_Delay(20);

	getRawSCC2130(ptIMUDev,SCC2130_CMD_SET_FILTER_60HZ);
	HAL_Delay(800);
	ptIMUDev->scc2130_state.RawGyroStatus1 = getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_RATE_STATUS1);
	ptIMUDev->scc2130_state.GyroStatus1 = extractData(ptIMUDev->scc2130_state.RawGyroStatus1);
	delay_ns(300);
	ptIMUDev->scc2130_state.RawGyroStatus1 = getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_RATE_STATUS2);
	ptIMUDev->scc2130_state.GyroStatus1 = extractData(ptIMUDev->scc2130_state.RawGyroStatus1);
	delay_ns(300);
	ptIMUDev->scc2130_state.RawGyroStatus2 = getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_STATUS);
	ptIMUDev->scc2130_state.GyroStatus2 = extractData(ptIMUDev->scc2130_state.RawGyroStatus2);
	delay_ns(300);
	ptIMUDev->scc2130_state.RawAcceStatus  = getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_COMMON_STATUS);
	ptIMUDev->scc2130_state.AcceStatus = extractData(ptIMUDev->scc2130_state.RawAcceStatus);
	delay_ns(300);
	ptIMUDev->scc2130_state.RawCommonStatus = getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_STATUS_SUMMARY);
	ptIMUDev->scc2130_state.CommonStatus = extractData(ptIMUDev->scc2130_state.RawCommonStatus);
	delay_ns(300);
	ptIMUDev->scc2130_state.RawOverviewStatus = getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_STATUS_SUMMARY);
	ptIMUDev->scc2130_state.OverviewStatus = extractData(ptIMUDev->scc2130_state.RawOverviewStatus);


    for(int i=0;i<2;i++)
    {
    	delay_ns(300);
    	ptIMUDev->getIMU(ptIMUDev);
    }

    ptIMUDev->AccData.AngleAbsoluteStatic = -asin(ptIMUDev->AccData.AccY);
}


IMU_DEVICE *SCC2130(uint16_t jointNum)
{
	//new a scc2130 device on the heap
	IMU_DEVICE *ptSCC2130Dev = (IMU_DEVICE *)malloc(sizeof(IMU_DEVICE));
	if(ptSCC2130Dev == NULL)
		return NULL;
	memset(ptSCC2130Dev,0,sizeof(IMU_DEVICE));

	//jointNum
	ptSCC2130Dev->jointNum = jointNum;

	//methods
	ptSCC2130Dev->getIMU = getSCC2130;

	//configure spi
	ptSCC2130Dev->hspi = &hspi_IMU;
	ptSCC2130Dev->CS_Port = IMU_CS_GPIO_Ports[jointNum];
	ptSCC2130Dev->CS_Pin = IMU_CS_Pins[jointNum];



	//parameters
	ptSCC2130Dev->radius = 0.2;

	warmup_IMU(ptSCC2130Dev);

	return ptSCC2130Dev;
}



static void IMUHub_attachIMUDevice(IMU_HUB *ptIMUHub,IMU_DEVICE *ptIMUDev)
{
	ptIMUHub->IMUDevices[ptIMUDev->jointNum]=ptIMUDev;
	ptIMUDev->pParent = ptIMUHub;
	ptIMUHub->Num+=1;
}

static void IMUHub_getIMU(IMU_HUB *ptIMUHub,uint16_t num)
{
	ptIMUHub->IMUDevices[num]->getIMU(ptIMUHub->IMUDevices[num]);
}

static void IMUHub_getIMUAll(IMU_HUB * ptIMUHub)
{
	for(int i=0;i<ptIMUHub->Num;i++)
		ptIMUHub->getIMU(ptIMUHub,i);
}


IMU_HUB *IMUHUB(struct CENTRAL_STRUCT *ptCentral)
{
	//new a angle Hub on the heap
	IMU_HUB * ptIMUHub = (IMU_HUB *)malloc(sizeof(IMU_HUB));
	if(ptIMUHub==NULL)
		return NULL;
	memset(ptIMUHub,0,sizeof(IMU_HUB));

	//add parent Central
	ptIMUHub->pParent = ptCentral;
	ptCentral->ptIMUHub = ptIMUHub;

	//attach methods
	ptIMUHub->attach = IMUHub_attachIMUDevice;
	ptIMUHub->getIMU = IMUHub_getIMU;
	ptIMUHub->getIMUAll = IMUHub_getIMUAll;




			
	return ptIMUHub;
}



/*********************individual read*******************************/
/*static float getRateXOnce(IMU_DEVICE * ptIMUDev)
{
	int16_t data;
	getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_RATE);
	delay_ns(300);
	data = (int16_t)getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_RATE);
	return(data/50.0f);
}
static float getRateXCont(IMU_DEVICE * ptIMUDev)
{
	int16_t data;
	data = (int16_t) getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_RATE);
	return(data/50.0f);
}
static float getAccX(IMU_DEVICE *ptIMUDev)
{
	int16_t data;
	getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_X);
	delay_ns(300);
	data = (int16_t)getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_X);
	return(data/1962.0f);
}
static float getAccY(IMU_DEVICE *ptIMUDev)
{
	int16_t data;
	getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_Y);
	delay_ns(300);
	data = (int16_t)getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_Y);
	return(data/1962.0f);
}
static float getAccZ(IMU_DEVICE *ptIMUDev)
{
	int16_t data;
	getRawSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_Y);
	delay_ns(300);
	data = (int16_t)getDatSCC2130(ptIMUDev,SCC2130_CMD_READ_ACC_Y);
	return(data/1962.0f);
}*/


