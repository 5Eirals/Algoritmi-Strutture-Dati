#include "PQ_vect.h"

int KEYcmp(Key a, Key b) {
    return a == b ? 0 : a < b ? -1 : 1;
}

Key getKey(item_p item) {
    return item->key;
}

void itemDisplay(item_p item) {
    printf("key:%d val:%d\n", item->key, item->val);
}

struct pqueue_s {
    item_t* q;
    int N;
};

PQ PQinit(int maxN) {
    PQ pq = (PQ) malloc(sizeof(pqueue_t));
    pq->q = (item_p) malloc(sizeof(item_t)*maxN);
    pq->N = 0;
    return pq;
}

int PQempty(PQ pq){return pq->N == 0;}

void PQinsert(PQ pq, item_t item) {
    int i = pq->N++;
    pq->q[i] = item;

    while(i > 0 && KEYcmp(getKey(&pq->q[i-1]), getKey(&pq->q[i])) == 1) {
        item_t temp = pq->q[i];
        pq->q[i] = pq->q[i-1];
        pq->q[i-1] = temp;

        i--;
    }
}

item_t PQextractMax(PQ pq) {
    return pq->q[--(pq->N)];
}
item_t PQshowMax(PQ pq) {
    itemDisplay(& pq->q[pq->N-1]);
    return pq->q[pq->N-1];
}
void PQdisplay(PQ pq) {
    for(int i = 0; i < pq->N; i++) {
        itemDisplay(& pq->q[i]);
    }
}

int PQsearch(PQ pq, item_t item) {
    int left = 0, right = pq->N-1, middle;
    Key key = getKey(&item);

    while(left <= right) {
        middle = left + (right - left)/2;
        if (KEYcmp(getKey(&pq->q[middle]), key) == 0) {
            return middle;
        }
        if (KEYcmp(getKey(&pq->q[middle]), key) == -1) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}

void PQchange(PQ pq, item_t item) {
    int index = PQsearch(pq, item);
    if(index == -1) {
        printf("Item not found \n");
        return;
    }

    pq->q[index] = item;

    //fixdown
    int i = index;
    while(i > 0 && KEYcmp(getKey(&pq->q[i-1]), getKey(&pq->q[i])) == 1) {
        item_t temp = pq->q[i];
        pq->q[i] = pq->q[i-1];
        pq->q[i-1] = temp;

        i--;
    }

    //fixup
    if (i == index)
        while(i < pq->N - 1 && KEYcmp(getKey(&pq->q[i+1]), getKey(&pq->q[i])) == -1) {
            item_t temp = pq->q[i];
            pq->q[i] = pq->q[i+1];
            pq->q[i+1] = temp;

            i++;
        }

    return;
}