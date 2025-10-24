 # typedef int (*compareFn)(const void *, const void *);

 # static bool AreEqual(const void *a, const void *b, compareFn cmp) {
 # if (cmp(a, b) == 0)
 #  return true;
 #   else
 #  return false;
 # }

# cmp
# b
# a
# saved pc
main:
addi sp, sp, -12
# cmp
# b
# a
la x10, cmp
sw x10, 8(sp)

addi sp, sp, -4
sw x1, 0(sp)
call are_equal
lw x1, 0(sp)
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
# load b
lw x11, 8(sp)
# load a
lw x12, 4(sp)

# b
# a
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
mv x10, x0
ret


.data

msg:
.asciiz "test\n"
