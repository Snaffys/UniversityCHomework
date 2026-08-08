#include "../include/doubleToExponential.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int assertOutput(const char* testName, double input, const char* expected) {
    char* result = doubleToExponential(input);

    if (strcmp(result, expected) == 0) {
        printf("Passed %s\n", testName);
        free(result);
        return 1;
    }
    else {
        printf("Failed %s: got: %s, expected: %s\n", testName, result, expected);
        free(result);
        return 0;
    }
}

void testZero() {
    printf("Zero values:\n");
    assertOutput("positive zero", 0.0, "+0.0*2^0");
    assertOutput("negative zero", -0.0, "-0.0*2^0");
}

void testPowersOfTwo() {
    printf("Powers of two:\n");
    assertOutput("2^-1", 0.5, "+1*2^-1");
    assertOutput("2^0", 1.0, "+1*2^0");
    assertOutput("2^1", 2.0, "+1*2^1");
    assertOutput("2^2", 4.0, "+1*2^2");
    assertOutput("2^3", 8.0, "+1*2^3");
    assertOutput("2^4", 16.0, "+1*2^4");
    assertOutput("2^5", 32.0, "+1*2^5");
    assertOutput("negative power", -4.0, "-1*2^2");
}

void testKnownValues() {
    printf("Known values:\n");
    assertOutput("negative decimal", -2.5, "-1.25*2^1");
    assertOutput("positive decimal", 10.0, "+1.25*2^3");
}

void runTests() {
    printf("Running tests:\n");

    testZero();
    printf("\n");

    testPowersOfTwo();
    printf("\n");

    testKnownValues();
    printf("\n");

    printf("All tests finished.\n");
}

#ifdef TEST_MAIN
int main()
{
    runTests();
    return 0;
}
#endif
