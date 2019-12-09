#include "graph.h"
#include "file_read.h"
#include <stdlib.h>
#include <stdio.h>

/*VYTVOŘENÍ JEDNODUCHÉHO GRAFU*/

int testGraph(char *file_name, unsigned int start, unsigned int end) {
    unsigned int num_of_nodes;
    FILE *file = fopen(file_name, "r");
    if (!file)
        return -1;
    num_of_nodes = countNodes(file);
    tNode *graph = (tNode *) malloc(num_of_nodes * sizeof(tNode));
    printf("==================================================================\n");
    printf("Počet uzlů: %d\n\n", num_of_nodes);
    printf("Po přečtení souboru: \n");
    printf("----------------------------------------------------\n");
    fileRead(file, graph, num_of_nodes);
    graphPrint(graph, num_of_nodes);
    printf("----------------------------------------------------\n\n");
    unsigned int *path = NULL;
    unsigned int path_length = 0;
    printf("Po vyhledání nejkratší cesty: \n");
    printf("----------------------------------------------------\n");
    shortestPath(graph, num_of_nodes, start, end, &path, &path_length);
    distancePrint(graph, num_of_nodes);
    printf("----------------------------------------------------\n\n");
    printf("Nejkratší cesta z uzlu | %d | do uzlu | %d | : \n", start, end);
    if (path_length == 0) {
        printf("Cesta neexistuje!");
    } else {
        for (unsigned int i = 0; i < path_length; ++i) {
            printf("| %d | ", path[i]);
        }
    }
    unsigned int length = 0;
    printf("\n\nVšechny nejkratší cesty: \n---------------------------------------------------\n");
    unsigned int *paths = NULL;
    pathsFinder(graph, num_of_nodes, start, end, &length, &paths);
    /*Proměnná spaces je zavedena jen za účelem formátování výstupu konzolového okna*/
    int spaces = 5;
    /* Pro výpis je nutno procházet pole paths od konce, jelikož cesty ukládá invertovaně (od konečného uzlu po startovací)*/
    for (unsigned int j = 0; j < length; ++j) {
        /*Pokud je nalezen začáteční uzel, jedná se o konec jedné cesty*/
        if (paths[length - j - 1] == start && j !=0) {
            /*Tisk spojnice*/
            printf("\n%*s%s\n",spaces-7,"","|");
            printf("%*s%s\n",spaces-7,"","|");
            printf("%*s%s\n",spaces-7,"","↓");
            spaces = 5;
        }
        printf("| %2d | ", paths[length - j - 1]);
        spaces+=7;
    }
    printf("\n==================================================================\n");
    fclose(file);
    graphRemove(graph, num_of_nodes);
    free(paths);
    free(path);
    return 0;
}


int main() {
    testGraph("../graph6.txt", 1, 17);
}
