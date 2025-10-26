#include "../circularList/circularList.h"
#include <stdio.h>
#include <stdlib.h>

int rhyme(int numWarrior, int numMurder);

int main() {
    int n = 41;
    int m = 3;
    int result = rhyme(n, m);
    if (result != -1)
        printf("Initial position should be: %d\n", result);
    
    n = 1;
    m = 1;
    result = rhyme(n, m);
    if (result != -1)
        printf("Initial position should be: %d\n", result);
    
    n = 2;
    m = 2;
    result = rhyme(n, m);
    if (result != -1)
        printf("Initial position should be: %d\n", result);
    
    n = 7;
    m = 3;
    result = rhyme(n, m);
    if (result != -1)
        printf("Initial position should be: %d\n", result); 
        
    return 0;
}

int rhyme(int numWarrior, int numMurder) {
    if (numWarrior <= 0 || numMurder <= 0) {
        printf("Incorrect initial data");
        return -1;
    }

    CircularList *head = NULL;
    for (int i = 1; i <= numWarrior; ++i) {
        if (addToList(i, &head) == -1) {
            printf("Couldn't allocate memory");
            freeList(head);
            return -1;
        }
    }

    CircularList *prev = head;
    while (prev->next != head)
        prev = prev->next;

    CircularList *current = head;
    
    while (current->next != current) {
        for (int i = 0; i < numMurder - 1; ++i) {
            prev = current;
            current = current->next;
        }

        prev->next = current->next;
        if (current == head)
            head = current->next;

        CircularList *toDelete = current;
        current = current->next;
        free(toDelete);
    }
    int lastPos = current->data;
    free(current);
    return lastPos;
}

