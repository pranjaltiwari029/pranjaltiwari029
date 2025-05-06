#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

void splitIntoRuns(const char *inputFile, const char *run1, const char *run2) {
    FILE *in = fopen(inputFile, "r");
    FILE *r1 = fopen(run1, "w");
    FILE *r2 = fopen(run2, "w");
    int prev, curr;
    int toggle = 0;

    if (!in || !r1 || !r2) {
        printf("Error opening files!\n");
        exit(1);
    }

    if (fscanf(in, "%d", &prev) != 1) {
        fclose(in);
        fclose(r1);
        fclose(r2);
        return;
    }

    fprintf(r1, "%d ", prev);

    while (fscanf(in, "%d", &curr) == 1) {
        if (curr < prev) {
            toggle = 1 - toggle; // Switch files
        }

        if (toggle == 0)
            fprintf(r1, "%d ", curr);
        else
            fprintf(r2, "%d ", curr);

        prev = curr;
    }

    fclose(in);
    fclose(r1);
    fclose(r2);
}

int isSingleRun(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    int prev, curr;

    if (!fp) {
        printf("Error opening file %s\n", fileName);
        exit(1);
    }

    if (fscanf(fp, "%d", &prev) != 1) {
        fclose(fp);
        return 1; // Empty file considered as sorted
    }

    while (fscanf(fp, "%d", &curr) == 1) {
        if (curr < prev) {
            fclose(fp);
            return 0;
        }
        prev = curr;
    }

    fclose(fp);
    return 1;
}

void mergeRuns(const char *run1, const char *run2, const char *outputFile) {
    FILE *r1 = fopen(run1, "r");
    FILE *r2 = fopen(run2, "r");
    FILE *out = fopen(outputFile, "w");
    int num1, num2;
    int end1 = 0, end2 = 0;

    if (!r1 || !r2 || !out) {
        printf("Error opening files for merging!\n");
        exit(1);
    }

    if (fscanf(r1, "%d", &num1) != 1) end1 = 1;
    if (fscanf(r2, "%d", &num2) != 1) end2 = 1;

    while (!end1 && !end2) {
        if (num1 <= num2) {
            fprintf(out, "%d ", num1);
            if (fscanf(r1, "%d", &num1) != 1) end1 = 1;
        } else {
            fprintf(out, "%d ", num2);
            if (fscanf(r2, "%d", &num2) != 1) end2 = 1;
        }
    }

    while (!end1) {
        fprintf(out, "%d ", num1);
        if (fscanf(r1, "%d", &num1) != 1) end1 = 1;
    }

    while (!end2) {
        fprintf(out, "%d ", num2);
        if (fscanf(r2, "%d", &num2) != 1) end2 = 1;
    }

    fclose(r1);
    fclose(r2);
    fclose(out);
}

void displayFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    int num;

    if (!fp) {
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
    const char *inputFile = "input.txt";
    const char *run1 = "run1.txt";
    const char *run2 = "run2.txt";
    const char *outputFile = "sorted.txt";

    while (!isSingleRun(inputFile)) {
        splitIntoRuns(inputFile, run1, run2);
        mergeRuns(run1, run2, outputFile);

        // Update input for next pass
        FILE *src = fopen(outputFile, "r");
        FILE *dst = fopen(inputFile, "w");
        int num;
        while (fscanf(src, "%d", &num) == 1) {
            fprintf(dst, "%d ", num);
        }
        fclose(src);
        fclose(dst);
    }

    printf("Sorting completed!\n");
    displayFile(outputFile);

    return 0;
}
