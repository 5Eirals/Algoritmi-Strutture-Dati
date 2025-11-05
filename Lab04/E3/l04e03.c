#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_ERROR -1

typedef enum { zaffiro, rubino, topazio,  smeraldo} pietre;

typedef struct{
    int z; // zaffiro -> zaffiro || rubino
    int r; // rubino -> smeraldo || topazio
    int t; // topazio -> zaffiro || rubino
    int s; // smeraldo -> smeraldo || topazio
    int len;
} neckless_s, *Neckless;

int necklessPerm(pietre last, Neckless total, Neckless neckless, int count);
int makeNeckless(Neckless total, int* max);
int readNeckless(Neckless* total, char* path);
void freeNeckless(Neckless* total, int N);
void printNeckless(Neckless neckless);

int main() {
    char* path = "Lab04/E3/very_easy_test_set.txt";
    Neckless* total;
    int N = readNeckless(total, path);
    int* max = (int*)malloc(sizeof(int));
    *max = 0;

    for (int i = 0; i < N; i++) {
        printf("TEST #%d\n", i+1);
        printNeckless(total[i]);
        printf("Combinazioni valide: %d, Collana massima di lunghezza: %d\n",
            makeNeckless(total, max), *max);
    }

    free(max);
    freeNeckless(total, N);
    return 0;
}

int readNeckless(Neckless* total, char* path){
    int N;
    FILE* f;
    if((f=fopen(path, "r"))==NULL){
        printf("An error occurred while opening file, terminating...\n");
        return FILE_ERROR;
    }
    fscanf(f, "%d", &N);
    total = (Neckless*)malloc(N*sizeof(Neckless));
    for(int i=0; i<N; i++){
        total[i] = (Neckless)malloc(sizeof(neckless_s));
        fscanf(f, "%d %d %d %d", &total[i]->z, &total[i]->r, &total[i]->t, &total[i]->s);
        total[i]->len = total[i]->s + total[i]->t + total[i]->r + total[i]->z;
    }

    return N;
}

void freeNeckless(Neckless* total, int N){
    for(int i=0; i<N; i++){
        free(total[i]);
    }
    free(total);
}

void printNeckless(Neckless neckless){
    printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",
         neckless->z, neckless->r, neckless->t, neckless->s, neckless->len);
}

int makeNeckless(Neckless total, int* max) {
    int count = 0;
    return count;
}

int necklessPerm(pietre last, Neckless total, Neckless neckless, int count){
    return count;
}
