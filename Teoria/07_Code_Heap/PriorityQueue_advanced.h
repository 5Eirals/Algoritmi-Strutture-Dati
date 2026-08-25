#include <stdio.h>
#include <stdlib.h>
#include <ST.h>

typedef struct item {
    int data;
    int priority;
} *Item, item_t;

typedef struct heapItem_t {
    int index;
    int priority;
} heapItem, *HeapItem;

typedef struct pqueue_t {
    HeapItem heap;
    int* qp;
    ST hash;
    int heapSize;
} *PQ, pqueue;

void printItem(Item item);
int priorityGet(Item item);
int keyPriorityCmp(HeapItem item1, HeapItem item2);
int dataCmp(Item item1, Item item2);

int LEFT(int index);
int RIGHT(int index);
int PARENT(int index);
void HEAPify(PQ pq, int index);

PQ PQinit(int maxN);
void PQfree(PQ pq);
int PQempty(PQ pq);
void PQinsert(PQ pq, item_t item);
item_t PQextractMax(PQ pq);
heapItem PQshowMax(PQ pq);
void PQdisplay(PQ pq);
int PQsize(PQ pq);
void PQchange(PQ pq, item_t item);

