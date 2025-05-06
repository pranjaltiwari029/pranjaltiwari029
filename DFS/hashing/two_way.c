#include <stdio.h>
#include <stdlib.h>

void mergeFiles(const char *file1, const char *file2, const char *mergedFile) {
    FILE *f1, *f2, *fout;
    int num1, num2;
    int end1 = 0, end2 = 0;

    f1 = fopen(file1, "r");
    f2 = fopen(file2, "r");
    fout = fopen(mergedFile, "w");

    if (f1 == NULL || f2 == NULL || fout == NULL) {
        printf("Error opening files!\n");
        exit(1);
    }

    // Read first numbers from both files
    if (fscanf(f1, "%d", &num1) != 1) end1 = 1;
    if (fscanf(f2, "%d", &num2) != 1) end2 = 1;

    // Merge process
    while (!end1 && !end2) {
        if (num1 <= num2) {
            fprintf(fout, "%d ", num1);
            if (fscanf(f1, "%d", &num1) != 1) end1 = 1;
        } else {
            fprintf(fout, "%d ", num2);
            if (fscanf(f2, "%d", &num2) != 1) end2 = 1;
        }
    }

    // Write remaining numbers from file1
    while (!end1) {
        fprintf(fout, "%d ", num1);
        if (fscanf(f1, "%d", &num1) != 1) end1 = 1;
    }

    // Write remaining numbers from file2
    while (!end2) {
        fprintf(fout, "%d ", num2);
        if (fscanf(f2, "%d", &num2) != 1) end2 = 1;
    }

    printf("Files merged successfully into '%s'!\n", mergedFile);

    fclose(f1);
    fclose(f2);
    fclose(fout);
}

void displayFile(const char *filename) {
    FILE *fp;
    int num;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    printf("Contents of %s:\n", filename);
    while (fscanf(fp, "%d", &num) == 1) {
        printf("%d ", num);
    }
    printf("\n");

    fclose(fp);
}

int main() {
    const char *file1 = "file1.txt";
    const char *file2 = "file2.txt";
    const char *mergedFile = "merged.txt";

    mergeFiles(file1, file2, mergedFile);
    displayFile(mergedFile);

    return 0;
}
