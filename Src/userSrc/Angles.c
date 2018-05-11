#include <Angles.h>
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "kalman.h"
#include "main.h"
#include "stm32f7xx.h"
#include "tim.h"
#include "spi.h"
static uint16_t DummyWords[2] = {0xffff,0xffff};
static uint16_t ClearWords[1]= {0x4001};


/**********Angle Usage**************
 * ANGLE_HUB *ptAngleHub = ANGLEHUB();
 * AS5048 *ptAS5048Dev1 = AS5048(&hspi1,SPI1_CS_GPIO_Port,SPI1_CS_GPIO_Pin);
 * AS5048 *ptAS5048Dev2 = AS5048(&hspi1,SPI1_CS_GPIO_Port,SPI1_CS_2_GPIO_Pin);
 * MINI4096 *ptMINI4096Dev1 = MINI4096(&hspi3,SPI3_CS_GPIO_Port,SPI3_CS_GPIO_Pin);
 * AS5311 *ptAS5311Dev1 = AS5311(&hspi1,SPI1_CS_GPIO_Port,SPI1_CS_GPIO_Pin,&htim11,EXTI_GPIO_Port,EXTI_GPIO_Pin);
 * angleHub.attach(ptAS5048Dev1,1);
 * angleHub.attach(ptAS5048Dev2,2);
 * angleHub.attach(ptMINI4096Dev1,3);
 * angleHub.attach(ptAS5311Dev1,4);
 *
 * angleHub.getAngle(ptAngleHub,2);  //get the second angle
 * angleHub.getAngleAll(ptAngleHub); //get all the angles, stored in angleHub.angles;
 */

GPIO_TypeDef *ANGLE_CS_GPIO_Ports[JOINT_NUM_MAX] = {ANGLE_0_CS_GPIO_Port,ANGLE_1_CS_GPIO_Port,ANGLE_2_CS_GPIO_Port,ANGLE_3_CS_GPIO_Port};
uint16_t	ANGLE_CS_Pins[JOINT_NUM_MAX] = {ANGLE_0_CS_Pin,ANGLE_1_CS_Pin,ANGLE_2_CS_Pin,ANGLE_3_CS_Pin};

TIM_HandleTypeDef *ANGLE_TIMs[JOINT_NUM_MAX] = {&htim_ANGLE_0,&htim_ANGLE_1,&htim_ANGLE_2,&htim_ANGLE_3};
GPIO_TypeDef *ANGLE_Z_GPIO_Ports[JOINT_NUM_MAX] = {ANGLE_0_Z_GPIO_Port,ANGLE_1_Z_GPIO_Port,ANGLE_2_Z_GPIO_Port,ANGLE_3_Z_GPIO_Port};
uint16_t	ANGLE_Z_Pins[JOINT_NUM_MAX] = {ANGLE_0_Z_Pin,ANGLE_1_Z_Pin,ANGLE_2_Z_Pin,ANGLE_3_Z_Pin};


/******************************AS5048 Device**********************************/
static void AS5048_CS_LOW(AS5048_DEVICE *ptAS5048Dev)
{
	ptAS5048Dev->CS_Port->BSRR=(uint32_t)ptAS5048Dev->CS_Pin<<16U;
}

static void AS5048_CS_HIGH(AS5048_DEVICE *ptAS5048Dev)
{
	ptAS5048Dev->CS_Port->BSRR=(uint32_t)ptAS5048Dev->CS_Pin;
}


static void AS5048_spi_configure(AS5048_DEVICE *ptAS5048Dev)
{
	//store spi configuration
	ptAS5048Dev->spiBaudRatePrescalerStore = ptAS5048Dev->hspi->Init.BaudRatePrescaler;
	ptAS5048Dev->spiCLKPhaseStore = ptAS5048Dev->hspi->Init.CLKPhase;
	ptAS5048Dev->spiCLKPolarityStore = ptAS5048Dev->hspi->Init.CLKPolarity;

	//change spi configuration to AS5048
	ptAS5048Dev->hspi->Init.BaudRatePrescaler = 32;
	ptAS5048Dev->hspi->Init.CLKPhase = SPI_PHASE_2EDGE;
	ptAS5048Dev->hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
	HAL_SPI_Init(ptAS5048Dev->hspi);
}

