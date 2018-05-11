#ifndef __ANGELS_H_
#define __ANGELS_H_

#include <Central.h>
#include "stm32f7xx_hal.h"
#include "kalman.h"
#define AS5048_NOP                      0x0000      // No operation dummy information
#define AS5048_CLEAR_ERROR_FLAG         0x0001      // Read address for Error flags
#define AS5048_ANGLE                    0x3FFF      // Read address for Magnetic Angle (with zero correction)
#define AS5048_PARITY_EVEN              0x8000      // Position for EVEN Parity bit
#define AS5048_ReadMask                 0x4000      // Position for Write/Read bit (0 / 1 respectively)
#define AS5048_DataMask                 0x3FFF      // Mask to get the Data only
#define AS5048_ErroMask                 0x4000      // Position of Error flag read from AS5048


#define __AS5048_GET_FLAG(__DATA__, __FLAG__)  (((__DATA__) & (__FLAG__)) == (__FLAG__))
#define __AS5311_RawAB(__Handle_) (uint16_t)((__Handle_)->htim->Instance->CNT)


typedef struct ANGLE_DEVICE_STRUCT{
	float angle;
	float velocity;
	float acceleration;
	uint16_t jointNum;
	struct ANGLE_HUB_STRUCT *pParent;
	float (*getAngle)(struct ANGLE_DEVICE_STRUCT *);
	void (*setZero)(struct ANGLE_DEVICE_STRUCT *);
}ANGLE_DEVICE;

typedef   struct AS5048_DEVICE_STRUCT{                            // Structure for data and parameters read from the AS5048 device
    ANGLE_DEVICE base;
    uint16_t rawData;
    uint16_t rawSPI;
	float     RawAngle;
    float 	 RawAnglePre;
    float 		 AnglePre;
    float 		 Offset;
    float 		angleCo;
    int8_t         loops;
    uint8_t      Error;
    GPIO_TypeDef *CS_Port;
    uint16_t	CS_Pin;
    SPI_HandleTypeDef *hspi;
    uint32_t spiBaudRatePrescalerStore;
    uint32_t spiCLKPhaseStore;
    uint32_t spiCLKPolarityStore;
}AS5048_DEVICE;

typedef struct MINI4096_DEVICE_STRUCT{
	ANGLE_DEVICE base;
    float     RawAngle;
    float 	 RawAnglePre;
    float 		 AnglePre;
    float 		 Offset;
    float 		angleCo;
    int8_t         loops;
    GPIO_TypeDef *CS_Port;
    uint16_t	CS_Pin;
    SPI_HandleTypeDef *hspi;
}MINI4096_DEVICE;

typedef struct AS5311_DEVICE_STRUCT{
	ANGLE_DEVICE base;

    float 		AngleSPI;
    uint16_t	rawSPI;
    float 		angleCoSPI;
    float 		SPIFraction;
    int16_t		SPIIndex;
    float 		SPIOffsetFrac;

    float 		AngleABZ;
    int16_t 	Index;
    int32_t		AB;
    int32_t		ABLast;
    float 		angleCoAB;
    float 		ABFraction;
    int16_t 	ABIndex;
    float 		ABOffsetFrac;

    int16_t dir;
    int16_t loop;


    GPIO_TypeDef *CS_Port;
    uint16_t	CS_Pin;
    SPI_HandleTypeDef *hspi;
    TIM_HandleTypeDef *htim;
    GPIO_TypeDef *EXTI_Port;
    uint16_t	EXTI_Pin;
}AS5311_DEVICE;


typedef struct ANGLE_HUB_STRUCT{
	struct CENTRAL_STRUCT *pParent;
	ANGLE_DEVICE *angleDevices[JOINT_NUM_MAX];
	float angles[JOINT_NUM_MAX];
	float velocity[JOINT_NUM_MAX];
	float acceleration[JOINT_NUM_MAX];

	uint16_t Num;
	float   (*getAngle)(struct ANGLE_HUB_STRUCT *,uint16_t);
	void  	(*getAngleAll)(struct ANGLE_HUB_STRUCT *);
	void 	(*attach)(struct ANGLE_HUB_STRUCT *,ANGLE_DEVICE *);
}ANGLE_HUB;

ANGLE_HUB *ANGLEHUB(struct CENTRAL_STRUCT *);
MINI4096_DEVICE *MINI4096(uint16_t);
AS5048_DEVICE *AS5048(uint16_t);
AS5311_DEVICE *AS5311(uint16_t jointNum);
void AS5311_EXTICallback(AS5311_DEVICE *ptAS5311Dev); //update Z and last AB
#endif
