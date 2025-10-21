# int fibonacci(int i) {
#  if (i <= 1) {
#    return i;
#  }  
#  int i1 = fibonacci(i - 1);
#  int i2 = fibonacci(i - 2);
#  return i1 + i2;
#}

.text

main:
  
addi sp, sp, -4

li x10, 6
sw x10, 0(sp)

addi sp, sp, -4
sw x1, 0(sp)
call fibonacci
lw x1, 0(sp)
addi sp, sp, 8

mv x10, x11
li x10, 1
ecall

li x10, 10
ecall

# int fibonacci(int i) {
#  if (i <= 1) {
#    return i;
#  }
#  int i1 = fibonacci(i - 1);
#  int i2 = fibonacci(i - 2);
#  return i1 + i2;
# }
fibonacci:

# if (i <= 1)
addi sp, sp, -8
lw x10, 12(sp)
li x11, 1
bgt x10, x11, recursion


addi sp, sp, 8
ret

recursion:
# fibonacci(i - 1)
lw x10, 12(sp)
addi sp, sp, -4
addi x10, x10, -1
sw x10, 0(sp)

addi sp, sp, -4
sw ra, 0(sp)
call fibonacci
lw ra, 0(sp) # ra==x1
addi sp, sp, 8

# i1 = fibonacci(i - 1)
sw x10, 4(sp)

# int i2 = fibonacci(i - 2)
lw x10, 12(sp)
addi sp, sp, -4
addi x10, x10, -2
sw x10, 0(sp)

addi sp, sp, -4
sw ra, 0(sp)
call fibonacci
lw ra, 0(sp)
addi sp, sp, 8

sw x10, 0(sp)

lw x10, 0(sp)
lw x11, 4(sp)

add x10, x10, x11

addi sp, sp, 8
ret


#int fibonacci(int i) {
#  if (i <= 1) {
#    return i;
#  }  
#  int i1 = fibonacci(i - 1);
#  int i2 = fibonacci(i - 2);
#  return i1 + i2;
# }
