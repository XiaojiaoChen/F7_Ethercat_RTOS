#ifndef __ADS8588_H
#define	__ADS8588_H

#include "stm32f7xx_hal.h"


#define TNUM 50
typedef struct AD_DEVICE_STRUCT{
	int16_t uChannel[8];
	float fChannel[8];
	float fMinVoltage;
	float fMaxVoltage;
	float fRange;
	float fMid;
	int32_t DMAStartTime;
	int32_t DMAEndTime;
	int32_t LastDMATime;
	uint16_t uChannelNum;
	SPI_HandleTypeDef *AD_spi;
	uint8_t ucDataFlag;
	void (*getVoltage)(struct AD_DEVICE_STRUCT *ptADDev);
	void (*Reset)(struct AD_DEVICE_STRUCT *ptADDev);

/*	float tauTrain[TNUM];
	float forceTrain[TNUM];

	float *forceP;
	float *forcePStart;
	float *forcePMid;
	float *forcePEnd;

	float *tauP;
	float *tauPStart;
	float *tauPMid;
	float *tauPEnd;*/
}AD_DEVICE;

void Init_AD(AD_DEVICE * ptADDev,uint16_t numChannel,float vMin,float vMax,SPI_HandleTypeDef *AD_spi);
void AD_BUSYCallback(AD_DEVICE *ptADDev);
void AD_SPICallback(AD_DEVICE *ptADDev);
#endif /* __BSP_ADC_H */



