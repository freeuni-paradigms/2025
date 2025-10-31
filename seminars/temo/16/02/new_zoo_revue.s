# struct human { 8 bytes
#   int doug;         | 0 offset
#   short emmyjo[2];  | 4 offset
# }; 
# 
# struct other { 16 byte
#   char *freddie;           | 0  offset
#   struct human charlie;    | 4  offset
#   struct human *henrietta; | 12 offset
# };
#  
# static struct human **AskingQuestions(struct human *heroes); 
# static struct human **BeingCalm(short *conformity, struct other *gooddeeds) { 
#   conformity[*conformity] = 0; 
#   gooddeeds += ((struct human *) (gooddeeds->henrietta[0].emmyjo))->doug; 
#   return AskingQuestions((struct human *) &gooddeeds); 
# } 

# other * gooddeeds      | 4 bytes  | 8 offsets
# short * conformity     | 4 bytes  | 4 offsets
# saved_pc               | 4 bytes  | 0 offsets
being_calm:
#   conformity[*conformity] = 0; 
# load conformity in x10
lw x10, 4(sp)
# load *conformity in x11
lh x11, 0(x10)

# conformity + x11 * 2
li x12, 2
mul x12, x11 x12
add x11, x11, x12
sh x0, 0(x11)

#   gooddeeds += ((struct human *) (gooddeeds->henrietta[0].emmyjo))->doug; 
# load gooddeeds in x10
lw x10, 8(sp)

# load x11 gooddeeds->henrietta (human *)    (*gooddeeds).henrietta
lw x11, 12(x10)

# (x11) henrietta[0]    *henrietta
# henrietta->emmyjo
# load emmyjo address in x12
addi x12, x11, 4

# load x12->doug in x13
lw x13, 0(x12)

# multiply x13 to 16 (sizeof other)
li x14, 16
mul x13, x13, x14

# add gooddeeds(x10) x13
add x10, x10, x13
# store x10 value to stack
sw x10, 8(sp)

#   return AskingQuestions((struct human *) &gooddeeds); 
# load gooddeeds address in x10
addi x10, sp, 8

# store x10 to stack
addi sp, sp, -4
sw x10, 0(sp)

# store saved pc
addi sp, sp, -4
sw ra, 0(sp)

call asking_questions

lw ra, 0(sp)
addi sp, sp, 8

ret

asking_questions:
ret
