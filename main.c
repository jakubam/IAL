#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

unsigned int countNodes(FILE *file) {
    unsigned int num_of_nodes = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n')
            num_of_nodes++;
    }
    return num_of_nodes;
}

void fileRead(FILE *file, tNode *graph, unsigned int num_of_nodes) {
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        //TODO: Read graph, malloc connections

    }
};

/*VYTVOŘENÍ JEDNODUCHÉHO GRAFU*/

int main() {
    tNode *graph;
    unsigned int num_of_nodes;
    FILE *file = fopen("../graph.txt", "r");
    if(!file)
        return -1;
    num_of_nodes = countNodes(file);
    printf("%d",num_of_nodes);
    fclose(file);
    return 0;
}
