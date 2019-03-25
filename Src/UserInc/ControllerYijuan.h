#ifndef __CONTROLLERYIJUAN_H
#define __CONTROLLERYIJUAN_H

#define mymin(X,Y) ((X) < (Y) ? (X) : (Y))
#define mymax(X,Y) ((X) < (Y) ? (Y) : (X))



struct SENSOR_DATA
{
  //key sensor data
  float pos;       
  float vel;       
  float p1;        
  float p2;
  float torque;   

  //other sensor data
  float posRaw;
  float posOffset;
  float p1dot;
  float p2dot;
  float p1Raw;
  float p2Raw;
  float torqueRaw;
};
/*extern struct SENSOR_DATA sensor_data;*/

struct MYERROR{
	float angle;
	float velocity;
	float x3;
	float x4;
};
/*extern struct MYERROR error;*/
struct CONTROLPARA{
	float kd;
	float kp;
	float ki;
	float k1;
	float k2;
};
/*extern struct CONTROLPARA controlPara;*/

struct EQUILIBRIUMCONTROLPARA{
	float kp;
	float ki;
	float kd;
};
/*extern struct EQUILIBRIUMCONTROLPARA eqControlPara;

extern float angle_nom[];
extern float velocity_nom[];
extern float acceleration_nom[];
extern float k_nom[];
extern float kdot_nom[];

extern float tau;
extern float k_actual;
extern float m1dpre,m2dpre,m1dpos,m2dpos,m1,m2,m1dplus,m2dplus,m1dmax,m2dmax,dm1,dm2;
extern float uCommand1,uCommand2;
extern float flow1_cal,flow2_cal;


extern float p1d,p2d;
extern float Pa;
extern float Pu;
extern float Plimit;*/
extern float x3d_ingre[];

void yisetAngle(float a);
void yisetStiffness(float k);
void yisetKp(float kp);
void yisetKd(float kd);
void yisetKi(float ki);
void yiinitControlPara();
void yiController();

#endif
