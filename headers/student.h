#ifndef STUDENT_H
#define STUDENT_H

struct student
{
    int studentId;
    char name[30];
    char password[10];
    int roomNumber;
};

void addStudent(); //done
void viewStudent(); //done
void editStudent(int studentId);
void deleteStudent();
int studentLogin(int studentId[10],char password[10]); 
void searchStudentById(int studentId); //done
void searchStudentByName(char name[30]); //done



#endif