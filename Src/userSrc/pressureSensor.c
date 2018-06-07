/*
 * pressureSensorSPI.c
 *
 *  Created on: Mar 29, 2018
 *      Author: 402072495
 */
#include <pressureSensor.h>
#include "string.h"
#include <stdlib.h>
#include "main.h"
#include "spi.h"

static uint32_t DummyByte[] = { 0xFFFFFFFF };
static float PaPerPSI = 6895;
float Patm = 101325;

GPIO_TypeDef *PRESSURE_CS_GPIO_Ports[JOINT_NUM_MAX][2] = {  {PRESSURE_00_CS_GPIO_Port, PRESSURE_01_CS_GPIO_Port},
														{PRESSURE_10_CS_GPIO_Port, PRESSURE_11_CS_GPIO_Port},
														{PRESSURE_20_CS_GPIO_Port, PRESSURE_21_CS_GPIO_Port},
														{PRESSURE_30_CS_GPIO_Port, PRESSURE_31_CS_GPIO_Port}};
uint16_t PRESSURE_CS_Pins[JOINT_NUM_MAX][2] = { {PRESSURE_00_CS_Pin,PRESSURE_01_CS_Pin},
											{PRESSURE_10_CS_Pin, PRESSURE_11_CS_Pin},
											{PRESSURE_20_CS_Pin, PRESSURE_21_CS_Pin},
											{PRESSURE_30_CS_Pin,PRESSURE_31_CS_Pin}};

/************************************HoneyWell 060PGSA3 gauge pressure sensor****************************************/
static void PRESSURESPI_CS_LOW(HWGAUGE_DEVICE *ptPRESSURESPIDev) {
	ptPRESSURESPIDev->CS_Port->BSRR = (uint32_t) ptPRESSURESPIDev->CS_Pin << 16U;
}

static void PRESSURESPI_CS_HIGH(HWGAUGE_DEVICE *ptPRESSURESPIDev) {
	ptPRESSURESPIDev->CS_Port->BSRR = (uint32_t) ptPRESSURESPIDev->CS_Pin;
}

static void HWPGSA3_readRawSPI(HWGAUGE_DEVICE *ptPressureDev) {
	uint16_t tem[2];
	/*read SPI pressure and temperature, 4 bytes*/
	PRESSURESPI_CS_LOW(ptPressureDev);
	HAL_SPI_TransmitReceive(ptPressureDev->pressure_spi, (uint8_t *) DummyByte, (uint8_t *) tem, 1, 1);
	PRESSURESPI_CS_HIGH(ptPressureDev);
	ptPressureDev->rawSPIPressure = (int16_t) (tem[0] & 0x3FFF);
	//ptPressureDev->rawSPITemperature = (int16_t) (tem[1] >> 5);
}

static void HWPGSA3_ValidateData(HWGAUGE_DEVICE *pt) {
	pt->base.pressure = (float) (pt->rawSPIPressure - pt->uOutMin) / (pt->uOutMax - pt->uOutMin) * (pt->PMax - pt->PMin) + pt->PMin; //unit Pa
	//pt->Temperature = pt->rawSPITemperature / 10.235f - 50.0f;

}

static float HWPGSA3_getPressure(PRESSURE_DEVICE *ptPressureDev) {
	HWGAUGE_DEVICE *pt = (HWGAUGE_DEVICE *) ptPressureDev;
	HWPGSA3_readRawSPI(pt);
	HWPGSA3_ValidateData(pt);
	return pt->Pressure;
}

HWGAUGE_DEVICE *HWPGSA3(uint16_t jointNum, uint16_t seq) {
	HWGAUGE_DEVICE *ptHWPGSA3 = (HWGAUGE_DEVICE *) malloc(sizeof(HWGAUGE_DEVICE));
	if (ptHWPGSA3 == NULL)
		return NULL;
	memset(ptHWPGSA3, 0, sizeof(HWGAUGE_DEVICE));

	ptHWPGSA3->base.jointNum = jointNum;
	ptHWPGSA3->base.position = seq;

	ptHWPGSA3->base.getPressure = HWPGSA3_getPressure;

	ptHWPGSA3->pressure_spi = &hspi_PRESSURE;
	ptHWPGSA3->CS_Port = PRESSURE_CS_GPIO_Ports[jointNum][seq];
	ptHWPGSA3->CS_Pin = PRESSURE_CS_Pins[jointNum][seq];


	ptHWPGSA3->PMax = 30 * PaPerPSI + Patm;  //60*6895 Pa
	ptHWPGSA3->PMin = Patm;
	ptHWPGSA3->uOutMin = 0x0666;
	ptHWPGSA3->uOutMax = 0x3999;
	return ptHWPGSA3;
}
/****************************************************************************************************************/

