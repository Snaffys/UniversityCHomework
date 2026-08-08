#include "../list/list.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

int checkListContent(SortedList *head, int expected[], int size) {
    SortedList *current = head;
    int count = 0;

    for (int i = 0; i < size; ++i) {
        if (current == NULL)
            return 0;
        if (current->data != expected[i])
            return 0;
        current = current->next;
        count++;
    }

    return (current == NULL) && (count == size);
}

void testNullSafety() {
    printf("Testing NULL ptr safety\n");

    SortedList *nullList = NULL;

    printList(nullList);
    freeList(nullList);

    printf("Test passed.\n");
}

void testEmptyList() {
    printf("Testing empty list\n");

    SortedList *head = NULL;

    assert(removeFromList(91, &head) == -1);
    assert(head == NULL);

    printf("Test passed.\n");
}

void testAddToEmptyList() {
    printf("Testing add to empty list\n");

    SortedList *head = NULL;

    assert(addToList(20, &head) == 0);
    assert(head != NULL);
    assert(head->data == 20);
    assert(head->next == NULL);

    freeList(head);

    printf("Test passed.\n");
}

void testAddMultipleElements() {
    printf("Testing add multiple elements\n");

    SortedList *head = NULL;

    assert(addToList(65, &head) == 0);
    assert(addToList(29, &head) == 0);
    assert(addToList(15, &head) == 0);
    assert(addToList(0, &head) == 0);
    assert(addToList(10, &head) == 0);
    assert(addToList(-2, &head) == 0);

    int expected[] = {-2, 0, 10, 15, 29, 65};
    assert(checkListContent(head, expected, 6));

    freeList(head);

    printf("Test passed.\n");
}

void testAddDuplicates() {
    printf("Testing add duplicates\n");

    SortedList *head = NULL;

    assert(addToList(20, &head) == 0);
    assert(addToList(20, &head) == 0);
    assert(addToList(20, &head) == 0);

    SortedList *current = head;
    int count = 0;
    while (current != NULL) {
        assert(current->data == 20);
        current = current->next;
        count++;
    }
    assert(count == 3);

    freeList(head);

    printf("Test passed.\n");
}

void testRemoveFromList() {
    printf("Testing remove from list\n");

    SortedList *head = NULL;

    assert(addToList(20, &head) == 0);
    assert(addToList(15, &head) == 0);
    assert(addToList(10, &head) == 0);
    assert(addToList(-5, &head) == 0);
    assert(addToList(-100, &head) == 0);
  
    assert(removeFromList(10, &head) == 0);
    int expected1[] = {-100, -5, 15, 20};
    assert(checkListContent(head, expected1, 4));
  
    assert(removeFromList(-100, &head) == 0);
    int expected2[] = {-5, 15, 20};
    assert(checkListContent(head, expected2, 3));
  
    assert(removeFromList(20, &head) == 0);
    int expected3[] = {-5, 15};
    assert(checkListContent(head, expected3, 2));
  
    assert(removeFromList(15, &head) == 0);
    int expected4[] = {-5};
    assert(checkListContent(head, expected4, 1));

    assert(removeFromList(-5, &head) == 0);
    assert(head == NULL);
  
    printf("Test passed.\n");
}

void testRemoveNonexistent() {
    printf("Testing remove nonexistent\n");

    SortedList *head = NULL;

    assert(addToList(10, &head) == 0);
    assert(addToList(20, &head) == 0);

    assert(removeFromList(15, &head) == -1);

    int expected[] = {10, 20};
    assert(checkListContent(head, expected, 2));

    freeList(head);

    printf("Test passed.\n");
}

void testMemoryManagement() {
    printf("Testing memory management\n");

    SortedList *head = NULL;

    for (int i = 0; i < 100; ++i)
        assert(addToList(i, &head) == 0);

    for (int i = 0; i < 100; i += 2)
        assert(removeFromList(i, &head) == 0);

    SortedList *current = head;
    for (int i = 1; i < 100; i += 2) {
        assert(current != NULL);
        assert(current->data == i);
        current = current->next;
    }
    assert(current == NULL);

    freeList(head);

    head = NULL;
    assert(addToList(20, &head) == 0);
    freeList(head);

    printf("Test passed.\n");
}

void testBoundaryValues() {
    printf("Testing boundary values\n");

    SortedList *head = NULL;

    assert(addToList(0, &head) == 0);
    assert(addToList(-1000, &head) == 0);
    assert(addToList(1000, &head) == 0);

    assert(addToList(INT_MAX, &head) == 0);
    assert(addToList(INT_MIN, &head) == 0);

    assert(head != NULL);
    assert(head->data == INT_MIN);

    SortedList *current = head;
    while (current->next != NULL)
        current = current->next;

    assert(current->data == INT_MAX);

    freeList(head);

    printf("Test passed.\n");
}

void testDeterministicBehavior() {
    printf("Testing deterministic behavior\n");

    SortedList *head = NULL;

    int addSequence[] = {6, -10, 32, 28, -90, 3, 0};
    int removeSequence[] = {3, 0, 6, 32, -90, -10, 28};

    for (int i = 0; i < 7; ++i)
        assert(addToList(addSequence[i], &head) == 0);
    
    int expectedAfterAdd[] = {-90, -10, 0, 3, 6, 28, 32};
    assert(checkListContent(head, expectedAfterAdd, 7));
  
    for(int i = 0; i < 7; ++i)
        assert(removeFromList(removeSequence[i], &head) == 0);
    
    assert(head == NULL);
  
    freeList(head);
  
    printf("Test passed.\n");
}

void runAllTests() {
    printf("Running all tests\n");

    testNullSafety();
    testEmptyList();
    testAddToEmptyList();
    testAddMultipleElements();
    testAddDuplicates();
    testRemoveFromList();
    testRemoveNonexistent();
    testMemoryManagement();
    testBoundaryValues();
    testDeterministicBehavior();

    printf("All tests passed.\n");
}

