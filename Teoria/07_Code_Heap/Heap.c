#include "Heap.h"

void printItem(Item item) {
    printf(" Data:%03d-key:%03d;", item->data, item->key);
}
int keyGet(Item item) {
    return item->key;
}

int keyItemCmp(Item item1, Item item2) {
    return item1->key - item2->key;
}

int LEFT(int index) {return 2 * index + 1;}
int RIGHT(int index) {return 2 * index + 2;}
int PARENT(int index) {return (index-1)/2;}
void Swap(Heap heap, int index1, int index2) {
    Item item1 = heap -> A[index1];
    heap -> A[index1] = heap -> A[index2];
    heap -> A[index2] = item1;
}

Heap HEAPinit(int maxSize) {
    Heap heap;
    heap = (Heap) malloc(sizeof(struct heap));
    heap -> A = (Item *) malloc(sizeof(Item) * maxSize);
    heap -> len = 0;
    return heap;
}

void HEAPfree(Heap heap) {
    free(heap -> A);
    free(heap);
}

void HEAPfill(Heap heap, Item item) {
    int index = 0;
    index = heap -> len++;
    heap -> A[index] = item;
    return;
}

void printHeap(Heap heap) {
    for (int i = 0; i < heap -> len; i++) {
        printItem(heap -> A[i]);
    }
}

void HEAPify(Heap heap, int index) {
    int left, right, largest;
    left = LEFT(index);
    right = RIGHT(index);
    if (left < heap -> len && keyItemCmp(heap -> A[left], heap -> A[index]) > 0) {
        largest = left;
    } else {
        largest = index;
    }
    if (right < heap -> len && keyItemCmp(heap -> A[right], heap -> A[largest]) > 0) {
        largest = right;
    }
    if (largest != index) {
        Swap(heap, index, largest);
        HEAPify(heap, largest);
    }
}

void HEAPbuild(Heap heap) {
    for (int i = (heap->len)/2-1; i >= 0; i--) {
        HEAPify(heap, i);
    }
}

void HEAPsort(Heap heap) {
    int size = heap -> len;
    HEAPbuild(heap);
    for (int i = heap -> len-1; i > 0; i--) {
        Swap(heap, i, 0);
        heap -> len--;
        HEAPify(heap, 0);
    }

    heap -> len = size; 
}