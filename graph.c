#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*Funkce realizující inicializaci samotného grafu*/
void nodeInit(tNode *node) {
    node->num_of_connections = 0;
    node->done = 0;
    node->connections = (tConnection *) malloc(sizeof(tConnection));
    node->previous = NULL;
}

/*Funkce vytvářející spojení*/
void addConnection(tNode *node, tNode *ptr, unsigned int weight) {
    node->connections = (tConnection *) realloc(node->connections, ++node->num_of_connections * sizeof(tConnection));
    node->connections[node->num_of_connections - 1].node = ptr;
    node->connections[node->num_of_connections - 1].weight = weight;
}

/*Funkce realizující uvolnění grafu*/
void graphRemove(tNode *graph, unsigned int num_of_nodes) {
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        free(graph[i].connections);
    }
    free(graph);
}

/*Pomocná funkce, pro tisk grafu a údajů o uzlech*/
void graphPrint(tNode *graph, unsigned int num_of_nodes) {
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        printf("Uzel: %2d ", i + 1);
        printf("Spojení: | ");
        for (unsigned int j = 0; j < graph[i].num_of_connections; j++) {
            printf("index: %2ld váha: %2d | ",
                   (graph[i].connections[j].node) - graph + 1, graph[i].connections[j].weight);
        }
        putchar('\n');
    }
}

/*Pomocná funkce, pro tisk vzdáleností*/
void distancePrint(tNode *graph, unsigned int num_of_nodes) {
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        printf("Uzel: %2d ", i + 1);
        if (graph[i].distance == INT_MAX)
            printf("Vzdálenost:   ∞\n");
        else
            printf("Vzdálenost: %3d\n", graph[i].distance);
    }
}
/*Funkce, která kontroluje zda jsou všechny uzly zpracovány*/
bool pathIsFinished(tNode *graph, unsigned int num_of_nodes) {
    for (unsigned i = 0; i < num_of_nodes; i++) {
        if (!graph[i].done)
            return false;
    }
    return true;
}

/*Funkce, která najde nejbližší uzel*/
tNode *findClosest(tNode *graph, unsigned int num_of_nodes) {
    unsigned int min_distance = INT_MAX;
    unsigned int position_of_min = 0;
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        if ((!graph[i].done) && (graph[i].distance < min_distance)) {
            min_distance = graph[i].distance;
            position_of_min = i;
        }
    }
    /*Ošetření pro případ, kdy graf obsahuje uzly, ke kterým ze startovacího uzlu nevede žádná cesta*/
    if (min_distance == INT_MAX)
        return NULL;
    return &graph[position_of_min];
}

/* Funkce realizující nalezení nejkratší cesty*/
void shortestPath(tNode *graph, unsigned int num_of_nodes, unsigned int start, unsigned int end, unsigned int **path,
                  unsigned int *path_length) {
    /*Dekrementace čísel uzlů, aby reprezentovaly indexy*/
    start--;
    end--;
    /*Inicializace*/
    for (unsigned i = 0; i < num_of_nodes; i++) {
        graph[i].distance = INT_MAX;
        graph[i].done = false;
        graph[start].previous = NULL;
    }
    graph[start].distance = 0;
    graph[start].done = true;
    graph[start].previous = NULL;
    *path_length = 0;
    /*U startovního uzlu se podíváme na sousedící uzly a přiřadíme jim odpovídající vzdálenost */
    for (unsigned int i = 0; i < graph[start].num_of_connections; i++) {
        graph[start].connections[i].node->distance = graph[start].connections[i].weight;
        graph[start].connections[i].node->previous = &graph[start];
    }
    tNode *closest;
    while (!pathIsFinished(graph, num_of_nodes)) {
        /* Vyber uzel s nejkratší vzdáleností*/
        closest = findClosest(graph, num_of_nodes);
        if (!closest)
            return;
        closest->done = true;
        /*Byl nalezen cílový uzel*/
        if (closest == &graph[end]) {
            /*Vytvoření cesty*/
            tNode *temp = closest;
            while (temp) {
                (*path) = realloc(*path, (*path_length + 1) * sizeof(unsigned int));
                (*path)[(*path_length)++] = temp - graph + 1;
                temp = temp->previous;
            }
            /* Cesta je uložena od konečného uzlu k uzlu startovacímu, proto ji je nutné převrátit*/
            unsigned int t;
            for (unsigned i = 0; i < *path_length / 2; i++) {
                t = (*path)[i];
                (*path)[i] = (*path)[*path_length - 1 - i];
                (*path)[*path_length - 1 - i] = t;
            }
        }
        /*Aktualizace vzdáleností*/
        unsigned int distance = 0;
        for (unsigned int i = 0; i < closest->num_of_connections; i++) {
            if (!closest->connections[i].node->done) {
                distance = closest->distance + closest->connections[i].weight;
                if (distance < closest->connections[i].node->distance) {
                    closest->connections[i].node->distance = distance;
                    closest->connections[i].node->previous = closest;
                }
            }
        }
    }
}

/* Funkce pro vyhledání všech nejkratších cest. Proměnná paths reprezentuje ukazatel na dynamické pole, do kterého budou
 * uloženy všechny nejkratší cestypomocí jednotlivých uzlů. V případě nalezení více cest jsou následující cesty
 * do pole ukládány jen od rozbočovacího uzlu*/
void pathsFinder(tNode *graph, unsigned int num_of_nodes, unsigned int start, unsigned int end, unsigned int *length,
                 unsigned int **paths) {
    /*Dekrementace čísel uzlů, aby reprezentovaly indexy*/
    start--;
    end--;
    /* Ukončení rekurze - bylo dosaženo počátečního uzlu*/
    if (end == start) {
        /* Uložení počátečního uzlu do pole paths*/
        (*paths) = realloc(*paths, ++(*length) * sizeof(unsigned int));
        (*paths)[*length - 1] = &graph[start] - graph + 1;
        return;
    }
    for (unsigned int i = 0; i < num_of_nodes; i++) {
        /*Nalezne všechny uzly, které jsou od startu méně vzdálené než konečný uzel*/
        if ((graph[i].distance < graph[end].distance))
            for (unsigned int j = 0; j < graph[i].num_of_connections; j++) {
                /*Podmínka pro vazbu s konečným uzlem*/
                if (graph[i].connections[j].node == &graph[end]) {
                    /*Pokud se součet vzdálenosti uzlu od počátku a váhy jeho spojení s konečným uzlem rovná vzdálenosti
                     * konečného uzlu od počátku, pak uzel  leží na nejkratší cestě.*/
                    if (graph[end].distance == graph[i].distance + graph[i].connections[j].weight) {
                        /*Do dynamického pole paths je uložen koncový uzel*/
                        (*paths) = realloc(*paths, ++(*length) * sizeof(unsigned int));
                        (*paths)[*length - 1] = &graph[end] - graph + 1;
                        pathsFinder(graph, num_of_nodes, ++start, &graph[i] - graph + 1, length, paths);
                        start--;
                    }
                }
            }
    }
}