/***********************HoneyWell 060PAAA5 Absolute Pressure Sensor********************************************/
static float HW060PAAA5_getPressure(PRESSURE_DEVICE *ptPressureDev) {
	HW060ABSOLUTE_DEVICE *pt = (HW060ABSOLUTE_DEVICE *) ptPressureDev;
	float vtem = pt->ptADDevice->fChannel[pt->ADPort];
	float ptem = (vtem - pt->VMin) / (pt->VMax - pt->VMin) * (pt->PMax - pt->PMin) + pt->PMin;
	pt->base.pressure = ptem;
	return ptem;
}

HW060ABSOLUTE_DEVICE *HW060PAAA5(AD_DEVICE *ptADDev, uint16_t ADPort, uint16_t jointNum, uint16_t seq) {
	HW060ABSOLUTE_DEVICE* ptHW060PAA5 = (HW060ABSOLUTE_DEVICE *) malloc(sizeof(HW060ABSOLUTE_DEVICE));
	if (ptHW060PAA5 == NULL)
		return NULL;
	memset(ptHW060PAA5, 0, sizeof(HW060ABSOLUTE_DEVICE));
	ptHW060PAA5->ptADDevice = ptADDev;
	ptHW060PAA5->ADPort = ADPort;
	ptHW060PAA5->base.jointNum = jointNum;
	ptHW060PAA5->base.position = seq;
	ptHW060PAA5->VMax = 0.9 * 4.959f; //output 10%-90% of Vsupply
	ptHW060PAA5->VMin = 0.1 * 4.959f;
	ptHW060PAA5->PMax = 60 * PaPerPSI;
	ptHW060PAA5->PMin = 0;
	ptHW060PAA5->base.getPressure = HW060PAAA5_getPressure;
	return ptHW060PAA5;
}
/************************************************************************************************************/

/*************************************************Pressure Hub************************************************/
static void pressureHub_attachPressureDev(PRESSURE_HUB *ptPressureHub, PRESSURE_DEVICE *ptPressureDev) {
	ptPressureHub->pressureDevices[ptPressureDev->jointNum][ptPressureDev->position] = ptPressureDev;
	ptPressureDev->pParent = ptPressureHub;
	ptPressureHub->Num += 1;
}

static float pressureHub_getPressure(PRESSURE_HUB *ptPressureHub, uint16_t jointN, uint16_t seq) {
	PRESSURE_DEVICE *pt = ptPressureHub->pressureDevices[jointN][seq];
	return pt->getPressure(pt);
}

static uint16_t pressureHub_getPressureAll(PRESSURE_HUB *ptPressureHub) {
	PRESSURE_DEVICE *pt;
	uint16_t n = 0;
	for (int i = 0; i < JOINT_NUM_MAX; i++)
		for (int j = 0; j < 2; j++)
			if (NULL != (pt = ptPressureHub->pressureDevices[i][j])) {
				ptPressureHub->Pressure[i][j] = pt->getPressure(pt);
				n++;
			}
	return n;
}

static void pressureHub_getPressureAll_DMA(PRESSURE_HUB *ptPressureHub) {

	HWGAUGE_DEVICE *ptPressureDev = (HWGAUGE_DEVICE *) (ptPressureHub->pressureDevices[0][0]);
    ptPressureHub->DMAStartTime = TIC();
	ptPressureHub->DMAnum = 0;
	PRESSURESPI_CS_LOW(ptPressureDev);
	HAL_SPI_TransmitReceive_DMA(ptPressureDev->pressure_spi, (uint8_t *) DummyByte, (uint8_t *) (&ptPressureDev->rawData), 1);
}

