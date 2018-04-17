#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#define mymin(X,Y) ((X) < (Y) ? (X) : (Y))
#define mymax(X,Y) ((X) < (Y) ? (Y) : (X))

#include "stm32f7xx.h"
#include "myPID.h"
#include <Central.h>


typedef enum{
	HARD_QUICK,
	HARD_SLOW,
	SOFT_QUICK,
	SOFT_SLOW,
}M_CONTROLLER_MODE;
extern M_CONTROLLER_MODE mMode;


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
extern pCONTROLPARA pControlPara;

typedef struct {
	float kp;
	float ki;
	float kd;
	float kflow;
	float stiffness;
	float ulim;
}mCONTROLPARA;
extern  mCONTROLPARA mControlPara;

typedef struct VARIABLE_STRUCT{
	float Real;
	float Nom;
	float Err;
}VARIABLE_TEMPLATE;






typedef struct CONTROLLER_TYPE_STRUCT{
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
	struct CONTROLLER_HUB_STRUCT *pParent;
	void (*control)(struct CONTROLLER_TYPE_STRUCT *pCon);
}CONTROLLER_TYPE;


typedef struct CONTROLLER_HUB_STRUCT{
	struct CONTROLLER_TYPE_STRUCT *ptController[JOINT_NUM];
	struct CENTRAL_STRUCT *pParent;
	uint16_t num;
	void (*attach)(struct CONTROLLER_HUB_STRUCT *,struct CONTROLLER_TYPE_STRUCT *);
	void (*control)(struct CONTROLLER_HUB_STRUCT *,uint16_t);
	void (*controlAll)(struct CONTROLLER_HUB_STRUCT *);
}CONTROLLER_HUB;


CONTROLLER_TYPE *CONTROLLER(uint16_t jointNum);
CONTROLLER_HUB* CONTROLLERHUB(struct CENTRAL_STRUCT *ptCentral);



extern float m1dpre,m2dpre,m1dpos,m2dpos,m1,m2,m1dplus,m2dplus,m1dmax,m2dmax,dm1,dm2;
extern float uCommand1,uCommand2;
extern float flow1_cal,flow2_cal;

extern float pressureSaturation[2];
extern float p1d,p2d;
extern float xeqd,xrestd,v1,v2;
extern float x3d_ingre[6];

extern uint16_t hardness;
extern uint16_t quickness;
extern uint16_t tauEffectiveFlag;
extern uint16_t positionFeedbackFlag;




void setmControllerMode(M_CONTROLLER_MODE mmode);
void setPosition(float);
void setStiffness(float);

void equilibriumPointController();
void backSteppingController(void);


#endif
