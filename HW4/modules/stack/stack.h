#pragma once

typedef struct Stack {
    char data;
    struct Stack *next;
} Stack;

/**
 * @brief Push element to stack
 * @param data Character to push
 * @param head Pointer to pointer of stack head
 * @return -1 if couldn't allocate memory, 0 otherwise
 */
int pushToStack(char data, Stack **head);

/**
 * @brief Pop element from stack
 * @param head Pointer to pointer of stack head
 * @return Popped character or '\0' if stack is empty
 */
char popFromStack(Stack **head);

/**
 * @brief Free all stack memory
 * @param head Pointer to stack head
 */
void freeStack(Stack *head);

