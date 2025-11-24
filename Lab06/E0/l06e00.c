#include <stdio.h>
#include <stdlib.h>

int* readCities(char* path, int* N);
int solveR(int *val, int* opt, int n, int k);
void solveDP(int* val, int n);
void displaySol(int *opt, int *val, int n);
void solve(int* val, int n);
int max(int a, int b);

int main(){
	char* path = "Lab06/E0/val0.txt";
    int N;
    int* val = readCities(path, &N);
	solve(val, N);
	solveDP(val, N);

	return 0;
}

int* readCities(char* path, int* N){
	FILE *f;
    if ((f = fopen(path, "r")) == NULL){
    	printf("Error opening file\n");
        return NULL;
    }
    fscanf(f, "%d", N);
    int* cities = (int*)malloc(*N+1 * sizeof(int));
    cities[0] = 0;
    for(int i = 1; i <= *N; i++){
      fscanf(f, "%d", &cities[i]);
    }

    return cities;
}

int solveR(int *val, int *opt, int n, int k) {
	if (k==0)
		return 0;
	if (k==1)
		return val[1];
	return max(solveR(val,opt,n,k-1), solveR(val,opt,n,k-2) + val[k]);
}

void solve(int* val, int n) {
	int *opt;
	opt = calloc((n+1),sizeof(int));
	printf("Recursive solution: ");
	printf("maximum population covered %d\n", solveR(val, opt, n, n));
}

void solveDP(int* val, int n) {
	int i, *opt;
	opt = calloc((n+1),sizeof(int));
	opt[1] = val[1];
	for (i=2; i<=n; i++) {
		if (opt[i-1] > opt[i-2]+val[i])
			opt[i] = opt[i-1];
		else
			opt[i] = opt[i-2] + val[i];
	}
	printf("Dynamic programming solution: ");
	printf("maximum population covered %d\n", opt[n]);
	displaySol(opt, val, n);
}

void displaySol(int *opt, int *val, int n){
	int i, j, *sol;
	sol = calloc((n+1),sizeof(int));
	sol[1]=1;
	i=n;
	while (i>=2) {
		printf("i=%d\n", i);
		if (opt[i] == opt[i-1]){
			sol[i] = 0;
			i--;
		}
		else if (opt[i] == opt[i-2] + val[i]) {
			sol[i] = 1;
			sol[i-1] = 0;
			i -=2;
		}
	}
	for (i=1; i<=n; i++)
		if (sol[i])
			printf("%d ", val[i]);
	printf("\n");
}

int max(int a, int b) {
	if (a > b)
		return a;
	return b;
}
