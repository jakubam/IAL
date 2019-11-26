#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void graphInit(tGraph *graph) {
    for (int i = 0; i < NUM_OF_NODES; i++) {
        graph->nodes[i] = NULL;
    }
}

void nodeInsert(tGraph *graph, tName name, unsigned int position) {
    if (position < NUM_OF_NODES) {
        tNode *new_node = (tNode *) malloc(sizeof(struct tNode));
        if (!new_node)
            return;
        new_node->name = name;
        new_node->weight = 0;
        new_node->position = position;
        new_node->next = NULL;
        graph->nodes[position] = new_node;
    }
}

void makeConnection(tGraph *graph, unsigned int position, tName neighbour_name, unsigned int neighbour_position,
                    tWeight weight) {
    if (position < NUM_OF_NODES) {
        tNode *head_node = graph->nodes[position];
        tNode *new_node = (tNode *) malloc(sizeof(struct tNode));
        new_node->name = neighbour_name;
        new_node->position = neighbour_position;
        new_node->weight = weight;
        new_node->next = NULL;
        /* Vkládání do prázdného seznamu*/
        if (head_node->next == NULL) {
            head_node->next = new_node;
        } else {
            /*Vkládání do seznamu, který již obsahuje spojení*/
            tNode *last_node = head_node->next;
            /*Zastavení na posledním spojení*/
            while (last_node->next) {
                last_node = last_node->next;
            }
            last_node->next = new_node;
        }
    }
}

void graphClear(tGraph *graph) {
    tNode *temp;
    tNode *to_delete;
    for (int i = 0; i < NUM_OF_NODES; i++) {
        temp = graph->nodes[i]->next;
        while (temp) {
            to_delete = temp;
            temp = temp->next;
            free(to_delete);
        }
        free(graph->nodes[i]);
        graph->nodes[i] = NULL;
    }
}

void graphPrint(tGraph *graph) {
    for (int i = 0; i < NUM_OF_NODES; i++) {
        printf("Pozice: %d Uzel: %s ", graph->nodes[i]->position, graph->nodes[i]->name);
        tNode *temp = graph->nodes[i]->next;
        printf("Spojení: | ");
        while (temp) {
            printf("%s %2d | ", temp->name, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void shortestPath(tGraph *graph, unsigned int start_position, unsigned int end_position) {
    int distance[NUM_OF_NODES];
    unsigned int previous_node[NUM_OF_NODES];
    unsigned int already_visited[NUM_OF_NODES];
    for (int i = 0; i < NUM_OF_NODES; i++) {
        distance[i] = INT_MAX;
        previous_node[i] = 0;
    }
    distance[start_position] = 0;
    int min_distance = INT_MAX;
    unsigned int closest;
    tNode *temp = graph->nodes[start_position]->next;
    for (int i = 0; i < NUM_OF_NODES - 1; i++) {
        while (temp) {
            distance[temp->position] = temp->weight;
            if (temp->weight < min_distance) {
                min_distance = temp->weight;
                closest = temp->position;
            }
            temp = temp->next;
        }
    }
    /* TODO: IMPLEMENT LOGIC */

    for (int i = 0; i < NUM_OF_NODES; i++) {
        printf("Distance: %d\n", distance[i]);
    }
}
