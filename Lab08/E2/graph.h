#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 128

typedef enum { false, true } bool;

typedef char* str;
typedef struct vertex_s vertex, *vertex_p;
typedef struct node_s node, *link;
typedef struct edge_s edge_t, *edge;
typedef struct graph_s graph_t, *graph;
typedef struct st_s *ST;
typedef struct list_s list_t, *list;

ST STinit();
void STfree(ST st);
int STinsert(ST st, str val);
void STprint(FILE *f, ST st);
int STsearch(ST st, str val);
int STgetIndex(ST st, str val);
str STgetValue(ST st, int key);
void STdelete(ST st, int key);

list list_init();
void list_free(list list);
void list_insert(list list, link node);
void list_delete(list list, int key);

graph graph_init();
void graph_free(graph graph);
void graph_read(FILE *f, graph graph);
void graph_print(FILE *f, graph graph);
void graph_insert(graph graph, edge edge);

#endif
