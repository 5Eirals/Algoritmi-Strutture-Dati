#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

#define CODE_LEN 7
#define MAX_EQUIP 8

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

Playable_Characters freadPlayableCharacter(char* path);
void freePlayableCharacter(Playable_Characters list);
void insertCharacter(Playable_Characters list, Character character);
void deleteCharacter(Playable_Characters list, char* id);
Link searchCharacter(Playable_Characters list, char* code);
void printCharacterStats(Character character);
Character scanfCharacter(FILE* src);
