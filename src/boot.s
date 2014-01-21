[BITS 32]
global start
start:
	mov esp, stack_top
	jmp main_loop

ALIGN 4

; Multiboot compliant headers
; Necessary to be bootable by GRUB
multiboot:	
; Flags options
MB_PAGE_ALIGN	equ (1<<0)			;Bit0=1 :	Boot modules must be page-aligned
MB_MEMINFO 		equ (1<<1)			;Bit1=1 :	Send memory information through the
									;			multiboot information structure (EBX)

MB_MAGIC_NUMBER equ 0x1BADB002		;Magic number
MB_FLAGS		equ (MB_PAGE_ALIGN | MB_MEMINFO)
MB_CHECKSUM equ -(MB_MAGIC_NUMBER + MB_FLAGS)

dd    MB_MAGIC_NUMBER
dd    MB_FLAGS
dd    MB_CHECKSUM

SECTION  .text
GLOBAL main_loop
EXTERN kernel_main
main_loop:
        mov		esp, stack_top
        push	eax
        call	kernel_main
        pop		eax
        cli
        hlt

; Infinite loop
.Lhang: 
        jmp .Lhang

; Init stack
STACK_SIZE equ 04000h
SECTION .bootstrap_stack
stack_bottom: 
resb STACK_SIZE
GLOBAL stack_top
stack_top: 

EXTERN  gp
GLOBAL gdt_flush
GLOBAL gdt_flush:function
gdt_flush:
		LGDT [gp]
        mov  ax, 0x10
        mov  ds, ax
        mov  es, ax
        mov  fs, ax
        mov  gs, ax
        mov  ss, ax
        jmp  0x08:flush2
flush2: 
        ret

EXTERN  idtp
GLOBAL idt_load:function
GLOBAL idt_load
idt_load: 
		LIDT [idtp]
        ret

; ISR

GLOBAL isr0
GLOBAL isr1
GLOBAL isr2
GLOBAL isr3
GLOBAL isr4
GLOBAL isr5
GLOBAL isr6
GLOBAL isr7
GLOBAL isr8
GLOBAL isr9
GLOBAL isr10
GLOBAL isr11
GLOBAL isr12
GLOBAL isr13
GLOBAL isr14
GLOBAL isr15
GLOBAL isr16
GLOBAL isr17
GLOBAL isr18
GLOBAL isr19
GLOBAL isr20
GLOBAL isr21
GLOBAL isr22
GLOBAL isr23
GLOBAL isr24
GLOBAL isr25
GLOBAL isr26
GLOBAL isr27
GLOBAL isr28
GLOBAL isr29
GLOBAL isr30
GLOBAL isr31

; Divide by zero
isr0: 
        cli
		push byte 0
		push byte 0
        jmp isr_common_stub

; Debug exception
isr1: 
        cli
        push byte 0
        push byte 1
        jmp isr_common_stub

; Non maskbale interrup exception
isr2: 
        cli
        push byte 0
        push byte 2
        jmp isr_common_stub


; Breakpoint exception
isr3: 
        cli
        push byte 0
        push byte 3
        jmp isr_common_stub


; Into Detected Overflow Exception
isr4: 
        cli
        push byte 0
        push byte 4
        jmp isr_common_stub

; Out of bounds exception
isr5: 
        cli
        push byte 0
        push byte 5
        jmp isr_common_stub

; Invalid opcode exception
isr6: 
        cli
        push byte 0
        push byte 6
        jmp isr_common_stub

; No coprocessor Exception
isr7: 
        cli
        push byte 0
        push byte 7
        jmp isr_common_stub

; Double fault exception
isr8: 
        cli
        push byte 8
        jmp isr_common_stub

; Coprocessor segment overrun exception
isr9: 
        cli
        push byte 0
        push byte 9
        jmp isr_common_stub

; Bad TSS Exception
isr10: 
        cli
        push byte 10
        jmp isr_common_stub

; Segment not present exception
isr11: 
        cli
        push byte 11
        jmp isr_common_stub

; Stack fault exception
isr12: 
        cli
        push byte 12
        jmp isr_common_stub

; General protecton fault exception
isr13: 
        cli
        push byte 13
        jmp isr_common_stub

; Page fault exception
isr14: 
        cli
        push byte 14
        jmp isr_common_stub

; Unknown interrupt exception
isr15: 
        cli
        push byte 0
        push byte 15
        jmp isr_common_stub

; Coprocessor fault exception
isr16: 
        cli
        push byte 0
        push byte 16
        jmp isr_common_stub

; Alignement check exception
isr17: 
        cli
        push byte 0
        push byte 17
        jmp isr_common_stub

; Machine check exception
isr18: 
        cli
        push byte 0
        push byte 18
        jmp isr_common_stub

; Reserved exception (19-31)
isr19: 
        cli
        push byte 0
        push byte 19
        jmp isr_common_stub

isr20: 
        cli
        push byte 0
        push byte 20
        jmp isr_common_stub

isr21: 
        cli
        push byte 0
        push byte 21
        jmp isr_common_stub

isr22: 
        cli
        push byte 0
        push byte 22
        jmp isr_common_stub

isr23: 
        cli
        push byte 0
        push byte 23
        jmp isr_common_stub

isr24: 
        cli
        push byte 0
        push byte 24
        jmp isr_common_stub

isr25: 
        cli
        push byte 0
        push byte 25
        jmp isr_common_stub

isr26: 
        cli
        push byte 0
        push byte 26
        jmp isr_common_stub

isr27: 
        cli
        push byte 0
        push byte 27
        jmp isr_common_stub

isr28: 
        cli
        push byte 0
        push byte 28
        jmp isr_common_stub

isr29: 
        cli
        push byte 0
        push byte 29
        jmp isr_common_stub

isr30: 
        cli
        push byte 0
        push byte 30
        jmp isr_common_stub

isr31: 
        cli
        push byte 0
        push byte 31
        jmp isr_common_stub



EXTERN fault_handler

isr_common_stub: 
    pusha
    push  ds
    push  es
    push  fs
    push  gs
    mov  ax,0x10
    mov  ds,ax
    mov  es,ax
    mov  fs,ax
    mov  gs,ax
    mov  eax,esp
    push  eax
    mov eax, fault_handler
    call eax
    pop  eax
    pop  gs
    pop  fs
    pop  es
    pop  ds
    popa
    add  esp,8
    iret