void pressure_SPICallback(PRESSURE_HUB *ptPressureHub) {

	//close previous SPI
	HWGAUGE_DEVICE *ptPressureDevPre = (HWGAUGE_DEVICE *) (*(ptPressureHub->pressureDevices[0] + ptPressureHub->DMAnum));
	PRESSURESPI_CS_HIGH(ptPressureDevPre);

	//post calculation
	ptPressureDevPre->rawSPIPressure = (int16_t) (ptPressureDevPre->rawData & 0x3FFF);
	HWPGSA3_ValidateData(ptPressureDevPre);
	*(ptPressureHub->Pressure[0]+ptPressureHub->DMAnum) = ptPressureDevPre->base.pressure;

	//check if remaining
	if (++ptPressureHub->DMAnum < ptPressureHub->Num) {
		//begin next SPI_DMA
		HWGAUGE_DEVICE *ptPressureDevNext = (HWGAUGE_DEVICE *) (*(ptPressureHub->pressureDevices[0] + ptPressureHub->DMAnum));
		PRESSURESPI_CS_LOW(ptPressureDevNext);
		HAL_SPI_TransmitReceive_DMA(ptPressureDevNext->pressure_spi, (uint8_t *) DummyByte, (uint8_t *) (&ptPressureDevNext->rawData), 1);
	}
	else{
		ptPressureHub->DMAEndTime = TIC();
		ptPressureHub->LastDMATime = ptPressureHub->DMAEndTime -ptPressureHub->DMAStartTime;
		ptPressureHub->DMACompleted = 1;
	}

}

PRESSURE_HUB *PRESSUREHUB(CENTRAL *ptCentral) {


	//new a pressureSensorHub on the heap
	PRESSURE_HUB *ptPressureHub = (PRESSURE_HUB *) malloc(sizeof(PRESSURE_HUB));
	if (ptPressureHub == NULL)
		return NULL;
	memset(ptPressureHub, 0, sizeof(PRESSURE_HUB));

	//add parent Central
	ptPressureHub->pParent = ptCentral;
	ptCentral->ptPressureHub = ptPressureHub;

	//attach methods
	ptPressureHub->attach = pressureHub_attachPressureDev;
	ptPressureHub->getPressure = pressureHub_getPressure;
	ptPressureHub->getPressureAll = pressureHub_getPressureAll;
	ptPressureHub->getPressureAll_DMA = pressureHub_getPressureAll_DMA;






//	/*Add one pressure sensor, attached to ADPort  0, JointNum 0,  position 0*/
//	ptHW060PAAA5 = HW060PAAA5(&(ptCentral->ADDevice), 0, 0, 0);
//	ptPressureHub->attach(ptPressureHub, (PRESSURE_DEVICE *) ptHW060PAAA5);
//
//	/*Add one pressure sensor, attached to ADPort  1, JointNum 0,  position 1*/
//	ptHW060PAAA5 = HW060PAAA5(&(ptCentral->ADDevice), 1, 0, 1);
//	ptPressureHub->attach(ptPressureHub, (PRESSURE_DEVICE *) ptHW060PAAA5);
//
//	/*Add one pressure sensor, attached to ADPort  2, JointNum 1,  position 0*/
//	ptHW060PAAA5 = HW060PAAA5(&(ptCentral->ADDevice), 2, 1, 0);
//	ptPressureHub->attach(ptPressureHub, (PRESSURE_DEVICE *) ptHW060PAAA5);
//
//	/*Add one pressure sensor, attached to ADPort  3, JointNum 1,  position 1*/
//	ptHW060PAAA5 = HW060PAAA5(&(ptCentral->ADDevice), 3, 1, 1);
//	ptPressureHub->attach(ptPressureHub, (PRESSURE_DEVICE *) ptHW060PAAA5);
//
//	/*Add one pressure sensor, attached to ADPort  4, JointNum 2,  position 0*/
//	ptHW060PAAA5 = HW060PAAA5(&(ptCentral->ADDevice), 4, 2, 0);
//	ptPressureHub->attach(ptPressureHub, (PRESSURE_DEVICE *) ptHW060PAAA5);
//
//	/*Add one pressure sensor, attached to ADPort  5, JointNum 2,  position 1*/
//	ptHW060PAAA5 = HW060PAAA5(&(ptCentral->ADDevice), 5, 2, 1);
//	ptPressureHub->attach(ptPressureHub, (PRESSURE_DEVICE *) ptHW060PAAA5);
//
//	/*Add one pressure sensor, attached to ADPort  6, JointNum 3,  position 0*/
//	ptHW060PAAA5 = HW060PAAA5(&(ptCentral->ADDevice), 6, 3, 0);
//	ptPressureHub->attach(ptPressureHub, (PRESSURE_DEVICE *) ptHW060PAAA5);
//
//	/*Add one pressure sensor, attached to ADPort  7, JointNum 3,  position 1*/
//	ptHW060PAAA5 = HW060PAAA5(&(ptCentral->ADDevice), 7, 3, 1);
//	ptPressureHub->attach(ptPressureHub, (PRESSURE_DEVICE *) ptHW060PAAA5);

	return ptPressureHub;
}

