#include <stdio.h>
#include <stdlib.h>

#define MAXC 255

// default values fro compiler
typedef void* Key;
typedef void* Item;

//type1
typedef int item_1;
typedef int Key_1;

//type2
typedef char *Item_2;
typedef char *Key_2;

//type3
typedef struct item_t3 {
    char name[MAXC];
    int num;
} item_3, *Item_3;
typedef char* Key_3;

//type4
typedef struct item_t4 {
    char* name;
    int num;
} item_4, *Item_4;
typedef char* Key_4;

//interfacce

int KEYcompare(Key k1, Key k2);
Key KEYscan();
Item ITEMscan();
Item ITEMnew();
void ITEMfree(Item item);
void ITEMshow(Item item);
int ITEMcompare(Item item1, Item item2);
int ITEMcheckVoid(Item item);
Item ITEMsetVoid();