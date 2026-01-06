#include "pgList.h"

typedef struct node_s {
	pg_t pg;
	struct node_s *next;
} node_t, *link_t;

typedef struct pgList_s {
	link_t head;
	link_t tail;
	int len;
};

static link_t emptyNode() {
	link_t emptyNode = (link_t)malloc(sizeof(struct node_s));
	emptyNode->next = NULL;
	return emptyNode;
}

pgList_t pgList_init() {
	pgList_t pgList = (pgList_t)malloc(sizeof(struct pgList_s));
	pgList->head = emptyNode();
	pgList->tail = pgList->head;
	pgList->len = 0;
	return pgList;
}

void pgList_insert(pgList_t pgList, pg_t pg) {
	link_t newNode = (link_t)malloc(sizeof(node_t));

	pg_copy(&newNode->pg, &pg);

	newNode->pg.equip = equipArray_init();
	newNode->next = NULL;

	pgList->tail->next = newNode;
	pgList->tail = newNode;

	pgList->len++;
}

void pgList_read(FILE *fp, pgList_t pgList) {
	while(!feof(fp)){
		pg_t buffer;
		pg_read(fp, &buffer);
		pgList_insert(pgList, buffer);
	}
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
	if(pgList->len > 0)
		for(link_t head = pgList->head->next; head != NULL; head = head->next){
				pg_print(fp, &head->pg, invArray);
				fprintf(fp, "\n");
		}
}

void freeNode(link_t node){
	pg_clean(&node->pg);
	free(node);
}

static void freeList(link_t head){
	if(head == NULL)
		return;
	freeList(head->next);
	freeNode(head);
}

void pgList_free(pgList_t pgList) {
	freeList(pgList->head);
}

void pgList_remove(pgList_t pgList, char* cod) {
	for(link_t current = pgList->head->next, previous = NULL; current != NULL; previous = current, current = current->next) {
		if(strcmp(current->pg.cod, cod) == 0){
			previous->next = current->next;
			freeNode(current);
		}
	}
}

pg_t* pgList_searchByCode(pgList_t pgList, char* cod){
	for(link_t head = pgList->head->next; head != NULL; head = head->next){
		if(strcmp(cod, head->pg.cod)==0)
			return &head->pg;
	}
	return NULL;
}


