typedef struct stack_s stack_t, *STACK;

typedef struct item_s {
    int key;
    int val;
} item_t, *Item;
typedef int Key;

STACK STACKinit(int maxN);
int STACKempty(STACK s);
void STACKpush(STACK s, item_t item);
item_t STACKpop(STACK s);
