/*
 * myPID.c
 *
 *  Created on: Oct 4, 2017
 *      Author: yii
 */

#include "myPID.h"

PID_Type anglePID;
PID_Type *anglePIDP=&anglePID;

/* PID update function. Should be called every dt seconds.
 *  input r:reference
 *	input y:feedback
 *	output u:control signal
 */
void updatePID(PID_Type *pid,float r, float y,float *u)
{
	float err = r - y;
	float kprerr = pid->Kpr * r-y;
	float kdrerr = pid->Kdr * r-y;
	float v1;

	if(pid->Direction==-1)
	{
		err=-err;
		kprerr=-kprerr;
		kdrerr=-kdrerr;
	}
	//P_part=Kp*(Kr*ref-yin)
	pid->P = pid->Kp * kprerr;

	//I_part
	pid->I = pid->I + pid->Kp * pid->Ki * err;

	//D_part
	//first order low-pass
	//backward Euler
	v1 = pid->Kd * pid->DFCoeff[0] * kdrerr;
	pid->D = v1 - pid->DFStore[0] - pid->DFStore[1];
	pid->DFStore[0] = v1;
	pid->DFStore[1] = pid->DFCoeff[1] * pid->D;
	pid->D = pid->Kp * pid->D;

	//PID total output is the sum of P I D part.
	pid->U = pid->P + pid->I + pid->D;

	//saturation
	if(pid->U>pid->Umax)
		pid->U = pid->Umax;
	else if(pid->U<pid->Umin)
		pid->U = pid->Umin;

	*u=pid->U;
}

void initPID(PID_Type *pid,float kp,float ki,float kd,float umax,float umin)
{
	 pid->Kp=kp;
	 pid->Ki=ki;
	 pid->Kd=kd;
	 pid->Kpr=1;
	 pid->Kdr=0.0f;
	 pid->Dt=0.001f;
	 pid->Direction=1;
	 pid->DFStore[0]=0;
	 pid->DFStore[1]=0;
	 pid->Tau=1;
	 pid->DFCoeff[0]=2.0f / (pid->Dt + 2*pid->Tau);
	 pid->DFCoeff[1]=(pid->Dt - 2*pid->Tau) / (pid->Dt + 2*pid->Tau);
	 pid->P=0;
	 pid->I=0;
	 pid->D=0;
	 pid->U=0;
	 pid->Umax=umax;//5e-4;
	 pid->Umin=umin;//-5e-4;
}

void tuningPID(PID_Type *pid, float kp,float ki,float kd)
{
	setKp(pid,kp);
	setKi(pid,ki);
	setKd(pid,kd);

}


void setKp(PID_Type *pid, float kp)
{
	if(kp>=0)
		pid->Kp = kp;
}

void setKd(PID_Type *pid, float kd)
{
	if(kd>=0)
		pid->Kd = kd;
}

void setKi(PID_Type *pid, float ki)
{
	if(ki>=0)
		pid->Ki = ki;
}

void setKdr(PID_Type *pid, float kdr)
{
	if(kdr>=0)
		pid->Kdr = kdr;
}

void setKpr(PID_Type *pid, float kpr)
{
	if(kpr>=0)
		pid->Kpr = kpr;
}

void setTau(PID_Type *pid, float Tau)
{
	pid->Tau = Tau;
}

void setDt(PID_Type *pid, float dt)
{
	pid->Dt = dt;
}

void setDir(PID_Type *pid, float dir)
{
	if(dir==1 || dir==-1)
		pid->Direction = dir;
}

void setUmax(PID_Type *pid, float umax)
{
	pid->Umax = umax;
}

void setUmin(PID_Type *pid, float umin)
{
	pid->Umin = umin;
}
