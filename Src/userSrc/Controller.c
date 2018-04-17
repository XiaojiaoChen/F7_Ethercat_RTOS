#include <Central.h>
#include "Controller.h"
#include "stdlib.h"
/*
 #include "PlantModel.h"
 #include "math.h"
 #include "valveFlowFunc.h"
 #include "spi.h"
 #include "kalman.h"
 #include "myPID.h"
 #include "pressureRegulator_ITV2030.h"
 #include "LTC2668.h"
 #include "trajectoryGeneration.h"


 float angle_nom[1] = { 0.0f };
 float velocity_nom[1] = { 0.0f };
 float acceleration_nom[1] = { 0.0f };
 float k_nom[1]={20};
 float kdot_nom[1]={0};
 float kddot_nom[1] = {0};




 float tau;
 float k_actual;
 float m1dpre, m2dpre, m1dpos, m2dpos, m1, m2, m1dplus, m2dplus, m1dmax, m2dmax,
 dm1, dm2;
 float uCommand1, uCommand2;
 float flow1_cal, flow2_cal;

 float pressureSaturation[2];
 float p1d, p2d;
 float xeqd, xrestd, v1, v2;
 float x3d_ingre[6];

 uint16_t hardness = 1;
 uint16_t quickness = 0;
 uint16_t tauEffectiveFlag = 0;
 uint16_t positionFeedbackFlag = 0;

 static float x00, x01, x02, x03;

 static float Pa = 101325;
 static float Pu = 251325;
 static float u1, u2;
 static float x1, x2, x3, x4, x3dd, x4dd, p1, p2;
 static float a1, a2, b2, c1, c2;
 static float tem_ra, tem_laddx, tem_lsubx;
 static float x3d, x4d;
 static float G, Gr;
 static float gama = 1.4;
 static float g = 9.8;
 static float R = 287;
 static float T = 300;
 static float G, Gr, Grx;
 static float tauZeroBound = 0.5;
 static float tauEffectiveBound = 2;

 static float angle_Max[1] = {1.5};
 static float angle_Min[1] = {-1.5};


 static float ss, ss1, ss2;
 static float f1, f2, f0, Ff;
 static float slaw, slaw1, slaw2;

 pCONTROLPARA pControlPara ={
 .kd = 0.5,
 .kp = 40,
 .kpeq = 20,
 .k1 = 30,
 .ep1 = 0.5,
 .thickness1 =0.1,
 .k2 = 30,
 .ep2 = 0.5,
 .thickness2 = 0.1,
 };

 mCONTROLPARA mControlPara ={
 .kp = 5e-4,
 .ki = 1e-4,
 .kd = 0.001,
 .kflow = 20,
 .stiffness = 12
 };

 ERRORDATA error = {
 .angle = 0,
 .velocity = 0,
 .x3 = 0,
 .x4 = 0
 };

 mCONTROLPARA mControlParaPreset[4] = {
 {.kp = 5e-4,	.ki = 1e-4,		.kd = 1e-5,		.kflow = 20, 	.stiffness = 20,		.ulim =5e-5},     	 //HARD_QUICK
 {.kp = 5e-4,	.ki = 1e-4,		.kd = 1e-5,		.kflow = 10,	.stiffness = 20,		.ulim =5e-5},		 //HARD_SLOW
 {.kp = 5e-5,	.ki = 1e-3,		.kd = 0,		.kflow = 20,	.stiffness = 11,		.ulim =5e-5},		 //SOFT_QUICK
 {.kp = 5e-5,	.ki = 1e-3,		.kd = 0,		.kflow = 10,	.stiffness = 11,		.ulim =5e-5},	 	//SOFT_SLOW
 };
 M_CONTROLLER_MODE mMode;
 */
#include "string.h"
#include "cifXApplicationDemo.h"


