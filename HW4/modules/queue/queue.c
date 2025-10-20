#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int pushToQueue(char data, Queue **head, Queue **tail) {
    Queue *newQueueNode = (Queue *)malloc(sizeof(Queue));
    if (newQueueNode == NULL)
        return -1;

    newQueueNode->data = data;
    newQueueNode->next = NULL;

    if (*head == NULL) {
        *head = newQueueNode;
        *tail = newQueueNode;
    } else {
        (*tail)->next = newQueueNode;
        *tail = newQueueNode;
    }
    return 0;
}

void printQueue(Queue *head) {
    while (head != NULL) {
        printf("%c ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeQueue(Queue *head) {
    Queue *current = head;
    while (current != NULL) {
        Queue *next = current->next;
        free(current);
        current = next;
    }
}

