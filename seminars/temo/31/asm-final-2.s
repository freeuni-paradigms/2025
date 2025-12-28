#typedef struct {
#    char *name; // 4, off 0
#    short freeCredits; // 2, off 4
#    short *grades; // 4, off 6
#    short (*addScores)(void *scores, int n); // 4, off 10
#} Student; // 14 bytes
#
#typedef struct {
#    char *name;    // 4, off 0
#    short credits; // 2, off 4
#    short studentsNumber; // 2, off 6
#    Student **students; // 4, off 8 
#} Course; // 12 bytes
#
#short studentScore(Course *course, int studentIndex, int defaultScore) {
#    int result = 0;
#    short scores[4];
#
#    if (((Student *)(course->students[studentIndex]->name))->addScores((void *)scores, 4) >= 40) {
#        result += scores[0] * course->credits;
#    } else {
#        result = defaultScore;
#    }
#
#    return result;
#}

# int defaultScore # 4 bytes | 24  off
# int studentIndex # 4 bytes | 20  off
# Course *course   # 4 bytes | 16  off
# return address   # 4 bytes | 12  off
studentScore:
# int result       # 4 bytes | 8   off
# short scores[4]  # 8 bytes | 0   off


#    int result = 0;
addi sp, sp, -12
sw x0, 8(sp)

# ((Student *)(course->students[studentIndex]->name))->addScores((void *)scores
# load course in x10
lw x10, 16(sp)
# load students in x10
lw x10, 8(x10)
# students[studentIndex]  ==> students + studentsIndex * sizeof(Student *)
# load studentIndex in x11
lw x11, 20(sp)
# load Student * size in x12
li x12, 4
mul x11, x11, x12

# add x10 student index 
add x10, x10, x11

# load name in x10
lw x10, 0(x10)

# load addScore in x10
lw x10, 10(x10)

lw x11, 0(sp)
li x12, 4

# load function pointer
addi sp, sp, -8
mv x11, sp
sw x12, 4(sp)

addi sp, sp, -4
sw ra, 0(sp)
#### jalr
jalr x10

lw ra, 0(sp)
addi sp, sp, 12


#    if (x10 >= 40) {
#        result += scores[0] * course->credits;
#    } else {
#        result = defaultScore;
#    }
#
li x11, 40

blt x10, x11, less
# load scores[0] in x12
lh x12, 0(sp)
# laod course->credits in x13
lw x13, 16(sp)
lh x13, 4(x13)
mul x12, x12, x13

lw x13, 8(sp)
add x13, x13, x12
sw x13, 8(sp)

j end

less:
# defaultScore
lw x12, 24(sp)
sw x12, 8(sp)

end:
# load resul in x10
lw x10, 8(sp)
addi sp, sp, 12
ret

