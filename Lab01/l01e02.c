#include <stdlib.h>
#include <stdio.h>

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

void printRoute(Route* route);

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



	return 0;
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