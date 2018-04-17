#include "kalman.h"


KALMAN_TYPE FulTypeKalman=Kalman_Ful;
KALMAN_TYPE SimTypeKalman=Kalman_Sim;


KALMAN_FILTER kalman_rotation;
KALMAN_FILTER kalman_pressure[2];
KALMAN_FILTER kalman_torque;

static void kalmanInitSizeMem(KALMAN_FILTER *s,KALMAN_TYPE type);
static void kalman_step(KALMAN_FILTER *s);


void kalman_Init(KALMAN_FILTER *s, float *q, float *r,float dt,uint8_t type)
{
	kalmanInitSizeMem(s,type);
	s->step = kalman_step;
	s->dt = dt;
	if(type == Kalman_Ful){
		s->A.pData[0]=1;
		s->A.pData[1]=dt;
		s->A.pData[2]=dt*dt/2;
		s->A.pData[3]=0;
		s->A.pData[4]=1;
		s->A.pData[5]=dt;
		s->A.pData[6]=0;
		s->A.pData[7]=0;
		s->A.pData[8]=1;

		s->B.pData[0]=0;
		s->B.pData[1]=0;
		s->B.pData[2]=1;

		s->Q.pData[0]=(*q)*dt*dt*dt*dt*dt*dt/36.0f;
		s->Q.pData[1]=(*q)*dt*dt*dt*dt*dt/12.0f;
		s->Q.pData[2]=(*q)*dt*dt*dt*dt/6.0f;
		s->Q.pData[3]=(*q)*dt*dt*dt*dt*dt/12.0f;
		s->Q.pData[4]=(*q)*dt*dt*dt*dt/4.0f;
		s->Q.pData[5]=(*q)*dt*dt*dt/2.0f;
		s->Q.pData[6]=(*q)*dt*dt*dt*dt/6.0f;
		s->Q.pData[7]=(*q)*dt*dt*dt/2.0f;
		s->Q.pData[8]=(*q)*dt*dt;


		s->R.pData[0]=*r;
		s->R.pData[1]=0;
		s->R.pData[2]=0;
		s->R.pData[3]=0;
		s->R.pData[4]=*(r+1);
		s->R.pData[5]=0;
		s->R.pData[6]=0;
		s->R.pData[7]=0;
		s->R.pData[8]=*(r+2);
		
		s->H.pData[0]=1;
		s->H.pData[1]=0;
		s->H.pData[2]=0;
		s->H.pData[3]=0;
		s->H.pData[4]=1;
		s->H.pData[5]=0;
		s->H.pData[6]=0;
		s->H.pData[7]=0;
		s->H.pData[8]=1;

		arm_mat_trans_f32(&s->A,&s->At);
		arm_mat_trans_f32(&s->H,&s->Ht);
	}
	else if(type == Kalman_Sim){
		s->A.pData[0]=1;
		s->A.pData[1]=dt;
		s->A.pData[2]=0;
		s->A.pData[3]=1;

		s->B.pData[0]=dt*dt/2.0f;
		s->B.pData[1]=dt;
		
		s->Q.pData[0]=(*q)*dt*dt*dt*dt/4.0f;
		s->Q.pData[1]=(*q)*dt*dt*dt/2.0f;
		s->Q.pData[2]=(*q)*dt*dt*dt/2.0f;
		s->Q.pData[3]=(*q)*dt*dt;

		s->R.pData[0]=*r;

		s->H.pData[0]=1;
		s->H.pData[1]=0;
		
		arm_mat_trans_f32(&s->A,&s->At);
		arm_mat_trans_f32(&s->H,&s->Ht);
	}

	
}

