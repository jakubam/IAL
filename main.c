#include "graph.h"
#include <stdlib.h>

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
    //nodeInsert(graph, "D", 3);
    //nodeInsert(graph, "E", 4);
    /* Vytvoření spojení*/
    makeConnection(graph, 0, "B", 1,1);
    makeConnection(graph, 0, "C", 2,3);
  /*  makeConnection(graph, 0, "D",3,5);
    makeConnection(graph, 0, "E", 4,-9);
    makeConnection(graph, 1, "A", 0,-1);
    makeConnection(graph, 1, "D", 3,-5);
    makeConnection(graph, 2, "E", 4,9);
    makeConnection(graph, 3, "A", 0,3);
    makeConnection(graph, 3, "B", 1,5);
    makeConnection(graph, 4, "C", 2,-9);*/

    shortestPath(graph, 0, 2);
    graphPrint(graph);
    graphClear(graph);
    free(graph);
}