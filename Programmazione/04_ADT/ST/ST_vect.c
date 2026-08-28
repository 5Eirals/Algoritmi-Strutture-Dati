#include "ST_vect.h"

#include <stdio.h>

Key keyGet(item_t item) {
    return item.name;
}

int KEYcmp(Key a, Key b) {
    return a == b ? 0 : a < b ? -1 : 1;
}

static item_t ITEMsetVoid() {
    item_t item;
    item.name = NULL;
    item.val = 0;
    return item;
}

int isItemVoid(item_t item) {
    return item.name == NULL;
}

struct symboltable {
    item_t* a;
    int maxN;
    int size;
};

ST STinit(int maxN) {
    ST st = (ST) malloc(sizeof(st_t));
    st->a = (item_p) malloc(sizeof(item_t) * maxN);

    for (int i = 0; i < maxN; i++)
        st->a[i] = ITEMsetVoid();

    st->maxN = maxN;
    st->size = 0;
    return st;
}

int STcount(ST st) {
    return st->size;
}

void STfree(ST st) {
    free(st->a);
    free(st);
}

void STinsert(ST st, item_t item) {
    int i = st->size++;

    //gestire riallocazione
    if ( st->size == st->maxN ) {
        st -> a = realloc(st -> a, sizeof(item_t) * st->maxN * 2);
        if (st->a == NULL) {
            return;
        }
        st->maxN = st->maxN * 2;
    }
    while ( i > 0 && KEYcmp(keyGet(item), keyGet(st->a[i-1])) == -1) {
        st->a[i] = st->a[i-1];
        i--;
    }
    st->a[i] = item;
}

item_t STsearch(ST st, Key key) {
    int left = 0, right = st->size-1, middle;

    while(left <= right) {
        middle = left + (right - left)/2;
        if (KEYcmp(keyGet(st->a[middle]), key) == 0) {
            return st->a[middle];
        }
        if (KEYcmp(keyGet(st->a[middle]), key) == -1) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return ITEMsetVoid();
}

void STdelete(ST st, Key key) {
    int j=0;
    while (KEYcmp(keyGet(st->a[j]), key) != 0) // trova il dato
        j++;
    for (int i = j; i < st->size-1; i++) // retrocede il vettore
        st->a[i] = st->a[i+1];

    st->size--;

}

item_t STselect(ST st, int r) {
    return st->a[r];
}

void STdisplay(ST st) {
    for (int i = 0; i < st->M; i++) {
        if (!isItemVoid(st->a[i])) {
            printf("%s %d\n", st->a[i].name, st->a[i].val);
        }
    }
}
