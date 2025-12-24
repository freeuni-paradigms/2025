; typedef struct {
;     char *name;                                   // 4 bytes - 0 offset
;     short freeCredits;                            // 2 bytes - 4 offset
;     short *grades;                                // 4 bytes - 6 offset
;     short (*addScores)(void *scores, int n);      // 4 bytes - 10 offset
; } Student;                                    // 14 bytes
;
; typedef struct {
;     char *name;                   // 4 bytes - 0 offset
;     short credits;                // 2 bytes - 4 offset
;     short studentsNumber;         // 2 bytes - 6 offset
;     Student **students;           // 4 bytes - 8 offset
; } Course;                     // 12 bytes
;
; short studentScore(Course *course, int studentIndex, int defaultScore) {
;     int result = 0;
;     short scores[4];
;
;     if (((Student *)(course->students[studentIndex]->name))->addScores((void *)scores, 4) >= 40) {
;         result += scores[0] * course->credits;
;     } else {
;         result = defaultScore;
;     }
;
;     return result;
; }
;

; course        -> 4(sp)
; studentIndex  -> 8(sp)
; defaultScore  -> 12(sp) 

; stack grew by 12
studentScore:
    ; int result = 0;
    addi sp, sp, -4
    sw zero, 0(sp)

    ; short scores[4];
    addi sp, sp, -8

    ; if (((Student *)(course->students[studentIndex]->name))->addScores((void *)scores, 4) >= 40) {
    lw t0, 16(sp)      ; get course (pointer)
    lw t0, 8(t0)       ; get course->students (ponter pointe)
    lw t1, 20(sp)      ; get studentIndex
    li t2, 4
    mul t1, t1, t2     ; alternative -> sl t1, t1, 2
    add t0, t0, t1
    lw t0, 0(t0)       ; course->students[studentIndex] (pointer)
    lw t0, 0(t0)       ; name (pointer)

    lw t0, 10(t0)      ; addScores (function pointer)

    addi sp, sp, -12   ; get ready for function call
    sw ra, 0(sp)
    li t1, 4
    sw t1, 8(sp)       ; int n
    addi t1, sp, 12
    sw t1, 4(sp)       ; (void *)scores

    jalr t0

    lw ra, 0(sp)       ; revert changes
    addi sp, sp, 12

    li t0, 40
    
    blt a0, t0, else
        ; result += scores[0] * course->credits;
        lh t0, 0(sp)    ; score[0]
        lw t1, 16(sp)   ; course
        lh t1, 4(t1)    ; course->credits
        mul t0, t0, t1

        lw t1, 8(sp)    ; result
        add t1, t0, t1  
        sw t1, 8(sp)

        j endif

    else:
        ; result = defaultScore;
        lw t0, 24(sp)  ; defaultScore
        sw t0, 8(sp)

    endif:

    lw a0, 8(sp)
    addi sp, sp, 12
    ret
