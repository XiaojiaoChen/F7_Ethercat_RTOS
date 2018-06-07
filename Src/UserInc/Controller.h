#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#define mymin(X,Y) ((X) < (Y) ? (X) : (Y))
#define mymax(X,Y) ((X) < (Y) ? (Y) : (X))

#include "stm32f7xx.h"
#include "myPID.h"
#include "arm_math.h"
#include <Central.h>





typedef enum{
	HARD_QUICK,
	HARD_SLOW,
	SOFT_QUICK,
	SOFT_SLOW,
}M_CONTROLLER_MODE;


typedef struct{
	float kd;
	float kp;
	float kpeq;
	float ki;
	float k1;
	float ep1;
	float thickness1;
	float k2;
	float ep2;
	float thickness2;
}pCONTROLPARA;


typedef struct {
	float kp;
	float ki;
	float kd;
	float kflow;
	float stiffness;
	float ilim;
	float ulim;
}mCONTROLPARA;
extern  mCONTROLPARA mControlPara;

typedef struct VARIABLE_STRUCT{
	float Real;
	float Nom;
	float Err;
}VARIABLE_TEMPLATE;

typedef struct CONTROLLER_STATE_STRUCT{

	float m1dpre,m2dpre,m1dpos,m2dpos,m1,m2,m1dplus,m2dplus,m1dmax,m2dmax,dm1,dm2;
	float v1,v2;
	float flow1_cal,flow2_cal;
	float pressureSaturation[2];
	float p1d,p2d;
	float x3d_ingre[6];
	uint16_t quickness;
	uint16_t tauEffectiveFlag;
	uint16_t positionFeedbackFlag;

}CONTROLLER_STATE;



typedef struct CONTROLLER_TYPE_STRUCT{
	struct CONTROLLER_HUB_STRUCT *pParent;
	void (*control)(struct CONTROLLER_TYPE_STRUCT *pCon);
	VARIABLE_TEMPLATE pos; //0: Nominal;   1: measured;  2: error
	VARIABLE_TEMPLATE vel;
	VARIABLE_TEMPLATE acc;
	VARIABLE_TEMPLATE pre[2];
	VARIABLE_TEMPLATE tor;
	VARIABLE_TEMPLATE stiff;
	float	pOut[2];
	uint16_t jointNum;
	int8_t pControllerType;
	PID_Type pid;
	float R;
	float T;
	float g;
	float gama;
	float Pu;
	float Pmax;
	CONTROLLER_STATE state;

}CONTROLLER_TYPE;


typedef struct CONTROLLER_HUB_STRUCT{
	struct CONTROLLER_TYPE_STRUCT *ptController[JOINT_NUM_MAX];
	struct CENTRAL_STRUCT *pParent;
	uint16_t num;
	void (*attach)(struct CONTROLLER_HUB_STRUCT *,struct CONTROLLER_TYPE_STRUCT *);
	void (*control)(struct CONTROLLER_HUB_STRUCT *,uint16_t);
	void (*controlAll)(struct CONTROLLER_HUB_STRUCT *);
}CONTROLLER_HUB;


CONTROLLER_TYPE *CONTROLLER(uint16_t jointNum);
CONTROLLER_HUB* CONTROLLERHUB(struct CENTRAL_STRUCT *ptCentral);








void setmControllerMode(M_CONTROLLER_MODE mmode);
void setPosition(float);
void setStiffness(float);



#endif
