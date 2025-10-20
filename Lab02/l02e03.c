#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_ERROR 3
#define INPUT_ERROR 4
#define MAX_LEN 30

typedef enum {FALSE = 0, TRUE} boolean;

typedef struct date_s Date;
struct date_s {
	int dd;
    int mm;
    int yy;
};

typedef struct time_s Time;
struct time_s {
	int sec;
    int min;
    int hh;
};

typedef struct route_s Route;
struct route_s {
	char route_id[MAX_LEN];
    char start[MAX_LEN];
    char end[MAX_LEN];
    Date date;
    Time departure_time;
    Time arrival_time;
    int delay;
};

typedef struct registry_s Registry;
struct registry_s {
	int len;
    Route* list;
    Route** src;
	Route** time_sorted;
	Route** code_sorted;
	Route** start_sorted;
	Route** end_sorted;
};

typedef enum comando_e comando;
enum comando_e {
	r_stampa, r_tempo, r_codice, r_partenza, r_arrivo, r_cerca_codice, r_cerca_partenza, r_fine
};

int mallocRegistry(FILE* fin, Registry* registry);
void freeRegistry(Registry* registry);
int readRegistry(char* path, Registry* registry);

int monthToDays(int month);
int compareTime(Time t1, Time t2);
int compareDates(Date d1, Date d2);
void printDate(Date d);
void printRoute(Route* route);
void fprintRoute(Route* route, FILE* file);

comando leggiComando();
boolean selezionaDati(Registry* registry, comando e);

void MergeCommand(Route** list, Route** holder, int left, int middle, int right, comando e);
void MergeSort(Route** list, Route** holder, int len, int left, int right, comando e);

void printLog(Route** routes, int len, boolean toFIle);
void sortCommand(Registry* routes, comando e);
void searchCodeLinear(Registry* routes, char* code);
void searchCode(Registry* routes, char* code);
void searchDepartureLinear(Registry routes, char* departure);
void searchDeparture(Registry* routes, char* departure);

int main(){
	FILE* fin;
    char path[MAX_LEN];
    Registry* registry = (Registry*)malloc(sizeof(Registry));


	while (selezionaDati(registry, leggiComando())) {}

	return 0;
}

int mallocRegistry(FILE* fin, Registry* registry){
	int len = 1;
    char buffer[128];
    while(!feof(fin)){
    	fgets(buffer, 128, fin);
        len++;
    }

    printf("Registri len: %d\n", len);

	registry->list = (Route*)malloc(sizeof(Route) * len);
	registry->src = (Route**)malloc(len*sizeof(Route*));
	registry->time_sorted = (Route**)malloc(len*sizeof(Route*));
	registry->code_sorted = (Route**)malloc(len*sizeof(Route*));
	registry->start_sorted = (Route**)malloc(len*sizeof(Route*));
	registry->end_sorted = (Route**)malloc(len*sizeof(Route*));

    return len;
}

int readRegistry(char* path, Registry* registry){
  	FILE* fin;

	if((fin = fopen(path, "r")) == NULL){
		printf("An error occurred during input-file opening, terminating\n");
		return FILE_ERROR;
	}
	registry->len = mallocRegistry(fin, registry);
    fclose(fin);

	fin = fopen(path, "r");
	for(int i = 0; i < registry->len; i++){
		if (feof(fin) != EOF && fscanf(fin, " %s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d ",
				 registry->list[i].route_id,
				 registry->list[i].start,
				 registry->list[i].end,
				 &registry->list[i].date.yy,
				 &registry->list[i].date.mm,
				 &registry->list[i].date.dd,
				 &registry->list[i].departure_time.hh,
				 &registry->list[i].departure_time.min,
				 &registry->list[i].departure_time.sec,
				 &registry->list[i].arrival_time.hh,
				 &registry->list[i].arrival_time.min,
				 &registry->list[i].arrival_time.sec,
				 &registry->list[i].delay
				 ) != 13) {
			printf("An error occurred durinng input-file reading, terminating\n");
			return INPUT_ERROR;
				 }
	}

	for(int i = 0; i < registry->len; i++){
		registry->src[i] = &(registry->list[i]);
		registry->time_sorted[i] = &(registry->list[i]);
		registry->code_sorted[i] = &(registry->list[i]);
		registry->start_sorted[i] = &(registry->list[i]);
		registry->end_sorted[i] = &(registry->list[i]);
	}

    fclose(fin);
    return TRUE;

}

