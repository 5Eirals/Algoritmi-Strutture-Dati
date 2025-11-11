#include <stdio.h>
#include <stdlib.h>

typedef struct { int *scelte; int num_scelte; } Livello;

int princ_molt(int pos, Livello *val, int *sol, int k, int count);

int main(){
	int k, i, j, total, *sol;
	printf("Inserisci il numero di decisioni n: ");
	scanf("%d", &k);
	Livello* valor = malloc(k * sizeof(Livello));
	for(i = 0; i < k; i++) {
		printf("Inserisci il numero di scelte per il passo %d: ", i);
		scanf("%d", &valor[i].num_scelte);
		valor[i].scelte = malloc(valor[i].num_scelte * sizeof(int));
	}
	for (i = 0; i < k; i++)
		for (j = 0; j < valor[i].num_scelte; j++) {
			printf("inserisci scelta %d-esima a livello %d: ", j, i);
			scanf("%d", &valor[i].scelte[j]);
		}
	sol = malloc(k * sizeof(int));

	printf("L'applicazione del principio di moltiplicazione da' le seguenti soluzioni: \n");
	total = princ_molt(0, valor, sol, k, 0);
	printf("e in totale sono %d \n", total);
	free(sol);
	for (i = 0; i < k; i++)
		free(valor[i].scelte);
	free(valor);
	return 0;
}

int princ_molt(int pos, Livello *val, int *sol, int k, int count) {
	int i;
	if (pos >= k) {
		for (i = 0; i < k; i++)
			printf("%d ", sol[i]);
		printf("\n");
		return count+1;
	}
	for (i = 0; i < val[pos].num_scelte; i++) {
		sol[pos] = val[pos].scelte[i];
		count = princ_molt(pos+1, val, sol, k, count);
	}
	return count;
}