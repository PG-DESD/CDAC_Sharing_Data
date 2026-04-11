/**
 @file hal_uart.c
 @brief Contains routines for UART interface
 @author Arif B <arif.dev@pm.me>
 */

#include <vega/interrupt.h>
#include <vega/thejas32.h>
#include <vega/uart.h>

#include <stdio.h>
#include <errno.h>


/*---------------------------------------------------------------------------------------------------*/

UART_Handle_t huart0 = {
	.Instance = UART0,
	.BaudRate = 115200,
	.WordLength = 8,
	.Parity = 'N',
	.StopBits = 1,
	.RxBuffer = NULL,
	.TxBuffer = NULL,
	.RxXferCount = 0,
	.TxXferCount = 0,
	.TxState = STATE_READY,
	.RxState = STATE_READY
};

UART_Handle_t huart1 = {
	.Instance = UART1,
	.BaudRate = 115200,
	.WordLength = 8,
	.Parity = 'N',
	.StopBits = 1,
	.RxBuffer = NULL,
	.TxBuffer = NULL,
	.RxXferCount = 0,
	.TxXferCount = 0,
	.TxState = STATE_READY,
	.RxState = STATE_READY
};

UART_Handle_t huart2 = {
	.Instance = UART2,
	.BaudRate = 115200,
	.WordLength = 8,
	.Parity = 'N',
	.StopBits = 1,
	.RxBuffer = NULL,
	.TxBuffer = NULL,
	.RxXferCount = 0,
	.TxXferCount = 0,
	.TxState = STATE_READY,
	.RxState = STATE_READY
};

 
/*---------------------------------------------------------------------------------------------------*/

/* 
Initialises UART controller with attributes suggested by huart
*/

