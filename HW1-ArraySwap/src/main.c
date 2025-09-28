#include <stdio.h>

void reverseSwap(int *arr, int start, int end);
void printArray(int *arr, int arrSize);

void reverseSwap(int *arr, int start, int end) {
    while (start < end) {
        arr[start] = arr[start] + arr[end];
        arr[end] = arr[start] - arr[end];
        arr[start] = arr[start] - arr[end];
        start++;
        end--;
    }
}

void printArray(int *arr, int arrSize) {
    printf("array: ");
    for (int i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]);
    }
};

int main() {
    int arr[] = {1, -2, 3, 4, -5, 6, 7};
    int m = 3;
    int n = 4;

    reverseSwap(arr, 0, m + n - 1);
    reverseSwap(arr, 0, n - 1);
    reverseSwap(arr, n, m + n - 1);

    printArray(arr, m + n);
    return 0;
}
