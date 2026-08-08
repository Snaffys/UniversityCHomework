#pragma once

typedef struct List {
    int value;
    struct List* next;
} List;

List* listPush(int value, List* list);
List* listReverse(List* list);
void listFree(List* list);
int listIsEmpty(List* list);

typedef struct Queue {
    List* front;
    List* rear;
} Queue;

int queueCheck(Queue* q);
int enqueue(Queue* q, int value);
int dequeue(Queue* q, int* value);
void queueClear(Queue* q);
