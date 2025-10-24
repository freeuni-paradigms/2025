# typedef int (*compareFn)(const void *, const void *);
# 
# static bool AreEqual(const void *a, const void *b, compareFn cmp) {
#  if (cmp(a, b) == 0)
#   return true;
#  else
#   return false;
# }

# b
# a
# saved pc
## compareFn

# cmp
# b
# a
# saved pc

main: 
addi sp, sp, -12
# store <cmp> in 8(sp)
la x10, cmp
sw x10, 8(sp)

addi sp, sp, -4
sw ra, 0(sp)

call are_equal

lw ra, 0(sp)
addi sp, sp, 16

li x10, 10
ecall

cmp:

li x10, 4
la x11, msg
ecall

li x10, 1
ret

are_equal:

# load cmp in x10
lw x10, 12(sp)
# load b in x11
lw x11, 8(sp)
# load a in x12
lw x12, 4(sp)

# b
# a
## saved pc
## compareFn

addi sp, sp, -8
sw x12, 0(sp)
sw x11, 4(sp)

addi sp, sp, -4
sw ra, 0(sp)

jalr ra, x10, 0

lw ra, 0(sp)
addi sp, sp, 12

bne x10, x0, not_equals
li x10, 1
ret
not_equals:
li x10, 0
ret

.data

msg:
  .asciiz "test\n"
