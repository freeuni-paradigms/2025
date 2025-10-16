main:
	ADDI sp sp -4
	LI x10 3
	SW x10 0(sp)
	ADDI sp sp -4
	SW ra 0(sp)
	CALL fact
	LW ra 0(sp)
	ADDI sp sp 8
	MV x11 x10
	LI x10 1
	ECALL
	LI x10 10
	ECALL


fact:
	LW x10 4(sp)
	BNE x10 x0 not_zero
	LI x10 1
	RET
not_zero:
	LW x11 4(sp)
	ADDI x11 x11 -1
	ADDI sp sp -4
	LW x11 0(sp)
	ADDI sp sp -4
	SW ra 0(sp)
	CALL fact
	LW ra 0(sp)
	ADDI sp sp 8
	LW x11 4(sp)
	MUL x10 x10 x11
	RET
