#include "invArray.h"


typedef struct invArray_s{
    inv_t** array;
    int length;
};


invArray_t invArray_init() {
    invArray_t invArray = (invArray_t)malloc(sizeof(struct invArray_s));
    invArray->array = NULL;
    int length = 0;
    return invArray;
};

void invArray_free(invArray_t invArray) {
    for (int i = 0; i < invArray->length; i++) {
        free(invArray->array[i]);
    }
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray) {
    fscanf(fp, "%d", &(invArray->length));
    invArray->array = (inv_t**)malloc(sizeof(inv_t*) * invArray->length);

    for (int i = 0; i < invArray->length; i++){
        invArray->array[i] = (inv_t*)malloc(sizeof(inv_t));
        inv_read(fp, invArray->array[i]);
    }

    fclose(fp);
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, invArray->array[index]);
}

void invArray_print(FILE *fp, invArray_t invArray){
    for(int i = 0; i < invArray->length; i++){
        invArray_printByIndex(fp, invArray, i);
    }
}

inv_t* invArray_getByIndex(invArray_t invArray, int index){
	return invArray->array[index];
}

int invArray_searchByName(invArray_t invArray, char* name){
	for(int i = 0; i < invArray->length; i++) {
	    if(strcmp(invArray->array[i]->name, name) == 0)
	        return i;
	}
	return -1;
}


