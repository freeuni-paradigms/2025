# struct human { 
#   int doug;        | 0 offset
#   short emmyjo[2]; | 4 offset
# }; 
# struct other { 
#   char *freddie;           | 0 offset
#   struct human charlie;    | 4  offset
#   struct human *henrietta; | 12  offset
# }; 
# static struct human **AskingQuestions(struct human *heroes); 

# static struct human **BeingCalm(short *conformity, struct other *gooddeeds) { 
#   conformity[*conformity] = 0; 
#   gooddeeds += ((struct human *) (gooddeeds->henrietta[0].emmyjo))->doug; 
#   return AskingQuestions((struct human *) &gooddeeds); 
# } 


# other *gooddeeds   | 4 bytes | 8 offset
# short *conformity  | 4 bytes | 4 offset
# saved pc           | 4 bytes | 0 offset
beign_calm:

#   conformity[*conformity] = 0; 
# load conformity in x10
lw x10, 4(sp)
# load *conformity in x11
lh x11, 0(x10)
# conformity[*conformity] = 0       
# conformity + *conformity = 0    (char *)conformity + sizeof(short) * (*conformity) = 0
# load 2 * (*conformity) in x11
li x12, 2
mul x11, x11, x12
add x10, x10, x11

# store x0 in x10 address
sh x0, 0(x10)


#   gooddeeds += ((struct human *) (gooddeeds->henrietta[0].emmyjo))->doug; 
# load gooddeeds in x10
lw x10, 8(sp)

# gooddeeds->henrietta     (*gooddeeds).henrietta
# load gooddeeds->henrieta in x11
lw x11, 12(x10)

# henrietta[0].emmyjo =>  *henrietta.emmyjo
lw x12, 4(x11)

load doug in x13
lw x13, 0(x12)

# gooddeeds += x13  => (char*)gooddeeds + sizeof(other) * x13
li x14, 16
mul x14, x13, x14
add x10, x10, x14


# static struct human **AskingQuestions(struct human *heroes); 
#   return AskingQuestions((struct human *) &gooddeeds);

addi x10, sp, 8
addi sp, sp, -4
sw x10, 0(sp)

addi sp, sp, -4
sw ra, 0(sp)

la x14, asking_question
jalr x14

lw ra, 0(sp)
addi sp, sp, 8

ret

# human *
# saved pc
asking_questions:

ret
