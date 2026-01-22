#include "headers/admin.h"
#include "headers/room.h"
#include "headers/student.h"
#include "headers/ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void manageAdmins(int currentAdminId) {
  int choice;
  do {
    clearScreen();
    printTitle();
    printf("\n" COLOR_BOLD "=== Admin Management ===" COLOR_RESET "\n");
    printf(COLOR_GREEN "1." COLOR_RESET " Add New Admin\n");
    printf(COLOR_GREEN "2." COLOR_RESET " View All Admins\n");
    printf(COLOR_GREEN "3." COLOR_RESET " Search Admin by ID\n");
    printf(COLOR_GREEN "4." COLOR_RESET " Search Admin by Name\n");
    printf(COLOR_GREEN "5." COLOR_RESET " Edit Admin\n");
    printf(COLOR_GREEN "6." COLOR_RESET " Delete Admin\n");
    printf(COLOR_RED "0. Back to Dashboard" COLOR_RESET "\n");
    printf("Enter Choice: ");

    if (scanf("%d", &choice) != 1) {
      clearBuffer();
      choice = -1;
    }

    switch (choice) {
    case 1:
      clearScreen();
      addAdmin();
      waitForInput();
      break;
    case 2:
      clearScreen();
      showAdmins(currentAdminId);
      waitForInput();
      break;
    case 3: {
      int searchId;
      printf("Enter ID to search: ");
      scanf("%d", &searchId);
      searchAdminById(searchId);
      waitForInput();
      break;
    }
    case 4: {
      char name[30];
      printf("Enter Name to search: ");
      scanf(" %[^\n]", name);
      searchAdminByName(name);
      waitForInput();
      break;
    }
    case 5: {
      int editId;
      printf("Enter ID to edit: ");
      scanf("%d", &editId);
      editAdmin(editId);
      waitForInput();
      break;
    }
    case 6: {
      int delId;
      printf("Enter ID to delete: ");
      scanf("%d", &delId);
      deleteAdmin(delId);
      waitForInput();
      break;
    }
    case 0:
      break;
    default:
      printf(COLOR_RED "Invalid choice!\n" COLOR_RESET);
      waitForInput();
    }
  } while (choice != 0);
}

void manageStudents() {
  int choice;
  do {
    clearScreen();
    printTitle();
    printf("\n" COLOR_BOLD "=== Student Management ===" COLOR_RESET "\n");
    printf(COLOR_GREEN "1." COLOR_RESET " Add New Student\n");
    printf(COLOR_GREEN "2." COLOR_RESET " View All Students\n");
    printf(COLOR_GREEN "3." COLOR_RESET " Search Student by ID\n");
    printf(COLOR_GREEN "4." COLOR_RESET " Search Student by Name\n");
    printf(COLOR_GREEN "5." COLOR_RESET " Edit Student\n");
    printf(COLOR_GREEN "6." COLOR_RESET " Delete Student\n");
    printf(COLOR_RED "0. Back to Dashboard" COLOR_RESET "\n");
    printf("Enter Choice: ");

    if (scanf("%d", &choice) != 1) {
      clearBuffer();
      choice = -1;
    }

    switch (choice) {
    case 1:
      clearScreen();
      addStudent();
      waitForInput();
      break;
    case 2:
      clearScreen();
      viewStudent();
      waitForInput();
      break;
    case 3: {
      int sId;
      printf("Enter Student ID: ");
      scanf("%d", &sId);
      searchStudentById(sId);
      waitForInput();
      break;
    }
    case 4: {
      char sName[30];
      printf("Enter Student Name: ");
      scanf(" %[^\n]", sName);
      searchStudentByName(sName);
      waitForInput();
      break;
    }
    case 5: {
      int editSId;
      printf("Enter Student ID to edit: ");
      scanf("%d", &editSId);
      editStudent(editSId);
      waitForInput();
      break;
    }
    case 6: {
      int delSId;
      printf("Enter Student ID to delete: ");
      scanf("%d", &delSId);
      deleteStudent(delSId);
      waitForInput();
      break;
    }
    case 0:
      break;
    default:
      printf(COLOR_RED "Invalid choice!\n" COLOR_RESET);
      waitForInput();
    }
  } while (choice != 0);
}

