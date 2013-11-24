.set STACK_SIZE,	0x4000

# Multiboot compliant headers
# Necessary to be bootable by GRUB
.set MAGIC,	0x1BADB002	#Magic number

# Flags options
.set ALIGN,	1<<0		#Bit0=1 : Boot modules must be page-aligned
.set MEMINFO,	1<<1		#Bit1=1 : Send memory information through the
				#multiboot information structure (EBX)
.set FLAGS,	ALIGN | MEMINFO

.set CHECKSUM,	-(MAGIC + FLAGS)

# Multiboot section
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Init stack
.section .bootstrap_stack
stack_bottom:
.skip STACK_SIZE
.global stack_top
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
	pushl %eax
	call kernel_main
	popl %eax
	cli
	hlt

# Infinite loop
.Lhang:
	jmp .Lhang

.size _start, . - _start

.extern gp
.globl gdt_flush
.type gdt_flush, @function
gdt_flush:
	lgdt gp
	movw %ax, 0x10
	movw %ds, %ax
	movw %es, %ax
	movw %fs, %ax
	movw %gs, %ax
	movw %ss, %ax
	ljmp $0x08,$flush2
flush2:
	ret

.extern idtp
.globl idt_load
.type idt_load, @function
idt_load:
	lidt idtp
	ret

# ISR

.globl isr0
.globl isr1
.globl isr2
.globl isr3
.globl isr4
.globl isr5
.globl isr6
.globl isr7
.globl isr8
.globl isr9
.globl isr10
.globl isr11
.globl isr12
.globl isr13
.globl isr14
.globl isr15
.globl isr16
.globl isr17
.globl isr18
.globl isr19
.globl isr20
.globl isr21
.globl isr22
.globl isr23
.globl isr24
.globl isr25
.globl isr26
.globl isr27
.globl isr28
.globl isr29
.globl isr30
.globl isr31

# Divide by zero
isr0:
	cli
	push $0
	push $0
	jmp isr_common_stub
	
# Debug exception
isr1:
	cli
	push $0
	push $1
	jmp isr_common_stub
	
# Non maskbale interrup exception
isr2:
	cli
	push $0
	push $2
	jmp isr_common_stub
	
	
# Breakpoint exception
isr3:
	cli
	push $0
	push $3
	jmp isr_common_stub


# Into Detected Overflow Exception
isr4:
	cli
	push $0
	push $4
	jmp isr_common_stub

# Out of bounds exception
isr5:
	cli
	push $0
	push $5
	jmp isr_common_stub

# Invalid opcode exception
isr6:
	cli
	push $0
	push $6
	jmp isr_common_stub

# No coprocessor Exception
isr7:
	cli
	push $0
	push $7
	jmp isr_common_stub

# Double fault exception
isr8:
	cli
	push $8
	jmp isr_common_stub

# Coprocessor segment overrun exception
isr9:
	cli
	push $0
	push $9
	jmp isr_common_stub

# Bad TSS Exception
isr10:
	cli
	push $10
	jmp isr_common_stub

# Segment not present exception
isr11:
	cli
	push $11
	jmp isr_common_stub

# Stack fault exception
isr12:
	cli
	push $12
	jmp isr_common_stub

# General protecton fault exception
isr13:
	cli
	push $13
	jmp isr_common_stub

# Page fault exception
isr14:
	cli
	push $14
	jmp isr_common_stub

# Unknown interrupt exception
isr15:
	cli
	push $0
	push $15
	jmp isr_common_stub

# Coprocessor fault exception
isr16:
	cli
	push $0
	push $16
	jmp isr_common_stub

# Alignement check exception
isr17:
	cli
	push $0
	push $17
	jmp isr_common_stub

# Machine check exception
isr18:
	cli
	push $0
	push $18
	jmp isr_common_stub

# Reserved exception (19-31)
isr19:
	cli
	push $0
	push $19
	jmp isr_common_stub

isr20:
	cli
	push $0
	push $20
	jmp isr_common_stub

isr21:
	cli
	push $0
	push $21
	jmp isr_common_stub

isr22:
	cli
	push $0
	push $22
	jmp isr_common_stub

isr23:
	cli
	push $0
	push $23
	jmp isr_common_stub

isr24:
	cli
	push $0
	push $24
	jmp isr_common_stub

isr25:
	cli
	push $0
	push $25
	jmp isr_common_stub

isr26:
	cli
	push $0
	push $26
	jmp isr_common_stub

isr27:
	cli
	push $0
	push $27
	jmp isr_common_stub

isr28:
	cli
	push $0
	push $28
	jmp isr_common_stub

isr29:
	cli
	push $0
	push $29
	jmp isr_common_stub

isr30:
	cli
	push $0
	push $30
	jmp isr_common_stub

isr31:
	cli
	push $0
	push $31
	jmp isr_common_stub



.extern fault_handler

isr_common_stub:
    pusha
    pushw %ds
    pushw %es
    pushw %fs
    pushw %gs
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movl %eax, %esp
    pushl %eax
    call fault_handler
    popl %eax
    popw %gs
    popw %fs
    popw %es
    popw %ds
    popa
    addl $8, %esp
    iret
