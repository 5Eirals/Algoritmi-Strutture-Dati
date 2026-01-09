#include "graph.h"

struct vertex_s {
	str id;
    str subnet;
};

struct st_s{
	int len;
    int maxSize;
    vertex* keys;
} st_t;

struct edge_s {
	int flow;
    vertex start_vertex;
    vertex end_vertex;
};

struct node_s {
	int val;
    int flow;
    link next;
};


struct list_s{
	int len;
    link head;
    link tail;
};

struct graph_s {
	int madj[MAX_SIZE][MAX_SIZE];
    list* ladj;
	ST ST;
	int V;
	int E;
};

ST STinit(){
	ST st = (ST) malloc(sizeof(st_t));
    st->len = 0;
    st->maxSize = 2;
    st->keys = (str*) malloc(sizeof(str) * st->maxSize);
	return st;
}

void STfree(ST st){
	free(st->keys);
    free(st);
}

int STinsert(ST st, str val){
	if(st->len == 0){
    	strcpy(st->keys[0].id,val);
        st->len++;
        return 0;
	}

	if(st->len == st->maxSize){
    	st->maxSize *= 2;
        st->keys = (vertex*) realloc(st->keys, sizeof(vertex) * st->maxSize);
	}

    strcpy(st->keys[st->len].id, val);

	for(int i = st->len; i > 0; i--){
        if(strcmp(st->keys[i].id, st->keys[i-1].id) > 0){
          	str temp;
            strcpy(temp, st->keys[i-1].id);
			strcpy(st->keys[i].id, st->keys[i-1].id);
            strcpy(st->keys[i].id, temp);
        } else {
        	st->len++;
			return i;
        }
	}

    st->len++;
}

void STprint(FILE* f, ST st){
	for(int i = 0; i < st->len; i++)
          fprintf(f, " %.2d :<%s> <%s> \n", i, st->keys[i].id, st->keys[i].subnet);

    fprintf(f, "\n");
}

void STdelete(ST st, int key){
	for(int i = key; i < st->len; i++)
          strcpy(st->keys[i].id, st->keys[i+1].id);
    st->len--;
}

str STgetValue(ST st, int key){
	return st->keys[key].id;
}

static int search(str* arr, str target, int start, int end){
	int mid = start + (end - start) / 2;
    if(end < start || start > end)
    	return -1;
    if(arr[mid] == target)
    	return mid;
    else if(strcmp(arr[mid], target) < 0)
    	return search(arr, target, start, mid - 1);
    else
      return search(arr, target, mid + 1, end);
}

int STsearch(ST st, str val){
	return search(st->keys, val, 0, st->len - 1);
}

link newNode(int val){
	link node = (link) malloc(sizeof(node));
    node->val = val;
    node->next = NULL;
    return node;
}

void freeNode(link node){
	free(node);
}

link nullNode(){
	link node = (link) malloc(sizeof(node));
    node->val = -1;
    node->next = NULL;
    return node;
}

bool isNodeNull(link node){
	if(node->val == -1)
          return true;
    return false;
}

list list_init(){
	list l = (list) malloc(sizeof(list_t));
    l->len = 0;
    l->head = nullNode();
    l->tail = l->head;
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

void free_list(list l){
	free_head(l->head);
}

link list_search(list l, int key){
	for(link curr = l->head->next; curr != NULL; curr = curr->next){
        if(curr->val == key)
            return curr;
	}
}

void list_delete(list l, int key){
	for(link curr = l->head->next, prev = l->head; curr != NULL; prev = curr, curr = curr->next){
        if(curr->val == key){
        	prev->next = curr->next;
                return;
        }
	}
}

graph graph_init(){
	graph g = (graph) malloc(sizeof(graph_t));
    g->V = 0;
    g->E = 0;
    g->ST = STinit();
    for(int i = 0; i < MAX_SIZE; i++)
    	for(int j = 0; j < MAX_SIZE; j++)
        	g->madj[i][j] = 0;

    return g;
}

void graph_free(graph g){
    STfree(g->ST);
    free(g);
}

edge_t nullEdge(){
	edge_t edge;
    edge.flow = -100;
    return edge;
}

bool isNullEdge(edge_t edge){
	return edge.flow == -100 ? true : false;
}

edge_t edge_read(FILE *f){
  	edge_t buf;
	if(fscanf(f, "%s %s %s %s %d",
        	buf.start_vertex.id,
        	buf.start_vertex.subnet,
           	buf.end_vertex.id,
           	buf.end_vertex.subnet,
           	&buf.flow
        ) == 5)
    	return buf;
    return nullEdge();
}

void graph_insert(graph g, edge e){
	int found1 = STsearch(g->ST, e->start_vertex.id);
	int found2 = STsearch(g->ST, e->end_vertex.id);
    if(found1 == -1)
    	found1 = STinsert(g->ST, e->start_vertex.id);
    if(found2 == -1)
    	found2 = STinsert(g->ST, e->end_vertex.id);

    g->madj[found1][found2] = e->flow;
    g->madj[found2][found1] = e->flow;

    g->V = g->ST->len;
    g->E++;
}

void print_sqmatr(FILE *f, int** mat, int size){
  	for(int i = 0; i < size; i++)
		fprintf(f, " %02d |", i);
    fprintf(f, "\n");

	for(int i = 0; i < size; i++){
		fprintf(f, " %02d |", i);
    	for(int j = 0; j < size; j++){
        	fprintf(f, " %02d |", mat[i][j]);
    	}
        fprintf(f, "\n");
	}
    fprintf(f, "\n");
}

void graph_print(FILE* f, graph g){
    STprint(f, g->ST);
	print_sqmatr(f, g->madj, g->V);
}

void graph_read(FILE *f, graph g){
	while(!feof(f)){
       	edge_t e = edge_read(f);
        if(isNullEdge(e))
        	printf("Invalid edege format\n");
        else
        	graph_insert(g, &e);
	}
}

