#include <Central.h>
#include "Controller.h"
#include "stdlib.h"
#include "PlantModel.h"
#include "math.h"
#include "MPYEValve.h"
#include "myPID.h"

#include "trajectoryGeneration.h"
#include "string.h"
#include "cifXApplicationDemo.h"
//
//static float angle_Max[1] = {1.5};
//static float angle_Min[1] = {-1.5};
//
//
//static float ss, ss1, ss2;
//static float f1, f2, f0, Ff;
//static float slaw, slaw1, slaw2;
static float Patm = 101325.0f;

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

mCONTROLPARA mControlParaPreset[1] = {
{.kp = 10,	.ki = 1e-2,		.kd = 1e-1,		.kflow = 15, 	.stiffness = 20,	.ilim=1,	.ulim =4}     	 //HARD_QUICK
};
M_CONTROLLER_MODE mMode;


float A[2][2];
float B[2];

static void PSController_m(CONTROLLER_TYPE *ptController);
static void PSController_pm(CONTROLLER_TYPE *ptController);
static void PSController_p(CONTROLLER_TYPE *ptController);

/*This function simply does the control algorithm, without commanding actuators*/
void controller_controlFunc(CONTROLLER_TYPE *ptController) {

	APP_INPUT_DATA_T *pReal = ptController->pParent->pParent->ptSensorData;
	APP_OUTPUT_DATA_T *pNom = ptController->pParent->pParent->ptNominalData;
	uint16_t num = ptController->jointNum;
	ACTUATOR_HUB *ptActuatorHub = ptController->pParent->pParent->ptActuatorHub;
	int trajectorySource = 1;	 	//0:EtherCAT   1:Local

		if (trajectorySource == 0) {
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

		} else {
			/*get command type*/
			ptController->pControllerType = pNom->commandType[num];

			/*generate local nominal trajectory*/
			TrajGen(&(ptCentral->positionTrajectory[num]), HAL_GetTick());
			pNom->angle[num] = ptCentral->positionTrajectory[num].x_out;
			pNom->velocity[num] = ptCentral->positionTrajectory[num].v_out;
			pNom->acceleration[num] = ptCentral->positionTrajectory[num].a_out;

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
		}

		/*controlType specific block*/
		switch (ptController->pControllerType) {
		case PositionStiffnessControl:
			PSController_m(ptController);
			ptCentral->ptNominalData->pressure[num][0] = ptController->pre[0].Nom;
			ptCentral->ptNominalData->pressure[num][1] = ptController->pre[1].Nom;
			ptCentral->ptSensorData->stiffness[num] = ptController->stiff.Real;
			//or PSController_p();
			//or PSController_pm();
			break;

		case TorqueControl:

			break;

		}


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

	//parameter
	ptController->Pu = Patm + 201325; //update in the loop
	ptController->R = 287;
	ptController->T = 273.15+28; //could be updated in the loop
	ptController->g = 9.8;
	ptController->gama = 1.4;
	initPID(&(ptController->pid),mControlParaPreset[0].kp,mControlParaPreset[0].ki,mControlParaPreset[0].kd,mControlParaPreset[0].ilim,-mControlParaPreset[0].ilim,mControlParaPreset[0].ulim,-mControlParaPreset[0].ulim);

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




	return ptControllerHub;
}


