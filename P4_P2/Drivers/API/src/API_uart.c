/*
 * API_uart.c
 *
 *  Created on: 22 nov. 2021
 *      Author: gcasti
 */

#include <stdio.h>
#include <string.h>
#include "API_uart.h"

typedef struct BaudRate
{
    char strBaud[20];
    int intBaud;
}BaudRate_t;

// Define un arreglo de estructuras con tipos predefinidos de velocidades de Baud Rate
static BaudRate_t DefBaudRate[5]={
    {"2400",2400},
    {"4800",4800},
    {"9600",9600},
    {"19200",19200},
    {"115200",115200},
};

typedef enum{B2400, B4800, B9600, B19200, B115200} baud_t;

// Selección del Baud Rate de operación, utilizar los tipos numerados
const baud_t confbaud = B115200;

/* UART handler declaration */
static UART_HandleTypeDef UartHandle;

/**
 * Función privada que envia los parámetros de configuración
 * del módulo UART
 */
static void sendParameters(){
	  uartSendString("\n\r **************************** \r");
	  uartSendString("\n\r * Modulo UART inicializado   \r");
    uartSendString("\n\r * Baud Rate: ");
	  uartSendString(DefBaudRate[confbaud].strBaud);
	  if(UART_STOPBITS_1 == UartHandle.Init.StopBits){
		  uartSendString("\n\r * Stop bit: 1");
	  }else{uartSendString("\n\r * Stop bit: 2");}
	  uartSendString("\n\r * Flow control:");
	  switch(UartHandle.Init.HwFlowCtl){
		  case UART_HWCONTROL_NONE:
			  uartSendString("NONE ");
			  break;
		  case UART_HWCONTROL_RTS:
			  uartSendString("RTS ");
			  break;
		  case UART_HWCONTROL_CTS:
			  uartSendString("CTS ");
			  break;
		  case UART_HWCONTROL_RTS_CTS:
			  uartSendString("RTS/CTS ");
			  break;
		  default:
			  break;
	 }

	  uartSendString("\n\r * Parity:");
	  	  switch(UartHandle.Init.Parity ){
	  		  case UART_PARITY_NONE:
	  			  uartSendString("NONE ");
	  			  break;
	  		  case UART_PARITY_EVEN:
	  			  uartSendString("EVEN ");
	  			  break;
	  		  case UART_PARITY_ODD:
	  			  uartSendString("ODD ");
	  			  break;
	  		  default:
	  			  break;
	  	  }
	  uartSendString("\n\r **************************** \n\r");

}

bool_t uartInit(){
	HAL_StatusTypeDef retVal = HAL_OK;

	  /* Configure the UART peripheral ######################################*/
	  /* USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 115200 baud
	      - Hardware flow control disabled (RTS and CTS signals) */

	  UartHandle.Instance        = USARTx;
	  UartHandle.Init.BaudRate   = DefBaudRate[confbaud].intBaud;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
		  retVal = HAL_ERROR;
	  }

	  sendParameters();
	  return retVal;
}


void uartSendString(char * pstring){
	HAL_UART_Transmit(&UartHandle,(uint8_t *)pstring,strlen(pstring)/sizeof(char), 1000);
}