static void AS5048_spi_deconfigure(AS5048_DEVICE *ptAS5048Dev)
{
	//restore the spi configuration
	ptAS5048Dev->hspi->Init.BaudRatePrescaler = ptAS5048Dev->spiBaudRatePrescalerStore;
	ptAS5048Dev->hspi->Init.CLKPhase = ptAS5048Dev->spiCLKPhaseStore;
	ptAS5048Dev->hspi->Init.CLKPolarity = ptAS5048Dev->spiCLKPolarityStore;
	HAL_SPI_Init(ptAS5048Dev->hspi);
}

static uint16_t AS5048_readRaw(AS5048_DEVICE *ptAS5048Dev)
{
	uint16_t rawtemp = 0;

	//change spi configuration to AS5048
	AS5048_spi_configure(ptAS5048Dev);

	AS5048_CS_LOW(ptAS5048Dev);
	if (ptAS5048Dev->Error == 1){
		HAL_SPI_TransmitReceive_IT(ptAS5048Dev->hspi,(uint8_t *)ClearWords,(uint8_t *)(&rawtemp),1);
	} else{
		HAL_SPI_TransmitReceive_IT(ptAS5048Dev->hspi,(uint8_t *)DummyWords,(uint8_t *)(&rawtemp),1);
	}
	while(HAL_SPI_STATE_READY != HAL_SPI_GetState(ptAS5048Dev->hspi));
	AS5048_CS_HIGH(ptAS5048Dev);


	delay_us(1);

	AS5048_CS_LOW(ptAS5048Dev);
	HAL_SPI_TransmitReceive_IT(ptAS5048Dev->hspi,(uint8_t *)DummyWords,(uint8_t *)(&rawtemp),1);
	while(HAL_SPI_STATE_READY != HAL_SPI_GetState(ptAS5048Dev->hspi));
	AS5048_CS_HIGH(ptAS5048Dev);

	delay_us(1);

	AS5048_CS_LOW(ptAS5048Dev);
	HAL_SPI_TransmitReceive_IT(ptAS5048Dev->hspi,(uint8_t *)DummyWords,(uint8_t *)(&rawtemp),1);
	while(HAL_SPI_STATE_READY != HAL_SPI_GetState(ptAS5048Dev->hspi));
	AS5048_CS_HIGH(ptAS5048Dev);

	//change back spi configuration to original configuration(AS5311)
	AS5048_spi_deconfigure(ptAS5048Dev);

	ptAS5048Dev->rawData =(uint16_t) rawtemp;
	if(__AS5048_GET_FLAG(rawtemp,AS5048_ErroMask)==RESET)
		ptAS5048Dev->Error=0;
	else
		ptAS5048Dev->Error=1;
	ptAS5048Dev->rawSPI =(uint16_t)(rawtemp & AS5048_DataMask);
	return ptAS5048Dev->rawSPI;
}

static void AS5048_ValidateData(AS5048_DEVICE *ptAS5048Dev,uint16_t AS5048RawData)
{
	float AS5048RawAngleTemp;
	float errtem;
	/*********Discard error data and send clear command*******************/
	if(!ptAS5048Dev->Error)
		{
			AS5048RawAngleTemp = ptAS5048Dev->angleCo*AS5048RawData;
			errtem = AS5048RawAngleTemp-ptAS5048Dev->RawAnglePre;
		    if(errtem>6.24 && errtem<6.32)	//valid data with loops -1
			{
				 ptAS5048Dev->loops=ptAS5048Dev->loops-1;
			}
			else if(errtem<-6.24 && errtem>-6.32)	//valid data with loops +1
			{
				ptAS5048Dev->loops=ptAS5048Dev->loops+1;
			}
			else if(errtem>0.1 && errtem<-0.1)			//invalid data, using last data
			{
				AS5048RawAngleTemp = ptAS5048Dev->RawAnglePre;
			}
		    ptAS5048Dev->RawAngle = AS5048RawAngleTemp;
			ptAS5048Dev->base.angle=ptAS5048Dev->RawAngle+ptAS5048Dev->loops*2*M_PI-ptAS5048Dev->Offset;
			ptAS5048Dev->RawAnglePre = ptAS5048Dev->RawAngle;
			ptAS5048Dev->AnglePre = ptAS5048Dev->base.angle;
		}
}


