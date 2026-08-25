#include "PriorityQueue_base.h"

void printItem(Item item) {
    printf(" Data:%03d-Priority:%03d;", item->data, item->priority);
}

int priorityGet(Item item) {
    return item->priority;
}
int keyPriorityCmp(Item item1, Item item2) {
    return item1->priority - item2->priority;
}

int dataCmp(Item item1, Item item2) {
    return item1->data - item2->data;
}

int LEFT(int index) {return 2 * index + 1;}
int RIGHT(int index) {return 2 * index + 2;}
int PARENT(int index) {return (index-1)/2;}
void Swap(PQ pq, int index1, int index2) {
    Item item1 = pq -> A[index1];
    pq -> A[index1] = pq -> A[index2];
    pq -> A[index2] = item1;
}

void HEAPify(Heap heap, int index) {
    int left, right, largest;
    left = LEFT(index);
    right = RIGHT(index);
    if (left < heap -> len && keyItemCmp(heap -> A[left], heap -> A[index]) > 0) {
        largest = left;
    } else {
        largest = index;
    }
    if (right < heap -> len && keyItemCmp(heap -> A[right], heap -> A[largest]) > 0) {
        largest = right;
    }
    if (largest != index) {
        Swap(heap, index, largest);
        HEAPify(heap, largest);
    }
}

PQ PQinit(int maxN) {
    PQ pq = (PQ)malloc(sizeof(struct PQ));
    pq -> A = (Item )malloc(sizeof(item_t) * maxN);
    pq -> heapSize = 0;
}

void PQfree(PQ pq) {
    free(pq -> A);
    free(pq);
}

int PQempty(PQ pq) {return pq -> heapSize == 0;}

int PQsize(PQ pq) { return pq -> heapSize; }

item_t PQshowMax(PQ pq) { return pq -> A[0];}

void PQdisplay(PQ pq) {
    for (int i = 0; i < pq -> heapSize; i++) {
        printItem(&pq -> A[i]);
    }
}

void PQinsert(PQ pq, item_t item) {
    int i = pq->heapSize++;
    while ( i >= 1 && keyPriorityCmp(&pq->A[PARENT(i)], &item)==-1 ) {
        pq -> A[i] = pq -> A[PARENT(i)];
        i = PARENT(i);
    }
    pq -> A[i] = item;
    return;
}

item_t PQextractMax(PQ pq) {
    item_t temp;
    Swap(pq, 0, pq->heapSize - 1);
    pq->heapSize--;
    HEAPify(pq, 0);
    return temp;

}

void PQchange (PQ pq, item_t item) {
    int found = 0, pos;

    //scansione O(n)
    for (int i = 0; i < pq -> heapSize && found == 0; i++) {
        if (dataCmp(&pq -> A[i], &item)==0) {
            found = 1;
            pos = i;
        }
    }

    if (found == 1) {
        //fixup
        while (pos >= 1 && priorityGet(&pq -> A[PARENT(pos)]) < priorityGet(&item)) {
            pq -> A[pos] = pq -> A[PARENT(pos)];
            pos = PARENT(pos);
        }
        //fixdown
        pq -> A[pos] = item;
        HEAPify(pq, pos);
    } else
        printf("Key not Found \n");
    return;
}