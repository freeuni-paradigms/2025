.text
	call main

# int max(int a) {
#   short x = a;
#   short y = *(((short*)&a) + 1);
#   if (x > y) {
# 	    return x;
#   } else {
# 	    return y;
#   }
# }
max:
    addi sp, sp, -4
    
    # short x = a;
    lw a0, 4(sp)        # a
    sh a0, 2(sp)        # x = a

    # short y = *(((short*)&a) + 1);
    addi t0, sp, 4      # &a
    addi t0, t0, 2      # ((short*)&a) + 1
    lh t0, 0(t0)        # *(((short*)&a) + 1)
    sh t0, 0(sp)        # y = ...

    # if (x > y) return x;
    lh t0, 2(sp)        # x
    lh t1, 0(sp)        # y
    bgt t0, t1, x_greater 

        # return y
        mv a0, t1
        j return

    x_greater:
        # return x
        mv a0, t0

    return:
    addi sp, sp, 4
	ret

# typedef struct {
#   double d;       # 8 bytes           - offset 0
#   char c[4];      # 4 bytes (4 * 1)   - offset 8
#   int i;          # 4 bytes           - offset 12
    # } Work;       # 16 bytes
# 
# typedef int(*TransformFN)(int);
#
# int process(int n, Work* w, TransformFN tfn) {
#   int ret = 0;
#   int i = 0;
#   while (i < n) {
# 	    ret += tfn(*(int*)((short*)w[i].c + 1));
# 	    i += 2;
#   }
#   return ret;
# }
process:
    addi sp, sp, -12
    sw ra, 8(sp)
    sw zero, 4(sp)              # ret
    sw zero, 0(sp)              # i

    # while (i < n)
    start_while:
        lw t0, 0(sp)            # i
        lw a0, 12(sp)           # n
        bge t0, a0, end_while   # if (i >= n) break;

        # ret += tfn(*(int*)((short*)w[i].c + 1));
        lw a1, 16(sp)           # w
        slli t0, t0, 4          # i * 16 for pointer arithmetic on Work *
        add t1, a1, t0          # t1 = &(w[i])
        addi t1, t1, 8          # w[i].c
        addi t1, t1, 2          # ((short*)w[i].c + 1) pointer arithmetic on short *
        lw t1, 0(t1)            # tfn argument
        
        lw a2, 20(sp)           # tfn
        addi sp, sp, -4
        sw t1, 0(sp)            # function argument
        jalr a2
        addi sp, sp, 4

        lw t0, 4(sp)            # ret
        add t0, t0, a0          # ret += tfn return value (register)
        sw t0, 4(sp)            # ret += tfn return value (stack)

        # i += 2
        lw t0, 0(sp)            # i
        addi t0, t0, 2          # i += 2 (register)
        sw t0, 0(sp)            # i += 2 (stack)
        
        j start_while

    end_while:
    lw a0, 4(sp)

    lw ra, 8(sp)
    addi sp, sp, 12
	ret

run_test_max:
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
copy_max:
	beq a2, a0, call_func_max
	lw a4, 0(a1)
	sw a4, 0(a3)
	addi a1, a1, 4
	addi a3, a3, 4
	addi a2, a2, 4
	j copy_max
call_func_max:
	call max
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
	li a1, 1287
	li a2, 84345604
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	call run_test_max
	lw ra, 0(sp)
	addi sp, sp, 16
	ret

CONST:
	li a0, 2
	ret

INPOUT:
	lw a0, 0(sp)
	ret

TEST_2:
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
	la a0, TEST_2_NAME
	li a1, 4
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

TEST_3:
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
	la a0, TEST_3_NAME
	li a1, 134743558
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
