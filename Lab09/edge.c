#include "edge.h"

struct edge_s {
    int weight;
    str start_vertex;
    str end_vertex;
} edge_t;



edge_list edge_list_init() {
    edge_list e = (edge_list)malloc(sizeof(edge));
    e->size = 0;
    e->maxSize = 2;
    e->edge_list = NULL;
    return e;
}

void edge_list_free(edge_list l) {
    for(int i = 0; i < l->size; i++)
        edge_free(l->edge_list[i]);
    free(l);
}

int edge_list_size(edge_list list) {
    return list->size;
}

edge getEdge(edge_list list, int i) {
    return list->edge_list[i];
}

edge newEdge(str start, str end, int weight) {
    edge e = (edge)malloc(sizeof(edge_t));
    e->start_vertex = start;
    e->end_vertex = end;
    e->weight = weight;
    return e;
}

void edge_print(edge e) {
    printf("%s -> %s %d\n", e->start_vertex, e->end_vertex, e->weight);
}

str edge_getStart(edge e) {
    return e->start_vertex;
}

str edge_getEnd(edge e) {
    return e->end_vertex;
}

int edge_getWeight(edge e) {
    return e->weight;
}

edge nullEdge(){
    edge e = (edge)malloc(sizeof(edge_t));
    e->weight = -100;
    return e;
}

bool isNullEdge(edge e){
    return e->weight == -100 ? true : false;
}

void edge_free(edge e) {
    free(e);
}

void read_edge_list(FILE *f, edge_list list) {
    list->edge_list = (edge*) malloc(sizeof(edge) * list->maxSize );
    while (!feof(f)) {
        if (list->size == list->maxSize) {
            list->maxSize *= 2;
            list->edge_list = (edge*) realloc(list->edge_list, sizeof(edge) * list->maxSize);
        }

        edge e = (edge)malloc(sizeof(edge_t));
        char v1[MAX_SIZE], v2[MAX_SIZE];
        if(fscanf(f, " %s %s %d ", v1, v2, &e->weight) != 3)
            printf("Invalid edege format\n");
        else {
            e->start_vertex = strdup(v1);
            e->end_vertex = strdup(v2);
            list->edge_list[list->size++] = e;
        }
    }
}

void edge_list_insert(edge_list list, edge e) {
    if (list->edge_list == NULL) {
        list->edge_list = (edge*) realloc(list->edge_list, sizeof(edge)* list->maxSize);
        list->edge_list[list->size++] = e;
        return;
    }

    if (list->size == list->maxSize) {
        list->maxSize *= 2;
        list->edge_list = (edge*) realloc(list->edge_list, sizeof(edge) * list->maxSize);
    }
    list->edge_list[list->size++] = e;
}

void print_edge_list(edge_list list) {
    for(int i = 0; i < list->size; i++)
        edge_print(list->edge_list[i]);
}
