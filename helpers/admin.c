#include <stdio.h>
#include <string.h>
#include "../headers/admin.h"
#include <ctype.h>

#define MAX_ADMINS 1000

// Function prototypes
static void toLower(char *s);
static int isValidPassword(const char *p);

void initalizeAdminSystem() // initializing default admin
{
    struct admin defaultUser;
    FILE *fp;

    fp = fopen("data/admin.dat", "wb");

    if (fp != NULL)
    {
        if ((fread(&defaultUser, sizeof(struct admin), 1, fp) == 0))
        {
            int adminId = 1000;
            char name[20] = "default";
            char password[64] = "Test@123";
            defaultUser.adminId = adminId;
            strcpy(defaultUser.name, name);
            strcpy(defaultUser.password, password);

            fwrite(&defaultUser, sizeof(struct admin), 1, fp);
            fclose(fp);
        }
    }
    else
    {
        printf("Error: Unable to open file.\n");
    }
}

void addAdmin(){
    struct admin newAdmin;
    FILE *fp;

    printf("Admin ID: ");
    scanf("%d", &newAdmin.adminId);

    printf("Name of Admin: ");
    scanf(" %[^\n]", newAdmin.name);   // FIX: leading space to consume newline

    printf("Password: ");
    scanf("%9s", newAdmin.password);



    fp=fopen("data/admin.dat","ab");

    if (fp==NULL)
    {
        printf("NO INITAL DATA FOUND ! CREATING DEFAULT ADMIN....");
        initalizeAdminSystem();
        return;
    }

    fwrite(&newAdmin, sizeof(struct admin), 1, fp);
    fclose(fp);   // FIX: proper fclose

    printf("\nDATA ADDED SUCCESSFULLY !!\n");
}


//show admins
void showAdmins(int adminId){
    struct admin allAdmins;
    FILE *fp = fopen("data/admin.dat", "rb");

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n===== Admin Records =====\n");

    while (fread(&allAdmins, sizeof(struct admin), 1, fp) == 1) {
        printf("Admin ID   : %d\n", allAdmins.adminId);
        printf("Name         : %s\n", allAdmins.name);
        printf("Password     : %s\n", allAdmins.password);
        printf("---------------------------\n");
    }
    fclose(fp);
}


//search by id
void searchAdminById(int adminId) {
    struct admin a;
    FILE *fp = fopen("data/admin.dat", "rb");

    if (fp == NULL) {
        printf("Couldn't find Admin File!\n");
        return;
    }

    while (fread(&a, sizeof(struct admin), 1, fp) == 1) {
        if (a.adminId == adminId) {
            printf("Admin ID   : %d\n", a.adminId);
            printf("Name       : %s\n", a.name);
            printf("Password   : %s\n", a.password);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Admin not found.\n");
}


//search by name

void searchAdminByName(char name[30]) {
    struct admin a;
    FILE *fp = fopen("data/admin.dat", "rb");

    if (fp == NULL) {
        printf("Couldn't find Admin File!\n");
        return;
    }

    char inputName[30];
    strcpy(inputName, name);
    toLower(inputName);

    while (fread(&a, sizeof(struct admin), 1, fp) == 1) {
        char fileName[30];
        strcpy(fileName, a.name);
        toLower(fileName);

        if (strcmp(fileName, inputName) == 0) {
            printf("Admin ID   : %d\n", a.adminId);
            printf("Name       : %s\n", a.name);
            printf("Password   : %s\n", a.password);
        }
    }

    fclose(fp);
}


//edit admin 

void editAdmin(int adminId) {
    struct admin admins[MAX_ADMINS];
    int count = 0;
    FILE *fp = fopen("data/admin.dat", "rb");

    if (fp == NULL) {
        printf("Could not find Admin File!\n");
        return;
    }

    while (count < MAX_ADMINS &&
           fread(&admins[count], sizeof(struct admin), 1, fp) == 1) {
        count++;
    }
    fclose(fp);

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (admins[i].adminId == adminId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Admin not found.\n");
        return;
    }

    int choice;
    do {
        printf("\n1.Edit Name  2.Edit Password  3.Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            scanf(" %[^\n]", admins[index].name);
            break;
        case 2:
            scanf("%9s", admins[index].password);
            break;
        }
    } while (choice != 3);

    fp = fopen("data/admin.dat", "wb");
    for (int i = 0; i < count; i++)
        fwrite(&admins[i], sizeof(struct admin), 1, fp);

    fclose(fp);
}

//delete admin 

void deleteAdmin(int adminId) {
    struct admin admins[MAX_ADMINS];
    int count = 0, index = -1;
    FILE *fp = fopen("data/admin.dat", "rb");

    if (fp == NULL) {
        printf("No Admin file found.\n");
        return;
    }

    while (count < MAX_ADMINS &&
           fread(&admins[count], sizeof(struct admin), 1, fp) == 1)
        count++;

    fclose(fp);

    for (int i = 0; i < count; i++) {
        if (admins[i].adminId == adminId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Admin not found.\n");
        return;
    }

    for (int i = index; i < count - 1; i++)
        admins[i] = admins[i + 1];

    fp = fopen("data/admin.dat", "wb");
    for (int i = 0; i < count - 1; i++)
        fwrite(&admins[i], sizeof(struct admin), 1, fp);

    fclose(fp);
}


//admin login 

int adminLogin(int adminId, char password[64]) {
    struct admin a;
    FILE *fp = fopen("data/admin.dat", "rb");

    if (fp == NULL) {
        printf("No admin data found.\n");
        return -1;
    }



    while (fread(&a, sizeof(struct admin), 1, fp) == 1) {
        if (a.adminId == adminId &&
            strcmp(a.password, password) == 0) {
            fclose(fp);
            printf("Admin login successful!\n");
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid admin credentials.\n");
    return -1;
}

// Define the missing toLower function
static void toLower(char *s) {
    for (; *s; s++) {
        if (*s >= 'A' && *s <= 'Z')
            *s = *s + 32;
    }
}

// Define the missing isValidPassword function
static int isValidPassword(const char *p) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0;
    int len = strlen(p);

    if (len < 6 || len > 9)
        return 0;

    for (int i = 0; i < len; i++) {
        if (p[i] >= 'A' && p[i] <= 'Z') hasUpper = 1;
        else if (p[i] >= 'a' && p[i] <= 'z') hasLower = 1;
        else if (p[i] >= '0' && p[i] <= '9') hasDigit = 1;
        // Allows special characters
    }
    return hasUpper && hasLower && hasDigit;
}


