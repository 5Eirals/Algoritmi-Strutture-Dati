#include "graph.h"
#include "st.h"
#include "edge.h"

int main() {
    edge_list vec = edge_list_init();
    ST table = STinit();
    graph Graph = graph_init();

    FILE *f = fopen("../grafo4.txt", "r");
    STload(f, table);
    read_edge_list(f, vec);
    graph_load(Graph, table, vec);

    graph_print(stdout, Graph);

    edge_list loop_edges = graph_makeDAGsetlist(Graph);
    print_edge_list(loop_edges);
    graph_makeDAG(Graph, loop_edges);
    graph_print(stdout, Graph);

    graph_shortestPathBF(Graph, 0);

    graph_free(Graph);
    //STfree(table);
    //edge_list_free(vec);
    fclose(f);

    return 0;
}