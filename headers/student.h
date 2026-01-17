#ifndef STUDENT_H
#define STUDENT_H

struct student
{
    int studentId;
    char name[30];
    char password[10];
    int roomNumber;
};

void addStudent();
void viewStudent();
void editStudent();
void deleteStudent();
int studentLogin(int id[10],char password[10]);
void searchStudentById(int studentId);



#endif