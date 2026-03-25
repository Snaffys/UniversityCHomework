#include "../include/states.h"

BinaryMinHeap* createHeap(int capacity)
{
    BinaryMinHeap* heap = malloc(sizeof(BinaryMinHeap));
    if (heap == NULL) {
        printf("Couldn't allocate memory\n");
        return NULL;
    }
    heap->data = malloc(capacity * sizeof(Edge));
    if (heap->data == NULL) {
        printf("Couldn't allocate memory\n");
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

void swapHeapNodes(Edge* edge1, Edge* edge2)
{
    Edge tmp = *edge1;
    *edge1 = *edge2;
    *edge2 = tmp;
}

int heapPush(BinaryMinHeap* heap, int city, int dist)
{
    if (heap == NULL) {
        printf("Heap is unitialized\n");
        return 1;
    }
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        Edge* tmp = realloc(heap->data, heap->capacity * sizeof(Edge));
        if (tmp == NULL) {
            printf("Couldn't expand heap\n");
            return 1;
        }
        heap->data = tmp;
    }

    // add element at the end
    int currChild = heap->size++;
    heap->data[currChild].to = city;
    heap->data[currChild].len = dist;

    // move child up if it's smaller than parent
    while (currChild > 0) {
        int parent = (currChild - 1) / 2;
        if (heap->data[parent].len <= heap->data[currChild].len) {
            break;
        }
        swapHeapNodes(&heap->data[parent], &heap->data[currChild]);
        currChild = parent;
    }

    return 0;
}

Edge notEmptyHeapPop(BinaryMinHeap* heap)
{
    // receive smallest element (root)
    Edge root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    // move received element at the bottom of the heap
    int i = 0;
    while (1) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int smallest = i;

        if (leftChild < heap->size && heap->data[leftChild].len < heap->data[smallest].len) {
            smallest = leftChild;
        }
        if (rightChild < heap->size && heap->data[rightChild].len < heap->data[smallest].len) {
            smallest = rightChild;
        }
        if (smallest == i) {
            break;
        }

        swapHeapNodes(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }

    return root;
}

int heapEmpty(BinaryMinHeap* heap)
{
    if (heap == NULL)
        return 1;
    return heap->size == 0;
}

void freeHeap(BinaryMinHeap* heap)
{
    if (heap == NULL) {
        return;
    }
    free(heap->data);
    free(heap);
}

int readFile(const char* file, int* numCities, int* numRoads, int* numCapitals, City** graph, int** capitals)
{
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        printf("Couldn't open file states.txt\n");
        return 1;
    }

    if (fscanf(f, "%d %d", numCities, numRoads) != 2) {
        printf("Couldn't read data\n");
        fclose(f);
        return 1;
    }

    // count edges for each city
    int* numRoadsForCity = calloc(*numCities, sizeof(int));
    if (numRoadsForCity == NULL) {
        printf("Couldn't allocate memory\n");
        fclose(f);
        return 1;
    }
    for (int i = 0; i < *numRoads; ++i) {
        int city1, city2, len;
        if (fscanf(f, "%d %d %d", &city1, &city2, &len) != 3) {
            printf("Couldn't read data\n");
            free(numRoadsForCity);
            fclose(f);
            return 1;
        }
        numRoadsForCity[city1 - 1]++;
        numRoadsForCity[city2 - 1]++;
    }
    rewind(f);
    if (fscanf(f, "%d %d", numCities, numRoads) != 2) {
        printf("Couldn't read data\n");
        free(numRoadsForCity);
        fclose(f);
        return 1;
    }

    // fill graph
    *graph = malloc((*numCities) * sizeof(City));
    if (*graph == NULL) {
        printf("Couldn't allocate memory\n");
        free(numRoadsForCity);
        fclose(f);
        return 1;
    }
    for (int i = 0; i < *numCities; ++i) {
        (*graph)[i].edges = malloc(numRoadsForCity[i] * sizeof(Edge));
        if ((*graph)[i].edges == NULL) {
            printf("Couldn't allocate memory\n");
            for (int j = 0; j < i; ++j) {
                free((*graph)[j].edges);
            }
            free(*graph);
            free(numRoadsForCity);
            fclose(f);
            return 1;
        }
        (*graph)[i].size = 0;
    }
    for (int i = 0; i < *numRoads; ++i) {
        int city1, city2, roadLen;
        if (fscanf(f, "%d %d %d", &city1, &city2, &roadLen) != 3) {
            printf("Couldn't read data\n");
            for (int i = 0; i < *numCities; ++i) {
                free((*graph)[i].edges);
            }
            free(*graph);
            free(numRoadsForCity);
            fclose(f);
            return 1;
        }
        (*graph)[city1 - 1].edges[(*graph)[city1 - 1].size].to = city2 - 1;
        (*graph)[city1 - 1].edges[(*graph)[city1 - 1].size].len = roadLen;
        (*graph)[city1 - 1].size++;
        (*graph)[city2 - 1].edges[(*graph)[city2 - 1].size].to = city1 - 1;
        (*graph)[city2 - 1].edges[(*graph)[city2 - 1].size].len = roadLen;
        (*graph)[city2 - 1].size++;
    }

    // fill capitals
    if (fscanf(f, "%d", numCapitals) != 1) {
        printf("Couldn't read data\n");
        for (int i = 0; i < *numCities; ++i) {
            free((*graph)[i].edges);
        }
        free(*graph);
        free(numRoadsForCity);
        fclose(f);
        return 1;
    }
    *capitals = malloc((*numCapitals) * sizeof(int));
    if (*capitals == NULL) {
        printf("Couldn't allocate memory\n");
        for (int i = 0; i < *numCities; ++i) {
            free((*graph)[i].edges);
        }
        free(*graph);
        free(numRoadsForCity);
        fclose(f);
        return 1;
    }
    for (int i = 0; i < *numCapitals; ++i) {
        if (fscanf(f, "%d", &(*capitals)[i]) != 1) {
            printf("Couldn't read data\n");
            for (int i = 0; i < *numCities; ++i) {
                free((*graph)[i].edges);
            }
            free(*graph);
            free(numRoadsForCity);
            fclose(f);
            return 1;
        }
        --((*capitals)[i]);
    }

    free(numRoadsForCity);
    fclose(f);
    return 0;
}

