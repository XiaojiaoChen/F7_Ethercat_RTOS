#include "kalman.h"
#include "string.h"
#include <stdlib.h>
#include "stddef.h"




static void kalmanInitSizeMem(KALMAN_FILTER *s);
static void kalman_step(KALMAN_FILTER *s);

static void kalman_StoreMeasure(KALMAN_FILTER *ptKalmanFilter, uint8_t num,float z)
{
	ptKalmanFilter->Z.pData[num] = z;
}


static void kalman_setQ(KALMAN_FILTER *ptKalmanFilter, float *pQ)
{
	float dt=ptKalmanFilter->dt;
	if(ptKalmanFilter->kalmanType == KALMAN_CONST_VELOCITY)
		{
		ptKalmanFilter->Q.pData[0]=(*pQ)*dt*dt*dt*dt/4.0f;
		ptKalmanFilter->Q.pData[1]=(*pQ)*dt*dt*dt/2.0f;
		ptKalmanFilter->Q.pData[2]=(*pQ)*dt*dt*dt/2.0f;
		ptKalmanFilter->Q.pData[3]=(*pQ)*dt*dt;
		}
	else if(ptKalmanFilter->kalmanType == KALMAN_CONST_ACCELERATION)
	{
		ptKalmanFilter->Q.pData[0]=(*pQ)*dt*dt*dt*dt*dt*dt/36.0f;
		ptKalmanFilter->Q.pData[1]=(*pQ)*dt*dt*dt*dt*dt/12.0f;
		ptKalmanFilter->Q.pData[2]=(*pQ)*dt*dt*dt*dt/6.0f;
		ptKalmanFilter->Q.pData[3]=(*pQ)*dt*dt*dt*dt*dt/12.0f;
		ptKalmanFilter->Q.pData[4]=(*pQ)*dt*dt*dt*dt/4.0f;
		ptKalmanFilter->Q.pData[5]=(*pQ)*dt*dt*dt/2.0f;
		ptKalmanFilter->Q.pData[6]=(*pQ)*dt*dt*dt*dt/6.0f;
		ptKalmanFilter->Q.pData[7]=(*pQ)*dt*dt*dt/2.0f;
		ptKalmanFilter->Q.pData[8]=(*pQ)*dt*dt;
	}
}

static void kalman_setR(KALMAN_FILTER *ptKalmanFilter, float *pR)
{
	if(ptKalmanFilter->kalmanType == KALMAN_CONST_VELOCITY){
		ptKalmanFilter->R.pData[0]=*pR;
	}
	else if(ptKalmanFilter->kalmanType == KALMAN_CONST_ACCELERATION)
	{
		ptKalmanFilter->R.pData[0]=*pR;
		ptKalmanFilter->R.pData[1]=0;
		ptKalmanFilter->R.pData[2]=0;
		ptKalmanFilter->R.pData[3]=0;
		ptKalmanFilter->R.pData[4]=*(pR+1);
		ptKalmanFilter->R.pData[5]=0;
		ptKalmanFilter->R.pData[6]=0;
		ptKalmanFilter->R.pData[7]=0;
		ptKalmanFilter->R.pData[8]=*(pR+2);
	}
}


