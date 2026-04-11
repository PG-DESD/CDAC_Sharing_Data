/** 
 @file thejas32.h
 @brief THEJAS32 hardware registers
 @author Arif B (arif.dev@pm.me)
*/

#ifndef _THEJAS32_H_
#define _THEJAS32_H_

#ifdef __cplusplus
    extern "C" {
#endif /* __cpluscplus */

#include <stdint.h>

#define __IO    	volatile

enum ret_t {
	OK = 0x10,
	FAIL = 0x11,
};

enum state_t {
	STATE_READY = 0xca11ab1e,
	STATE_BUSY = 0xca11ed
};

#define SYSTEMCLK		(100000000UL)		/* 100 MHz core clock */

/*
* @brief Memory Map
*/

#define UART_BASE						(0x10000100UL)
#define SPI_BASE                        (0x10000600UL)
#define I2C_BASE                        (0x10000800UL)
#define TIMER_BASE                      (0x10000A00UL)
#define ADC_BASE                        (0x10001000UL)                   
#define PWM_BASE                        (0x10400000UL)
#define PLIC_BASE                       (0x20010000UL)
#define PLIC_SWINT_EN					(0x20010400UL)

/*---------------------------------------------------------------------------------------------------*/
/*
* @brief GPIO Registers
*/

#define GPIOA_BASE                  (0x10080000UL)   
#define GPIOA_DIR					(*(__IO uint32_t *)(0x100C0000UL))

#define GPIOB_BASE                  (0x10180000UL)  
#define GPIOB_DIR					(*(__IO uint32_t *)(0x101C0000UL))

/*---------------------------------------------------------------------------------------------------*/

/* TIMER 
32-bit auto-reload down counter
*/

typedef struct {
	__IO uint32_t LOAD;						/* Load Count Register */
	const __IO uint32_t CVAL;				/* Current Value Register */
	__IO uint32_t CTRL;						/* Control Register */
	const __IO uint32_t ICLR;				/* Interrupt Clear Register */
	const __IO uint32_t ISR;				/* Interrupt Status Register */
} Timer_Reg_t;


#define TIMER0						((Timer_Reg_t *)(TIMER_BASE + 0x00UL))			
#define TIMER1						((Timer_Reg_t *)(TIMER_BASE + 0x14UL))
#define TIMER2						((Timer_Reg_t *)(TIMER_BASE + 0x28UL))

#define TIMERS_RAWISR				(*(__IO uint32_t *)(TIMER_BASE + 0xA8UL))	/* Global Raw Interrupt Status register for all timers */
#define TIMER0_RAWISR				(0x1UL)
#define TIMER1_RAWISR				(0x2UL)
#define TIMER2_RAWISR				(0x4UL)

/* Timer Control Register bits */
#define TIMER_CTRL_EN_Pos			(0UL)
#define TIMER_CTRL_EN				(0x1U << TIMER_CTRL_EN_Pos)					/* Timer Enable */
#define TIMER_CTRL_MODE_Pos			(1UL)
#define TIMER_CTRL_MODE_1			(0x1U << TIMER_CTRL_MODE_Pos)				/* Periodic Mode */
#define TIMER_CTRL_INT_Pos			(2UL)
#define TIMER_CTRL_INTMsk  			(1U << TIMER_CTRL_INT_Pos)					/* Timer Interrupt Mask */

/*---------------------------------------------------------------------------------------------------*/

/* PWM Controller */

typedef struct
{
	__IO uint32_t CTRL;					/* PWM Control register */
	const __IO uint32_t SR;				/* PWM Status register */
	__IO uint32_t PERIOD;				/* PWM Period register */
	__IO uint32_t DUTY;					/* PWM Duty cycle register */
} PWM_Reg_t;


#define PWMCH1						((PWM_Reg_t *)(PWM_BASE + 0x00UL))
#define PWMCH2						((PWM_Reg_t *)(PWM_BASE + 0x10UL))
#define PWMCH3						((PWM_Reg_t *)(PWM_BASE + 0x20UL))
#define PWMCH4						((PWM_Reg_t *)(PWM_BASE + 0x30UL))
#define PWMCH5						((PWM_Reg_t *)(PWM_BASE + 0x40UL))
#define PWMCH6						((PWM_Reg_t *)(PWM_BASE + 0x50UL))
#define PWMCH7						((PWM_Reg_t *)(PWM_BASE + 0x60UL))
#define PWMCH8						((PWM_Reg_t *)(PWM_BASE + 0x70UL))

/* PWM Control registers */
#define PWM_CTRL_MODE_Pos			(0UL)
#define PWM_CTRL_MODE_IDLE			(0x0U << PWM_CTRL_MODE_Pos)
#define PWM_CTRL_MODE_ONESHOT		(0x1U << PWM_CTRL_MODE_Pos)
#define PWM_CTRL_MODE_CONTINUOUS	(0x1U << PWM_CTRL_MODE_Pos)

#define PWM_CTRL_AC_Pos				(2UL)
#define PWM_CTRL_AC_LEFT			(0x0U << PWM_CTRL_AC_Pos)
#define PWM_CTRL_AC_RIGHT			(0x1U << PWM_CTRL_AC_Pos)

#define PWM_CTRL_IE_Pos				(4UL)
#define PWM_CTRL_IE					(0x1U << PWM_CTRL_IE_Pos)

#define PWM_CTRL_OPC_Pos			(5UL)
#define PWM_CTRL_OPC_LOW			(0x0U << PWM_CTRL_OPC_Pos)
#define PWM_CTRL_OPC_HIGH			(0x1U << PWM_CTRL_OPC_Pos)

#define PWM_CTRL_RCOUNT_Pos			(6UL)

/* PWM Status registers */
#define PWM_SR_STAT_Pos				(0UL)
#define PWM_SR_STAT_IDLE			(0x0U << PWM_SR_STAT_Pos)
#define PWM_SR_STAT_ACTIVE			(0x1U << PWM_SR_STAT_Pos)	

#define PWM_SR_IP_Pos				(1UL)
#define PWM_SR_IP					(0x1U << PWM_SR_IP_Pos)

/* Global PWM registers */

#define PWM_GCR						(*(__IO uint32_t *)(PWM_BASE + 0x80UL))

#define PWM_GCR_EN_Pos				(0UL)
#define PWM_GCR_EN					(0x1U << PWM_GCR_EN_Pos)

#define PWM_GCR_IE_Pos				(1UL)
#define PWM_GCR_IE					(0x1U << PWM_GCR_IE_Pos)

#define PWM_GCR_IP_Pos				(2UL)
#define PWM_GCR_IP					(0x1U << PWM_GCR_IP_Pos)


/*---------------------------------------------------------------------------------------------------*/

/*
PLIC - Platform-Level Interrupt Controller (for External Interrupts)
*/

typedef struct {
	const __IO uint32_t RAWISR;				/* Raw Interrupt Status */
	const uint32_t Padding1;				/* Address Padding */
	__IO uint32_t IER;						/* Interrupt Enable Register */
	const uint32_t Padding2;				/* Address padding */
	const __IO uint32_t ISR;				/* Interrupt Status */
} PLIC_Reg_t;


#define PLIC						((PLIC_Reg_t *)0x20010000UL)

/*---------------------------------------------------------------------------------------------------*/
/*
* UART Controller
Based on UART16450
*/

typedef struct {
	union {
		const __IO uint32_t RXFIFO;				/* UART Receiever Buffer Register */
		__IO uint32_t TXFIFO;					/* UART Transmitter Holding Register */
		__IO uint32_t DLL;						/* UART Divisor Latch LSB */
	};
	union {
		__IO uint32_t IER;						/* UART Interrupt Enable Register */
		__IO uint32_t DLM;						/* UART Divisor Latch MSB */
	};
	const __IO uint32_t IIR;					/* UART Interrupt Identification Register */		
	__IO uint32_t LCR;                          /* UART Line Control Register */
	const uint32_t PadMCR;						/* Modem Control Register Unavailable */
	__IO uint32_t LSR;							/* UART Line Status Register */	
	const uint32_t PadMSR;						/* Modem Status Register Unavailable */
	__IO uint32_t SCRATCH;						/* UART Scratch Register */
} UART_Reg_t;

#define UART0 							((UART_Reg_t *)(UART_BASE + 0x0000UL))    /* 0x1000 0100 */
#define UART1 							((UART_Reg_t *)(UART_BASE + 0x0100UL))    /* 0x1000 0200 */
#define UART2 							((UART_Reg_t *)(UART_BASE + 0x0200UL))    /* 0x1000 0300 */

/* UART Interrupt Enable Register (IER) bits */

#define UART_IER_RXFF_Pos				(0U)			
#define UART_IER_RXFF					(0x1U << UART_IER_RXFF_Pos)			/* Receive FIFO Full interrupt */
#define UART_IER_TXFE_Pos				(1U)			
#define UART_IER_TXFE					(0x1U << UART_IER_TXFE_Pos)			/* Transmit FIFO Empty Interrupt */
#define UART_IER_RXLS_Pos				(2U)				
#define UART_IER_RXLS					(0x1U << UART_IER_RXLS_Pos)			/* Receiver Line Status Interrupt */


/* UART Interrupt Identification Register (IIR) bits */

#define UART_IIR_NPEND_Pos				(0U)	
#define UART_IIR_NPEND					(0x1U << UART_IIR_PEND_Pos)	/* Interrupt NOT Pending */

#define UART_IIR_ID_Pos					(1U)						/* Interrupt ID [2:0] */
#define UART_IIR_ID_RXLS				(0x3U << UART_IIR_ID_Pos)	/* RX Line Status Interrupt ID */
#define UART_IIR_ID_RXFF				(0x2U << UART_IIR_ID_Pos)	/* RX FIFO Full Interrupt ID */
#define UART_IIR_ID_TXFE				(0x1U << UART_IIR_ID_Pos)	/* TX FIFO Empty Interrupt ID */


/* UART Line Control Register */

/* | DLAB | SB | SP | PS | PE | STOP | WL [1:0] |  */

#define UART_LCR_WL_Pos                 (0U)    /* Word Length [1:0] */
#define UART_LCR_WL_Msk                 (0x3U << UART_LCR_WL_Pos)
#define UART_LCR_WL8					(0x3U << UART_LCR_WL_Pos)
#define UART_LCR_WL7					(0x2U << UART_LCR_WL_Pos)
#define UART_LCR_WL6					(0x1U << UART_LCR_WL_Pos)
#define UART_LCR_WL5					(0x0U << UART_LCR_WL_Pos)

#define UART_LCR_STOP_Pos               (2U)    /* Stop Bits */
#define UART_LCR_STOP_1					(0x0U << UART_LCR_STOP_Pos)
#define UART_LCR_STOP_2					(0x1U << UART_LCR_STOP_Pos)

#define UART_LCR_PE_Pos                	(3U)    
#define UART_LCR_PE	                	(0x1U << UART_LCR_PE_Pos)    /* Parity Enable */

#define UART_LCR_PS_Pos                 (4U)    /* Parity Selection */
#define UART_LCR_PS_EVEN				(0x0U << UART_LCR_PS_Pos)
#define UART_LCR_PS_ODD					(0x1U << UART_LCR_PS_Pos)

#define UART_LCR_PE_NONE				(0x0U << UART_LCR_PE_Pos)
#define UART_LCR_PE_EVEN				(0x1U << UART_LCR_PE_Pos | 0x0U << UART_LCR_PS_Pos)
#define UART_LCR_PE_ODD					(0x1U << UART_LCR_PE_Pos | 0x0U << UART_LCR_PS_Pos)


#define UART_LCR_SP_Pos                 (5U)    /* Stick Parity */
#define UART_LCR_SP						(0x1U << UART_LCR_SP_Pos)

#define UART_LCR_SB_Pos                 (6U)    /* Set Break */
#define UART_LCR_SB                 	(0x1U << UART_LCR_SB_Pos)    /* Set Break */

#define UART_LCR_DLAB_Pos               (7U)    /* Divisor Latch Access Bit */
#define UART_LCR_DLAB 					(0x1U << UART_LCR_DLAB_Pos)

/* UART Line Status Register */

#define UART_LSR_RXFF_Pos				(0U)	/* RX FIFO Full */
#define UART_LSR_RXFF					(1U << UART_LSR_RXFF_Pos)  

#define UART_LSR_ORE_Pos				(1U)	/* Overrun Error bit */
#define UART_LSR_ORE					(0x1 << UART_LSR_ORE_Pos)	

#define UART_LSR_PE_Pos					(2U)	/* Parity Error bit */
#define UART_LSR_PE						(0x1U << UART_LSR_PE_Pos)	

#define UART_LSR_FE_Pos					(3U)	/* Framing Error bit */
#define UART_LSR_FE						(0x1U << UART_LSR_FE_Pos)	

#define UART_LSR_BRKINT_Pos				(4U)	/* Break Interrupt bit */
#define UART_LSR_BRKINT					(0X1U << UART_LSR_BRKINT_Pos)

#define UART_LSR_TXFE_Pos				(5U)	/* Transmitter FIFO Empty */
#define UART_LSR_TXFE					(1UL << UART_LSR_TXFE_Pos )

#define UART_LSR_TXE_Pos				(6U)	/* Transmitter FIFO and shift-register Empty */
#define UART_LSR_TXE					(0x1U << UART_LSR_TXE_Pos)	

#define UART_LSR_FIFOERR_Pos			(7U)	/*  FIFO Error */
#define UART_LSR_FIFOERR				(0x1U << UART_LSR_FIFOERR_Pos)	/*  FIFO Error */

/*---------------------------------------------------------------------------------------------------*/



#ifdef __cplusplus
    }
#endif /* __cplusplus */
#endif /* _THEJAS32_H_ */