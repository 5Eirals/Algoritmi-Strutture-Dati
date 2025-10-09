#include <stdlib.h>
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

typedef enum comando_e comando;
enum comando_e {
	r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
};

void printRoute(Route* route);
comando leggiComando();
void selezionaDati(Route* routes, comando e);
void printDateInterval(Route* routes, Date start, Date end);
void printDeparture(Route* routes, char* station);
void printArrival(Route* routes, char* station);
void printDelay(Route* routes, Date start, Date end, int tot_delay);
void printTotalDelay(Route* routes, char* code);

int main(){
	FILE* fin, *fout;
    int N;

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

	printf("Digitare l'operazione desiderata:\n"
		"\t1. elencare tutte le corse partite in un certo intervallo di date <date>\n"
		"\t2. elencare tutti le corse partite da una certa fermata <partenza>\n"
		"\t3. elencare tutti le corse che fanno capolinea in una certa fermata <capolinea>\n"
		"\t4. elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date <ritardo>\n"
		"\t5. elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta <ritardo_tot>\n"
		"\t6. esci <fine>\n"
		">> "
	);

	selezionaDati(routes, leggiComando());

	fclose(fin);
	fclose(fout);
	return 0;
}
comando leggiComando() {
	char str[30];
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

void selezionaDati(Route* routes, comando e) {
	while (1) {
		switch (e) {
			case r_date:
				printDateInterval(routes, start, end);
			break;
			case r_partenza:
				printDeparture(routes, station);
			break;
			case r_capolinea:
				printArrival(routes, station);
			break;
			case r_ritardo:
				printDelay(routes, start,  end, tot_delay);
			break;
			case r_ritardo_tot:
				printTotalDelay(routes, code);
			break;
			case r_fine:
				printf("\t---\texiting program\t---\n");
				return;
			default:
				printf("An unexpected error occurred, terminating ...\n");
				return ;
		}
	}
}

void printRoute(Route* route){
	printf("%s %s - %s %d/%d/%d\n\tdeparture - %02d:%02d:%02d\n\tarrival - %02d:%02d:%02d\n\tdelay: %02d\n\n",
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