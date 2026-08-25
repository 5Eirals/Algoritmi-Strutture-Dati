#include <stdio.h>
#include <stdlib.h>



int disposizioniRipetute(int pos, int* val, int* sol, int N, int k, int cnt);
void printSol(int* arr, int* ind, int l);

int main(){
    int arr[] = {1, 2, 3, 4};
    int N = 4, k = 3;

    int* sol = (int*)calloc(N, sizeof(int));

    printf("Number of dispositions: %d\n", disposizioniRipetute(0, arr, sol, N, k, 0));

    return 0;
}

void printSol(int* arr, int* ind, int l){
    for(int i = 0; i < l; i++)
        printf("%d ", arr[ind[i]]);
    printf("\n");
}

//pos: indice di sol corrente
//val: insieme degli elementi disponibili
//sol: vettore degli indici degli elementi di val che compongono la soluzione
//N: numero di elementi di val
//k: lunghezza della soluzione cercata
//cnt: contatore delle soluzioni trovate

//come disposizioni semplici senza mark

int disposizioniRipetute(int pos, int* val, int* sol, int N, int k, int cnt){
    if(pos >= k){
        printSol(val, sol, k);
        return cnt+1;
    }

    for(int i = 0; i < N; i++){
        sol[pos] = i;
        cnt = disposizioniRipetute(pos+1, val, sol, N, k, cnt);
    }

    return cnt;
}