KALMAN_FILTER * KALMANFILTER(float *pQ, float *pR,float dt,uint16_t kalmanType)
{
	KALMAN_FILTER * ptKalmanFilter = (KALMAN_FILTER *)malloc(sizeof(KALMAN_FILTER));
	if(ptKalmanFilter==NULL)
		return NULL;
	memset(ptKalmanFilter,0,sizeof(KALMAN_FILTER));

	//allocate memory on heap basd on kalman filter kalmanType
	ptKalmanFilter->kalmanType = kalmanType;
	kalmanInitSizeMem(ptKalmanFilter);

	//attach methods
	ptKalmanFilter->step = kalman_step;
	ptKalmanFilter->setQ = kalman_setQ;
	ptKalmanFilter->setR = kalman_setR;
	ptKalmanFilter->store = kalman_StoreMeasure;

	//update rate 0.001s
	ptKalmanFilter->dt = dt;

	//init values
	if(kalmanType == KALMAN_CONST_ACCELERATION){
		ptKalmanFilter->A.pData[0]=1;
		ptKalmanFilter->A.pData[1]=dt;
		ptKalmanFilter->A.pData[2]=dt*dt/2;
		ptKalmanFilter->A.pData[3]=0;
		ptKalmanFilter->A.pData[4]=1;
		ptKalmanFilter->A.pData[5]=dt;
		ptKalmanFilter->A.pData[6]=0;
		ptKalmanFilter->A.pData[7]=0;
		ptKalmanFilter->A.pData[8]=1;

		ptKalmanFilter->B.pData[0]=0;
		ptKalmanFilter->B.pData[1]=0;
		ptKalmanFilter->B.pData[2]=1;

		ptKalmanFilter->H.pData[0]=1;
		ptKalmanFilter->H.pData[1]=0;
		ptKalmanFilter->H.pData[2]=0;
		ptKalmanFilter->H.pData[3]=0;
		ptKalmanFilter->H.pData[4]=1;
		ptKalmanFilter->H.pData[5]=0;
		ptKalmanFilter->H.pData[6]=0;
		ptKalmanFilter->H.pData[7]=0;
		ptKalmanFilter->H.pData[8]=1;

		arm_mat_trans_f32(&ptKalmanFilter->A,&ptKalmanFilter->At);
		arm_mat_trans_f32(&ptKalmanFilter->H,&ptKalmanFilter->Ht);
	}
	else if(kalmanType == KALMAN_CONST_VELOCITY){
		ptKalmanFilter->A.pData[0]=1;
		ptKalmanFilter->A.pData[1]=dt;
		ptKalmanFilter->A.pData[2]=0;
		ptKalmanFilter->A.pData[3]=1;

		ptKalmanFilter->B.pData[0]=dt*dt/2.0f;
		ptKalmanFilter->B.pData[1]=dt;

		ptKalmanFilter->H.pData[0]=1;
		ptKalmanFilter->H.pData[1]=0;
		
		arm_mat_trans_f32(&ptKalmanFilter->A,&ptKalmanFilter->At);
		arm_mat_trans_f32(&ptKalmanFilter->H,&ptKalmanFilter->Ht);
	}

	ptKalmanFilter->setQ(ptKalmanFilter,pQ);
	ptKalmanFilter->setR(ptKalmanFilter,pR);

	return ptKalmanFilter;
	
}






