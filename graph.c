#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void nodeInit(tNode *node) {
    node->num_of_connections = 0;
    node->done = 0;
    node->connections = (tConnection *) malloc(sizeof(tConnection));
}

void addConnection(tNode *node, tNode *ptr, unsigned int weight) {
    node->connections = (tConnection *) realloc(node->connections, ++node->num_of_connections * sizeof(tConnection));
    node->connections[node->num_of_connections - 1].node = ptr;
    node->connections[node->num_of_connections - 1].weight = weight;
}

void graphRemove(tNode *graph, unsigned int num_of_nodes) {
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        free(graph[i].connections);
    }
    free(graph);
}

void graphPrint(tNode *graph, unsigned int num_of_nodes) {
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        printf("Uzel: %d ", i + 1);
        printf("Spojení: | ");
        for (unsigned int j = 0; j < graph[i].num_of_connections; j++) {
            printf("index: %2ld distance: %d  váha: %2d | ",
                   (graph[i].connections[j].node) - graph + 1, graph[i].distance, graph[i].connections[j].weight);
        }
        putchar('\n');
    }
}

bool pathIsFinished(tNode *graph, unsigned int num_of_nodes) {
    for (unsigned i = 0; i < num_of_nodes; i++) {
        if (!graph[i].done)
            return false;
    }
    return true;
}

tNode *findClosest(tNode *graph, unsigned int num_of_nodes) {
    unsigned int min_distance = INT_MAX;
    unsigned int position_of_min = 0;
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        if ((!graph[i].done) && (graph[i].distance < min_distance)) {
            min_distance = graph[i].distance;
            position_of_min = i;
        }
    }
    return &graph[position_of_min];
}

void shortestPath(tNode *graph, unsigned int num_of_nodes, unsigned int start, unsigned int end, unsigned int **path, unsigned int *path_length) {
    start--;
    end--;
    *path_length = 0;
    for (unsigned i = 0; i < num_of_nodes; i++) {
        graph[i].distance = INT_MAX;
        graph[i].done = false;
    }
    graph[start].distance = 0;
    graph[start].done = true;

    for (unsigned int i = 0; i < graph[start].num_of_connections; i++) {
        graph[start].connections[i].node->distance = graph[start].connections[i].weight;
        graph[start].connections[i].node->previous = &graph[start];
    }
    tNode *closest;
    while (!pathIsFinished(graph, num_of_nodes)) {
        closest = findClosest(graph, num_of_nodes);
        closest->done = true;

        if (closest == &graph[end]) {

            if (closest->previous != NULL || closest == &graph[start]) {
                tNode *temp = closest;
                while (temp) {
                    *path = realloc(*path, sizeof(unsigned int));
                    (*path)[(*path_length)++] = temp - graph + 1;
                    temp = temp->previous;
                }
                unsigned int t;
                for (unsigned i = 0; i < *path_length/2; i++) {
                    t =(*path)[i];
                    (*path)[i] = (*path)[*path_length - 1];
                    (*path)[*path_length - 1] = t;
                }
            }
        }
        unsigned int distance = 0;
        for (unsigned int i = 0; i < closest->num_of_connections; i++) {
            if (!closest->connections[i].node->done) {
                distance = closest->distance + closest->connections[i].weight;
                if (distance < closest->connections[i].node->distance) {
                    closest->connections[i].node->distance = distance;
                    closest->connections[i].node->previous = closest;
                }
            }
        }
    }
}


