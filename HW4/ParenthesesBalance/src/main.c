#include "../../modules/stack/stack.h"
#include <stdbool.h>
#include <stdio.h>

bool checkParenthesesBalance(const char *checkString);

int main() {
    bool result = checkParenthesesBalance("(Hello!)(");
    printf("%d\n", result);

    result = checkParenthesesBalance(")/-l,,.s3");
    printf("%d\n", result);

    result = checkParenthesesBalance("({[]})asd()");
    printf("%d\n", result);

    result = checkParenthesesBalance("([{]})");
    printf("%d\n", result);
}

bool checkParenthesesBalance(const char *checkString) {
    if (checkString == NULL)
        return true;

    Stack *head = NULL;
    int errorCode = 0;

    for (int i = 0; checkString[i] != '\0'; ++i) {
        if (checkString[i] == '(' || checkString[i] == '[' ||
            checkString[i] == '{') {
            errorCode = pushToStack(checkString[i], &head);
            if (errorCode == -1) {
                printf("Error: couldn't allocate memory\n");
                freeStack(head);
                return false;
            }
        } else if (checkString[i] == ')' || checkString[i] == ']' ||
                   checkString[i] == '}') {
            if (head != NULL) {
                char lastParenthesis = popFromStack(&head);
                if ((checkString[i] == ')' && lastParenthesis != '(') ||
                    (checkString[i] == ']' && lastParenthesis != '[') ||
                    (checkString[i] == '}' && lastParenthesis != '{')) {
                    freeStack(head);
                    return false;
                }
            } else
                return false;
        }
    }

    bool isBalanced = (head == NULL);
    freeStack(head);
    return isBalanced;
}

