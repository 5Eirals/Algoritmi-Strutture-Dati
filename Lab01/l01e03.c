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

comando leggiComando();
boolean selezionaDati(Log* routes, comando e);

void MergeDates(Route* listA, Route* listB, int len);
void MergeStrings(Route* listA, Route* listB, int len);
void MergeSortDates(Route* list, int len, int left, int right);
void MergeSortStrings(Route* list, int len, int left, int right);

void printLog(Log routes, boolean toFIle);
void sortDate(Log* routes);
void sortCode(Log* routes);
void sortDeparture(Log* routes);
void sortArrival(Log* routes);
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
		printf("An error occurred during input-file opening, terminating\n");
		return FILE_ERROR;
	}

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

	while (selezionaDati(&log, leggiComando())) {}

	fclose(fin);
	fclose(fout);
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
        "\t6. ricerca di trattaa per codice <cerca_c>\n"
        "\t7. ricerca di tratta per stazione di partenza <cerca_p>\n"
		"\t8. esci <fine>\n"
		">> "
	);

	for (;;) {
		scanf(" %s", str);
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
		default: printf("Error date format \n"); return -1;
	}
}

int compareDates (Date d1, Date d2) {
	int tot_days_1 = d1.yy * 365 + d1.yy%4 - d1.yy%400 + monthToDays(d1.mm) + d1.dd;
	int tot_days_2 = d2.yy * 365 + d2.yy%4 - d2.yy%400 + monthToDays(d2.mm) + d2.dd;

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

void sortDate(Log* routes){

}

boolean selezionaDati(Log* routes, comando e) {
	char info[MAX_LEN];
	switch(e){
		case r_stampa:
            if(scanf("%s", info) == 1){
            	if(strcmp(info, "file") == 0)
                	printLog(*routes, TRUE);
            	else
                	printLog(*routes, FALSE);
            }
        break;
		case r_tempo:
            sortDate(routes);
            printf("\tLog sorted by date-time\n");
			break;
		case r_codice:
            sortCode(routes);
			printf("\tLog sorted by route code\n");
			break;
		case r_partenza:
			sortDeparture(routes);
			printf("\tLog sorted by departure station\n");
			break;
		case r_arrivo:
        	sortArrival(routes);
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


