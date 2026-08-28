#include "QUEUE_list.h"

struct queue_s {
    link head;
    link tail;
};

static link NEW (item_t item, link next) {
    link x = (link) malloc(sizeof(node_t));
    x->item = item;
    x->next = next;
    return x;
}

QUEUE QUEUEinit(int maxN) {
    QUEUE q = (QUEUE) malloc(sizeof(queue_t));
    q->head = NULL;
    return q;
}

int QUEUEempty(QUEUE q) {
    return q->head == NULL;
}

void QUEUEput(QUEUE q, item_t item) {
    if (q->head == NULL) {
        q->tail = NEW (item, q->head);
        q->head = q->tail;
        return;
    }

    q->tail->next = NEW (item, q->tail->next);
    q->tail = q->tail->next;
    return;
}

int QUEUEget(QUEUE q) {
    item_t item = q->head->item;
    link t = q->head->next;
    free(q->head);
    q->head = t;
    return item;
}
