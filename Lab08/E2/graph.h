#ifndef GRAPH_H
#define GRAPH_H

#include "st.h"
#include "list.h"


typedef struct vertex_s vertex, *vertex_p;
typedef struct node_s node, *link;
typedef struct edge_s edge_t, *edge;
typedef struct graph_s graph_t, *graph;
typedef struct list_s list_t, *list;

graph graph_init();
void graph_free(graph graph);
void graph_read(FILE *f, graph graph);
void graph_print(FILE *f, graph graph);
void graph_insert(graph graph, edge edge);
void graph_printEdges(FILE *f, graph g);
void graph_createAdjList(graph graph);
void graph_printEdgesList(FILE* f, graph g);
void graph_checkAdj(FILE* f, graph g);

#endif
