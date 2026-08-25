#include <stdio.h>
#include <stdlib.h>



int permutazioniRipetute(int pos, int* dist_val, int* dist_mark, int* sol, int n_dist, int cnt);
int getDistVal(int* val, int* dist_val, int* dist_mark, int N);
int getDistValOrd(int* val, int* dist_val, int* dist_mark, int N);
int find(int target, int* arr, int N);
void printSol(int* arr, int* ind, int l);

int main() {
    int arr[] = {1, 2, 2, 2, 3, 3, 3, 4};
    int N = 8;

    int* sol = (int*)calloc(N, sizeof(int));
    int* dist_val = (int*)calloc(N, sizeof(int));
    int* dist_mark = (int*)calloc(N, sizeof(int));

    int n_dist = getDistValOrd(arr, dist_val, dist_mark, N);

    printf("Number of dispositions: %d\n", permutazioniRipetute(0, dist_val, dist_mark, sol, n_dist, 0));

    return 0;
}

int find(int target, int* arr, int N) {
    for (int i = 0; i < N; i++)
        if (arr[i] == target)
            return i;
    return -1;
}

int getDistVal(int* val, int* dist_val, int* dist_mark, int N) {

    // SOLUZIONE O(N^2) -> Si ottimizza prima ordinando il vettore con O(NlogN) e poi riempiendo dist_val in O(N)

    int n_dist = 0, index = -1;
    for (int i = 0; i < N; i++) {
        index = find(val[i], dist_val, n_dist);
        if (index > 0) {
            dist_mark[index]++;
        } else {
            dist_val[n_dist] = val[i];
            dist_mark[n_dist]++;
            n_dist++;
        }
    }

    dist_val = (int*)realloc(dist_val, n_dist * sizeof(int));
    dist_mark = (int*)realloc(dist_mark, n_dist * sizeof(int));
    return n_dist;
}

int getDistValOrd(int* val, int* dist_val, int* dist_mark, int N) {
    // con vettore val già ordinato

    int n_dist = 0;
    dist_val[n_dist] = val[0];
    dist_mark[n_dist++]++;

    for (int i = 1; i < N; i++) {
        if (val[i] != dist_val[n_dist-1])
            dist_val[n_dist++] = val[i];

        dist_mark[n_dist-1]++;
    }


    dist_val = (int*)realloc(dist_val, n_dist * sizeof(int));
    dist_mark = (int*)realloc(dist_mark, n_dist * sizeof(int));
    return n_dist;
}

void printSol(int* arr, int* ind, int l){
    for(int i = 0; i < l; i++)
        printf("%d ", arr[ind[i]]);
    printf("\n");
}

//pos: indice di sol corrente
//dist_val: insieme degli elementi disponibili SENZA RIPETIZIONI
//dist_mark: numero di ripetizioni di ciascun elemento
//sol: vettore degli indici degli elementi di val che compongono la soluzione
//N: numero di elementi di val
//cnt: contatore delle soluzioni trovate

//uguale a disposizioni semplici ma k == N, analizzo su elementi distinti

int permutazioniRipetute(int pos, int* dist_val, int* dist_mark, int* sol, int n_dist, int cnt){
    if(pos >= n_dist){
        printSol(dist_val, sol, n_dist);
        return cnt+1;
    }
    for(int i = 0; i < n_dist; i++){ // per ogni elemento in val
        if (dist_mark[i] > 0) {
            dist_mark[i]--; // tolgo dalle ripetizioni disponibili
            sol[pos] = i; // segno l'indirizzo dell'elemento val in sol[pos]
            cnt = permutazioniRipetute(pos + 1, dist_val, dist_mark, sol, n_dist, cnt); //ricorro
            dist_mark[i]++; // riaggiungo alle ripetizioni disponibili
        }
    }
    return cnt;
}
