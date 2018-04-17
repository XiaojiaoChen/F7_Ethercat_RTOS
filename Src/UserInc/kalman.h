#ifndef __KALMAN_H
#define __KALMAN_H

#include "stm32f7xx_hal.h"
#include "arm_math.h"

#define N_State_Sim 2
#define M_Input_Sim 1
#define L_Measure_Sim 1

#define N_State_Ful 3
#define M_Input_Ful 1
#define L_Measure_Ful 3

typedef enum{
	Kalman_Ful,
	Kalman_Sim
}KALMAN_TYPE;

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

typedef struct KALMAN_FILTER_TYPE{
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
	KALMAN_TYPE  type;
	float	  dt;
	KALMAN_STATE_MEM_FUL memFul;
	KALMAN_STATE_MEM_SIM memSim;
	void (*step)(struct KALMAN_FILTER_TYPE *s);
	void (*setQ)(struct KALMAN_FILTER_TYPE *s);
	void (*setR)(struct KALMAN_FILTER_TYPE *s);
}KALMAN_FILTER;



void kalman_setQ(KALMAN_FILTER *s, float q);
void kalman_setR(KALMAN_FILTER *s, float r);
void kalman_Init(KALMAN_FILTER *s, float *q, float *r,float dt,KALMAN_TYPE type);
void kalman_StoreMeasure(KALMAN_FILTER *s, uint8_t num,float z);
#endif
