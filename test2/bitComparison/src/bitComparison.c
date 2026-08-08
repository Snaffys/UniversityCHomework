#include "../include/bitComparison.h"

int compareBinaryArrays(const bool* arr1, int len1, const bool* arr2, int len2)
{
    int i = 0, j = 0;
    while (i < len1 && !arr1[i])
        ++i;
    while (j < len2 && !arr2[j])
        ++j;
    int realLen1 = len1 - i;
    int realLen2 = len2 - j;

    if (realLen1 != realLen2)
        return (realLen1 > realLen2) ? 1 : -1;

    for (int k = 0; k < realLen1; ++k) {
        if (arr1[i + k] ^ arr2[j + k])
            return arr1[i + k] ? 1 : -1;
    }

    return 0;
}
