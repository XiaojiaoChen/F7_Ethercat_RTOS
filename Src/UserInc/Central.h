/*
 * Central.h
 *
 *  Created on: Mar 28, 2018
 *      Author: 402072495
 */

#ifndef USER_INC_CENTRAL_H_
#define USER_INC_CENTRAL_H_
#include <Angles.h>
#include <IMUs.h>
#include <pressureSensor.h>
#include "stm32f7xx_hal.h"
#include "LTC2668.h"
#include "ADS8588.h"
#include "cifXApplicationDemo.h"
#include "Controller.h"
#include "pressureRegulator_ITV2030.h"
#include "MPYEValve.h"
#include "kalman.h"
#include "trajectoryGeneration.h"
/***************
 *
 */

enum CONTROLLER_TYPE{
	PositionStiffnessControl = 0x00,
	TorqueControl,
	PressureControl
};



struct PROCESS_TIME{
	int32_t usartTime;
	int32_t KalmanTime;
	int32_t copyTime;
	int32_t PressureTime;
	int32_t ADTime;
	int32_t IMUTime;
	int32_t AngleTime;
	int32_t SensorAllTime;
	int32_t EthercatIOTime;
	int32_t EthercatPacketTime;
	int32_t ControlTime;
	int32_t taskTime1;
	int32_t taskTime2;
};

/***********State*********************************/


typedef struct CENTRAL_STRUCT
{
	APP_INPUT_DATA_T *ptSensorData;
	APP_OUTPUT_DATA_T *ptNominalData;
	AD_DEVICE ADDevice;
	DA_DEVICE DADevice;
	struct IMU_HUB_STRUCT *ptIMUHub;
	struct ACTUATOR_HUB_STRUCT *ptActuatorHub;
	struct REGULATOR_HUB_STRUCT *ptRegulatorHub;
	struct PRESSURE_HUB_STRUCT *ptPressureHub;
	struct ANGLE_HUB_STRUCT	*ptAngleHub;
	struct CONTROLLER_HUB_STRUCT *ptControlHub;
	struct KALMAN_FILTER_HUB_STRUCT *ptKalmanFilterHub;
	TRAJ_GEN positionTrajectory[JOINT_NUM_MAX];
	struct PROCESS_TIME process_time;
	uint16_t gogogo;
	void (*updateData)(struct CENTRAL_STRUCT *ptCentral);
	void (*control)(struct CENTRAL_STRUCT *ptCentral);
	void (*applyControl)(struct CENTRAL_STRUCT *ptCentral);
	void (*LLsetVoltage)(struct CENTRAL_STRUCT *ptCentral,uint16_t,float);
	void (*LLsetPressure)(struct CENTRAL_STRUCT *ptCentral,uint16_t,uint16_t,float);
	void (*LLsetPSource)(struct CENTRAL_STRUCT *ptCentral,float);
	void (*transmit)(struct CENTRAL_STRUCT *ptCentral);

}CENTRAL;

/**********Golbal Data*****************/
void Init_Central(CENTRAL *ptCentral,APP_DATA_T *EthercatAppData);
extern CENTRAL gCentral;
extern CENTRAL *ptCentral;
#endif /* USER_INC_MYMIDDLELAYER_H_ */
