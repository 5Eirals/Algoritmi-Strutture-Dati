typedef struct stack_s *STACK, stack_t;

typedef struct item_s {
    int key;
    int val;
} item_t, *Item;
typedef int Key;

typedef struct node_s *link;
typedef struct node_s {
    item_t item;
    link next;
} node;

struct stack_s {link head;};

STACK STACKinit(int maxN);
int STACKempty(STACK s);
void STACKpush(STACK s, item_t item);
item_t STACKpop(STACK s);

