#include <stdio.h>
#include <stdlib.h>

void LISDP(int* val, int N);
void LISprint(int* val, int* P, int last);

int main(){
  	int val[] = {11, 7, 13, 15, 8, 14};
    int N = 6;
    LISDP(val, N);
	return 0;
}

void LISDP(int* val, int N){
	int ris = 1, *L = malloc(sizeof(int) * N), *P = malloc(sizeof(int) * N), last=1;
        //L : lunghezza i-esima della LIS
        //P : elemento precedente all'i-esimo
    L[0] = 1; P[0] = -1;
    for(int i = 1; i < N; i++){
    	L[i] = 1; P[i] = -1; // condizioni di base
        for(int j = 0; j < i; j++){ //scandisco il vettore tenendo val[i] come prefisso (riferimento)
         	if(val[j] < val[i] && L[i] < 1 + L[j]){ // se l'elemento val[j] è minore di val[i] e allunga la sequenza L[i]
                  L[i] = 1 + L[j]; // incrementa la lunghezza della sequenza
                  P[i] = j; // aggiorna il puntatore all'elemento precedente della sequenza
         	}
        }
        if(ris < L[i]){
        	ris = L[i]; // aggiorno la soluzione ottimale
        	last = i; // aggiorno l'elemento prefisso della soluzione ottimale
      	}
    }

    printf("Una delle soluzioni ottimali della LIS è:\n");
    LISprint(val, P, last);
    printf("lunghezza: %d\n", ris);

	free(L);
	free(P);
}

void LISprint(int* val, int* P, int last){
	if (last == -1){
    	return;
	}
	LISprint(val, P, P[last]);
	printf("%d\t", val[last]);
}


