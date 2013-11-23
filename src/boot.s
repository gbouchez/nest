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
