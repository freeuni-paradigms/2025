typedef struct {
    char *name;
    short freeCredits;
    short *grades;
    short (*addScores)(void *scores, int n);
} Student;

typedef struct {
    char *name;
    short credits;
    short studentsNumber;
    Student **students;
} Course;

short studentScore(Course *course, int studentIndex, int defaultScore) {
    int result = 0;
    short scores[4];

    if (((Student *)(course->students[studentIndex]->name))->addScores((void *)scores, 4) >= 40) {
        result += scores[0] * course->credits;
    } else {
        result = defaultScore;
    }

    return result;
}

