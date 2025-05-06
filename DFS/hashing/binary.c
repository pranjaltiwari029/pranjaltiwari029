#include <stdio.h>
#include <stdlib.h>

void createFile(const char *filename) {
    FILE *fp;
    int n, num;

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error creating file!\n");
        exit(1);
    }

    printf("Enter number of integers: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        fwrite(&num, sizeof(int), 1, fp);
    }

    fclose(fp);
    printf("File created successfully!\n");
}

void modifyValue(const char *filename) {
    FILE *fp;
    int index, new_value;
    long offset;

    fp = fopen(filename, "rb+"); // open for read and write
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("Enter index to modify (starting from 0): ");
    scanf("%d", &index);
    printf("Enter new value: ");
    scanf("%d", &new_value);

    offset = index * sizeof(int);
    if (fseek(fp, offset, SEEK_SET) != 0) {
        printf("Error seeking to position!\n");
        fclose(fp);
        return;
    }

    fwrite(&new_value, sizeof(int), 1, fp);
    printf("Value modified successfully!\n");

    fclose(fp);
}

void displayFile(const char *filename) {
    FILE *fp;
    int num;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("\nContents of the file:\n");
    while (fread(&num, sizeof(int), 1, fp)) {
        printf("%d ", num);
    }
    printf("\n");

    fclose(fp);
}

int main() {
    const char *filename = "data.bin";
    int choice;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Create File\n");
        printf("2. Modify Value\n");
        printf("3. Display File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile(filename);
                break;
            case 2:
                modifyValue(filename);
                break;
            case 3:
                displayFile(filename);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
