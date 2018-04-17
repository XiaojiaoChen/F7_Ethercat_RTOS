#include "main.h"
#include "math.h"
#include "LTC2668.h"
#include "string.h"


#define DA_CS_LOW()  DA_CS_GPIO_Port->BSRR=(uint32_t)DA_CS_Pin<<16U;
#define DA_CS_HIGH() DA_CS_GPIO_Port->BSRR=DA_CS_Pin;



static void LTC2668_write(DA_DEVICE *ptDADevice,uint8_t dac_command, uint8_t dac_address, uint16_t dac_code)
{

  uint16_t DA_Transfer_Send[2];
  DA_Transfer_Send[0] = (uint16_t)(dac_command | dac_address);
  DA_Transfer_Send[1] = dac_code;

  DA_CS_LOW();
  HAL_SPI_Transmit(ptDADevice->DA_spi,(uint8_t *)DA_Transfer_Send,2,1);
  DA_CS_HIGH();
  
}

static uint16_t LTC2668_voltage_to_code(DA_DEVICE * ptDADev,float dac_voltage)
{
  uint16_t dac_code;
  float float_code;
  float_code = 65535.0f * (dac_voltage - ptDADev->fMinVoltage) / ptDADev->fRange;                    // Calculate the DAC code
  float_code = (float_code > (floor(float_code) + 0.5f)) ? ceil(float_code) : floor(float_code);     // Round
  if (float_code < 0.0f) float_code = 0.0f;
  if (float_code > 65535.0f) float_code = 65535.0f;
  dac_code = (uint16_t) (float_code);                                                               // Convert to unsigned integer
  return (dac_code);
}

static void setVoltage(DA_DEVICE *ptDADevice,uint16_t selected_dac, float vol)
{

	ptDADevice->fChannel[selected_dac]=vol;
	ptDADevice->uChannel[selected_dac] = LTC2668_voltage_to_code(ptDADevice,vol);
	LTC2668_write(ptDADevice,LTC2668_CMD_WRITE_N_UPDATE_N, selected_dac, ptDADevice->uChannel[selected_dac]);
}


void Init_DA(DA_DEVICE * ptDADev,float vMin,float vMax,SPI_HandleTypeDef *DA_spi)
{
	memset(ptDADev->uChannel,0,sizeof(ptDADev->uChannel));
	memset(ptDADev->fChannel,0,sizeof(ptDADev->fChannel));
	ptDADev->fMinVoltage = vMin;
	ptDADev->fMaxVoltage = vMax;
	ptDADev->fRange = vMax-vMin;
	ptDADev->fMid = (vMax+vMin)/2.0;
	ptDADev->DA_spi=DA_spi;
	ptDADev->ucDataFlag = 0;
	ptDADev->setVoltage = setVoltage;
}

