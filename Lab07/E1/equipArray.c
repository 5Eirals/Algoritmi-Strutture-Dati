#include "equipArray.h"


typedef struct  equipArray_s{
    int inv[EQUIP_SLOT];
    int inUse;
};

equipArray_t equipArray_init(){
    equipArray_t equipArray = (equipArray_t)malloc(sizeof(struct equipArray_s));
    equipArray->inUse = 0;

    return equipArray;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUse;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
	for(int i = 0; i < equipArray->inUse; i++){
        invArray_printByIndex(fp, invArray, equipArray->inv[i]);
	}
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    return equipArray->inv[index];
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    char name[LEN];
    printf("Inserisci il nome dell'oggetto da inserire nell'inventario:\n");
    scanf(" %s", name);
    int index = invArray_searchByName(invArray, name);
    if(index == -1) {
        printf("Oggetto '%s' non trovato\n", name);
    } else {
        if (equipArray->inUse == EQUIP_SLOT) {
            printf("L'inventario è già pieno\n");
        } else {
            equipArray->inv[equipArray->inUse++] = index;
        }
    }
}


