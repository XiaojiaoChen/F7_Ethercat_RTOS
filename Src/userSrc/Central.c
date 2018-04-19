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
CENTRAL *ptCentral = &gCentral;

/*update sensor data, to be sent in the EthercatCyclicIODataHandler()*/
static void central_updateData(struct CENTRAL_STRUCT *ptCentral) {
	int32_t lc1, lc2,lc3,lc4;
	int32_t timeoutSensor = 250;
	static int32_t CyclicDelayTime = 500;

	/*This is to ensure the timer to have enough ticks before its overflow and reset during this process*/
	if (TIC() > 0x7FFF7FFF)
		TTTimer.Instance->CNT = 0;
	lc1 = TIC();

	//get pressures non blocking through DMA. This would take 200 us for 8 channels
	ptCentral->ptPressureHub->getPressureAll_DMA(ptCentral->ptPressureHub);

	/*get Analog none blocking, througn DMA. This would take 40us for 8 channels*/
	ptCentral->ADDevice.getVoltage(&ptCentral->ADDevice);

	/*get Angles,blocking. This would take 100us for 4 channels*/
	ptCentral->ptAngleHub->getAngleAll(ptCentral->ptAngleHub);

	/*get IMU, blocking. This would take 100us for 4 channels*/


	/*wait for a fixed timeout*/
	while ((TIC() - lc1) < timeoutSensor);

	/*store data to Ethercat Buffer*/
	for (int i = 0; i < JOINT_NUM; i++) {
		ptCentral->ptSensorData->angle[i] = ptCentral->ptAngleHub->angles[i];
		ptCentral->ptSensorData->velocity[i] = ptCentral->ptAngleHub->velocity[i];
		ptCentral->ptSensorData->acceleration[i] = ptCentral->ptAngleHub->acceleration[i];
		ptCentral->ptSensorData->pressure[i][0] = ptCentral->ptPressureHub->Pressure[i][0];
		ptCentral->ptSensorData->pressure[i][1] = ptCentral->ptPressureHub->Pressure[i][1];
	}

	lc2 = TIC();
	ptCentral->process_time.SensorTime = lc2-lc1;

	//add Slave timestamp
	ptCentral->ptSensorData->timeTick = TIC();

	//Ethercat Exchange Data
	  if(CyclicDelayTime>0){
		  CyclicDelayTime--;
	  }else{
		  lc2 = TIC();
		  EthercatCyclicIODataHandler();
		  ptCentral->process_time.EthercatIOTime = TIC()-lc2;
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


