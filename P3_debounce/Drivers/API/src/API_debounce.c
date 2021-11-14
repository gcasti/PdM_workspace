/*
 * API_debounce.c
 *
 *  Created on: 14 nov. 2021
 *      Author: gcasti
 */
#include "API_debounce.h"


typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
} debounce_t;

static debounce_t stateActual;
static delay_t timerDebounce;

// Funciones privadas
void buttonPressed(){
	BSP_LED_Toggle(LED1);
}

void buttonReleased(){
	BSP_LED_Toggle(LED2);
}

void debounceInit(void){
	stateActual = BUTTON_UP;
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	delayInit(&timerDebounce, DELAY_DEBOUNCE);

}


void debounceUpdate(void){

	switch(stateActual){
		case BUTTON_UP:
			if (BSP_PB_GetState(BUTTON_USER) ){
				delayRead(&timerDebounce);
				stateActual = BUTTON_FALLING;
			}
			break;

		case BUTTON_FALLING:
			if(delayRead(&timerDebounce)){
				if(BSP_PB_GetState(BUTTON_USER)){
					buttonPressed();
					stateActual = BUTTON_DOWN;
				}else{
					stateActual = BUTTON_UP;
				}
			}
			break;

		case BUTTON_DOWN:
			if (!BSP_PB_GetState(BUTTON_USER) ){
				delayRead(&timerDebounce);
				stateActual = BUTTON_RISING;
			}
			break;

		case BUTTON_RISING:
			if(delayRead(&timerDebounce)){
				if(!BSP_PB_GetState(BUTTON_USER)){
					buttonReleased();
					stateActual = BUTTON_UP;
				}else{
					stateActual = BUTTON_DOWN;
				}
			}
			break;

		default :
			debounceInit();
	}
}


