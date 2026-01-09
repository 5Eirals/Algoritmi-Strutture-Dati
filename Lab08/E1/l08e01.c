#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEN 100
#define FIELDS 5
#define MAX_ELEM 5
#define MAX_DIAG 3
#define INPUT_PATH "Lab07/E2/elementi.txt"

typedef enum {false, true} bool;
typedef enum {type, ingresso, uscita, precedence, finale} order_e;
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
    fprintf(fp, "%s - ", element->info[precedence] ? "segue" : "primo");
    fprintf(fp, "%s\n", element->info[finale] ? "stop" : "continua");
    fprintf(fp, "val: %.02f - diff: %02d\n\n", element->value, element->difficulty);
}

int compareElemRev(const void *a, const void *b) {
	return (((element_p)b)->value*100 - ((element_p)a)->value*100);
}

void diag_print(FILE *fp, diagonal_p diagonal, invElements_p invElements) {
	fprintf(fp, "%.03f \n", diagonal->value);
	for(int i = 0; i < diagonal->len; i++) {
		elem_printName(fp, &invElements->elements[diagonal->elements[i]]);
	}
		fprintf(fp, "\n");
}

int diag_getLastElem(diagonal_p diagonal) {
	return diagonal->elements[diagonal->len - 1];
}

void best_diagonal(diagonal_p diagonal, int DD, int DL, invElements_p invElements) {
	printf("Inside best diagonal\n");
	diagonal->len = 0;
	diagonal->difficulty = 0;
	diagonal->value = 0;
	int index = 0, limit = DD > DL ? DL : DD; ;
	bool skipped = false;
	for(int i = 0; i < invElements->len && diagonal->difficulty < limit && diagonal->len < MAX_DIAG; i++) {
		skipped = true;
		if (invElements->elements[i].difficulty < DD) {
			if (invElements->elements[i].info[precedence] == next && diagonal->len == 0) {
				diagonal->elements[++index] = i;
				diagonal->value += invElements->elements[i].value;
				diagonal->difficulty += invElements->elements[i].difficulty;
				diagonal->len++;
				for (int j = i+1; j < invElements->len; j++) {
					if (invElements->elements[j].info[precedence] == first)
						if ( invElements->elements[j].info[uscita] == invElements->elements[i].info[ingresso])
							if (diagonal->difficulty + invElements->elements[j].difficulty <= DD) {
								diagonal->elements[index-1] = j;
								diagonal->value += invElements->elements[j].value;
								diagonal->difficulty += invElements->elements[j].difficulty;
								diagonal->len++;
								i++;
								break;
							}

				}
				skipped = false;
			} else if (diagonal->len == 0 || invElements->elements[i].info[ingresso] == invElements->elements[i-1].info[uscita]) {
				diagonal->elements[index++] = i;
				diagonal->value += invElements->elements[i].value;
				diagonal->difficulty += invElements->elements[i].difficulty;
				diagonal->len++;
				skipped = false;
			}


			if (!skipped && index > 0 && invElements->elements[diagonal->elements[index - 1]].info[finale] == stop) {
				printf("Stop\n");
				break;
			}
		}
	}

	return;
}

void program_print(FILE *fp, program_p program, invElements_p invElements) {
	fprintf(fp, "TOT: %.03f \n", program->tot);
	for(int i = program->len; i > 0 ; i--) {
		fprintf(fp, "DIAG #%d > ", i);
		diag_print(fp, &program->diagonals[i-1], invElements);
	}
}

void program_clean(program_p program) {
	free(program);
}

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

	qsort(invElement->elements, invElement->len, sizeof(element_t), compareElemRev);
}

void invElements_print(FILE *fp, invElements_p invElement){
	for(int i = 0; i < invElement->len; i++){
        elem_printFull(fp, &invElement->elements[i]);
	}
}

element_t invElements_byIndex(invElements_p invElements, int index) {
	return invElements->elements[index];
}

program_p best_program(int DD, int DP, invElements_p invElements) {
	printf("Inside best program\n");
	program_p best = (program_p) malloc(sizeof(program_t));
	best->tot = 0;
	best->difficulty = 0;
	best->len = 0;
	float old_tot;
	int diff_left = DP;
	do {
		best_diagonal(&best->diagonals[best->len], DD, diff_left, invElements);
		if (best->len == 0)
			if (invElements->elements[best->diagonals[0].elements[best->diagonals[0].len-1]].difficulty > 8) {
				printf("Assigned Bonus\n");
				best->diagonals[0].value * 1.5;
			}
		old_tot = best->tot;
		best->tot += best->diagonals[best->len].value;
		best->difficulty += best->diagonals[best->len].difficulty;
		diff_left -= best->difficulty;
		best->len++;
	} while(diff_left > 0 && best->len < MAX_DIAG);

	return best;
}

int main(){
	int DD, DP;
    invElements_t* invElement = invElements_init();
    FILE *fin;
    fin = fopen(INPUT_PATH, "r");
    invElements_read(fin, invElement);

    invElements_print(stdout, invElement);

	// printf("Insert maximum Diagonal Difficulty and maximum Program Difficulty: ");
	// scanf("%d %d", &DD, &DP);

	program_p program = best_program(7, 30, invElement);
	program_print(stdout, program, invElement);
	program_clean(program);

	return 0;
}
