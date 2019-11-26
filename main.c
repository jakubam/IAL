#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

struct tNode *node;
struct tGraph *graph;

/*VYTVOŘENÍ JEDNODUCHÉHO GRAFU*/
int main() {
    graph = (tGraph *) malloc(sizeof(struct tGraph));
    if (!graph)
        return 0;
    graphInit(graph);
    /*Vytvoření uzlů*/
    nodeInsert(graph, "A", 0);
    nodeInsert(graph, "B", 1);
    nodeInsert(graph, "C", 2);

    /* Vytvoření spojení*/
    makeConnection(graph, 0, "B", 1, 1);
    makeConnection(graph, 0, "C", 2, 3);
    makeConnection(graph, 1, "A", 0, 1);
    makeConnection(graph, 2, "A", 0, 3);
    graphPrint(graph);

    printf("\nNejkratší cesta z uzlu A do zbývajících: \n");
    shortestPath(graph, 0, 2);
    graphClear(graph);
    free(graph);
}