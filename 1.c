#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student information
struct Student {
    char name[50];
    int rollNumber;
    int marks[5];
    int totalMarks;
    float averageMarks;
};

// Function to calculate total and average marks
void calculateMarks(struct Student *student) {
    int totalMark = 0;
    for (int i = 0; i < 5; ++i) {
        totalMark+= student->marks[i];
    }
    student->averageMarks = 0;
    student->totalMarks = totalMark;
    student->averageMarks = (float) totalMark / 5;
    printf("Average...... %f",student->averageMarks);
}

// Function to compare students for sorting based on total marks
int compareStudents(const void *a, const void *b) {
    return ((struct Student *)b)->totalMarks - ((struct Student *)a)->totalMarks;
}

int main() {
    FILE *file = fopen("student.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    struct Student students[100];
    int numStudents = 0;

    // Reading information about each student from the file
    while (fscanf(file, "%s %d %d %d %d %d %d",
                  students[numStudents].name,
                  &students[numStudents].rollNumber,
                  &students[numStudents].marks[0],
                  &students[numStudents].marks[1],
                  &students[numStudents].marks[2],
                  &students[numStudents].marks[3],
                  &students[numStudents].marks[4]) == 7) {
        calculateMarks(&students[numStudents]);
        numStudents++;

        // Break if we have read information for more than 100 students
        if (numStudents >= 100) {
            break;
        }
    }

    fclose(file);

    // Calculate total and average marks for each student
    for (int i = 0; i < numStudents; ++i) {
        calculateMarks(&students[i]);
    }

    // Sort students based on total marks
    // qsort(students, numStudents, sizeof(struct Student), compareStudents);

    // Display results
    printf("\nStudent names sorted based on total marks:\n");
    for (int i = 0; i < numStudents; ++i) {
        printf("%d. %s - Total Marks: %d ; Average Marks: %f\n", students[i].rollNumber, students[i].name, students[i].totalMarks, students[i].averageMarks);

    }

    return 0;
}
