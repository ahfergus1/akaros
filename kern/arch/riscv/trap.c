#include <arch/arch.h>
#include <assert.h>
#include <arch/trap.h>
#include <arch/console.h>
#include <string.h>
#include <process.h>
#include <syscall.h>
#include <monitor.h>
#include <manager.h>
#include <stdio.h>
#include <smp.h>
#include <slab.h>
#include <mm.h>
#include <umem.h>
#include <pmap.h>

/* These are the stacks the kernel will load when it receives a trap from user
 * space.  The deal is that they get set right away in entry.S, and can always
 * be used for finding the top of the stack (from which you should subtract the
 * sizeof the trapframe.  Note, we need to have a junk value in the array so
 * that this is NOT part of the BSS.  If it is in the BSS, it will get 0'd in
 * kernel_init(), which is after these values get set.
 *
 * TODO: if these end up becoming contended cache lines, move this to
 * per_cpu_info. */
uintptr_t core_stacktops[MAX_NUM_CPUS] = {0xcafebabe, 0};

void
advance_pc(trapframe_t* state)
{
	state->epc += 4;
}

/* Set stacktop for the current core to be the stack the kernel will start on
 * when trapping/interrupting from userspace */
void set_stack_top(uintptr_t stacktop)
{
	core_stacktops[core_id()] = stacktop;
}

/* Note the assertion assumes we are in the top page of the stack. */
uintptr_t get_stack_top(void)
{
	register uintptr_t sp asm ("sp");
	uintptr_t stacktop = core_stacktops[core_id()];
	assert(ROUNDUP(sp, PGSIZE) == stacktop);
	return stacktop;
}

void
idt_init(void)
{
}

void
sysenter_init(void)
{
}

/* Helper.  For now, this copies out the TF to pcpui, and sets cur_tf to point
 * to it. */
static void
set_current_tf(struct per_cpu_info *pcpui, struct trapframe *tf)
{
	if (irq_is_enabled())
		warn("Turn off IRQs until cur_tf is set!");
	assert(!pcpui->cur_tf);
	pcpui->actual_tf = *tf;
	pcpui->cur_tf = &pcpui->actual_tf;
}

static int
format_trapframe(trapframe_t *tf, char* buf, int bufsz)
{
	// slightly hackish way to read out the instruction that faulted.
	// not guaranteed to be right 100% of the time
	uint32_t insn;
	if(!(current && !memcpy_from_user(current,&insn,(void*)tf->epc,4)))
		insn = -1;

	int len = snprintf(buf,bufsz,"TRAP frame at %p on core %d\n",
	                   tf, core_id());
	static const char* regnames[] = {
	  "z ", "ra", "v0", "v1", "a0", "a1", "a2", "a3",
	  "a4", "a5", "a6", "a7", "t0", "t1", "t2", "t3",
	  "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3",
	  "s4", "s5", "s6", "s7", "s8", "fp", "sp", "tp"
	};
	
	tf->gpr[0] = 0;
	
	for(int i = 0; i < 32; i+=4)
	{
		for(int j = 0; j < 4; j++)
			len += snprintf(buf+len, bufsz-len,
			                "%s %016lx%c", regnames[i+j], tf->gpr[i+j], 
			                j < 3 ? ' ' : '\n');
	}
	len += snprintf(buf+len, bufsz-len,
	                "sr %016lx pc %016lx va %016lx insn       %08x\n",
					tf->sr, tf->epc, tf->badvaddr, insn);

	buf[bufsz-1] = 0;
	return len;
}

void
print_trapframe(trapframe_t* tf)
{
	char buf[1024];
	int len = format_trapframe(tf,buf,sizeof(buf));
	cputbuf(buf,len);
}
static void exit_halt_loop(trapframe_t* tf)
{
	extern char after_cpu_halt;
	if ((char*)tf->epc >= (char*)&cpu_halt && (char*)tf->epc < &after_cpu_halt)
		tf->epc = tf->gpr[1];
}

/* Assumes that any IPI you get is really a kernel message */
static void
handle_ipi(trapframe_t* tf)
{
	clear_ipi();
	poll_keyboard(); // keypresses can trigger IPIs

	if (!in_kernel(tf))
		set_current_tf(&per_cpu_info[core_id()], tf);
	else
		exit_halt_loop(tf);

	handle_kmsg_ipi(tf, 0);
}

static void
unhandled_trap(trapframe_t* state, const char* name)
{
	static spinlock_t screwup_lock = SPINLOCK_INITIALIZER;
	spin_lock(&screwup_lock);

	if(in_kernel(state))
	{
		print_trapframe(state);
		panic("Unhandled trap in kernel!\nTrap type: %s", name);
	}
	else
	{
		char tf_buf[1024];
		format_trapframe(state, tf_buf, sizeof(tf_buf));

		warn("Unhandled trap in user!\nTrap type: %s\n%s", name, tf_buf);
		backtrace();
		spin_unlock(&screwup_lock);

		assert(current);
		enable_irq();
		proc_destroy(current);
	}
}

static void
handle_timer_interrupt(trapframe_t* tf)
{
	if (!in_kernel(tf))
		set_current_tf(&per_cpu_info[core_id()], tf);
	else
		exit_halt_loop(tf);
	
	timer_interrupt(tf, NULL);
}

