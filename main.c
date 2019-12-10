#include "graph.h"
#include "file_read.h"
#include <stdlib.h>
#include <stdio.h>

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
            printf("| %2d | ", path[i]);
        }
    }
    unsigned int length = 0;
    printf("\n\nVšechny nejkratší cesty: \n---------------------------------------------------\n");
    unsigned int *paths = NULL;
    pathsFinder(graph, num_of_nodes, start, end, &length, &paths);
    /*Pro výpis je nutno procházet pole paths od konce, jelikož cesty ukládá invertovaně(od konečného uzlu po startovací)*/
    for (unsigned int j = 0; j < length; ++j) {
        /*Pokud je nalezen začáteční uzel, jedná se o konec jedné cesty*/
        if (paths[length - j - 1] == start && j !=0) {
            printf("<-- Na tomto uzlu se cesta sbíhá s cestou následující\n\n");
        }
        printf("| %2d | ", paths[length - j - 1]);
    }
    printf("\n==================================================================\n");
    fclose(file);
    graphRemove(graph, num_of_nodes);
    free(paths);
    free(path);
    return 0;
}


int main() {
    printf("JEDNODUCHÝ NEORIENTOVANÝ NEOHODNOCENÝ GRAF\n");
    testGraph("graph_simple.txt", 1, 5);
    printf("\n\nJEDNODUCHÝ NEORIENTOVANÝ NEOHODNOCENÝ GRAF -- NEEXISTUJÍCÍ SPOJENÍ\n");
    testGraph("graph_no_connection.txt", 1, 4);
    printf("\n\nJEDNODUCHÝ NEORIENTOVANÝ NEOHODNOCENÝ GRAF -- EXISTUJÍ DVĚ NEJKRATŠÍ CESTY\n");
    testGraph("graph_two_paths.txt", 1, 8);
    printf("\n\nNEORIENTOVANÝ NEOHODNOCENÝ GRAF\n");
    testGraph("graph_unoriented_weightless.txt", 1, 17);
    printf("\n\nNEORIENTOVANÝ OHODNOCENÝ GRAF\n");
    testGraph("graph_unoriented_weighted.txt", 1, 17);
    printf("\n\nORIENTOVANÝ NEOHODNOCENÝ GRAF\n");
    testGraph("graph_oriented_weightless.txt", 1, 17);
    printf("\n\nORIENTOVANÝ OHODNOCENÝ GRAF\n");
    testGraph("graph_oriented_weighted.txt", 1, 17);

}
