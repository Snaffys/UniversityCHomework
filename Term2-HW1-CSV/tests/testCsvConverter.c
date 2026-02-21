#include "../include/csvConverter.h"

void testIsDoubleValidInteger()
{
    int result = isDouble("123");
    if (result != 1)
        printf("FAIL testIsDoubleValidInteger: expected 1, got %d\n", result);
    else
        printf("PASS testIsDoubleValidInteger\n");
}

void testIsDoubleValidDecimal()
{
    int result = isDouble("12.34");
    if (result != 1)
        printf("FAIL testIsDoubleValidDecimal: expected 1, got %d\n", result);
    else
        printf("PASS testIsDoubleValidDecimal\n");
}

void testIsDoubleScientific()
{
    int result = isDouble("5e12");
    if (result != 1)
        printf("FAIL testIsDoubleScientific: expected 1, got %d\n", result);
    else
        printf("PASS testIsDoubleScientific\n");
}

void testIsDoubleInvalid()
{
    int result = isDouble("abc");
    if (result != 0)
        printf("FAIL testIsDoubleInvalid: expected 0, got %d\n", result);
    else
        printf("PASS testIsDoubleInvalid\n");
}

void testIsDoubleEmpty()
{
    int result = isDouble("");
    if (result != 0)
        printf("FAIL testIsDoubleEmpty: expected 0, got %d\n", result);
    else
        printf("PASS testIsDoubleEmpty\n");
}

void testTrimCsvField()
{
    char str[] = "\"Test\"";
    int len = trimCsvField(str);

    if (strcmp(str, "Test") != 0 || len != 4)
        printf("FAIL testTrimCsvFieldSimple: expected \"Test\" (len 4), got \"%s\" (len %d)\n", str, len);
    else
        printf("PASS testTrimCsvFieldSimple\n");
}

void testGetTrimmedLenQuoted()
{
    int result = getTrimmedLen("\"Test\"", 6);
    if (result != 4)
        printf("FAIL testGetTrimmedLenQuoted: expected 4, got %d\n", result);
    else
        printf("PASS testGetTrimmedLenQuoted\n");
}

void testGetTrimmedLenUnquoted()
{
    int result = getTrimmedLen("test", 4);
    if (result != 4)
        printf("FAIL testGetTrimmedLenUnquoted: expected 4, got %d\n", result);
    else
        printf("PASS testGetTrimmedLenUnquoted\n");
}

#ifdef TEST_MAIN
int main()
{
    testIsDoubleValidInteger();
    testIsDoubleValidDecimal();
    testIsDoubleScientific();
    testIsDoubleInvalid();
    testIsDoubleEmpty();
    testTrimCsvField();
    testGetTrimmedLenQuoted();
    testGetTrimmedLenUnquoted();

    printf("All tests executed\n");
    return 0;
}
#endif
