/*
 * Central.c
 *
 *  Created on: Mar 28, 2018
 *      Author: 402072495
 */
#include <Central.h>
#include "tim.h"
#include "spi.h"
#include "string.h"
#include "stdlib.h"
#include "pressureSensor.h"
#include "Controller.h"
#include "myUsartFunctions.h"
#include "PlantModel.h"
CENTRAL gCentral;
CENTRAL *ptCentral = &gCentral;

static float Q_KF_AS5048[]={2e5};
static float R_KF_AS5048[]={1e-8,1e-5,10};
//static float Q_KF_AS5311[]={2e5};
//static float R_KF_AS5311[]={1e-8,1e-4,0.1};
static float Q_KF_PressureSPI[]={1e12};
static float R_KF_PressureSPI[]={4000};
static float kalmanUpdateRate = 0.001;
float YiangleOffset=3.141;
/*update sensor data, to be sent in the EthercatCyclicIODataHandler()*/
static void central_updateData(struct CENTRAL_STRUCT *ptCentral) {
	int32_t lc1, lc2,lc3,lc4,lc5,lc6;
	static int32_t CyclicDelayTime = 2000;

	 if(CyclicDelayTime>0){
		  CyclicDelayTime--;
	 }else
	 {
		/*This is to ensure the timer to have enough ticks before its overflow and reset during this process*/
		if (TIC() > 0x7FFF7FFF)
			TTTimer.Instance->CNT = 0;
		lc1 = TIC();


		/*****************************************update sensor data**************************************/
		//get pressures non blocking through DMA. This would take 200 us for 8 channels
		ptCentral->ptPressureHub->getPressureAll_DMA(ptCentral->ptPressureHub);

		/*get Analog none blocking, througn DMA. This would take 40us for 8 channels*/
		ptCentral->ADDevice.getVoltage(&ptCentral->ADDevice);
		lc2 = TIC();

		/*get Angles,blocking. This would take 100us for 4 channels*/
		ptCentral->ptAngleHub->getAngleAll(ptCentral->ptAngleHub);
		lc3 = TIC();

#ifdef YIJUAN
		ptCentral->ptAngleHub->angles[0]=ptCentral->ADDevice.fChannel[6]/4.9*2*3.1415926f-YiangleOffset;
#endif
		/*get IMU, blocking. This would take 100us for 4 channels*/
		ptCentral->ptIMUHub->getIMU(ptCentral->ptIMUHub,0);
		lc4 = TIC();

		/*sensor fusion*/
		ptCentral->ptKalmanFilterHub->stepAll(ptCentral->ptKalmanFilterHub);
		lc5 = TIC();

		/*store data to Ethercat Buffer*/
		for (int i = 0; i < JOINT_NUM_MAX; i++) {

			if (i == 0) {
				ptCentral->ptSensorData->angle[i] = ptCentral->ptAngleHub->angles[i];
				ptCentral->ptSensorData->velocity[i] = ptCentral->ptIMUHub->IMUDevices[i]->AccData.RateX;
				ptCentral->ptSensorData->acceleration[i] = ptCentral->ptIMUHub->IMUDevices[i]->AccData.AngleAccel;
			}

			ptCentral->ptSensorData->pressure[i][0] = ptCentral->ptPressureHub->Pressure[i][0];
			ptCentral->ptSensorData->pressure[i][1] = ptCentral->ptPressureHub->Pressure[i][1];


			if (ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][0] != NULL) {
				ptCentral->ptSensorData->filtered_Angle[i] = ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][0]->X.pData[0];
				ptCentral->ptSensorData->filtered_velocity[i] = ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][0]->X.pData[1];
				ptCentral->ptSensorData->filtered_acceleration[i] = ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][0]->X.pData[2];
			}

			if (ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][1] != NULL) {
				ptCentral->ptSensorData->filtered_pressure[i][0] = ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][1]->X.pData[0];
				ptCentral->ptSensorData->filtered_pressureDot[i][0] = ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][1]->X.pData[1];
			}

			if (ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][2] != NULL) {
				ptCentral->ptSensorData->filtered_pressure[i][1] = ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][2]->X.pData[0];
				ptCentral->ptSensorData->filtered_pressureDot[i][1] = ptCentral->ptKalmanFilterHub->ptKalmanFilter[i][2]->X.pData[1];
			}

			ptCentral->ptSensorData->torque[0] = ptCentral->ADDevice.fChannel[0];
			ptCentral->ptSensorData->force[0]= ptCentral->ADDevice.fChannel[1]*100;


		}
		lc6 = TIC();

		//pressure and AD are non-blocking using DMA, this time is from commanding to receiving the last return result.
		ptCentral->process_time.PressureTime = ptCentral->ptPressureHub->LastDMATime;
		ptCentral->process_time.ADTime = ptCentral->ADDevice.LastDMATime;

		//Angle and IMU are non-blocking
		ptCentral->process_time.AngleTime = lc3-lc2;
		ptCentral->process_time.IMUTime = lc4-lc3;
		ptCentral->process_time.KalmanTime = lc5-lc4;
		ptCentral->process_time.copyTime = lc6-lc5;

		//usart transfer total time. This time is also nonblocking. This task only consumes  the idle time of each 1ms period.
		ptCentral->process_time.usartTime = UsartDevice.lastTxTime;

		//total sensor time
		ptCentral->process_time.SensorAllTime = lc6-lc1;

		//add Slave timestamp
		ptCentral->ptSensorData->timeTick = TIC();

		/*****************************************Ethercat exchange data 150us**************************************/
		//Ethercat Exchange Data
		lc2 = TIC();
		//EthercatCyclicIODataHandler();
		ptCentral->process_time.EthercatIOTime = TIC()-lc2;

	}

}

