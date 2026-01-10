#include "graph.h"

#define MIN_WT -1000

struct graph_s {
    int** madj;
    ST ST;
    int V;
    int E;
};

graph graph_init() {
    graph g = (graph) malloc(sizeof(graph_t));
    g->V = 0;
    g->E = 0;
    g->ST = STinit();
    g->madj = NULL;
    return g;
}

void graph_free(graph g){
    for(int i = 0; i < g->V; i++)
        free(g->madj[i]);
    free(g->madj);
    STfree(g->ST);
    free(g);
}

static void print_sqmatr(FILE *f, int** mat, int size){
    fprintf(f, "     |");
    for(int i = 0; i < size; i++)
        fprintf(f, " %.3d |", i);
    fprintf(f, "\n");

    for(int i = 0; i < size; i++){
        fprintf(f, " %.3d |", i);
        for(int j = 0; j < size; j++){
            fprintf(f, " %.3d |", mat[i][j]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
}

void graph_print(FILE* f, graph g){
    STprint(f, g->ST);
    print_sqmatr(f, g->madj, g->V);
}

void graph_load(graph g, ST st, edge_list list) {
    g->ST = st;
    g->V = STsize(st);
    g->madj = (int**) malloc(sizeof(int*) * g->V);
    for(int i = 0; i < g->V; i++)
        g->madj[i] = calloc(g->V, sizeof(int));
    for(int i = 0; i < edge_list_size(list); i++) {
        edge e = getEdge(list, i);
        g->madj[STsearch(st, edge_getStart(e))][STsearch(st, edge_getEnd(e))] = edge_getWeight(e);
    }
}

void graph_foundCycle(graph g, int i, bool* visited, bool* not_visited, edge_list loop_edges) {
    if(!visited[i]) {
        visited[i] = true;
        not_visited[i] = true;

        for(int j = 0; j < g->V; j++) {
            if (g->madj[i][j] != 0) {
                if(!visited[j])
                    graph_foundCycle(g, j, visited, not_visited, loop_edges);
                else if(not_visited[j]) {
                    edge e = newEdge(STgetValue(g->ST, i), STgetValue(g->ST, j), g->madj[i][j]);
                    edge_list_insert(loop_edges, e);
                }
            }
        }
    }
    not_visited[i] = false;
}

edge_list graph_makeDAGsetlist(graph g) {
    bool* visited = (bool*) calloc(g->V, sizeof(bool));
    bool* not_visited = (bool*) calloc(g->V, sizeof(bool));
    edge_list loop_edges = edge_list_init();

    for(int i = 0; i < g->V; i++) {
        if(!visited[i])
            graph_foundCycle(g, i, visited, not_visited, loop_edges);
    }
    free(visited);
    free(not_visited);
    return loop_edges;
}

void graph_makeDAG(graph g, edge_list loop_edges) {
    int max_weight = -1;
    for(int i = 0; i < loop_edges->size; i++) {
        if(edge_getWeight(loop_edges->edge_list[i]) > max_weight)
            max_weight = edge_getWeight(loop_edges->edge_list[i]) ;
    }

    for(int i = 0; i < loop_edges->size; i++) {
        if(edge_getWeight(loop_edges->edge_list[i]) == max_weight) {
            int v1 = STsearch(g->ST, edge_getStart(loop_edges->edge_list[i]));
            int v2 = STsearch(g->ST, edge_getEnd(loop_edges->edge_list[i]));
            g->madj[v1][v2] = 0;
        }
    }
}

void graph_shortestPathBF(graph g, int id) {
    int v, i, negcycfound;
    int *st, *d;
    st = malloc(g->V*sizeof(int));
    d = malloc(g->V*sizeof(int));
    for (v = 0; v < g->V; v++) {
        st[v]= -1;
        d[v] = MIN_WT;
    }
    d[id] = 0;
    st[id] = id;

    for(i = 0; i < g->V - 1; i++)
        for(v = 0; v < g->V; v++) {
            if(d[v] == MIN_WT)
                continue;
            for(int w = 0; w < g->V; w++) {
                int weight = g->madj[v][w];
                if(weight != 0) { // edge exists
                    if(d[w] < d[v] + weight) {
                        d[w] = d[v] + weight;
                        st[w] = v;
                    }
                }
            }
        }

    // for (v = 0; v < g->V; v++)
    //     printf("Parentof %s is%s \n",
    //     STgetValue(g->ST, v),
    //     STgetValue(g->ST, st[v]));
    printf("\n Longest Distance from %s\n",
    STgetValue(g->ST, id));
    for (v = 0; v < g->V; v++)
        printf("%s: %d\n", STgetValue(g->ST, v), d[v]);
    free(st);
    free(d);


}
