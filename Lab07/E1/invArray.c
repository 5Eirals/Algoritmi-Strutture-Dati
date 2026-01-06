#include "invArray.h"


typedef struct invArray_s {
    inv_t** array;
    int length;
};

static int max(int a, int b) {
    return a > b ? a : b;
}

invArray_t invArray_init() {
    invArray_t invArray = (invArray_t)malloc(sizeof(invArray_s));
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
    char* name_b, type_b;

    for (int i = 0; i < invArray->length; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d",
             name_b,
             type_b,
             &(invArray->array[i]->stat.hp),
             &(invArray->array[i]->stat.mp),
             &(invArray->array[i]->stat.atk),
             &(invArray->array[i]->stat.def),
             &(invArray->array[i]->stat.mag),
             &(invArray->array[i]->stat.spr)
             );
        strcpy(invArray->array[i]->name, name_b);
    }

    fclose(fp);
}

void fprintStat(FILE *fp, stat_t stat){
    fprintf(fp, " hp:%.3d mp:%.3d atk:%.3d def:%.3d mag:%.3d spr:%.3d\n",
          stat.hp > 0 ? stat.hp : 1,
          stat.mp > 0 ? stat.mp : 1,
          stat.atk > 0 ? stat.atk : 1,
          stat.def > 0 ? stat.def : 1,
          stat.mag > 0 ? stat.mag : 1,
          stat.spr > 0 ? stat.spr : 1
    );
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    int width = max(strlen(invArray->array[index]->name), strlen(invArray->array[index]->type)) + 2;
    fprintf(fp, "%.*s\n", LN_LEN, SEPARATOR);
    fprintf(fp, " Name: %*.*s%s\n",
           width-strlen(invArray->array[index]->name),
           width-strlen(invArray->array[index]->name),
           SPACER,
           invArray->array[index]->name
           );
    fprintf(fp, " Class: %*.*s%s\n",
           width-strlen(invArray->array[index]->type),
           width-strlen(invArray->array[index]->type),
           SPACER,
           invArray->array[index]->type);
    fprintStat(fp, invArray->array[index]->stat);
    fprintf(fp, "%.*s\n", LN_LEN, SEPARATOR);
}

void invArray_print(FILE *fp, invArray_t invArray){
    for(int i = 0; i < invArray->length; i++){
        invArray_printByIndex(fp, invArray, i);
    }
}

inv_t* invArray_getByIndex(invArray_t invArray, int index){
  return invArray->array[index];
}


