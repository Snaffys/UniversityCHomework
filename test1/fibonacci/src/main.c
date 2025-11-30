#include <stdio.h>

int fibonacciDigit(int n);

int main() {
    printf("%d\n", fibonacciDigit(7));
    printf("%d\n", fibonacciDigit(11));

    return 0;
}

int fibonacciDigit(int n) {
    if (n <= 0)
        return -1;
    if (n == 1 || n == 2)
        return 1;

    int currentPos = 2;
    long long a = 1, b = 1;

    while (currentPos < n) {
        long long next = a + b;
        a = b;
        b = next;

        long long temp = next;
        int numDigits = 0;
        while (temp > 0) {
            numDigits++;
            temp /= 10;
        }

        if (currentPos + numDigits >= n) {
            int leftSpace = n - currentPos - 1;
            long long divisor = 1;

            for (int i = 0; i < numDigits - leftSpace - 1; i++) {
                divisor *= 10;
            }

            return (int)((next / divisor) % 10);
        }

        currentPos += numDigits;
    }

    return -1;
}
