#include "../SET_ord_list.h"

struct set_s {
    link head;
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
    for (link x = s->head, p = NULL; x != NULL; p = x, x = x->next) {
        if (KEYcmp(getKey(&x->item), getKey(&item)) == 0)
            break;
        if (KEYcmp(getKey(&x->item), getKey(&item)) == 1) {
            newNode->next = x;
            if (p == NULL) {
                s ->head = newNode;
            } else {
                p->next = newNode;
            }
            s->N++;
            break;
        }
    }

    return;
}

int SETsearch(SET s, Key key) {
    for (link x = s->head; x != NULL; x = x->next) {
        if (KEYcmp(getKey(&x->item), key) == 0) {
            return 1;
        }
        if (KEYcmp(getKey(&x->item), key) == 1) {
            return 0;
        }
    }
    return 0;
}

SET SETunion(SET s1, SET s2) {
    link x1 = s1->head, x2 = s2->head;
    int j = 0;
    SET s = SETinit(s1->N + s2->N);

    link xs = s1->head;
    link heads = (link) malloc(sizeof(node));
    heads->next = NULL;

    if (KEYcmp(getKey(&x1->item), getKey(&x2->item)) == 1) {
        heads -> item = x2->item;
        xs->next = heads;
        xs = heads;
        x2 = x2->next;
    } else {
        heads -> item = x1->item;
        xs->next = heads;
        xs = heads;
        x1 = x1->next;
    }


    while (x1 != NULL || x2 != NULL) {
        link newNode = (link) malloc(sizeof(node));
        newNode ->next = NULL;

        if (x1 == NULL ) {
            newNode -> item = x2->item;
            xs->next = newNode;
            xs = newNode;
            x2 = x2->next;
        } else if (x2 == NULL) {
            newNode -> item = x1->item;
            xs->next = newNode;
            xs = newNode;
            x1 = x1->next;
        } else if (KEYcmp(getKey(&x1->item), getKey(&x2->item)) == -1) {
            newNode -> item = x1->item;
            xs->next = newNode;
            xs = newNode;
            x1 = x1->next;
        } else if (KEYcmp(getKey(&x1->item), getKey(&x2->item)) == 1) {
            newNode -> item = x2->item;
            xs->next = newNode;
            xs = newNode;
            x2 = x2->next;
        } else { // entrambi validi
            newNode -> item = x2->item;
            xs->next = newNode;
            xs = newNode;
            x1 = x1->next;
            x2 = x2->next;
        }

        j++;
    }
    s->N = j;
    return s;
}

SET SETintersection(SET s1, SET s2) {
    link x1, x2, xs;
    int count = 0;
    SET s = SETinit(s1->N+s2->N);
    xs = s->head;
    x1 = s1->head;
    x2 = s2->head;

    while (x1 != NULL && x2 != NULL) {
        if (KEYcmp(getKey(&x1->item), getKey(&x2->item)) == 0) {
            link newNode = (link) malloc(sizeof(node));
            newNode -> item = x1->item;
            newNode -> next = NULL;
            if (xs != NULL) {
                xs->next = newNode;
            }
            xs = newNode;
            x1 = x1->next;
            x2 = x2->next;
            count++;
        } else if (KEYcmp(getKey(&x1->item), getKey(&x2->item)) == -1) {
            x1 = x1->next;
        } else {
            x2 = x2->next;
        }
    }

    s->N = count;
    return s;
}
