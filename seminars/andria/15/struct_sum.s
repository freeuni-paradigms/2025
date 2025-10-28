.text
# CALLS MAIN FUNCTION; DO NOT REMOVE
call main

##### YOUR CODE STARTS HERE ######
StructSum:

# typedef struct {
#   char c;        // 1 byte            - offset = 0
#   short s[2];    // 4 bytes (2 * 2)   - offset = 1
#   int i;         // 4 bytes           - offset = 5
# } Data;   // 9 bytes
# 
# typedef void (*PopulateFn)(int num, Data *d);
# 
# int StructSum(int num, PopulateFn popFn) {
#   Data d;
#   popFn(num, &d);
#   return d.c + d.s[0] + d.s[0] + d.s[1] + d.i;
# }
    # start of function
    addi sp, sp, -4
    sw ra, 0(sp)

    # Data d;
    addi sp, sp, -9

    # popFn(num, &d);
    lw a0, 13(sp)   # num
    mv a1, sp       # &d
    lw t0, 17(sp)   # popFn

    addi sp, sp, -8
    sw a0, 0(sp)
    sw a1, 4(sp)
    jalr t0
    addi sp, sp, 8
    
    # return d.c + d.s[0] + d.s[0] + d.s[1] + d.i;
    lb t0, 0(sp)        # d.c
    lh t1, 1(sp)        # d.s[0]
    lh t2, 3(sp)        # d.s[1]
    lw t3, 5(sp)        # d.i

    add a0, t0, t1
    add a0, a0, t1
    add a0, a0, t2
    add a0, a0, t3

    # end of function
    addi sp, sp, 9
    lw ra, 0(sp)
    addi sp, sp, 4
    ret


#######  YOUR CODE ENDS HERE  ######
TEST_FUNCTION:

### TEST CODE BELOW ###
### TEST CODE BELOW ###
### gcc generated test code. not meant to be read: ###
populate_threes:
	lw x13, 0(sp)
	lw x10, 4(sp)
	addi x11, x13, 3
	la x15, .LC6
	lb x17, 0(x15)
	add x16, x10, x17
	sb x11, 0(x16)
	lb x17, 1(x15)
	add x16, x10, x17
	sh x11, 0(x16)
	lb x17, 2(x15)
	add x16, x10, x17
	sh x11, 0(x16)
	lb x17, 3(x15)
	add x16, x10, x17
	sw x11, 0(x16)
	li x3, 0
	li x4, 0
	li x5, 0
	li x6, 0
	li x7, 0
	li x8, 0
	li x9, 0
	li x10, 0
	li x11, 0
	li x12, 0
	li x13, 0
	li x14, 0
	li x15, 0
	li x16, 0
	li x17, 0
	li x18, 0
	li x19, 0
	li x20, 0
	li x21, 0
	li x22, 0
	li x23, 0
	li x24, 0
	li x25, 0
	li x26, 0
	li x27, 0
	li x28, 0
	li x29, 0
	li x30, 0
	li x31, 0
	ret

populate_2pows:
	lw x13, 0(sp)
	lw x10, 4(sp)
	addi x11, x13, 2
	la x15, .LC6
	lb x17, 0(x15)
	add x16, x10, x17
	sb x11, 0(x16)
	addi x11, x13, 4
	lb x17, 1(x15)
	add x16, x10, x17
	sh x11, 0(x16)
	addi x11, x13, 8
	lb x17, 2(x15)
	add x16, x10, x17
	sh x11, 0(x16)
	addi x11, x13, 16
	lb x17, 3(x15)
	add x16, x10, x17
	sw x11, 0(x16)
	li x3, 0
	li x4, 0
	li x5, 0
	li x6, 0
	li x7, 0
	li x8, 0
	li x9, 0
	li x10, 0
	li x11, 0
	li x12, 0
	li x13, 0
	li x14, 0
	li x15, 0
	li x16, 0
	li x17, 0
	li x18, 0
	li x19, 0
	li x20, 0
	li x21, 0
	li x22, 0
	li x23, 0
	li x24, 0
	li x25, 0
	li x26, 0
	li x27, 0
	li x28, 0
	li x29, 0
	li x30, 0
	li x31, 0
	ret
main:
        addi    sp,sp,-64
        sw      ra,60(sp)
        sw      s0,56(sp)
        addi    s0,sp,64
        sw      a0,-52(s0)
        sw      a1,-56(s0)
        la    a1, populate_threes
        li      a0,0
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-20(s0)
        la    a5, .LC0
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-20(s0)
        addi    a5,a5,-15
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall
        la    a1, populate_threes
        li      a0,1
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-24(s0)
        la    a5, .LC1
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-24(s0)
        addi    a5,a5,-20
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall
        la    a1, populate_threes
        li      a0,-1
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-28(s0)
        la    a5, .LC2
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-28(s0)
        addi    a5,a5,-10
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall
        la    a1, populate_2pows
        li      a0,0
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-32(s0)
        la    a5, .LC3
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-32(s0)
        addi    a5,a5,-34
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall
        la    a1, populate_2pows
        li      a0,1
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-36(s0)
        la    a5, .LC4
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-36(s0)
        addi    a5,a5,-39
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall
        la    a1, populate_2pows
        li      a0,-1
		  addi sp, sp, -8
		  sw a0, 0(sp)
		  sw a1, 4(sp)
        call    StructSum
		  addi sp, sp, 8
        sw      a0,-40(s0)
        la    a5, .LC5
        mv      a1,a5
        li      a0,4
        ecall
        lw      a5,-40(s0)
        addi    a5,a5,-29
        seqz    a5,a5
        andi    a5,a5,0xff
        mv      a1,a5
        li      a0,1
        ecall
        li      a1,10
        li      a0,11
        ecall
        li      a5,0
        mv      a0,a5
        lw      ra,60(sp)
        lw      s0,56(sp)
        addi    sp,sp,64
		  li a0, 10
		  ecall
        jr      ra

.data
.LC0:
        .string "[TEST #1] StructSum( 0, fill_with_threes)  test_result="
        .string ""
.LC1:
        .string "[TEST #2] StructSum( 1, fill_with_threes)  test_result="
        .string ""
.LC2:
        .string "[TEST #3] StructSum(-1, fill_with_threes)  test_result="
        .string ""
.LC3:
        .string "[TEST #4] StructSum( 0, fill_with_2pows)   test_result="
        .string ""
.LC4:
        .string "[TEST #5] StructSum( 1, fill_with_2pows)   test_result="
        .string ""
.LC5:
        .string "[TEST #6] StructSum(-1, fill_with_2pows)   test_result="
        .string ""
.LC6:
        .word 84082944
