#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

#define CODE_LEN 7
#define MAX_EQUIP 8

typedef enum {FALSE, TRUE} bool;

typedef struct{
	int inUse;
    Object vettEq[MAX_EQUIP];
} equipment_s, *Equipment;

typedef struct {
	char code[CODE_LEN];
    char name[MAX_LEN];
    char type[MAX_LEN];
    Equipment equip;
    Stats stats;
} playable_character_s, Character;

typedef struct node_s *Link;
typedef struct node_s {
	Character character;
    Link next;
} Node;


typedef struct{
	Link head;
    Link tail;
    int len;
} playables_s, *Playable_Characters;

Playable_Characters freadPlayableCharacters(char* path);
void freePlayableCharacter(Playable_Characters list);
void insertCharacter(Playable_Characters list, Character character);
Character deleteCharacter(Playable_Characters list, char* id);
Character searchCharacter(Playable_Characters list, char* code);
Link selectCharacter(Playable_Characters list, char* id);
void printCharacterStats(Character character);
void printAvailableInventory(Inventory inventory);
void printAvailableCharacters(Playable_Characters list);
Character scanfCharacter(FILE* src);
int isNullCharacter(Character character);
Character nullCharacter();
void addEquipment(Playable_Characters list, char* char_id, Inventory inv, char* item_code);
void removeEquipment(Playable_Characters list, char* char_id, Inventory inv, char* item_code);
