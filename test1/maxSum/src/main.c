#include <stdio.h>

void printMax(int *numbers, const int size);

int binaryDigitSum(int num);

int main() {
    int numbers[] = {15, 7, 3, 31, 63, 1, 255, 127, 85};
    const int size = sizeof(numbers) / sizeof(numbers[0]);

    printMax(numbers, size);

    return 0;
}

void printMax(int *numbers, const int size) {
    int maxSum = -1;
    int maxNumbers[size];
    int count = 0;

    for (int i = 0; i < size; i++) {
        int currentSum = binaryDigitSum(numbers[i]);

        if (currentSum > maxSum) {
            maxSum = currentSum;
            count = 0;
            maxNumbers[count++] = numbers[i];
        } else if (currentSum == maxSum)
            maxNumbers[count++] = numbers[i];
    }

    for (int i = 0; i < count; i++)
        printf("%d ", maxNumbers[i]);
    printf("\n");
}

int binaryDigitSum(int num) {
    int sum = 0;

    if (num < 0)
        num = -num;

    while (num > 0) {
        sum += num % 2;
        num = num / 2;
    }

    return sum;
}

