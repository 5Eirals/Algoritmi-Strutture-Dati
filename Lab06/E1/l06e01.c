#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE, TRUE} bool;

typedef struct {
	int start;
	int end;
	int duration;
} att;

att* readActivities(char* path, int* N);
void printActivities(att* V, int N);
void selectActivitiesDP(att* V, int N);
void printOptimal(att* V, int* P, int index);
void MSortActivities(att* V, int N);
void mergeSort(att* V, int start, int end);
void merge(att* V, int start, int middle, int end);

int main(){
	int N;
	char* path = "Lab06/E1/att3.txt";
	att* V = readActivities(path, &N);

	printActivities(V, N);
	MSortActivities(V, N);
	printActivities(V, N);
	selectActivitiesDP(V, N);

	free(V);
	return 0;
}

att* readActivities(char* path, int* N) {
	FILE* file;
	if ((file = fopen(path, "r")) == NULL) {
		printf("An error occurred while opening input file, terminating...\n");
		return NULL;
	}

	fscanf(file, "%d", N);
	att* V = (att*)malloc(*N * sizeof(att));
	for (int i = 0; i < *N; i++) {
		fscanf(file, "%d %d", &(V[i].start), &(V[i].end));
		V[i].duration = V[i].end - V[i].start;
	}

	return V;
}

void printActivities(att* V, int N) {
	for (int i = 0; i < N; i++)
		printf("(%d, %d) ", V[i].start, V[i].end);
	printf("\n");
}

void selectActivitiesDP(att* V, int N) {
	int L[N], P[N], queue = 0, last = 1;
	L[0] = 0;
	P[0] = -1;
	for (int i = 1; i < N; i++) {
		L[i] = V[i].duration;
		P[i] = -1;
		for (int j = 0; j < i; j++) {
			if (V[j].end <= V[i].start && (P[i] == -1 || V[j].duration >= V[P[i]].duration)) {
				if (V[P[i]].end > V[j].start)
					L[i] -= V[P[i]].duration;
				L[i] += V[j].duration;
				P[i] = j;
			}
		}
		if (queue < L[i]) {
			queue = L[i];
			last = i;
		}
	}
	printOptimal(V, P, last);
	printf("\n duration: %d\n", L[last]);
}

void printOptimal(att* V, int* P, int index) {
	if (index == -1){
		return;
	}
	printOptimal(V, P, P[index]);
	printf("(%d, %d) ", V[index].start, V[index].end);
}

void MSortActivities(att* V, int N) {
	mergeSort(V, 0, N-1);
}

void mergeSort(att* V, int start, int end) {
	if (start >= end)	return;
	printf("merge sort %d %d\n", start, end);
	int middle = start + (end-start) / 2;
	mergeSort(V, start, middle);
	mergeSort(V, middle+1, end);
	merge(V, start, middle, end);
}

void merge(att* V, int start, int middle, int end) {
	printf("merge arrays\n");
	att* Buffer = (att*)malloc((end - start + 1) * sizeof(att));
	int i = start, j = middle +1;
	for (int k = start; k <= end; k++) {
		if (j > end) {
			Buffer[k] = V[i++];
		} else if (i > middle){
			Buffer[k] = V[j++];
		} else if (V[i].start > V[j].start) {
			Buffer[k] = V[j++];
		} else {
			Buffer[k] = V[i++];
		}
	}
	for (int k = start; k <= end; k++) {
		V[k] = Buffer[k];
	}
	printActivities(V, end);
	free(Buffer);
	return;
}