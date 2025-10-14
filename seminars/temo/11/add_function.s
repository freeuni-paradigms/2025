.text

main:

# grow stack
addi sp, sp, -8

# store one
li x10, 40
sw x10, 0(sp)

# store two
li x10, 60
sw x10, 4(sp)

call add

addi sp, sp, 8

li x10, 1
ecall

li x10, 10
ecall


add:

addi sp, sp, -12

# load one to x10
lw, x10, 12(sp)
# load two to x11
lw, x11, 16(sp)
# sum of x10 and x11
add x11, x10, x11
# store sum in sum
sw x11, 0(sp)

addi sp, sp, 12

ret
