#include "ADS8588.h"
#include "main.h"
#include "string.h"
/******************Usage**********************/
/* 1. AD_DEVICE  ADDeviceInstace;
 * 2. Init_AD(&ADDeviceInstance,8,-10,10,&hspi2);            8 channels with (-10,10)V range on SPI2
 * 3. ADDeviceInstance.update(&ADDeviceInstance);
 * 4. AD_data=ADDeviceInstance.fChannel[0-7];   (20~30us)
 */


/********Hardware dependent implementation********/
/*1. define and configure
 *  AD_RESET OUTPUT
 *  AD_BUSY  INPUT
 *  AD_CONV  OUTPUT
 *  Pins in STM32CubeMX
 *2. define SPI and DMA
 *3. copy BUSY and SPI callbackFunc to corresponding postition.
  4. modifiy private defines
*/

/*****Private define*************/
#define AD_RESET_LOW()  (AD_RESET_GPIO_Port->BSRR=(uint32_t)AD_RESET_Pin<<16U)
#define AD_RESET_HIGH() (AD_RESET_GPIO_Port->BSRR=AD_RESET_Pin)
#define AD_CONV_LOW()  (AD_CONV_GPIO_Port->BSRR=(uint32_t)AD_CONV_Pin<<16U)
#define AD_CONV_HIGH() (AD_CONV_GPIO_Port->BSRR=AD_CONV_Pin)
#define AD_CS_LOW()  (AD_CS_GPIO_Port->BSRR=(uint32_t)AD_CS_Pin<<16U)
#define AD_CS_HIGH() (AD_CS_GPIO_Port->BSRR=AD_CS_Pin)

static uint32_t ulDummyWord=0xFFFFFFFF;


void AD_BUSYCallback(AD_DEVICE *ptADDev)
{
	AD_CS_LOW();
	HAL_SPI_TransmitReceive_DMA(ptADDev->AD_spi,(uint8_t *)ulDummyWord,(uint8_t *)ptADDev->uChannel, ptADDev->uChannelNum);
}

void AD_SPICallback(AD_DEVICE *ptADDev)
{
	AD_CS_HIGH();
	for(int i=0;i<ptADDev->uChannelNum;i++)
		{
		ptADDev->fChannel[i]=(int16_t)ptADDev->uChannel[i]*ptADDev->fRange/65536.0f+ptADDev->fMid;
		}
	ptADDev->ucDataFlag = 1;
}

static void AD_Reset(AD_DEVICE *ptADDev)
{
	
	AD_RESET_LOW();
	AD_RESET_HIGH();
	delay_us(1);
	AD_RESET_LOW();
}


static void AD_getVoltage(AD_DEVICE *ptADDev)
{
	AD_CONV_LOW();
	for(int i=0;i<2;i++);
	AD_CONV_HIGH();
	ptADDev->ucDataFlag = 0;
}

void Init_AD(AD_DEVICE * ptADDev,uint16_t numChannel,float vMin,float vMax,SPI_HandleTypeDef *AD_spi)
{
	memset(ptADDev->uChannel,0,sizeof(ptADDev->uChannel));
	memset(ptADDev->fChannel,0,sizeof(ptADDev->fChannel));
	ptADDev->fMinVoltage = vMin;
	ptADDev->fMaxVoltage = vMax;
	ptADDev->fRange = vMax-vMin;
	ptADDev->fMid = (vMax+vMin)/2.0;
	ptADDev->uChannelNum = numChannel;

	ptADDev->AD_spi=AD_spi;
	ptADDev->ucDataFlag = 0;
	ptADDev->getVoltage = AD_getVoltage;
	ptADDev->Reset = AD_Reset;
	ptADDev->Reset(ptADDev);

}





