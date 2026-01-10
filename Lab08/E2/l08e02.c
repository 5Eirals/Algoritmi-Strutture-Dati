#include "graph.h"

#define PATH "../grafo.txt" //Coherent with CMAKE Location in file structure

int main(){

    FILE *fin = fopen(PATH, "r");

    graph Graph = graph_init();
    graph_read(fin, Graph);

    graph_print(stdout, Graph);
    graph_printEdges(stdout, Graph);

    printf("Adjacency list:\n");
    graph_createAdjList(Graph);
    graph_printEdgesList(stdout, Graph);

    graph_checkAdj(stdin, Graph);

    graph_free(Graph);
    fclose(fin);

    return 0;
}
