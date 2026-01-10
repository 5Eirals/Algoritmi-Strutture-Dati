#include "st.h"

struct st_s{
    int len;
    int maxSize;
    vertex* keys;
} st_t;

ST STinit(){
    ST st = (ST) malloc(sizeof(st_t));
    st->len = 0;
    st->maxSize = 2;
    st->keys = (vertex*) malloc(sizeof(vertex) * st->maxSize);
    return st;
}

void STfree(ST st){
    for(int i = 0; i < st->len; i++) {
        free(st->keys[i].id);
        free(st->keys[i].subnet);
    }
    free(st->keys);
    free(st);
}

int STsize(ST st) {
    return st->len;
}

void STprint(FILE* f, ST st){
    for(int i = 0; i < st->len; i++)
        fprintf(f, " %.2d :<%s> <%s> \n", i, st->keys[i].id, st->keys[i].subnet);

    fprintf(f, "\n");
}

void switchVertex(vertex* v1, vertex* v2) {
    str temp_id = v1->id;
    str temp_subnet = v1->subnet;

    v1->id = v2->id;
    v1->subnet = v2->subnet;

    v2->id = temp_id;
    v2->subnet = temp_subnet;
}

void STinsert(ST st, vertex val){
    if(st->len == 0){
        st->keys[0].id = strdup(val.id);
        st->keys[0].subnet = strdup(val.subnet);
        st->len++;
        return;
    }

    if(st->len == st->maxSize){
        st->maxSize *= 2;
        st->keys = (vertex*) realloc(st->keys, sizeof(vertex) * st->maxSize);
    }

    if (STsearch(st, val.id) > -1)
        return;


    st->keys[st->len].id = strdup(val.id);
    st->keys[st->len].subnet = strdup(val.subnet);


    for(int i = st->len; i > 0; i--){
         if(strcmp(st->keys[i].id, st->keys[i-1].id) < 0)
             switchVertex(&st->keys[i-1], &st->keys[i]);
         else
             break;

    }

    st->len++;
}


void STdelete(ST st, int key){
    free(st->keys[key].id);
    free(st->keys[key].subnet);
    for(int i = key; i < st->len-1; i++) {
        st->keys[i] = st->keys[i+1];
    }
    st->len--;
}

str STgetValue(ST st, int key){
    return st->keys[key].id;
}

static int search(vertex* arr, str target, int start, int end){
    int mid = start + (end - start) / 2;
    if(start > end)
        return -1;
    if(strcmp(arr[mid].id, target) == 0)
        return mid;
    if(strcmp(arr[mid].id, target) > 0)
        return search(arr, target, start, mid - 1);
    return search(arr, target, mid + 1, end);
}

int STsearch(ST st, str val){
    return search(st->keys, val, 0, st->len - 1);
}
