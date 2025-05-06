#include <stdio.h>

void countSort(int arr[], int n) {
    int i;
    
    // Find the maximum element in the array
    int max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // Create a count array to store count of individual elements
    int count[max + 1];
    
    // Initialize count array with 0
    for (i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Store the count of each element
    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Modify the original array using the count array
    int index = 0;
    for (i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
}

int main() {
    int n, i;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    
    printf("Enter %d non-negative integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    countSort(arr, n);

    printf("Sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
