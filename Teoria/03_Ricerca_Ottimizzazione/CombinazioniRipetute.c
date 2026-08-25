#include <stdio.h>
#include <stdlib.h>



int combinazioniSemplici(int start, int pos, int* val, int* sol, int N, int k, int cnt);
void printSol(int* arr, int* ind, int l);

int main(){
    int arr[] = {1, 2, 3, 4, 5, 6};
    int N = 6, k = 2;

    int* sol = (int*)calloc(N, sizeof(int));

    printf("Number of dispositions: %d\n", combinazioniSemplici(0, 0, arr, sol, N, k, 0));

    return 0;
}

void printSol(int* arr, int* ind, int l){
    for(int i = 0; i < l; i++)
        printf("%d ", arr[ind[i]]);
    printf("\n");
}


//start: indice di partenza del ciclo (primo elemento disponibile non ancora utilizzato)
//pos: indice di sol corrente
//val: insieme degli elementi disponibili
//sol: vettore degli indici degli elementi di val che compongono la soluzione
//mark: vettore che registra se l'indice è già stato utilizzato
//N: numero di elementi di val
//k: lunghezza della soluzione cercata
//cnt: contatore delle soluzioni trovate

//come combinazioni semplici ma incremento l'indice start dopo la chiamata ricorsiva per poter riutilizzare l'elemento

int combinazioniSemplici(int start, int pos, int* val, int* sol, int N, int k, int cnt){
    if(pos >= k){
        printSol(val, sol, k);
        return cnt+1;
    }

    for(int i = start; i < N; i++){
        sol[pos] = i;
        cnt = combinazioniSemplici(start, pos+1, val, sol, N, k, cnt);
        start++;
    }

    return cnt;
}
