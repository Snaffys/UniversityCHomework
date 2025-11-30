#include "../list/list.h"
#include <stdio.h>
#include <string.h>

void printMenu();

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        extern void runAllTests();
        runAllTests();
        return 0;
    }

    SortedList *head = NULL;
    int errorCode = 0;
    int dialogCode = -1;
    int value = 0;

    do {
        printMenu();

        if (scanf("%d", &dialogCode) != 1) {
            printf("Wrong input\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (dialogCode) {
        case 0:
            break;

        case 1:
            printf("Element to add: ");

            if (scanf("%d", &value) != 1) {
                printf("Error: not an integer!\n");
                while (getchar() != '\n')
                    ;
                break;
            }

            errorCode = addToList(value, &head);
            if (errorCode == -1)
                printf("Error: couldn't allocate memory\n");
            else
                printf("Add %d to list\n", value);
            break;

        case 2:
            printf("Element to remove: ");

            if (scanf("%d", &value) != 1) {
                printf("Error: not an integer!\n");
                while (getchar() != '\n')
                    ;
                break;
            }

            errorCode = removeFromList(value, &head);
            if (errorCode == -1)
                printf("Element was not found in the list\n");
            else
                printf("Remove %d from list\n", value);
            break;

        case 3:
            printList(head);
            break;

        default:
            printf("Wrong input!\n");
            break;
        }
    } while (dialogCode != 0);

    freeList(head);
    return 0;
}

void printMenu() {
    printf("Operations:\n");
    printf("0 - exit\n");
    printf("1 - add to list\n");
    printf("2 - remove from list\n");
    printf("3 - print list\n");
    printf("choose operation\n");
}