void freeRegistry(Registry* registry){
	free(registry->list);
	free(registry->src);
	free(registry->time_sorted);
	free(registry->code_sorted);
	free(registry->start_sorted);
	free(registry->end_sorted);
    free(registry);
}

comando leggiComando() {
	char str[30];

	printf("Digitare l'operazione desiderata:\n"
		"\t1. stampa, a scelta se a video o su file, dei contenuti del file <stampa>\n"
		"\t2. ordinamento del vettore per data, e a parità di date per ora  <tempo>\n"
		"\t3. ordinamento del vettore per codice di tratta <codice>\n"
		"\t4. ordinamento del vettore per stazione di partenza <partenza>\n"
		"\t5. ordinamento del vettore per stazione di arrivo <arrivo>\n"
        "\t6. ricerca di tratta per codice <cerca_c>\n"
        "\t7. ricerca di tratta per stazione di partenza <cerca_p>\n"
		"\t8. esci <fine>\n"
		">> "
	);

	for (;;) {
		scanf(" %s", str);
		if (strcmp(str, "stampa") == 0) return r_stampa;
		if (strcmp(str, "tempo") == 0) return r_tempo;
		if (strcmp(str, "codice") == 0) return r_codice;
		if (strcmp(str, "partenza") == 0) return r_partenza;
		if (strcmp(str, "arrivo") == 0) return r_arrivo;
		if (strcmp(str, "cerca_c") == 0) return r_cerca_codice;
		if (strcmp(str, "cerca_p") == 0) return r_cerca_partenza;
		if (strcmp(str, "fine") == 0) return r_fine;

		printf("Comando errato o sconosciuto, riprovare: ");
	}
}