void kalmanInitSizeMem(KALMAN_FILTER *ptKalmanFilter)
{
	if(ptKalmanFilter->kalmanType == KALMAN_CONST_ACCELERATION){

		//allocate memory
		ptKalmanFilter->pMem = (void *)malloc(sizeof(KALMAN_STATE_MEM_FUL));
		KALMAN_STATE_MEM_FUL *pMemFul = (KALMAN_STATE_MEM_FUL *)(ptKalmanFilter->pMem);
		memset(pMemFul,0,sizeof(KALMAN_STATE_MEM_FUL));

		//link memory
		arm_mat_init_f32(&ptKalmanFilter->X,		N_State_Ful,			  1,	&(pMemFul->arrayX[0]));
		arm_mat_init_f32(&ptKalmanFilter->A,		N_State_Ful,	N_State_Ful,	&(pMemFul->arrayA[0]));
		arm_mat_init_f32(&ptKalmanFilter->B,		N_State_Ful,	M_Input_Ful,	&(pMemFul->arrayB[0]));
		arm_mat_init_f32(&ptKalmanFilter->U,		M_Input_Ful,			  1,	&(pMemFul->arrayU[0]));
		arm_mat_init_f32(&ptKalmanFilter->H,		L_Measure_Ful,	N_State_Ful,	&(pMemFul->arrayH[0]));
		arm_mat_init_f32(&ptKalmanFilter->Z,		L_Measure_Ful,			  1,	&(pMemFul->arrayZ[0]));
		arm_mat_init_f32(&ptKalmanFilter->P,		N_State_Ful,	N_State_Ful,	&(pMemFul->arrayP[0]));
		arm_mat_init_f32(&ptKalmanFilter->Q,		N_State_Ful,	N_State_Ful,	&(pMemFul->arrayQ[0]));
		arm_mat_init_f32(&ptKalmanFilter->R,		L_Measure_Ful,	L_Measure_Ful,	&(pMemFul->arrayR[0]));
		arm_mat_init_f32(&ptKalmanFilter->K,		N_State_Ful,	L_Measure_Ful,	&(pMemFul->arrayK[0]));
		arm_mat_init_f32(&ptKalmanFilter->At,	N_State_Ful,	N_State_Ful,	&(pMemFul->arrayAt[0]));
		arm_mat_init_f32(&ptKalmanFilter->Ht,	N_State_Ful,	L_Measure_Ful,	&(pMemFul->arrayHt[0]));
		arm_mat_init_f32(&ptKalmanFilter->NL,	N_State_Ful,	L_Measure_Ful,	&(pMemFul->arrayNL[0]));
		arm_mat_init_f32(&ptKalmanFilter->NN[0],	N_State_Ful,	N_State_Ful,	&(pMemFul->arrayNN[0][0]));
		arm_mat_init_f32(&ptKalmanFilter->NN[1],	N_State_Ful,	N_State_Ful,	&(pMemFul->arrayNN[1][0]));
		arm_mat_init_f32(&ptKalmanFilter->LL[0],	L_Measure_Ful,	L_Measure_Ful,	&(pMemFul->arrayLL[0][0]));
		arm_mat_init_f32(&ptKalmanFilter->LL[1],	L_Measure_Ful,	L_Measure_Ful,	&(pMemFul->arrayLL[1][0]));
		arm_mat_init_f32(&ptKalmanFilter->L[0] ,	L_Measure_Ful,			    1,	&(pMemFul->arrayL[0][0]));
		arm_mat_init_f32(&ptKalmanFilter->L[1] ,	L_Measure_Ful,				1,	&(pMemFul->arrayL[1][0]));
		arm_mat_init_f32(&ptKalmanFilter->N[0] ,	N_State_Ful,				1,	&(pMemFul->arrayN[0][0]));
		arm_mat_init_f32(&ptKalmanFilter->N[1] ,	N_State_Ful,				1,	&(pMemFul->arrayN[1][0]));

	}
	else if(ptKalmanFilter->kalmanType == KALMAN_CONST_VELOCITY ){

		//allocate memory
		ptKalmanFilter->pMem = (void *)malloc(sizeof(KALMAN_STATE_MEM_SIM));
		KALMAN_STATE_MEM_SIM *pMemSim = (KALMAN_STATE_MEM_SIM *)(ptKalmanFilter->pMem);
		memset(pMemSim,0,sizeof(KALMAN_STATE_MEM_SIM));

		//link memory to matrix
		arm_mat_init_f32(&ptKalmanFilter->X,		N_State_Sim,			  1,	&(pMemSim->arrayX[0]));
		arm_mat_init_f32(&ptKalmanFilter->A,		N_State_Sim,	N_State_Sim,	&(pMemSim->arrayA[0]));
		arm_mat_init_f32(&ptKalmanFilter->B,		N_State_Sim,	M_Input_Sim,	&(pMemSim->arrayB[0]));
		arm_mat_init_f32(&ptKalmanFilter->U,		M_Input_Sim,			  1,	&(pMemSim->arrayU[0]));
		arm_mat_init_f32(&ptKalmanFilter->H,		L_Measure_Sim,	N_State_Sim,	&(pMemSim->arrayH[0]));
		arm_mat_init_f32(&ptKalmanFilter->Z,		L_Measure_Sim,			  1,	&(pMemSim->arrayZ[0]));
		arm_mat_init_f32(&ptKalmanFilter->P,		N_State_Sim,	N_State_Sim,	&(pMemSim->arrayP[0]));
		arm_mat_init_f32(&ptKalmanFilter->Q,		N_State_Sim,	N_State_Sim,	&(pMemSim->arrayQ[0]));
		arm_mat_init_f32(&ptKalmanFilter->R,		L_Measure_Sim,	L_Measure_Sim,	&(pMemSim->arrayR[0]));
		arm_mat_init_f32(&ptKalmanFilter->K,		N_State_Sim,	L_Measure_Sim,	&(pMemSim->arrayK[0]));
		arm_mat_init_f32(&ptKalmanFilter->At,	N_State_Sim,	N_State_Sim,	&(pMemSim->arrayAt[0]));
		arm_mat_init_f32(&ptKalmanFilter->Ht,	N_State_Sim,	L_Measure_Sim,	&(pMemSim->arrayHt[0]));
		arm_mat_init_f32(&ptKalmanFilter->NL,	N_State_Sim,	L_Measure_Sim,	&(pMemSim->arrayNL[0]));
		arm_mat_init_f32(&ptKalmanFilter->NN[0],	N_State_Sim,	N_State_Sim,	&(pMemSim->arrayNN[0][0]));
		arm_mat_init_f32(&ptKalmanFilter->NN[1],	N_State_Sim,	N_State_Sim,	&(pMemSim->arrayNN[1][0]));
		arm_mat_init_f32(&ptKalmanFilter->LL[0],	L_Measure_Sim,	L_Measure_Sim,	&(pMemSim->arrayLL[0][0]));
		arm_mat_init_f32(&ptKalmanFilter->LL[1],	L_Measure_Sim,	L_Measure_Sim,	&(pMemSim->arrayLL[1][0]));
		arm_mat_init_f32(&ptKalmanFilter->L[0] ,	L_Measure_Sim,			    1,	&(pMemSim->arrayL[0][0]));
		arm_mat_init_f32(&ptKalmanFilter->L[1] ,	L_Measure_Sim,				1,	&(pMemSim->arrayL[1][0]));
		arm_mat_init_f32(&ptKalmanFilter->N[0] ,	N_State_Sim,				1,	&(pMemSim->arrayN[0][0]));
		arm_mat_init_f32(&ptKalmanFilter->N[1] ,	N_State_Sim,				1,	&(pMemSim->arrayN[1][0]));
	}
}


