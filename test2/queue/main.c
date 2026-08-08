#include "include/queue.h"
#include <stdio.h>

int main()
{
    Queue q = { NULL, NULL };

    int values[] = { 1, 2, 3, 4, 5, 6 };
    for (int i = 0; i < (int)(sizeof(values) / sizeof(values[0])); ++i) {
        if (enqueue(&q, values[i]) == -1) {
            printf("enqueue error\n");
            queueClear(&q);
            return 1;
        }
    }

    int value;
    while (dequeue(&q, &value) == 0)
        printf("%d\n", value);

    queueClear(&q);

    return 0;
}
