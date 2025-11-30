#include "../include/logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int assertInt(const char* name, int got, int expected)
{
    if (got != expected) {
        printf("Failed %s: got: %d, expected: %d\n", name, got, expected);
        return 0;
    }
    printf("Passed %s\n", name);
    return 1;
}

int assertStr(const char* name, const char* got, const char* expected)
{
    if (strcmp(got, expected) != 0) {
        printf("Failed %s: got: %s, expected: %s\n", name, got, expected);
        return 0;
    }
    printf("Passed %s\n", name);
    return 1;
}

void testToTwosComplementPositive()
{
    char* b = toTwosComplement(5);
    char expected[BITS_NUM + 1];
    for (int i = 0; i < BITS_NUM; ++i)
        expected[i] = '0';
    expected[BITS_NUM - 3] = '1';
    expected[BITS_NUM - 1] = '1';
    expected[BITS_NUM] = '\0';
    assertStr("toTwosComplement(5)", b, expected);
    free(b);
}

void testToTwosComplementNegative()
{
    char* b = toTwosComplement(-1);
    char expected[BITS_NUM + 1];
    for (int i = 0; i < BITS_NUM; ++i)
        expected[i] = '1';
    expected[BITS_NUM] = '\0';
    assertStr("toTwosComplement(-1)", b, expected);
    free(b);
}

void testBinaryAdditionPositive()
{
    char* a = toTwosComplement(5);
    char* b = toTwosComplement(7);
    char* sum = binaryAddition(a, b);
    int dec = toDecimal(sum);
    assertInt("binaryAddition(5+7)", dec, 12);
    free(a);
    free(b);
    free(sum);
}

void testBinaryAdditionNegative()
{
    char* a = toTwosComplement(-5);
    char* b = toTwosComplement(1);
    char* sum = binaryAddition(a, b);
    int dec = toDecimal(sum);
    assertInt("binaryAddition(-5+1)", dec, -4);
    free(a);
    free(b);
    free(sum);
}

void testToDecimalZero()
{
    char* a = toTwosComplement(0);
    int dec = toDecimal(a);
    assertInt("toDecimal(0)", dec, 0);
    free(a);
}

void testToDecimalNegative()
{
    char* a = toTwosComplement(-1);
    int dec = toDecimal(a);
    assertInt("toDecimal(-1)", dec, -1);
    free(a);
}

void runTests()
{
    testToTwosComplementPositive();
    testToTwosComplementNegative();
    testBinaryAdditionPositive();
    testBinaryAdditionNegative();
    testToDecimalZero();
    testToDecimalNegative();
    printf("All tests finished.\n");
}

#ifdef TEST_MAIN
int main()
{
    runTests();
    return 0;
}
#endif
