#include <stdio.h>

int multiplication(int x) {
    int xPow = x * x;
    return (xPow + 1) * (xPow + x) + 1;
}
<<<<<<< HEAD
=======

int main() {
    printf("%d", multiplication(2));
    return 0;
}
>>>>>>> d954746 (add multiplication algorithm)
