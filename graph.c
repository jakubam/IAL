#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


void graphInit(tGraph *graph) {
    for (int i = 0; i < NUM_OF_NODES; i++) {
        graph->nodes[i] = NULL;
    }
}

void nodeInsert(tGraph *graph, tKey key, unsigned int position) {
    if (position < NUM_OF_NODES) {
        tNode *new_node = (tNode *) malloc(sizeof(struct tNode));
        if (!new_node)
            return;
        new_node->key = key;
        new_node->connection = NULL;
        graph->nodes[position] = new_node;
    }
}

void makeConnection(tGraph *graph, unsigned int position, tKey neighbour_key, tWeight weight) {
    if (position < NUM_OF_NODES) {
        tNode *head_node = graph->nodes[position];
        tConnection *new_connection = (tConnection *) malloc(sizeof(struct tConnection));
        new_connection->key = neighbour_key;
        new_connection->weight = weight;
        new_connection->connection = NULL;
        /* Vkládání do prázdného seznamu*/
        if (head_node->connection == NULL) {
            head_node->connection = new_connection;
        } else {
            /*Vkládání do seznamu, který již obsahuje spojení*/
            tConnection *last_connection = head_node->connection;
            /*Zastavení na posledním spojení*/
            while (last_connection->connection) {
                last_connection = last_connection->connection;
            }
            last_connection->connection = new_connection;
        }
    }
}

void graphClear(tGraph *graph) {
    tConnection *temp;
    tConnection *to_delete;
    for (int i = 0; i < NUM_OF_NODES; i++) {
        temp = graph->nodes[i]->connection;
        while (temp) {
            to_delete = temp;
            temp = temp->connection;
            free(to_delete);
        }
        free(graph->nodes[i]);
        graph->nodes[i] = NULL;
    }
}

void graphPrint(tGraph *graph) {
    for (int i = 0; i < NUM_OF_NODES; i++) {
        printf("Uzel: %s ", graph->nodes[i]->key);
        tConnection *connection = graph->nodes[i]->connection;
        printf("Spojení: | ");
        while (connection) {
            printf("%s %2d | ", connection->key, connection->weight);
            connection = connection->connection;
        }
        printf("\n");
    }
}