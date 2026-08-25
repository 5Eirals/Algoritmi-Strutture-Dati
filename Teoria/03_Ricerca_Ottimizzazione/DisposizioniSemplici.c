#include <stdio.h>
#include <stdlib.h>



int disposizioniSemplici(int pos, int* val, int* sol, int* mark, int N, int k, int cnt);
void printSol(int* arr, int* ind, int l);

int main(){
    int arr[] = {1, 2, 3, 4};
    int N = 4, k = 3;

    int* mark = (int*)calloc(N, sizeof(int));
    int* sol = (int*)calloc(N, sizeof(int));

    printf("Number of dispositions: %d\n", disposizioniSemplici(0, arr, sol, mark, N, k, 0));

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
//mark: vettore che registra se l'indice è già stato utilizzato
//N: numero di elementi di val
//k: lunghezza della soluzione cercata
//cnt: contatore delle soluzioni trovate

int disposizioniSemplici(int pos, int* val, int* sol, int* mark, int N, int k, int cnt){
    if(pos >= k){
        printSol(val, sol, k);
        return cnt+1;
    }
    for(int i = 0; i < N; i++) // per ogni elemento in val
        if(mark[i] == 0){ // se val[i] non è già stato preso
            mark[i] = 1; // marco  val[i] come preso
            sol[pos] = i; // segno l'indirizzo dell'elemento val in sol[pos]
            cnt = disposizioniSemplici(pos + 1, val, sol, mark, N, k, cnt); //ricorro
            mark[i] = 0; //smarco i
        }
    return cnt;
}