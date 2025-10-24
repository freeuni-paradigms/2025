# int main() {
#   short scores[4];
#   Banana(scores, 3);
# }

# static void Banana(short scores[], int n) {
#    scores[n] = 10;
# }

# s
# s
# s
# s

# n
# scores
# saved pc
main:

addi sp, sp, -8
li x10, 7
sh x10, 6(sp)

lh x11, 6(sp)
li x10, 1
ecall

mv x11, sp

addi sp, sp, -8
# write sth on stack

# store 3 in n
li x10, 3
sw x10, 4(sp)

sw x11, 0(sp)

addi sp, sp, -4
sw ra, 0(sp)
call banana
lw ra, 0(sp)

addi sp, sp, 12

lh x11, 6(sp)
li x10, 1
ecall

addi sp, sp, 8

li x10, 10
ecall

banana:

# load n in x10
lw x10, 8(sp)
# load scores in x11
lw x11, 4(sp)

# scores[n] == (char *)scores + n * sizeof(short)
li x12, 2
# store n * 2 in x12
mul x12, x10, x12

# store scores + n * 2 in x12
add x12, x11, x12

# store 10 in x13
li x13, 10

# store x13 in x12 address
sh x13, 0(x12)

ret