/*************************************flow control************************************/
void PSController_m(CONTROLLER_TYPE *ptController) {

	 CONTROLLER_STATE *pS = &(ptController->state);

	 float x0 =myjoint.x0;
	 float x1 =ptController->pos.Real;
	 float x1d = ptController->pos.Nom;
	 float x2 =ptController->vel.Real;


	 float p1 =ptController->pre[0].Real;
	 float p2 =ptController->pre[1].Real;

	 float RT =  ptController->R * ptController->T;

//	 float G = myjoint.rotaryPlate.m * ptController->g * myjoint.rotaryPlate.com * cos(x1);
	 float Gr = myjoint.rotaryPlate.m * ptController->g * myjoint.rotaryPlate.com * cos(x1d);
	 float Grx = -myjoint.rotaryPlate.m * ptController->g * myjoint.rotaryPlate.com	* sin(x1d);

	// float Ff = (myjoint.shelinder1.fc + myjoint.shelinder2.fc) * myjoint.rotaryPlate.r + myjoint.rotaryPlate.fc;

	float  x00d = x0 + x1d;
	float  x01d = x0 - x1d;
	float  x00 = x0+x1;
	float  x01 = x0-x1;
	float  RTx02 = 2*RT*x0;
	ptController->Pu = ptCentral->ptRegulatorHub->pressureCommand[0];
	if(ptController->Pu>400001 || ptController->Pu<-1)
	{
		printf("wrong pressure source");
		ptController->Pu = 301325;
	}

	 if (x2 < 0.05 && x2 > -0.05)
		 x2 = 0;


	 pS->v1 = myjoint.rotaryPlate.r * myjoint.shelinder1.A * x00;
	 pS->v2 = myjoint.rotaryPlate.r * myjoint.shelinder2.A * x01;

	 pS->m1 = p1 * pS->v1 / RT;
	 pS->m2 = p2 * pS->v2 / RT;


	 if (ptController->pos.Err < 0.005 && ptController->pos.Err > -0.005)
		 {
			 x1 = x1d;
		 }
	 if(pS->positionFeedbackFlag){
			 //update m1d
			 updatePID(&ptController->pid, x1d, x1, &pS->m1dplus);

			 //update m2d maintaining stiffness unchanged
			 pS->m2dplus = -x00 * x00/x01/x01 * pS->m1dplus;
		 }
	 else {
		 pS->m1dplus = 0;
		 pS->m2dplus = 0;
	 }

	 A[0][0] = x00d*x00d/RTx02;
	 A[0][1] = A[0][0]*x01d/ptController->gama;
	 A[1][0] = -x01d*x01d/RTx02;
	 A[1][1] = -A[1][0]*x00d/ptController->gama;

	 B[0] = myjoint.I * ptController->acc.Nom + myjoint.K * ptController->pos.Nom + Gr +  pS->m1dplus;
	 B[1] = ptController->stiff.Nom - myjoint.K - Grx;

	 pS->m1dpos = A[0][0]*B[0]+A[0][1]*B[1];
	 pS->m2dpos = A[1][0]*B[0]+A[1][1]*B[1];


//	 pS->m1dpre = (x00d * x00d * (myjoint.I * ptController->acc.Nom + myjoint.K * ptController->pos.Nom + Gr )
//			 	 + x00d * x00d * x01d * ( ptController->stiff.Nom - myjoint.K - Grx) / ptController->gama)
//				/ (2 *RT * x0);
//	 pS->m2dpre = (-x01d * x01d* (myjoint.I * ptController->acc.Nom + myjoint.K * ptController->pos.Nom + Gr )
//			     + x01d * x01d * x00d* (ptController->stiff.Nom - myjoint.K - Grx) / ptController->gama )
//				/ (2 * RT * x0);


	 ptController->pre[0].Nom =  pS->m1dpos*RT/ pS->v1;
	 ptController->pre[1].Nom =  pS->m2dpos*RT/ pS->v2;

	 ptController->stiff.Real =  myjoint.K	- myjoint.rotaryPlate.m * ptController->g * myjoint.rotaryPlate.com * sin(x1)
				+ RT * ptController->gama	* (pS->m1/x00/x00 + pS->m2/x01/x01);

	 pS->flow1_cal = -mControlPara.kflow * (pS->m1 - pS->m1dpos);
	 pS->flow2_cal = -mControlPara.kflow * (pS->m2 - pS->m2dpos);

	 ptController->pOut[0] = InverseValveFlowFunc(ptController->Pu, p1, pS->flow1_cal, 1);
	 ptController->pOut[1] = InverseValveFlowFunc(ptController->Pu, p2, pS->flow2_cal, 1);


}

void PSController_pm(CONTROLLER_TYPE *ptController) {


}

