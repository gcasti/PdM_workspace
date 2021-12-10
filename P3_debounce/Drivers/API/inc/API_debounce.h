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

/*
 * Inicializa el módulo antirebote
 */
void debounceInit();

/*
 * Actualiza la maáquina de estados del módulo antirebote
 */
void debounceUpdate();


#endif /* API_INC_API_DEBOUNCE_H_ */
