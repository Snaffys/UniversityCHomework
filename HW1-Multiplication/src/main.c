#include <stdio.h>

int multiplication(int x) {
    int xPow = x * x;
    return (xPow + 1) * (xPow + x) + 1;
}
