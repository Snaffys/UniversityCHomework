#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int pushToStack(char data, Stack **head) {
    Stack *newNode =
        (Stack *)malloc(sizeof(Stack));
    if (newNode == NULL)
        return -1;
    else {
        newNode->data = data;
        newNode->next = *head;
        *head = newNode;
        return 0;
    }
}

char popFromStack(Stack **head) {
    if (*head == NULL)
        return '\0';

    Stack *lastNode = *head;
    char lastNodeData = lastNode->data;
    *head = (*head)->next;
    free(lastNode);
    return lastNodeData;
}

void freeStack(Stack *head) {
    Stack *current = head;
    while (current != NULL) {
        Stack *next = current->next;
        free(current);
        current = next;
    }
}

