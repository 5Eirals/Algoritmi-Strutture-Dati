#include <stdio.h>
#include <stdlib.h>

typedef struct item {
    int data;
    int priority;
} *Item, item_t;

typedef struct pqueue {
    Item A;
    int heapSize;
} *PQ;

void printItem(Item item);
int priorityGet(Item item);
int keyPriorityCmp(Item item1, Item item2);
int dataCmp(Item item1, Item item2);

int LEFT(int index);
int RIGHT(int index);
int PARENT(int index);
void HEAPify(Heap heap, int index);

PQ PQinit(int maxN);
void PQfree(PQ pq);
int PQempty(PQ pq);
void PQinsert(PQ pq, item_t item);
item_t PQextractMax(PQ pq);
item_t PQshowMax(PQ pq);
void PQdisplay(PQ pq);
int PQsize(PQ pq);
void PQchange(PQ pq, item_t item);

