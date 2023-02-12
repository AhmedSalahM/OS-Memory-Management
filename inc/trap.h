#ifndef FOS_INC_TRAP_H
#define FOS_INC_TRAP_H

// Trap numbers
// These are processor defined:
#define T_DIVIDE     0		// divide error
#define T_DEBUG      1		// debug exception
#define T_NMI        2		// non-maskable interrupt
#define T_BRKPT      3		// breakpoint
#define T_OFLOW      4		// overflow
#define T_BOUND      5		// bounds check
#define T_ILLOP      6		// illegal opcode
#define T_DEVICE     7		// device not available 
#define T_DBLFLT     8		// double fault
/* #define T_COPROC  9 */	// reserved (not generated by recent processors)
#define T_TSS       10		// invalid task switch segment
#define T_SEGNP     11		// segment not present
#define T_STACK     12		// stack exception
#define T_GPFLT     13		// General protection fault
#define T_PGFLT     14		// page fault
/* #define T_RES    15 */	// reserved
#define T_FPERR     16		// floating point error
#define T_ALIGN     17		// Alignment check
#define T_MCHK      18		// machine check
#define T_SIMDERR   19		// SIMD floating point error

//IRQs
#define IRQ0_Clock   32		// Clock IRQ

// These are arbitrarily chosen, but with care not to overlap
// processor defined exceptions or interrupt vectors.
#define T_SYSCALL   48		// system call
#define T_DEFAULT   500		// catchall

#ifndef __ASSEMBLER__

#include <inc/types.h>

struct PushRegs {
	/* registers as pushed by pusha */
	uint32 reg_edi;
	uint32 reg_esi;
	uint32 reg_ebp;
	uint32 reg_oesp;		/* Useless */
	uint32 reg_ebx;
	uint32 reg_edx;
	uint32 reg_ecx;
	uint32 reg_eax;
};

struct Trapframe {
	struct PushRegs tf_regs;
	uint16 tf_es;
	uint16 tf_padding1;
	uint16 tf_ds;
	uint16 tf_padding2;
	uint32 tf_trapno;
	/* below here defined by x86 hardware */
	uint32 tf_err;
	uint32* tf_eip;
	uint16 tf_cs;
	uint16 tf_padding3;
	uint32 tf_eflags;
	/* below here only when crossing rings, such as from user to kernel */
	uint32* tf_esp;
	uint16 tf_ss;
	uint16 tf_padding4;
};


#endif /* !__ASSEMBLER__ */

// Must equal 'sizeof(struct Trapframe)'.
// A static_assert in kern/trap.c checks this.
#define SIZEOF_STRUCT_TRAPFRAME	0x44

#endif /* !FOS_INC_TRAP_H */
