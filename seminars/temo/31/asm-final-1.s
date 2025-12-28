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

# int defaultScore | 4 bytes | 24 offset
# int studentIndex | 4 bytes | 20 offset
# Course *course   | 4 bytes | 16 offset
# return address   | 4 bytes | 12 offset
studentScore:
# int result       | 4 bytes | 8 offset
# short scores[4]  | 8 bytes | 0 offset

#    int result = 0;
#    short scores[4];
addi sp, sp, -12
sw x0, 8(sp)

#course->students[studentIndex]->name))->addScores((void *)scores, 4)
# load course in x10
lw x10, 16(sp)
# load course->students
lw x10, 8(x10)

# load studentIndex in x11
lw x11, 20(sp)
# x11 * 4 (sizeof Student *)
li x12, 4
mul x11, x11, x12

add x10, x10, x11

# load student * in x10
lw x10, 0(x10)

# load student->name in x10
lw x10, 0(x10)

# load addScores in x10
lw x10, 10(x10)

# grow stack and ...
# load scores in x11
addi x11, sp, 0
# load 4 in x12
li x12, 4

addi sp, sp, -8
sw x11, 0(sp)
sw x12, 4(sp)

addi sp, sp, -4
sw ra, 0(sp)

jalr x10
#
lw ra, 0(sp)
addi sp, sp, 12

li x11, 40
blt x10, x11, else
#        result += scores[0] * course->credits;

# result
lw x10, 8(sp)
# scores[0]
lh x11, 0(sp)
# course->credits
lw x12, 16(sp)
lh x12, 4(x12)

mul x11, x11, x12

# store result
add x10, x11, x10
sw x10, 8(sp)

j end
else:
#        result = defaultScore;
# defaultScore
lw x10, 24(sp)
sw x10, 8(sp)
end:

lw x10, 8(sp)
addi sp, sp, 12
ret 
