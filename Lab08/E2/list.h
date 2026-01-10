#ifndef LIST_H
#define LIST_H

#include "stdsymb.h"

typedef struct node_s *link;

typedef struct list_s{
    int len;
    link head;
    link tail;
}list_t, *list;

list list_init();
link newNode(int key, int flow);
link node_getNext(link node);
bool isNodeNull(link node);
int node_getFlow(link node);
int node_getKey(link node);
void list_free(list list);
void list_insert(list list, link node);
void list_delete(list list, int key);
link list_search(list list, int key);

#endif
