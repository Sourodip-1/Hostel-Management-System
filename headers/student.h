#ifndef STUDENT_H
#define STUDENT_H

struct student {
  int studentId;
  char name[30];
  char password[65];
  int roomNumber;
};

void addStudent();                                  // done
void viewStudent();                                 // done
void editStudent(int studentId);                    // done
void deleteStudent(int studentId);                  // done
int studentLogin(int studentId, char password[30]); // done
void searchStudentById(int studentId);              // done
void searchStudentByName(char name[30]);            // done
int getStudentRoom(int studentId);

#endif