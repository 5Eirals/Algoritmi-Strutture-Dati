#include "PriorityQueue_advanced.h"

void printItem(Item item) {
    printf(" Data:%03d-Priority:%03d;", item->data, item->priority);
}

int priorityGet(Item item) {
    return item->priority;
}
int keyPriorityCmp(HeapItem item1, HeapItem item2) {
    return item1->priority - item2->priority;
}

int dataCmp(Item item1, Item item2) {
    return item1->data - item2->data;
}

int LEFT(int index) {return 2 * index + 1;}
int RIGHT(int index) {return 2 * index + 2;}
int PARENT(int index) {return (index-1)/2;}
void Swap(PQ pq, int pos1, int pos2) {
    int index1, index2;
    heapItem temp = pq -> heap[pos1];
    pq->heap[pos1] = pq->heap[pos2];
    pq->heap[pos2] = temp;

    pq->qp[index1] = pos1;
    pq->qp[index2]=pos2;

}

void HEAPify(PQ pq, int index) {
    int left, right, largest;
    left = LEFT(index);
    right = RIGHT(index);
    if (left < pq->heapSize && pq->heap[left].priority > pq->heap[index].priority) {
        largest = left;
    } else {
        largest = index;
    }
    if (right < pq->heapSize && pq->heap[right].priority > pq->heap[largest].priority) {
        largest = right;
    }
    if (largest != index) {
        Swap(pq, index, largest);
        HEAPify(pq, largest);
    }
}

PQ PQinit(int maxN) {
    PQ pq = (PQ)malloc(sizeof(pqueue));
    pq -> heap = (HeapItem )malloc(sizeof(heapItem) * maxN);
    pq -> hash = STinit(maxN);
    pq -> qp = (int*)malloc(sizeof(int) * maxN);
    for (int i = 0; i < maxN; i++) {
        pq -> heap[i].index = -1;
    }
    for (int i = 0; i < maxN; i++) {
        pq -> qp[i] = -1;
    }
    pq -> heapSize = 0;
    return pq;
}

void PQfree(PQ pq) {
    free(pq -> heap);
    free(pq -> hash);
    free(pq -> qp);
    free(pq);
}

int PQempty(PQ pq) {return pq -> heapSize == 0;}

int PQsize(PQ pq) { return pq -> heapSize; }

heapItem PQshowMax(PQ pq) { return pq -> heap[0];}

void PQdisplay(PQ pq) {
    for (int i = 0; i < pq -> heapSize; i++) {
        printf("...\n");
    }
}

void PQinsert(PQ pq, item_t item) {
    int i = pq->heapSize++, index, priority;

    index = STinsert(pq->hash, item);
    priority = STgetPriority(pq->hash, index);

    while ( i >= 1 && pq->heap[PARENT(i)].priority < priority) {
        pq -> heap[i] = pq -> heap[PARENT(i)];
        pq -> qp[pq->heap[i].index] = i;
        i = PARENT(i);
    }
    pq -> heap[i].index = index;
    pq -> heap[i].priority = priority;
    pq -> qp[index] = i;
    return;
}

item_t PQextractMax(PQ pq) {
    item_t temp;
    temp = STgetItem(pq->hash, pq->heap[0].index);
    STdelete(pq->hash, temp);
    Swap(pq, 0, pq->heapSize - 1);
    int index = pq->heap[pq->heapSize - 1].index;
    pq -> qp[index] = -1;
    pq->heapSize--;
    pq->heap[pq->heapSize].index = -1; // ridondante
    HEAPify(pq, 0);
    return temp;

}

void PQchange (PQ pq, item_t item) {
    int index, priority, pos;
    heapItem temp;
    index = STsearch(pq->hash, item);

    if (index == -1) { printf("item not found\n"); return; }
    else printf("found at index: %d\n", index);

    priority = priorityGet(&item);
    STchangePriority(pq->hash, index, priority);

    pos = pq->qp[index];
    temp = pq->heap[pos];
    temp.priority = priority;

    while (pos >= 1 && pq->heap[PARENT(pos)].index < priority) {
        pq ->heap[pos] = pq->heap[PARENT(pos)];
        pq->qp[pq->heap[pos].index] = pos;
        pos = PARENT(pos);

    }

    pq->heap[pos] = temp;
    pq->qp[index] = pos;
    HEAPify(pq, pos);
}
