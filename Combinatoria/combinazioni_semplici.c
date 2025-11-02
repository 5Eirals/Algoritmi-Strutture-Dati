#include <stdio.h>
#include <stdlib.h>

int combinazioni(int pos, int* val, int* sol, int start, int n, int k, int count);

int main(){
	int n = 4, k = 3, count=0, start=0;
	int* val = (int*)malloc(n*sizeof(int));
	int* sol = (int*)malloc(k*sizeof(int));

	val[0] = 1;
	val[1] = 5;
	val[2] = 9;
	val[3] = 4;
	printf("\nnumero di disposizioni: %d\n", combinazioni(0, val, sol, start, n, k, count));

	free(sol);
	free(val);
	return 0;
}

int combinazioni(int pos, int* val, int* sol, int start, int n, int k, int count){
	if(pos >= k){
		for(int i = 0; i < k; i++) printf("%d",sol[i]);
		printf(" ");
		return ++count;
	}

	for(int i = start; i < n; i++){
		sol[pos] = val[i];
		count = combinazioni(pos + 1, val, sol, i+1, n, k, count);
	}
	return count;
}