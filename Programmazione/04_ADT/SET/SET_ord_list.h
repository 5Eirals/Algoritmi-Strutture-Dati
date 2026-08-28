#include <stdlib.h>
#include <stdio.h>

typedef struct item_s {
    int key;
    int val;
} item_t, *Item;
typedef int Key;

typedef struct setNode_s *link;
typedef struct setNode_s {
    item_t item;
    link next;
} node;

Key getKey(Item item);
int KEYcmp(Key a, Key b);

typedef struct set_s *SET, set_t;

SET SETinit(int maxN);
void SETfree(SET s);
void SETfill(SET s, item_t item);
int SETsearch(SET s, Key key);
SET SETunion(SET s1, SET s2);
SET SETintersection(SET s1, SET s2);
int SETsize(SET s);
int SETempty(SET s);
void SETprint(SET s);

