/*
 * moteurElev.c
 *
 *  Created on: May 22, 2023
 *      Author: PENG Laurine
 */

#include "moteurs.h"

void testmoteur(TIM_HandleTypeDef tim,int val)
{
	__HAL_TIM_SET_COMPARE(&tim, TIM_CHANNEL_1, val);
	HAL_Delay(5000);
	__HAL_TIM_SET_COMPARE(&tim, TIM_CHANNEL_1, 0);
}



