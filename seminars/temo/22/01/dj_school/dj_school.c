#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

#define FREE_TEACHER -1

bool studentsDone = false;
sem_t signalTeacher[MAX_NUM_TEACHERS];
sem_t signalStudent[MAX_NUM_STUDENTS];
int studentsWaiting[MAX_NUM_TEACHERS] = {FREE_TEACHER};
bool studentResults[MAX_NUM_STUDENTS] = {false};
pthread_cond_t students_cond;
pthread_cond_t teachers_cond;
int studentsCount;
int teachersCount;
pthread_mutex_t mutex;
sem_t wait_teacher;
pthread_mutex_t locks[MAX_NUM_TEACHERS];

void init(int num_students, int num_teachers) {
  for (int i = 0; i < num_students; i++) {
    sem_init(&signalTeacher[i], 0, 0);
    pthread_mutex_init(&locks[i], NULL);
    studentResults[i] = false;
  }

  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < num_teachers; i++) {
    sem_init(&signalStudent[i], 0, 0);
    studentsWaiting[i] = FREE_TEACHER;
  }

  pthread_cond_init(&students_cond, NULL);
  pthread_cond_init(&teachers_cond, NULL);
  
  sem_init(&wait_teacher, 0, 0);

  studentsCount = num_students;
  teachersCount = num_teachers;

  studentsDone = false;
}

void* Teacher(void* args) {
  int id = *(int*)args;
  // IMPLEMENT
  while (true) {
    sem_post(&wait_teacher);
    sem_wait(&signalTeacher[id]);
    if (studentsDone) {
      break;
    }
    bool result = TeacherEvaluateStudent(id, studentsWaiting[id]);
    studentResults[studentsWaiting[id]] = result;
    sem_post(&signalStudent[studentsWaiting[id]]);
    pthread_mutex_lock(&locks[id]);
    studentsWaiting[id] = FREE_TEACHER;
    pthread_mutex_unlock(&locks[id]);
  }
  TeacherDone(id);
  pthread_mutex_lock(&mutex);
  teachersCount--;
  if (teachersCount == 0) {
    pthread_cond_signal(&teachers_cond);
  }
  pthread_mutex_unlock(&mutex);
}

void* Student(void* args) {
  int id = *(int*)args;
  // IMPLEMENT
  while (true) {
    StudentRecordSet(id);
    int teacher_id = -1;
    //printf("aa\n");
    //pthread_mutex_lock(&mutex);
    //pthread_cond_wait(&wait_teacher, &mutex);
    //printf("AA\n");
    //pthread_mutex_unlock(&mutex);
    //printf("bb\n");
    sem_wait(&wait_teacher);
    for (int i = 0; i < MAX_NUM_TEACHERS; i++) {
      pthread_mutex_lock(&locks[i]);
      if (studentsWaiting[i] == FREE_TEACHER) {
        studentsWaiting[i] = id;
        teacher_id = i;
        pthread_mutex_unlock(&locks[i]);
        break;
      } else {
        pthread_mutex_unlock(&locks[i]);
      }
    }
    sem_post(&signalTeacher[teacher_id]);

    sem_wait(&signalStudent[id]);

    bool result = studentResults[id];
    StudentWasEvaluatedByTeacher(id, teacher_id, result);

    if (result) {
      break;
    }
  }

  StudentDone(id);
  pthread_mutex_lock(&mutex);
  studentsCount--;
  if (studentsCount == 0) 
    pthread_cond_signal(&students_cond);
  pthread_mutex_unlock(&mutex);
}


void StartSchool(int num_students, int num_teachers) {
  // IMPLEMENT: Initialize semaphores and mutexes if needed.
  int teacher_id[MAX_NUM_TEACHERS];
  int student_id[MAX_NUM_STUDENTS];
  init(num_students, num_teachers);
  for (int i = 0; i < MAX_NUM_TEACHERS; i++) {
    sem_init(&signalTeacher[i], 0, 0);
  }
  for (int i = 0; i < MAX_NUM_STUDENTS; i++) {
    sem_init(&signalStudent[i], 0, 0);
  }
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
  // IMPLEMENT: Wait for the all students and teachers to finish.
  
  pthread_mutex_lock(&mutex);
  pthread_cond_wait(&students_cond, &mutex);
  pthread_mutex_unlock(&mutex);

  studentsDone = true;

  for (int i = 0; i < num_teachers; i++) {
    sem_post(&signalTeacher[i]);
  }

  pthread_mutex_lock(&mutex);
  pthread_cond_wait(&teachers_cond, &mutex);
  pthread_mutex_unlock(&mutex);

  SchoolEnd();
}
