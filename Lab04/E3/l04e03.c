#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERROR -1

typedef enum { FALSE, TRUE } bool;
typedef enum { zaffiro, rubino, topazio,  smeraldo} pietre;

typedef struct{
    int z; // zaffiro -> zaffiro || rubino
    int r; // rubino -> smeraldo || topazio
    int t; // topazio -> zaffiro || rubino
    int s; // smeraldo -> smeraldo || topazio
    int len;
} neckless_s, *Neckless;

int necklessPerm(pietre last, Neckless base, Neckless neckless, int count, Neckless max);
int makeNeckless(Neckless base, Neckless max);
int readNeckless(Neckless* total, char* path);
void freeNecklesses(Neckless* total, int N);
void printNeckless(Neckless neckless);
Neckless newNeckless();

int main() {
    char* path = "Lab04/E3/very_easy_test_set.txt";
    Neckless* total;
    int N = readNeckless(total, path);
    Neckless max = newNeckless();

    for (int i = 0; i < N; i++) {
        printf("TEST #%d\n", i+1);
        printNeckless(total[i]);
        printf("Combinazioni valide: %d, Collana massima di lunghezza: \n",
            makeNeckless(total, max));
        printNeckless(max);
        printf("\n");
    }

    free(max);
    freeNecklesses(total, N);
    return 0;
}

int readNeckless(Neckless* total, char* path){
    int N;
    FILE* f;
    if((f=fopen(path, "r"))==NULL){
        printf("An error occurred while opening file, terminating...\n");
        return ERROR;
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

void freeNecklesses(Neckless* total, int N){
    for(int i=0; i<N; i++){
        free(total[i]);
    }
    free(total);
}

Neckless newNeckless() {
    Neckless neckless = (Neckless)malloc(sizeof(neckless_s));
    neckless->z = 0;
    neckless->r = 0;
    neckless->t = 0;
    neckless->s = 0;
    neckless->len = 0;
    return neckless;
}

void printNeckless(Neckless neckless){
    printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",
         neckless->z, neckless->r, neckless->t, neckless->s, neckless->len);
}

int makeNeckless(Neckless base, Neckless max) {
    int count = 0;
    Neckless neckless = newNeckless();

    count += necklessPerm(zaffiro, base, neckless, count, max);
    count += necklessPerm(rubino, base, neckless, count, max);
    count += necklessPerm(topazio, base, neckless, count, max);
    count += necklessPerm(smeraldo, base, neckless, count, max);

    free(neckless);
    return count;
}

int necklessPerm(pietre last, Neckless base, Neckless neckless, int count, Neckless max) {
    bool end = FALSE;

    switch (last) {
        case zaffiro:
            if (base->z > 0) {
                base->z -= 1;
                neckless->z += 1;
                neckless->len += 1;

                count += necklessPerm(zaffiro, base, neckless, count, max);

                base->z += 1;
                neckless->z -= 1;
                neckless->len -= 1;
            }
            if (base->r > 0) {
                base->r -= 1;
                neckless->r += 1;
                neckless->len += 1;

                count += necklessPerm(rubino, base, neckless, count, max);

                base->r += 1;
                neckless->r -= 1;
                neckless->len -= 1;
            }
            if (base->z < 1 && base->r < 1) {
                end = TRUE;
            }
            break;
        case rubino:
            if (base->s > 0) {
                base->s -= 1;
                neckless->s += 1;
                neckless->len += 1;

                count += necklessPerm(smeraldo, base, neckless, count, max);

                base->s += 1;
                neckless->s -= 1;
                neckless->len -= 1;
            }
            if (base->t > 0) {
                base->t -= 1;
                neckless->t += 1;
                neckless->len += 1;

                count += necklessPerm(topazio, base, neckless, count, max);

                base->t += 1;
                neckless->t -= 1;
                neckless->len -= 1;
            }
            if (base->s < 1 && base->t < 1) {
                end = TRUE;
            }
            break;
        case topazio:
            if (base->z > 0) {
                base->z -= 1;
                neckless->z += 1;
                neckless->len += 1;

                count += necklessPerm(zaffiro, base, neckless, count, max);

                base->z += 1;
                neckless->z -= 1;
                neckless->len -= 1;
            }
            if (base->r > 0) {
                base->r -= 1;
                neckless->r += 1;
                neckless->len += 1;

                count += necklessPerm(rubino, base, neckless, count, max);

                base->r += 1;
                neckless->r -= 1;
                neckless->len -= 1;
            }
            if (base->z < 1 && base->r < 1) {
                end = TRUE;
            }
            break;
        case smeraldo:
            if (base->s > 0) {
                base->s -= 1;
                neckless->s += 1;
                neckless->len += 1;

                count += necklessPerm(smeraldo, base, neckless, count, max);

                base->s += 1;
                neckless->s -= 1;
                neckless->len -= 1;
            }
            if (base->t > 0) {
                base->t -= 1;
                neckless->t += 1;
                neckless->len += 1;

                count += necklessPerm(topazio, base, neckless, count, max);

                base->t += 1;
                neckless->t -= 1;
                neckless->len -= 1;
            }
            if (base->s < 1 && base->t < 1) {
                end = TRUE;
            }
            break;
        default:
            printf("An impossible error occurred\n");
            return ERROR;
    }

    if (end == TRUE) {
        if (neckless->len > max-> len) {
            max->len = neckless->len;
            max->s = neckless->s;
            max->t = neckless->t;
            max->r = neckless->r;
            max->z = neckless->z;
        }
        return ++count;
    }
}
