#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"

Inventory freadInventory(char* path){
	FILE *file;
	if ((file = fopen(path, "r")) == NULL){
        printf("--- File Error ---\n");
        return NULL;
	}

    Inventory invTable = (Inventory) malloc(sizeof(inventory_s));
    fscanf(file, "%d", &(invTable->N_objects));
    invTable->objects = (Objects) malloc((invTable->N_objects) * sizeof(object_s));
    for (int i = 0; i < invTable->N_objects; i++){
    	fscanf(file, "%s %s %d %d %d %d %d %d",
             invTable->objects[i].name,
             invTable->objects[i].type,
             &(invTable->objects[i].stats.hp),
             &(invTable->objects[i].stats.mp),
             &(invTable->objects[i].stats.atk),
             &(invTable->objects[i].stats.def),
             &(invTable->objects[i].stats.mag),
             &(invTable->objects[i].stats.spr)
             );

    }

    fclose(file);
    return invTable;
}

Object searchObject(Inventory invTable, char* name){
	for(int i = 0; i < invTable->N_objects; i++){
          if (strcmp(name, invTable->objects[i].name) == 0){
            	return &invTable->objects[i];
          }
	}
    printf(">>> Object not found\n");
    return NULL;
}


int max(int a, int b){
	return a > b ? a : b;
}

void printObject(Object obj){
	int width = max(strlen(obj->name), strlen(obj->type)) + 2;
        printf("%.*s\n", STATS_LEN, SEPARATOR);
        printf(" Name: %*.*s%s\n",
               width-strlen(obj->name),
               width-strlen(obj->name),
               SPACER,
               obj->name
               );
        printf(" Class: %*.*s%s\n",
               width-strlen(obj->type),
               width-strlen(obj->type),
               SPACER,
               obj->type);
        printf(" hp:%.3d mp:%.3d atk:%.3d def:%.3d mag:%.3d spr:%.3d\n",
               obj->stats.hp,
               obj->stats.mp,
               obj->stats.atk,
               obj->stats.def,
               obj->stats.mag,
               obj->stats.spr
               );
        printf("%.*s\n", STATS_LEN, SEPARATOR);
}

void freeInventory(Inventory invTable){
	free(invTable->objects);
    free(invTable);
}
