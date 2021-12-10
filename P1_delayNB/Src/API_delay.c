/*
 * API_delay.c
 *
 *  Created on: 8 nov. 2021
 *      Author: Guillermo
 */

#include "API_delay.h"
#include "stm32f4xx_hal.h"

void delayInit( delay_t *delay, tick_t duration )
{
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead( delay_t *delay )
{
	uint32_t actual_time = 0;
	bool_t timeOut = false;

	if (delay->running){
		actual_time = HAL_GetTick()-delay->startTime;
		if(actual_time >= delay->duration){
			delay->running = false;
			timeOut = true;
		}else{
			timeOut = false;
		}
	}else{
		delay->startTime = HAL_GetTick();
		delay->running = true;
		timeOut = false;
	}
	return timeOut;
}

void delayWrite( delay_t *delay, tick_t duration ){
	if(delay->running){
		delay->running = false;
	}
	delay->duration = duration;
}