static float AS5048_getAngle(ANGLE_DEVICE *ptAngleDev)
{

	AS5048_DEVICE * ptAS5048Dev = (AS5048_DEVICE *)ptAngleDev;
	ptAS5048Dev->rawSPI=AS5048_readRaw(ptAS5048Dev);
	AS5048_ValidateData(ptAS5048Dev,ptAS5048Dev->rawSPI);
	return ptAS5048Dev->base.angle;
}

static void  AS5048_setZero(ANGLE_DEVICE *ptAngleDev)
{
	AS5048_DEVICE * ptAS5048Dev = (AS5048_DEVICE *)ptAngleDev;
	ptAS5048Dev->rawSPI = AS5048_readRaw(ptAS5048Dev);
	ptAS5048Dev->RawAngle =  ptAS5048Dev->angleCo*ptAS5048Dev->rawSPI;
	ptAS5048Dev->RawAnglePre = ptAS5048Dev->RawAngle;
	ptAS5048Dev->loops = 0;
	ptAS5048Dev->Offset = ptAS5048Dev->RawAngle+ptAS5048Dev->loops*2*M_PI;
	ptAS5048Dev->base.angle= 0 ;
	ptAS5048Dev->AnglePre = 0;
}

AS5048_DEVICE *AS5048(uint16_t jointNum)
{
	//new a AS5048A
	AS5048_DEVICE* ptAS5048Dev = (AS5048_DEVICE *)malloc(sizeof(AS5048_DEVICE));
	if(ptAS5048Dev==NULL)
		return NULL;
	memset(ptAS5048Dev,0,sizeof(AS5048_DEVICE));

	//implement virtual method
	ptAS5048Dev->base.getAngle = AS5048_getAngle;
	ptAS5048Dev->base.setZero = AS5048_setZero;

	//
	ptAS5048Dev->base.jointNum = jointNum;

	//
	ptAS5048Dev->angleCo = 0.0003834952;       //Rad

	/***********due to PCB limitation, we have to use IMU_1 spi currently***
	 *
	 * attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * attention!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 */
	//configure spi
	ptAS5048Dev->CS_Pin = IMU_1_CS_Pin;
	ptAS5048Dev->CS_Port =  IMU_1_CS_GPIO_Port;
	ptAS5048Dev->hspi = &hspi_IMU;
   /****************************************************************/



	//dummy transmit
	HAL_SPI_Transmit(ptAS5048Dev->hspi,(uint8_t *)DummyWords,1,1);
	ptAS5048Dev->base.setZero((ANGLE_DEVICE *)ptAS5048Dev);
	delay_us(1);
	ptAS5048Dev->base.getAngle((ANGLE_DEVICE *)ptAS5048Dev);
	delay_us(1);

   return ptAS5048Dev;
}



/***************************MINI4096 Device***************************************/
static void MINI4096_CS_LOW(MINI4096_DEVICE *ptMINI4096Dev)
{
	ptMINI4096Dev->CS_Port->BSRR=(uint32_t)ptMINI4096Dev->CS_Pin<<16U;
}

static void MINI4096_CS_HIGH(MINI4096_DEVICE *ptMINI4096Dev)
{
	ptMINI4096Dev->CS_Port->BSRR=(uint32_t)ptMINI4096Dev->CS_Pin;
}

