#include "include/logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int firstNum, secNum;
    printf("First number = ");
    if (scanf("%d", &firstNum) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Second number = ");
    if (scanf("%d", &secNum) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    char* firstBin = toTwosComplement(firstNum);
    char* secBin = toTwosComplement(secNum);
    printf("First binary:\n");
    printBinary(firstBin);
    printf("Second binary:\n");
    printBinary(secBin);

    char* addition = binaryAddition(firstBin, secBin);
    printf("Addition:\n");
    printBinary(addition);

    int decimal = toDecimal(addition);
    printf("Decimal:\n%d", decimal);

    free(firstBin);
    free(secBin);
    free(addition);

    return 0;
}