void manageRooms() {
  int choice;
  do {
    clearScreen();
    printTitle();
    printf("\n" COLOR_BOLD "=== Room Management ===" COLOR_RESET "\n");
    printf(COLOR_GREEN "1." COLOR_RESET " Add New Room\n");
    printf(COLOR_GREEN "2." COLOR_RESET " View All Rooms\n");
    printf(COLOR_GREEN "3." COLOR_RESET " Check Room Availability\n");
    printf(COLOR_GREEN "4." COLOR_RESET " Edit Room Details\n");
    printf(COLOR_GREEN "5." COLOR_RESET " Assign Room to Student\n");
    printf(COLOR_GREEN "6." COLOR_RESET " Remove Student from Room\n");
    printf(COLOR_GREEN "7." COLOR_RESET " View Assigned Students\n");
    printf(COLOR_GREEN "8." COLOR_RESET " View Fee Status (Placeholder)\n");
    printf(COLOR_RED "0. Back to Dashboard" COLOR_RESET "\n");
    printf("Enter Choice: ");

    if (scanf("%d", &choice) != 1) {
      clearBuffer();
      choice = -1;
    }
    switch (choice) {
    case 1:
      clearScreen();
      addRoom();
      waitForInput();
      break;
    case 2:
      clearScreen();
      viewRooms();
      waitForInput();
      break;
    case 3: {
      int rNum;
      clearScreen();
      printf("Enter Room Number to check: ");
      scanf("%d", &rNum);
      int avail = checkRoomAvailability(rNum);
      if (avail)
        printf(COLOR_GREEN "Room %d is Available.\n" COLOR_RESET, rNum);
      else
        printf(COLOR_RED "Room %d is Full or Not Found.\n" COLOR_RESET, rNum);
      waitForInput();
    } break;
    case 4: {
      int rNum;
      clearScreen();
      printf("Enter Room Number to edit: ");
      scanf("%d", &rNum);
      editRoomDetails(rNum);
      waitForInput();
    } break;
    case 5: {
      int sId, rNum;
      clearScreen();
      printf("Enter Student ID: ");
      scanf("%d", &sId);
      printf("Enter Room Number: ");
      scanf("%d", &rNum);
      assignRoomToStudent(sId, rNum);
      waitForInput();
    } break;
    case 6: {
      int sId;
      clearScreen();
      printf("Enter Student ID to remove: ");
      scanf("%d", &sId);
      removeStudentFromRoom(sId);
      waitForInput();
    } break;
    case 7:
      clearScreen();
      viewAssignedStudents();
      waitForInput();
      break;
    case 8:
      clearScreen();
      paidDueStudents();
      waitForInput();
      break;
    case 0:
      break;
    default:
      printf(COLOR_RED "Invalid choice!\n" COLOR_RESET);
      waitForInput();
    }
  } while (choice != 0);
}

