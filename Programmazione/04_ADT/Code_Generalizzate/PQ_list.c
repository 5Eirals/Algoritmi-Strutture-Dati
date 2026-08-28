#include "PQ_list.h"

struct node_s {
    item_t item;
    link next;
};

struct pqueue_s {
    link head;
};

int KEYcmp(Key a, Key b) {
    return a == b ? 0 : a < b ? -1 : 1;
}

Key getKey(item_p item) {
    return item->key;
}

void itemDisplay(item_p item) {
    printf("key:%d val:%d\n", item->key, item->val);
}
static link NEW (item_t item, link next) {
    link x = (link) malloc(sizeof(node_t));
    x->item = item;
    x->next = next;
    return x;
}

PQ PQinit(int maxN) {
    PQ pq = (PQ) malloc(sizeof(pqueue_t));
    pq->head = NULL;
    return pq;
}

int PQempty(PQ pq) {
    return pq->head == NULL;
}

item_t PQshowMax(PQ pq) {
    return pq->head->item;
}

void PQdisplay(PQ pq) {
    for (link x = pq->head; x != NULL; x = x->next) {
        itemDisplay(& x->item);
    }
    return;
}

void PQinsert(PQ pq, item_t item) {
    Key key = getKey(&item);
    if (pq->head == NULL && KEYcmp(key, getKey(&pq->head->item))==-1) {
        pq->head = NEW (item, pq->head);
        return;
    }

    link x, p;
    for (x = pq->head->next, p = pq->head; x != NULL && KEYcmp(key, getKey(&pq->head->item))==-1; p = x, x = x->next) {}
    p->next = NEW (item, x);

    return;
}

item_t PQextractMax(PQ pq) {
    item_t item;
    link t;
    if (PQempty(pq)) {
        printf("PQ empty\n");
        return ITEMsetVoid();
    }

    item = pq->head->item;
    t = pq->head->next;
    free(pq->head);
    pq->head = t;
    return item;
}

void PQchange(PQ pq, item_t item) {
    if (PQempty(pq)) {
        printf("PQ empty\n");
        return;
    }

    for (link x = pq->head, p = NULL; x != NULL; p =x, x = x->next) {
        if (KEYcmp(getKey(&item), getKey(& x->item))==0) {
            if (x == pq->head) {
                pq->head = x->next;
            } else {
                p->next = x->next;
            }
            free(x);
            break;
        }
    }

    PQinsert(pq, item);
    return;
}


