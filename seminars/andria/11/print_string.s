main:
   # addi sp, sp, -4
   # 
   # li t0, 'a'
   # li t1, 'p'
   # li t2, 0

   # sw t0, 0(sp)
   # sw t1, 1(sp)
   # sw t1, 2(sp)
   # sw t2, 3(sp)

   # mv a1, sp
   # li a0, 4
   # ecall

   # li a0, 10
   # ecall

    la a1, str
    li a0, 4
    ecall

    li a0, 10
    ecall


.data
str: .string "app"
