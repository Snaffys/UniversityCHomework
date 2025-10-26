#pragma once

typedef struct SortedList {
    int data;
    struct SortedList *next;
} SortedList;

/**
 * @brief Add element to list
 * @param data Integer to add
 * @param head Pointer to pointer of list head
 * @return -1 if couldn't allocate memory, 0 otherwise
 */
int addToList(int data, SortedList **head);

/**
 * @brief Remove element from list
 * @param data Integer to remove
 * @param head Pointer to pointer of list head
 * @return -1 if couldn't find element, 0 otherwise
 */
int removeFormList(int data, SortedList **head);

/**
 * @brief Print list data
 * @param head Pointer to list head
 */
void printList(SortedList *head);

/**
 * @brief Free list data
 * @param head Pointer to list head
 */
void freeList(SortedList *head);

