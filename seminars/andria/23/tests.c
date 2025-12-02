#include "dj_school.h"

void TestOneStudentOneTeacher() {
    StartSchool(1, 1);
}

void TestThreeStudentsFiveTeacher() {
    StartSchool(3, 5);
}

void TestHundredStudentsTenTeachers() {
    StartSchool(100, 10);
}

int main() {
    TestOneStudentOneTeacher();
    TestThreeStudentsFiveTeacher();
    // TestHundredStudentsTenTeachers();
}
