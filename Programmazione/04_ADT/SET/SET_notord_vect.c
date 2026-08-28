#include "../SET_notord_vect.h"

struct set_s {
    Item vect;
    int N;
};

int min(int a, int b) {
    return a < b ? a : b;
}

int KEYcmp(Key a, Key b) {
    return a == b ? 0 : a < b ? -1 : 1;
}

Key getKey(Item item) {
    return item->key;
}

SET SETinit(int maxN) {
    SET s = (SET) malloc(sizeof(set_t));
    s->vect = (Item)malloc(sizeof(item_t) * maxN);
    s->N = 0;
    return s;
}

void SETfree(SET s) {
    free(s->vect);
    free(s);
}

int SETsize(SET s) {
    return s->N;
}

void SETfill(SET s, item_t item) {
    if (SETsearch(s, item.key)) return;
    s->vect[s->N] = item;
    s->N++;
}

int SETsearch(SET s, Key key) {
    for (int i = 0; i < s->N; i++) {
        if (KEYcmp(getKey(&s->vect[i]), key) == 0) {
            return 1;
        }
    }

    return 0;
}

SET SETunion(SET s1, SET s2) {
    // ordina e poi SETunion ordinato oppure
    int size1 = SETsize(s1), size2 = SETsize(s2);
    SET s = SETinit(size1 + size2);

    for (int i1 = 0; i1 < size1; i1++) {
        SETfill(s, s1->vect[i1]);
    }

    for (int i2 = 0; i2 < size2; i2++) {
        SETfill(s, s2->vect[i2]);
    }
    return s;
}

SET SETintersection(SET s1, SET s2) {
    int j = 0, size1 = SETsize(s1), size2 = SETsize(s2), minsize = min(size1, size2);
    SET s = SETinit(minsize);

    for (int i1 = 0; i1 < size1; i1++) {
        if (SETsearch(s2, s1->vect[i1].key)) {
            s->vect[j++] = s1->vect[i1];
        }
    }

    s->N = j;
    return s;
}
