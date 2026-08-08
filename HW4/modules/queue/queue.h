#pragma once

typedef struct Queue {
    char data;
    struct Queue *next;
} Queue;

/**
 * @brief Push element to queue
 * @param data Character to push
 * @param head Pointer to pointer of queue head
 * @param tail Pointer to pointer of queue tail
 * @return -1 if couldn't allocate memory, 0 otherwise
 */
int pushToQueue(char data, Queue **head, Queue **tail);

/**
 * @brief Print all elements in queue
 * @param head Pointer to queue head
 */
void printQueue(Queue *head);

/**
 * @brief Free all queue memory
 * @param head Pointer to queue head
 */
void freeQueue(Queue *head);

