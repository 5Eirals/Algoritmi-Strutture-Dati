#include <stdlib.h>

typedef struct item_s {
    int key;
    int val;
} item_t, *Item;
typedef int Key;

typedef struct queue_s queue_t, *QUEUE;

QUEUE QUEUEinit(int maxN);
void QUEUEput(QUEUE q, item_t item);
item_t QUEUEget(QUEUE q);
int QUEUEempty(QUEUE q);