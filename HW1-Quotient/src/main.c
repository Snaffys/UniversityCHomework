#include <stdio.h>

int findQuotient(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0;
    }

    int sign = 1;
    if ((a < 0 && b > 0) || (a > 0 && b < 0))
        sign = -sign;

    int bAbs = (b < 0) ? -b : b;
    int q = 0;

    while ((((a < 0) ? -a : a)) > bAbs || a < 0) {
        a = a - b * sign;
        q++;
    }

    return q * sign;
}

int main() {
    printf("%d\n", findQuotient(-7, -2));
    printf("%d\n", findQuotient(7, 2));
    printf("%d\n", findQuotient(-7, 2));
    printf("%d\n", findQuotient(7, -2));
    printf("%d\n", findQuotient(-2, 2));
    printf("%d\n", findQuotient(2, 7));
    return 0;
}
