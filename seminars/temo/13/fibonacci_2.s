## int fibonacci (int i) {
##   if (i <= 1) return i;
##   int fib1 = fibonacci(i - 1);
##   int fib2 = fibonacci(i - 2);
## 
##   return fib1 + fib2;
## }
# 0 1 1 2 3 5 8 13
# 

.text

main:

addi sp, sp, -4
li x10, 7
sw x10, 0(sp)

addi sp, sp, -4
sw x1, 0(sp)
call fibonacci
lw x1, 0(sp)

addi sp, sp, 8

mv x11, x10
li x10, 1
ecall

li x10, 10
ecall

fibonacci:
addi sp, sp, -8
lw x10, 12(sp)
li x11, 1

bgt x10, x11, recursion

# base case, return i
addi sp, sp, 8

ret

recursion:

# load i in x10
lw x10, 12(sp)
addi x10, x10, -1

addi sp, sp, -4
sw x10, 0(sp)

addi sp, sp, -4
sw x1, 0(sp)
call fibonacci
lw x1, 0(sp)

addi sp, sp, 8

# store return value in fib1
sw x10, 4(sp)

# load i in x10
lw x10, 12(sp)
addi x10, x10, -2

addi sp, sp, -4
sw x10, 0(sp)

addi sp, sp, -4
sw x1, 0(sp)
call fibonacci
lw x1, 0(sp)

addi sp, sp, 8

# store return value in fib2
sw x10, 0(sp)

# load fib2 in x10
lw x10, 0(sp)
# load fib1 in x11
lw x11, 4(sp)
add x10, x10, x11

addi sp, sp, 8
ret

## int fibonacci (int i) {
##   if (i <= 1) return i;
##   int fib1 = fibonacci(i - 1);
##   int fib2 = fibonacci(i - 2);
## 
##   return fib1 + fib2;
## }
