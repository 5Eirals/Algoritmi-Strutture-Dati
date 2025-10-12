#include <stdio.h>
#include <string.h>

#define FILE_ERROR 3
#define INPUT_ERROR 4
#define MAX_LEN 30

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
	r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
};

int monthToDays(int month);
int compareDates(Date d1, Date d2);
void printDate(Date d);
void printRoute(Route route);
comando leggiComando();
int selezionaDati(Log routes, comando e);
void printDateInterval(Log routes, Date start, Date end);
void printDeparture(Log routes, char* station);
void printArrival(Log routes, char* station);
void printDelay(Log routes, Date start, Date end);
void printTotalDelay(Log routes, char* code);

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

	while (selezionaDati(log, leggiComando())) {}

	fclose(fin);
	fclose(fout);
	return 0;
}
comando leggiComando() {
	char str[30];

	printf("Digitare l'operazione desiderata:\n"
		"\t1. elencare tutte le corse partite in un certo intervallo di date <date>\n"
		"\t2. elencare tutti le corse partite da una certa fermata <partenza>\n"
		"\t3. elencare tutti le corse che fanno capolinea in una certa fermata <capolinea>\n"
		"\t4. elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date <ritardo>\n"
		"\t5. elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta <ritardo_tot>\n"
		"\t6. esci <fine>\n"
		">> "
	);

	for (;;) {
		scanf(" %s", str);
		if (strcmp(str, "date") == 0) return r_date;
		if (strcmp(str, "partenza") == 0) return r_partenza;
		if (strcmp(str, "capolinea") == 0) return r_capolinea;
		if (strcmp(str, "ritardo") == 0) return r_ritardo;
		if (strcmp(str, "ritardo_tot") == 0) return r_ritardo_tot;
		if (strcmp(str, "fine") == 0) return r_fine;

		printf("Comando errato o sconosciuto, riprovare: ");
	}
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

void printDateInterval(Log routes, Date start, Date end) {
	int found = 0;
	for (int i = 0; i < routes.len; i++) {
		if (compareDates(routes.list[i].date, start) > 0 && compareDates(routes.list[i].date, end) < 0) {
			printRoute(routes.list[i]);
			found = 1;
		}
	}
	if (!found) {
		printf("\t\t> No match found \n");
	}
}

void printDeparture(Log routes, char* station) {
	int found = 0;
	for (int i = 0; i < routes.len; i++) {
		if (strcmp(station, routes.list[i].start) == 0) {
			printRoute(routes.list[i]);
			found = 1;
		}
	}
	if (!found) {
		printf("\t\t> No match found \n");
	}
}

void printArrival(Log routes, char* station) {
	int found = 0;
	for (int i = 0; i < routes.len; i++) {
		if (strcmp(station, routes.list[i].end) == 0) {
			printRoute(routes.list[i]);
			found = 1;
		}
	}
	if (!found) {
		printf("\t\t> No match found \n");
	}
}

void printDelay(Log routes, Date start, Date end){
	int found = 0;
	for (int i = 0; i < routes.len; i++) {
		if (compareDates(routes.list[i].date, start) > 0 && compareDates(routes.list[i].date, end) < 0 && routes.list[i].delay > 0) {
			printRoute(routes.list[i]);
			found = 1;
		}
	}
	if (!found) {
		printf("\t\t> No match found \n");
	}
}

void printTotalDelay(Log routes, char* code){
	int total_delay = 0;
	int found = 0;
	for (int i = 0; i < routes.len; i++) {
		if (strcmp(code, routes.list[i].route_id) == 0) {
			found = 1;
			total_delay += routes.list[i].delay;
		}
	}
	if (!found) {
		printf("\t\t> No match found \n");
	} else {
		printf("Ritardo totale accumulato dalle corse di codice '%s': %d\n", code, total_delay);
	}
}



int selezionaDati(Log routes, comando e) {
	Date start, end;
    char station[30], code [30];

	switch (e) {
		case r_date:
            if(scanf(" %d/%d/%d", &start.yy, &start.mm, &start.dd) == 3)
                scanf(" %d/%d/%d", &end.yy, &end.mm, &end.dd);
            else{
                printf("Inserire la data di Inizio: <yyyy/mm/dd>\n");
                scanf(" %d/%d/%d", &start.yy, &start.mm, &start.dd);
                printf("Inserire la data di Fine: <yyyy/mm/dd>\n");
                scanf(" %d/%d/%d", &end.yy, &end.mm, &end.dd);
            }

			printDateInterval(routes, start, end);
			break;
		case r_partenza:
            if(scanf(" %s", station) != 1){
                printf("Inserire la stazione di partenza> \n");
                scanf("%s", station);
            }
			printDeparture(routes, station);
		break;
		case r_capolinea:
			if(scanf(" %s", station) != 1){
				printf("Inserire la stazione di partenza: \n");
				scanf(" %s", station);
			}
			printArrival(routes, station);
			break;
		case r_ritardo:
			if(scanf(" %d/%d/%d", &start.yy, &start.mm, &start.dd) == 3)
				scanf(" %d/%d/%d", &end.yy, &end.mm, &end.dd);
			else{
				printf("Inserire la data di Inizio: <yyyy/mm/dd>\n");
				scanf(" %d/%d/%d", &start.yy, &start.mm, &start.dd);
				printf("Inserire la data di Fine: <yyyy/mm/dd>\n");
				scanf(" %d/%d/%d", &end.yy, &end.mm, &end.dd);
			}
			printDelay(routes, start,  end);
			break;
		case r_ritardo_tot:
			if(scanf(" %s", code) != 1){
				printf("Inserire il codice della tratta: \n");
				scanf(" %s", code);
			}
			printTotalDelay(routes, code);
			break;
		case r_fine:
			printf("\t---\texiting program \t---\n");
			return 0;
		default:
			printf("An unexpected error occurred, terminating ...\n");
			return 0;

	}

	return 1;
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