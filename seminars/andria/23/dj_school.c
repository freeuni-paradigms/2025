#include "dj_school.h"
#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

#define LOCK(mut) (pthread_mutex_lock(&mut))
#define UNLOCK(mut) (pthread_mutex_unlock(&mut))

void* Teacher(void* args) {
    int id = *(int *)args;

    TeacherDone(id);
    return NULL;
}

void* Student(void* args) {
    int id = *(int *)args;

    StudentDone(id);
    return NULL;
}

void StartSchool(int num_students, int num_teachers) {
    int teacher_id[num_students];
    int student_id[num_teachers];

    for (int i = 0; i < num_teachers; ++i) {
        teacher_id[i] = i;
        pthread_t tid;
        pthread_create(&tid, NULL, Teacher, &teacher_id[i]);
        pthread_detach(tid);
    }

    for (int i = 0; i < num_students; ++i) {
        student_id[i] = i;
        pthread_t tid;
        pthread_create(&tid, NULL, Student, &student_id[i]);
        pthread_detach(tid);
    }

    SchoolEnd();
}
