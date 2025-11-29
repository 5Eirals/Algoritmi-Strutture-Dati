#include "menu.h"

#define DEFAULT_PG "../pg.txt"
#define DEFAULT_INV "../inventario.txt"


int main (int argc, char *argv[]){
	Inventory inventory = freadInventory(argc>2 ? argv[1] : DEFAULT_INV);
    Playable_Characters character_list = freadPlayableCharacters(argc>2 ? argv[2] : DEFAULT_PG);

    startGameLoop(inventory, character_list);

	return 0;
}

void startGameLoop(Inventory inventory, Playable_Characters character_list) {
	bool gameOn = TRUE; char check; char str[128], str2[128]; Character buffer;

	printAvailableInventory(inventory);
	printAvailableCharacters(character_list);
	printGameMenu();

	while (gameOn) {
		switch (getCommand()) {
			case load_c:
				check = getchar();
				if(check != '\n' && scanf("%s", str) == 1)
					character_list = freadPlayableCharacters(str);
				else {
					printf("Insert source path: ");
					scanf("%s", str);
					character_list = freadPlayableCharacters(str);
				}
				break;
			case load_i:
				check = getchar();
				if(check != '\n' && scanf("%s", str) == 1)
				inventory = freadInventory(str);
				else {
					printf("Insert source path: ");
					scanf("%s", str);
					inventory = freadInventory(str);
				}
				break;
			case available_c:
				printAvailableCharacters(character_list);
				break;
			case available_i:
				printAvailableInventory(inventory);
			break;
			case ins_c:
				while (isNullCharacter(buffer = scanfCharacter(stdin)))
					printf(" --- character information: Invalid Format - retry --- \n");
				insertCharacter(character_list, buffer);
				printf("Inserted: \n");
				printCharacterStats(character_list->tail->character);
				break;
			case del_c:
				check = getchar();
				if(check != '\n' && scanf("%s", str) == 1) {
					if (isNullCharacter(buffer = deleteCharacter(character_list, str)))
						printf(" --- No character matches code or name <%s> ---\n", str);
					else {
						printf(">> Deleted: %s - %s\n", buffer.code, buffer.name);
					}
				}else {
					printf("Insert character code or name: ");
					scanf("%s", str);
					if (isNullCharacter(buffer = deleteCharacter(character_list, str)))
						printf(" --- No character matches code or name <%s> ---\n", str);
					else {
						printf(">> Deleted: %s - %s\n", buffer.code, buffer.name);
					}
				}
				break;
			case print_c:
				check = getchar();
				if(check != '\n' && scanf("%s", str) == 1) {
					if (isNullCharacter(buffer = searchCharacter(character_list, str)))
						printf(" --- No character matches code or name <%s> ---\n", str);
					else
						printCharacterStats(buffer);

				}
				else {
					printf("Insert character code or name: ");
					scanf("%s", str);
					if (isNullCharacter(buffer = searchCharacter(character_list, str)))
						printf(" --- No character matches code or name <%s> ---\n", str);
					else
						printCharacterStats(buffer);
				}
				break;
			case add_o:
				check = getchar();
				if(check != '\n' && scanf("%s %s", str, str2) == 2) {
					addEquipment(character_list, str, inventory, str2);
				} else {
					printf("Insert character code or name: ");
					scanf("%s", str);
					printf("Insert item name: ");
					scanf("%s", str2);
					addEquipment(character_list, str, inventory, str2);
				}
				break;
			case rem_o:
				check = getchar();
				if(check != '\n' && scanf("%s %s", str, str2) == 2) {
					removeEquipment(character_list, str, inventory, str2);
				} else {
					printf("Insert character code or name: ");
					scanf("%s", str);
					printf("Insert item name: ");
					scanf("%s", str2);
					removeEquipment(character_list, str, inventory, str2);
				}
				break;
			case menu:
				printGameMenu();
				break;
			case end:
				printf(" --- Closing game... See you next time! ---\n");
				gameOn = endGameLoop();

				freeInventory(inventory);
				freePlayableCharacter(character_list);
				break;
			default:
				printf(" --- Unknown command, retry ---\n");
				break;
		}
		check = getchar(); //clear residual
	}
}

command getCommand() {
	char cmd[MAX_LEN];
	printf(">> ");
	scanf("%s", cmd);

	if (strcmp(cmd, "cread") == 0) {
		return load_c;
	} else if (strcmp(cmd, "iread") == 0) {
		return load_i;
	} else if (strcmp(cmd, "characters") == 0) {
		return available_c;
	} else if (strcmp(cmd, "items") == 0) {
		return available_i;
	}else if (strcmp(cmd, "ins") == 0) {
		return ins_c;
	}else if (strcmp(cmd, "del") == 0) {
		return del_c;
	} else if (strcmp(cmd, "print") == 0) {
		return print_c;
	} else if (strcmp(cmd, "add") == 0) {
		return add_o;
	} else if (strcmp(cmd, "remove") == 0) {
		return rem_o;
	} else if (strcmp(cmd, "menu") == 0) {
		return menu;
	} else if (strcmp(cmd, "end") == 0) {
		return end;
	}
	return -1;
}

void printGameMenu() {
	printf("Action Menu:\n"
		"\t 1. Load character list from file: <cread [filename]>\n"
		"\t 2. Load inventory items from file: <iread [filename]>\n"
		"\t 3. Display available characters: <characters>\n"
		"\t 4. Display available inventory items: <items>\n"
		"\t 5. Insert a new character in list <ins [code] [name] [class] [hp mp atk def mag spr]>\n"
		"\t 6. Delete character from character list <del [code/name]>\n"
		"\t 7. Print character's info and statistics <print [code/name]>\n"
		"\t 8. Add item to a character's inventory <add [character code/name] [item name]>\n"
		"\t 9. Remove item from a character's inventory <add [character code/name] [item name]>\n"
		"\t10. Show again this Menu <menu>\n"
		"\t11. Exit Game <end>\n\n"
	);
}

bool endGameLoop() {
	return FALSE;
}