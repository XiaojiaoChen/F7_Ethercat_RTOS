#include "pressureRegulator_ITV2030.h"
#include "string.h"
#include "stdlib.h"





/*************************************ITV2030 pressure regulator***********************************/
static void ITV_setPressure(REGULATOR_DEVICE *ptITV2030Dev, float pc)       // gauge pressure
{ 
	//pressure command saturation
	if(pc<ptITV2030Dev->Pmin)
		ptITV2030Dev->Pcommand = ptITV2030Dev->Pmin;
	else if(pc>ptITV2030Dev->Pmax)
		ptITV2030Dev->Pcommand = ptITV2030Dev->Pmax;
	else
		ptITV2030Dev->Pcommand = pc;

	//calculate voltage command
	ptITV2030Dev->Vcommand = (pc-ptITV2030Dev->Pmin)/(ptITV2030Dev->Pmax-ptITV2030Dev->Pmin)*(ptITV2030Dev->Vinmax-ptITV2030Dev->Vinmin)+ptITV2030Dev->Vinmin;

	//DA board output
	ptITV2030Dev->ptDADev->setVoltage(ptITV2030Dev->ptDADev,ptITV2030Dev->DAPort,ptITV2030Dev->Vcommand);
}



/*this will not initiate a new read on AD, just read AD Last Data
 *Therefore it is necessary for the AD board to be working cyclicly
 */
static float ITV_getPressure(REGULATOR_DEVICE *ptITV2030Dev)
{
	//read AD board buffer
	float vtem=ptITV2030Dev->ptADDev->fChannel[ptITV2030Dev->ADPort];

	//translate to pressure value
	float ptem=(vtem-ptITV2030Dev->Voutmin)/(ptITV2030Dev->Voutmax-ptITV2030Dev->Voutmin)*(ptITV2030Dev->Pmax-ptITV2030Dev->Pmin)+ptITV2030Dev->Pmin;

	return ptem;
}


/*TO DO*/
void ITV_setZero(REGULATOR_DEVICE *ptITV2030Dev)
{

}

REGULATOR_DEVICE *ITV2030(DA_DEVICE *ptDADev,uint16_t DAPort,AD_DEVICE *ptADDev,uint16_t ADPort,float pmax,uint16_t num)
{

	REGULATOR_DEVICE *ptITV2030Dev = (REGULATOR_DEVICE *)malloc(sizeof(REGULATOR_DEVICE));
	if(ptITV2030Dev == NULL)
		return NULL;
	memset(ptITV2030Dev,0,sizeof(REGULATOR_DEVICE));

	ptITV2030Dev->ptDADev = ptDADev;
	ptITV2030Dev->DAPort = DAPort;
	ptITV2030Dev->ptADDev = ptADDev;
	ptITV2030Dev->ADPort = ADPort;
	ptITV2030Dev->Num = num;
	ptITV2030Dev->Pmin = 0;
	ptITV2030Dev->Pmax = pmax;
	ptITV2030Dev->Vinmax = 5.0f;
	ptITV2030Dev->Vinmin = 0.0f;
	ptITV2030Dev->Voutmin = 1.0f;  //output voltage is 1~5V acoording to ITV2030 Datasheet
	ptITV2030Dev->Voutmax = 5.0f;
	ptITV2030Dev->setPressure = ITV_setPressure;
	ptITV2030Dev->getPressure = ITV_getPressure;
	ptITV2030Dev->setZero  = ITV_setZero;

	return ptITV2030Dev;
}








static void regulatorHub_attach(struct REGULATOR_HUB_STRUCT *pRegulatorHub,struct REGULATOR_DEVICE_STRUCT *pRegulatorDev)
{
	pRegulatorHub->regulator[pRegulatorDev->Num] = pRegulatorDev;
	pRegulatorDev->pParent = pRegulatorHub;
	pRegulatorHub->num++;
}

static void regulatorHub_setPressure(struct REGULATOR_HUB_STRUCT *ptRegulatorHub,uint16_t num,float pre)
{
	REGULATOR_DEVICE *ptRegulatorDev = ptRegulatorHub->regulator[num];
	ptRegulatorHub->pressureCommand[num] = pre;
	ptRegulatorDev->setPressure(ptRegulatorDev,pre);
}
static float regulatorHub_getPressure(struct REGULATOR_HUB_STRUCT *ptRegulatorHub,uint16_t num)
{
	REGULATOR_DEVICE *ptRegulatorDev = ptRegulatorHub->regulator[num];
	return ptRegulatorDev->getPressure(ptRegulatorDev);
}

static void regulatorHub_setZero(struct REGULATOR_HUB_STRUCT *ptRegulatorHub)
{

}


REGULATOR_HUB *REGULATORHUB(CENTRAL *ptCentral)
{
	//New a RegulatorHub on the heap
	REGULATOR_HUB *ptRegulatorHub = (REGULATOR_HUB *)malloc(sizeof(REGULATOR_HUB));
	if(ptRegulatorHub == NULL)
		return NULL;
	memset(ptRegulatorHub,0,sizeof(REGULATOR_HUB));

	//add parent Central
	ptRegulatorHub->pParent = ptCentral;
	ptCentral->ptRegulatorHub = ptRegulatorHub;

	//attach methods
	ptRegulatorHub->attach = regulatorHub_attach;
	ptRegulatorHub->setPressure = regulatorHub_setPressure;
	ptRegulatorHub->getPressure = regulatorHub_getPressure;
	ptRegulatorHub->setZero = regulatorHub_setZero;



	return ptRegulatorHub;
}

