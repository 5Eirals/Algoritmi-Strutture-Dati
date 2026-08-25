#include <stdio.h>
#include <stdlib.h>

typedef struct item {
    int data;
    int priority;
} *Item;

typedef struct heap {
    Item A;
    int len;
} Heap;

void printItem(Item item);
int keyGet(Item item);
int keyItemCmp(Item item1, Item item2);

int LEFT(int index);
int RIGHT(int index);
int PARENT(int index);

Heap HEAPinit(int maxSize);
void HEAPfree(Heap heap);
void HEAPfill(Heap heap, Item item);
void printHeap(Heap heap);
void HEAPify(Heap heap, int index);
void HEAPbuild(Heap heap);
void HEAPsort(Heap heap);

