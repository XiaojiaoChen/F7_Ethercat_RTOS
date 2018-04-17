#ifndef __MPYEVAVLE_H
#define	__MPYEVAVLE_H

#include <Central.h>
#include "stm32f7xx_hal.h"
#include "main.h"
#include "LTC2668.h"

typedef struct ACTUATOR_STRUCT{
	uint16_t jointNum;
	uint16_t position;
	struct ACTUATOR_HUB_STRUCT *pParent;
	void (*act)(struct ACTUATOR_STRUCT *);
	float command; //could be voltage, PWM duty ...
}ACTUATOR;

typedef struct MPYE_VALVE_STRUCT{
	ACTUATOR base;
	struct DA_DEVICE_STRUCT *ptDADev;
	uint16_t DAPort;
}MPYE_VALVE;

typedef struct ACTUATOR_HUB_STRUCT{
	struct CENTRAL_STRUCT *pParent;
	ACTUATOR *actuator[JOINT_NUM][2];
	uint16_t num;
	void (*attach)(struct ACTUATOR_HUB_STRUCT *,struct ACTUATOR_STRUCT *);
	void (*moveJoint)(struct ACTUATOR_HUB_STRUCT *,uint16_t);
	void (*moveAll)(struct ACTUATOR_HUB_STRUCT *);
}ACTUATOR_HUB;

ACTUATOR_HUB *ACTUATORHUB(struct CENTRAL_STRUCT *);

MPYE_VALVE *MPYEVALVE(DA_DEVICE *,uint16_t DAPort,uint16_t jointNum,uint16_t pos);


float valveFlowFunc(float P1,float P2,float u);
float InverseValveFlowFunc(float P1,float P2,float q,int active);
float valveAreaFunc(float u);
float InverseValveAreaFunc(float area,float dir);



#endif
