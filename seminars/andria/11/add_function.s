# int a0 = 67;
# int a1 = 39
# a0 = add(a0, a1)
# print(a0);
# exit();

main:
    li a0, 67
    li a1, 39

    call add            # mv ra, pc + 4; jump add 

    mv a1, a0
    li a0, 1
    ecall

    li a0, 10
    ecall

    
add:
    add a0, a0, a1
    ret                 # jump ra
