#include "ST_list.h"

#include <stdio.h>

typedef struct node_s node_t, *link;
struct node_s {
    item_t val;
    link next;
};

typedef struct list_s list_t, *list_p;
struct list_s {
    link head;
    int size;
};

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

static link NEW (item_t item, link next) {
    link x = (link)malloc(sizeof(node_t));
    if (x == NULL) {
        return NULL;
    }
    x->val = item;
    x->next = next;

    return x;
}

struct symboltable {
    list_t tab;
};

ST STinit(int maxN) {
    ST st = (ST) malloc(sizeof(st_t));
    if (st == NULL) return NULL;
    st->tab.head = NULL;
    st->tab.size = 0;
    return st;
}

int STcount(ST st) {
    return st->tab.size;
}

void STfree(ST st) {
    if (st == NULL) return;

    link x = st->tab.head;
    while (x != NULL) {
        link tmp = x;
        x = x->next;
        free(tmp); // free the key if it's a dynamic string/vector
    }
    free(st);
}

void STinsert(ST st, item_t item) {

    if (st == NULL) return;

    if (st->tab.head == NULL || KEYcmp(keyGet(item), keyGet(st->tab.head->val)) == -1)
        st->tab.head = NEW(item, st->tab.head);
    else
        for (link x = st->tab.head->next, p = st->tab.head; x != NULL && KEYcmp(keyGet(item), keyGet(x->val)) == -1; p = x, x = x->next)
                p->next = NEW(item, x);

    st->tab.size++;
    return;
}

item_t STsearch(ST st, Key key) {

    if (st == NULL) return ITEMsetVoid();
    if (st->tab.head == NULL) return ITEMsetVoid();

    for (link x = st->tab.head; x != NULL && KEYcmp(key, keyGet(x->val)) == -1; x = x->next)
        if (KEYcmp(key, keyGet(x->val)) == 0)
            return x->val;

    return ITEMsetVoid();
}

void STdelete(ST st, Key key) {
    if (st == NULL) return;
    if (st->tab.head == NULL) return;

    for (link x = st->tab.head, p = NULL; x != NULL && KEYcmp(key, keyGet(x->val)) == -1; p = x, x = x->next) {
        if (KEYcmp(key, keyGet(x->val)) == 0) {
            if (p == NULL)
                st->tab.head = x->next;
            else
                p->next = x->next;

            free(x);
            break;
        }
    }

    st->tab.size--;
}

item_t STselect(ST st, int r) {
    link x = st->tab.head;
    for (int i = 0 ; i < r ; i++)
        x = x->next;
    return x->val;
}

void STdisplay(ST st) {
    for (link x = st->tab.head; x != NULL; x = x->next) {
        if (!isItemVoid(x->val)) {
            printf("%s %d\n", x->val.name, x->val.val);
        }
    }
}
