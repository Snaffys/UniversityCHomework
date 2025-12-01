#include "include/bitComparison.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    bool num1[] = { 0, 1, 0, 1, 1, 0, 0 };
    bool num2[] = { 1, 1, 0, 0, 1, 1 };

    int len1 = sizeof(num1) / sizeof(num1[0]);
    int len2 = sizeof(num2) / sizeof(num2[0]);

    int result = compareBinaryArrays(num1, len1, num2, len2);

    printf("Number 1: ");
    for (int i = 0; i < len1; ++i)
        printf("%d", num1[i]);
    printf("\nNumber 2: ");
    for (int i = 0; i < len2; ++i)
        printf("%d", num2[i]);

    printf("\n\nResult: ");
    if (result == 1)
        printf("Number 1 > Number 2\n");
    else if (result == -1)
        printf("Number 1 < Number 2\n");
    else
        printf("Number 1 == Number 2\n");

    return 0;
}
