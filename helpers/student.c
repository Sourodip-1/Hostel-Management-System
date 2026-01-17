#include <stdio.h>
#include "../headers/student.h"



//ADDING STUDENT
void addStudent(void)
{

    FILE *fp;

    struct student newstudent;

    printf("Student ID: ");
    scanf("%d", &newstudent.studentId);

    printf("Name of Student: ");
    scanf("%19s", &newstudent.name);

    printf("Password: ");
    scanf("%9s", &newstudent.password);

    printf("Room Number: ");
    scanf("%d", &newstudent.roomNumber);

    //file handeling
    fp=fopen("../data/students.dat","ab");

    //error handeling
    if (fp==NULL)
    {
        printf("Could Not Find Students File!\n");
        return;
    }

    printf("\nDATA ADDED SUCCESSFULLY !!\n");
    fwrite(&newstudent,sizeof(struct student),1,fp);
    fclose(fp);

    //display new record
    printf("\n::::Student Information Added::::\n");
    printf("Student ID: %d\n", newstudent.studentId);
    printf("Name: %s\n", newstudent.name);
    printf("Password: %s\n", newstudent.password);
    printf("Room Number: %d\n", newstudent.roomNumber);
}


//VIEWING STUDENT
void viewStudent(void)
{
    struct student viewStudents;
    FILE *fp;

    fp = fopen("../data/students.dat", "rb");
    if (fp == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    printf("\n===== Student Records =====\n");

    while (fread(&viewStudents, sizeof(struct student), 1, fp))
    {
        printf("Student ID   : %d\n", viewStudents.studentId);
        printf("Name         : %s\n", viewStudents.name);
        printf("Password     : %s\n", viewStudents.password);
        printf("Room Number  : %d\n", viewStudents.roomNumber);
        printf("---------------------------\n");
    }
    fclose(fp);
}

//SEARCH STUDENT BY ID
void searchStudentById(int studentId){
    struct student searchById;
    FILE *fp;

    fp=fopen("../data/students.dat","rb");
    if (fp==NULL)
    {
        printf("Couldnt Find Students File!");
        return;
    }
    printf("==== Details of Student with ID number %d ====\n",studentId);
    while (fread(&searchById,sizeof(struct student),1,fp))
    {
        if (searchById.studentId==studentId)
        {
            printf("Student ID   : %d\n", searchById.studentId);
            printf("Name         : %s\n", searchById.name);
            printf("Password     : %s\n", searchById.password);
            printf("Room Number  : %d\n", searchById.roomNumber);
            printf("---------------------------\n");
        }
        
    }
    
    
}



//Dummy main func. for testing

int main(){
    addStudent();

    // int id;
    // printf("ID to Search: ");
    // scanf(" %d",&id);
    // searchStudentById(id);
}
