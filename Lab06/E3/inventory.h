#ifndef INVENTORY_H
#define INVENTORY_H

#endif

#define MAX_LEN 50

typedef struct stats_s{
	int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} Stats;

typedef struct {
	char name[MAX_LEN];
    char type[MAX_LEN];
    Stats stats;
}object_s, *Object, *Objects;

typedef struct {
	Objects objects;
    int N_objects;
}inventory_s, *Inventory;

Inventory freadInventory(char* path);
void freeInventory(Inventory inventory);
Object searchObject(Inventory invTable, char* name);
void printObject(Object obj);

