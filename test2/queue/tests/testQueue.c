#include "../include/queue.h"
#include <stdio.h>

void testEmptyQueueDequeue()
{
    Queue q = { NULL, NULL };
    int value;
    int result = dequeue(&q, &value);

    if (result != -1)
        printf("FAIL testEmptyQueueDequeue: expected -1, got %d\n", result);
    else
        printf("PASS testEmptyQueueDequeue\n");
}

void testEnqueueDequeueSingle()
{
    Queue q = { NULL, NULL };
    int value;

    if (enqueue(&q, 20) != 0)
        printf("FAIL testEnqueueDequeueSingle: enqueue failed\n");
    if (dequeue(&q, &value) != 0)
        printf("FAIL testEnqueueDequeueSingle: dequeue failed\n");

    if (value != 20)
        printf("FAIL testEnqueueDequeueSingle: expected 20, got %d\n", value);
    else
        printf("PASS testEnqueueDequeueSingle\n");

    queueClear(&q);
}

void testFIFOOrder()
{
    Queue q = { NULL, NULL };
    int value;

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    dequeue(&q, &value);
    if (value != 1)
        printf("FAIL testFIFOOrder[1]: expected 1, got %d\n", value);

    dequeue(&q, &value);
    if (value != 2)
        printf("FAIL testFIFOOrder[2]: expected 2, got %d\n", value);

    dequeue(&q, &value);
    if (value != 3)
        printf("FAIL testFIFOOrder[3]: expected 3, got %d\n", value);
    else
        printf("PASS testFIFOOrder\n");

    queueClear(&q);
}

void testReverseInvariant()
{
    Queue q = { NULL, NULL };
    int value;

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    dequeue(&q, &value);
    dequeue(&q, &value);
    dequeue(&q, &value);

    if (value != 3)
        printf("FAIL testReverseInvariant: expected 3, got %d\n", value);
    else
        printf("PASS testReverseInvariant\n");

    queueClear(&q);
}

#ifdef TEST_MAIN
int main()
{
    testEmptyQueueDequeue();
    testEnqueueDequeueSingle();
    testFIFOOrder();
    testReverseInvariant();
    printf("All tests completed\n");
    return 0;
}
#endif
