#include <stdio.h>

int multiplication(int x) {
    int xPow = x * x;
    return (xPow + 1) * (xPow + x) + 1;
}

int main() {
    printf("%d", multiplication(2));
    return 0;
}
