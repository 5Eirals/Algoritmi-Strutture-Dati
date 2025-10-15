#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 3

int** malloc2dR(int** m, FILE* fin, int* nc, int* nl);
void free2dR(int*** m, int nr);
void separa(int** m, int nr, int nc, int* whites, int* blacks);
void printMatrix(int** m, int nr, int nc);

int main(){
    FILE* fin;
    int nr, nc;
    int** matrix = NULL;
    matrix = malloc2dR(matrix, fin, &nr, &nc);
    int* whites = (int*)malloc(sizeof(int)), *blacks = (int*)malloc(sizeof(int));

    printMatrix(matrix, nr, nc);
    separa(matrix, nc, nr, whites, blacks);

    free2dR(&matrix, nr);
    free(whites);
    free(blacks);

    return 0;
}

int** malloc2dR(int** m, FILE* fin, int* nr, int* nc){
    if((fin = fopen("Lab02/mat.txt", "r")) == NULL){
        printf("An error occurred during input-file opening, terminating\n");
        exit(FILE_ERROR);
    }

    fscanf(fin, "%d %d", nr, nc);
    m = (int**)malloc(*nr * sizeof(int*));
    for(int i = 0; i < *nr; i++){
        m[i] = (int*)malloc(*nc * sizeof(int));
        for(int j = 0; j < *nc; j++){
            fscanf(fin, "%d", &m[i][j]);
        }
    }

    fclose(fin);

    return m;
}

void free2dR(int*** m, int nr){
    for(int i = 0; i < nr; i++)
        free((*m)[i]);
    free(*m);
}

void printMatrix(int** m, int nr, int nc){
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

void separa(int** m, int nr, int nc, int* whites, int* blacks) {
    int w = 0, b = 0;
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if ((i+j)%2 != 0) {
                whites = (int*)realloc(whites, (w+1)*sizeof(int));
                whites[w++] = m[i][j];
            } else {
                blacks = (int*)realloc(blacks, (b+1)*sizeof(int));
                blacks[b++] = m[i][j];
            }
        }
    }
}