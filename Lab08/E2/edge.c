#include "edge.h"

struct edge_s {
    int flow;
    vertex start_vertex;
    vertex end_vertex;
} edge_t;


str edge_getStartId(edge e) {
    return e->start_vertex.id;
}

str edge_getEndId(edge e) {
    return e->end_vertex.id;
}

vertex edge_getStart(edge e) {
    return e->start_vertex;
}

vertex edge_getEnd(edge e) {
    return e->end_vertex;
}

int edge_getFlow(edge e) {
    return e->flow;
}

edge nullEdge(){
    edge e = (edge)malloc(sizeof(edge_t));
    e->flow = -100;
    return e;
}

bool isNullEdge(edge e){
    return e->flow == -100 ? true : false;
}

void edge_free(edge e) {
    free(e->start_vertex.id);
    free(e->start_vertex.subnet);
    free(e->end_vertex.id);
    free(e->end_vertex.subnet);
    free(e);
}

void edge_read(FILE *f, edge buffer){
    char id1[MAX_SIZE], id2[MAX_SIZE], net1[MAX_SIZE], net2[MAX_SIZE];
    fscanf(f, " %s %s %s %s %d",
            id1, net1, id2, net2,
               &buffer->flow
        );
    buffer->start_vertex.id = strdup(id1);
    buffer->start_vertex.subnet = strdup(net1);
    buffer->end_vertex.id = strdup(id2);
    buffer->end_vertex.subnet = strdup(net2);
}
