#include "../include/queue.h"
#include <stdlib.h>

List* listPush(int value, List* list)
{
    List* newNode = (List*)malloc(sizeof(List));
    if (!newNode)
        return NULL;

    newNode->value = value;
    newNode->next = list;
    return newNode;
}

List* listReverse(List* list)
{
    List* result = NULL;
    List* current = list;

    while (current) {
        List* newResult = listPush(current->value, result);
        if (!newResult) {
            listFree(result);
            return NULL;
        }
        result = newResult;
        current = current->next;
    }
    return result;
}

void listFree(List* list)
{
    while (list) {
        List* next = list->next;
        free(list);
        list = next;
    }
}

int listIsEmpty(List* list)
{
    return list == NULL;
}

int queueCheck(Queue* q)
{
    if (listIsEmpty(q->front) && !listIsEmpty(q->rear)) {
        List* newFront = listReverse(q->rear);
        if (!newFront)
            return -1;

        listFree(q->rear);
        q->rear = NULL;
        q->front = newFront;
    }
    return 0;
}

int enqueue(Queue* q, int value)
{
    List* newRear = listPush(value, q->rear);
    if (!newRear)
        return -1;

    q->rear = newRear;

    return queueCheck(q);
}

int dequeue(Queue* q, int* value)
{
    if (listIsEmpty(q->front)) {
        if (listIsEmpty(q->rear))
            return -1;

        if (queueCheck(q) == -1)
            return -1;
    }

    *value = q->front->value;
    List* oldFront = q->front;
    q->front = q->front->next;
    free(oldFront);

    return 0;
}

void queueClear(Queue* q)
{
    listFree(q->front);
    listFree(q->rear);
    q->front = NULL;
    q->rear = NULL;
}