int UART_Init(UART_Handle_t *huart) 
{
	if (huart == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->Instance == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->TxState == STATE_BUSY || huart->RxState == STATE_BUSY) {
		errno = EBUSY;
		return FAIL;
	}

	(huart->Instance)->LCR = 0x00000000UL;

	switch (huart->WordLength) {
		case 8:
			(huart->Instance)->LCR |= UART_LCR_WL8;
			break;
		case 7:
			(huart->Instance)->LCR |= UART_LCR_WL7;
			break;
		case 6:
			(huart->Instance)->LCR |= UART_LCR_WL6;
			break;
		case 5:
			(huart->Instance)->LCR |= UART_LCR_WL5;
			break;
		default:
			return EINVAL;
	}
		
	switch (huart->Parity) {
		case 'n':
		case 'N':
		case 0:
			(huart->Instance)->LCR &= ~(0x1UL << UART_LCR_PE_Pos);
			break;
		case 'e':
		case 'E':
		case 2:
			(huart->Instance)->LCR |= UART_LCR_PE_EVEN;
			break;
		case 'o':
		case 'O':
		case 1:
			(huart->Instance)->LCR |= UART_LCR_PE_ODD;
			break;
		default:
			return EINVAL;
	}

	switch (huart->StopBits) {
		case 1:
			(huart->Instance)->LCR |= UART_LCR_STOP_1;
			break;
		case 2:
			(huart->Instance)->LCR |= UART_LCR_STOP_2;
			break;
		default:
			return EINVAL;
	}
	

	uint32_t divisor = (uint32_t) (SYSTEMCLK / ((huart->BaudRate) * 16));

	/* Enable Latch Access and load MSB and LSB into divisor latch register to set baud rate*/

	(huart->Instance)->LCR |= UART_LCR_DLAB;
	(huart->Instance)->DLL = divisor & 0xFFFFUL;
	(huart->Instance)->DLM = (divisor >> 8) & 0xFFFFUL;

	/* Disable Divisor Latch access */
	(huart->Instance)->LCR &= ~(UART_LCR_DLAB);

	/* Disable all UART interrupts */
	(huart->Instance)->IER = 0x00UL;

	return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int UART_Transmit(UART_Handle_t *huart, const char *buffer, uint32_t len)
{
	if (huart == NULL || buffer == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->Instance == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->TxState == STATE_BUSY) {
		errno = EBUSY;
		return FAIL;
	}

	huart->TxState = STATE_BUSY;
	// Transmit till specified length or till buffer is empty
	while (*buffer && len--) {
		// Wait till Tx FIFO is empty
		while (! (huart->Instance->LSR & UART_LSR_TXFE));

		(huart->Instance)->TXFIFO = *buffer++;
	}
	huart->TxState = STATE_READY;

	return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int UART_Transmit_IT(UART_Handle_t *huart, const char *buffer, uint32_t len)
{
	if (len == 0) {
		return OK;
	}

	if (huart == NULL || buffer == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->Instance == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->TxState == STATE_BUSY) {
		errno = EBUSY;
		return FAIL;
	}

	int irqn;
	if (huart->Instance == UART0) {
		irqn = UART0_IRQn;
	}
	else if (huart->Instance == UART1) {
		irqn = UART1_IRQn;
	}
	else if (huart->Instance == UART2) {
		irqn = UART2_IRQn;
	}
	else {
		errno = ENXIO;
		return FAIL;
	}

	huart->TxBuffer = (char *)buffer;
	huart->TxXferCount = len;
	huart->Instance->IER |= UART_IER_TXFE;
	PLIC->IER |= 0x1 << irqn;

	huart->TxState = STATE_BUSY;

	return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int UART_Receive(UART_Handle_t *huart, char *buffer, uint32_t len)
{
	if (huart == NULL || buffer == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->Instance == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->RxState == STATE_BUSY) {
		errno = EBUSY;
		return FAIL;
	}

	huart->RxState = STATE_BUSY;
	// Receive till specified length
	while (len--) {
		//wait till RX FIFO is full
		while (! (huart->Instance->LSR & UART_LSR_RXFF));
		*buffer++ = huart->Instance->RXFIFO;
	}
	huart->RxState = STATE_READY;


	return OK;
}

/*---------------------------------------------------------------------------------------------------*/

int UART_Receive_IT(UART_Handle_t *huart, char *buffer, uint32_t len)
{
	if (len == 0) {
		return OK;
	}
	
	if (huart == NULL || buffer == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->Instance == NULL) {
		errno = EFAULT;
		return FAIL;
	}

	if (huart->RxState == STATE_BUSY) {
		errno = EBUSY;
		return FAIL;
	}

	int irqn;
	if (huart->Instance == UART0) {
		irqn = UART0_IRQn;
	}
	else if (huart->Instance == UART1) {
		irqn = UART1_IRQn;
	}
	else if (huart->Instance == UART2) {
		irqn = UART2_IRQn;
	}
	else {
		errno = ENXIO;
		return FAIL;
	}

	huart->RxBuffer = buffer;
	huart->RxXferCount = len;
	huart->Instance->IER |= UART_IER_RXFF;
	PLIC->IER |= 0x1 << irqn;

	huart->RxState = STATE_BUSY;

	return OK;
}

/*---------------------------------------------------------------------------------------------------*/

void __UART_RxISR(UART_Handle_t *huart)
{
	*(huart->RxBuffer) = (huart->Instance->RXFIFO & 0xFFUL);
	huart->RxBuffer++;
	huart->RxXferCount--;

	if (huart->RxXferCount == 0UL) {
		huart->Instance->IER &= ~(UART_IER_RXFF);
		UART_RxCpltCallback(huart);
		huart->RxState = STATE_READY;
		return;
	}
}

void __UART_TxISR(UART_Handle_t *huart)
{
	huart->Instance->TXFIFO = (*(uint32_t *)huart->TxBuffer) & 0xFFUL;
	huart->TxBuffer++;
	huart->TxXferCount--;

	if (huart->TxXferCount == 0UL) {
		huart->Instance->IER &= ~(UART_IER_TXFE);
		UART_TxCpltCallback(huart);
		huart->TxState = STATE_READY;
		return;
	}
}

/*---------------------------------------------------------------------------------------------------*/

void __UART_ISR(UART_Handle_t *huart)
{
	if (huart == NULL) {
		errno = EFAULT;
		return;
	}

	if (huart->Instance == NULL) {
		errno = EFAULT;
		return;
	}

	uint32_t id = huart->Instance->IIR & 0xE;

	switch (id) {
		case UART_IIR_ID_RXFF:
			__UART_RxISR(huart);
			break;

		case UART_IIR_ID_TXFE:
			__UART_TxISR(huart);
			break;

		default:
			break;
	}
}


void UART0_IRQHandler(void)
{
	__UART_ISR(&huart0);
}

void UART1_IRQHandler(void)
{
	__UART_ISR(&huart1);
}

void UART2_IRQHandler(void)
{
	__UART_ISR(&huart2);
}


__attribute__((weak)) void UART_RxCpltCallback(UART_Handle_t *huart)
{
	return;
}

__attribute__((weak)) void UART_TxCpltCallback(UART_Handle_t *huart)
{
	return;
}

/*---------------------------------------------------------------------------------------------------*/