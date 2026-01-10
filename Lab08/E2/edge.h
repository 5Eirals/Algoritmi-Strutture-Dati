#ifndef EDGE_H
#define EDGE_H

#include "stdsymb.h"

#define MAX_SIZE 128

typedef struct edge_s *edge;


edge nullEdge();
bool isNullEdge(edge e);
void edge_free(edge e);
void edge_read(FILE *f, edge buffer);
str edge_getStartId(edge e);
str edge_getEndId(edge e);
vertex edge_getStart(edge e);
vertex edge_getEnd(edge e);
int edge_getFlow(edge e);


#endif //EDGE_H
