/*
 * trajectoryGeneration.h
 *
 *  Created on: Oct 23, 2017
 *      Author: 40207
 */

#ifndef USER_INC_TRAJECTORYGENERATION_H_
#define USER_INC_TRAJECTORYGENERATION_H_

#include <stdint.h>


typedef enum{
	TRAJ_GEN_STATE_READY,
	TRAJ_GEN_STATE_BUSY
}TRAJ_GEN_StateTypeDef;

typedef enum{
	TRAJ_GEN_STEP,
	TRAJ_GEN_SQUARE,
	TRAJ_GEN_STEP_SCURVE,
	TRAJ_GEN_SQUARE_SCURVE,
	TRAJ_GEN_SINOID
}TRAJ_GEN_CurveTypeDef;


typedef struct{
	float x0;
	float *x_out;
	float *v_out;
	float *a_out;
	float T;
	float xd;
}TYPE_STEP;


typedef struct{
	float x0;
	float x1;
	float *x_out;
	float *v_out;
	float *a_out;
	float t;
	float holdT;
	int dir[2];
}TYPE_SQUARE;

typedef struct{
	float x0;
	float x1;
	float *x_out;
	float *v_out;
	float *a_out;
	float t;
	float T;
	float ts;
	float J;
	float dis;
	float _J[5];
	float _t[6];
	float _x[6];
	float _xdot[6];
	float _xddot[6];
	int segment;
	float LinearProportion;
}TYPE_STEPSCURVE;

typedef struct{
	float x0;
	float x1;
	float *x_out;
	float *v_out;
	float *a_out;
	float transT;
	float holdT;
	float _t[5];
	float period;
	uint32_t curPeriod;
	TYPE_STEPSCURVE scurve[3];
}TYPE_SQUARESCURVE;

typedef struct{
	float x0;
	float v0;
	float *x_out;
	float *v_out;
	float *a_out;
	float t;
	float T;
	float amplitude;
	float frequency;
	float period;
	float omega;
	float phi;

}TYPE_SINOID;

struct __TRAJ_GEN{
	TRAJ_GEN_StateTypeDef trajState;
	TRAJ_GEN_CurveTypeDef lineType;
	unsigned long tStart;
	unsigned long tDuration;
	unsigned long tEnd;
	unsigned long t;   //0-duration
	unsigned long repetition;
	float x0;
	float v0;
	float a0;
	float xd;
	float vd;
	float ad;
	float *x_out;
	float *v_out;
	float *a_out;
	float vaverage;
	TYPE_STEP   step;
	TYPE_SQUARE square;
	TYPE_STEPSCURVE stepScurve;
	TYPE_SQUARESCURVE squareScurve;
	TYPE_SINOID sinoid;
	void (*generator)(struct __TRAJ_GEN *traj,float t);
};
typedef struct __TRAJ_GEN TRAJ_GEN;

/**one trajectory object*/
extern TRAJ_GEN positionTrajectory;
extern TRAJ_GEN stiffnessTrajectory;

/***call once in setup********/
void InitTraj(TRAJ_GEN *traj,float vaverage,float  *x_out,float *v_out,float *a_out);

/***call in loop********/
void TrajGen(TRAJ_GEN *traj,uint32_t globalT);

/*****call accordingly to change Trajectory*/
void UpdateTraj(TRAJ_GEN *traj,float xd,uint32_t startTime,uint32_t duration,TRAJ_GEN_CurveTypeDef lineType);



#endif /* USER_INC_TRAJECTORYGENERATION_H_ */