/*This function simply does the control algorithm, without commanding actuators*/
void controller_controlFunc(CONTROLLER_TYPE *ptController) {

	APP_INPUT_DATA_T *pReal = ptController->pParent->pParent->ptSensorData;
	APP_OUTPUT_DATA_T *pNom = ptController->pParent->pParent->ptNominalData;
	uint16_t num = ptController->jointNum;
	ACTUATOR_HUB *ptActuatorHub = ptController->pParent->pParent->ptActuatorHub;
	/*get command type*/
	ptController->pControllerType = pNom->commandType[num];

	/*retrieve measured data and nominal data to local buffer*/
	ptController->pos.Real = pReal->angle[num];
	ptController->pos.Nom = pNom->angle[num];
	ptController->pos.Err = ptController->pos.Nom - ptController->pos.Real;

	ptController->vel.Real = pReal->velocity[num];
	ptController->vel.Nom = pNom->velocity[num];
	ptController->vel.Err = ptController->vel.Nom - ptController->vel.Real;

	ptController->acc.Real = pReal->acceleration[num];
	ptController->acc.Nom = pNom->acceleration[num];
	ptController->acc.Err = ptController->acc.Nom - ptController->acc.Real;

	ptController->pre[0].Real = pReal->pressure[num][0];
	ptController->pre[0].Nom = pNom->pressure[num][0];
	ptController->pre[0].Err = ptController->pre[0].Nom - ptController->pre[0].Real;

	ptController->pre[1].Real = pReal->pressure[num][1];
	ptController->pre[1].Nom = pNom->pressure[num][1];
	ptController->pre[1].Err = ptController->pre[1].Nom - ptController->pre[1].Real;

	ptController->tor.Real = pReal->torque[num];
	ptController->tor.Nom = pNom->torque[num];
	ptController->tor.Err = ptController->tor.Nom - ptController->tor.Real;

	ptController->stiff.Real = pReal->stiffness[num];
	ptController->stiff.Nom = pNom->stiffness[num];
	ptController->stiff.Err = ptController->stiff.Nom - ptController->stiff.Real;




	/*common control block*/





	/*controlType specific block*/
	switch(ptController->pControllerType) {
			   case PositionStiffnessControl:

			      break;

			   case TorqueControl:

			      break;

	}


	/*Control Output in local buffer*/
	ptController->pOut[0] = 5.0f;
	ptController->pOut[1] = 5.0f;

	/*Control output to hardware buffer,ready for act*/
	ptActuatorHub->actuator[num][0]->command = ptController->pOut[0];
	ptActuatorHub->actuator[num][1]->command = ptController->pOut[1];



}


CONTROLLER_TYPE *CONTROLLER(uint16_t jointNum)
{

	//New a controller on the heap
	CONTROLLER_TYPE *ptController = (CONTROLLER_TYPE *)malloc(sizeof(CONTROLLER_TYPE));
	if(ptController == NULL)
		return NULL;
	memset(ptController,0,sizeof(CONTROLLER_TYPE));

	ptController->jointNum = jointNum;

	//implement function
	ptController->control = controller_controlFunc;

	return ptController;
}





static void controllerHub_control(struct CONTROLLER_HUB_STRUCT *ptControllerHub, uint16_t num)
{

	CONTROLLER_TYPE *ptController = ptControllerHub->ptController[num];
	ptController->control(ptController);
}

static void controllerHub_controlAll(struct CONTROLLER_HUB_STRUCT *ptControllerHub)
{
	for(int i=0;i<ptControllerHub->num;i++)
	{
		ptControllerHub->control(ptControllerHub,i);
	}
}



static void controllerHub_attach(CONTROLLER_HUB *ptControllerHub,CONTROLLER_TYPE *ptController)
{
	ptControllerHub->ptController[ptController->jointNum] = ptController;
	ptController->pParent = ptControllerHub;
	ptControllerHub->num++;
}




CONTROLLER_HUB* CONTROLLERHUB(CENTRAL *ptCentral)
{

	//New a controlHub on the heap
	CONTROLLER_HUB * ptControllerHub = (CONTROLLER_HUB *)malloc(sizeof(CONTROLLER_HUB));
	if(ptControllerHub == NULL)
		return NULL;
	memset(ptControllerHub, 0, sizeof(CONTROLLER_HUB));

	//add parent
	ptControllerHub->pParent =  ptCentral;
	ptCentral->ptControlHub = ptControllerHub;


	//attach methods
	ptControllerHub->control = controllerHub_control;
	ptControllerHub->controlAll = controllerHub_controlAll;
	ptControllerHub->attach = controllerHub_attach;


	//New a controller on the heap
	CONTROLLER_TYPE *ptController;

	ptController= CONTROLLER(0);
	ptControllerHub->attach(ptControllerHub,ptController);

	ptController = CONTROLLER(1);
	ptControllerHub->attach(ptControllerHub,ptController);

	ptController = CONTROLLER(2);
	ptControllerHub->attach(ptControllerHub,ptController);


	ptController = CONTROLLER(3);
	ptControllerHub->attach(ptControllerHub,ptController);

	return ptControllerHub;
}

