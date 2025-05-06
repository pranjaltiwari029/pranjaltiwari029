#include <stdio.h>

// A utility function to get the maximum value in arr[]
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// A function to do counting sort based on a specific digit (exp is 1, 10, 100, etc.)
void countSort(int arr[], int n, int exp) {
    int output[n]; // output array
    int count[10] = {0};

    // Store count of occurrences
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that it contains actual position
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output array back to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] using Radix Sort
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);

    // Do counting sort for every digit (exp = 1, 10, 100, ...)
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main() {
    int n;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    
    printf("Enter %d non-negative integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    radixSort(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