int assignStates(int numCities, int numCapitals, int* capitals, City* graph, int* stateOfCity)
{
    int* visited = calloc(numCities, sizeof(int));
    if (visited == NULL) {
        printf("Couldn't allocate memory\n");
        return 1;
    }

    BinaryMinHeap** heaps = malloc(numCapitals * sizeof(BinaryMinHeap*));
    if (heaps == NULL) {
        printf("Couldn't allocate memory\n");
        free(visited);
        return 1;
    }

    // fill heaps of capitals with neighbors
    for (int s = 0; s < numCapitals; ++s) {
        heaps[s] = createHeap(graph[capitals[s]].size);
        if (heaps[s] == NULL) {
            for (int i = 0; i < s; ++i) {
                freeHeap(heaps[i]);
            }
            free(visited);
            free(heaps);
            return 1;
        }
        stateOfCity[capitals[s]] = s;
        visited[capitals[s]] = 1;

        for (int edge = 0; edge < graph[capitals[s]].size; ++edge) {
            int to = graph[capitals[s]].edges[edge].to;
            int len = graph[capitals[s]].edges[edge].len;
            if (heapPush(heaps[s], to, len)) {
                for (int i = 0; i < s; ++i) {
                    freeHeap(heaps[i]);
                }
                free(visited);
                free(heaps);
                return 1;
            }
        }
    }

    // assign cities to states
    int assigned = numCapitals;
    while (assigned < numCities) {
        for (int s = 0; s < numCapitals; ++s) {
            while (!heapEmpty(heaps[s])) {
                Edge node = notEmptyHeapPop(heaps[s]);
                if (!visited[node.to]) {
                    stateOfCity[node.to] = s;
                    visited[node.to] = 1;
                    ++assigned;

                    for (int edge = 0; edge < graph[node.to].size; ++edge) {
                        int to = graph[node.to].edges[edge].to;
                        int len = graph[node.to].edges[edge].len;
                        if (!visited[to]) {
                            if (heapPush(heaps[s], to, len)) {
                                for (int i = 0; i < numCapitals; ++i) {
                                    freeHeap(heaps[i]);
                                }
                                free(visited);
                                free(heaps);
                                return 1;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    for (int s = 0; s < numCapitals; ++s) {
        freeHeap(heaps[s]);
    }
    free(visited);
    free(heaps);
    return 0;
}
