#include <stdio.h>
#include <stdlib.h>
#include "playable_character.h"

#define DEFAULT_PG "C:\\Users\\Emanuele\\CLionProjects\\Algoritmi-Strutture-Dati\\Lab06\\E3\\pg.txt"
#define DEFAULT_INV "Lab06/E3/inv.txt"

int main (int argc, char *argv[]){
	printf("argc = %d\n", argc);
	Inventory inventory = freadInventory(argc>2 ? argv[1] : DEFAULT_INV);
    Playable_Characters character_list = freadPlayableCharacters(argc>1 ? argv[2] : DEFAULT_PG);

    printAvailableInventory(inventory);
    printAvailableCharacters(character_list);
	return 0;
}