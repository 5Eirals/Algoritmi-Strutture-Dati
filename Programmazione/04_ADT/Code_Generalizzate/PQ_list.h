#include <stdlib.h>
#include <stdio.h>

typedef struct item_s {
    int key;
    int val;
} item_t, *item_p;
typedef int Key;

typedef struct node_s node_t, *link;

typedef struct pqueue_s pqueue_t, *PQ;

Key getKey(item_p item);
int KEYcmp(Key a, Key b);
item_t ITEMsetVoid();

PQ PQinit(int maxN);
int PQempty(PQ pq);
void PQinsert(PQ pq, item_t item);
item_t PQextractMax(PQ pq);
item_t PQshowMax(PQ pq);
void PQdisplay(PQ pq);
void PQchange(PQ pq, item_t item);
