#ifndef LTC2668_H
#define LTC2668_H
#include "stm32f7xx_hal.h"

#define  LTC2668_CMD_WRITE_N              0x00  //!< Write to input register n
#define  LTC2668_CMD_UPDATE_N             0x10  //!< Update (power up) DAC register n
#define  LTC2668_CMD_WRITE_N_UPDATE_ALL   0x20  //!< Write to input register n, update (power-up) all
#define  LTC2668_CMD_WRITE_N_UPDATE_N     0x30  //!< Write to input register n, update (power-up) 
#define  LTC2668_CMD_POWER_DOWN_N         0x40  //!< Power down n
#define  LTC2668_CMD_POWER_DOWN_ALL       0x50  //!< Power down chip (all DAC's, MUX and reference)

#define  LTC2668_CMD_SPAN                 0x60  //!< Write span to dac n
#define  LTC2668_CMD_CONFIG               0x70  //!< Configure reference / toggle
#define  LTC2668_CMD_WRITE_ALL            0x80  //!< Write to all input registers
#define  LTC2668_CMD_UPDATE_ALL           0x90  //!< Update all DACs
#define  LTC2668_CMD_WRITE_ALL_UPDATE_ALL 0xA0  //!< Write to all input reg, update all DACs
#define  LTC2668_CMD_MUX                  0xB0  //!< Select MUX channel (controlled by 5 LSbs in data word)
#define  LTC2668_CMD_TOGGLE_SEL           0xC0  //!< Select which DACs can be toggled (via toggle pin or global toggle bit)
#define  LTC2668_CMD_GLOBAL_TOGGLE        0xD0  //!< Software toggle control via global toggle bit
#define  LTC2668_CMD_SPAN_ALL             0xE0  //!< Set span for all DACs
#define  LTC2668_CMD_NO_OPERATION         0xF0  //!< No operation

#define  LTC2668_SPAN_0_TO_5V             0x0000
#define  LTC2668_SPAN_0_TO_10V            0x0001
#define  LTC2668_SPAN_PLUS_MINUS_5V       0x0002
#define  LTC2668_SPAN_PLUS_MINUS_10V      0x0003
#define  LTC2668_SPAN_PLUS_MINUS_2V5      0x0004

#define  LTC2668_REF_DISABLE              0x0001  //! Disable internal reference to save power when using an ext. ref.
#define  LTC2668_THERMAL_SHUTDOWN         0x0002  //! Disable thermal shutdown (NOT recommended)

#define  LTC2668_MUX_DISABLE              0x0000  //! Disable MUX
#define  LTC2668_MUX_ENABLE               0x0010  //! Enable MUX, OR with MUX channel to be monitored

#define  LTC2668_TOGGLE_REG_A              0x0000  //! Update DAC with register A
#define  LTC2668_TOGGLE_REG_B              0x0010  //! Update DAC with register B


typedef struct DA_DEVICE_STRUCT{
	uint16_t uChannel[16];
	float fChannel[16];
	float fMinVoltage;
	float fMaxVoltage;
	float fRange;
	float fMid;
	SPI_HandleTypeDef *DA_spi;
	uint8_t ucDataFlag;
	void (*setVoltage)(struct DA_DEVICE_STRUCT *ptDADev,uint16_t number, float vol);
}DA_DEVICE;

void Init_DA(DA_DEVICE * ptDADev,float vMin,float vMax,SPI_HandleTypeDef *DA_spi);


#endif  // LTC2668_H
