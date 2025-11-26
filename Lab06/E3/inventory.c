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

void printObject(Object obj){
	printf("*___________________________________________________________________________*\n"
           "  <%50s>\nType: <%50s>\nStats:\n"
           "  hp:%.3d mp:%.3d atk:%.3d def:%.3d mag:%.3d spr:%.3d\n"
           "*___________________________________________________________________________*\n",
         obj->name,
         obj->type,
         obj->stats.hp,
         obj->stats.mp,
         obj->stats.atk,
         obj->stats.def,
         obj->stats.mag,
         obj->stats.spr);
}

void freeInventory(Inventory invTable){
	free(invTable->objects);
    free(invTable);
}
