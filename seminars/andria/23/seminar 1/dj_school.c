#include "dj_school.h"
#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

#define LOCK(mut) (pthread_mutex_lock(&mut))
#define UNLOCK(mut) (pthread_mutex_unlock(&mut))

sem_t free_teacher;
pthread_mutex_t global_lock;
int student_count;

struct teacher_data_t {
    int teacher_id, cur_student_id;
    bool is_busy;
    pthread_mutex_t internal_lock;
    sem_t grading;
} teachers_data [MAX_NUM_TEACHERS];


typedef struct {
    int student_id;
    sem_t done, send, recieve;
} student_args_t;

void* Teacher(void* args) {
    int id = *(int *)args;

    while (true) {
        LOCK(global_lock);
        if (student_count <= 0) {
            UNLOCK(global_lock);
            break;
        }
        UNLOCK(global_lock);
        
        // wait for free student
        sem_wait(&teachers_data[id].grading);
        // get student id
        int student_id;
        int result = TeacherEvaluateStudent(id, student_id);
        // send result to student
        sem_post(&teachers_data[id].grading);
    }

    TeacherDone(id);  
    return NULL;
}

void* Student(void* args) {
    int id = *(int *)args;

    bool result = false;

    while (!result) {
        StudentRecordSet(id);
        // find free teacher (get teacher id)
        int teacher_id;
        // send our set (send our id to techer)
        // receive anwser
        StudentWasEvaluatedByTeacher(id, teacher_id, result);
    }

    LOCK(global_lock);
    student_count--;
    UNLOCK(global_lock);

    // tell teacher you are done
    StudentDone(id);    
    return NULL;
}

void StartSchool(int num_students, int num_teachers) {
    int teacher_id[num_teachers];
    int student_id[num_students];

    sem_init(&free_teacher, 0, num_teachers);
    pthread_mutex_init(&global_lock, NULL);
    student_count = num_students;

    for (int i = 0; i < num_teachers; ++i) {
        teacher_id[i] = i;
        pthread_t tid;
        
        teachers_data[i].teacher_id = teacher_id[i];
        teachers_data[i].cur_student_id = -1;
        sem_init(&teachers_data[i].grading, 0, 0);

        pthread_create(&tid, NULL, Teacher, &teacher_id[i]);
        pthread_detach(tid);
    }

    for (int i = 0; i < num_students; ++i) {
        student_id[i] = i;
        pthread_t tid;

        // student_args_t args;
        // args.student_id = student_id[i];
        // sem_init(&args.done, 0, 1);
        // sem_init(&args.send, 0, 0);
        // sem_init(&args.recieve, 0, 0);

        pthread_create(&tid, NULL, Student, &student_id[i]);
        pthread_detach(tid);
    }

    SchoolEnd();
}
