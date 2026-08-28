#include "STACK_vect.h"

#include <stdlib.h>

struct stack_s {
    Item s;
    int N;
};

STACK STACKinit(int maxN) {
    STACK sp = (STACK)malloc(sizeof(stack_t));
    sp -> s = (Item)malloc(sizeof(item_t) * maxN);
    sp -> N = 0;
    return sp;
}

int STACKempty(STACK sp) {
    return sp -> N == 0;
}

void STACKpush(STACK sp, item_t item) {
    sp->s[sp -> N++] = item;
}

item_t STACKpop(STACK sp) {
    return sp->s[--(sp -> N)];
}