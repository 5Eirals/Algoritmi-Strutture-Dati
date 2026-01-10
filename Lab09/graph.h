#ifndef GRAPH_H
#define GRAPH_H

#include "st.h"

typedef struct graph_s graph_t, *graph;

graph graph_init();
void graph_free(graph graph);
void graph_load(graph graph, ST st, edge_list list);
void graph_print(FILE *f, graph graph);
edge_list graph_makeDAGsetlist(graph g);
void graph_makeDAG(graph g, edge_list loop_edges);
void graph_shortestPathBF(graph g, int id);

#endif
