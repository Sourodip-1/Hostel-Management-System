#ifndef ADMIN_H
#define ADMIN_H

struct admin {
  int adminId;
  char name[20];
  char password[65];
};

void initalizeAdminSystem(); // done
void addAdmin();             // done
void showAdmins(int adminId);
int adminLogin(int id, char password[65]);
void searchAdminById(int adminId);
void deleteAdmin(int adminId);
void editAdmin(int adminId);
void searchAdminByName(char name[30]);

#endif