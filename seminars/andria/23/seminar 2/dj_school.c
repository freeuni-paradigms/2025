#include "dj_school.h"
#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

#define LOCK(mut) (pthread_mutex_lock(&mut))
#define UNLOCK(mut) (pthread_mutex_unlock(&mut))


typedef struct {
    int teacher_id, curr_student_id;
    bool grade, is_free;
    pthread_mutex_t internal_lock;
    sem_t grading_start, grading_end, thread_end;
} teacher_data_t;

typedef struct {
    int student_id;
} student_data_t;

teacher_data_t teachers[MAX_NUM_TEACHERS];
int students_count, teachers_count;
pthread_mutex_t global_lock;

void* Teacher(void* args) {
    int id = *(int *)args;

    while (true) {    
        LOCK(global_lock);
        if (students_count <= 0) {
            UNLOCK(global_lock);
            break;
        }
        UNLOCK(global_lock);

        // wait for student
        sem_wait(&teachers[id].grading_start);

        LOCK(teachers[id].internal_lock);
        int student_id = teachers[id].curr_student_id;
        teachers[id].grade = TeacherEvaluateStudent(id, student_id);
        UNLOCK(teachers[id].internal_lock);

        // send grade to student
        LOCK(teachers[id].internal_lock);
        sem_post(&teachers[id].grading_end);
    }

    TeacherDone(id);
    sem_post(&teachers[id].thread_end);
    return NULL;
}

void* Student(void* args) {
    int id = *(int *)args;
    
    bool grade = false;
    while (!grade) {
        StudentRecordSet(id);
        
        // find free teacher (get teacher_id) and send id
        int teacher_id;
        for (int i = 0; true; i++, i %= teachers_count)
        {
            LOCK(teachers[i].internal_lock);
            if (teachers[i].is_free) {
                teacher_id = i;
                teachers[i].curr_student_id = id;
                teachers[i].is_free = false;

                UNLOCK(teachers[i].internal_lock);
                break;
            }
            UNLOCK(teachers[i].internal_lock);
        }
        sem_post(&teachers[teacher_id].grading_start);

        // wait for response (update grade)
        sem_wait(&teachers[teacher_id].grading_end);
        grade = teachers[teacher_id].teacher_id;
        teachers[teacher_id].is_free = true;
        UNLOCK(teachers[teacher_id].internal_lock);

        StudentWasEvaluatedByTeacher(id, teacher_id, grade);
    }

    StudentDone(id);

    LOCK(global_lock);
    students_count--;
    UNLOCK(global_lock);
    
    return NULL;
}

void StartSchool(int num_students, int num_teachers) {
    int teacher_id[num_students];
    int student_id[num_teachers];

    students_count = num_students;
    teachers_count = num_teachers;
    pthread_mutex_init(&global_lock, NULL);

    for (int i = 0; i < num_teachers; ++i) {
        teacher_id[i] = i;
        pthread_t tid;

        teachers[i].teacher_id = teacher_id[i];
        teachers[i].curr_student_id = -1;
        teachers[i].grade = false;
        teachers[i].is_free = true;
        pthread_mutex_init(&teachers[i].internal_lock, NULL);
        sem_init(&teachers[i].grading_start, 0, 0);
        sem_init(&teachers[i].grading_end, 0, 0);
        sem_init(&teachers[i].thread_end, 0, 0);

        pthread_create(&tid, NULL, Teacher, &teacher_id[i]);
        pthread_detach(tid);
    }

    for (int i = 0; i < num_students; ++i) {
        student_id[i] = i;
        pthread_t tid;
        pthread_create(&tid, NULL, Student, &student_id[i]);
        pthread_detach(tid);
    }

    for (int i = 0; i < num_teachers; i++)
        sem_wait(&teachers[i].thread_end);

    pthread_mutex_destroy(&global_lock);

    SchoolEnd();
}
