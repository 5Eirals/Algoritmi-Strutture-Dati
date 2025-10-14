#include <stdio.h>
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

typedef struct log_s Log;
struct log_s {
	int len;
	Route* list;
};

typedef enum comando_e comando;
enum comando_e {
	r_stampa, r_tempo, r_codice, r_partenza, r_arrivo, r_cerca_codice, r_cerca_partenza, r_fine
};

int monthToDays(int month);
int compareTime(Time t1, Time t2);
int compareDates(Date d1, Date d2);
void printDate(Date d);
void printRoute(Route route);
void fprintRoute(Route route, FILE* file);

comando leggiComando();
boolean selezionaDati(Log* routes, comando e, FILE* file);

void MergeCommand(Route* list, Route* holder, int left, int middle, int right, comando e);
void MergeSor(Route* list, Route* holder, int len, int left, int right, comando e);

void printLog(Log routes, boolean toFIle, FILE* file);
void sortCommand(Log* routes, comando e);
void searchCodeLinear(Log routes, char* code);
void searchCode(Log* routes, char* code);
void searchDepartureLinear(Log routes, char* departure);
void searchDeparture(Log* routes, char* departure);

int main(){
	FILE* fin, *fout;
    int N;
	Log log;

    if((fin = fopen("Lab01/corse.txt", "r")) == NULL){
    	printf("An error occurred during input-file opening, terminating\n");
        return FILE_ERROR;
    }
	if((fout = fopen("output.txt", "w")) == NULL){
		printf("An error occurred during output-file opening, aborting\n");
		return;
	}

	fprintf(fout, "checking output file\n");

    if(fscanf(fin, " %d ", &N) != 1){
    	printf("An error occurred during input-file N reading, terminating\n");
        return INPUT_ERROR;
    }

	log.len = N;
    Route routes[N];

    for(int i = 0; i < N; i++){
    	if (feof(fin) != EOF && fscanf(fin, " %s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d ",
				 routes[i].route_id,
				 routes[i].start,
				 routes[i].end,
				 &routes[i].date.yy,
				 &routes[i].date.mm,
				 &routes[i].date.dd,
				 &routes[i].departure_time.hh,
				 &routes[i].departure_time.min,
				 &routes[i].departure_time.sec,
				 &routes[i].arrival_time.hh,
				 &routes[i].arrival_time.min,
				 &routes[i].arrival_time.sec,
				 &routes[i].delay
				 ) != 13) {
    		printf("An error occurred durinng input-file reading, terminating\n");
    		return INPUT_ERROR;
    	}
    }

	log.list = routes;

	while (selezionaDati(&log, leggiComando(), fout)) {}

	fclose(fin);
	return 0;
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

void printRoute(Route route){
	printf("%s %s - %s %04d/%02d/%02d\n\tdeparture - %02d:%02d:%02d\n\tarrival - %02d:%02d:%02d\n\tdelay: %02d\n\n",
         route.route_id,
         route.start,
         route.end,
         route.date.yy,
         route.date.mm,
         route.date.dd,
         route.departure_time.hh,
         route.departure_time.min,
         route.departure_time.sec,
         route.arrival_time.hh,
         route.arrival_time.min,
         route.arrival_time.sec,
         route.delay);
    return;
}

void fprintRoute(Route route, FILE* file){
	fprintf(file, "%s %s - %s %04d/%02d/%02d\n\tdeparture - %02d:%02d:%02d\n\tarrival - %02d:%02d:%02d\n\tdelay: %02d\n\n",
		 route.route_id,
		 route.start,
		 route.end,
		 route.date.yy,
		 route.date.mm,
		 route.date.dd,
		 route.departure_time.hh,
		 route.departure_time.min,
		 route.departure_time.sec,
		 route.arrival_time.hh,
		 route.arrival_time.min,
		 route.arrival_time.sec,
		 route.delay);
	return;
}

void searchCodeLinear(Log routes, char* code){
	for(int i = 0; i < routes.len; i++){
    	if(strcmp(code, routes.list[i].route_id) == 0){
        	printRoute(routes.list[i]);
        	break;
    	}
    }
}

void searchDepartureLinear(Log routes, char* departure){
	for(int i = 0; i < routes.len; i++){
		if(strcmp(departure, routes.list[i].start) == 0){
			printRoute(routes.list[i]);
		}
	}
}

void MergeCommand(Route* list, Route* holder, int left, int middle, int right, comando e){

    int i = left, j = middle + 1;

    for(int k = left; k <= right; k++){
    	if(i > middle)
        	holder[k] = list[j++];
    	else if(j > right)
        	holder[k] = list[i++];
        else {
	        switch(e) {
	        	case r_tempo:
	        		if(compareDates(list[i].date, list[j].date) < 0)
	        			holder[k] = list[i++];
	        		else if(compareDates(list[i].date, list[j].date) == 0) {
	        			if (compareTime(list[i].departure_time, list[j].departure_time) <= 0)
	        				holder[k] = list[i++];
	        			else
	        				holder[k] = list[j++];
	        		} else
	        			holder[k] = list[j++];

	        	break;
	        	case r_codice:
	        		if(strcmp(list[i].route_id, list[j].route_id) < 0)
	        			holder[k] = list[i++];
	        		else
	        			holder[k] = list[j++];
	        	break;
	        	case r_arrivo:
	        		if(strcmp(list[i].end, list[j].end) < 0)
	        			holder[k] = list[i++];
	        		else
	        			holder[k] = list[j++];
	        	break;
	        	case r_partenza:
	        		if(strcmp(list[i].start, list[j].start) < 0)
	        			holder[k] = list[i++];
	        		else
	        			holder[k] = list[j++];
	        	default:
	        		printf("Missmatched command, aborting");
	        	return;
	        }
        }
    }

    for(int k = left; k <= right; k++){
    	list[k] = holder[k];
    }

    return;
}

void MergeSort(Route* list, Route* holder, int len, int left, int right, comando e){
	if (left >= right) return;

    int middle = (left + right) / 2;

    MergeSort(list, holder, len, left, middle, e);
    MergeSort(list, holder, len, middle + 1, right, e);
    MergeCommand(list, holder, left, middle, right, e);

}

void sortCommand(Log* routes, comando e){
	Route holder[routes->len];
	MergeSort(routes->list, holder, routes->len, 0, routes->len - 1, e);
}


void printLog(Log routes, boolean toFile, FILE* file){
	if(toFile) {
		for(int i = 0; i < routes.len; i++)
			fprintRoute(routes.list[i], file);
	} else {
		for(int i = 0; i < routes.len; i++)
			printRoute(routes.list[i]);
	}
	return;
}

boolean selezionaDati(Log* routes, comando e, FILE * file) {
	char info[MAX_LEN];
	char check;
	switch(e){
		case r_stampa:
			check = getchar();
			printf("read char: %d", check);
            if(check != '\n' && scanf("%s", info) == 1){
            	if(strcmp(info, "file") == 0)
                	printLog(*routes, TRUE, file);
            	else
                	printLog(*routes, FALSE, file);
            }
        break;
		case r_tempo:
            sortCommand(routes, e);
            printf("\tLog sorted by date-time\n");
			break;
		case r_codice:
            sortCommand(routes, e);
			printf("\tLog sorted by route code\n");
			break;
		case r_partenza:
			sortCommand(routes, r_partenza);
			printf("\tLog sorted by departure station\n");
			break;
		case r_arrivo:
			sortCommand(routes, e);
            printf("\tLog sorted by arrival station\n");
			break;
		case r_cerca_codice:
			break;
		case r_cerca_partenza:
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