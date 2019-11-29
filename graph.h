
 /*  Graf je implementován pomocí dynamického pole, na jehož jednotlivé indexy jsou ukládány uzly tNode.
 * Typ tNode reprezentuje samotný uzel, obsahuje vzdálenost vůči startovnímu uzlu při hledání nejkratší cesty,
 * dále obsahuje počet spojení, spojení jsou ukládána do dynamického pole, promměná done vyjadřuje zda uzel byl při
 * hledání nejkratší cesty již zpracován.
 * Typ tConnection vyjadřuje samotné spojení, je zde uložena váha spojení a ukazatel na příslušný uzel, mezi kterým
 * je spojení realizováno.
 *
 *
 * VÁHA:
 *
 * Kladná čísla - cesta je orientována směrem od uzlu, opačnou orientaci nevyjadřujeme, neboť je v rámci hledání
 * nejkratší cesty zbytečná.
 * Speciální případ - Pokud jsou všechny cesty ohodnoceny nulou, pak se jedná o nevážený a neorientovaný graf.
 *
 *
 *
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdbool.h>

typedef struct tNode {
    unsigned int distance;
    unsigned int num_of_connections;
    struct tConnection *connections;
    struct tNode* previous;
    bool done;
} tNode;

typedef struct tConnection {
    unsigned int weight;
    struct tNode *node;
} tConnection;

void nodeInit(tNode *node);
void addConnection(tNode *node, tNode *ptr, unsigned int weight);
void graphPrint(tNode* graph, unsigned int num_of_nodes);
void graphRemove(tNode *graph, unsigned int num_of_nodes);

void shortestPath(tNode *graph, unsigned int num_of_nodes, unsigned int start, unsigned int end);
tNode findClosest(tNode *graph, unsigned int num_of_nodes);
bool pathIsFinished(tNode *graph, unsigned int num_of_nodes);
#endif