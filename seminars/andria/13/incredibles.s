# typedef struct {
#   int violet;             // 4 bytes 
#   char *dash[2];          // 8 bytes (2 * 4 bytes)
#   char superboy[4];       // 4 bytes (4 * 1 bytes)
# } superhero;              // 16 bytes

# static superhero **pixar(superhero *syndrome);

# static superhero *theincredibles(short *frozone, superhero elastigirl)
#   frozone += elastigirl.superboy[*frozone];                               // line 1
#   ((superhero *)((superhero *) elastigirl.dash[0])->dash)->violet = 400;  // line 2 
#   return *pixar(&elastigirl) + 10;                                        // line 3
# }
theincredibles:
    addi sp, sp, -4
    sw ra, 0(sp)

    # Line 1
    lw a0, 4(sp)        # frozone
    lh t0, 0(a0)        # *frozone

    addi t1, t0, 20     # offset to elastigirl.superboy[*frozone]
    add t1, sp, t1      # &elastigirl.superboy[*frozone]
    lb t1, 0(t1)        # elastigirl.superboy[*frozone]

    add a0, a0, t1
    add a0, a0, t1      # t1 = 2 * offset => pointer arithmetic on short *
    sw a0, 4(sp)        # entire line

    # Line 2
    lw t0, 12(sp)       # elastigirl.dash[0]
    addi t0, t0, 4      # (superhero *) elastigirl.dash[0])->dash

    li t1, 400
    sw t1, 0(t0)        # entire line

    # Line 3
    addi t0, sp, 8      # &elastigirl

    addi sp, sp, -4     # store first argument (&elastigirl) in stack before call
    sw t0, 0(sp)
    call pixel          # call pixel(&elastigirl)
    lw t0, 0(sp)
    addi sp, sp, 4      # restore stack

    lw a0, 0(a0)        # *pixel(&elastigirl)
    addi a0, a0, 160     # *pixel(&elastigirl) + 10 = with pointer arithmetic on superhero * (16 * 10)

    lw ra, 0(sp)
    addi sp, sp, 4

    ret

pixel:
    ret
