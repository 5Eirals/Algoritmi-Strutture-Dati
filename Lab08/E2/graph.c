#include "graph.h"

struct graph_s {
	int** madj;
    list* ladj;
	ST ST;
	int V;
	int E;
    bool list_created;
};

graph graph_init() {
	graph g = (graph) malloc(sizeof(graph_t));
	g->V = 0;
	g->E = 0;
	g->ST = STinit();
	g->list_created = false;
	g->madj = NULL;
    return g;
}

void graph_free(graph g){
	for(int i = 0; i < g->V; i++)
		free(g->madj[i]);
	free(g->madj);
	if (g->list_created) {
		for(int i = 0; i < g->V; i++)
			list_free(g->ladj[i]);
		free(g->ladj);
	}
    STfree(g->ST);
    free(g);
}

void graph_insert(graph g, edge e){
	STinsert(g->ST, edge_getStart(e));
	STinsert(g->ST, edge_getEnd(e));

    g->V = STsize(g->ST);
    g->E++;
}

void graph_loadST( FILE *f, graph g) {
	rewind(f);
	while(!feof(f)) {
		edge e = nullEdge();
		edge_read(f, e);
		if(isNullEdge(e))
			printf("Invalid edege format\n");
		else
			graph_insert(g, e);
		edge_free(e);
	}
}

void graph_createAdjMatr(FILE *f, graph g) {
	g->madj = (int**) malloc(sizeof(int*) * g->V);
	for(int i = 0; i < g->V; i++)
		g->madj[i] = calloc(g->V, sizeof(int));

	rewind(f);
	while(!feof(f)) {
		edge e = nullEdge();
		edge_read(f, e);
		if(isNullEdge(e))
			printf("Invalid edege format\n");
		else {
			int ind1 = STsearch(g->ST, edge_getStartId(e));
			int ind2 = STsearch(g->ST, edge_getEndId(e));

			g->madj[ind1][ind2] = edge_getFlow(e);
			g->madj[ind2][ind1] = edge_getFlow(e);

		}

		edge_free(e);
	}
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

void graph_read(FILE *f, graph g) {
	graph_loadST(f, g);
	STprint(stdout, g->ST);
	graph_createAdjMatr(f, g);
}

void graph_printEdges(FILE* f, graph g){
    for(int i = 0; i < g->V; i++){
        fprintf(f, "#%.2d <%s> \n", i, STgetValue(g->ST, i));
        for(int j = 0; j < g->V; j++){
            if(g->madj[i][j] != 0){
                fprintf(f, "\t\t[%.2d]-> <%s>\n", g->madj[i][j], STgetValue(g->ST, j));
            }
        }
    }
}

void graph_createAdjList(graph g){
    g->ladj = (list*) malloc(sizeof(list) * g->V);
    for(int i = 0; i < g->V; i++){
    	g->ladj[i] = list_init();
        for(int j = 0; j < g->V; j++){
            if(g->madj[i][j] != 0){
                list_insert(g->ladj[i], newNode(j, g->madj[i][j]));
            }
        }
    }
    g->list_created = true;
}

void graph_printEdgesList(FILE* f, graph g) {
	for(int i = 0; i < g->V; i++) {
		fprintf(f, "#%.2d <%s> \n", i, STgetValue(g->ST, i));
		for (link head = node_getNext(g->ladj[i]->head); head != NULL; head = node_getNext(head)) {
			fprintf(f, "\t\t[%.2d]-> <%s>\n", node_getFlow(head), STgetValue(g->ST, node_getKey(head)));
		}
	}
}

bool vertex_isAdjMatr(str v1, str v2, graph g){
    if(g->madj[STsearch(g->ST, v1)][STsearch(g->ST, v2)] > 0){
      return true;
    }
    return false;
}

bool vertex_isAdjList(str v1, str v2, graph g) {
	if (isNodeNull(list_search(g->ladj[STsearch(g->ST, v1)], STsearch(g->ST, v2))))
		return false;
	return true;

}

bool vertex_checkAdjList(graph g, str v1, str v2, str v3){
	if(vertex_isAdjList(v1, v2, g)
		&& vertex_isAdjList(v3, v1, g)
		&& vertex_isAdjList(v3, v2, g)){
		return true;
		}
	return false;
}

bool vertex_checkAdjMatr(graph g, str v1, str v2, str v3){
    if(vertex_isAdjMatr(v1, v2, g)
        && vertex_isAdjMatr(v3, v1, g)
        && vertex_isAdjMatr(v3, v2, g)){
        return true;
    }
    return false;
}

void graph_checkAdj(FILE* f, graph g) {
	if (f == stdin)
		printf("Insert the name of 3 Edges <id_elab>: \n");
	char vs[3][MAX_SIZE];

	for(int i = 0; i < 3; i++)
	 	fscanf(f, "%s", vs[i]);


	if(vertex_checkAdjMatr(g, vs[0], vs[1], vs[2]))
		printf("The vertices are adjacent in pairs\n");
	else
		printf("The vertices are not adjacent in pairs\n");

	if(vertex_checkAdjList(g, vs[0], vs[1], vs[2]))
		printf("The vertices are adjacent in pairs\n");
	else
		printf("The vertices are not adjacent in pairs\n");

}

