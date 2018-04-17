/*
 * SCC2130D08.c
 *
 *  Created on: Dec 27, 2017
 *      Author: 402072495
 */
#include "main.h"
#include "SCC2130D08.h"
#include "math.h"
#include "string.h"

#define IMU_CS_LOW()  SPI2_CS_GPIO_Port->BSRR=(uint32_t)SPI2_CS_Pin<<16U;
#define IMU_CS_HIGH() SPI2_CS_GPIO_Port->BSRR=SPI2_CS_Pin;


static float radius=0.5;

static uint32_t getRawSCC2130(IMU_DEVICE *ptIMUDev,uint32_t cmd)
{
	uint16_t AccReceiveBuf[2];
	uint16_t cmd16[2];
	uint32_t ret;
	cmd16[0]=(uint16_t)(cmd>>16);
	cmd16[1]=(uint16_t)cmd;
	IMU_CS_LOW();
	HAL_SPI_TransmitReceive(ptIMUDev->IMU_spi,(uint8_t *)cmd16,(uint8_t *)AccReceiveBuf,2,1);
	IMU_CS_HIGH();
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

void getAllSCC2130(IMU_DEVICE *ptIMUDev)
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

	//ptIMUDev->AccData.AngleAccel =  (ptIMUDev->AccData.AccZ - cos(ptIMUDev->AccData.AngleAbsoluteStatic + sensor_pos_data.angle))*9.8/radius;

}

void warmup_IMU(IMU_DEVICE * ptIMUDev)
{
	uint16_t AccReceiveBuf[2];
	// let the SLK Polarity be low
	HAL_SPI_TransmitReceive(ptIMUDev->IMU_spi,(uint8_t *)AccReceiveBuf,(uint8_t *)AccReceiveBuf,1,1);
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


void Init_IMU(IMU_DEVICE * ptIMUDev,SPI_HandleTypeDef *IMU_spi)
{
	memset(&ptIMUDev->AccData,0,sizeof(ptIMUDev->AccData));
	memset(&ptIMUDev->scc2130_state,0,sizeof(ptIMUDev->scc2130_state));

	ptIMUDev->IMU_spi=IMU_spi;
	ptIMUDev->getIMU = getAllSCC2130;

	warmup_IMU(ptIMUDev);
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


