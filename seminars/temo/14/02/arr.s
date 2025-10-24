# int main() {
#   short scores[4];
#   Banana(scores, 2);
# }

# static void Banana(short scores[], int n) {
#   scores[n] = 10;
# }

# s
# s
# s
# s

main:

addi sp, sp, -8
sh x0, 4(sp)

lh x11, 4(sp)
li x10, 1
ecall

# store array address in x12
mv x12, sp

# n
# scores
addi sp, sp, -8
# store 2 in n
li x10, 2
sw x10, 4(sp)
# store scores address in scores
sw x12, 0(sp)

# saved pc
addi sp, sp, -4
sw ra, 0(sp)
call banana
lw x1, 0(sp)
addi sp, sp, 12

lh x11, 4(sp)
li x10, 1
ecall

addi sp, sp, 8

li x10, 10
ecall

# n
# scores
# saved pc

banana:

# load scores in x10
lw x10, 4(sp)

# load n in x11
lw x11, 8(sp)

# load 10 in x12
li x12, 10

li x13, 2
mul x13, x11, x13

# scores[n] == scores + n == (char *) scores + n * sizeof(short)

# store 10 in scores n-th element
add x13, x10, x13
sw x12, 0(x13)

ret
