#ifndef EDGE_H
#define EDGE_H

#include "stdsymb.h"

typedef struct edge_s *edge;
typedef struct edge_list_s {
    edge *edge_list;
    int maxSize;
    int size;
} edge_list_t, *edge_list;


edge nullEdge();
edge newEdge(str v1, str v2, int weight);
bool isNullEdge(edge e);
edge_list edge_list_init();
int edge_list_size(edge_list list);
void edge_list_free(edge_list list);
edge getEdge(edge_list list, int i);
void read_edge_list(FILE* f, edge_list list);
void edge_free(edge e);
str edge_getStart(edge e);
str edge_getEnd(edge e);
int edge_getWeight(edge e);
void edge_list_insert(edge_list list, edge e);
void print_edge_list(edge_list list);


#endif //EDGE_H
