/*
 * API_debounce.h
 *
 *  Created on: 14 nov. 2021
 *      Author: gcasti
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_


#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal.h"
#include "API_delay.h"

#define DELAY_DEBOUNCE 40

void debounceInit();
void debounceUpdate();


#endif /* API_INC_API_DEBOUNCE_H_ */