void adminMenu() {
  int id;
  char password[64];

  clearScreen();
  printTitle();
  printf("\n" COLOR_YELLOW "=== Admin Login ===" COLOR_RESET "\n");
  printf("Admin ID: ");
  scanf("%d", &id);
  printf("Password: ");
  scanf("%63s", password);

  if (adminLogin(id, password) == 1) {
    printAnimated(
        COLOR_GREEN "Login Successful! Loading Dashboard..." COLOR_RESET, 20);
    int choice;
    do {
      clearScreen();
      printTitle();
      printf("\n" COLOR_BOLD "=== Admin Dashboard ===" COLOR_RESET "\n");
      printf("Logged in as ID: " COLOR_CYAN "%d" COLOR_RESET "\n", id);
      printf("-----------------------\n");
      printf(COLOR_GREEN "1." COLOR_RESET " Manage Admins\n");
      printf(COLOR_GREEN "2." COLOR_RESET " Manage Students\n");
      printf(COLOR_GREEN "3." COLOR_RESET " Manage Rooms\n");
      printf(COLOR_RED "0. Logout" COLOR_RESET "\n");
      printf("Number of selection: ");

      if (scanf("%d", &choice) != 1) {
        clearBuffer();
        choice = -1;
      }

      switch (choice) {
      case 1:
        manageAdmins(id);
        break;
      case 2:
        manageStudents();
        break;
      case 3:
        manageRooms();
        break;
      case 0:
        printf(COLOR_YELLOW "Logging out...\n" COLOR_RESET);
        waitForInput();
        break;
      default:
        printf(COLOR_RED "Invalid choice.\n" COLOR_RESET);
        waitForInput();
      }
    } while (choice != 0);
  } else {
    printf(COLOR_RED "Auth Failed!" COLOR_RESET "\n");
    waitForInput();
  }
}

void studentMenu() {
  int id;
  char password[30];

  clearScreen();
  printTitle();
  printf("\n" COLOR_YELLOW "=== Student Login ===" COLOR_RESET "\n");
  printf("Student ID: ");
  scanf("%d", &id);
  printf("Password: ");
  scanf("%29s", password);

  if (studentLogin(id, password) == 1) {
    printAnimated(
        COLOR_GREEN "Login Successful! Loading Profile..." COLOR_RESET, 20);
    int choice;
    do {
      clearScreen();
      printTitle();
      printf("\n" COLOR_BOLD "=== Student Dashboard ===" COLOR_RESET "\n");
      printf("Welcome Student ID: " COLOR_CYAN "%d" COLOR_RESET "\n", id);
      printf("-------------------------\n");
      printf(COLOR_GREEN "1." COLOR_RESET " View Profile\n");
      printf(COLOR_RED "0. Logout" COLOR_RESET "\n");
      printf("Number of selection: ");

      if (scanf("%d", &choice) != 1) {
        clearBuffer();
        choice = -1;
      }

      switch (choice) {
      case 1:
        clearScreen();
        searchStudentById(id);
        waitForInput();
        break;
      case 0:
        printf(COLOR_YELLOW "Logging out...\n" COLOR_RESET);
        waitForInput();
        break;
      default:
        printf(COLOR_RED "Invalid choice.\n" COLOR_RESET);
        waitForInput();
      }
    } while (choice != 0);
  } else {
    printf(COLOR_RED "Auth Failed!" COLOR_RESET "\n");
    waitForInput();
  }
}

int main() {
  setupConsole();
  initalizeAdminSystem();
  int choice;

  printAnimated(COLOR_CYAN "Initializing System Modules..." COLOR_RESET, 10);

  do {
    clearScreen();
    printTitle();
    printf("\n");
    printf(COLOR_BOLD "    MAIN MENU    " COLOR_RESET "\n");
    printf(COLOR_GREEN "1." COLOR_RESET " Admin Login\n");
    printf(COLOR_GREEN "2." COLOR_RESET " Student Login\n");
    printf(COLOR_RED "0. Exit" COLOR_RESET "\n");
    printf("----------------------------------\n");
    printf("Number of selection: ");

    if (scanf("%d", &choice) != 1) {
      clearBuffer();
      choice = -1;
    }

    switch (choice) {
    case 1:
      adminMenu();
      break;
    case 2:
      studentMenu();
      break;
    case 0:
      printAnimated(COLOR_CYAN "\nExiting System... Goodbye!" COLOR_RESET, 30);
      break;
    default:
      printf(COLOR_RED "Invalid choice! Please try again.\n" COLOR_RESET);
      waitForInput();
    }
  } while (choice != 0);

  return 0;
}
