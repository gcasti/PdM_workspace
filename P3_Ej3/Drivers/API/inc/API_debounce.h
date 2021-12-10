/*
 * API_debounce.h
 *
 *  Created on: 14 nov. 2021
 *      Author: gcasti
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_


// Tiempo en milisegundos para el antirebote
#define DELAY_DEBOUNCE 40

// Se define un puntero a funciones para las llamadas a callbacks
typedef void (*callback)(void);


/*
 * Callback que se ejecuta en el estado inicial del módulo debounce
 */
void setInitCBK(callback cbkinit);

/*
 * Callback que se ejecuta cuando se detecta un flanco ascendente
 */
void setButtomPressedCBK(callback cbkpressed);

/*
 * Callback que se ejecuta cuando se detecta un flanco descendente
 */
void setButtomReleasedCBK(callback cbkreleased);


/*
 * Inicializa el módulo antirebote
 */
void debounceInit();

/*
 * Actualiza la maáquina de estados del módulo antirebote
 */
void debounceUpdate();


#endif /* API_INC_API_DEBOUNCE_H_ */
