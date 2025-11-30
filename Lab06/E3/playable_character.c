#include "playable_character.h"

Character scanfCharacter(FILE* src){
	Character holder;
    if (fscanf(src, "%s %s %s %d %d %d %d %d %d",
                       holder.code,
                       holder.name,
                       holder.type,
                       &holder.stats.hp,
                       &holder.stats.mp,
                       &holder.stats.atk,
                       &holder.stats.def,
                       &holder.stats.mag,
                       &holder.stats.spr
                       ) == 9)
		return holder;
	return nullCharacter();
}

void insertCharacter(Playable_Characters list, Character _character){
	Link newNode = (Link)malloc(sizeof(Node));

	newNode->character = _character;

    newNode->character.equip = (Equipment)malloc(sizeof(equipment_s));
    newNode->character.equip->inUse = 0;
    newNode->next = NULL;


    list->tail->next = newNode;
    list->tail = newNode;

    list->len++;
}

Playable_Characters freadPlayableCharacters(char* path){
	FILE* file;
    if((file = fopen(path, "r"))==NULL){
    	printf("--- File Error ---\n");
        return NULL;
    }

    Playable_Characters list = (Playable_Characters)malloc(sizeof(playables_s));
    list->tail = (Link)malloc(sizeof(Node));
    list->head = (Link)malloc(sizeof(Node));

	list->head->character = nullCharacter();

    list->tail = list->head;
    list->len = 0;

    while(!feof(file)){
        insertCharacter(list, scanfCharacter(file));
    }

    return list;
}

Character nullCharacter(){
	Character nc;
    strcpy(nc.code, "NULL");
    strcpy(nc.name, "NULL");
    strcpy(nc.type, "NULL");
    nc.equip = NULL;
    return nc;
}

int isNullCharacter(Character character){
	if(strcmp(character.code, "NULL")==0)
        return 1;
    if(strcmp(character.name, "NULL")==0)
        return 1;
    if(strcmp(character.code, "NULL")==0)
        return 1;
    return 0;
}

