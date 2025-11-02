#include <stdio.h>
#include <stdlib.h>

int disposizioni(int pos, int* val, int* sol, int n, int k, int count);

int main(){
	int n = 4, k = 2, count=0;
	int* val = (int*)malloc(n*sizeof(int));
	int* sol = (int*)malloc(k*sizeof(int));

	val[0] = 1;
	val[1] = 0;
	val[2] = 9;
	val[3] = 4;
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
