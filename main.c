#include "graph.h"
#include "file_read.h"
#include <stdlib.h>
#include <stdio.h>

/*VYTVOŘENÍ JEDNODUCHÉHO GRAFU*/

int main() {
    unsigned int num_of_nodes;
    FILE *file = fopen("../graph.txt", "r");
    if(!file)
        return -1;
    num_of_nodes = countNodes(file);
    tNode *graph = (tNode*)malloc(num_of_nodes*sizeof(tNode));
    printf("Number of nodes: %d\n",num_of_nodes);
    fileRead(file, graph, num_of_nodes);
    graphPrint(graph, num_of_nodes);
    //shortestPath(graph,num_of_nodes,1,3);
    fclose(file);
    graphRemove(graph, num_of_nodes);
    return 0;
}