void freeNode(Link node){
	free(node->character.equip);
    free(node);
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

Character searchCharacter(Playable_Characters list, char* id){
	for(Link head = list->head->next; head != NULL; head = head->next){
          if(strcmp(id, head->character.code)==0 || strcmp(id, head->character.name)==0)
            return head->character;
	}
    return nullCharacter();
}

Link selectCharacter(Playable_Characters list, char* id) {
	for(Link head = list->head->next; head != NULL; head = head->next){
		if(strcmp(id, head->character.code)==0 || strcmp(id, head->character.name)==0)
			return head;
	}
	return NULL;
}

static Character deleteCharacterCode(Playable_Characters list, char* code){
	Character holder;
	for(Link current = list->head, previous = NULL; current != NULL; previous = current, current = current->next){
    	if(strcmp(current->character.code, code) == 0){
        	previous->next = current->next;
            holder = current->character;
            freeNode(current);
            return holder;
    	}
	}
    return nullCharacter();
}

static Character deleteCharacterName(Playable_Characters list, char* name){
	Character holder;
	for(Link current = list->head, previous = NULL; current != NULL; previous = current, current = current->next){
    	if(strcmp(current->character.name, name) == 0){
        	previous->next = current->next;
            holder = current->character;
            freeNode(current);
            return holder;
    	}
	}
    return nullCharacter();
}

static bool checkCode(char* str) {
	if (strlen(str)+1 == CODE_LEN)
		if (str[0] == 'P' && str[1] == 'G')
			return TRUE;
	return FALSE;
}

Character deleteCharacter(Playable_Characters list, char* id){
	if(checkCode(id))
          return deleteCharacterCode(list, id);
    return deleteCharacterName(list, id);
}

void addEquipment(Playable_Characters list, char* char_id, Inventory inv, char* item_id) {
	Link cnode; Object item;

	if ((cnode = selectCharacter(list, char_id)) == NULL) {
		printf(" --- No character matches code or name <%s> ---\n", char_id);
		return;
	}

	if (isNullCharacter(cnode->character)) {
		printf(" --- Error, character is NULL ---\n");
		return;
	}

	if ((item = searchObject(inv, item_id)) == NULL) {
		printf(" --- No item matches name <%s> ---\n", item_id);
		return;
	}

	if (cnode->character.equip->inUse == MAX_EQUIP) {
		printf(" --- <%s> inventory is full, remove an object and try again ---\n", cnode->character.name);
		return;
	}

	cnode->character.equip->vettEq[cnode->character.equip->inUse] = item;
	cnode->character.equip->inUse++;
	printf(" --- Added <%s> to <%s> inventory ---\n", item->name, cnode->character.name);
	return;
}

void removeEquipment(Playable_Characters list, char* char_id, Inventory inv, char* item_id) {
	Link cnode;

	if ((cnode = selectCharacter(list, char_id)) == NULL) {
		printf(" --- No character matches code or name <%s> ---\n", char_id);
		return;
	}

	if (isNullCharacter(cnode->character)) {
		printf(" --- Error, character is NULL ---\n");
		return;
	}

	for (int i = 0; i < cnode->character.equip->inUse; i++) {
		if (strcmp(cnode->character.equip->vettEq[i]->name,item_id) == 0) {
			printf(" --- Removed <%s> from <%s> inventory ---\n",item_id, cnode->character.name);
			for (int j = i; j < cnode->character.equip->inUse-1; j++) {
				cnode->character.equip->vettEq[j] = cnode->character.equip->vettEq[j+1];
			}
			cnode->character.equip->inUse--;
			return;
		}
	}

	printf("--- <%s> already missing from <%s> inventory ---\n", item_id, cnode->character.name);
}

static Stats sumStats(Stats a, Stats b){
	Stats sum;
    sum.hp = a.hp + b.hp;
    sum.mp = a.mp + b.mp;
    sum.atk = a.atk + b.atk;
    sum.def = a.def + b.def;
    sum.mag = a.mag + b.mag;
    sum.spr = a.spr + b.spr;
    return sum;
}

static Stats calcStats(Character character){
	Stats total = character.stats;
    for(int i = 0; i < character.equip->inUse; i++){
    	total = sumStats(total, character.equip->vettEq[i]->stats);
    }
    return total;
}

static void printEquipment(Equipment e){
  	if(e->inUse == 0){
          printf("\t\t< empty >\n");
          return;
  	}

	int len = e->inUse;
	int widths[len];
	for(int i = 0; i < len; i++)
    	widths[i] = max(strlen(e->vettEq[i]->name), strlen(e->vettEq[i]->type))+1;
    for(int i = 0; i < len; i++)
    	printf("|  %.*s ", widths[i], SEPARATOR);
    printf("\n");
    for(int i = 0; i < len; i++){
      	int padlen = widths[i] - strlen(e->vettEq[i]->name);
    	printf("|  %s%*.*s ", e->vettEq[i]->name, padlen, padlen, SPACER);
    }
    printf("\n");
    for(int i = 0; i < len; i++){
      	int padlen = widths[i] - strlen(e->vettEq[i]->type);
    	printf("|  %s%*.*s ", e->vettEq[i]->type, padlen, padlen, SPACER);
    }
    printf("\n");
    for(int i = 0; i < len; i++)
    	printf("|  %.*s ", widths[i], SEPARATOR);
	printf("\n");
}

void printCharacterStats(Character character){
	printf("| > %s\n"
         "| %s \n| Class:%s\tEquipment:\n",
         character.code, character.name, character.type);
    printEquipment(character.equip);
    Stats stats = calcStats(character);
    printf("| Stats:\n| hp:%.3d mp:%.3d atk:%.3d def:%.3d mag:%.3d spr:%.3d\n",
           stats.hp>0?stats.hp:0,
           stats.mp>0?stats.mp:0,
           stats.atk>0?stats.atk:0,
           stats.def>0?stats.def:0,
           stats.mag>0?stats.mag:0,
           stats.spr>0?stats.spr:0
           );
}

void printAvailableInventory(Inventory inventory){
	printf("Game Items:\n");
    for(int i = 0; i < inventory->N_objects; i++){
		printObject(&inventory->objects[i]);
    }
    printf("\n");
}

void printAvailableCharacters(Playable_Characters list){
	printf("Available characters:\n");
	if(list->len > 0)
		for(Link head = list->head->next; head != NULL; head = head->next){
			if (!isNullCharacter(head->character)) {
				printCharacterStats(head->character);
				printf("\n");
			}
		}
}




