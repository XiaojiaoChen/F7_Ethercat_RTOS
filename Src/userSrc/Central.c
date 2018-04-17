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

CENTRAL gCentral;

/*update sensor data, to be sent in the EthercatCyclicIODataHandler()*/
static void central_updateData(struct CENTRAL_STRUCT *ptCentral) {
	int32_t local_c1, local_c2;
	int32_t timeoutAD = 100;
	int32_t periodUpdate = 200;
	static int32_t CyclicDelayTime = 500;

	/*This is to ensure the timer to have enough ticks before its overflow and reset during this process*/
	if (TIC() > 0x7FFF7FFF)
		TTTimer.Instance->CNT = 0;

	/*record the start Tick*/
	local_c1 = TIC();

	/*get all Analog, none blocking, should check dataFlag for data receiving done*/
	ptCentral->ADDevice.getVoltage(&ptCentral->ADDevice);

	/*get Angles, blocking*/
	ptCentral->ptAngleHub->getAngleAll(ptCentral->ptAngleHub);

	/*get IMU blocking*/

	/*wait for Analog read accomplished, or Tick timeout*/
	while (ptCentral->ADDevice.ucDataFlag == 0) {
		local_c2 = TIC();
		if ((local_c2 - local_c1) > timeoutAD)
			break;
	}

	/*get all pressure, since Analog pressure sensor just simply read AD results*/
	ptCentral->ptPressureHub->getPressureAll(ptCentral->ptPressureHub);

	/*store data to Ethercat Buffer*/
	for (int i = 0; i < ptCentral->ptAngleHub->Num; i++) {
		ptCentral->ptSensorData->angle[i] = ptCentral->ptAngleHub->angles[i];
		ptCentral->ptSensorData->velocity[i] = 1.23; //ptCentral->angleHub->velocity[i];
		ptCentral->ptSensorData->acceleration[i] = 10.2; //ptCentral->angleHub->acceleration[i];
		ptCentral->ptSensorData->pressure[i][0] = 124.7;
		ptCentral->ptSensorData->pressure[i][1] = 133.5;
	}
	//add Slave timestamp
	ptCentral->ptSensorData->timeTick = HAL_GetTick();

//	/*wait for predefined Update period. This is to ensure EthercatCyclicIODataHandler to have a fixed starting time*/
//	while (1) {
//		local_c2 = TIC();
//		if ((local_c2 - local_c1) > periodUpdate)
//			break;
//	}

	//Ethercat Exchange Data
	  if(CyclicDelayTime>0){
		  CyclicDelayTime--;
	  }else{
		  EthercatCyclicIODataHandler();
	  }

}

static void central_control(CENTRAL *ptCentral) {

	//the controllerHub is incharge of control
	ptCentral->ptControlHub->controlAll(ptCentral->ptControlHub);
}

/*Apply controlHub outcome to actuatorHub, and do it
 * THis function is actuator-specific, by different types of actuator command.
 */
static void central_applyControl(struct CENTRAL_STRUCT *ptCentral) {

	//The ActuatorHub is in charge of commanding hardware
	ptCentral->ptActuatorHub->moveAll(ptCentral->ptActuatorHub);
}

void LLSetVoltage(struct CENTRAL_STRUCT *ptCentral, uint16_t DAPort, float voltage) {

}
void LLSetPressure(struct CENTRAL_STRUCT *ptCentral, uint16_t jointNum, uint16_t seq, float pre) {

}
void LLSetPSource(struct CENTRAL_STRUCT *ptCentral, float psource) {

}

static void transmitData(CENTRAL *ptCentral) {

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
	ptCentral->transmit = transmitData;



	//Init AD Device Instance
	Init_AD(&ptCentral->ADDevice, 8, -10, 10, &hspi_AD);

	//Init DA Device Instance
	Init_DA(&ptCentral->DADevice, 0, 10, &hspi_DA);

	/*Init IMU Device*/
	//Init_IMU(&ptCentral->IMUDevice,&hspi3);
	/*****************New a AngleHub on heap**************************************/
	ANGLE_HUB * ptAngleHub = ANGLEHUB(ptCentral);

	/*****************New a pressureHub on heap***************************************/
	PRESSURE_HUB *ptPressureHub = PRESSUREHUB(ptCentral);


	/*****************New a regulatorHub on heap*************************************/
	REGULATOR_HUB *ptRegulatorHub = REGULATORHUB(ptCentral);

	/*****************New a controllerHub on heap***************************************/
	CONTROLLER_HUB *ptControllerHub = CONTROLLERHUB(ptCentral);

	/*****************New a actuaotrHub on heap**************************************/
	ACTUATOR_HUB *ptActuatorHub = ACTUATORHUB(ptCentral);


	/**************************link  SensorData and Ethercat*************************/
	ptCentral->ptSensorData = &(EthercatAppData->tInputData);
	ptCentral->ptNominalData = &(EthercatAppData->tOutputData);

}


