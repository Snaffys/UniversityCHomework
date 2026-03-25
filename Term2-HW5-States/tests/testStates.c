#include "../include/states.h"

void testHeapPushPop()
{
    BinaryMinHeap* heap = createHeap(2);
    if (heap == NULL) {
        printf("FAIL testHeapPushPop: heap is NULL\n");
        return;
    }
    heapPush(heap, 0, 10);
    heapPush(heap, 1, 5);
    heapPush(heap, 2, 20);

    Edge e1 = notEmptyHeapPop(heap);
    Edge e2 = notEmptyHeapPop(heap);
    Edge e3 = notEmptyHeapPop(heap);

    if (e1.len != 5 || e1.to != 1)
        printf("FAIL testHeapPushPop: first pop expected 1:5, got %d:%d\n", e1.to, e1.len);
    else if (e2.len != 10 || e2.to != 0)
        printf("FAIL testHeapPushPop: second pop expected 0:10, got %d:%d\n", e2.to, e2.len);
    else if (e3.len != 20 || e3.to != 2)
        printf("FAIL testHeapPushPop: third pop expected 2:20, got %d:%d\n", e3.to, e3.len);
    else
        printf("PASS testHeapPushPop\n");

    freeHeap(heap);
}

void testAssignIsolatedStates()
{
    const int numCities = 4;
    const int numCapitals = 2;

    City graph[numCities];
    for (int i = 0; i < numCities; ++i) {
        graph[i].edges = malloc(2 * sizeof(Edge));
        if (graph[i].edges == NULL) {
            printf("FAIL testAssignIsolatedStates: memory wasn't allocated\n");
            for (int j = 0; j < i; ++j) {
                free(graph[j].edges);
            }
            return;
        }
        graph[i].size = 0;
    }

    // city 0 connected to city 1
    graph[0].edges[graph[0].size].to = 1;
    graph[0].edges[graph[0].size].len = 5;
    graph[0].size++;
    graph[1].edges[graph[1].size].to = 0;
    graph[1].edges[graph[1].size].len = 5;
    graph[1].size++;
    // city 2 connected to 3
    graph[2].edges[graph[2].size].to = 3;
    graph[2].edges[graph[2].size].len = 7;
    graph[2].size++;
    graph[3].edges[graph[3].size].to = 2;
    graph[3].edges[graph[3].size].len = 7;
    graph[3].size++;

    int* capitals = malloc(numCapitals * sizeof(int));
    if (capitals == NULL) {
        printf("FAIL testAssignIsolatedStates: memory wasn't allocated\n");
        for (int i = 0; i < numCities; ++i) {
            free(graph[i].edges);
        }
        return;
    }
    capitals[0] = 0;
    capitals[1] = 2;

    int* stateOfCity = malloc(numCities * sizeof(int));
    if (stateOfCity == NULL) {
        printf("FAIL testAssignIsolatedStates: memory wasn't allocated\n");
        for (int i = 0; i < numCities; ++i) {
            free(graph[i].edges);
        }
        return;
    }
    for (int i = 0; i < numCities; i++) {
        stateOfCity[i] = -1;
    }

    if (assignStates(numCities, numCapitals, capitals, graph, stateOfCity)) {
        printf("FAIL testAssignIsolatedStates: assignStates returned error\n");
    } else if (stateOfCity[0] != 0 || stateOfCity[1] != 0 || stateOfCity[2] != 1 || stateOfCity[3] != 1) {
        printf("FAIL testAssignIsolatedStates: unexpected state assignment\nstate of city 0: %d\nstate of city 1: "
               "%d\nstate of city 2: %d\nstate of city 3: %d\n",
            stateOfCity[0], stateOfCity[1], stateOfCity[2], stateOfCity[3]);
        printf("should be:\nstate of city 0: 0\nstate of city 1: 0\nstate of city 2: 1\nnstate of city 3: 1\n");
    } else {
        printf("PASS testAssignIsolatedStates\n");
    }

    for (int i = 0; i < numCities; ++i) {
        free(graph[i].edges);
    }
}

void testAssignStatesTieBreak()
{
    const int numCities = 3;
    const int numCapitals = 2;

    City graph[numCities];
    for (int i = 0; i < numCities; ++i) {
        graph[i].edges = malloc(2 * sizeof(Edge));
        if (graph[i].edges == NULL) {
            printf("FAIL testAssignStatesTieBreak: memory wasn't allocated\n");
            for (int j = 0; j < i; ++j) {
                free(graph[j].edges);
            }
            return;
        }
        graph[i].size = 0;
    }

    // city 0 connected to city 1
    graph[0].edges[graph[0].size].to = 1;
    graph[0].edges[graph[0].size].len = 5;
    graph[0].size++;
    graph[1].edges[graph[1].size].to = 0;
    graph[1].edges[graph[1].size].len = 5;
    graph[1].size++;
    // city 1 connected to 2
    graph[1].edges[graph[1].size].to = 2;
    graph[1].edges[graph[1].size].len = 5;
    graph[1].size++;
    graph[2].edges[graph[2].size].to = 1;
    graph[2].edges[graph[2].size].len = 5;
    graph[2].size++;

    int* capitals = malloc(numCapitals * sizeof(int));
    if (capitals == NULL) {
        printf("FAIL testAssignStatesTieBreak: memory wasn't allocated\n");
        for (int i = 0; i < numCities; ++i) {
            free(graph[i].edges);
        }
        return;
    }
    capitals[0] = 0;
    capitals[1] = 2;

    int* stateOfCity = malloc(numCities * sizeof(int));
    if (stateOfCity == NULL) {
        printf("FAIL testAssignStatesTieBreak: memory wasn't allocated\n");
        for (int i = 0; i < numCities; ++i) {
            free(graph[i].edges);
        }
        return;
    }
    for (int i = 0; i < numCities; i++) {
        stateOfCity[i] = -1;
    }

    if (assignStates(numCities, numCapitals, capitals, graph, stateOfCity)) {
        printf("FAIL testAssignStatesTieBreak: assignStates retuned error\n");
    } else if (stateOfCity[1] != 0) {
        printf("FAIL testAssignStatesTieBreak: city 1 should belong to state 0, but belongs to state %d\n",
            stateOfCity[1]);
    } else {
        printf("PASS testAssignStatesTieBreak\n");
    }

    for (int i = 0; i < numCities; ++i) {
        free(graph[i].edges);
    }
}

#ifdef TEST_MAIN
int main()
{
    testHeapPushPop();
    testAssignIsolatedStates();
    testAssignStatesTieBreak();

    printf("All tests executed\n");
    return 0;
}
#endif
