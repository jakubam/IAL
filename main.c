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
    printf("Počet uzlů: %d\n\n",num_of_nodes);
    printf("Po přečtení souboru: \n");
    printf("----------------------------------------------------\n");
    fileRead(file, graph, num_of_nodes);
    graphPrint(graph, num_of_nodes);
    printf("----------------------------------------------------\n\n");
    unsigned int *path = NULL;
    unsigned int path_length = 0;
    unsigned int start = 1;
    unsigned int end = 3;
    printf("Po vyhledání nejkratší cesty: \n");
    printf("----------------------------------------------------\n");
    shortestPath(graph,num_of_nodes,start,end, &path, &path_length);
    graphPrint(graph, num_of_nodes);
    printf("----------------------------------------------------\n\n");
    printf("Path from node | %d | to node | %d | : \n", start, end);
    for (int i = 0; i < path_length; ++i) {
        printf("| %d | ", path[i]);
    }


    fclose(file);
    graphRemove(graph, num_of_nodes);
    free(path);
    return 0;
}
