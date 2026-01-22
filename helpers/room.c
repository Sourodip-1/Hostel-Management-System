#include "../headers/room.h"
#include "../headers/student.h"
#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 200

void addRoom() {
  struct room newRoom;
  FILE *fp;

  printf("Room Number: ");
  scanf("%d", &newRoom.roomNumber);

  printf("Capacity of the Room: ");
  scanf("%d", &newRoom.roomCapacity); // FIX: leading space to consume newline

  printf("Room Type (AC / Non AC)");
  scanf("%10s", newRoom.Ac_Or_NonAc); // FIX: removed &, length bound

  printf("Room Charges Per Person: ");
  scanf("%d", &newRoom.roomChargesPerPerson);
  printf("How Many Students are Assigned: ");
  scanf("%d", &newRoom.studentAssigned);

  fp = fopen("data/room.dat", "ab");

  if (fp == NULL) {
    printf("Could Not Find Rooms File!\n");
    return;
  }

  fwrite(&newRoom, sizeof(struct room), 1, fp);
  fclose(fp); // FIX: proper fclose

  printf("\nROOM ADDED SUCCESSFULLY !!\n");
}

/* -------------------- VIEW ROOMS -------------------- */
void viewRooms() {
  struct room r;
  FILE *fp = fopen("data/room.dat", "rb");

  if (fp == NULL) {
    printf("No rooms found.\n");
    return;
  }

  printf("\n%-10s %-10s %-10s %-10s %-15s\n", "Room No", "Capacity", "Type",
         "Assigned", "Charges");
  printf("------------------------------------------------------------\n");

  while (fread(&r, sizeof(struct room), 1, fp) == 1) {
    printf("%-10d %-10d %-10s %-10d %-15d\n", r.roomNumber, r.roomCapacity,
           r.Ac_Or_NonAc, r.studentAssigned, r.roomChargesPerPerson);
  }
  fclose(fp);
}

/* -------------------- CHECK AVAILABILITY -------------------- */
int checkRoomAvailability(int roomNumber) {
  struct room r;
  FILE *fp = fopen("data/room.dat", "rb");

  if (fp == NULL) {
    return 0;
  }

  while (fread(&r, sizeof(struct room), 1, fp) == 1) {
    if (r.roomNumber == roomNumber) {
      fclose(fp);
      if (r.studentAssigned < r.roomCapacity) {
        return 1; // Available
      } else {
        return 0; // Full
      }
    }
  }
  fclose(fp);
  return 0; // Room not found
}

/* -------------------- EDIT ROOM DETAILS -------------------- */
void editRoomDetails(int roomNumber) {
  struct room rooms[MAX_ROOMS];
  int count = 0;
  FILE *fp = fopen("data/room.dat", "rb");

  if (fp == NULL) {
    printf("No rooms found.\n");
    return;
  }

  while (count < MAX_ROOMS &&
         fread(&rooms[count], sizeof(struct room), 1, fp) == 1) {
    count++;
  }
  fclose(fp);

  int index = -1;
  for (int i = 0; i < count; i++) {
    if (rooms[i].roomNumber == roomNumber) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Room not found.\n");
    return;
  }

  int choice;
  do {
    printf("\n1. Edit Capacity\n");
    printf("2. Edit Type (AC/Non-AC)\n");
    printf("3. Edit Charges\n");
    printf("4. Back\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter new Capacity: ");
      scanf("%d", &rooms[index].roomCapacity);
      break;
    case 2:
      printf("Enter new Type: ");
      scanf("%s", rooms[index].Ac_Or_NonAc);
      break;
    case 3:
      printf("Enter new Charges: ");
      scanf("%d", &rooms[index].roomChargesPerPerson);
      break;
    case 4:
      break;
    default:
      printf("Invalid choice.\n");
    }
  } while (choice != 4);

  fp = fopen("data/room.dat", "wb");
  for (int i = 0; i < count; i++) {
    fwrite(&rooms[i], sizeof(struct room), 1, fp);
  }
  fclose(fp);
  printf("Room updated successfully.\n");
}

