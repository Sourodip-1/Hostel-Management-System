#include "../headers/complaint.h"
#include "../headers/ui.h" // assuming ui.h has colors and input helpers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMPLAINT_FILE "data/complaints.dat"

void raiseComplaint(int studentId, int roomNumber) {
  struct complaint c;
  FILE *fp = fopen(COMPLAINT_FILE, "ab");

  // Auto-generate ID (simple count + 1)
  // For a real system, we might want to read the last ID.
  // Here we can just scan the file to find the max ID.
  FILE *readFp = fopen(COMPLAINT_FILE, "rb");
  int maxId = 0;
  if (readFp) {
    struct complaint temp;
    while (fread(&temp, sizeof(struct complaint), 1, readFp) == 1) {
      if (temp.id > maxId)
        maxId = temp.id;
    }
    fclose(readFp);
  }
  c.id = maxId + 1;

  c.studentId = studentId;
  c.roomNumber = roomNumber;
  c.isResolved = 0;

  printf("Enter Date (YYYY-MM-DD): ");
  scanf("%11s", c.date);

  printf("Enter Complaint Description: ");
  scanf(" %[^\n]", c.description);

  if (fp == NULL) {
    printf("Error opening complaints file!\n");
    return;
  }

  fwrite(&c, sizeof(struct complaint), 1, fp);
  fclose(fp);

  printf("\nComplaint Raised Successfully! Complaint ID: %d\n", c.id);
}

void viewMyComplaints(int studentId) {
  struct complaint c;
  FILE *fp = fopen(COMPLAINT_FILE, "rb");

  if (fp == NULL) {
    printf("Be the first to raise a complaint!\n");
    return;
  }

  printf("\n=== My Complaints ===\n");
  int found = 0;
  while (fread(&c, sizeof(struct complaint), 1, fp) == 1) {
    if (c.studentId == studentId) {
      printf("ID: %d | Date: %s | Status: %s\n", c.id, c.date,
             c.isResolved ? "RESOLVED" : "OPEN");
      printf("Desc: %s\n", c.description);
      printf("-------------------------\n");
      found = 1;
    }
  }
  if (!found)
    printf("No complaints found.\n");
  fclose(fp);
}

void viewAllComplaints() {
  struct complaint c;
  FILE *fp = fopen(COMPLAINT_FILE, "rb");

  if (fp == NULL) {
    printf("No complaints data.\n");
    return;
  }

  printf("\n=== All Complaints ===\n");
  while (fread(&c, sizeof(struct complaint), 1, fp) == 1) {
    printf("ID: %d | Student: %d | Room: %d | Date: %s | Status: %s\n", c.id,
           c.studentId, c.roomNumber, c.date,
           c.isResolved ? "RESOLVED" : "OPEN");
    printf("Desc: %s\n", c.description);
    printf("-------------------------\n");
  }
  fclose(fp);
}

void resolveComplaint(int complaintId) {
  FILE *fp = fopen(COMPLAINT_FILE, "rb+");
  struct complaint c;
  int found = 0;

  if (fp == NULL) {
    printf("No complaints data.\n");
    return;
  }

  while (fread(&c, sizeof(struct complaint), 1, fp) == 1) {
    if (c.id == complaintId) {
      c.isResolved = 1;
      fseek(fp, -(long)sizeof(struct complaint), SEEK_CUR);
      fwrite(&c, sizeof(struct complaint), 1, fp);
      found = 1;
      break;
    }
  }

  fclose(fp);

  if (found)
    printf("Complaint %d marked as RESOLVED.\n", complaintId);
  else
    printf("Complaint ID %d not found.\n", complaintId);
}
