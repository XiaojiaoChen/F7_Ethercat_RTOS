/*
 * LM10.h
 *
 *  Created on: Nov 7, 2017
 *      Author: 40207
 */

#ifndef USER_INC_LM10_H_
#define USER_INC_LM10_H_
#include "stm32f7xx_hal.h"
void initLinearEncoder(TIM_HandleTypeDef *htim);
float getPosition();

#endif /* USER_INC_LM10_H_ */
