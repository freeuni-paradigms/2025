# typedef struct {
#   int violet;       | 0 offset
#   char *dash[2];    | 4 offset
#   char superboy[4]; | 12 offset
# } superhero; 
# 
# static superhero **pixar(superhero *syndrome); 
# static superhero *theincredibles(short *frozone, superhero elastigirl) { 
#   frozone += elastigirl.superboy[*frozone]; 
#   ((superhero *)((superhero *) elastigirl.dash[0])->dash)->violet = 400; 
#   return *pixar(&elastigirl) + 10; 
# } 


# superhero elastigirl | 16 bytes  | 8 offset
# short *frozone       | 4 bytes   | 4 offset
# saved pc             | 4 bytes   | 0 offset
theincreadibles:
#   frozone += elastigirl.superboy[*frozone]; 
# load frozone in x10
lw x10, 4(sp)
# load *frozone in x10
lh x10, 0(x10)
# load elastigirl.superboy in x11
addi x11, sp, 20
# load elastigirl.superboy x10 offset value in x12
add x11, x11, x10
lw x12, 0(x11)
# add x12 to frozone
li x13, 2
mul x12, x12, x13
lw x10, 4(sp)
add x10, x10, x12
sw x10, 4(sp)

#   ((superhero *)((superhero *) elastigirl.dash[0])->dash)->violet = 400; 
# load elastigirl.dash[0] in x10
lw x10, 12(sp)
# load *((superhero *) elastigirl.dash[0])).dash in x10
addi x10, x10, 4
# (superhero *)((superhero *) elastigirl.dash[0])->dash)->violet
li x11, 400
sw x11, 0(x10)

#   return *pixar(&elastigirl) + 10; 
# load &elastigirl in x10
addi x10, sp, 16

addi sp, sp, -4
sw x10, 0(sp)

addi sp, sp, -4
sw x1, 0(sp)
call pixar
lw x1, 0(sp)
addi sp, sp, 8

# load *rv in x10
lw x10, 0(x10)

# load 10 in x11
li x11, 10
# load struct size in x12
li x12, 16
# add 10 * sizeof(struct) to *pixar
mul x11, x11, x12
add x10, x10, x11
ret

pixar:
ret