static void central_control(CENTRAL *ptCentral) {
	ptCentral->ptControlHub->controlAll(ptCentral->ptControlHub);
}

static void central_applyControl(struct CENTRAL_STRUCT *ptCentral) {
	ptCentral->ptActuatorHub->moveAll(ptCentral->ptActuatorHub);
}

void LLSetVoltage(struct CENTRAL_STRUCT *ptCentral, uint16_t DAPort, float voltage) {
	 ptCentral->DADevice.setVoltage(&(ptCentral->DADevice),DAPort,voltage);
}
void LLSetPressure(struct CENTRAL_STRUCT *ptCentral, uint16_t jointNum, uint16_t seq, float pre) {

}
void LLSetPSource(struct CENTRAL_STRUCT *ptCentral, float psource) {
	ptCentral->ptRegulatorHub->setPressure(ptCentral->ptRegulatorHub,0,psource);
}


void Init_Central(CENTRAL *ptCentral, APP_DATA_T *EthercatAppData) {

	//Central is a global variable on stack
	memset(ptCentral, 0, sizeof(CENTRAL));

	/*******************attache methods****************************************/
	ptCentral->updateData = central_updateData;
	ptCentral->control = central_control;
	ptCentral->applyControl = central_applyControl;
	ptCentral->LLsetPSource = LLSetPSource;
	ptCentral->LLsetPressure = LLSetPressure;
	ptCentral->LLsetVoltage = LLSetVoltage;

	//Init AD Device Instance
	Init_AD(&ptCentral->ADDevice, 8, -10, 10, &hspi_AD);

	//Init DA Device Instance
	Init_DA(&ptCentral->DADevice, 0, 10, &hspi_DA);


	/*****************New a IMUHub on heap**************************************/
	IMU_HUB * ptIMUHub = IMUHUB(ptCentral);
	IMU_DEVICE *ptSCC2130Dev = SCC2130(0);
	ptIMUHub->attach(ptIMUHub,(IMU_DEVICE *)ptSCC2130Dev);

	/*****************New a AngleHub on heap**************************************/
	ANGLE_HUB * ptAngleHub = ANGLEHUB(ptCentral);
//	AS5311_DEVICE *ptAS5311Dev;
	AS5048_DEVICE *ptAS5048Dev;
	ptAS5048Dev = AS5048(0);
	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5048Dev);


//	ptAS5311Dev = AS5311(0);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev);
//	ptAS5311Dev = AS5311(1);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev);
//	ptAS5311Dev = AS5311(2);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev);
//	ptAS5311Dev = AS5311(3);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev);


	/*****************New a pressureHub on heap***************************************/
	PRESSURE_HUB *ptPressureHub = PRESSUREHUB(ptCentral);
	HWGAUGE_DEVICE *ptHWPGSA3;
	ptHWPGSA3 = HWPGSA3(0,0);
	ptPressureHub->attach(ptPressureHub,(PRESSURE_DEVICE *)ptHWPGSA3);
	ptHWPGSA3 = HWPGSA3(0,1);
	ptPressureHub->attach(ptPressureHub,(PRESSURE_DEVICE *)ptHWPGSA3);
	ptHWPGSA3 = HWPGSA3(1,0);
	ptPressureHub->attach(ptPressureHub,(PRESSURE_DEVICE *)ptHWPGSA3);
	ptHWPGSA3 = HWPGSA3(1,1);
	ptPressureHub->attach(ptPressureHub,(PRESSURE_DEVICE *)ptHWPGSA3);
	ptHWPGSA3 = HWPGSA3(2,0);
	ptPressureHub->attach(ptPressureHub,(PRESSURE_DEVICE *)ptHWPGSA3);
	ptHWPGSA3 = HWPGSA3(2,1);
	ptPressureHub->attach(ptPressureHub,(PRESSURE_DEVICE *)ptHWPGSA3);
	ptHWPGSA3 = HWPGSA3(3,0);
	ptPressureHub->attach(ptPressureHub,(PRESSURE_DEVICE *)ptHWPGSA3);
	ptHWPGSA3 = HWPGSA3(3,1);
	ptPressureHub->attach(ptPressureHub,(PRESSURE_DEVICE *)ptHWPGSA3);



	/*****************New a regulatorHub on heap*************************************/
	REGULATOR_HUB *ptRegulatorHub = REGULATORHUB(ptCentral);
	REGULATOR_DEVICE *ptITV2030Dev = ITV2030(&(ptCentral->DADevice),15,&(ptCentral->ADDevice),2,400000,0);
	ptRegulatorHub->attach(ptRegulatorHub,ptITV2030Dev);


	/*****************New a controllerHub on heap***************************************/
	CONTROLLER_HUB *ptControllerHub = CONTROLLERHUB(ptCentral);
	CONTROLLER_TYPE *ptController;
	ptController= CONTROLLER(0);
	ptControllerHub->attach(ptControllerHub,ptController);
