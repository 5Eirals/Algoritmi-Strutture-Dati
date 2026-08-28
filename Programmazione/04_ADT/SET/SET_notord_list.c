#include "../SET_notord_list.h"

struct set_s {
    link head;
    int N;
};

int KEYcmp(Key a, Key b) {
    return a == b ? 0 : a < b ? -1 : 1;
}

Key getKey(Item item) {
    return item->key;
}

SET SETinit(int maxN) {
    SET s = (SET) malloc(sizeof(set_t));
    s->head = NULL;
    s->N = 0;
    return s;
}

void SETfree(SET s) {
    link t;
    for (link x = s->head; x != NULL; x = t) {
        t = x->next;
        free(x);
    }
    free(s);
}

void SETfill(SET s, item_t item) {
    link newNode = (link) malloc(sizeof(node));
    newNode->item = item;
    newNode->next = s->head;
    s->head = newNode;
    return;
}

int SETsearch(SET s, Key key) {
    for (link x = s->head; x != NULL; x = x->next) {
        if (KEYcmp(getKey(&x->item), key) == 0) {
            return 1;
        }
    }
    return 0;
}

SET SETunion(SET s1, SET s2) {
    link x1, x2;
    int found, count = 0;
    SET s = SETinit(s1->N+s2->N);
    for (x1 = s1->head; x1 != NULL; x1 = x1->next) {
        SETfill(s, x1->item);
    }
    for (x2 = s2->head; x2 != NULL; x2 = x2->next) {
        x1 = s1->head;
        found = 0;
        while (x1 != NULL && found == 0) {
            if (KEYcmp(getKey(&x1->item), getKey(&x2->item)) == 0) {
                found = 1;
            }
            x1 = x1->next;
        }
        if (found == 0) {
            SETfill(s, x2->item);
            count++;
        }
    }
    s->N = s1->N + count;
    return s;
}

SET SETintersection(SET s1, SET s2) {
    link x1, x2;
    int count = 0;
    SET s = SETinit(s1->N+s2->N);
    x1 = s1->head;
    for (x1 = s1->head; x1 != NULL; x1 = x1->next) {
        x2 = s2->head;
        for (x2 = s2->head; x2 != NULL; x2 = x2->next) {
            if (KEYcmp(getKey(&x1->item), getKey(&x2->item)) == 0) {
                SETfill(s, x1->item);
                count++;
                break;
            }
        }
    }
    s->N = count;
    return s;
}