static uint16_t MINI4096_readRaw(MINI4096_DEVICE *ptMINI4096Dev)
{
	uint16_t MINI4096RawData;
	MINI4096_CS_LOW(ptMINI4096Dev);
	HAL_SPI_TransmitReceive(ptMINI4096Dev->hspi,(uint8_t *)DummyWords,(uint8_t *)(&MINI4096RawData),1,1);
	MINI4096_CS_HIGH(ptMINI4096Dev);
	delay_us(1);
	MINI4096_CS_LOW(ptMINI4096Dev);
	HAL_SPI_TransmitReceive(ptMINI4096Dev->hspi,(uint8_t *)DummyWords,(uint8_t *)(&MINI4096RawData),1,1);
	MINI4096_CS_HIGH(ptMINI4096Dev);
	return ((uint16_t)((MINI4096RawData>>3)&0x0FFF));
}

static void MINI4096_ValidateData(MINI4096_DEVICE *ptMINI4096Dev,uint16_t MINI4096RawData)
{
	float MINI4096RawAngleTemp;
	float errtem;
	MINI4096RawAngleTemp = MINI4096RawData*ptMINI4096Dev->angleCo;
	errtem = MINI4096RawAngleTemp-ptMINI4096Dev->RawAnglePre;
	if(errtem>6.24 && errtem<6.32)	//valid data with loops -1
	{
		 ptMINI4096Dev->loops=ptMINI4096Dev->loops-1;
		 ptMINI4096Dev->RawAngle = MINI4096RawAngleTemp;
	}
	else if(errtem<-6.24 && errtem>-6.32)	//valid data with loops +1
	{
		ptMINI4096Dev->loops=ptMINI4096Dev->loops+1;
		ptMINI4096Dev->RawAngle = MINI4096RawAngleTemp;
	}
	else if(errtem>0.1 && errtem<-0.1)			//invalid data, using last data
	{
		ptMINI4096Dev->RawAngle = ptMINI4096Dev->RawAnglePre;
	}
	ptMINI4096Dev->base.angle=ptMINI4096Dev->RawAngle+ptMINI4096Dev->loops*2*M_PI-ptMINI4096Dev->Offset;
	ptMINI4096Dev->RawAnglePre = ptMINI4096Dev->RawAngle;
	ptMINI4096Dev->AnglePre = ptMINI4096Dev->base.angle;
}

static float MINI4096_getAngle(ANGLE_DEVICE *ptANGLEDev)
{
	MINI4096_DEVICE * ptMINI4096Dev = (MINI4096_DEVICE *)ptANGLEDev;
	uint16_t MINI4096RawData;
	MINI4096RawData = MINI4096_readRaw(ptMINI4096Dev);
	MINI4096_ValidateData(ptMINI4096Dev,MINI4096RawData);
	return ptMINI4096Dev->base.angle;
}

static void MINI4096_setZero(ANGLE_DEVICE *ptAngleDev)
{
	MINI4096_DEVICE * ptMINI4096Dev = (MINI4096_DEVICE *)ptAngleDev;
	uint16_t MINI4096RawData;
	MINI4096RawData = MINI4096_readRaw(ptMINI4096Dev);
	ptMINI4096Dev->RawAngle = ((uint16_t)((MINI4096RawData>>3)&0x0FFF))*ptMINI4096Dev->angleCo;
	ptMINI4096Dev->RawAnglePre = ptMINI4096Dev->RawAngle;
	ptMINI4096Dev->loops = 0;
	ptMINI4096Dev->Offset = ptMINI4096Dev->RawAngle+ptMINI4096Dev->loops*2*M_PI;
	ptMINI4096Dev->base.angle= 0 ;
	ptMINI4096Dev->AnglePre = 0;
}

