#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int addToList(int data, SortedList **head) {
    SortedList *newNode = (SortedList *)malloc(sizeof(SortedList));
    if (newNode == NULL)
        return -1;

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL || data <= (*head)->data) {
        newNode->next = *head;
        *head = newNode;
        return 0;
    }

    SortedList *current = *head;
    while (current->next != NULL && current->next->data < data)
        current = current->next;
    newNode->next = current->next;
    current->next = newNode;
    return 0;
}

int removeFromList(int data, SortedList **head) {
    if (*head == NULL)
        return -1;

    SortedList *current = *head;
    SortedList *prev = NULL;

    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return -1;

    if (prev == NULL)
        *head = current->next;
    else
        prev->next = current->next;

    free(current);
    return 0;
}

void printList(SortedList *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    SortedList *current = head;
    printf("List:\n");
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void freeList(SortedList *head) {
    SortedList *current = head;
    while (current != NULL) {
        SortedList *next = current->next;
        free(current);
        current = next;
    }
}

