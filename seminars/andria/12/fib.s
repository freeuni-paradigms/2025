
.globl _main

# int main() {
#   print_int(fib(7));
#   return 0;
# }
_main:
    # a0 = fib(7)
    li a0, 7
    call fib
    
    # a1 = a0
    # print_int(a1)
    mv a1, a0
    li a0, 1
    ecall

    # exit(0)  -  return 0;
    li a0, 10
    ecall

# int fib(int n) {
#   if (n < 1) return 0;
#   if (n == 1) return 1;
#   return fib(n - 1) + fib(n - 2);
# }
fib:
    # prefix
    addi sp, sp, -4
    sw ra, 0(sp)

    # if (n < 1) return 0;
    bgt a0, zero, else_one
        mv a0, zero
        j exit

    # if (n == 1) return 1;
    else_one:
    li t0, 1
    beq a0, t0, exit
        
    # t1 = fib(n - 1)
    addi sp, sp, -4
    sw a0, 0(sp)

    addi a0, a0, -1
    call fib
    mv t1, a0

    lw a0, 0(sp)
    addi sp, sp, 4

    # t2 = fib(n - 2)
    addi sp, sp, -8
    sw a0, 0(sp)
    sw t1, 4(sp)

    addi a0, a0, -2
    call fib
    mv t2, a0

    lw t1, 4(sp)
    lw a0, 0(sp)
    addi sp, sp, 8

    # a0 = t1 + t2
    add a0, t1, t2
    
    exit:
    #suffix
    lw ra, 0(sp)
    addi sp, sp, 4

    ret

