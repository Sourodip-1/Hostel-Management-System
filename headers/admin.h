#ifndef ADMIN_H
#define ADMIN_H

struct admin
{
    int adminId;
    char name[20];
    char pasword[64];
};


void initalizeAdminSystem;
int adminLogin(int id,char password[20]);


#endif