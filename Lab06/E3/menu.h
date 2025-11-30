#ifndef MENU_H
#define MENU_H

#endif

#include "playable_character.h"

typedef enum {load_c, load_i, available_c, available_i, ins_c, del_c, print_c, add_o, rem_o, menu, end} command;

void startGameLoop(Inventory inventory, Playable_Characters character_list);
bool endGameLoop();
command getCommand();
void printGameMenu();