#include "include/states.h"

int main()
{
    int numCities, numRoads, numCapitals;
    int* capitals;
    City* graph;

    if (readFile("states.txt", &numCities, &numRoads, &numCapitals, &graph, &capitals)) {
        return 1;
    }

    int* stateOfCity = calloc(numCities, sizeof(int));
    if (stateOfCity == NULL) {
        printf("Couldn't allocate memory\n");
        for (int i = 0; i < numCities; ++i) {
            free(graph[i].edges);
        }
        free(graph);
        free(capitals);
        return 1;
    }

    if (assignStates(numCities, numCapitals, capitals, graph, stateOfCity)) {
        free(stateOfCity);
        for (int i = 0; i < numCities; ++i) {
            free(graph[i].edges);
        }
        free(graph);
        free(capitals);
        return 1;
    }

    for (int s = 0; s < numCapitals; ++s) {
        printf("State %d: \nCities: ", s + 1);
        for (int c = 0; c < numCities; ++c) {
            if (stateOfCity[c] == s) {
                printf("%d ", c + 1);
            }
        }
        printf("\n");
    }

    free(stateOfCity);
    for (int i = 0; i < numCities; ++i) {
        free(graph[i].edges);
    }
    free(graph);
    free(capitals);
    return 0;
}
