#include <stdbool.h>
#include <stdio.h>

int countSubstrings(char *string, char *substring) {
    int subCounter = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == substring[0]) {
            bool substringInString = true;
            for (int j = 0; substring[j] != '\0'; j++) {
                if (string[i + j] == '\0' || string[i + j] != substring[j]) {
                    substringInString = false;
                    break;
                }
            }
            if (substringInString)
                subCounter++;
        }
    }
    return subCounter;
}

int main() {
    printf("%d\n", countSubstrings("afkleowqna1h1h11njsdEIor1hNLS31h", "1h"));
    return 0;
}

