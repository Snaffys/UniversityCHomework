#include "include/doubleToExponential.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    double number;
    printf("Enter a number: ");

    if (scanf("%lf", &number) != 1) {
        printf("Invalid input!\n");
        return 1;
    }

    char* result = doubleToExponential(number);
    printf("Result: %s\n", result);
    free(result);

    return 0;
}
