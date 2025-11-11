#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define ERROR -1
#define N_STONES 4

typedef enum { FALSE, TRUE } bool;
typedef enum { zaffiro, rubino, topazio,  smeraldo} pietre;

typedef struct{
    int* stones;
    int len;
} neckless_s, *Neckless;

//int necklessRic(pietre last, Neckless base, Neckless neckless, int count, Neckless max);
int princ_molt(int pos, Neckless base, Neckless sol, int min, int count);
int makeNeckless(Neckless base, Neckless max);
Neckless* readNeckless(Neckless* total, char* path, int* N);
void freeNecklesses(Neckless* total, int N);
void printNeckless(Neckless neckless);
Neckless newNeckless(Neckless New);

int main() {
    char* path = "Lab04/E3/very_easy_test_set.txt";
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
        total[i]->stones = (int*)malloc(*N * sizeof(int));
        fscanf(f, "%d %d %d %d",
            &total[i]->stones[zaffiro],
            &total[i]->stones[rubino],
            &total[i]->stones[topazio],
            &total[i]->stones[smeraldo]
            );
        total[i]->len = total[i]->stones[zaffiro] + total[i]->stones[rubino] + total[i]->stones[topazio] + total[i]->stones[smeraldo];
    }

    return total;
}

void freeNecklesses(Neckless* total, int N){
    for(int i=0; i<N; i++){
        free(total[i]->stones);
        free(total[i]);
    }
    free(total);
}

Neckless newNeckless(Neckless New) {
    New = (Neckless)malloc(sizeof(neckless_s));
    New->stones = (int*)calloc(N_STONES,sizeof(int));
    New->len = 0;
    return New;
}

void printNeckless(Neckless neckless){
    printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n",
         neckless->stones[zaffiro], neckless->stones[rubino], neckless->stones[topazio], neckless->stones[smeraldo], neckless->len);
}

int makeNeckless(Neckless base, Neckless max) {
    int count = 0;
    max->stones = calloc(N_STONES, sizeof(int));

    int min = INT_MAX;
    for (int i = 0; i < N_STONES; i++)
        if (base->stones[i] < min)
            min = base->stones[i];
    if (min > 0) {
        for (int i = 0; i < N_STONES; i++)
            max->stones[i] = min-1;
        max->len = (min-1)*N_STONES;
        printf("Min: %d\n", min);
    }

    count = princ_molt(zaffiro, base, max, min, count);

    return count;
}

int princ_molt(int pos, Neckless base, Neckless sol, int min, int count) {
    int i;
    if (pos >= N_STONES) {
        printf("Terminal case\n");
        for (i = 0; i < N_STONES; i++)
            printf("%d ", sol->stones[i]);
        printf("\n");
        return count+1;
    }
    for (i = 0; i < base->stones[pos]; i++) {
        if (sol->stones[pos] < base->stones[pos]) {
            sol->stones[pos] += 1;
            sol->len += 1;
            printf("%d: %d - %d \n",count, pos, sol->stones[pos]);
            if (pos == zaffiro || pos == topazio) {
                if (sol->stones[zaffiro] <= base->stones[zaffiro])
                    count += princ_molt(zaffiro, base, sol, min, count);
                if (sol->stones[rubino] <= base->stones[rubino])
                    count += princ_molt(zaffiro, base, sol, min, count);
            }else if (pos == smeraldo || pos == rubino) {
                if (sol->stones[smeraldo] <= base->stones[smeraldo])
                    count += princ_molt(zaffiro, base, sol, min, count);
                if (sol->stones[topazio] <= base->stones[topazio])
                    count += princ_molt(topazio, base, sol, min, count);
            }
        }

    }
    return count;
}

// int necklessRic(pietre last, Neckless base, Neckless neckless, int count, Neckless max) {
//     bool end = FALSE;
//     switch (last) {
//         case zaffiro:
//             if (base->z > 0) {
//                 base->z -= 1;
//                 neckless->z += 1;
//                 neckless->len += 1;
//
//                 //printf("zaffiro ");
//                 count += necklessPerm(zaffiro, base, neckless, count, max);
//
//                 base->z += 1;
//                 neckless->z -= 1;
//                 neckless->len -= 1;
//             }
//             if (base->r > 0) {
//                 base->r -= 1;
//                 neckless->r += 1;
//                 neckless->len += 1;
//
//                 //printf("rubino ");
//                 count += necklessPerm(rubino, base, neckless, count, max);
//
//                 base->r += 1;
//                 neckless->r -= 1;
//                 neckless->len -= 1;
//             }
//             if (base->z < 1 && base->r < 1) {
//                 end = TRUE;
//             }
//             break;
//         case rubino:
//             if (base->s > 0) {
//                 base->s -= 1;
//                 neckless->s += 1;
//                 neckless->len += 1;
//
//                 //printf("smeraldo ");
//                 count += necklessPerm(smeraldo, base, neckless, count, max);
//
//                 base->s += 1;
//                 neckless->s -= 1;
//                 neckless->len -= 1;
//             }
//             if (base->t > 0) {
//                 base->t -= 1;
//                 neckless->t += 1;
//                 neckless->len += 1;
//
//                 //printf("topazio ");
//                 count += necklessPerm(topazio, base, neckless, count, max);
//
//                 base->t += 1;
//                 neckless->t -= 1;
//                 neckless->len -= 1;
//             }
//             if (base->s < 1 && base->t < 1) {
//                 end = TRUE;
//             }
//             break;
//         case topazio:
//             if (base->z > 0) {
//                 base->z -= 1;
//                 neckless->z += 1;
//                 neckless->len += 1;
//
//                 //printf("zaffiro ");
//                 count += necklessPerm(zaffiro, base, neckless, count, max);
//
//                 base->z += 1;
//                 neckless->z -= 1;
//                 neckless->len -= 1;
//             }
//             if (base->r > 0) {
//                 base->r -= 1;
//                 neckless->r += 1;
//                 neckless->len += 1;
//
//                 //printf("rubino ");
//                 count += necklessPerm(rubino, base, neckless, count, max);
//
//                 base->r += 1;
//                 neckless->r -= 1;
//                 neckless->len -= 1;
//             }
//             if (base->z < 1 && base->r < 1) {
//                 end = TRUE;
//             }
//             break;
//         case smeraldo:
//             if (base->s > 0) {
//                 base->s -= 1;
//                 neckless->s += 1;
//                 neckless->len += 1;
//
//                 //printf("smeraldo ");
//                 count += necklessPerm(smeraldo, base, neckless, count, max);
//
//                 base->s += 1;
//                 neckless->s -= 1;
//                 neckless->len -= 1;
//             }
//             if (base->t > 0) {
//                 base->t -= 1;
//                 neckless->t += 1;
//                 neckless->len += 1;
//
//                 //printf("topazio ");
//                 count += necklessPerm(topazio, base, neckless, count, max);
//
//                 base->t += 1;
//                 neckless->t -= 1;
//                 neckless->len -= 1;
//             }
//             if (base->s < 1 && base->t < 1) {
//                 end = TRUE;
//             }
//             break;
//         default:
//             printf("An impossible error occurred\n");
//             return ERROR;
//     }
//
//     if (end == TRUE) {
//         //printf("\n#%d found combo: ", count);
//         //printNeckless(neckless);
//         if (neckless->len > max-> len) {
//             max->len = neckless->len;
//             max->s = neckless->s;
//             max->t = neckless->t;
//             max->r = neckless->r;
//             max->z = neckless->z;
//         }
//         return ++count;
//     }
// }