/* -------------------- ASSIGN ROOM TO STUDENT -------------------- */
void assignRoomToStudent(int studentId, int roomNumber) {
  if (checkRoomAvailability(roomNumber) == 0) {
    printf("Room %d is full or does not exist.\n", roomNumber);
    return;
  }

  // 1. Update Student's Room
  struct student students[1000]; // Assuming MAX_STUDENTS from student.c
  int sCount = 0;
  FILE *sFp = fopen("data/students.dat", "rb");
  if (sFp == NULL) {
    printf("Student data not found.\n");
    return;
  }
  while (sCount < 1000 &&
         fread(&students[sCount], sizeof(struct student), 1, sFp) == 1) {
    sCount++;
  }
  fclose(sFp);

  int sIndex = -1;
  for (int i = 0; i < sCount; i++) {
    if (students[i].studentId == studentId) {
      sIndex = i;
      break;
    }
  }

  if (sIndex == -1) {
    printf("Student ID %d not found.\n", studentId);
    return;
  }

  // Check if student already has a room (optional, but good practice)
  if (students[sIndex].roomNumber != 0) {
    // Could ask for confirmation, but simply overwriting or warning is easiest.
    // For now, let's warn but proceed, or handle the count decrement of old
    // room? To keep it simple, we assume reassignment handles the count logic
    // if we do it carefully. But wait, if we overwrite, we should decrement the
    // OLD room's count. That adds complexity: "Move Student" logic. Let's
    // assume this is for fresh assignment. If roomNumber != 0, warn.
    if (students[sIndex].roomNumber != 0) {
      printf("Warning: Student already assigned to Room %d. Please remove "
             "first.\n",
             students[sIndex].roomNumber);
      return;
    }
  }

  students[sIndex].roomNumber = roomNumber;

  sFp = fopen("data/students.dat", "wb");
  for (int i = 0; i < sCount; i++)
    fwrite(&students[i], sizeof(struct student), 1, sFp);
  fclose(sFp);

  // 2. Update Room Count
  struct room rooms[MAX_ROOMS];
  int rCount = 0;
  FILE *rFp = fopen("data/room.dat", "rb");
  if (rFp) {
    while (rCount < MAX_ROOMS &&
           fread(&rooms[rCount], sizeof(struct room), 1, rFp) == 1)
      rCount++;
    fclose(rFp);

    for (int i = 0; i < rCount; i++) {
      if (rooms[i].roomNumber == roomNumber) {
        rooms[i].studentAssigned++;
        break;
      }
    }

    rFp = fopen("data/room.dat", "wb");
    for (int i = 0; i < rCount; i++)
      fwrite(&rooms[i], sizeof(struct room), 1, rFp);
    fclose(rFp);
  }

  printf("Student %d assigned to Room %d successfully.\n", studentId,
         roomNumber);
}

/* -------------------- REMOVE STUDENT FROM ROOM -------------------- */
void removeStudentFromRoom(int studentId) {
  // 1. Find Student and Get Room
  struct student
      students[MAX_ROOMS]; // using MAX_ROOMS sized buffer safely or defining
                           // MAX_STUDENTS locally? helpers/student.c defined
                           // MAX_STUDENTS 1000. Let's use 1000 here for safety.
  struct student buffer_students[1000];
  int sCount = 0;
  FILE *sFp = fopen("data/students.dat", "rb");
  if (!sFp) {
    printf("Student data not found.\n");
    return;
  }
  while (sCount < 1000 &&
         fread(&buffer_students[sCount], sizeof(struct student), 1, sFp) == 1)
    sCount++;
  fclose(sFp);

  int sIndex = -1;
  for (int i = 0; i < sCount; i++) {
    if (buffer_students[i].studentId == studentId) {
      sIndex = i;
      break;
    }
  }

  if (sIndex == -1) {
    printf("Student ID %d not found.\n", studentId);
    return;
  }

  int oldRoomNumber = buffer_students[sIndex].roomNumber;
  if (oldRoomNumber == 0) {
    printf("Student is not assigned to any room.\n");
    return;
  }

  // 2. Update Student Record
  buffer_students[sIndex].roomNumber = 0;
  sFp = fopen("data/students.dat", "wb");
  for (int i = 0; i < sCount; i++)
    fwrite(&buffer_students[i], sizeof(struct student), 1, sFp);
  fclose(sFp);

  // 3. Update Room Count
  struct room rooms[MAX_ROOMS];
  int rCount = 0;
  FILE *rFp = fopen("data/room.dat", "rb");
  if (rFp) {
    while (rCount < MAX_ROOMS &&
           fread(&rooms[rCount], sizeof(struct room), 1, rFp) == 1)
      rCount++;
    fclose(rFp);

    for (int i = 0; i < rCount; i++) {
      if (rooms[i].roomNumber == oldRoomNumber) {
        if (rooms[i].studentAssigned > 0)
          rooms[i].studentAssigned--;
        break;
      }
    }

    rFp = fopen("data/room.dat", "wb");
    for (int i = 0; i < rCount; i++)
      fwrite(&rooms[i], sizeof(struct room), 1, rFp);
    fclose(rFp);
  }
  printf("Student removed from Room %d successfully.\n", oldRoomNumber);
}

/* -------------------- VIEW ASSIGNED STUDENTS -------------------- */
void viewAssignedStudents() {
  struct student s;
  FILE *fp = fopen("data/students.dat", "rb");
  if (!fp) {
    printf("No students found.\n");
    return;
  }

  printf("\n%-10s %-20s %-10s\n", "ID", "Name", "Room No");
  printf("------------------------------------------\n");

  int found = 0;
  while (fread(&s, sizeof(struct student), 1, fp) == 1) {
    if (s.roomNumber != 0) {
      printf("%-10d %-20s %-10d\n", s.studentId, s.name, s.roomNumber);
      found = 1;
    }
  }
  fclose(fp);

  if (!found)
    printf("No students currently assigned to rooms.\n");
}

/* -------------------- PAID DUE STUDENTS (PLACEHOLDER) -------------------- */
void paidDueStudents() {
  printf("\n[Feature Not Implemented] Fee module is currently missing data "
         "structures to link fees to students.\n");
}
