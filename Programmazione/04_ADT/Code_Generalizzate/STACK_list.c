#include "STACK_list.h"

#include <stdlib.h>

static link NEW (item_t item, link next) {
    link x = (link) malloc(sizeof(node));
    x->item = item;
    x->next = next;
    return x;
}

STACK STACKinit(int maxN) {
    STACK sp = (STACK) malloc(sizeof(stack_t));
    sp->head = NULL;
    return sp;
}

int STACKempty(STACK s) {
    return s->head == NULL;
}

void STACKpush(STACK s, item_t item) {
    s->head = NEW (item, s->head);
}

item_t STACKpop(STACK s) {
    item_t item = s->head->item;
    link t = s->head->next;
    free(s->head);
    s->head = t;
    return item;
}