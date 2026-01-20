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
    scanf(" %[^\n]", newstudent.name);

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
    #define MAX_STUDENTS 1000
    struct student students[MAX_STUDENTS];
    int count = 0;
    FILE *fp;

    fp = fopen("../data/students.dat", "rb");
    if (fp == NULL) {
        printf("Could not find Students File!\n");
        return;
    }

    while (fread(&students[count], sizeof(struct student), 1, fp) && count < MAX_STUDENTS) {
        count++;
    }
    fclose(fp);

    // Find the student index
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].studentId == studentId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student with ID %d not found.\n", studentId);
        return;
    }

    int choice;
    do {
        printf("\nEditing Student ID: %d\n", students[index].studentId);
        printf("1. Edit Name\n");
        printf("2. Edit Password\n");
        printf("3. Edit Room Number\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter New Name: ");
            scanf("%[^\n]", students[index].name);
            break;

        case 2:
            printf("Enter New Password: ");
            scanf("%9s", students[index].password);
            break;

        case 3:
            printf("Enter New Room Number: ");
            scanf("%d", &students[index].roomNumber);
            break;

        case 4:
            printf("No changes made.\n");
            break;

        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 4);

    // Write back all students
    fp = fopen("../data/students.dat", "wb");
    if (fp == NULL) {
        printf("Could not open Students File for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(&students[i], sizeof(struct student), 1, fp);
    }
    fclose(fp);

    printf("Student Data Updated Successfully!\n");
}



//delete student
void deleteStudent(int studentId){
    #define MAX_STUDENT 1000 //max values that can be loaded into memory at once

    struct student studentDelete[MAX_STUDENTS]; //setting the interface with the max load
    int count=0; // number of valid student records currently loaded into memory. defualt no of records that can be loaded is 0
    int index= -1; //position of the student you are searching for.
    FILE *fp;

    fp=fopen("../data/students.dat","rb");
    if (fp==NULL)
    {
        printf("Error: No File Found !");
        return;
    }

    //loading all studnets in an array
    while(count < MAX_STUDENT && fread(&studentDelete[count],sizeof(struct student),1,fp) == 1){
        count++;
    }


    //finding th student in the index range

    for (int i = 0; i < count; i++)
    {
        if(studentDelete[i].studentId==studentId){
            index = i;
            break;
        }
    }


    //error case handeling
    if (index == -1){
        printf("Student with Student ID : %d Not Found\n",studentId);
        return;
    }

    //Shifting records left to overwrite deleted student.
    for (int i = index; i < count - 1; i++)
    {
        studentDelete[i] = studentDelete[i+1];
    }

    count --;

    //rewrting the file without the deleted data

    fp=fopen("../data/students.dat","wb");
    if (fp==NULL)
    {
        printf("no file fount to write in.");
        return;
    }
    
    for (int i = 0; i < count; i++)
    {
        fwrite(&studentDelete[i],sizeof(struct student),1,fp);
    }
    fclose;
    
    
    printf("student with ID %d deleted successfully",studentId);

}



//STUDENT LOGIN

int studentLogin(int studentId,char password[10]){
    #define MAX_STUDENT 1000

    struct student checkStudent[MAX_STUDENT];
    FILE *fp;
    int count=0;
    int index=-1;
    fp = fopen("../data/students.dat","rb");
    if (fp==NULL)
    {
        printf("No Students DATA Found !");
    }

    while (count<MAX_STUDENTS && fread(&checkStudent[count],sizeof(struct student),1,fp)==1)
    {
        count++;
    }
    
    for (int i = 0; i < count; i++)
    {
        if (checkStudent[i].studentId==studentId && strcmp(checkStudent[i].password,password)==0)
        {
            index=i;
            printf("Login Successfull!\n");
            break;
        }
    }

    if (index==-1)
    {
        printf("Stundent Not Found with the given stundent Id %d\n",studentId);
        return -1;
    }else{
        printf("Logged in as student: %d\n",studentId);
        searchStudentById(studentId);
        return 1;
    }
}
//Dummy main func. for testing

int main(){
    // addStudent();
    // addStudent();
    // addStudent();

    viewStudent();

    // char name[30];
    // printf("Name to Search: ");
    // scanf(" %s",&name);
    // searchStudentByName(name);
    // int studentId;
    // printf("enter Student ID to delete: ");
    // scanf("%d",&studentId);
    // searchStudentById(studentId);

    int studentIp;
    char password[10];
    printf("enter Student ID to Login: ");
    scanf("%d",&studentIp);
    printf("enter Student password to Login: ");
    scanf("%s",&password);
    studentLogin(studentIp,password);

    // viewStudent();
}

