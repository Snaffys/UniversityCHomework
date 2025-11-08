#include "circularList.h"
#include <stdio.h>
#include <stdlib.h>

int addToList(int data, CircularList **head) {
    CircularList *newNode = (CircularList *)malloc(sizeof(CircularList));
    if (newNode == NULL)
        return -1;

    newNode->data = data;

    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
        return 0;
    }

    CircularList *current = *head;
    while (current->next != *head)
        current = current->next;
    newNode->next = *head;
    current->next = newNode;
    return 0;
}

int removeFromList(int data, CircularList **head) {
    if (*head == NULL)
        return -1;

    CircularList *current = *head;
    CircularList *prev = NULL;

    do {
        if (current->data == data)
            break;
        prev = current;
        current = current->next;
    } while (current != *head);

    if (current->data != data)
        return -1;

    if (current->next == current) {
        free(current);
        *head = NULL;
        return 0;
    }

    if (current == *head) {
        prev = *head;
        while (prev->next != *head)
            prev = prev->next;
        *head = current->next;
    }

    prev->next = current->next;
    free(current);
    return 0;
}

void freeList(CircularList *head) {
    if (head == NULL)
        return;

    CircularList *last = head;
    while (last->next != head)
        last = last->next;
    last->next = NULL;

    CircularList *current = head;
    while (current != NULL) {
        CircularList *next = current->next;
        free(current);
        current = next;
    }
}

