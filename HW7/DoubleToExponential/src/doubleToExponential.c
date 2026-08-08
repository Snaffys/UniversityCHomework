#include "../include/doubleToExponential.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    double value;
    struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        uint64_t mantissa : 52;
        uint64_t exponent : 11;
        uint64_t sign : 1;
#else
        uint64_t sign : 1;
        uint64_t exponent : 11;
        uint64_t mantissa : 52;
#endif
    } parts;
} DoubleUnion;

char* doubleToExponential(double num) {
    DoubleUnion du;
    du.value = num;

    int sign = du.parts.sign;
    int codedExponent = du.parts.exponent;
    uint64_t mantissa = du.parts.mantissa;

    if (codedExponent == 0 && mantissa == 0) {
        char *result = malloc(9);
        sprintf(result, "%c0.0*2^0", sign ? '-' : '+');
        return result;
    }

    int exponent;
    double normalizedMantissa;

    if (codedExponent == 0) {
        // denormalized numbers
        exponent = -1022;
        normalizedMantissa = (double)mantissa / (1ULL << 52);
    }
    else {
        // normalized numbers
        exponent = codedExponent - 1023;
        normalizedMantissa = 1.0 + (double)mantissa / (1ULL << 52);
    }

    char* result = malloc(100);
    sprintf(result, "%c%.20g*2^%d", sign ? '-' : '+', normalizedMantissa, exponent);
    return result;
}