MINI4096_DEVICE * MINI4096(uint16_t jointNum)
{
	MINI4096_DEVICE* ptMINI4096Dev = (MINI4096_DEVICE *)malloc(sizeof(MINI4096_DEVICE));
	if(ptMINI4096Dev==NULL)
		return NULL;
	memset(ptMINI4096Dev,0,sizeof(MINI4096_DEVICE));
	ptMINI4096Dev->base.getAngle = MINI4096_getAngle;
	ptMINI4096Dev->base.setZero = MINI4096_setZero;
	ptMINI4096Dev->angleCo = 2*3.14159265f/4096.0f;
	ptMINI4096Dev->CS_Pin = ANGLE_CS_Pins[jointNum];
	ptMINI4096Dev->CS_Port = ANGLE_CS_GPIO_Ports[jointNum];
	ptMINI4096Dev->hspi = &hspi_ANGLE;
	ptMINI4096Dev->base.jointNum = jointNum;

	HAL_SPI_Transmit(ptMINI4096Dev->hspi,(uint8_t *)DummyWords,1,1);
	ptMINI4096Dev->base.setZero((ANGLE_DEVICE *)ptMINI4096Dev);
	delay_us(1);
	ptMINI4096Dev->base.getAngle((ANGLE_DEVICE *)ptMINI4096Dev);
	delay_us(1);
	return ptMINI4096Dev;
}




/*****************************AS5311**************************************/
static void AS5311_CS_LOW(AS5311_DEVICE *ptAS5311Dev)
{
	ptAS5311Dev->CS_Port->BSRR=(uint32_t)ptAS5311Dev->CS_Pin<<16U;
}

static void AS5311_CS_HIGH(AS5311_DEVICE *ptAS5311Dev)
{
	ptAS5311Dev->CS_Port->BSRR=(uint32_t)ptAS5311Dev->CS_Pin;
}


/*This function does a raw read SPI, and mask the data
 * although 12-bit, we only need 10 bits to reduce noise*/
static void AS5311_readRawSPI(AS5311_DEVICE *ptAS5311Dev)
{
	uint16_t AS5311RawData;

//	//first read
//	AS5311_CS_LOW(ptAS5311Dev);
//	HAL_SPI_TransmitReceive(ptAS5311Dev->hspi,(uint8_t *)DummyWords,(uint8_t *)(&AS5311RawData),1,1);
//	AS5311_CS_HIGH(ptAS5311Dev);
//	delay_us(1);
	int32_t c1,c2;
	//second read. for the case that returned data is last read command.
	AS5311_CS_LOW(ptAS5311Dev);
	c1=TIC();
	HAL_SPI_TransmitReceive(ptAS5311Dev->hspi,(uint8_t *)DummyWords,(uint8_t *)(&AS5311RawData),1,1);
	c2=TIC();
	AS5311_CS_HIGH(ptAS5311Dev);

	//mask data
	ptAS5311Dev->rawSPI = (uint16_t)((AS5311RawData>>5)&0x03FF);
}

/*This callback function is attached to Index interrupt, would update Z index and record instant AB counts*/
void AS5311_EXTICallback(AS5311_DEVICE *ptAS5311Dev)
{
	ptAS5311Dev->dir = (__HAL_TIM_IS_TIM_COUNTING_DOWN(ptAS5311Dev->htim))?-1:1;
	//If negative direction, sync AB first, then update index
	if(-1 == ptAS5311Dev->dir){
		ptAS5311Dev->htim->Instance->CNT = ptAS5311Dev->Index*1024;
		ptAS5311Dev->ABLast = ptAS5311Dev->Index*1024;
		if(!(ptAS5311Dev->Index%64)){
			ptAS5311Dev->loop--;
		}
		ptAS5311Dev->Index--;
	}
	else{//If positive direction, update index first, then sync AB
		ptAS5311Dev->Index++;
		if(!(ptAS5311Dev->Index%64)){
			ptAS5311Dev->loop++;
		}
		ptAS5311Dev->htim->Instance->CNT = ptAS5311Dev->Index*1024;
		ptAS5311Dev->ABLast = (ptAS5311Dev->Index*1024);
	}

}

