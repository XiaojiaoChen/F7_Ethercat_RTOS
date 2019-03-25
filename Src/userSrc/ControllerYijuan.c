#include "ControllerYijuan.h"
#include "Controller.h"
#include "PlantModel.h"
#include "math.h"
#include "MPYEValve.h"
#include "myPID.h"
#include "Central.h"
float deltaT=0.001f;

float k_nom[1]={16}; //K+rA*gama*(120000/pi+120000/pi) ~= 12
float kdot_nom[1]={0};

float tau;
float k_actual;
float m1dpre, m2dpre, m1dpos, m2dpos, m1, m2, m1dplus, m2dplus, m1dmax, m2dmax,
		dm1, dm2;

float p1d, p2d;
float xeqd, xrestd, v1, v2;
float x3d_ingre[6];
float Pa = 101325;
float Pu = 301325;
float Plimit = 300000;

extern int verbose;
static float x00, x01, x02, x03;

static float u1, u2;
static float x0,x1, x2, x3, x4, x3dd, x4dd, p1, p2;
static float a1, a2, b2, c1, c2;
static float x3d, x4d;
static float gama = 1.4;
static float g = 9.8;
static float R = 287;
static float T = 300;

static float ss, ss1, ss2;
static float f1, f2, f0, Ff;
static float slaw, slaw1, slaw2;
static float calculateFriction(int);
static float mySAT(float, float);

struct SENSOR_DATA sensor_data;
struct CONTROLPARA controlPara;
struct MYERROR error;
static float Iterm=0;
float Imax=50;
float Imin=-50;
float x1pre=0;
float magicK=5;

void yiController() //update values in uCommand1 and uCommand2
{
	CONTROLLER_TYPE *ptController = ptCentral->ptControlHub->ptController[0];
	CONTROLLER_STATE *pS = &(ptController->state);

	float ulim = 0.9;



    
	//   float errlim=ulim/anglePIDP->Kp;
	x0=YiJuanPlant.x0;
	x1 = ptCentral->ptSensorData->angle[0];
	x2 = ptController->vel.Real;
	p1 = ptController->pre[0].Real;
	p2 = ptController->pre[1].Real;

 // x2=(x1-x1pre)/deltaT;
  x1pre=x1;
  if (x2 < 1 && x2 > 1)
    x2 = 0;
    
	x3 = p1 - p2;
	x4 = p1;


	Ff = YiJuanPlant.F;
	if (x2 < 0)
		Ff = -Ff;
	else if (x2 == 0)
		Ff = 0;

	x00 = x0 + x1;
	x01 = x0 - x1;

	/************feedback linearization control for theta**************/
	error.angle = ptController->pos.Err;
  if(error.angle<0.003 && error.angle>-0.003)
    error.angle = 0;
	error.velocity = x2 - ptController->vel.Nom;
  if(error.velocity<0.03 && error.velocity>-0.03)
    error.velocity= 0;

  Iterm = Iterm + error.angle*controlPara.ki;
  if(Iterm>Imax)
    Iterm = Imax;
  else if (Iterm < Imin)
    Iterm = Imin;
	x3d = ((YiJuanPlant.I * ptController->acc.Nom - controlPara.kd * error.velocity - controlPara.kp * error.angle - Iterm) + YiJuanPlant.K * x1+ magicK * x1+ Ff ) / YiJuanPlant.rA;
	x4d = (x3d*x00 +  (ptController->stiff.Nom - YiJuanPlant.K)*x00*x01/gama/YiJuanPlant.rA)/2/x0;

x3d_ingre[0] = - controlPara.kp * error.angle / YiJuanPlant.rA;
x3d_ingre[1] = - controlPara.kd * error.velocity/ YiJuanPlant.rA;
x3d_ingre[2] = YiJuanPlant.K * x1 / YiJuanPlant.rA;
x3d_ingre[3] = -Iterm / YiJuanPlant.rA;
  
  p1d=x4d;
  p2d=p1d-x3d;

  if(x3d>0){
    if(p1d>Plimit){
      p1d=Plimit;
      p2d=p1d-x3d;
      }
  }
  else{
    if(p2d>Plimit){
    p2d=Plimit;
    p1d=p2d+x3d;
    }
  }
  ptController->pre[0].Nom=p1d;
  ptController->pre[1].Nom=p2d;
	/*************************************Using valve*******************/
	x3dd = 0;
	x4dd = 0;

	//************feedback linearization for x4**************
	a1 = -gama * x2 / x00;
	c1 = gama * R * T / (YiJuanPlant.rA * x00);
	error.x4 = p1 - p1d;
	ss1 = error.x4;
	slaw1 = -controlPara.k1 * ss1;
	pS->flow1_cal = (-a1 * x4 + x4dd + slaw1) / c1;

	u1 = InverseValveFlowFunc(YiJuanPlant.Psource, p1, pS->flow1_cal, 1);
	pS->flow1_cal = valveFlowFunc(YiJuanPlant.Psource, p1, u1);
	// updatePID(anglePIDP,angle_nom[0],x1,&u1);

	//************feedback linearization for x4**************
	a2 = gama * x2 / x01;
	b2 = -2 * gama * x0 * x2 * x4 / (x00 * x01)
			+ gama * R * T * pS->flow1_cal / (YiJuanPlant.rA * x00);
	c2 = -gama * R * T / (YiJuanPlant.rA * x01);
	error.x3 = x3 - x3d;
	ss2 = error.x3;

	slaw2 = -controlPara.k2 * ss2; //-controlPara.ep2*mySAT(ss2,controlPara.thickness2);
	pS->flow2_cal = (-a2 * x3 - b2 + x3dd + slaw2) / c2;

	u2 = InverseValveFlowFunc(Pu, p2, pS->flow2_cal, 1);
	pS->flow2_cal = valveFlowFunc(Pu, p2, u2);

	ptController->pOut[0] = u1;
	ptController->pOut[1] = u2;

	ptController->stiff.Real = YiJuanPlant.K	+ YiJuanPlant.rA * gama	* (p1 / x00 + p2 / x01);
}

float mySAT(float x, float delta) {
	return mymin(mymax(x/delta,-1), 1);
}

void yiinitControlPara()
{
  controlPara.kp=30;
  controlPara.ki=0.5;
  controlPara.kd =0;
  controlPara.k1=15;
  controlPara.k2=15;
}

void yisetAngle(float a)
{
	ptCentral->ptNominalData->angle[0]=a;
}
void yisetStiffness(float k)
{
	ptCentral->ptNominalData->stiffness[0]=k;
}
void yisetKp(float kp)
{
  controlPara.kp = kp;
}

void yisetKd(float kd)
{
  controlPara.kd = kd;
}
void yisetKi(float ki)
{
  controlPara.ki = ki;
}

