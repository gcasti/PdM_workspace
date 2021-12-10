/*
 * API_delay.h
 *
 *  Created on: 8 nov. 2021
 *      Author: Guillermo
 *      Modulo de software para trabajar con retardos no bloqueantes
 */

#include <stdio.h>
#include <stdbool.h>


#ifndef API_DELAY_H_
#define API_DELAY_H_

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;  	// Contiene el tiempo cuando arranca el timer
   tick_t duration;		// Cantidad que desea contarse en ms
   bool_t running;		// Estado del timer
} delay_t;

/*
 * Inicializa el módulo de delay
 */
void delayInit( delay_t *delay, tick_t duration );

/*
 * Devuelve el estado del módulo
 */
bool_t delayRead( delay_t *delay );

void delayWrite( delay_t *delay, tick_t duration );


#endif /* API_DELAY_H_ */
