#include "../include/logic.h"
#include <stdio.h>
#include <stdlib.h>

const int BITS_NUM = sizeof(int) * 8;

char* toTwosComplement(const int num)
{
    char* binaryStr = (char*)malloc(BITS_NUM + 1);
    unsigned int mask = 1 << (BITS_NUM - 1);

    unsigned int uNum = (unsigned int)num;

    for (int i = 0; i < BITS_NUM; ++i) {
        binaryStr[i] = (uNum & mask) ? '1' : '0';
        mask >>= 1;
    }
    binaryStr[BITS_NUM] = '\0';

    return binaryStr;
}

void printBinary(const char* binaryStr)
{
    for (int i = 0; i < BITS_NUM; ++i) {
        printf("%c", binaryStr[i]);
        if ((i + 1) % 8 == 0 && i != BITS_NUM - 1)
            printf(" ");
    }
    printf("\n");
}

char* binaryAddition(const char* firstBin, const char* secBin)
{
    char* binaryStr = (char*)malloc(BITS_NUM + 1);

    int carry = 0;
    for (int i = BITS_NUM - 1; i >= 0; --i) {
        int firstBit = firstBin[i] - '0';
        int secBit = secBin[i] - '0';

        int sum = firstBit + secBit + carry;
        binaryStr[i] = (sum % 2) + '0';
        carry = sum / 2;
    }
    binaryStr[BITS_NUM] = '\0';

    return binaryStr;
}

int toDecimal(const char* binaryStr)
{
    unsigned int decimal = 0;

    for (int i = 0; i < BITS_NUM; ++i)
        decimal = (decimal << 1) | (binaryStr[i] - '0');

    return (int)decimal;
}
