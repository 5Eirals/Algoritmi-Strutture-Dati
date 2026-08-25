#include <stdlib.h>
#include <stdio.h>

typedef struct item_s{
    int key;
    int value;
} item, *Item;

typedef struct node_s *link;
typedef struct node_s{
    Item value;
    link next;
} node;

typedef struct list_s {
    link head;
    link tail;
    int size;
} *List;

Item createItem(int key, int value);
int itemGetKey(Item item);
int itemGetValue(Item item);
int compareItemKey(Item item1, Item item2);

List listInit();
Item search(List list, int key);
// void insertHead(List list, Item item);
void insertTail(List list, Item item);
void removeNode(List list, int key);
void freeList(List list);
void freeNode(link node);
void printItem(Item item);
void printList(List list);

int main(){
    List list = listInit();
    for(int i = 0; i < 10; i++)
        insertTail(list, createItem(i, i*10));
    printList(list);
    printf("\n");

    printItem(search(list, 5));
    printf("\n");

    removeNode(list, 3);
    printList(list);
    printf("\n");

    freeList(list);
    return 0;
}

void printItem(Item item){
    printf("%02d : %02d \n", item->key, item->value);
}

void printList(List list){
    for(link node = list->head->next; node != NULL; node = node->next) {
        printItem(node->value);
    }
}

void freeList(List list){
    freeNode(list->head);
    free(list);
}

void freeNode(link node){
    if(node->next == NULL){
        free(node);
        return;
    }

    freeNode(node->next);
}

Item createItem(int key, int value){
    Item item = (Item)malloc(sizeof(item));
    item->key = key;
    item->value = value;
    return item;
}

Item search(List list, int key){
    for(link node = list->head->next; node != NULL; node = node->next)
        if(node->value->key == key)
            return node->value;

}

void removeNode(List list, int key){
    for(link node = list->head->next, prev = list->head; node!= NULL;){
        if(node->value->key == key){
            link temp = node;
            prev->next = node->next;

            node = node->next;
            prev = temp->next;

            free(temp->value);
            free(temp);
            list->size--;
        }
        prev = node;
        node = node->next;

    }
}

void insertTail(List list, Item item){
    link newNode = (link)malloc(sizeof(node));
    newNode->value = item;
    newNode->next = NULL;
    list->tail->next = newNode;
    list->tail = newNode;
}

List listInit(){
    List list = (List)malloc(sizeof(struct list_s));
    list->size = 0;
    list->head = (link)malloc(sizeof(node));
    list->head->next = NULL;
    list->tail = list->head;
    return list;
}