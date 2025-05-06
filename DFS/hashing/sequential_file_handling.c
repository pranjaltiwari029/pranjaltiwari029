#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll_no;
    char name[50];
    float marks;
} Student;

void createFile() {
    FILE *fp;
    Student s;
    int n;

    fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Error creating file!\n");
        return;
    }

    printf("Enter number of students: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &s.roll_no);
        printf("Name: ");
        scanf(" %[^\n]", s.name);  // to read full line including spaces
        printf("Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(Student), 1, fp);
    }

    fclose(fp);
    printf("File created successfully!\n");
}

void displayRecords() {
    FILE *fp;
    Student s;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nStudent Records:\n");
    printf("Roll No\tName\t\tMarks\n");
    printf("------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%d\t%-15s%.2f\n", s.roll_no, s.name, s.marks);
    }

    fclose(fp);
}

void searchRecord(int roll_no) {
    FILE *fp;
    Student s;
    int found = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll_no == roll_no) {
            printf("\nRecord Found:\n");
            printf("Roll No: %d\n", s.roll_no);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nRecord with Roll No %d not found.\n", roll_no);
    }

    fclose(fp);
}

int main() {
    int choice, roll_no;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Create File\n");
        printf("2. Display Records\n");
        printf("3. Search Record by Roll No\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                printf("Enter Roll No to search: ");
                scanf("%d", &roll_no);
                searchRecord(roll_no);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
