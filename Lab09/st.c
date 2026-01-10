#include "st.h"

typedef struct st_s{
    int len;
    str* keys;
} st_t;

ST STinit(){
    ST st = (ST) malloc(sizeof(st_t));
    st->len = 0;
    return st;
}

void STload( FILE *f, ST st) {
    fscanf(f, "%d", &st->len);
    st->keys = (str*) malloc(sizeof(str) * st->len);

    for(int i = 0; i < st->len; i++) {
        str holder = (str) malloc(sizeof(char)*MAX_SIZE);
        fscanf(f, " %s ", holder);
        st->keys[i] = strdup(holder);
        free(holder);
    }
}

void STfree(ST st){
    for(int i = 0; i < st->len; i++) {
        free(st->keys[i]);
    }
    free(st->keys);
    free(st);
}

int STsize(ST st) {
    return st->len;
}

void STprint(FILE* f, ST st){
    for(int i = 0; i < st->len; i++)
        fprintf(f, " %.2d :<%s> \n", i, st->keys[i]);

    fprintf(f, "\n");
}


void STdelete(ST st, int key){
    free(st->keys[key]);
    for(int i = key; i < st->len-1; i++) {
        st->keys[i] = st->keys[i+1];
    }
    st->len--;
}

str STgetValue(ST st, int key){
    return st->keys[key];
}

int STsearch(ST st, str val){
    for (int i = 0; i < st->len; i++)
        if(strcmp(st->keys[i], val) == 0)
            return i;
    return -1;
}
