#ifndef ROOM_H
#define ROOM_H

struct room
{
    int roomNumber;
    int roomCapacity;
    char Ac_Or_NonAc[10];
    int roomChargesPerPerson;
    int studentAssigned;
};

void addRoom(void);
void editRoomDetails(void);
void viewAssignedStudents(void);
void paidDueStudents(void);
void assignRoomToStudent(int studentId, int roomNumber);
void removeStudentFromRoom(int studentId);
void viewRooms(void);
int checkRoomAvailability(int roomNumber);

#endif