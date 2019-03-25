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
	float l0;
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
	float x0;
	float lamda;
	struct Rotary_Plate rotaryPlate;
	struct SHELINDER shelinder1;
	struct SHELINDER shelinder2;
};
struct YIJUAN_ROTARY_PLANT{
  float Psource;
  float rA;
  float x0;
  float v0;
  float I;
	float K;
	float F;
	float fm;
	float fc;
	float kv;
};

extern struct YIJUAN_ROTARY_PLANT YiJuanPlant;
void Init_YiJuanPlant(void);

extern struct MYJOINT myjoint;
void Init_myjoint(void);
#endif
