/*
 * API_uart.h
 *
 *  Created on: 22 nov. 2021
 *      Author: gcasti
 */

#ifndef API_SRC_API_UART_H_
#define API_SRC_API_UART_H_

#include <stdbool.h>
#include "stm32f4xx_nucleo_144.h"

typedef bool bool_t;


/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3


/**
 * Inicializa el módulo UART utilizando los parámetros definidos
 * dentro de la función
 */
bool_t uartInit();

/**
 * Envía una cadena de carácteres mediante el módulo UART.
 */
void uartSendString(char * pstring);



#endif /* API_SRC_API_UART_H_ */
