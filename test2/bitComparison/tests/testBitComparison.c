#include "../include/bitComparison.h"
#include <stdbool.h>
#include <stdio.h>

void testGreater()
{
    bool arr1[] = { 1, 0, 1 };
    bool arr2[] = { 0, 1, 1 };
    int result = compareBinaryArrays(arr1, 3, arr2, 3);
    if (result != 1)
        printf("FAIL testGreater: expected 1, got %d\n", result);
    else
        printf("PASS testGreater\n");
}

void testEqualWithLeadingZeros()
{
    bool arr1[] = { 0, 0, 1 };
    bool arr2[] = { 1 };
    int result = compareBinaryArrays(arr1, 3, arr2, 1);
    if (result != 0)
        printf("FAIL testEqualWithLeadingZeros: expected 0, got %d\n", result);
    else
        printf("PASS testEqualWithLeadingZeros\n");
}

void testDifferentLengths()
{
    bool arr1[] = { 1, 0, 0, 0 };
    bool arr2[] = { 1, 1, 1 };
    int result = compareBinaryArrays(arr1, 4, arr2, 3);
    if (result != 1)
        printf("FAIL testDifferentLengths: expected 1, got %d\n", result);
    else
        printf("PASS testDifferentLengths\n");
}

void testZeros()
{
    bool arr1[] = { 0 };
    bool arr2[] = { 0, 0, 0 };
    int result = compareBinaryArrays(arr1, 1, arr2, 3);
    if (result != 0)
        printf("FAIL testZeros: expected 0, got %d\n", result);
    else
        printf("PASS testZeros\n");
}

void testLargeNumbers()
{
    bool arr1[] = { 1, 1, 0, 1, 1, 0, 1 };
    bool arr2[] = { 1, 1, 0, 1, 1, 0, 0 };
    int result = compareBinaryArrays(arr1, 7, arr2, 7);
    if (result != 1)
        printf("FAIL testLargeNumbers: expected 1, got %d\n", result);
    else
        printf("PASS testLargeNumbers\n");
}

#ifdef TEST_MAIN
int main()
{
    testGreater();
    testEqualWithLeadingZeros();
    testDifferentLengths();
    testZeros();
    testLargeNumbers();
    printf("All tests passed\n");
    return 0;
}
#endif
