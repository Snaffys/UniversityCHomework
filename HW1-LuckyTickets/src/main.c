#include <stdio.h>

int getLuckyTicketsAmount(int sumOfNumbers) {
    int ticketsAmount = 1000000;
    int count = 0;

    for (int i = 0; i < ticketsAmount; i++) {
        int sum1 = 0, sum2 = 0;
        int currTicket = i;

        for (int j = 0; j < 3; j++) {
            sum1 += currTicket % 10;
            currTicket /= 10;
        }
        for (int j = 0; j < 3; j++) {
            sum2 += currTicket % 10;
            currTicket /= 10;
        }

        if (sum1 == sumOfNumbers && sum2 == sumOfNumbers)
            count++;
    }
    return count;
}

int main() {
    const int sumOfNumbers = 12;
    printf("%d", getLuckyTicketsAmount(sumOfNumbers));
    return 0;
}

