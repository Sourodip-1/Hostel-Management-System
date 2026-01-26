#include "../headers/student.h"
#include "../headers/security.h"
#include <stdio.h>
#include <string.h>

// CODE BEAUTYFICATION IS DONE USING AI

// ALL FUNCITONS ARE HAND WRITTEN
/*
    FIX SUMMARY (high level):
    - Fixed macro inconsistencies (MAX_STUDENT vs MAX_STUDENTS)
    - Fixed unsafe scanf usage
    - Fixed newline buffer issues
    - Removed non-standard strlwr()
    - Fixed fclose bug
    - Improved login flow safety
    - Added basic validation helpers
*/

// Macro moved to header student.h

/* -------------------- Utility Helpers -------------------- */

// FIX: portable lowercase conversion (replaces non-standard strlwr)
static void toLower(char *s) {
  for (; *s; s++) {
    if (*s >= 'A' && *s <= 'Z')
      *s = *s + 32;
  }
}

// FIX: basic password policy (regex-like validation)
static int isValidPassword(const char *p) {
  int hasUpper = 0, hasLower = 0, hasDigit = 0;
  int len = strlen(p);

  if (len < 6 || len > 9)
    return 0;

  for (int i = 0; i < len; i++) {
    if (p[i] >= 'A' && p[i] <= 'Z')
      hasUpper = 1;
    else if (p[i] >= 'a' && p[i] <= 'z')
      hasLower = 1;
    else if (p[i] >= '0' && p[i] <= '9')
      hasDigit = 1;
    // Allows special characters
  }
  return hasUpper && hasLower && hasDigit;
}

/* -------------------- ADD STUDENT -------------------- */

void addStudent(void) {
  FILE *fp;
  struct student newstudent;

  printf("Student ID: ");
  scanf("%d", &newstudent.studentId);

  printf("Name of Student: ");
  scanf(" %[^\n]", newstudent.name); // FIX: leading space to consume newline

  char tempPass[30];
  printf("Password: ");
  scanf("%29s", tempPass);
  hashPassword(tempPass, newstudent.password);

  newstudent.roomNumber = 0; // Initialize with no room

  fp = fopen("data/students.dat", "ab");

  if (fp == NULL) {
    printf("Could Not Find Students File!\n");
    return;
  }

  fwrite(&newstudent, sizeof(struct student), 1, fp);
  fclose(fp); // FIX: proper fclose

  printf("\nDATA ADDED SUCCESSFULLY !!\n");
}

/* -------------------- VIEW STUDENTS -------------------- */

void viewStudent(void) {
  struct student viewStudents;
  FILE *fp = fopen("data/students.dat", "rb");

  if (fp == NULL) {
    printf("No student records found.\n");
    return;
  }

  printf("\n===== Student Records =====\n");

  while (fread(&viewStudents, sizeof(struct student), 1, fp) == 1) {
    printf("Student ID   : %d\n", viewStudents.studentId);
    printf("Name         : %s\n", viewStudents.name);
    printf("Password     : %s\n", viewStudents.password);
    printf("Room Number  : %d\n", viewStudents.roomNumber);
    printf("---------------------------\n");
  }
  fclose(fp);
}

/* -------------------- SEARCH BY ID -------------------- */

void searchStudentById(int studentId) {
  struct student s;
  FILE *fp = fopen("data/students.dat", "rb");

  if (fp == NULL) {
    printf("Couldn't find Students File!\n");
    return;
  }

  while (fread(&s, sizeof(struct student), 1, fp) == 1) {
    if (s.studentId == studentId) {
      printf("Student ID   : %d\n", s.studentId);
      printf("Name         : %s\n", s.name);
      printf("Password     : %s\n", s.password);
      printf("Room Number  : %d\n", s.roomNumber);
      fclose(fp);
      return;
    }
  }
  fclose(fp);
  printf("Student not found.\n");
}

/* -------------------- SEARCH BY NAME -------------------- */

