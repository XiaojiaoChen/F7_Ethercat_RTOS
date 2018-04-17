#ifndef __PLANTMODEL_H
#define __PLANTMODEL_H


#include "stm32f7xx.h"

struct Rotary_Plate{
	float r;
	float m;
    float I;
	float com;
	float b;
	float f;
	float fm;
	float fc;
	float kv;
};

struct SHELINDER{
	float lmax;
	float x0;
	float A;
	float v0;
	float m;
	float k;
	float b;
	float fm;
	float fc;
	float kv;
};
struct MYJOINT{
	float I;
	float B;
	float K;
	float lamda;
	float Psource;
	struct Rotary_Plate rotaryPlate;
	struct SHELINDER shelinder1;
	struct SHELINDER shelinder2;
};
extern struct MYJOINT myjoint;
void Init_myjoint(void);
#endif