/*This function gets the final angle,velocity and acceleration from raw sensor data*/
static void AS5311_ValidateData(AS5311_DEVICE *ptAS5311Dev)
{
	//calculates SPI fraction
	ptAS5311Dev->SPIFraction = ptAS5311Dev->rawSPI/1024.0f;

	//calculate AB fraction
	ptAS5311Dev->AB = (int32_t)(ptAS5311Dev->loop*65536) +(int32_t)__AS5311_RawAB(ptAS5311Dev);
	ptAS5311Dev->ABFraction =  (ptAS5311Dev->AB-ptAS5311Dev->ABLast)/1024.0f;

	//SPI index is the same as main Index, because SPI reading is always from left to right on the axis
	ptAS5311Dev->SPIIndex = ptAS5311Dev->Index;

	//AB index would change in negative area, because AB counting has sign.
	ptAS5311Dev->ABIndex = (ptAS5311Dev->ABFraction>=0)?(ptAS5311Dev->Index):(ptAS5311Dev->Index+1);

	//final SPI counting plus offset
	ptAS5311Dev->AngleSPI = (ptAS5311Dev->SPIIndex+ptAS5311Dev->SPIFraction-ptAS5311Dev->SPIOffsetFrac)*2*3.14159265f/64.0f;

	//final AB counting plus offset
	ptAS5311Dev->AngleABZ =   (ptAS5311Dev->ABIndex+ptAS5311Dev->ABFraction-ptAS5311Dev->ABOffsetFrac)*2*3.14159265f/64.0f;

	//choose one angle to be the output angle, this part could be done more reliably
	ptAS5311Dev->base.angle = ptAS5311Dev->AngleSPI;

}

/*get angle*/
static float AS5311_getAngle(ANGLE_DEVICE *ptANGLEDev)
{
	AS5311_DEVICE * ptAS5311Dev = (AS5311_DEVICE *)ptANGLEDev;
	AS5311_readRawSPI(ptAS5311Dev);
	AS5311_ValidateData(ptAS5311Dev);
	return ptAS5311Dev->base.angle;
}


static void AS5311_setZero(ANGLE_DEVICE *ptAngleDev)
{
	AS5311_DEVICE * ptAS5311Dev = (AS5311_DEVICE *)ptAngleDev;
	AS5311_readRawSPI(ptAS5311Dev);
	ptAS5311Dev->SPIOffsetFrac= ptAS5311Dev->rawSPI/1024.0f;
	ptAS5311Dev->ABOffsetFrac=ptAS5311Dev->SPIOffsetFrac;

	ptAS5311Dev->AngleSPI = 0;
	ptAS5311Dev->SPIIndex = 0;
	ptAS5311Dev->AngleABZ = 0;
	ptAS5311Dev->Index = 0;
	ptAS5311Dev->ABLast = 0;
	ptAS5311Dev->AB = 0;
	ptAS5311Dev->ABIndex = 0;
	ptAS5311Dev->ABFraction = ptAS5311Dev->ABOffsetFrac;
	__HAL_TIM_SET_COUNTER(ptAS5311Dev->htim,(uint16_t)(ptAS5311Dev->ABFraction*1024));
}

AS5311_DEVICE * AS5311(uint16_t jointNum)
{
	//New a AS5311 on the heap
	AS5311_DEVICE* ptAS5311Dev = (AS5311_DEVICE *)malloc(sizeof(AS5311_DEVICE));
	if(ptAS5311Dev==NULL)
		return NULL;
	memset(ptAS5311Dev,0,sizeof(AS5311_DEVICE));

	//implement virtual method
	ptAS5311Dev->base.getAngle = AS5311_getAngle;
	ptAS5311Dev->base.setZero = AS5311_setZero;

	//actual joint num
	ptAS5311Dev->base.jointNum = jointNum;

	ptAS5311Dev->angleCoSPI = 2*3.14159265f/64.0f/1024.0f;
	ptAS5311Dev->angleCoAB = 2*3.14159265f/64.0f/1024.0f;

	//SPI configuration
	ptAS5311Dev->CS_Pin = ANGLE_CS_Pins[jointNum];
	ptAS5311Dev->CS_Port = ANGLE_CS_GPIO_Ports[jointNum];
	ptAS5311Dev->hspi = &hspi_ANGLE;

	//AB Timer configuration
	ptAS5311Dev->htim = ANGLE_TIMs[jointNum];

	//Z-index EXTI configuration
	ptAS5311Dev->EXTI_Port = ANGLE_Z_GPIO_Ports[jointNum];
	ptAS5311Dev->EXTI_Pin = ANGLE_Z_Pins[jointNum];

	//start a dummy transport
	AS5311_CS_LOW(ptAS5311Dev);
	HAL_SPI_Transmit(ptAS5311Dev->hspi,(uint8_t *)DummyWords,1,1);
	AS5311_CS_HIGH(ptAS5311Dev);

	//start AB counting
	HAL_TIM_Encoder_Start(ptAS5311Dev->htim,TIM_CHANNEL_ALL);

	//zero postition
	ptAS5311Dev->base.setZero((ANGLE_DEVICE *)ptAS5311Dev);
	delay_us(1);

	//get angle
	ptAS5311Dev->base.getAngle((ANGLE_DEVICE *)ptAS5311Dev);
	delay_us(1);

	return ptAS5311Dev;
}



