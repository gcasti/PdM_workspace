/*
 * API_delay.h
 *
 *  Created on: 8 nov. 2021
 *      Author: Guillermo
 */

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

#ifndef API_DELAY_H_
#define API_DELAY_H_

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;  	// Contiene el tiempo cuando arrancó el delay
   tick_t duration;		// Cantidad que desea contarse en ms
   bool_t running;		// Estado del delay
} delay_t;

void delayInit( delay_t *delay, tick_t duration );
bool_t delayRead( delay_t *delay );
void delayWrite( delay_t *delay, tick_t duration );


#endif /* API_DELAY_H_ */
