#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void graphPrint(tNode *graph, unsigned int num_of_nodes) {
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        printf("Uzel: %d ", i);
        printf("Spojení| ");
        for (unsigned int j = 0; j < graph[i].num_of_connections; j++) {
             printf("index: %ld distance: %d  váha: %d | ",(graph[i].connections[j]->node) - graph,graph[i].distance, graph[i].connections[j]->weight);
        }
    }
}

bool pathIsFinished(tNode *graph, unsigned int num_of_nodes){
    for (unsigned i = 0; i < num_of_nodes; i++) {
        if(!graph[i].done)
            return false;
    }
    return true;
}

tNode findClosest(tNode *graph, unsigned int num_of_nodes) {
        unsigned int min_distance = INT_MAX;
        unsigned int position_of_min = 0;
        for(unsigned int i = 0; i < num_of_nodes; i++){
            if(graph[i].distance < min_distance) {
                min_distance = graph[i].distance;
                position_of_min = i;
            }
        }
        return graph[position_of_min];
}

void shortestPath(tNode *graph, unsigned int num_of_nodes, unsigned int start, unsigned int end) {
    for (unsigned i = 0; i < num_of_nodes; i++) {
        graph[i].distance = INT_MAX;
        graph[i].done = false;
    }
    graph[start].distance = 0;

   // unsigned int min_distance;
    tNode closest;
    while (!pathIsFinished(graph,num_of_nodes)) {
        closest = findClosest(graph, num_of_nodes);
        closest.done = true;

        unsigned int distance = 0;
        for(unsigned int i = 0; i < closest.num_of_connections; i++){
                if(!closest.connections[i]->node->done){
                    distance = closest.distance + closest.connections[i]->weight;
                    if(distance < closest.connections[i]->node->distance){
                        closest.connections[i]->node->distance = distance;
                        closest.connections[i]->node->previous = &closest;
                    }
                }
        }
    }
}


