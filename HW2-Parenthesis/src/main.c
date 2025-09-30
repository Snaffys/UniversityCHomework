#include <stdbool.h>
#include <stdio.h>

bool parenthesisBalance(char *checkString, char lParenthesis) {
    char rParenthesis;
    if (lParenthesis == '(')
        rParenthesis = ')';
    else if (lParenthesis == '[')
        rParenthesis = ']';
    else if (lParenthesis == '{')
        rParenthesis = '}';
    else
        return false;

    int balance = 0;
    for (int i = 0; checkString[i] != '\0'; i++) {
        if (checkString[i] == lParenthesis)
            balance++;
        else if (checkString[i] == rParenthesis) {
            if (balance == 0)
                return false;
            balance--;
        }
    }
    return balance == 0;
}

int main() {
    printf("%d\n", parenthesisBalance("[test]]", '['));
    printf("%d\n", parenthesisBalance("((test)test)", '('));
    printf("%d\n", parenthesisBalance("}}}}test", '{'));
    return 0;
}
