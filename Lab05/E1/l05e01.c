#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE, TRUE} bool;

typedef struct {
	int start;
    int end;
    int duration;
} att;

typedef struct {
	att* attList;
	int duration;
	int len;
} Queue;

att* readActivities(char* path, att* V, int* N);
void attSel(int N, att* V);
void printActivity(att A);
void attPerm(int pos, att* queue, Queue* sol, int* mark, int n, Queue* max);
void attPowerset(int pos, att* queue, Queue* sol, int n, int start, Queue* max);
Queue* newQueue(Queue* Q, int N);
void freeQueue(Queue* Q);
//bool isValid(att a, att b);
bool isValid(Queue* Q);

int main() {
	int N;
    char* path = "Lab05/E1/att1.txt";
    att* V;
    V = readActivities(path, V, &N);

	attSel(N, V);

	free(V);
	return 0;
}

void printActivity(att A) {
	printf("start: %d, end: %d, duration: %d\n", A.start, A.end, A.duration);
}

att* readActivities(char* path, att* V, int* N) {
	FILE* file;
    if ((file = fopen(path, "r")) == NULL) {
    	printf("An error occurred while opening input file, terminating...\n");
        return NULL;
    }

    fscanf(file, "%d", N);
    V = (att*)malloc(*N * sizeof(att));
    for (int i = 0; i < *N; i++) {
    	fscanf(file, "%d %d", &(V[i].start), &(V[i].end));
    	V[i].duration = V[i].end - V[i].start;
    }

    return V;
}

Queue* newQueue(Queue* Q, int N) {
	Q = (Queue*)malloc(sizeof(Queue));
	Q->attList = (att*)malloc(N * sizeof(att));
	Q->duration = 0;
	Q->len = 0;
	return Q;
}

void freeQueue(Queue* Q) {
	free(Q->attList);
	free(Q);
}

void printQueue(Queue* Q) {
	for (int i = 0; i < Q->len; i++)
		printf("(%d, %d) ", Q->attList[i].start, Q->attList[i].end);
	printf("\nDuration: %d\n", Q->duration);
}

bool isValid(Queue* Q) {
	for (int i = 1; i < Q->len; i++)
		if (Q->attList[i].start < Q->attList[i - 1].end)
			return FALSE;
	return TRUE;
}

void attSel(int N, att* V) {
	Queue* sol, *best;
	sol = newQueue(sol, N);
	best = newQueue(best, N);
	int* mark = (int*)calloc(N, sizeof(int));

	//attPerm(0, V, sol, mark, N, best);
	attPowerset(0, V, sol, N, 0, best);

	printf("Best Queue: ");
	printQueue(best);

	free(mark);
	freeQueue(best);
	freeQueue(sol);
}

// void attPerm(int pos, att* queue, Queue* sol, int* mark, int n, Queue* max){
// 	if(pos >= n){
// 		printQueue(sol);
// 		if (isValid(sol) && sol->duration > max->duration) {
// 			printf("found valid max;\n");
// 			max->duration = sol->duration;
// 			max->len = sol->len;
// 			for(int i = 0; i < max->len; i++)
// 				max->attList[i] = sol->attList[i];
// 		}
// 		return;
// 	}
//
// 	for(int i = 0; i < n; i++){
// 		if(mark[i] == 0){
// 			mark[i] = 1;
// 			sol->attList[pos] = queue[i];
// 			sol->duration += queue[i].duration;
// 			sol->len++;
// 			attPerm(pos + 1, queue, sol, mark, n, max);
// 			mark[i] = 0;
// 		}
// 	}
// 	return;
// }

void attPowerset(int pos, att* queue, Queue* sol, int n, int start, Queue* max) {
	if (start >= n){
		if (sol->duration > max->duration) {
			max->duration = sol->duration;
			max->len = sol->len;
			for(int i = 0; i < max->len; i++)
				max->attList[i] = sol->attList[i];
		}
		return;
	}
	for (int i = start; i < n; i++){
		sol->attList[pos] = queue[i];
		sol->duration += queue[i].duration;
		sol->len++;
		if (pos > 0) {
			if (isValid(sol)) {
				attPowerset(pos + 1, queue, sol, n, i+1, max);
			}
		} else {
			attPowerset(pos + 1, queue, sol, n, i+1, max);
		}

		sol->len--;
		sol->duration -= queue[i].duration;
	}

	attPowerset(pos, queue, sol, n, n, max);
	return;
}

