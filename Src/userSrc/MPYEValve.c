#include <MPYEValve.h>
#include "math.h"
#include "string.h"
#include "stdlib.h"




/*****************************FESTO MPYE-5-1/8-010B Valve****************************/
static void MPYE_move(struct ACTUATOR_STRUCT * ptActuator)
{
	MPYE_VALVE *ptMPYE = (MPYE_VALVE *)ptActuator;
	ptMPYE->ptDADev->setVoltage(ptMPYE->ptDADev,ptMPYE->DAPort,ptMPYE->base.command);
}

MPYE_VALVE *MPYEVALVE(DA_DEVICE *ptDADev,uint16_t DAPort,uint16_t jointNum,uint16_t pos)
{
	//New a MPYEValve
	MPYE_VALVE *ptMPYE = (MPYE_VALVE *)malloc(sizeof(MPYE_VALVE));
	if(ptMPYE == NULL)
		return NULL;
	memset(ptMPYE,0,sizeof(MPYE_VALVE));

	//implement virtual function
	ptMPYE->base.act = MPYE_move;

	//record DA port
	ptMPYE->DAPort = DAPort;

	//attach to joint
	ptMPYE->base.jointNum = jointNum;
	ptMPYE->base.position = pos;

	//attach to DA board
	ptMPYE->ptDADev = ptDADev;

	return ptMPYE;
}





/****************************Actuator Hub Functions*********************************/
static void _attach(ACTUATOR_HUB *ptActuatorHub,ACTUATOR *ptActuator)
{
	ptActuatorHub->actuator[ptActuator->jointNum][ptActuator->position] = ptActuator;
	ptActuator->pParent = ptActuatorHub;
	ptActuatorHub->num++;
}

static void actuatorHub_moveJoint(ACTUATOR_HUB *ptActuatorHub,uint16_t jointNum)
{
	ACTUATOR *ptActuator;

	//move the first actuator
	ptActuator=ptActuatorHub->actuator[jointNum][0];
	ptActuator->act(ptActuator);

	//move the second actuator
	ptActuator=ptActuatorHub->actuator[jointNum][1];
	ptActuator->act(ptActuator);

}
static void actuatorHub_moveAll(ACTUATOR_HUB *ptActuatorHub)
{
	for(int i=0;i<JOINT_NUM;i++)
	{
		ptActuatorHub->moveJoint(ptActuatorHub,i);
	}
}

ACTUATOR_HUB *ACTUATORHUB(struct CENTRAL_STRUCT *ptCentral)
{
	ACTUATOR_HUB *ptActuatorHub = (ACTUATOR_HUB *)malloc(sizeof(ACTUATOR_HUB));
	if(ptActuatorHub == NULL)
		return NULL;
	memset(ptActuatorHub,0,sizeof(ACTUATOR_HUB));

	ptActuatorHub->pParent = ptCentral;
	ptCentral->ptActuatorHub = ptActuatorHub;

	ptActuatorHub->attach = _attach;
	ptActuatorHub->moveJoint = actuatorHub_moveJoint;
	ptActuatorHub->moveAll = actuatorHub_moveAll;


	MPYE_VALVE *ptMPYE;
	//New a Actuator attached to DAPort 0, jointNum 0, position 0
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),0,0,0);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);

	//New a Actuator attached to DAPort 1, jointNum 0, position 1
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),1,0,1);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);

	//New a Actuator attached to DAPort 2, jointNum 1, position 0
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),2,1,0);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);

	//New a Actuator attached to DAPort 3, jointNum 1, position 1
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),3,1,1);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);

	//New a Actuator attached to DAPort 4, jointNum 2, position 0
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),4,2,0);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);

	//New a Actuator attached to DAPort 5, jointNum 2, position 1
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),5,2,1);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);

	//New a Actuator attached to DAPort 6, jointNum 3, position 0
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),6,3,0);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);

	//New a Actuator attached to DAPort 7, jointNum 3, position 1
	ptMPYE = MPYEVALVE(&(ptCentral->DADevice),7,3,1);
	ptActuatorHub->attach(ptActuatorHub,(ACTUATOR *)ptMPYE);


	return ptActuatorHub;
}



static float blam=0.999f;
static float bcr=0.52f;
static float bcr_2=0.2304f;
static float sqrtT=17.3205;
static float C1=.0404184;
static float tem2=997.9166666;
static float dir,Pu,Pd,A,tem,Pr,flow,vol;//these need to be assigned values in each function !



float valveFlowFunc(float P1,float P2,float u)
{

if (u>5){
			  if(P2>101325){
						Pu=P2;
						Pd=101325;
						dir=-1;}
				else{
						Pu=101325;
						Pd=P2;
						dir=1;}
		}
else{
        if(P1>P2){
						Pu=P1;
						Pd=P2;
						dir=1;}
				else{
						Pu=P2;
						Pd=P1;
						dir=-1;}
		}
   
    A=valveAreaFunc(u);
    tem=Pu/sqrtT;
    Pr=Pd/Pu;

    
    if (Pr<bcr)       //choked flow
        flow=dir*A*C1*tem;
    else if(Pr<blam)  //subsonic flow
        flow=dir*A*C1*tem*sqrt(1-(Pr-bcr)*(Pr-bcr)/bcr_2);
    else            //laminar flow
		{
    	tem=(Pu-Pd)/sqrtT;
		flow=dir*A*C1*tem*(1-Pr)*tem2;
    }
		return flow;
}

	
float InverseValveFlowFunc(float P1,float P2,float q,int active)
{ 
     if(P2>=101325){    //Muscle pressure is higher than Atm
        if(q>0){        //Incharge from source
            Pu=P1;
            Pd=P2;
            dir=1;}
        else{          //Outcharge to Atm
            Pu=P2;
            Pd=101325;
            dir=-1;}
					}
     else if(q>0){        //only incharge process with two different ways
              dir=1;      //active incharge from source
              Pu=P1;
              Pd=P2;
              if(!active){           //passive incharge from Atm
                Pu=101325;
                Pd=P2;}
							}
         else{                 //no negative pressure source, impossible!!!!!just for assignment
					    Pu=P2;
					    Pd=0;
					    dir=-1;
							}
     
       
    tem=Pu/sqrtT;
    Pr=Pd/Pu;
   
    if (Pr<bcr)       //choked flow  y=dir*A*C1*tem
        A=q/(dir*C1*tem);
    else if (Pr<blam)  //subsonic flow   y=dir*A*C1*tem*sqrt(1-((Pr-bcr)/(1-bcr))^2);
        A=q/(dir*C1*tem*sqrt(1-(Pr-bcr)*(Pr-bcr)/bcr_2));
    else{            //laminar flow    y=dir*A*Cd*C1*tem*((1-Pr)/(1-blam))*sqrt(1-((blam-bcr)/(1-bcr))^2);
        tem=(Pu-Pd)/sqrtT;
        if(tem==0)
           A=0;
        else
					 A=q/(dir*C1*tem*(1-Pr)*tem2);
			}
    
			
    vol=InverseValveAreaFunc(A,dir);
    return vol;
}



float valveAreaFunc(float u)
{
	if(u>5) u=10-u;
	return((3e-06)/(1+exp(6*(u-4.15)))+1e-07);
	
}

float InverseValveAreaFunc(float area,float indir)
{
	float y=0;
	if(area<1.18e-7)
		return 5;
	if(area>3.09999e-6)
		area=3.09999e-6;
	y=4.15+log((3e-6)/(area-(1e-7))-1)/6.0f;
	if(indir<0)
		y=10-y;
	return(y);
}
						
