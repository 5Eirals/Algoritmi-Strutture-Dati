#include <stdio.h>
#include <stdlib.h>

int disposizioni(int pos, int* val, int* sol, int n, int k, int count);

int main(){
	int n = 2, k = 4, count=0;
	int* val = (int*)malloc(n*sizeof(int));
	int* sol = (int*)malloc(k*sizeof(int));

	val[0] = 0;
	val[1] = 1;
	printf("\nnumero di disposizioni: %d\n", disposizioni(0, val, sol, n, k, count));

	free(val);
	free(sol);
	return 0;
}

int disposizioni(int pos, int* val, int* sol, int n, int k, int count){
	if(pos >= k){
		for(int i = 0; i < k; i++) printf("%d",sol[i]);
		printf(" ");
		return ++count;
	}

	for(int i = 0; i < n; i++){
		sol[pos] = val[i];
		count = disposizioni(pos + 1, val, sol, n, k, count);
	}
	return count;
}
