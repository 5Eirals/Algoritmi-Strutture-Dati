#include <stdio.h>
#include <stdlib.h>

int powerset_divideetimpera(int pos, int* val, int* sol, int n, int start, int count);
int powerset_disposizioni(int pos, int* val, int* sol, int n, int count);
int powerset_combinazioni(int pos, int* val, int* sol, int n, int start, int count);
int powerset_r(int pos, int* val, int* sol, int n, int start, int count);

int main() {
	int n = 4, start = 0, count = 0;
    int* val = (int*)malloc(n*sizeof(int));
    int* sol = (int*)malloc(n*sizeof(int));

	val[0] = 1;
	val[1] = 2;
	val[2] = 3;
	val[3] = 4;

	printf("\nnumero di disposizioni: %d\n", powerset_divideetimpera(0, val, sol, n, 0, count));

	free(sol);
	free(val);
	return 0;
}

int powerset_divideetimpera(int pos, int* val, int* sol, int n, int start, int count) {
	if (start >= n){
		for (int i = 0; i < pos; i++) printf("%d", sol[i]);
		printf(" ");
		return ++count;
	}
    for (int i = start; i < n; i++){
    	sol[pos] = val[i];
        count = powerset_divideetimpera(pos + 1, val, sol, n, i+1, count);
    }

    count = powerset_divideetimpera(pos, val, sol, n, n, count);
    return count;
}

int powerset_disposizioni(int pos, int* val, int* sol, int n, int count) {
	if (pos >= n) {

	}
}