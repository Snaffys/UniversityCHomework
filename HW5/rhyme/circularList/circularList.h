#pragma once

typedef struct CircularList {
    int data;
    struct CircularList *next;
} CircularList;

/**
 * @brief Add element to list
 * @param data Integer to add
 * @param head Pointer to pointer of list head
 * @return -1 if couldn't allocate memory, 0 otherwise
 */
int addToList(int data, CircularList **head);

/**
 * @brief Remove element from list
 * @param data Integer to remove
 * @param head Pointer to pointer of list head
 * @return -1 if couldn't find element, 0 otherwise
 */
int removeFromList(int data, CircularList **head);

/**
 * @brief Free list data
 * @param head Pointer to list head
 */
void freeList(CircularList *head);