void equilibriumPointController() {
	/*float x0 = 0.2 / myjoint.rotaryPlate.r;
	 float dentemp;
	 float v12;
	 x1 = kalman_rotation.X.pData[0];
	 x2 = kalman_rotation.X.pData[1];
	 p1 = kalman_pressure[0].X.pData[0] + Pa;
	 p2 = kalman_pressure[1].X.pData[0] + Pa;
	 if (x2 < 0.05 && x2 > -0.05)
	 x2 = 0;
	 x3 = p1 - p2;
	 x4 = p1;

	 Ff = (myjoint.shelinder1.fc + myjoint.shelinder2.fc) * myjoint.rotaryPlate.r
	 + myjoint.rotaryPlate.fc;

	 G = myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com * cos(x1);
	 Gr = myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com * cos(angle_nom[0]);
	 Grx = -myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com	* sin(angle_nom[0]);


	 xeqd = angle_nom[0];

	 x00 = x0 + xeqd;
	 x01 = x0 - xeqd;
	 v1 = myjoint.rotaryPlate.r * myjoint.shelinder1.A * (x0 + x1);
	 v2 = myjoint.rotaryPlate.r * myjoint.shelinder2.A * (x0 - x1);
	 v12 = v1 / v2;
	 m1 = p1 * v1 / R / T;
	 m2 = p2 * v2 / R / T;

	 m1dpre = (x00 * x00	* (myjoint.I * acceleration_nom[0] + myjoint.K * angle_nom[0] + Gr ) + x00 * x00 * x01 / gama * (k_nom[0] - myjoint.K - Grx))
	 / (2 * R * T * x0);
	 m2dpre = (-x01 * x01* (myjoint.I * acceleration_nom[0] + myjoint.K * angle_nom[0] + Gr ) + x01 * x01 * x00 / gama * (k_nom[0] - myjoint.K - Grx))
	 / (2 * R * T * x0);

	 //feedback of position to modify m1d and m2d
	 if (positionFeedbackFlag == 1) {
	 //accepted error bound
	 error.angle = x1 - xeqd;
	 if (error.angle < 0.005 && error.angle > -0.005)
	 x1 = xeqd;
	 //update m1d
	 updatePID(anglePIDP, xeqd, x1, &m1dplus);

	 //update m2d maintaining stiffness unchanged
	 m2dplus = -v12 * v12 * m1dplus;

	 } else {
	 m1dplus = 0;
	 m2dplus = 0;
	 }

	 m1dpos = m1dpre + m1dplus;
	 m2dpos = m2dpre + m2dplus;


	 flow1_cal = -mControlPara.kflow * (m1 - m1dpos);
	 flow2_cal = -mControlPara.kflow * (m2 - m2dpos);

	 u1 = InverseValveFlowFunc(myjoint.Psource, p1, flow1_cal, 1);
	 u2 = InverseValveFlowFunc(myjoint.Psource, p2, flow2_cal, 1);

	 uCommand1 = u1;
	 uCommand2 = u2;*/

}

