#ifndef _FILE_READ_H_
#define _FILE_READ_H_

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define FILE_ERR() printf("Invalid file\n"); exit(-1)
#define BUF_MAX 100

unsigned int countNodes(FILE *file);
void fileRead(FILE *file, tNode *graph, unsigned int num_of_nodes);

#endif