/** 
 @file csr.h
 @brief THEJAS32 Control and Status Register bits and macros
 @author Arif B (arif.dev@pm.me)
*/

#ifndef CSR_H
#define CSR_H

/* MSTATUS (Machine Status) register */

#define MSTATUS_MIE_Pos     (3)
#define MSTATUS_MIE         (0x1 << MSTATUS_MIE_Pos)            /* Machine Interrupt Enable */
#define MSTATUS_MPIE_Pos    (7)
#define MSTATUS_MPIE        (0x1 << MSTATUS_MPIE_Pos)           /* Machine Pending Interrupt Enable */


/* MTVEC (Machine Trap Vector Base-Address) register */

#define MTVEC_MODE_Pos      (0)
#define MTVEC_MODE_M0       (0x0 << MTVEC_MODE_Pos)
#define MTVEC_MODE_M1       (0x1 << MTVEC_MODE_Pos)
#define MTVEC_BASE_Pos      (2)

/* MIP (Machine Interrupt Pending) register */

#define MIP_MSIP_Pos        (3)
#define MIP_MSIP            (0x1 << MIP_MSIP_Pos)             /* Machine Software Interrupt Pending */
#define MIP_MTIP_Pos        (7)
#define MIP_MTIP            (0x1 << MIP_MTIP_Pos)             /* Machine Timer Interrupt Pending */
#define MIP_MEIP_Pos        (11)                              
#define MIP_MEIP            (0x1 << MIP_MEIP_Pos)             /* Machine External Interrupt Pending */


/* MIE (Machine Interrupt Enable) register */

#define MIE_MSIE_Pos        (3)
#define MIE_MSIE            (0x1 << MIE_MSIE_Pos)             /* Machine Software Interrupt Enable */
#define MIE_MTIE_Pos        (7)
#define MIE_MTIE            (0x1 << MIE_MTIE_Pos)             /* Machine Timer Interrupt Enable */
#define MIE_EIE_Pos         (11)                  
#define MIE_EIE             (0x1 << MIE_EIE_Pos)              /* Machine External Interrupt Enable */



/* MCAUSE (Machine Trap Cause) register */

#define MCAUSE_SW          (3)
#define MCAUSE_TIMER       (7)
#define MCAUSE_EXTI        (11)


/* CSR Macros */

#define csr_read(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define csr_write(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

#define csr_swap(reg, val) ({ unsigned long __tmp; \
  asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val)); \
  __tmp; })

#define csr_setbit(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })

#define csr_clrbit(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })

#endif // CSR_H