int compareTime(Time t1, Time t2) {
	int tot_1 = t1.sec + t1.min*60 + t1.hh*3600;
    int tot_2 = t2.sec + t2.min*60 + t2.hh*3600;

    return tot_1 - tot_2;
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

void printDate(Date d) {
	printf("%04d/%02d/%02d\n", d.yy, d.mm, d.dd);
}

void fprintRoute(Route* route, FILE* file){
	fprintf(file, "%s %s - %s %04d/%02d/%02d\n\tdeparture - %02d:%02d:%02d\n\tarrival - %02d:%02d:%02d\n\tdelay: %02d\n\n",
		 route->route_id,
		 route->start,
		 route->end,
		 route->date.yy,
		 route->date.mm,
		 route->date.dd,
		 route->departure_time.hh,
		 route->departure_time.min,
		 route->departure_time.sec,
		 route->arrival_time.hh,
		 route->arrival_time.min,
		 route->arrival_time.sec,
		 route->delay);
	return;
}

void searchCodeLinear(Registry* routes, char* code){
	for(int i = 0; i < routes->len; i++){
    	if(strcmp(code, routes->list[i].route_id) == 0){
        	printRoute(&(routes->list[i]));
        	break;
    	}
    }
}

void MergeCommand(Route** list, Route** holder, int left, int middle, int right, comando e){

    int i = left, j = middle + 1;

    for(int k = left; k <= right; k++){
    	if(i > middle)
        	holder[k] = list[j++];
    	else if(j > right)
        	holder[k] = list[i++];
        else {
	        switch(e) {
	        	case r_tempo:
	        		if(compareDates(list[i]->date, list[j]->date) < 0)
	        			holder[k] = list[i++];
	        		else if(compareDates(list[i]->date, list[j]->date) == 0) {
	        			if (compareTime(list[i]->departure_time, list[j]->departure_time) <= 0)
	        				holder[k] = list[i++];
	        			else
	        				holder[k] = list[j++];
	        		} else
	        			holder[k] = list[j++];

	        	break;
	        	case r_codice:
	        		if(strcmp(list[i]->route_id, list[j]->route_id) < 0)
	        			holder[k] = list[i++];
	        		else
	        			holder[k] = list[j++];
	        	break;
	        	case r_arrivo:
	        		if(strcmp(list[i]->end, list[j]->end) < 0)
	        			holder[k] = list[i++];
	        		else
	        			holder[k] = list[j++];
	        	break;
	        	case r_partenza:
	        		if(strcmp(list[i]->start, list[j]->start) < 0)
	        			holder[k] = list[i++];
	        		else
	        			holder[k] = list[j++];
	        	break;
	        	default:
	        		printf("Missmatched command, aborting\n");
	        	return;
	        }
        }
    }

	for(int k = left; k <= right; k++)
		list[k] = holder[k];

    return;
}

void MergeSort(Route** list, Route** holder, int len, int left, int right, comando e){
	if (left >= right) return;

    int middle = (left + right) / 2;

    MergeSort(list, holder, len, left, middle, e);
    MergeSort(list, holder, len, middle + 1, right, e);
    MergeCommand(list, holder, left, middle, right, e);

}

void sortCommand(Registry* routes, comando e){
	Route* holder[routes->len];
	switch (e) {
        case r_tempo:
        	MergeSort(routes->time_sorted, holder, routes->len, 0, routes->len - 1, e);
          	break;
        case r_codice:
        	MergeSort(routes->code_sorted, holder, routes->len, 0, routes->len - 1, e);
            break;
        case r_arrivo:
        	MergeSort(routes->end_sorted, holder, routes->len, 0, routes->len - 1, e);
            break;
        case r_partenza:
        	MergeSort(routes->start_sorted, holder, routes->len, 0, routes->len - 1, e);
            break;
       	default:
        	printf("Missmatched command, aborting\n");
        	return;
	}
}

void searchCode(Registry* routes, char* code) {
	sortCommand(routes, r_codice);
	int left = 0, right = routes->len, middle = 0;
	boolean found = FALSE;
	if (strcmp(routes->list[right-1].route_id, code) == 0) {
		printRoute(&(routes->list[right-1]));
		found = TRUE;
	}
	while (middle < right-1 && !found) {
		if (strcmp(routes->list[middle].route_id, code) == 0) {
			printRoute(&(routes->list[middle]));
			found = TRUE;
		} else if (strcmp(routes->list[middle].route_id, code) < 0){
			middle = (middle + right)/2;
		}else{
			middle = (middle + left)/2;
        }
	}

	if (!found)
		printf("No match found for code '%s'\n", code);
}

void searchDeparture(Registry* routes, char* station) {
	boolean found = FALSE;

	sortCommand(routes, r_partenza);
	for (int i = 0; i < routes->len; i++) {
		if ((int)strstr(routes->start_sorted[i]->start, station) == (int)&routes->start_sorted[i]->start) {
			printRoute(routes->start_sorted[i]);
			found = TRUE;
		}
	}

	if (!found)
		printf("No match found for station-token '%s'\n", station);
}


void printLog(Route** routes, int len, boolean toFile){
	FILE* fout;
	if(toFile) {
		if((fout = fopen("Lab01/output.txt", "w")) == NULL){
			printf("An error occurred during output-file opening, aborting\n");
			return;
		}
		for(int i = 0; i < len; i++)
			fprintRoute(routes[i], fout);
		fclose(fout);
	} else {
		for(int i = 0; i < len; i++)
			fprintRoute(routes[i], stdout);
	}
	return;
}

boolean selezionaDati(Registry* routes, comando e) {
	char info[MAX_LEN];
	char check;
	switch(e){
		case r_stampa:
			check = getchar();
            if(check != '\n' && scanf("%s", info) == 1 && strcmp(info, "file") == 0)
                printLog(routes->src, routes->len, TRUE);
            else
            	printLog(routes->src, routes->len, FALSE);
        break;
		case r_tempo:
            sortCommand(routes, e);
            printf("\tLog sorted by date-time:\n");
			printLog(routes->time_sorted, routes->len, FALSE);
			break;
		case r_codice:
            sortCommand(routes, e);
			printf("\tLog sorted by route code\n");
			printLog(routes->code_sorted, routes->len, FALSE);
			break;
		case r_partenza:
			sortCommand(routes, r_partenza);
			printf("\tLog sorted by departure station\n");
			printLog(routes->start_sorted, routes->len, FALSE);
			break;
		case r_arrivo:
			sortCommand(routes, e);
            printf("\tLog sorted by arrival station\n");
			printLog(routes->end_sorted, routes->len, FALSE);
			break;
		case r_cerca_codice:
			check = getchar();
			if(check != '\n' && scanf("%s", info) == 1)
				searchCode(routes, info);
			else {
				printf("Insert the code to search: \n");
				scanf("%s", info);
				searchCode(routes, info);
			}
			break;
		case r_cerca_partenza:
			check = getchar();
			if(check != '\n' && scanf("%s", info) == 1)
				searchDeparture(routes, info);
			else {
				printf("Insert the code to search: \n");
				scanf("%s", info);
				searchDeparture(routes, info);
			}
			break;
		case r_fine:
			printf("\t---\texiting program \t---\n");
			return FALSE;
			break;
        default:
        	printf("An unexpected error occurred, terminating ...\n");
			return FALSE;
    }

	return TRUE;
}