static void
handle_misaligned_fetch(trapframe_t* state)
{
	unhandled_trap(state, "Misaligned Fetch");
}

static void
handle_misaligned_load(trapframe_t* state)
{
	unhandled_trap(state, "Misaligned Load");
}

static void
handle_misaligned_store(trapframe_t* state)
{
	unhandled_trap(state, "Misaligned Store");
}

static void
handle_fault_fetch(trapframe_t* state)
{
	if(in_kernel(state))
	{
		print_trapframe(state);
		panic("Instruction Page Fault in the Kernel at %p!", state->epc);
	}

	set_current_tf(&per_cpu_info[core_id()], state);

	if(handle_page_fault(current, state->epc, PROT_EXEC))
		unhandled_trap(state, "Instruction Page Fault");
}

static void
handle_fault_load(trapframe_t* state)
{
	if(in_kernel(state))
	{
		print_trapframe(state);
		panic("Load Page Fault in the Kernel at %p!", state->badvaddr);
	}

	set_current_tf(&per_cpu_info[core_id()], state);

	if(handle_page_fault(current, state->badvaddr, PROT_READ))
		unhandled_trap(state, "Load Page Fault");
}

static void
handle_fault_store(trapframe_t* state)
{
	if(in_kernel(state))
	{
		print_trapframe(state);
		panic("Store Page Fault in the Kernel at %p!", state->badvaddr);
	}
	
	set_current_tf(&per_cpu_info[core_id()], state);

	if(handle_page_fault(current, state->badvaddr, PROT_WRITE))
		unhandled_trap(state, "Store Page Fault");
}

static void
handle_illegal_instruction(trapframe_t* state)
{
	assert(!in_kernel(state));

	// XXX for noFP demo purposes we're ignoring illegal insts in the user.
	advance_pc(state);
	env_pop_tf(state); /* We didn't save our TF, so don't use proc_restartcore */

	struct per_cpu_info *pcpui = &per_cpu_info[core_id()];
	set_current_tf(pcpui, state);
	if (emulate_fpu(state) == 0)
	{
		advance_pc(pcpui->cur_tf);
		return;
	}

	unhandled_trap(state, "Illegal Instruction");
}

static void
handle_fp_disabled(trapframe_t* tf)
{
	if(in_kernel(tf))
		panic("kernel executed an FP instruction!");

	tf->sr |= SR_EF;
	env_pop_tf(tf); /* We didn't save our TF, so don't use proc_restartcore */
}

static void
handle_syscall(trapframe_t* state)
{
	uintptr_t a0 = state->gpr[4];
	uintptr_t a1 = state->gpr[5];

	advance_pc(state);
	set_current_tf(&per_cpu_info[core_id()], state);
	enable_irq();
	prep_syscalls(current, (struct syscall*)a0, a1);
}

static void
handle_breakpoint(trapframe_t* state)
{
	advance_pc(state);
	monitor(state);
}

void
handle_trap(trapframe_t* tf)
{
	static void (*const trap_handlers[])(trapframe_t*) = {
	  [CAUSE_MISALIGNED_FETCH] = handle_misaligned_fetch,
	  [CAUSE_FAULT_FETCH] = handle_fault_fetch,
	  [CAUSE_ILLEGAL_INSTRUCTION] = handle_illegal_instruction,
	  [CAUSE_PRIVILEGED_INSTRUCTION] = handle_illegal_instruction,
	  [CAUSE_FP_DISABLED] = handle_fp_disabled,
	  [CAUSE_SYSCALL] = handle_syscall,
	  [CAUSE_BREAKPOINT] = handle_breakpoint,
	  [CAUSE_MISALIGNED_LOAD] = handle_misaligned_load,
	  [CAUSE_MISALIGNED_STORE] = handle_misaligned_store,
	  [CAUSE_FAULT_LOAD] = handle_fault_load,
	  [CAUSE_FAULT_STORE] = handle_fault_store,
	};

	static void (*const irq_handlers[])(trapframe_t*) = {
	  [IRQ_TIMER] = handle_timer_interrupt,
	  [IRQ_IPI] = handle_ipi,
	};
	
	struct per_cpu_info *pcpui = &per_cpu_info[core_id()];
	if (tf->cause < 0)
	{
		uint8_t irq = tf->cause;
		assert(irq < sizeof(irq_handlers)/sizeof(irq_handlers[0]) &&
		       irq_handlers[irq]);
		inc_irq_depth(pcpui);
		irq_handlers[irq](tf);
		dec_irq_depth(pcpui);
	}
	else
	{
		assert(tf->cause < sizeof(trap_handlers)/sizeof(trap_handlers[0]) &&
		       trap_handlers[tf->cause]);
		if (in_kernel(tf)) {
			inc_ktrap_depth(pcpui);
			trap_handlers[tf->cause](tf);
			dec_ktrap_depth(pcpui);
		} else {
			trap_handlers[tf->cause](tf);
		}
	}
	
	/* Return to the current process, which should be runnable.  If we're the
	 * kernel, we should just return naturally.  Note that current and tf need
	 * to still be okay (might not be after blocking) */
	if (in_kernel(tf))
		env_pop_tf(tf);
	else
		proc_restartcore();
}

/* We don't have NMIs now. */
void send_nmi(uint32_t os_coreid)
{
}
