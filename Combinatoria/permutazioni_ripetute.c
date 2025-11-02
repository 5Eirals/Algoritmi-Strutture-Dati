#include <stdio.h>
#include <stdlib.h>

int permutazioni(int pos, int* val, int* sol, int n, int count);
int compare(const int*a, const  int*b){return *a-*b;}
int getdist(int* vec, int* dist_vec, int n);
int main(){
	int n = 4, count=0;
	int* val = (int*)malloc(n*sizeof(int));
	int* sol = (int*)malloc(n*sizeof(int));
	int* dist_val = (int*)calloc(n, sizeof(int));


	val[0] = 1;
	val[1] = 3;
	val[3] = 1;
	val[2] = 2;

	qsort(val, n, sizeof(int), compare);

	printf("\nnumero di disposizioni: %d\n", permutazioni(0, dist_val, sol, getdist(val, dist_val, n), count));


	free(sol);
	free(val);
	free(dist_val);
	return 0;
}

int permutazioni(int pos, int* val, int* sol, int n, int count){
	if(pos >= n){
		for(int i = 0; i < n; i++) printf("%d",sol[i]);
		printf(" ");
		return ++count;
	}

	for(int i = 0; i < n; i++){
		sol[pos] = val[i];
		count = permutazioni(pos + 1, val, sol, n, count);

	}
	return count;
}

int getdist(int* vec, int* dist_vec, int n) {
	int j = 0;
	dist_vec[0] = vec[0];
	for(int i = 1; i < n; i++)
		if(vec[i] != dist_vec[j])
			dist_vec[++j] = vec[i];
	dist_vec = (int*)realloc(dist_vec, (j+1)*sizeof(int));
	return j+1;
}

