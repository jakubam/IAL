
/* Graf je implementován vázaným seznamem.
 * Typ tGraph představuje pole, na jehož jednotlivé indexy jsou ukládány uzly tNode.
 * Typ tNode reprezentuje samotný uzel, obsahuje jeho jméno, váhu spojení (vůči předchozímu uzlu), pozici v rámci grafu,
 * díky které je umožněn přístup k uzlu.
 *
 *
 * VÁHA:
 *
 * Kladná čísla - cesta je orientována směrem od uzlu
 * Záporná čísla - cesta je orientována směrem do uzlu
 * Speciální případ - Pokud jsou všechny cesty ohodnoceny nulou, pak se jedná o nevážený a neorientovaný graf.
 *
 *
 *
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#define NUM_OF_NODES 3  /*Počet uzlů určený čtením ze souboru. */

typedef char *tName;
typedef int tWeight;

typedef struct tNode {
    tName name;
    tWeight weight;
    unsigned int position;
    struct tNode* next;
} tNode;

typedef struct tGraph{
    struct tNode* nodes[NUM_OF_NODES];
}tGraph;

void graphInit(tGraph *graph);

void nodeInsert(tGraph *graph, tName name, unsigned int position);

void makeConnection(tGraph *graph, unsigned int position, tName neighbour_name, unsigned int neighbour_position, tWeight weight);

void graphPrint(tGraph *graph);

void graphClear(tGraph *graph);

void shortestPath(tGraph *graph, unsigned int start_position, unsigned int end_position);

tNode* findNode(tGraph *graph, tName key);
#endif