/****************************Angle Hub*************************************/

static void angleHub_attachAngleDevice(ANGLE_HUB *ptAngleHub,ANGLE_DEVICE *ptAngleDev)
{
	ptAngleHub->angleDevices[ptAngleDev->jointNum]=ptAngleDev;
	ptAngleDev->pParent = ptAngleHub;
	ptAngleHub->Num+=1;
}

static float angleHub_getAngle(ANGLE_HUB *ptAngleHub,uint16_t num)
{
	return ptAngleHub->angleDevices[num]->getAngle(ptAngleHub->angleDevices[num]);
}

static void angleHub_getAngleAll(ANGLE_HUB * ptAngleHub)
{
	for(int i=0;i<ptAngleHub->Num;i++)
		ptAngleHub->angles[i] = ptAngleHub->getAngle(ptAngleHub,i);
}

ANGLE_HUB *ANGLEHUB(CENTRAL *ptCentral)
{


	//new a angle Hub on the heap
	ANGLE_HUB * ptAngleHub = (ANGLE_HUB *)malloc(sizeof(ANGLE_HUB));
	if(ptAngleHub==NULL)
		return NULL;
	memset(ptAngleHub,0,sizeof(ANGLE_HUB));

	//add parent Central
	ptAngleHub->pParent = ptCentral;
	ptCentral->ptAngleHub = ptAngleHub;

	//attach methods
	ptAngleHub->attach = angleHub_attachAngleDevice;
	ptAngleHub->getAngle = angleHub_getAngle;
	ptAngleHub->getAngleAll = angleHub_getAngleAll;




//	ptAS5311Dev = AS5311(1);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev);
//
//	ptAS5311Dev = AS5311(2);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev);
//
//	ptAS5311Dev = AS5311(3);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev);

//	/*Add one encoder, attached to SPI, TIME, EXTI, JointNum 1*/
//	ptAS5311Dev1 = AS5311(&hspi_ANGLE,ANGLE_CS_GPIO_Port,ANGLE_CS_Pin,&htim_ANGLE,ENCODER_INDEX_GPIO_Port,ENCODER_INDEX_Pin,0);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev1,ptAS5311Dev1->base.jointNum);
//
//	/*Add one encoder, attached to SPI, TIME, EXTI, JointNum 2*/
//	ptAS5311Dev1 = AS5311(&hspi_ANGLE,ANGLE_CS_GPIO_Port,ANGLE_CS_Pin,&htim_ANGLE,ENCODER_INDEX_GPIO_Port,ENCODER_INDEX_Pin,0);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev1,ptAS5311Dev1->base.jointNum);
//
//	/*Add one encoder, attached to SPI, TIME, EXTI, JointNum 3*/
//	ptAS5311Dev1 = AS5311(&hspi_ANGLE,ANGLE_CS_GPIO_Port,ANGLE_CS_Pin,&htim_ANGLE,ENCODER_INDEX_GPIO_Port,ENCODER_INDEX_Pin,0);
//	ptAngleHub->attach(ptAngleHub,(ANGLE_DEVICE *)ptAS5311Dev1,ptAS5311Dev1->base.jointNum);



	return ptAngleHub;
}













