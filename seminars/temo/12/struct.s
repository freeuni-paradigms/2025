.text

main:

addi sp, sp, -12
# write some values

sw x0, 4(sp)
sw x0, 8(sp)

sw x1, 0(sp)

call binky

lw x1, 0(sp)

lw x11, 4(sp)
li x10, 1
ecall

lw x11, 8(sp)
ecall

addi sp, sp, 12

li x10, 10
ecall


binky:

addi sp, sp, -8

# store 1 in local.denominator
li x10, 1
sw x10, 4(sp)

# store 2 in param.denominator
li x10, 2
sw x10, 16(sp)

addi sp, sp, 8

ret