static void kalman_step(KALMAN_FILTER *s)
{
	//predict X=A*X
	arm_mat_mult_f32(&s->A,&s->X,&(s->N[0]));          //A*X -> N0  			 now N0 is a priori

	//predict P=A*P*At+Q
	arm_mat_mult_f32(&s->A,&s->P,&(s->NN[0]));         //A*P -> NN0
	arm_mat_mult_f32(&(s->NN[0]),&s->At,&(s->NN[1]));       //NN0*At -> NN1
	arm_mat_add_f32(&(s->NN[1]),&s->Q,&(s->NN[0]));         //NN1+Q -> NN0    		 now NN0 is a priori

	//kalman_gain K=P*Ht*Inv(H*P*Ht+R)
	 arm_mat_mult_f32(&(s->NN[0]),&s->Ht,&s->NL);     		//P*Ht -> NL
	 arm_mat_mult_f32(&s->H,&s->NL,&(s->LL[0]));     	 	//H*NL -> LL0
	 arm_mat_add_f32(&(s->LL[0]),&s->R,&(s->LL[1]));		//LL0+R -> LL1
	 arm_mat_inverse_f32(&(s->LL[1]),&(s->LL[0]));  		// Inv(LL1) -> LL0     side effect: LL1 turn to identity due to Gauss-Jordan method.
	 arm_mat_mult_f32(&s->NL,&(s->LL[0]),&s->K);       	//NL*LL0 -> K       	 now K is K

	//update X=X+K*(Z-H*X)
     arm_mat_mult_f32(&s->H,&(s->N[0]),&(s->L[0]));     	//H*N0 -> LN0
     arm_mat_sub_f32(&s->Z,&(s->L[0]),&(s->L[1]));          // (Z - LN0) -> LN1
     arm_mat_mult_f32(&s->K,&(s->L[1]),&(s->N[1])); 		//K*LN1 -> N1
	 arm_mat_add_f32(&(s->N[0]),&(s->N[1]),&s->X);     		//X+Ht_temp -> X         now X is a posteriori

  //update P=P-K*H*P
     arm_mat_mult_f32(&s->K,&s->H,&s->P);              	//K*H -> P
	 arm_mat_mult_f32(&s->P,&(s->NN[0]),&(s->NN[1]));       //P*NN0 -> NN1
	 arm_mat_sub_f32(&(s->NN[0]),&(s->NN[1]),&s->P);		//NN0-NN1 -> P      	 now P is a posteriori

}






