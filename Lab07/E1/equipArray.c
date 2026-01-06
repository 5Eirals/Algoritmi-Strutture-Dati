#include "equipArray.h"


typedef struct equipArray_s {
    invArray_t invArray;
    int inUse;
} *equipArray_t;

equipArray_t equipArray_init(){
    equipArray_t equipArray = (equipArray_t)malloc(sizeof(equipArray_s));
    equipArray->inUse = 0;
    equipArray->invArray = invArray_init();

    return equipArray;
}

void equipArray_free(equipArray_t equipArray){
    invArray_free(equipArray->invArray);
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUse;
}


