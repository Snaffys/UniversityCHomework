#include "../../modules/queue/queue.h"
#include "../../modules/stack/stack.h"
#include <ctype.h>
#include <stdio.h>

void shuntingYard(const char *expression);
int getPrecedence(char operation);

int main() {
    shuntingYard("1 + 1");
    shuntingYard("(1 + 1) * 2");
    shuntingYard("1 + 1 * 2");
    shuntingYard("3 + 4 * 2 / (1 - 5)");
    shuntingYard("1 + 2 + (3 + 4)");
    return 0;
}

void shuntingYard(const char *expression) {
    Stack *stackHead = NULL;
    Queue *queueHead = NULL;
    Queue *queueTail = NULL;
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
                   getPrecedence(currChar) <= getPrecedence(stackHead->data)) {
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
            while (stackHead != NULL && stackHead->data != '(') {
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

int getPrecedence(char operation) {
    if (operation == '/' || operation == '*')
        return 1;
    else if (operation == '-' || operation == '+')
        return 0;
    else
        return -1;
}

