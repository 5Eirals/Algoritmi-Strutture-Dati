#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 3


void printMatrix(int** matrix, int row, int col);

int main() {
	FILE* fin;
    int a, b;
	int* N = malloc(sizeof(int)), *E = malloc(sizeof(int));

    if((fin = fopen("Lab04/E1/grafo.txt", "r")) == NULL) {
    	printf("An error occured while opening the input file, terminating ...\n");
        return FILE_ERROR;
    }

    fscanf(fin, "%d %d", N, E);
   	int **graph = (int**) malloc(*N * sizeof(int*));
    for (int i = 0; i < *N; i++) {
        graph[i] = (int*) calloc(*N, sizeof(int));
    }

	printMatrix(graph, *E, *N);

    for (int i = 0; i < *E; i++) {
    	if(fscanf(fin, "%d %d", &a, &b) == 2){
    		graph[a][b] = 1;
    	}
    }

    printMatrix(graph, *E, *N);

    fclose(fin);
	for (int i = 0; i < *E; i++) {
		free(graph[i]);
	}
    free(graph);
    free(N);
    free(E);
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

