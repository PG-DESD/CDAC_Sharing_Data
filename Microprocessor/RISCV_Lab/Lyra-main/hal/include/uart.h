/**
 @file uart.h
 @brief header file for UART driver
 @author Arif B (arif.dev@pm.me)
 */

#ifndef _UART_H_
#define _UART_H_

#include <vega/thejas32.h>

#include <stdint.h>

#define UART_PARITY_NONE		('N')
#define UART_PARITY_ODD			('O')
#define UART_PARITY_EVEN		('E')


enum __UART_Error_t {
	UART_ERROR_OVERRUN = 0x20,
	UART_ERROR_PARITY = 0x21,
	UART_ERROR_FRAME = 0x22,
};


typedef struct __UART_Handle_t {
	UART_Reg_t *Instance;
	uint32_t BaudRate;
	uint32_t WordLength;
	uint32_t Parity;
	uint32_t StopBits;
	char *TxBuffer;
	uint32_t TxXferCount;
	uint32_t TxState;
	char *RxBuffer;
	uint32_t RxXferCount;
	uint32_t RxState;
} UART_Handle_t;

extern UART_Handle_t huart0;
extern UART_Handle_t huart1;
extern UART_Handle_t huart2;

/*---------------------------------------------------------------------------------------------------*/

/* Initialize the UART controller according to the Handle */
int UART_Init(UART_Handle_t *huart);

/*---------------------------------------------------------------------------------------------------*/

/* Transfer an amount of data over UART in blocking mode */
int UART_Transmit(UART_Handle_t *huart, const char *buffer, uint32_t len);

/*---------------------------------------------------------------------------------------------------*/

/* Transfer an amount of data over UART in non-blocking mode */
int UART_Transmit_IT(UART_Handle_t *huart, const char *buffer, uint32_t len);

/*---------------------------------------------------------------------------------------------------*/

/* UART Tx complete callback function */
void UART_TxCpltCallback(UART_Handle_t *huart);

/*---------------------------------------------------------------------------------------------------*/

/* Receive an amount of data over UART in blocking mode */
int UART_Receive(UART_Handle_t *huart, char *buffer, uint32_t len);

/*---------------------------------------------------------------------------------------------------*/

/* Receive an amount of data over UART in non-blocking mode */
int UART_Receive_IT(UART_Handle_t *huart, char *buffer, uint32_t len);

/*---------------------------------------------------------------------------------------------------*/

/* UART Rx complete callback function*/
void UART_RxCpltCallback(UART_Handle_t *huart);

/*---------------------------------------------------------------------------------------------------*/

#endif /*_UART_H_*/