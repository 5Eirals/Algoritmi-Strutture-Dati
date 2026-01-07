#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEN 100
#define FIELDS 5
#define MAX_ELEM 5
#define MAX_DIAG 3
#define INPUT_PATH "Lab07/E2/elementi.txt"

typedef enum {false, true} bool;
typedef enum {type, ingresso, uscita, precedence, finale} order;
typedef enum {transition, backward, forward} type_e;
typedef enum {back_i, front_i} ingresso_e;
typedef enum {back_u, front_u} uscita_e;
typedef enum {first, next} precedence_e;
typedef enum {go_on, stop } finale_e;

typedef struct element_s {
	char name[LEN];
	int info[FIELDS];
    float value;
    int difficulty;
} element_t, *element_p;

typedef struct invElements_s {
	element_p elements;
    int len;
} invElements_t, *invElements_p;

typedef struct diagonal_s {
	int elements[MAX_ELEM];
    int len;
	float value;
    int difficulty;
} diagonal_t, *diagonal_p;

typedef struct program_s {
	diagonal_t diagonals[MAX_DIAG];
    int len;
    float tot;
	int difficulty;
} program_t, *program_p;

void elem_printName(FILE *fp, element_p element){
	fprintf(fp, "%s ", element->name);
}
void elem_printFull(FILE *fp, element_p element){
	fprintf(fp, "%s \n ", element->name);

    switch(element->info[type]){
    	case transition:
        	fprintf(fp, "transizione - ");
        break;
        case backward:
			fprintf(fp, "acrobatico indietro - ");
        break;
        case forward:
        	fprintf(fp, "acrobatico avanti - ");
        break;
    }
    fprintf(fp, "%s - ", element->info[ingresso] ? "frontale" : "spalle");
    fprintf(fp, "%s - ", element->info[uscita] ? "frontale" : "spalle");
    fprintf(fp, "%s - ", element->info[precedence] ? "primo" : "segue");
    fprintf(fp, "%s\n", element->info[finale] ? "stop" : "continua");
    fprintf(fp, "val: %.02f - diff: %02d\n\n", element->value, element->difficulty);
}

void diag_print(FILE *fp, diagonal_p diagonal, invElements_p invElements) {
	fprintf(fp, "%.03f \n", diagonal->value);
	for(int i = 0; i < diagonal->len; i++) {
		elem_printName(fp, &invElements->elements[diagonal->elements[i]]);
	}
}

void program_print(FILE *fp, program_p program, invElements_p invElements) {
	fprintf(fp, "TOT: %.03f \n", program->tot);
	for(int i = 0; i < program->len; i++) {
		fprintf(fp, "DIAG #%d > ", i+1);
		diag_print(fp, &program->diagonals[i], invElements);
	}
}

program_p best_program(){}

invElements_p invElements_init(){
	invElements_p invElement = (invElements_p) malloc(sizeof(invElements_t));
    invElement->elements = NULL;
    invElement->len = 0;
    return invElement;
}

void invElements_free(invElements_p invElement){
	free(invElement->elements);
    free(invElement);
}

void invElements_read(FILE* fp, invElements_p invElement){
	int size; fscanf(fp, "%d", &size);

    invElement->elements = (element_p) malloc(sizeof(element_t) * size);
	invElement->len = size;

    for(int i = 0; i < size; i++){
    	fscanf(fp, "%s %d %d %d %d %d %f %d",
             invElement->elements[i].name,
             &invElement->elements[i].info[type],
             &invElement->elements[i].info[ingresso],
             &invElement->elements[i].info[uscita],
             &invElement->elements[i].info[precedence],
             &invElement->elements[i].info[finale],
             &invElement->elements[i].value,
             &invElement->elements[i].difficulty
             );
    }
}

void invElements_print(FILE *fp, invElements_p invElement){
	for(int i = 0; i < invElement->len; i++){
        elem_printFull(fp, &invElement->elements[i]);
	}
}

int main(){
	int DD, DP;
    invElements_t* invElement = invElements_init();
    FILE *fin;
    fin = fopen(INPUT_PATH, "r");
    invElements_read(fin, invElement);

    invElements_print(stdout, invElement);

	printf("Insert maximum Diagonal Difficulty and maximum Program Difficulty: ");
	scanf("%d %d", &DD, &DP);



	return 0;
}
