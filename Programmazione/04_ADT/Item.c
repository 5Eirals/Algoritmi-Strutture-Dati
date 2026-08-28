#include "Item.h"

#include <string.h>

static char buf[255];

Item ITEMnew() {
    Item_3 item = (Item) malloc(sizeof(item_3));
    if (item == NULL) {
        return ITEMsetVoid();
    }

    item->name[0] = '\0';
    item->num = 0;
    return item;
}

void ITEMfree(Item item) {
    free(item);
}

Item ITEMnew() {
    Item_4 item = (Item_4) malloc(sizeof(item_4));
    if (item == NULL) {
        return ITEMsetVoid();
    }

    item->name = NULL;
    item->num = 0;
    return item;
}

void ITEMfree(Item_4 item) {
    if (item->name != NULL) {free(item->name);}
    free(item);
}

Item ITEMscan() {
    Item_4 item = ITEMnew();
    if (item -> name != NULL) {
        scanf("%s %d", buf, &item -> num);
        item->name = strdup(buf); //allocates a copy of the buf string inside name
    }

    return item;
}