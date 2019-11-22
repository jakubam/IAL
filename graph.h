
/* Graf je implementován vázaným seznamem.
 * Typ tGraph představuje pole, na jehož jednotlivé indexy jsou ukládány uzly tNode.
 * Typ tNode obsahuje ukazatel tConnection*, jenž představuje záznam o vazbě s dalším uzlem (vzniká vázaný seznam).
 * Typ tConnection obsahuje také údaj o váze cesty mezi dvěma uzly.
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

#define NUM_OF_NODES 5

typedef char *tKey;
typedef int tWeight;

typedef struct tConnection {
    tKey key;
    tWeight weight;
    struct tConnection* connection;
} tConnection;

typedef struct tNode {
    tKey key;
    struct tConnection* connection;
} tNode;

typedef struct tGraph{
    struct tNode* nodes[NUM_OF_NODES];
}tGraph;

void graphInit(tGraph *graph);

void nodeInsert(tGraph *graph, tKey key, unsigned int position);

void graphPrint(tGraph *graph);

void makeConnection(tGraph *graph, unsigned int position, tKey neighbour_key, tWeight weight);

#endif