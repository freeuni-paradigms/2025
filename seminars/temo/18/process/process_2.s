.text
call main

min:
ret


# typedef struct { 16 bytes
#   double d;      | 8 bytes | 0 offset
#   char c[4];     | 4 bytes | 8 offset
#   int i;         | 4 bytes |12 offset
# } Work;
# w[i].c
# &(w[i].c[0])
# 
# typedef int(*TransformFN)(int);
# 
# int process(int n, Work* w, TransformFN tfn) {
#   int ret = 0;
#   int i = 0;
#   while (true) {
# 	i += 2;
# 	if (i == n) {
# 	  break;
# 	}
# 	ret += tfn(*(int*)((short*)w[i].c + 1));
#   }
#   return ret;
# }

# TransformFn tfn | 4 bytes |16 offset
# Work         *w | 4 bytes |12 offset
# int           n | 4 bytes | 8 offset
process:
# int         ret | 4 bytes | 4 offset
# int           i | 4 bytes | 0 offset
# grow stack
addi sp, sp, -8

#   int ret = 0;
sw x0, 4(sp)

#   int i = 0;
sw x0, 0(sp)

#   while (true) {
while_start:
# 	i += 2;
# load i in x10
lw x10, 0(sp)
addi x10, x10, 2
# store x10 in i
sw x10, 0(sp)

# 	if (i >= n) {
# load n in x11
lw x11, 8(sp)
# 	  break;
bge x10, x11, while_end

# 	ret += tfn(*(int*)((short*)w[i].c + 1));
# load w in x10
lw x11, 12(sp)

# w[i] = *((char *)w + i * sizeof(Work))
# load sizeof(Work) in x13
li x13, 16
# load i * x13 in x13
mul x13, x13, x10
# load w + x13 in x13
add x13, x11, x13
# load w[i].c in x12
addi x13, x13, 8
# (short*)x13 + 1
addi x13, x13, 2
# *(int*)(w13)
lw x13, 0(x13)

# load tfn in x10
lw x10, 16(sp)

# backup saved pc
addi sp, sp, -4
sw ra, 0(sp)

# grow stack for tfn args
addi sp, sp, -4
sw x13, 0(sp)

jalr x10

# shrink stack for tfn args
addi sp, sp, 4 

lw ra, 0(sp)
addi sp, sp, 4

# 	ret += x10;
# load ret in x11
lw x11, 4(sp)
add x10, x11, x10

# store x10 on 4(sp)
sw x10, 4(sp)

#   }
j while_start

while_end:
# load ret in x10
lw x10, 4(sp)

addi sp, sp, 8
ret


run_test_min:
	# print name
	li a0, 4
	lw a1, 4(sp)
	ecall
	la a1, RUNNING
	ecall
	# backup ra
	addi sp, sp, -4
	sw ra, 0(sp)
	# allocate stack for args + ra
	li a0, 4 # args size is 4
	addi a1, sp, 16
	li a2, 0
	sub sp, sp, a0
	mv a3, sp
copy_min:
	beq a2, a0, call_func_min
	lw a4, 0(a1)
	sw a4, 0(a3)
	addi a1, a1, 4
	addi a3, a3, 4
	addi a2, a2, 4
	j copy_min
call_func_min:
	call min
	addi sp, sp, 4 # args size is 4
	lw ra, 0(sp)
	addi sp, sp, 4
	mv a2, a0
	lw a3, 8(sp)
	li a0, 4
	lw a1, 4(sp)
	ecall
	bne a2, a3, failure
	li a0, 4
	la a1, SUCCESS
	ecall
	ret

run_test_process:
	# print name
	li a0, 4
	lw a1, 4(sp)
	ecall
	la a1, RUNNING
	ecall
	# backup ra
	addi sp, sp, -4
	sw ra, 0(sp)
	# allocate stack for args + ra
	li a0, 12 # args size is 12
	addi a1, sp, 16
	li a2, 0
	sub sp, sp, a0
	mv a3, sp
copy_process:
	beq a2, a0, call_func_process
	lw a4, 0(a1)
	sw a4, 0(a3)
	addi a1, a1, 4
	addi a3, a3, 4
	addi a2, a2, 4
	j copy_process
call_func_process:
	call process
	addi sp, sp, 12 # args size is 12
	lw ra, 0(sp)
	addi sp, sp, 4
	mv a2, a0
	lw a3, 8(sp)
	li a0, 4
	lw a1, 4(sp)
	ecall
	bne a2, a3, failure
	li a0, 4
	la a1, SUCCESS
	ecall
	ret

failure:
	li a0, 4
	la a1, FAILURE
	ecall
	ret

exit:
	li a0, 10
	ecall

TEST_1:
	addi sp, sp, -16
	la a0, TEST_1_NAME
	li a1, 1
	li a2, 16777218
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	call run_test_min
	lw ra, 0(sp)
	addi sp, sp, 16
	ret

TEST_2:
	addi sp, sp, -16
	la a0, TEST_2_NAME
	li a1, 2
	li a2, 50331650
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	call run_test_min
	lw ra, 0(sp)
	addi sp, sp, 16
	ret

TEST_3:
	addi sp, sp, -16
	la a0, TEST_3_NAME
	li a1, -128
	li a2, -2146135425
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	call run_test_min
	lw ra, 0(sp)
	addi sp, sp, 16
	ret

CONST:
	li a0, 2
	ret

INPOUT:
	lw a0, 0(sp)
	ret

TEST_4:
	addi sp, sp, -60

	addi x13, sp, 0
	li x10, 9
	li x11, 1
	li x12, 2
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi x13, sp, 16
	li x10, 10
	li x11, 3
	li x12, 4
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi x13, sp, 16
	li x10, 11
	li x11, 5
	li x12, 6
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi sp, sp, -24
	la a0, TEST_4_NAME
	li a1, 2
	li a2, 3
	addi a3, sp, 24
	la a4, CONST
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	sw a3, 16(sp)
	sw a4, 20(sp)
	call run_test_process
	lw ra, 0(sp)
	addi sp, sp, 24
	addi sp, sp, 60
	ret

TEST_5:
	addi sp, sp, -60

	addi x13, sp, 0
	li x10, 9
	li x11, 1
	li x12, 2
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi x13, x13, 16
	li x10, 10
	li x11, 3
	li x12, 4
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi x13, x13, 16
	li x10, 11
	li x11, 5
	li x12, 6
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi sp, sp, -24
	la a0, TEST_5_NAME
	li a1, 101057797
	li a2, 3
	addi a3, sp, 24
	la a4, INPOUT
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	sw a3, 16(sp)
	sw a4, 20(sp)
	call run_test_process
	lw ra, 0(sp)
	addi sp, sp, 24
	addi sp, sp, 60
	ret


main:
	call TEST_1
	call TEST_2
	call TEST_3
	call TEST_4
	call TEST_5
	call exit

.data
RUNNING:
	.string "RUNNING\n"
FAILURE:
	.string "FAILURE\n\n"
SUCCESS:
	.string "SUCCESS\n\n"
TEST_1_NAME:
    .string "TEST_1: "
TEST_2_NAME:
    .string "TEST_2: "
TEST_3_NAME:
    .string "TEST_3: "
TEST_4_NAME:
    .string "TEST_4: "
TEST_5_NAME:
    .string "TEST_5: "
TEST_6_NAME:
    .string "TEST_6: "
