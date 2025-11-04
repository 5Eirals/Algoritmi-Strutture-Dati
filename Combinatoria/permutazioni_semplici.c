#include <stdio.h>
#include <stdlib.h>

int permutazioni(int pos, int* val, int* sol, int* mark, int n, int count);

int main(){
	int n = 3, count=0;
	int* val = (int*)malloc(n*sizeof(int));
	int* sol = (int*)malloc(n*sizeof(int));
	int* mark = (int*)calloc(n, sizeof(int));

	val[0] = 1;
	val[1] = 2;
	val[2] = 3;

	printf("\nnumero di disposizioni: %d\n", permutazioni(0, val, sol, mark, n, count));

	free(mark);
	free(sol);
	return 0;
}

int permutazioni(int pos, int* val, int* sol, int *mark, int n, int count){
	if(pos >= n){
		for(int i = 0; i < n; i++) printf("%d",sol[i]);
		printf(" ");
		return ++count;
	}

	for(int i = 0; i < n; i++){
		if(mark[i] == 0){
			mark[i] = 1;
			sol[pos] = val[i];
			count = permutazioni(pos + 1, val, sol, mark, n, count);
			mark[i] = 0;
		}
	}
	return count;
}
