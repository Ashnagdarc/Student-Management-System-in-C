#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct for storing student information
struct Student {
    char name[50];
    int rollNumber;
    float marks;
};

// Function prototypes
void greetUser();
void displayMenu();
void addStudent(struct Student **students, int *totalStudents);
void displayStudents(struct Student *students, int totalStudents);
void editStudent(struct Student *students, int totalStudents);
void deleteStudent(struct Student **students, int *totalStudents);
void deleteAllStudents(struct Student **students, int *totalStudents);
void saveStudentsToFile(struct Student *students, int totalStudents);
void loadStudentsFromFile(struct Student **students, int *totalStudents);
void searchStudent(struct Student *students, int totalStudents);
float calculateAverageMarks(struct Student *students, int totalStudents);
void sortStudents(struct Student *students, int totalStudents);
void exitProgram(struct Student **students);

// Constants
#define PASS_MARKS 40
#define FILE_NAME "students.txt"

// Main function
int main() {
    struct Student *students = NULL;
    int totalStudents = 0;
    bool isRunning = true;

    greetUser();
    loadStudentsFromFile(&students, &totalStudents);

    while (isRunning) {
        displayMenu();
        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                addStudent(&students, &totalStudents);
                break;
            case 2:
                displayStudents(students, totalStudents);
                break;
            case 3:
                searchStudent(students, totalStudents);
                break;
            case 4:
                editStudent(students, totalStudents);
                break;
            case 5:
                deleteStudent(&students, &totalStudents);
                break;
            case 6:
                deleteAllStudents(&students, &totalStudents);
                break;
            case 7:
                printf("Average Marks: %.2f\n", calculateAverageMarks(students, totalStudents));
                break;
            case 8:
                sortStudents(students, totalStudents);
                break;
            case 9:
                saveStudentsToFile(students, totalStudents);
                break;
            case 0:
                isRunning = false;
                exitProgram(&students);
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }

    return 0;
}

// Function definitions
void greetUser() {
    char name[50];
    printf("Welcome to the Miva Student Management System!\n");
    printf("Please enter your name: ");
    scanf("%s", name);
    printf("Hello, %s!\n", name);
}

void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Edit Student\n");
    printf("5. Delete Student\n");
    printf("6. Delete All Students\n");
    printf("7. Calculate Average Marks\n");
    printf("8. Sort Students by Marks\n");
    printf("9. Save Students to File\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void addStudent(struct Student **students, int *totalStudents) {
    struct Student newStudent;

    printf("Enter student name: ");
    scanf("%s", newStudent.name);
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNumber);
    printf("Enter marks: ");
    scanf("%f", &newStudent.marks);

    (*totalStudents)++;
    *students = (struct Student *)realloc(*students, (*totalStudents) * sizeof(struct Student));
    (*students)[(*totalStudents) - 1] = newStudent;

    printf("Student added successfully!\n");
}

void displayStudents(struct Student *students, int totalStudents) {
    if (totalStudents == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < totalStudents; i++) {
        printf("Name: %s, Roll Number: %d, Marks: %.2f, Status: %s\n",
               students[i].name, students[i].rollNumber, students[i].marks,
               students[i].marks >= PASS_MARKS ? "Passed" : "Failed");
    }
}

void editStudent(struct Student *students, int totalStudents) {
    int rollNumber;
    printf("Enter roll number of the student to edit: ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < totalStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Enter new name: ");
            scanf("%s", students[i].name);
            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);
            printf("Student record updated successfully!\n");
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void deleteStudent(struct Student **students, int *totalStudents) {
    int rollNumber;
    printf("Enter roll number of the student to delete: ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < *totalStudents; i++) {
        if ((*students)[i].rollNumber == rollNumber) {
            for (int j = i; j < (*totalStudents) - 1; j++) {
                (*students)[j] = (*students)[j + 1];
            }
            (*totalStudents)--;
            *students = (struct Student *)realloc(*students, (*totalStudents) * sizeof(struct Student));
            printf("Student record deleted successfully!\n");
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void deleteAllStudents(struct Student **students, int *totalStudents) {
    free(*students);
    *students = NULL;
    *totalStudents = 0;
    printf("All student records deleted successfully!\n");
}

void saveStudentsToFile(struct Student *students, int totalStudents) {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < totalStudents; i++) {
        fprintf(file, "%s %d %f\n", students[i].name, students[i].rollNumber, students[i].marks);
    }

    fclose(file);
    printf("Student records saved to file successfully!\n");
}

void loadStudentsFromFile(struct Student **students, int *totalStudents) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return;
    }

    struct Student tempStudent;
    while (fscanf(file, "%s %d %f", tempStudent.name, &tempStudent.rollNumber, &tempStudent.marks) != EOF) {
        (*totalStudents)++;
        *students = (struct Student *)realloc(*students, (*totalStudents) * sizeof(struct Student));
        (*students)[(*totalStudents) - 1] = tempStudent;
    }

    fclose(file);
    printf("Student records loaded from file successfully!\n");
}

void searchStudent(struct Student *students, int totalStudents) {
    int rollNumber;
    printf("Enter roll number of the student to search: ");
    scanf("%d", &rollNumber);

    for (int i = 0; i < totalStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Name: %s, Roll Number: %d, Marks: %.2f, Status: %s\n",
                  students[i].name, students[i].rollNumber, students[i].marks,
                  students[i].marks >= PASS_MARKS ? "Passed" : "Failed");
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

float calculateAverageMarks(struct Student *students, int totalStudents) {
    if (totalStudents == 0) {
        return 0.0;
    }

    float totalMarks = 0.0;
    for (int i = 0; i < totalStudents; i++) {
        totalMarks += students[i].marks;
    }

    return totalMarks / totalStudents;
}

void sortStudents(struct Student *students, int totalStudents) {
    for (int i = 0; i < totalStudents - 1; i++) {
        for (int j = 0; j < totalStudents - i - 1; j++) {
            if (students[j].marks > students[j + 1].marks) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Students sorted by marks successfully!\n");
}

void exitProgram(struct Student **students) {
    free(*students);
    printf("Exiting the program. Goodbye!\n");
}