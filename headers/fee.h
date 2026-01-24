#ifndef FEE_H
#define FEE_H

struct fee {
  int studentId;
  int roomFeePerSemester;
  int isPaid; // 1 = Paid, 0 = Due
};

void assignFee(int studentId, int amount);
void payFee(int studentId); // Simulates payment
void viewFeeStatus(int studentId);

struct fee getFeeStatus(int studentId); // Helper for printing

#endif