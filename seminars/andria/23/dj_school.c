#include "dj_school.h"
#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

#define LOCK(mut) (pthread_mutex_lock(&mut))
#define UNLOCK(mut) (pthread_mutex_unlock(&mut))

sem_t students_done;
pthread_mutex_t global_lock;
int student_count, teacher_count;

struct teacher_data_t {
    int teacher_id, cur_student_id;
    bool is_busy, grade;
    pthread_mutex_t internal_lock;
    sem_t grading_start, grading_end, thread_end;
} teachers_data[MAX_NUM_TEACHERS];

void* Teacher(void* args) {
    int id = *(int *)args;

    while (true) {
        // wait for free student
        sem_wait(&teachers_data[id].grading_start);

        LOCK(global_lock);
        if (student_count <= 0) {
            UNLOCK(global_lock);
            break;
        }
        UNLOCK(global_lock);

        // get student id
        LOCK(teachers_data[id].internal_lock);
        teachers_data[id].grade = 
            TeacherEvaluateStudent(id, teachers_data[id].cur_student_id);
        UNLOCK(teachers_data[id].internal_lock);
        
        // send result to student
        sem_post(&teachers_data[id].grading_end);
    }

    TeacherDone(id);
    sem_post(&teachers_data[id].thread_end);  
    return NULL;
}

void* Student(void* args) {
    int id = *(int *)args;

    bool result = false;
    while (!result) {
        StudentRecordSet(id);
        // find free teacher (get teacher id)
        int teacher_id;
        for (int i = 0; true; i++, i %= teacher_count) {
            LOCK(teachers_data[i].internal_lock);
            if (teachers_data[i].is_busy) {
                UNLOCK(teachers_data[i].internal_lock);
                continue;
            }

            teacher_id = teachers_data[i].teacher_id;
            teachers_data[i].is_busy = true;
            teachers_data[i].cur_student_id = id;
            UNLOCK(teachers_data[i].internal_lock);
            break;
        }

        // send our set (send our id to teacher)
        sem_post(&teachers_data[teacher_id].grading_start);

        // receive anwser
        sem_wait(&teachers_data[teacher_id].grading_end);

        LOCK(teachers_data[id].internal_lock);
        result = teachers_data[teacher_id].grade;
        teachers_data[teacher_id].is_busy = false;
        UNLOCK(teachers_data[id].internal_lock);

        StudentWasEvaluatedByTeacher(id, teacher_id, result);
    }

    LOCK(global_lock);
    student_count--;
    UNLOCK(global_lock);

    // tell teacher you are done
    StudentDone(id);    
    sem_post(&students_done);
    return NULL;
}

void StartSchool(int num_students, int num_teachers) {
    int teacher_id[num_teachers];
    int student_id[num_students];

    sem_init(&students_done, 0, 0);
    pthread_mutex_init(&global_lock, NULL);
    student_count = num_students;
    teacher_count = num_teachers;

    for (int i = 0; i < num_teachers; ++i) {
        teacher_id[i] = i;
        pthread_t tid;
        
        teachers_data[i].teacher_id = teacher_id[i];
        teachers_data[i].cur_student_id = -1;
        teachers_data[i].is_busy = false;
        pthread_mutex_init(&teachers_data[i].internal_lock, NULL);
        sem_init(&teachers_data[i].grading_start, 0, 0);
        sem_init(&teachers_data[i].grading_end, 0, 0);
        sem_init(&teachers_data[i].thread_end, 0, 0);

        pthread_create(&tid, NULL, Teacher, &teacher_id[i]);
        pthread_detach(tid);
    }

    for (int i = 0; i < num_students; ++i) {
        student_id[i] = i;
        pthread_t tid;
        pthread_create(&tid, NULL, Student, &student_id[i]);
        pthread_detach(tid);
    }

    // wait for students to finish
    for (int i = 0; i < num_students; i++)
        sem_wait(&students_done);

    // wait for teacher to finish
    for (int i = 0; i < num_teachers; i++) {
        // wake up sleeping teachers to finish
        sem_post(&teachers_data[i].grading_start);

        sem_wait(&teachers_data[i].thread_end);

        pthread_mutex_destroy(&teachers_data[i].internal_lock);
        sem_destroy(&teachers_data[i].grading_start);
        sem_destroy(&teachers_data[i].grading_end);
        sem_destroy(&teachers_data[i].thread_end);
    }

    sem_destroy(&students_done);
    pthread_mutex_destroy(&global_lock);

    SchoolEnd();
}
