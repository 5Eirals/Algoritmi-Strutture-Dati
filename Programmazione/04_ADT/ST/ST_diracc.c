#include "ST_diracc.h"

#include <stdio.h>

// // funzione variabile a seconda della codifica che si vuole implementare
// int GETindex(Key k) { // per chiavi alfabetica A-Z
//     int i = k - 'A';
//     return i;
// }
//
// int GETindex(Key k) { //range numerico da 0 a M-1
//     int i = (int) k;
//     return i;
// }

int GETindex(Key k) { // chiavi come stringhe di lungezza fissa e corta (esplode troppo velocemente) si valutano come polinomi di base 26
    int i = 0, b = 26;
    for (; *k != '\0'; k++) //*k carattere corrente della stringa
        i = (b*i + (*k - ((int) 'A')));

    return i;

}

Key keyGet(item_t item) {
    return item.name;
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
    int N;
    int M;
};

ST STinit(int maxN) {
    ST st = (ST) malloc(sizeof(st_t));
    st->a = (item_p) malloc(sizeof(item_t) * maxN);

    for (int i = 0; i < maxN; i++)
        st->a[i] = ITEMsetVoid();

    st->M = maxN;
    st->N = 0;
    return st;
}

int STcount(ST st) {
    return st->N;
}

void STfree(ST st) {
    free(st->a);
    free(st);
}

void STinsert(ST st, item_t item) {
    int index = GETindex(keyGet(item));
    st->a[index] = item;
    st->N++;
}

item_t STsearch(ST st, Key key) {
    int index = GETindex(key);
    return st->a[index];
}

void STdelete(ST st, Key key) {
    st->a[GETindex(key)] = ITEMsetVoid();
    st->N--;
}

item_t STselect(ST st, int r) {
    for (int i = 0; i < st->M; i++) {
        if (!isItemVoid(st->a[i]) && r-- == 0) {
            return st->a[i];
        }
    }
    return ITEMsetVoid();
}

void STdisplay(ST st) {
    for (int i = 0; i < st->M; i++) {
        if (!isItemVoid(st->a[i])) {
            printf("%s %d\n", st->a[i].name, st->a[i].val);
        }
    }
}