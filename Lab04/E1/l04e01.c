#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 3


void printMatrix(int** matrix, int row, int col);
void printVertexCover(int** graph, int N, int E);
void vertexCoverComb(int pos, int** mat, int* sol, int start, int N, int k);
// rifare con powerset
int main() {
	FILE* fin;
    int a, b;
	int N, E;

    if((fin = fopen("Lab04/E1/grafo.txt", "r")) == NULL) {
    	printf("An error occured while opening the input file, terminating ...\n");
        return FILE_ERROR;
    }

    fscanf(fin, "%d %d", &N, &E);
   	int **graph = (int**) malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        graph[i] = (int*) calloc(N, sizeof(int));
    }

    for (int i = 0; i < E; i++) {
    	if(fscanf(fin, "%d %d", &a, &b) == 2){
    		graph[a][b] = 1;
    	}
    }

    printMatrix(graph, E, N);
	printVertexCover(graph, N, E);

    fclose(fin);
	for (int i = 0; i < E; i++) {
		free(graph[i]);
	}
    free(graph);
	return 0;
}

void printMatrix(int** matrix, int row, int col) {
	for (int i = 0; i < row; i++) {
          for (int j = 0; j < col; j++) {
            	printf("%d ", matrix[i][j]);
          }
          printf("\n");
	}
}

void printVertexCover(int** graph, int N, int E) {
	for (int i = 2; i <= E; i++) {
		int* sol = malloc(sizeof(int) * i);
		int* mark = calloc(N, sizeof(int));
		printf("Verterx cover for k:%d\n", i);
		vertexCoverComb(0, graph, sol, 0, N, i);
		free(sol);
	}
}

void vertexCoverComb(int pos, int** mat, int* sol, int start, int n, int k){
	printf("Inside vertexCoverComb\n");
	if(pos >= k){
		printf("(");
		for(int i = 0; i < k; i++) printf("%d ",sol[i]);
		printf(")\n");
		return;
	}

	for(int i = start; i < n; i++){
		for(int j = 0; j < n; j++) {
			if (mat[i][j] == 1) {
				printf("Match (%d, %d)\n sol: ", i, j); for(int i = 0; i < k; i++) printf("%d ",sol[i]); printf("\n");
				sol[pos] = i;
				vertexCoverComb(pos+1, mat, sol, j, n, k);
			}
		}

	}
}

