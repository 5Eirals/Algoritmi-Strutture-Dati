#include <stdlib.h>

typedef struct item_s {
    char* name;
    int val;
} item_t, *item_p;
typedef char* Key;

typedef struct symboltable *ST, st_t;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, item_t item);
item_t STsearch(ST, Key key);
void STdelete(ST st, Key key);
item_t STselect(ST st, int r); // r = rango: numero della chiave
void STdisplay(ST st);