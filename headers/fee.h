#ifndef FEE_H
#define FEE_H

#include "ui.h"

struct fee {
  int studentId;
  int roomFeePerSemester;
  int isPaid; // 1 = Paid, 0 = Due
};

void assignFee(int studentId, int amount);
void payFee(int studentId);           // Process payment
void viewFeeStatus(int studentId);    // View own fee status
void viewAllFees();                   // Admin view all fees
struct fee getFeeStatus(int studentId); // Helper for fee data retrieval

#endif