void kalman_StoreMeasure(KALMAN_FILTER *s, uint8_t num,float z)
{
	s->Z.pData[num] = z;
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




void kalmanInitSizeMem(KALMAN_FILTER *s,KALMAN_TYPE type)
{
	s->type = type;
if(type == Kalman_Ful){
	arm_mat_init_f32(&s->X,		N_State_Ful,			  1,	&(s->memFul.arrayX[0]));
	arm_mat_init_f32(&s->A,		N_State_Ful,	N_State_Ful,	&(s->memFul.arrayA[0]));
	arm_mat_init_f32(&s->B,		N_State_Ful,	M_Input_Ful,	&(s->memFul.arrayB[0]));
	arm_mat_init_f32(&s->U,		M_Input_Ful,			  1,	&(s->memFul.arrayU[0]));
	arm_mat_init_f32(&s->H,		L_Measure_Ful,	N_State_Ful,	&(s->memFul.arrayH[0]));
	arm_mat_init_f32(&s->Z,		L_Measure_Ful,			  1,	&(s->memFul.arrayZ[0]));
	arm_mat_init_f32(&s->P,		N_State_Ful,	N_State_Ful,	&(s->memFul.arrayP[0]));
	arm_mat_init_f32(&s->Q,		N_State_Ful,	N_State_Ful,	&(s->memFul.arrayQ[0]));
	arm_mat_init_f32(&s->R,		L_Measure_Ful,	L_Measure_Ful,	&(s->memFul.arrayR[0]));
	arm_mat_init_f32(&s->K,		N_State_Ful,	L_Measure_Ful,	&(s->memFul.arrayK[0]));
	arm_mat_init_f32(&s->At,	N_State_Ful,	N_State_Ful,	&(s->memFul.arrayAt[0]));
	arm_mat_init_f32(&s->Ht,	N_State_Ful,	L_Measure_Ful,	&(s->memFul.arrayHt[0]));
	arm_mat_init_f32(&s->NL,	N_State_Ful,	L_Measure_Ful,	&(s->memFul.arrayNL[0]));
	arm_mat_init_f32(&s->NN[0],	N_State_Ful,	N_State_Ful,	&(s->memFul.arrayNN[0][0]));
	arm_mat_init_f32(&s->NN[1],	N_State_Ful,	N_State_Ful,	&(s->memFul.arrayNN[1][0]));
	arm_mat_init_f32(&s->LL[0],	L_Measure_Ful,	L_Measure_Ful,	&(s->memFul.arrayLL[0][0]));
	arm_mat_init_f32(&s->LL[1],	L_Measure_Ful,	L_Measure_Ful,	&(s->memFul.arrayLL[1][0]));
	arm_mat_init_f32(&s->L[0] ,	L_Measure_Ful,			    1,	&(s->memFul.arrayL[0][0]));
	arm_mat_init_f32(&s->L[1] ,	L_Measure_Ful,				1,	&(s->memFul.arrayL[1][0]));
	arm_mat_init_f32(&s->N[0] ,	N_State_Ful,				1,	&(s->memFul.arrayN[0][0]));
	arm_mat_init_f32(&s->N[1] ,	N_State_Ful,				1,	&(s->memFul.arrayN[1][0]));

}
else if(type == Kalman_Sim ){
	arm_mat_init_f32(&s->X,		N_State_Sim,			  1,	&(s->memSim.arrayX[0]));
	arm_mat_init_f32(&s->A,		N_State_Sim,	N_State_Sim,	&(s->memSim.arrayA[0]));
	arm_mat_init_f32(&s->B,		N_State_Sim,	M_Input_Sim,	&(s->memSim.arrayB[0]));
	arm_mat_init_f32(&s->U,		M_Input_Sim,			  1,	&(s->memSim.arrayU[0]));
	arm_mat_init_f32(&s->H,		L_Measure_Sim,	N_State_Sim,	&(s->memSim.arrayH[0]));
	arm_mat_init_f32(&s->Z,		L_Measure_Sim,			  1,	&(s->memSim.arrayZ[0]));
	arm_mat_init_f32(&s->P,		N_State_Sim,	N_State_Sim,	&(s->memSim.arrayP[0]));
	arm_mat_init_f32(&s->Q,		N_State_Sim,	N_State_Sim,	&(s->memSim.arrayQ[0]));
	arm_mat_init_f32(&s->R,		L_Measure_Sim,	L_Measure_Sim,	&(s->memSim.arrayR[0]));
	arm_mat_init_f32(&s->K,		N_State_Sim,	L_Measure_Sim,	&(s->memSim.arrayK[0]));
	arm_mat_init_f32(&s->At,	N_State_Sim,	N_State_Sim,	&(s->memSim.arrayAt[0]));
	arm_mat_init_f32(&s->Ht,	N_State_Sim,	L_Measure_Sim,	&(s->memSim.arrayHt[0]));
	arm_mat_init_f32(&s->NL,	N_State_Sim,	L_Measure_Sim,	&(s->memSim.arrayNL[0]));
	arm_mat_init_f32(&s->NN[0],	N_State_Sim,	N_State_Sim,	&(s->memSim.arrayNN[0][0]));
	arm_mat_init_f32(&s->NN[1],	N_State_Sim,	N_State_Sim,	&(s->memSim.arrayNN[1][0]));
	arm_mat_init_f32(&s->LL[0],	L_Measure_Sim,	L_Measure_Sim,	&(s->memSim.arrayLL[0][0]));
	arm_mat_init_f32(&s->LL[1],	L_Measure_Sim,	L_Measure_Sim,	&(s->memSim.arrayLL[1][0]));
	arm_mat_init_f32(&s->L[0] ,	L_Measure_Sim,			    1,	&(s->memSim.arrayL[0][0]));
	arm_mat_init_f32(&s->L[1] ,	L_Measure_Sim,				1,	&(s->memSim.arrayL[1][0]));
	arm_mat_init_f32(&s->N[0] ,	N_State_Sim,				1,	&(s->memSim.arrayN[0][0]));
	arm_mat_init_f32(&s->N[1] ,	N_State_Sim,				1,	&(s->memSim.arrayN[1][0]));
	}
}


void kalman_setQ(KALMAN_FILTER *s, float q)
{

	float dt=s->dt;
	s->Q.pData[0]=q*dt*dt*dt*dt/4.0f;
	s->Q.pData[1]=q*dt*dt*dt/2.0f;
	s->Q.pData[2]=q*dt*dt*dt/2.0f;
	s->Q.pData[3]=q*dt*dt;
}

void kalman_setR(KALMAN_FILTER *s, float r)
{
	s->R.pData[0]=r;
}
