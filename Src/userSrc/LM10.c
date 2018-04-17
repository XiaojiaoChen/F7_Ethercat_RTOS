/*
 * LM10.c
 *
 *  Created on: Nov 7, 2017
 *      Author: 40207
 */
#include <LM10.h>
#include "tim.h"

static TIM_HandleTypeDef *htimLinearEncoder;

void initLinearEncoder(TIM_HandleTypeDef *htim)
{
	htimLinearEncoder=htim;
	HAL_TIM_Encoder_Start(htim,TIM_CHANNEL_ALL);
}

float getPosition()
{
	int32_t temp=(int32_t)htimLinearEncoder->Instance->CNT;

	return((float)(temp*0.001));
}

