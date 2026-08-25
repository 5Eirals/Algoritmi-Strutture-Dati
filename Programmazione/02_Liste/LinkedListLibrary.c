#include <stdio.h>
#include <stdlib.h>



typedef struct item {
    int value;
    int key;
} Item, *Item_p;

typedef struct node* link;
typedef struct node {
    Item item;
    link next;
} Node;

typedef struct list* List_p;
typedef struct list {
    link head;
    link tail;
    int len;
} List;


link newNode(int value, int key, link next);
void printNode(link node);
void freeNode(link node);
void initList(List_p liked_list);
void insertTail(List_p list, int value, int key);
void insertHead(List_p list, int value, int key);
void cancelNode(List_p list, int key);
int findNode(List_p list, int key);
void printList(List_p list);
void freeList(List_p list);


int main(void) {
    List_p linked_list = (List_p)malloc(sizeof(List));
    initList(linked_list);

    return 0;
}


link newNode(int val, int key, link next) {
    link n = (link)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Insufficient memory\n");
        return NULL;
    }

    n->item.value = val;
    n->item.key = key;
    n->next = next;

    return n;
}

void printNode(link node) {
    printf(" value: %03d , key: %03d \n", node->item.value, node->item.key);
}

void freeNode(link node) {
    free(node);

}

void initList(List_p liked_list) {
    liked_list->head = NULL;
    liked_list->tail = NULL;
    liked_list->len = 0;

}

void printList(List_p list) {
    for (link node = list->head; node != NULL; node = node->next) {
        printNode(node);
    }
}
void freeDf(link head) {
    if (head != NULL) {
        freeDf(head->next);
        freeNode(head);
    }
}

void freeList(List_p list) {
    freeDf(list->head);
    free(list);
}

void insertTail(List_p list, int value, int key) {
    link n = newNode(value, key, NULL);
    if (list->head == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        list->tail->next = n;
        list->tail = n;
    }

    list->len++;

}

void insertHead(List_p list, int value, int key) {
    link n = newNode(value, key, list->head);
    if (list->head == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        list->head = n;
    }

    list->len++;

}

void cancelNode(List_p list, int key) {
    for (link node = list->head, prev = NULL; node != NULL; prev = node, node = node->next) {
        if (node->item.key == key) {
            if (prev == NULL) {
                list->head = node->next;
                if (list->head == NULL) { // se avevo un solo elemento (node->next ora head è NULL) e lo cancello
                    list->tail = NULL;    // resetto anche la coda
                }
                freeNode(node);

            } else if (node->next == NULL) {
                prev->next = NULL;
                list->tail = prev;
                freeNode(node);
            } else {
                prev->next = node->next;
                freeNode(node);
            }
            list->len--;
            break;
        }
    }
}

int findNode(List_p list, int key) {
    for (link node = list->head; node != NULL; node = node->next) {
        if (node->item.key == key) {
            return node->item.value;
        }
    }
    return -1;
}