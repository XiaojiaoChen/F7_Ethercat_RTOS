#ifndef __PRESSURERUGULATORITV2030_H
#define __PRESSURERUGULATORITV2030_H

#include <Central.h>
#include "stm32f7xx_hal.h"
#include "LTC2668.h"
#include "ADS8588.h"

typedef struct REGULATOR_DEVICE_STRUCT{
	struct REGULATOR_HUB_STRUCT *pParent;
	DA_DEVICE *ptDADev;
	AD_DEVICE *ptADDev;
	uint16_t ADPort;
	uint16_t DAPort;
	uint16_t Num;
	float Pmin;
	float Pmax;
	float Vinmax;
	float Vinmin;
	float Voutmin;
	float Voutmax;
	float Vcommand;
	float Pcommand;
	void (*setPressure)(struct REGULATOR_DEVICE_STRUCT *, float);
	float (*getPressure)(struct REGULATOR_DEVICE_STRUCT *);
	void (*setZero)(struct REGULATOR_DEVICE_STRUCT *);

}REGULATOR_DEVICE;


typedef struct REGULATOR_HUB_STRUCT{
	struct CENTRAL_STRUCT *pParent;
	REGULATOR_DEVICE *regulator[JOINT_NUM*2];
	float pressureCommand[JOINT_NUM*2];
	uint16_t num;
	void (*attach)(struct REGULATOR_HUB_STRUCT *,struct REGULATOR_DEVICE_STRUCT *);
	void (*setPressure)(struct REGULATOR_HUB_STRUCT *,uint16_t,float);
	float (*getPressure)(struct REGULATOR_HUB_STRUCT *,uint16_t num);
	void (*setZero)(struct REGULATOR_HUB_STRUCT *);
}REGULATOR_HUB;


REGULATOR_HUB *REGULATORHUB(struct CENTRAL_STRUCT *);

REGULATOR_DEVICE *ITV2030(DA_DEVICE *ptDADev,uint16_t DAPort,AD_DEVICE *ptADDev,uint16_t ADPort,float pmax,uint16_t Num);
#endif