void backSteppingController() //update values in uCommand1 and uCommand2
{
	/*float ulim = 0.9;

	 x1 = kalman_rotation.X.pData[0];
	 x2 = kalman_rotation.X.pData[1];
	 p1 = kalman_pressure[0].X.pData[0] + Pa;
	 p2 = kalman_pressure[1].X.pData[0] + Pa;
	 if (x2 < 0.05 && x2 > -0.05)
	 x2 = 0;
	 x3 = p1 - p2;
	 x4 = p1;

	 f0=calculateFriction(0);
	 f1=calculateFriction(1);
	 f2=calculateFriction(2);
	 Ff=(f1-f2)*myjoint.rotaryPlate.r+f0;

	 Ff = (myjoint.shelinder1.fc + myjoint.shelinder2.fc) * myjoint.rotaryPlate.r
	 + myjoint.rotaryPlate.fc;
	 if (x2 < 0)
	 Ff = -Ff;
	 else if (x2 == 0)
	 Ff = 0;

	 G = myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com * cos(x1);
	 Gr = myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com * cos(angle_nom[0]);

	 tem_ra = myjoint.rotaryPlate.r * myjoint.shelinder1.A;
	 tem_laddx = myjoint.lamda + x1;
	 tem_lsubx = myjoint.lamda - x1;

	 error.angle = x1 - angle_nom[0];
	 error.velocity = x2 - velocity_nom[0];

	 x3d = ((myjoint.I * acceleration_nom[0] - pControlPara.kd * error.velocity
	 - pControlPara.kp * error.angle) + myjoint.K * x1 + Ff + G) / tem_ra;
	 x3d_ingre[0] = myjoint.I * acceleration_nom[0] / tem_ra;
	 x3d_ingre[1] = -pControlPara.kd * error.velocity / tem_ra;
	 x3d_ingre[2] = -pControlPara.kp * error.angle / tem_ra;
	 x3d_ingre[3] = myjoint.K * x1 / tem_ra;
	 x3d_ingre[4] = Ff / tem_ra;
	 x3d_ingre[5] = G / tem_ra;
	 x4d = (x3d * (myjoint.lamda + angle_nom[0]) * tem_ra * gama
	 + (k_nom[0] - myjoint.K
	 + myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com
	 * sin(angle_nom[0]))
	 * (myjoint.lamda + angle_nom[0])
	 * (myjoint.lamda - angle_nom[0]))
	 / (2 * myjoint.lamda * tem_ra * gama);
	 //  x4d=130000;

	 dp=x4d-x3d;
	 if(dp>Pa&&x4d<=Pa)
	 x4d=Pa;
	 else if(dp<=Pa&&x4d>Pa)
	 x4d=Pa+x3d;
	 else if(dp<=Pa&&x4d<=Pa &&x3d<=0)
	 x4d=Pa;
	 else if(dp<=Pa&&x4d<=Pa&&x3d>0)
	 x4d=Pa+x3d;

	 if(dp<=Pu&&x4d>Pu)
	 x4d=Pu;
	 else if(dp>Pu&&x4d<=Pu)
	 x4d=Pu+x3d;
	 else if(dp>Pu&&x4d>Pu&&x3d>0)
	 x4d=Pu;
	 else if(dp>Pu&&x4d>Pu&&x3d<=0)
	 x4d=Pu+x3d;

	 p1d=x4d;
	 p2d=x4d-x3d;


	 if (x3d > 0) {
	 p2d = 101325;
	 p1d = x3d + p2;
	 if (p1d > Pu)
	 p1d = Pu;
	 } else {
	 p1d = 101325;
	 p2d = p1 - x3d;
	 if (p2d > Pu)
	 p2d = Pu;
	 }

	 x3dd = 0;
	 x4dd = 0;

	 a1 = -gama * x2 / tem_laddx;
	 c1 = gama * R * T / (tem_ra * tem_laddx);
	 error.x4 = p1 - p1d;
	 ss1 = error.x4;
	 slaw1 = -pControlPara.k1 * ss1;
	 flow1_cal = (-a1 * x4 + x4dd + slaw1) / c1;

	 u1 = InverseValveFlowFunc(myjoint.Psource, p1, flow1_cal, 1);
	 flow1_cal = valveFlowFunc(myjoint.Psource, p1, u1);
	 // updatePID(anglePIDP,angle_nom[0],x1,&u1);

	 a2 = gama * x2 / tem_lsubx;
	 b2 = -2 * gama * myjoint.lamda * x2 * x4 / (tem_laddx * tem_lsubx)
	 + gama * R * T * flow1_cal / (tem_ra * tem_laddx);
	 c2 = -gama * R * T / (tem_ra * tem_lsubx);
	 error.x3 = x3 - x3d;
	 ss2 = error.x3;

	 slaw2 = -pControlPara.k2 * ss2; //-controlPara.ep2*mySAT(ss2,controlPara.thickness2);
	 flow2_cal = (-a2 * x3 - b2 + x3dd + slaw2) / c2;

	 u2 = InverseValveFlowFunc(myjoint.Psource, p2, flow2_cal, 1);
	 flow2_cal = valveFlowFunc(myjoint.Psource, p2, u2);

	 uCommand1 = u1;
	 uCommand2 = u2;

	 k_actual = myjoint.K
	 - myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com * sin(x1)
	 + tem_ra * gama
	 * (p1 / (myjoint.lamda + x1) + p2 / (myjoint.lamda - x1));
	 */
}

/****** small passive stiffness, strong position feedback
 * desired behavior: soft, quick
 */
void setmControllerMode(M_CONTROLLER_MODE mode) {
	/*tuningPID(anglePIDP, mControlParaPreset[mode].kp,mControlParaPreset[mode].ki,mControlParaPreset[mode].kd);
	 UpdateTraj(&stiffnessTrajectory,mControlParaPreset[mode].stiffness,HAL_GetTick(),0.01,TRAJ_GEN_STEP_SCURVE);
	 */}

void setPosition(float a) {
	/*	angle_nom[0] = a;
	 velocity_nom[0] = 0;
	 acceleration_nom[0] = 0;*/
}
void setStiffness(float k) {
	/*	k_nom[0] = k;
	 kdot_nom[0] = 0;
	 kddot_nom[0] = 0;*/
}
