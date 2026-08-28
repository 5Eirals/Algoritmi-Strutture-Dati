#include "../SET_ord_vect.h"

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
    int swapped = true;
    if (SETsearch(s, item.key)) return;
    s->vect[s->N] = item;
    s->N++;

    for (int i = s->N - 1; i > 0 && swapped; i--) {
        if (KEYcmp(getKey(&s->vect[i]), getKey(&s->vect[i-1])) == -1) {
            item_t temp = s->vect[i];
            s->vect[i] = s->vect[i-1];
            s->vect[i-1] = temp;
        } else swapped = false;
    }
}

int SETsearch(SET s, Key key) {
    int left= 0, middle, right = s->N - 1;
    while (left <= right) {
        middle = left + (right-left)/2;
        if (KEYcmp(getKey(&s->vect[middle]), key) == 0) {
            return 1;
        }
        if (KEYcmp(getKey(&s->vect[middle]), key) == -1) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return 0;
}

SET SETunion(SET s1, SET s2) {
    int j, i1 = 0, i2 = 0, size1 = SETsize(s1), size2 = SETsize(s2);
    SET s = SETinit(size1 + size2);

    for (j = 0; i1 < size1 || i2 < size2; j++) {
        if (i1 >= size1 ) {
            s->vect[j] = s2->vect[i2++];
        } else if (i2 >= size2) {
            s->vect[j] = s1->vect[i1++];
        } else if (KEYcmp(getKey(&s1->vect[j]), getKey(&s2->vect[j])) == -1) {
            s->vect[j] = s1->vect[i1++];
        } else if (KEYcmp(getKey(&s1->vect[j]), getKey(&s2->vect[j])) == 1) {
            s->vect[j] = s2->vect[i2++];
        } else { // entrambi validi
            s->vect[j] = s1->vect[i1++];
            i2++;
        }
    }
    s->N = j;
    return s;
}

SET SETintersection(SET s1, SET s2) {
    int j = 0, i1 = 0, i2 = 0, size1 = SETsize(s1), size2 = SETsize(s2), minsize = min(size1, size2);
    SET s = SETinit(minsize);

    while ( i1 < size1 && i2 < size2) {
        if (KEYcmp(getKey(&s1->vect[i1]), getKey(&s2->vect[i2])) == 0) {
            s->vect[j++] = s1->vect[i1++];
            i2++;
        } else if (KEYcmp(getKey(&s1->vect[i1]), getKey(&s2->vect[i2])) == -1){
            i1++;
        } else {
            i2++;
        }
    }

    s->N = j;
    return s;
}
