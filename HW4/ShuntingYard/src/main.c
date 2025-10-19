#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct OperationStack {
    char operation;
    struct OperationStack *next;
} OperationStack;

int pushToStack(char operation, OperationStack **head);
char popFromStack(OperationStack **head);
void freeStack(OperationStack *head);

typedef struct OutputQueue {
    char token;
    struct OutputQueue *next;
} OutputQueue;

int pushToQueue(char token, OutputQueue **head, OutputQueue **tail);
void printQueue(OutputQueue *head);
void freeQueue(OutputQueue *head);

int getPrecedence(char operation);
void shuntingYard(const char *expression);

int main() {
    shuntingYard("1 + 1");
    shuntingYard("(1 + 1) * 2");
    shuntingYard("1 + 1 * 2");
    shuntingYard("3 + 4 * 2 / (1 - 5)");
    shuntingYard("1 + 2 + (3 + 4)");
    return 0;
}

int pushToStack(char operation, OperationStack **head) {
    OperationStack *newOperation =
        (OperationStack *)malloc(sizeof(OperationStack));
    if (newOperation == NULL)
        return -1;
    else {
        newOperation->operation = operation;
        newOperation->next = *head;
        *head = newOperation;
        return 0;
    }
}

char popFromStack(OperationStack **head) {
    if (*head == NULL)
        return '\0';

    OperationStack *lastEl = *head;
    char lastElOperation = lastEl->operation;
    *head = (*head)->next;
    free(lastEl);
    return lastElOperation;
}

void freeStack(OperationStack *head) {
    OperationStack *current = head;
    while (current != NULL) {
        OperationStack *next = current->next;
        free(current);
        current = next;
    }
}

int pushToQueue(char token, OutputQueue **head, OutputQueue **tail) {
    OutputQueue *newQueueToken = (OutputQueue *)malloc(sizeof(OutputQueue));
    if (newQueueToken == NULL)
        return -1;

    newQueueToken->token = token;
    newQueueToken->next = NULL;

    if (*head == NULL) {
        *head = newQueueToken;
        *tail = newQueueToken;
    } else {
        (*tail)->next = newQueueToken;
        *tail = newQueueToken;
    }
    return 0;
}

void printQueue(OutputQueue *head) {
    while (head != NULL) {
        printf("%c ", head->token);
        head = head->next;
    }
    printf("\n");
}

void freeQueue(OutputQueue *head) {
    OutputQueue *current = head;
    while (current != NULL) {
        OutputQueue *next = current->next;
        free(current);
        current = next;
    }
}

int getPrecedence(char operation) {
    if (operation == '/' || operation == '*')
        return 1;
    else if (operation == '-' || operation == '+')
        return 0;
    else
        return -1;
}

void shuntingYard(const char *expression) {
    OperationStack *stackHead = NULL;
    OutputQueue *queueHead = NULL;
    OutputQueue *queueTail = NULL;
    int errorCode = 0;

    for (int i = 0; expression[i] != '\0'; ++i) {
        char currChar = expression[i];

        if (isdigit(currChar)) {
            errorCode = pushToQueue(currChar, &queueHead, &queueTail);
            if (errorCode == -1) {
                printf("Error: couldn't allocate memory\n");
                freeQueue(queueHead);
                freeStack(stackHead);
                return;
            }
        } else if (currChar == '+' || currChar == '-' || currChar == '*' ||
                   currChar == '/') {
            while (stackHead != NULL &&
                   getPrecedence(currChar) <=
                       getPrecedence(stackHead->operation)) {
                char lastStackOp = popFromStack(&stackHead);
                if (lastStackOp == '\0') {
                    printf("Error: trying to put empty operation into queue\n");
                    freeQueue(queueHead);
                    freeStack(stackHead);
                    return;
                }
                errorCode = pushToQueue(lastStackOp, &queueHead, &queueTail);
                if (errorCode == -1) {
                    printf("Error: couldn't allocate memory\n");
                    freeQueue(queueHead);
                    freeStack(stackHead);
                    return;
                }
            }
            errorCode = pushToStack(currChar, &stackHead);
            if (errorCode == -1) {
                printf("Error: couldn't allocate memory\n");
                freeQueue(queueHead);
                freeStack(stackHead);
                return;
            }
        } else if (currChar == '(') {
            errorCode = pushToStack(currChar, &stackHead);
            if (errorCode == -1) {
                printf("Error: couldn't allocate memory\n");
                freeQueue(queueHead);
                freeStack(stackHead);
                return;
            }
        } else if (currChar == ')') {
            while (stackHead != NULL && stackHead->operation != '(') {
                char lastStackOp = popFromStack(&stackHead);
                if (lastStackOp == '\0') {
                    printf("Error: trying to put empty operation into queue\n");
                    freeQueue(queueHead);
                    freeStack(stackHead);
                    return;
                }
                errorCode = pushToQueue(lastStackOp, &queueHead, &queueTail);
                if (errorCode == -1) {
                    printf("Error: couldn't allocate memory\n");
                    freeQueue(queueHead);
                    freeStack(stackHead);
                    return;
                }
            }
            if (popFromStack(&stackHead) != '(') {
                printf("Error: mismatched parentheses\n");
                freeQueue(queueHead);
                freeStack(stackHead);
                return;
            }
        } else if (currChar != ' ') {
            printf("Error: wrong math expression\n");
            freeQueue(queueHead);
            freeStack(stackHead);
            return;
        }
    }
    while (stackHead != NULL) {
        char lastStackOp = popFromStack(&stackHead);
        if (lastStackOp == '\0') {
            printf("Error: trying to put empty operation into queue\n");
            freeQueue(queueHead);
            freeStack(stackHead);
            return;
        }
        errorCode = pushToQueue(lastStackOp, &queueHead, &queueTail);
        if (errorCode == -1) {
            printf("Error: couldn't allocate memory\n");
            freeQueue(queueHead);
            freeStack(stackHead);
            return;
        }
    }

    printQueue(queueHead);
    freeQueue(queueHead);
    freeStack(stackHead);
    return;
}

