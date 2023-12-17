#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student information
struct Student
{
    char name[50];
    int roll;
    int marks;
    char dob[20];
};

// Function to create the file
void createFile(const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error creating the file.\n");
        exit(1);
    }
    fclose(file);
}

// Function to add a new record to the file
void addRecord(const char *filename, struct Student *newStudent)
{
    FILE *file = fopen(filename, "ab");
    if (file == NULL)
    {
        printf("Error opening the file for adding a record.\n");
        exit(1);
    }
    fwrite(newStudent, sizeof(struct Student), 1, file);
    fclose(file);
}

// Function to delete a record by roll number
void deleteRecord(const char *filename, int rollToDelete)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error opening the file for deleting a record.\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(file);
        exit(1);
    }

    struct Student currentStudent;
    int found = 0;

    while (fread(&currentStudent, sizeof(struct Student), 1, file) == 1)
    {
        if (currentStudent.roll != rollToDelete)
        {
            fwrite(&currentStudent, sizeof(struct Student), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("Record with roll number %d not found.\n", rollToDelete);
        remove("temp.dat");
    }
    else
    {
        remove(filename);
        rename("temp.dat", filename);
        printf("Record with roll number %d deleted successfully.\n", rollToDelete);
    }
}

// Function to modify marks based on the given conditions
void modifyMarks(const char *filename)
{
    FILE *file = fopen(filename, "rb+");
    if (file == NULL)
    {
        printf("Error opening the file for modifying marks.\n");
        exit(1);
    }

    struct Student currentStudent;

    while (fread(&currentStudent, sizeof(struct Student), 1, file) == 1)
    {
        if (currentStudent.marks < 50 && currentStudent.marks > 40)
        {
            currentStudent.marks += 10;
            fseek(file, -sizeof(struct Student), SEEK_CUR);
            fwrite(&currentStudent, sizeof(struct Student), 1, file);
        }
    }

    fclose(file);
}

int main()
{
    const char *filename = "student_records.dat";

    // (1) Create the file
    createFile(filename);
    int choice;
    while (1)
    {

        printf("\n*****MENU*****\n");
        printf("1 for Adding a record\n");
        printf("2 for Delete a record by roll number\n");
        printf("3 for Modify marks\n");
        printf("0 for EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            char name[50];
            int roll;
            int marks;
            char dob[20];
            scanf("%s", name);
            scanf("%d", &roll);
            scanf("%d", &marks);
            scanf("%s", dob);
            struct Student newStudent;
            strcpy(newStudent.name, name);
            newStudent.roll = roll;
            newStudent.marks = marks;
            strcpy(newStudent.dob, dob);

            addRecord(filename, &newStudent);
            break;
        case 2:
            int rollToDelete;
            printf("Enter the roll to be deleted: ");
            scanf("%d", &rollToDelete);
            deleteRecord(filename, rollToDelete);
            break;
        case 3:
            modifyMarks(filename);
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
