#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void graphPrint(tNode* graph, unsigned int num_of_nodes){
    for(unsigned int i = 0; i < num_of_nodes; i++){
        printf("Uzel: %d ",i);
        printf("Spojení: ");
        for (unsigned int j = 0; j < graph[i].num_of_connections; j++) {
            //TODO: Jak vypsat index uzlu v poli?
           // printf("%d %d | ",graph[i].connections[j]->node, graph[i].connections[j]->weight);
        }
    }
}
