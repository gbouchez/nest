.global test
.type test, @function
test:
	movl $stack_top, %esp
        call kernel_main
        cli
        hlt

.Lhang:
        jmp .Lhang

