#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50
#define FILE_ERROR 3
#define INPUT_ERROR 4

typedef struct {
	int dd;
	int mm;
	int yy;
} Date;

typedef struct {
	char code[MAX_LEN];
    char name[MAX_LEN];
    char surname[MAX_LEN];
    Date birthday;
    char city[MAX_LEN];
    char address[MAX_LEN];
    int cap;
} Item;

typedef struct node_s Node, *Link;
struct node_s{
	Item item;
	Link next;
};

typedef enum{
	r_read, r_print, r_search_code, r_canc_code, r_canc_date, r_end
} Command;

typedef enum{
	TRUE = 1, FALSE = 0
} boolean;

int monthToDays(int month);
int compareDates(Date d1, Date d2);
void fprintDate(FILE* f, Date d);
void fprintItem(FILE* f, Item item);
void fprintList(FILE* f, Link list);
void readFile(char* path, Link list);
void readTerminal(Link list);
Link searchCode(Link list, char* code);
Link removeCode(Link list, char* code);
Command getCommand();
int executeCommand(Link list, Command c);

int main(void){
	Link head = NULL;
    int status;
  	while((status = executeCommand(head, getCommand()) == TRUE)){}
	return status;
}

int monthToDays(int month) {
	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
		case 4: case 6: case 9: case 11: return 30;
		case 2: return 28;
		default: printf("Error date format month:%d \n", month); return -1;
	}
}

int compareDates (Date d1, Date d2) {
	int tot_days_1 = d1.yy * 365 + d1.yy%4 - d1.yy%400 + d1.dd;
	int tot_days_2 = d2.yy * 365 + d2.yy%4 - d2.yy%400 + d2.dd;

	for (int m = 1; m <= d1.mm; m++) {
		tot_days_1 += monthToDays(m);
	}
	for (int m = 1; m <= d2.mm; m++) {
		tot_days_2 += monthToDays(m);
	}

	return tot_days_1 - tot_days_2;
}

Command getCommand() {
	char str[30];

	printf("Digitare l'operazione desiderata:\n"
		"\t1. leggi i contenuti da file o da tastiera (default) <leggi path/default>\n"
		"\t2. stampa a video (default) o a file <stampa path/defualt>\n"
		"\t3. ricerca di un Item per codice <cerca_c>\n"
		"\t4. cancellazione di un Item per codice <canc_c>\n"
		"\t5. cancellazione di più item in un certo range di date <canc_date dd/mm/yy dd/mm/yy>\n"
		"\t6. esci <fine>\n"
		">> "
	);

	for (;;) {
		scanf(" %s", str);
		if (strcmp(str, "leggi") == 0) return r_read;
		if (strcmp(str, "stampa") == 0) return r_print;
		if (strcmp(str, "cerca_c") == 0) return r_search_code;
		if (strcmp(str, "canc_c") == 0) return r_canc_code;
		if (strcmp(str, "canc_date") == 0) return r_canc_date;
		if (strcmp(str, "fine") == 0) return r_end;

		printf("Comando errato o sconosciuto, riprovare: ");
	}
}

int executeCommand(Link list, Command c) {
  	Link ret;
	char info[MAX_LEN];
	char check;
	switch (c) {
        case r_read:
          	check = getchar();
			if(check != '\n' && scanf("%s", info) == 1){
            	readFile(info, list);
			} else {
            	readTerminal(list);
			}
            break;
        case r_print:
        	check = getchar();
			if(check != '\n' && scanf("%s", info) == 1){
                FILE *f;
                if((f = fopen(info, "r")) == NULL){
                	printf("An error occurred during input-file opening, terminating\n");
                    return FILE_ERROR;
                }
				fprintList(f, list);
			} else {
                printf("Insert <code> <name> <surname> <dd/mm/yy> <city> <address> <cap> : \n");
				readTerminal(list);
			}
			break;
        case r_search_code:
        	check = getchar();
            if(check == '\n' || scanf("%s", info) != 1){
                printf("Insert search key <code>: ");
            	scanf("%s", info);
            }
			ret = searchCode(list, info);
			if(ret != NULL){
				fprintItem(stdout, ret->item);
			} else {
				printf("No match found for code <%s>\n", info);
			}
            break;
        case r_canc_code:
        	check = getchar();
			if(check == '\n' || scanf("%s", info) != 1){
				printf("Insert search key <code>: ");
				scanf("%s", info);
			}
            ret = removeCode(list, info);
			if(ret != NULL){
                printf("Removed ");
				fprintItem(stdout, ret->item);
			} else {
				printf("No match found for code <%s>\n", info);
			}
            break;
        case r_end:
        	printf("\t---\texiting program \t---\n");
            return FALSE;
        default:
        	printf("Missmatched command, retry\n");
            break;
	}

    return TRUE;
}

void fprintDate(FILE* f, Date d) {
	fprintf(f, "%04d/%02d/%02d\n", d.yy, d.mm, d.dd);
}

void fprintItem(FILE* f, Item item) {
	fprintf(f, "CODE: %s\n\t%s %s\n\t", item.code, item.name, item.surname);
    fprintDate(f, item.birthday);
    fprintf(f, "\t%s\n\t%s\n\tcap: %d\n", item.city, item.address, item.cap);
}

void fprintList(FILE* f, Link list) {
	for(Link i = list; i->next != NULL; i = i->next) {
		fprintItem(f, i->item);
	}
}

Link searchCode(Link list, char* code) {
  	Link head = list;
	for(Link i = head->next; i->next != NULL; i = i->next) {
		if (strcmp(code, i->item.code) == 0)
        	return i;
	}

    return NULL;
}

Link removeCode(Link list, char* code) {
	for(Link i = list; i->next != NULL; i = i->next) {
		if (strcmp(code, i->item.code) == 0){
            i->next = i->next->next;
			return i;
		}
	}
	return NULL;
}