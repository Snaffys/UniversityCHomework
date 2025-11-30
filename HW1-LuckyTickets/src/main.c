#include <stdio.h>

int getLuckyTicketsAmount() {
    const int combinationsPossible = 28;

    int sumArr[combinationsPossible] = {0};

    for (int s = 0; s < combinationsPossible; ++s) {
        int count = 0;

        for (int firstNum = 0; firstNum <= 9; ++firstNum) {
            int remaining = s - firstNum;
            if (remaining < 0)
                break;
            if (remaining <= 18)
                count += (remaining <= 9) ? (remaining + 1) : (19 - remaining);
        }

        sumArr[s] = count;
    }

    int totalLucky = 0;
    for (int i = 0; i < combinationsPossible; ++i)
        totalLucky += sumArr[i] * sumArr[i];

    return totalLucky;
}

int main() {
    printf("%d", getLuckyTicketsAmount());
    return 0;
}
