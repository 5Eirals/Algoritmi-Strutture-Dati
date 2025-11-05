#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 3

typedef enum {TRUE = 1, FALSE = 0} bool;

typedef struct {
  int a;
  int b;
} Arch;

void printVertexCover(Arch* arches, int* nodes, int N, int E);
void vertexCoverPowerset(int pos, Arch* arches, int* nodes, int* sol, int start, int N, int E);
bool checkCover(Arch* arches, int* nodes, int N, int E);
int main() {
	FILE* fin;
    int a, b;
	int N, E;
    int* nodes;
    Arch* arches;

    if((fin = fopen("Lab04/E1/grafo.txt", "r")) == NULL) {
    	printf("An error occured while opening the input file, terminating ...\n");
        return FILE_ERROR;
    }

    fscanf(fin, "%d %d", &N, &E);

   	nodes = (int*) malloc(N * sizeof(int));
    for(int i = 0; i < N; i++) {
    	nodes[i] = i;
    }

    arches = (Arch*) malloc(E * sizeof(Arch));
    for (int i = 0; i < E; i++) {
    	if(fscanf(fin, "%d %d", &a, &b) == 2){
    		arches[i].a = a;
            arches[i].b = b;
    	}
    }

	printVertexCover(arches, nodes, N, E);

    fclose(fin);
	free(arches);
    free(nodes);
	return 0;
}


void printVertexCover(Arch* arches, int* nodes, int N, int E) {
	int* sol = malloc(sizeof(int) * N);
	vertexCoverPowerset(0, arches, nodes, sol, 0, N, E);
	free(sol);
}

bool checkCover(Arch* arches, int* nodes, int N, int E) {
	for (int i = 0; i < E; i++) {
		bool cover = FALSE;
		for (int j = 0; j < N; j++) {
			if (arches[i].a == nodes[j] || arches[i].b == nodes[j]) {
				cover = TRUE;
				break;
			}
		}
		if (cover == FALSE)
			return FALSE;
	}

	return TRUE;
}

void vertexCoverPowerset(int pos, Arch* arches, int* nodes, int* sol, int start, int n, int e){
	if (start >= n){
		if (checkCover(arches, sol, pos, e)) {
			for (int i = 0; i < pos; i++) printf("%d", sol[i]);
			printf(" ");
		}
		return;
	}
	for (int i = start; i < n; i++){
		sol[pos] = nodes[i];
		vertexCoverPowerset(pos + 1, arches, nodes, sol, i+1, n, e);
	}

	vertexCoverPowerset(pos, arches, nodes, sol, n, n, e);
	return;
}