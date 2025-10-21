.text

main:

addi sp, sp, -4

sw x1, 0(sp)
call apple
lw x1, 0(sp)
addi sp, sp, 4

li x10, 10
ecall

apple:

addi sp, sp, -12

li x11, 2
sh x11, 0(sp)
sh x11, 2(sp)
sh x11, 4(sp)
sh x11, 6(sp)

# store 1 in i
li x10, 1
sw x10, 8(sp)

# load i in x10
lw x10, 8(sp)

li x11, 2
mul x10, x10, x11
add x10, x10, sp

li x11, 10
sh x11, 0(x10)

lh x11, 2(sp)
li x10, 1
ecall

lh x11, 0(sp)
li x10, 1
ecall

lh x11, 4(sp)
li x10, 1
ecall

lh x11, 6(sp)
li x10, 1
ecall

li x11, 10
sb, x11, 0(sp)
sb, x0, 1(sp)

# prints newline
li x10, 4
mv x11, x2
ecall

addi sp, sp, 12
ret


