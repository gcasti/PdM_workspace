/*
 * API_debounce.c
 *
 *  Created on: 14 nov. 2021
 *      Author: gcasti
 */

#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal.h"
#include "API_debounce.h"
#include "API_delay.h"

/**************************************
 * 		Definición de estados
 **************************************/
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING,
} debounce_t;

/**************************************
 * 		Variables privadas
 **************************************/
static debounce_t stateActual;
static delay_t timerDebounce;

callback callbackInit;
callback callbackPressed;
callback callbackReleased;
/**************************************
 * 	Definición de funciones privadas
 **************************************/
static void buttonPressed(void);
static void buttonReleased(void);

/**************************************
 * 	Implementación de funciones públicas
 **************************************/
void debounceInit(void){
	stateActual = BUTTON_UP;
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

void setInitCBK(callback cbkinit){
	callbackInit = cbkinit;
}

void setButtomPressedCBK(callback cbkpressed){
	callbackPressed = cbkpressed;
}

void setButtomReleasedCBK(callback cbkreleased){
	callbackReleased = cbkreleased;
}


/**************************************
 * 	Implementación de funciones privadas
 **************************************/
static void buttonPressed(){
	(*callbackPressed)();
}

static void buttonReleased(){
	(*callbackReleased)();
}