void PSController_p(CONTROLLER_TYPE *ptController) //update values in uCommand1 and uCommand2
{
//	float ulim = 0.9;
//
//	 x1 = kalman_rotation.X.pData[0];
//	 x2 = kalman_rotation.X.pData[1];
//	 p1 = kalman_pressure[0].X.pData[0] + Pa;
//	 p2 = kalman_pressure[1].X.pData[0] + Pa;
//	 if (x2 < 0.05 && x2 > -0.05)
//	 x2 = 0;
//	 x3 = p1 - p2;
//	 x4 = p1;
//
//	 f0=calculateFriction(0);
//	 f1=calculateFriction(1);
//	 f2=calculateFriction(2);
//	 Ff=(f1-f2)*myjoint.rotaryPlate.r+f0;
//
//	 Ff = (myjoint.shelinder1.fc + myjoint.shelinder2.fc) * myjoint.rotaryPlate.r
//	 + myjoint.rotaryPlate.fc;
//	 if (x2 < 0)
//	 Ff = -Ff;
//	 else if (x2 == 0)
//	 Ff = 0;
//
//	 G = myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com * cos(x1);
//	 Gr = myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com * cos(angle_nom[0]);
//
//	 tem_ra = myjoint.rotaryPlate.r * myjoint.shelinder1.A;
//	 tem_laddx = myjoint.lamda + x1;
//	 tem_lsubx = myjoint.lamda - x1;
//
//	 error.angle = x1 - angle_nom[0];
//	 error.velocity = x2 - velocity_nom[0];
//
//	 x3d = ((myjoint.I * acceleration_nom[0] - pControlPara.kd * error.velocity
//	 - pControlPara.kp * error.angle) + myjoint.K * x1 + Ff + G) / tem_ra;
//	 x3d_ingre[0] = myjoint.I * acceleration_nom[0] / tem_ra;
//	 x3d_ingre[1] = -pControlPara.kd * error.velocity / tem_ra;
//	 x3d_ingre[2] = -pControlPara.kp * error.angle / tem_ra;
//	 x3d_ingre[3] = myjoint.K * x1 / tem_ra;
//	 x3d_ingre[4] = Ff / tem_ra;
//	 x3d_ingre[5] = G / tem_ra;
//	 x4d = (x3d * (myjoint.lamda + angle_nom[0]) * tem_ra * gama
//	 + (k_nom[0] - myjoint.K
//	 + myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com
//	 * sin(angle_nom[0]))
//	 * (myjoint.lamda + angle_nom[0])
//	 * (myjoint.lamda - angle_nom[0]))
//	 / (2 * myjoint.lamda * tem_ra * gama);
//	 //  x4d=130000;
//
//	 dp=x4d-x3d;
//	 if(dp>Pa&&x4d<=Pa)
//	 x4d=Pa;
//	 else if(dp<=Pa&&x4d>Pa)
//	 x4d=Pa+x3d;
//	 else if(dp<=Pa&&x4d<=Pa &&x3d<=0)
//	 x4d=Pa;
//	 else if(dp<=Pa&&x4d<=Pa&&x3d>0)
//	 x4d=Pa+x3d;
//
//	 if(dp<=Pu&&x4d>Pu)
//	 x4d=Pu;
//	 else if(dp>Pu&&x4d<=Pu)
//	 x4d=Pu+x3d;
//	 else if(dp>Pu&&x4d>Pu&&x3d>0)
//	 x4d=Pu;
//	 else if(dp>Pu&&x4d>Pu&&x3d<=0)
//	 x4d=Pu+x3d;
//
//	 p1d=x4d;
//	 p2d=x4d-x3d;
//
//
//	 if (x3d > 0) {
//	 p2d = 101325;
//	 p1d = x3d + p2;
//	 if (p1d > Pu)
//	 p1d = Pu;
//	 } else {
//	 p1d = 101325;
//	 p2d = p1 - x3d;
//	 if (p2d > Pu)
//	 p2d = Pu;
//	 }
//
//	 x3dd = 0;
//	 x4dd = 0;
//
//	 a1 = -gama * x2 / tem_laddx;
//	 c1 = gama * R * T / (tem_ra * tem_laddx);
//	 error.x4 = p1 - p1d;
//	 ss1 = error.x4;
//	 slaw1 = -pControlPara.k1 * ss1;
//	 flow1_cal = (-a1 * x4 + x4dd + slaw1) / c1;
//
//	 u1 = InverseValveFlowFunc(myjoint.Psource, p1, flow1_cal, 1);
//	 flow1_cal = valveFlowFunc(myjoint.Psource, p1, u1);
//	 // updatePID(anglePIDP,angle_nom[0],x1,&u1);
//
//	 a2 = gama * x2 / tem_lsubx;
//	 b2 = -2 * gama * myjoint.lamda * x2 * x4 / (tem_laddx * tem_lsubx)
//	 + gama * R * T * flow1_cal / (tem_ra * tem_laddx);
//	 c2 = -gama * R * T / (tem_ra * tem_lsubx);
//	 error.x3 = x3 - x3d;
//	 ss2 = error.x3;
//
//	 slaw2 = -pControlPara.k2 * ss2; //-controlPara.ep2*mySAT(ss2,controlPara.thickness2);
//	 flow2_cal = (-a2 * x3 - b2 + x3dd + slaw2) / c2;
//
//	 u2 = InverseValveFlowFunc(myjoint.Psource, p2, flow2_cal, 1);
//	 flow2_cal = valveFlowFunc(myjoint.Psource, p2, u2);
//
//	 uCommand1 = u1;
//	 uCommand2 = u2;
//
//	 k_actual = myjoint.K
//	 - myjoint.rotaryPlate.m * g * myjoint.rotaryPlate.com * sin(x1)
//	 + tem_ra * gama
//	 * (p1 / (myjoint.lamda + x1) + p2 / (myjoint.lamda - x1));
}

void toruqeController()
{

}

void pressureController()
{

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
