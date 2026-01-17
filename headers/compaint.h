#ifndef COMPLAINT_H
#define COMPLAINT_H

struct complaint
{
    char date[11];
    char complaint[400];
    int complaintStatus; // 1 = open , 0 = Closed
};

void raiseComplaint(int studentId,int roomNumber,char date[11],char complaint[400]);
void viewComplaint(void);
void flagComplaint(int complaintStatus);

#endif