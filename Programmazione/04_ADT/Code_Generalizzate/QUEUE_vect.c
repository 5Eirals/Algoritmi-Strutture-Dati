#include "QUEUE_vect.h"

//implemented through a circular buffer array -> head and tails are only incremented, the mod N allows for cyclicity

struct queue_s {
    item_t* q;
    int N;
    int head;
    int tail;
};

QUEUE QUEUEinit(int maxN) {
    QUEUE q = (QUEUE) malloc(sizeof(queue_t));
    q->q = (item_t *) malloc(sizeof(item_t) * maxN);
    q -> N = maxN+1;
    q->head = q->N;
    q -> tail = 0;
    return q;
}

void QUEUEput(QUEUE q, item_t item) {
    q -> q[q -> tail++] = item;
    q -> tail = q -> tail % q -> N;
}

item_t QUEUEget(QUEUE q) {
    q -> head = q -> head % q -> N;
    return q -> q[q -> head++];
}

int QUEUEempty(QUEUE q) {
    return (q->head)%(q->N) == q->tail;
}
