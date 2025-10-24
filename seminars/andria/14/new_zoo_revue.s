.globl BeginCalm

# struct human {
#     int doug;             // 4 bytes
#     short emmyjo[2];      // 4 bytes (2 * 2)
# };                        // 8 bytes
# 
# struct other {
#     char *freddie;                // 4 bytes
#     struct human charlie;         // 8 bytes
#     struct human *henrietta;      // 4 bytes
# };                                // 16 bytes
# 
# static struct human **AskingQuestions(sruct human *heroes);
# static struct human **BeginCalm(short *conformity, struct other *gooddeeds)
# {
#     conformity[*conformity] = 0;                                                // Line 1
#     gooddeeds += ((struct human *) (gooddeeds->henrietta[0].emmyjo))->doug;     // Line 2
#     return AskingQuestions((struct human *) &gooddeeds);                        // Line 3
# }

BeginCalm:
    addi sp, sp, -4
    sw ra, 0(sp)

    # Line 1
    lw a0, 4(sp)            # conformity
    lw t0, 0(a0)            # *conformity
    slli t0, t0, 1          # offset = *conformity * 2
    add t0, a0, t0          # conformity + offset
    sw zero, 0(t0)          # conformity[*conformity] = 0

    # Line 2
    lw a1, 8(sp)            # gooddeeds
    lw t0, 12(a1)           # gooddeeds->henrietta

    # optimization for next 2 lines ---  lw t0, 4(t0) 
    addi t0, t0, 4          # gooddeeds->henrietta[0].emmyjo (emmyjo is a pointer to short array)
    lw t0, 0(t0)            # ((struct human *) (gooddeeds->henrietta[0].emmyjo))->doug

    add a1, a1, t0          # update gooddeeds on register
    sw a1, 8(sp)            # update gooddeeds on stack
    
    # Line 3
    addi t0, sp, 8          # &gooddeeds

    addi sp, sp, -4         # store first argument of AskingQuestions on stack
    sw t0, 0(sp)
    call AskingQuestions    # call function
    addi sp, sp, 4

    # AskingQustions wrote it's return value in a0, and it is the same as our return value
    # no need to change a0

    lw ra, 0(sp)
    addi sp, sp, 4

    ret


AskingQuestions:
    ret
    
