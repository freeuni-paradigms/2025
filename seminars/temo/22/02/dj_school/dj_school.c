#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

int MAX_NUM_TEACHERS;
int MAX_NUM_STUDENTS;

// TODO init
pthread_mutex_t notifyTeacher[10];
pthread_mutex_t notifyStudent[100];
int teacherToStudent[10] = {-1};
bool studentEvaluations[100] = {false};
bool studentsDone = false;
pthread_mutex_t lock;

sem_t wait_students;
sem_t wait_teachers;
sem_t teachers_busy;


void init() {
  for (int i = 0; i < MAX_NUM_TEACHERS; i++) {
    pthread_mutex_init(&notifyTeacher[i], NULL);
    pthread_mutex_lock(&notifyTeacher[i]);
    teacherToStudent[i] = -1;
  }  

  for (int i = 0; i < MAX_NUM_STUDENTS; i++) {
    pthread_mutex_init(&notifyStudent[i], NULL);
    pthread_mutex_lock(&notifyStudent[i]);
    studentEvaluations[i] = false;
  }  

  studentsDone = false;

  pthread_mutex_init(&lock, NULL);

  sem_init(&wait_students, 0, 0);
  sem_init(&wait_teachers, 0, 0);
  sem_init(&teachers_busy, 0, MAX_NUM_TEACHERS);
}

void* Student(void* args) {
  int id = *(int*)args;
  // IMPLEMENT
  while (true) {
    StudentRecordSet(id);
    int teacher_id = -1;

    sem_wait(&teachers_busy);

    for (int i = 0; i < MAX_NUM_TEACHERS; i++) {
      pthread_mutex_lock(&lock);
      if (teacherToStudent[i] == -1) {
        teacher_id = i;
        teacherToStudent[i] = id;
        pthread_mutex_unlock(&lock);
        break;
      }
      pthread_mutex_unlock(&lock);
    }
    pthread_mutex_unlock(&notifyTeacher[teacher_id]);
    pthread_mutex_lock(&notifyStudent[id]);
    bool result = studentEvaluations[id];
    StudentWasEvaluatedByTeacher(id, teacher_id, result);
    if (result) 
      break;
  }
  StudentDone(id);
  sem_post(&wait_students);
  return NULL;
}

void* Teacher(void* args) {
  int id = *(int*)args;
  // IMPLEMENT
  while (true) {
    pthread_mutex_lock(&notifyTeacher[id]);
    if (studentsDone) 
      break;

    int student_id = teacherToStudent[id];
    bool result = TeacherEvaluateStudent(id, student_id); 
    studentEvaluations[student_id] = result;

    pthread_mutex_unlock(&notifyStudent[student_id]);

    pthread_mutex_lock(&lock);
    teacherToStudent[id] = -1;
    pthread_mutex_unlock(&lock);

    sem_post(&teachers_busy);
  }
  TeacherDone(id);
  sem_post(&wait_teachers);
  return NULL;
}


void StartSchool(int num_students, int num_teachers) {
  // IMPLEMENT: Initialize semaphores and mutexes if needed.
  int teacher_id[10];
  int student_id[100];

  MAX_NUM_STUDENTS = num_students;
  MAX_NUM_TEACHERS = num_teachers;
  init();
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
  
  for (int i = 0; i < MAX_NUM_STUDENTS; i++) {
    sem_wait(&wait_students);
  }

  studentsDone = true;

  for (int i = 0; i < MAX_NUM_TEACHERS; i++) {
    pthread_mutex_unlock(&notifyTeacher[i]);
  }

  for (int i = 0; i < MAX_NUM_TEACHERS; i++) {
    sem_wait(&wait_teachers);
  }

  SchoolEnd();
}
