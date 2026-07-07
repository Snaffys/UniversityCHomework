#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int to;
    int len;
} Edge;

typedef struct {
    Edge* edges;
    int size;
} City;

// each parent <= their children
typedef struct {
    Edge* data;
    int size;
    int capacity;
} BinaryMinHeap;

BinaryMinHeap* createHeap(int capacity);
void swapHeapNodes(Edge* edge1, Edge* edge2);
int heapPush(BinaryMinHeap* heap, int city, int dist);
Edge notEmptyHeapPop(BinaryMinHeap* heap);
int heapEmpty(BinaryMinHeap* heap);
void freeHeap(BinaryMinHeap* heap);

int readFile(const char* file, int* numCities, int* numRoads, int* numCapitals, City** graph, int** capitals);

int assignStates(int numCities, int numCapitals, int* capitals, City* graph, int* stateOfCity);
