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

	printCharacterStats(_character);

    list->tail->next = newNode;
    list->tail = newNode;

    list->len++;
}

Playable_Characters freadPlayableCharacters(char* path){
	FILE* file;
	printf("path: %s\n", path);
    if((file = fopen(path, "r"))==NULL){
    	printf("--- File Error ---\n");
        return NULL;
    }

    Playable_Characters list = (Playable_Characters)malloc(sizeof(playables_s));
    list->tail = (Link)malloc(sizeof(Node));
    list->head = (Link)malloc(sizeof(Node));
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

Character searchCharacter(Playable_Characters list, char* code){
	for(Link head = list->head->next; head != NULL; head = head->next){
          if(strcmp(code, head->character.code)==0)
            return head->character;
	}
    return nullCharacter();
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

Character deleteCharacter(Playable_Characters list, char* id){
	if(strlen(id) > CODE_LEN)
          return deleteCharacterCode(list, id);
    return deleteCharacterName(list, id);
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
          printf("< empty >\n");
          return;
  	}

	int len = e->inUse;
	int widths[len];
	for(int i = 0; i < len; i++)
    	widths[i] = max(strlen(e->vettEq[i]->name), strlen(e->vettEq[i]->type)) + 2;
    for(int i = 0; i < len; i++)
    	printf(" %.*s ", widths[i], SEPARATOR);
    printf("\n");
    for(int i = 0; i < len; i++){
      	int padlen = widths[i] - strlen(e->vettEq[i]->name);
    	printf(" %s%*.*s ", e->vettEq[i]->name, padlen, padlen, SPACER);
    }
    printf("\n");
    for(int i = 0; i < len; i++){
      	int padlen = widths[i] - strlen(e->vettEq[i]->type);
    	printf(" %s%*.*s ", e->vettEq[i]->type, padlen, padlen, SPACER);
    }
    printf("\n");
    for(int i = 0; i < len; i++)
    	printf(" %.*s ", widths[i], SEPARATOR);
	printf("\n");
}

void printCharacterStats(Character character){
	printf("| > %s\n"
         "%s \nClass:%s\tEquipment:\n",
         character.code, character.name, character.type);
    printEquipment(character.equip);
    Stats stats = calcStats(character);
    printf("Stats:\n  hp:%.3d mp:%.3d atk:%.3d def:%.3d mag:%.3d spr:%.3d\n",
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
	if(list->len > 0)
		for(Link head = list->head->next; head != NULL; head = head->next){
        	printCharacterStats(head->character);
		}
}




