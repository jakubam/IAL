#include "file_read.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*Funkcia počítajúca uzly (riadky) v súbore*/
unsigned int countNodes(FILE *file) {
    unsigned int num_of_nodes = 0;
    int c;
    rewind(file); //Návrat na začiatok súboru
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n')
            num_of_nodes++;
    }
    return num_of_nodes;
}

/*Načítanie grafu zo súboru
**Graf je v súbore uložený ako zoznam susedov.*/
void fileRead(FILE *file, tNode *graph, unsigned int num_of_nodes) {
    rewind(file); //Návrat na začiatok súboru
    /*Čítanie známeho počtu riadkov*/
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        unsigned int node_num, buf_len = 0;
        int c;
        char buf[BUF_MAX]; //Buffer pre uloženie susedného uzlu a váhy hrany

        /*Načítanie uzlu*/
        fscanf(file, "%u", &node_num);
        if (node_num != i+1) {
            FILE_ERR();
        }

        nodeInit(&graph[node_num-1]);

        /*Načítanie susedných uzlov a váh hrán
        **Hrany sú vo formáte sused-váha, oddelené medzerami.*/
        do  {
            c = fgetc(file);
            /*Uloženie znaku do bufferu*/
            if (!isspace(c)) {
                buf[buf_len++] = c;
            }
            /*Spracovanie bufferu*/
            else if (buf_len) {
                unsigned int con_num, weight;
                buf[buf_len] = '\0';
                buf_len = 0;
                if (sscanf(buf, "%u-%u", &con_num, &weight) == 2 && con_num <= num_of_nodes) {
                    addConnection(&graph[node_num-1], &graph[con_num-1], weight);
                }
                else {
                    FILE_ERR();
                }
            }
        } while (c != '\n');
    }
}
