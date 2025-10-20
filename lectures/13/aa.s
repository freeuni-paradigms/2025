mv x11 PC
li x10 1
ecall

	li x11 20
	addi x10 pc 20
	beq x0 x11 x10
lui x11 1
li x10 1
ecall
li x11 1
li x10 1
ecall
