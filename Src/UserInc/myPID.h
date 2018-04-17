/*
 * myPID.h
 *
 *  Created on: Oct 4, 2017
 *      Author: 40207
 */

#ifndef USER_INC_MYPID_H_
#define USER_INC_MYPID_H_

#include "stm32f7xx_hal.h"

typedef struct {
	 float Kp;
	 float Ki;
	 float Kd;
	 float Kpr;
	 float Kdr;
	 float Dt;
	 float IStore;
	 float DFStore[2];
	 float DFCoeff[2];
	 float Umax;
	 float Umin;
	 float P;
	 float I;
	 float D;
	 float Direction;
	 float Tau;
	 float U;
}PID_Type;


PID_Type anglePID;
PID_Type *anglePIDP;
void updatePID(PID_Type *pid,float r, float y,float *u);
void initPID(PID_Type *pid,float kp,float ki,float kd,float umax,float umin);
void tuningPID(PID_Type *pid, float kp,float ki,float kd);
void setKp(PID_Type *, float);
void setKi(PID_Type *, float);
void setKd(PID_Type *, float);
void setKpr(PID_Type *, float);
void setKdr(PID_Type *, float);
void setTau(PID_Type *, float);
void setDt(PID_Type *, float);
void setDir(PID_Type *, float);
void setUmax(PID_Type *, float);
void setUmin(PID_Type *, float);


#endif /* USER_INC_MYPID_H_ */