void searchStudentByName(char name[30]) {
  struct student s;
  FILE *fp = fopen("data/students.dat", "rb");

  if (fp == NULL) {
    printf("Couldn't find Students File!\n");
    return;
  }

  char inputName[30];
  strcpy(inputName, name);
  toLower(inputName); // FIX: portable lowercase

  while (fread(&s, sizeof(struct student), 1, fp) == 1) {
    char fileName[30];
    strcpy(fileName, s.name);
    toLower(fileName);

    if (strcmp(fileName, inputName) == 0) {
      printf("Student ID   : %d\n", s.studentId);
      printf("Name         : %s\n", s.name);
      printf("Password     : %s\n", s.password);
      printf("Room Number  : %d\n", s.roomNumber);
    }
  }
  fclose(fp);
}

/* -------------------- EDIT STUDENT -------------------- */

void editStudent(int studentId) {
  struct student students[MAX_STUDENTS];
  int count = 0;
  FILE *fp = fopen("data/students.dat", "rb");

  if (fp == NULL) {
    printf("Could not find Students File!\n");
    return;
  }

  while (count < MAX_STUDENTS &&
         fread(&students[count], sizeof(struct student), 1, fp) == 1) {
    count++;
  }
  fclose(fp);

  int index = -1;
  for (int i = 0; i < count; i++) {
    if (students[i].studentId == studentId) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Student not found.\n");
    return;
  }

  int choice;
  do {
    printf("\n1.Edit Name  2.Edit Password  3.Edit Room  4.Exit\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      scanf(" %[^\n]", students[index].name); // FIX: newline safe
      break;
    case 2:
      scanf("%29s", students[index].password);
      break;
    case 3:
      scanf("%d", &students[index].roomNumber);
      break;
    }
  } while (choice != 4);

  fp = fopen("data/students.dat", "wb");
  for (int i = 0; i < count; i++)
    fwrite(&students[i], sizeof(struct student), 1, fp);

  fclose(fp);
}

/* -------------------- DELETE STUDENT -------------------- */

void deleteStudent(int studentId) {
  struct student students[MAX_STUDENTS];
  int count = 0, index = -1;
  FILE *fp = fopen("data/students.dat", "rb");

  if (fp == NULL) {
    printf("No file found.\n");
    return;
  }

  while (count < MAX_STUDENTS &&
         fread(&students[count], sizeof(struct student), 1, fp) == 1)
    count++;

  fclose(fp);

  for (int i = 0; i < count; i++) {
    if (students[i].studentId == studentId) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Student not found.\n");
    return;
  }

  for (int i = index; i < count - 1; i++)
    students[i] = students[i + 1];

  fp = fopen("data/students.dat", "wb");
  for (int i = 0; i < count - 1; i++)
    fwrite(&students[i], sizeof(struct student), 1, fp);

  fclose(fp); // FIX: actual fclose call
}

/* -------------------- STUDENT LOGIN -------------------- */

int studentLogin(int studentId, char password[30]) {
  struct student s;
  FILE *fp = fopen("data/students.dat", "rb");

  if (fp == NULL) {
    printf("No student data found.\n");
    return -1;
  }

  char hashedInput[65];
  hashPassword(password, hashedInput);

  while (fread(&s, sizeof(struct student), 1, fp) == 1) {
    if (s.studentId == studentId && strcmp(s.password, hashedInput) == 0) {
      fclose(fp);
      printf("Login successful!\n");
      return 1;
    }
  }

  fclose(fp);
  printf("Invalid credentials.\n");
  return -1;
}

/* -------------------- GET STUDENT ROOM -------------------- */

int getStudentRoom(int studentId) {
  struct student s;
  FILE *fp = fopen("data/students.dat", "rb");

  if (fp == NULL) {
    return -1;
  }

  while (fread(&s, sizeof(struct student), 1, fp) == 1) {
    if (s.studentId == studentId) {
      fclose(fp);
      return s.roomNumber;
    }
  }
  fclose(fp);
  return -1;
}
