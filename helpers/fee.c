#include "../headers/fee.h"
#include "../headers/ui.h" // For colors if needed
#include <stdio.h>
#include <stdlib.h>

#define FEE_FILE "data/fees.dat"

void assignFee(int studentId, int amount) {
  struct fee f;
  FILE *fp = fopen(FEE_FILE, "rb+");
  int found = 0;

  if (fp == NULL) {
    fp = fopen(FEE_FILE, "wb"); // Create if not exists
    if (fp == NULL)
      return;
  }

  // Check if fee record exists
  while (fread(&f, sizeof(struct fee), 1, fp) == 1) {
    if (f.studentId == studentId) {
      f.roomFeePerSemester = amount;
      f.isPaid = 0; // Reset to due on new assignment? Or just update amount.
                    // Let's reset to due.
      fseek(fp, -(long)sizeof(struct fee), SEEK_CUR);
      fwrite(&f, sizeof(struct fee), 1, fp);
      found = 1;
      break;
    }
  }

  if (!found) {
    // Append new record
    f.studentId = studentId;
    f.roomFeePerSemester = amount;
    f.isPaid = 0;
    // Need to close and reopen in append mode or just seek to end?
    // rb+ allows write.
    fseek(fp, 0, SEEK_END);
    fwrite(&f, sizeof(struct fee), 1, fp);
  }

  fclose(fp);
  printf("Fee assigned successfully for Student ID %d.\n", studentId);
}

void payFee(int studentId) {
  struct fee f;
  FILE *fp = fopen(FEE_FILE, "rb+");
  int found = 0;

  if (fp == NULL) {
    printf("Fees file not found.\n");
    return;
  }

  while (fread(&f, sizeof(struct fee), 1, fp) == 1) {
    if (f.studentId == studentId) {
      if (f.isPaid) {
        printf("Fee is already paid.\n");
      } else {
        printf("Redirecting to payment gateway...\n");
// Open payment.html in default browser
#ifdef _WIN32
        system("start payment.html");
#elif __APPLE__
        system("open payment.html");
#else
        system("xdg-open payment.html");
#endif

        printf("\nPlease complete the payment in the browser.\n");
        printf("Press Enter after payment is complete to verify...\n");
        while (getchar() != '\n')
          ;        // Clear buffer if needed
        getchar(); // Wait for Enter

        f.isPaid = 1;
        fseek(fp, -(long)sizeof(struct fee), SEEK_CUR);
        fwrite(&f, sizeof(struct fee), 1, fp);
        printf("Fee Paid Successfully!\n");
      }
      found = 1;
      break;
    }
  }

  if (!found)
    printf("No fee record found for Student ID %d.\n", studentId);
  fclose(fp);
}

void viewFeeStatus(int studentId) {
  struct fee f;
  FILE *fp = fopen(FEE_FILE, "rb");
  int found = 0;

  if (fp == NULL) {
    printf("No fee data.\n");
    return;
  }

  while (fread(&f, sizeof(struct fee), 1, fp) == 1) {
    if (f.studentId == studentId) {
      printf("\n=== Fee Status ===\n");
      printf("Student ID: %d\n", f.studentId);
      printf("Amount    : %d\n", f.roomFeePerSemester);
      printf("Status    : %s\n", f.isPaid ? "PAID" : "DUE");
      found = 1;
      break;
    }
  }

  if (!found)
    printf("No fee record found for you.\n");
  fclose(fp);
}
struct fee getFeeStatus(int studentId) {
  struct fee f;
  struct fee notFound = {-1, 0, 0};
  FILE *fp = fopen(FEE_FILE, "rb");

  if (fp == NULL) {
    return notFound;
  }

  while (fread(&f, sizeof(struct fee), 1, fp) == 1) {
    if (f.studentId == studentId) {
      fclose(fp);
      return f;
    }
  }

  fclose(fp);
  return notFound;
}

void viewAllFees() {
  struct fee f;
  FILE *fp = fopen(FEE_FILE, "rb");
  int found = 0;

  if (fp == NULL) {
    printf("No fee data available.\n");
    return;
  }

  printf("\n" COLOR_BOLD "=== All Student Fees ===" COLOR_RESET "\n");
  printf("%-12s %-15s %-12s\n", "Student ID", "Amount", "Status");
  printf("--------------------------------------------\n");

  while (fread(&f, sizeof(struct fee), 1, fp) == 1) {
    printf("%-12d %-15d %s\n", f.studentId, f.roomFeePerSemester,
           f.isPaid ? COLOR_GREEN "PAID" COLOR_RESET
                    : COLOR_RED "DUE" COLOR_RESET);
    found = 1;
  }

  if (!found)
    printf("No fee records found.\n");

  fclose(fp);
}