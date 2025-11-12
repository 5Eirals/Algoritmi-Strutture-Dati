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
Neckless* readNeckless(Neckless* total, char* path, int* N);
void freeNecklesses(Neckless* total, int N);
void printNeckless(Neckless neckless);
Neckless newNeckless(Neckless New);

int main() {
    char* path = "Lab04/E3/easy_test_set.txt";
    int N;
    Neckless* total;
    total = readNeckless(total, path, &N);


    for (int i = 0; i < N; i++) {
        Neckless max;
        max = newNeckless(max);
        printf("TEST #%d\n", i+1);
        printf("Base: ");
        printNeckless(total[i]);
        printf("Combinazioni valide: %d, Collana massima di lunghezza: \n",
            makeNeckless(total[i], max));
        printNeckless(max);
        printf("\n");
        free(max);
    }


    freeNecklesses(total, N);
    return 0;
}

Neckless* readNeckless(Neckless* total, char* path, int* N){
    FILE* f;
    if((f=fopen(path, "r"))==NULL){
        printf("An error occurred while opening file, terminating...\n");
        return ERROR;
    }
    fscanf(f, "%d", N);
    total = (Neckless*)malloc(*N *sizeof(Neckless));
    for(int i=0; i < *N; i++){
        total[i] = (Neckless)malloc(sizeof(Neckless));
        fscanf(f, "%d %d %d %d", &total[i]->z, &total[i]->r, &total[i]->t, &total[i]->s);
        total[i]->len = total[i]->s + total[i]->t + total[i]->r + total[i]->z;
    }

    return total;
}

void freeNecklesses(Neckless* total, int N){
    for(int i=0; i<N; i++){
        free(total[i]);
    }
    free(total);
}

Neckless newNeckless(Neckless New) {
    New = (Neckless)malloc(sizeof(neckless_s));
    New->z = 0;
    New->r = 0;
    New->t = 0;
    New->s = 0;
    New->len = 0;
    return New;
}

void printNeckless(Neckless neckless){
    printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",
         neckless->z, neckless->r, neckless->t, neckless->s, neckless->len);
}

int makeNeckless(Neckless base, Neckless max) {
    int count = 0;
    Neckless neckless;
    neckless = newNeckless(neckless);

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

                //printf("zaffiro ");
                count += necklessPerm(zaffiro, base, neckless, count, max);

                base->z += 1;
                neckless->z -= 1;
                neckless->len -= 1;
            }
            if (base->r > 0) {
                base->r -= 1;
                neckless->r += 1;
                neckless->len += 1;

                //printf("rubino ");
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

                //printf("smeraldo ");
                count += necklessPerm(smeraldo, base, neckless, count, max);

                base->s += 1;
                neckless->s -= 1;
                neckless->len -= 1;
            }
            if (base->t > 0) {
                base->t -= 1;
                neckless->t += 1;
                neckless->len += 1;

                //printf("topazio ");
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

                //printf("zaffiro ");
                count += necklessPerm(zaffiro, base, neckless, count, max);

                base->z += 1;
                neckless->z -= 1;
                neckless->len -= 1;
            }
            if (base->r > 0) {
                base->r -= 1;
                neckless->r += 1;
                neckless->len += 1;

                //printf("rubino ");
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

                //printf("smeraldo ");
                count += necklessPerm(smeraldo, base, neckless, count, max);

                base->s += 1;
                neckless->s -= 1;
                neckless->len -= 1;
            }
            if (base->t > 0) {
                base->t -= 1;
                neckless->t += 1;
                neckless->len += 1;

                //printf("topazio ");
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
        //printf("\n#%d found combo: ", count);
        //printNeckless(neckless);
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