#ifndef FEE_H
#define FEE_H

struct fee
{
    int roomFeePerSemester;
    int paid; //1=paid , 0=Due
};

void roomFee(int studentId,int roomFeePerSemester);
void viewFeeStatus(int studentId);

#endif