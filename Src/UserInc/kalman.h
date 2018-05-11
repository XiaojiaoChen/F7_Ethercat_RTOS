#ifndef __KALMAN_H
#define __KALMAN_H

#include "stm32f7xx_hal.h"
#include "main.h"
#include "Central.h"
#include "arm_math.h"

#define N_State_Sim 2
#define M_Input_Sim 1
#define L_Measure_Sim 1

#define N_State_Ful 3
#define M_Input_Ful 1
#define L_Measure_Ful 3

#define KALMAN_CONST_VELOCITY	0
#define KALMAN_CONST_ACCELERATION	1

typedef struct {
	float32_t arrayX[N_State_Ful];
	float32_t arrayA[N_State_Ful*N_State_Ful];
	float32_t arrayB[N_State_Ful*M_Input_Ful];
	float32_t arrayU[M_Input_Ful*1];
	float32_t arrayH[L_Measure_Ful*N_State_Ful];
	float32_t arrayP[N_State_Ful*N_State_Ful];
	float32_t arrayQ[N_State_Ful*N_State_Ful];
	float32_t arrayR[L_Measure_Ful*L_Measure_Ful];
	float32_t arrayK[N_State_Ful*L_Measure_Ful];
	float32_t arrayZ[L_Measure_Ful*1];
	float32_t arrayAt[N_State_Ful*N_State_Ful];
	float32_t arrayHt[N_State_Ful*L_Measure_Ful];
	float32_t arrayNL[N_State_Ful*L_Measure_Ful];
	float32_t arrayNN[2][N_State_Ful*N_State_Ful];
	float32_t arrayLL[2][L_Measure_Ful*L_Measure_Ful];
	float32_t arrayL[2][L_Measure_Ful*1];
	float32_t arrayN[2][N_State_Ful*1];
}KALMAN_STATE_MEM_FUL;

typedef struct {
	float32_t arrayX[N_State_Sim];
	float32_t arrayA[N_State_Sim*N_State_Sim];
	float32_t arrayB[N_State_Sim*M_Input_Sim];
	float32_t arrayU[M_Input_Sim*1];
	float32_t arrayH[L_Measure_Sim*N_State_Sim];
	float32_t arrayP[N_State_Sim*N_State_Sim];
	float32_t arrayQ[N_State_Sim*N_State_Sim];
	float32_t arrayR[L_Measure_Sim*L_Measure_Sim];
	float32_t arrayK[N_State_Sim*L_Measure_Sim];
	float32_t arrayZ[L_Measure_Sim*1];
	float32_t arrayAt[N_State_Sim*N_State_Sim];
	float32_t arrayHt[N_State_Sim*L_Measure_Sim];
	float32_t arrayNL[N_State_Sim*L_Measure_Sim];
	float32_t arrayNN[2][N_State_Sim*N_State_Sim];
	float32_t arrayLL[2][L_Measure_Sim*L_Measure_Sim];
	float32_t arrayL[2][L_Measure_Sim*1];
	float32_t arrayN[2][N_State_Sim*1];
}KALMAN_STATE_MEM_SIM;

typedef struct KALMAN_FILTER_STRUCT{
	arm_matrix_instance_f32 X;
	arm_matrix_instance_f32 U;
	arm_matrix_instance_f32 A;
	arm_matrix_instance_f32 B;
	arm_matrix_instance_f32 H;
	arm_matrix_instance_f32 Z;
	arm_matrix_instance_f32 P;
	arm_matrix_instance_f32 Q;
	arm_matrix_instance_f32 R;
	arm_matrix_instance_f32 K;
	arm_matrix_instance_f32 At;
	arm_matrix_instance_f32 Ht;
	arm_matrix_instance_f32 NL;
	arm_matrix_instance_f32 NN[2];
	arm_matrix_instance_f32 LL[2];
	arm_matrix_instance_f32 L[2];
	arm_matrix_instance_f32 N[2];
	uint16_t  kalmanType;
	float	  dt;
	void *pMem;
	void (*step)(struct KALMAN_FILTER_STRUCT *s);
	void (*setQ)(struct KALMAN_FILTER_STRUCT *s,float *pQ);
	void (*setR)(struct KALMAN_FILTER_STRUCT *s,float *pR);
	void (*store)(struct KALMAN_FILTER_STRUCT *s, uint8_t num,float z);
}KALMAN_FILTER;

typedef struct KALMAN_FILTER_HUB_STRUCT{
	struct CENTRAL_STRUCT *pParent;
	void (*applyFilterResult)(struct KALMAN_FILTER_HUB_STRUCT *s);
	KALMAN_FILTER *ptKalmanFilter[JOINT_NUM_MAX][3];
	uint16_t Num;
	void (*attach)(struct KALMAN_FILTER_HUB_STRUCT *ptKalmanFilterHub, KALMAN_FILTER *ptKalmanFilter,uint16_t jointNum,uint16_t sensorSource);
	void (*stepAll)(struct KALMAN_FILTER_HUB_STRUCT *s);
}KALMAN_FILTER_HUB;

KALMAN_FILTER *KALMANFILTER(float *q, float *r,float dt,uint16_t kalmanType);

KALMAN_FILTER_HUB *KALMANFILTERHUB(struct CENTRAL_STRUCT *);


#endif
