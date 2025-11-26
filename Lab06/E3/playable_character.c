#include "playable_character.h"

Character scanfCharacter(FILE* src){
	Character holder;
    fscanf(src, "%s %s %s %d %d %d %d %d %d",
                       holder.code,
                       holder.name,
                       holder.type,
                       &holder.stats.hp,
                       &holder.stats.mp,
                       &holder.stats.atk,
                       &holder.stats.def,
                       &holder.stats.mag,
                       &holder.stats.spr
                       );
	return holder;
}

void insertCharacter(Playable_Characters list, Character _character){
	Link newNode = (Link)malloc(sizeof(Node));

	newNode->character = _character;
    newNode->character.equip = (Equipment)malloc(sizeof(equipment_s));
    newNode->character.equip->inUse = 0;
    newNode->next = NULL;

    list->tail->next->next = newNode;
    list->tail->next = newNode;

    list->len++;
}

Playable_Characters freadPlayableCharacter(char* path){
	FILE* file; int size = 2;
    if((file = fopen(path, "r"))==NULL){
    	printf("--- File Error ---\n");
        return NULL;
    }

    Playable_Characters list = (Playable_Characters)malloc(sizeof(playables_s));
    list->tail = (Link)malloc(sizeof(Node));
    list->head = (Link)malloc(sizeof(Node));
    list->tail->next = list->head;
    list->len = 0;

    while(!feof(file)){
        insertCharacter(list, scanfCharacter(file));
    }

    return list;
}

static void freeList(Link head){
	if(head == NULL)
          return;

    freeList(head->next);

    free(head->character.equip);
    free(head);
}

void freePlayableCharacter(Playable_Characters list){
	freeList(list->head);
}

Link searchCharacter(Playable_Characters list, char* code){
	for(Link head = list->head->next; head != NULL; head = head->next){}
}