//	ptController = CONTROLLER(1);
//	ptControllerHub->attach(ptControllerHub,ptController);
//	ptController = CONTROLLER(2);
//	ptControllerHub->attach(ptControllerHub,ptController);
//	ptController = CONTROLLER(3);
//	ptControllerHub->attach(ptControllerHub,ptController);


	/*****************New a actuaotrHub on heap**************************************/
	ACTUATOR_HUB *ptActuatorHub = ACTUATORHUB(ptCentral);
	MPYE_VALVE *ptMPYE;
	//New a Actuator attached to DAPort 0, jointNum 0, position 0
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),0,0,0);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),1,0,1);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);


	/*****************New a kalmanFilterHub on heap************************/
	KALMAN_FILTER_HUB *ptKalmanFilterHub = KALMANFILTERHUB(ptCentral);
	KALMAN_FILTER *ptKalmanFilter;
	//Angle
//	ptKalmanFilter = KALMANFILTER(Q_KF_AS5048, R_KF_AS5048,kalmanUpdateRate,KALMAN_CONST_ACCELERATION);
	float Q_KF_yijuan[]={40};
	float R_KF_yijuan[]={2e-5};
	ptKalmanFilter = KALMANFILTER(Q_KF_yijuan, R_KF_yijuan,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,0,0);
	//Pressure
	ptKalmanFilter = KALMANFILTER(Q_KF_PressureSPI, R_KF_PressureSPI,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,0,1);
	ptKalmanFilter = KALMANFILTER(Q_KF_PressureSPI, R_KF_PressureSPI,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,0,2);
	ptKalmanFilter = KALMANFILTER(Q_KF_PressureSPI, R_KF_PressureSPI,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,1,1);
	ptKalmanFilter = KALMANFILTER(Q_KF_PressureSPI, R_KF_PressureSPI,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,1,2);
	ptKalmanFilter = KALMANFILTER(Q_KF_PressureSPI, R_KF_PressureSPI,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,2,1);
	ptKalmanFilter = KALMANFILTER(Q_KF_PressureSPI, R_KF_PressureSPI,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,2,2);
	ptKalmanFilter = KALMANFILTER(Q_KF_PressureSPI, R_KF_PressureSPI,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,3,1);
	ptKalmanFilter = KALMANFILTER(Q_KF_PressureSPI, R_KF_PressureSPI,kalmanUpdateRate,KALMAN_CONST_VELOCITY);
	ptKalmanFilterHub->attach(ptKalmanFilterHub,ptKalmanFilter,3,2);

	/**************************link  SensorData and Ethercat*************************/
	ptCentral->ptSensorData = &(EthercatAppData->tInputData);
	ptCentral->ptNominalData = &(EthercatAppData->tOutputData);

	/**************Init local trajectory generation***************************/
	InitTraj(&(ptCentral->positionTrajectory[0]),1);
	InitTraj(&(ptCentral->positionTrajectory[1]),1);
	InitTraj(&(ptCentral->positionTrajectory[2]),1);
	InitTraj(&(ptCentral->positionTrajectory[3]),1);

	/*************************Init Value********************************/
	ptCentral->ptNominalData->stiffness[0] = 17;
	ptCentral->ptNominalData->stiffness[1] = 17;
	ptCentral->ptNominalData->stiffness[2] = 17;
	ptCentral->ptNominalData->stiffness[3] = 17;

	/**********************Init Plant parameters*******************/
	Init_myjoint();

	/***valve*****/
	LLSetVoltage(ptCentral,0,5.2);
	LLSetVoltage(ptCentral,1,5.2);

	//regulator
	LLSetPSource(ptCentral,0);

	 Init_YiJuanPlant();
	 yiinitControlPara();
}