/******************************************Kalman Filter Hub*********************************/

void kalmanHub_attach(struct KALMAN_FILTER_HUB_STRUCT *ptKalmanFilterHub, KALMAN_FILTER *ptKalmanFilter, uint16_t jointNum,uint16_t sensorSource)
{

	ptKalmanFilterHub->ptKalmanFilter[jointNum][sensorSource] = ptKalmanFilter;
	ptKalmanFilterHub->Num ++;

}


void kalmanHub_stepAll(struct KALMAN_FILTER_HUB_STRUCT *s)
{
	for(int i=0;i<1;i++)
		{
			if(s->ptKalmanFilter[i][0]!=NULL){
				//angle store
				s->ptKalmanFilter[i][0]->store(s->ptKalmanFilter[i][0],0,s->pParent->ptAngleHub->angles[i]);
				if(s->ptKalmanFilter[i][0]->kalmanType == KALMAN_CONST_ACCELERATION)
				{
					s->ptKalmanFilter[i][0]->store(s->ptKalmanFilter[i][0],1,s->pParent->ptIMUHub->IMUDevices[i]->AccData.RateX);
					s->ptKalmanFilter[i][0]->store(s->ptKalmanFilter[i][0],2,s->pParent->ptIMUHub->IMUDevices[i]->AccData.AngleAccel);
				}
				s->ptKalmanFilter[i][0]->step(s->ptKalmanFilter[i][0]);
			}

		    //pressure0 storee
			if(s->ptKalmanFilter[i][1]!=NULL){
				s->ptKalmanFilter[i][1]->store(s->ptKalmanFilter[i][1],0,s->pParent->ptPressureHub->Pressure[i][0]);
				s->ptKalmanFilter[i][1]->step(s->ptKalmanFilter[i][1]);
			}

			//pressure1 storee
			if(s->ptKalmanFilter[i][2]!=NULL){
				s->ptKalmanFilter[i][2]->store(s->ptKalmanFilter[i][2],0,s->pParent->ptPressureHub->Pressure[i][1]);
				s->ptKalmanFilter[i][2]->step(s->ptKalmanFilter[i][2]);
			}
		}

}


KALMAN_FILTER_HUB *KALMANFILTERHUB(struct CENTRAL_STRUCT *ptCentral)
{
	//new a kalmanfilterHub on the heap
	KALMAN_FILTER_HUB *ptKalmanFilterHub = (KALMAN_FILTER_HUB *)malloc(sizeof(KALMAN_FILTER_HUB));
	if(ptKalmanFilterHub == NULL)
		return NULL;
	memset(ptKalmanFilterHub,0,sizeof(KALMAN_FILTER_HUB));

	//parent
	ptCentral->ptKalmanFilterHub = ptKalmanFilterHub;
	ptKalmanFilterHub->pParent = ptCentral;

	//methods
	ptKalmanFilterHub->attach = kalmanHub_attach;
	ptKalmanFilterHub->stepAll = kalmanHub_stepAll;




	return ptKalmanFilterHub;
}








