#include <stdio.h>
#include <string.h>
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


//SEARCH BY NAME
void searchStudentByName(char name[30]){
    struct student searchByName;
    FILE *fp;

    fp=fopen("../data/students.dat","rb");
    if (fp==NULL)
    {
        printf("Couldnt Find Students File!");
        return;
    }
    printf("==== Details of Student with Name %s ====\n",name);
    while (fread(&searchByName,sizeof(struct student),1,fp))
    {
        if (strcmp(strlwr(searchByName.name),strlwr(name))==0)
        {
            printf("Student ID   : %d\n", searchByName.studentId);
            printf("Name         : %s\n", searchByName.name);
            printf("Password     : %s\n", searchByName.password);
            printf("Room Number  : %d\n", searchByName.roomNumber);
            printf("---------------------------\n");
        }
    }
}

//EDIT STUDENT
void editStudent(int studentId){
    struct student editStudentData;
    int choice,found=0;
    FILE *fp,*temp;
    fp=fopen("../data/students.dat","rb");
    temp=fopen("../data/temp.dat","wb");

    if (fp==NULL)
    {
        printf("Couldnt Find Students File!");
        return;
    }

    while (fread(&editStudentData,sizeof(struct student),1,fp))
    {
        if (editStudentData.studentId==studentId)
        {
            found=1;
            do
            {
                printf("\nEditing Student ID: %d\n", editStudentData.studentId);
                printf("1. Edit Name\n");
                printf("2. Edit Password\n");
                printf("3. Edit Room Number\n");
                printf("4. Exit\n");
                printf("Enter choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    printf("Enter New Name: ");
                    scanf("%19s", &editStudentData.name);
                    break;

                case 2:
                    printf("Enter New Password: ");
                    scanf("%9s", &editStudentData.password);
                    break;

                case 3:
                    printf("Enter New Room Number: ");
                    scanf("%d", &editStudentData.roomNumber);
                    break;

                case 4:
                    printf("No changes made.\n");
                    break;

                default:
                    printf("Invalid choice.\n");
                }
            } while (choice!=4);
        }
    }

    fwrite(&editStudentData,sizeof(struct student),1,temp);
    
    fclose(fp);
    fclose(temp);

    remove("../data/students.dat");
    rename("../data/temp.dat","../data/students.dat");

    if (found)
    {
        printf("Student Data Updated Successfully !!");
    }else
    {
        printf("Failed to Update Student Data.");
    } 
}






//Dummy main func. for testing

int main(){
    addStudent();

    viewStudent();

    // char name[30];
    // printf("Name to Search: ");
    // scanf(" %s",&name);
    // searchStudentByName(name);

    int studentId;
    printf("enter Student ID to search: ");
    scanf("%d",&studentId);
    editStudent(studentId);

    viewStudent();
}
