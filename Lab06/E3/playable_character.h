#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

#define CODE_LEN 7

typedef struct{
	int inUse;
    Object* vettEq;
} equipment_s, *Equipment;

typedef struct {
	char code[CODE_LEN];
    char name[MAX_LEN];
    char class[MAX_LEN];
    Equipment equip;
    Stats stats;
} playable_character_s;

typedef struct node_s Node, *Link;
typedef struct node_s {
	playable_character_s playable_character;
    Link next;
};

typedef struct playables_s {
	Link head;
    Link tail;
    int N_playables;
} playable_characters, *Playable_Characters;
