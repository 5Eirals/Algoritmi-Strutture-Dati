#include "list.h"

typedef struct node_s {
    int key;
    int flow;
    link next;
} node;


link newNode(int key, int flow){
    link new = (link) malloc(sizeof(node));
    new->key = key;
    new->flow = flow;
    new->next = NULL;
    return new;
}

void freeNode(link node){
    free(node);
}

link nullNode(){
    link n = (link) malloc(sizeof(node));
    n->key = -1;
    n->next = NULL;
    return n;
}

bool isNodeNull(link node){
    if(node->key == -1)
        return true;
    return false;
}

int node_getKey(link node) {
    return node->key;
}

int node_getFlow(link node) {
    return node->flow;
}

link node_getNext(link node) {
    return node->next;
}

list list_init(){
    list l = (list) malloc(sizeof(list_t));
    l->len = 0;
    l->head = nullNode();
    l->tail = l->head;
    return l;
};

void list_insert(list l, link node){
    l->tail->next = node;
    l->tail = node;
    l->len++;
}

void free_head(link head){
    if(head == NULL)
        return;
    free_head(head->next);
    free(head);
}

void list_free(list l){
    free_head(l->head);
}

link list_search(list l, int key){
    for(link curr = l->head->next; curr != NULL; curr = curr->next){
        if(curr->key == key)
            return curr;
    }
    return nullNode();
}

void list_delete(list l, int key){
    for(link curr = l->head->next, prev = l->head; curr != NULL; prev = curr, curr = curr->next){
        if(curr->key == key){
            prev->next = curr->next;
            return;
        }
    }
}