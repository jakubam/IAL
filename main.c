#include "graph.h"
#include "file_read.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int testGraph(FILE *file, unsigned int start, unsigned int end) {
    unsigned int num_of_nodes;
    num_of_nodes = countNodes(file);
	 /* Ošetření neplatných vstupů*/
    if ((start < 1 || start > num_of_nodes) || (end < 1 || end > num_of_nodes)){
        fclose(file);
        return -1;
	}
    if (start == end){
        fclose(file);
        return -1;
	}
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
    printf("\n==================================================================\n\n");
    fclose(file);
    graphRemove(graph, num_of_nodes);
    free(paths);
    free(path);
    return 0;
}


int main(int argc, char *argv[]) {

    /*Vypsání help*/
    if(argc == 2){
        if((strcmp(argv[1], "--help") == 0)){
            printf("Návod:\n");
			printf("----------------------------------------------\n");
			printf("Prosím, zadejte vstup ve tvaru: C S E (N)\n");
            printf("C: Cesta k grafu\n");
            printf("S: Startovní uzel (celé číslo)\n");
            printf("K: Konečný uzel (celé číslo)\n");
            printf("N: Nadpis (volitelné)\n");
			printf("-----------------------------------------------\n");
            return 0;
        }
    }

    /*Kontrola správného počtu argumentů*/
    if(!(argc == 4 || argc == 5)){
        fprintf(stderr,"Špatný počet argumentů\n");
        return -1;
    }

    /*Kontrola startovního a koncového uzlu*/
    char* next;
    int start = strtol(argv[2], &next, 10);
    if (*next != '\0') {
        fprintf(stderr,"Neplatný startovní uzel!\n");
        return -1;
    }
    int end = strtol(argv[3], &next, 10);
    if (*next != '\0') {
        fprintf(stderr,"Neplatný koncový uzel!\n");
        return -1;
    }

    /*Načtení souboru*/
    FILE * file;
    file = fopen(argv[1], "r");
    /*Je provedeno, pokud soubor existuje*/
    if(file != NULL){
		/*Vypíše nadpis, pokud je zadán*/
        if(argc == 5){
            printf("\n\n%s\n",argv[4]);
		}
        int check = testGraph(file, start, end);
        if(check != 0){
			fprintf(stderr, "Špatně definované čísla uzlů!\n");
            return -1;
        }
    } else {
        fprintf(stderr,"Neplatný soubor!\n");
        return -1;
    }
    return 0;
}
