#include <stdio.h>
extern void insertionSort(int *changeArr, int size);

int compareArrays(int *arr1, int *arr2, int size);
int fillArray(int *arr);

int main() {
    int changeArr[100];
    int origArr[100];

    int elNumber = fillArray(changeArr);

    for (int i = 0; i < elNumber; i++)
        origArr[i] = changeArr[i];

    insertionSort(changeArr, elNumber);
    int changeCount = compareArrays(origArr, changeArr, elNumber);

    return changeCount;
}

int compareArrays(int *arr1, int *arr2, int size) {
    int changes = 0;
    for (int i = 0; i < size; i++)
        if (arr1[i] != arr2[i])
            changes++;

    return changes;
}

int fillArray(int *arr) {
    int count = 0;
    printf("Enter numbers:\n");

    do {
        scanf("%d", &arr[count++]);
    } while (getchar() != '\n' && count < 100);

    return count;
}

