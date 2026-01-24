#ifndef COMPLAINT_H
#define COMPLAINT_H

struct complaint {
  int id; // unique id
  int studentId;
  int roomNumber;
  char date[12]; // YYYY-MM-DD
  char description[400];
  int isResolved; // 1 = resolved, 0 = open
};

// Student functions
void raiseComplaint(int studentId, int roomNumber);
void viewMyComplaints(int studentId);

// Admin functions
void viewAllComplaints();
void resolveComplaint(int complaintId);

#endif