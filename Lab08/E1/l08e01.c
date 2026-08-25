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

static bool elem_is_acro(const element_t* elem) {
    return elem->info[type] == forward || elem->info[type] == backward;
}

void best_diag(diagonal_p diag, int DD, invElements_p inv, bool requireSeq, bool* outHasSeq) {
    diag->len = 0;
    diag->difficulty = 0;
    diag->value = 0.0f;
    int lastUscita = front_i;
    bool hasAcro = false;
    bool prevWasAcro = false;
    *outHasSeq = false;

    for (int i = 0; i < inv->len && diag->len < MAX_ELEM; ++i) {
        element_t* e = &inv->elements[i];
        if (diag->difficulty + e->difficulty > DD) continue;
        if (e->info[ingresso] != lastUscita) continue;
        bool thisIsAcro = elem_is_acro(e);
        if (requireSeq && !*outHasSeq && !(prevWasAcro && thisIsAcro) && !thisIsAcro && hasAcro) {
            continue;
        }
        diag->elements[diag->len++] = i;
        diag->value += e->value;
        diag->difficulty += e->difficulty;
        if (thisIsAcro) {
            if (prevWasAcro) {
                *outHasSeq = true;
            }
            prevWasAcro = true;
            hasAcro = true;
        } else {
            prevWasAcro = false;
        }
        lastUscita = e->info[uscita];
    }

    if (!hasAcro) {
        for (int i = 0; i < inv->len; ++i) {
            element_t* e = &inv->elements[i];
            if (elem_is_acro(e)
                && e->info[ingresso] == lastUscita
                && diag->difficulty + e->difficulty <= DD
                && diag->len < MAX_ELEM)
            {
                diag->elements[diag->len++] = i;
                diag->value += e->value;
                diag->difficulty += e->difficulty;
                hasAcro = true;
                break;
            }
        }
    }
}

program_p best_program(int DD, int DP, invElements_p inv) {
    program_p prog = malloc(sizeof(program_t));
    prog->len = 0;
    prog->difficulty = 0;
    prog->tot = 0.0f;

    bool haveForward = false, haveBackward = false;
    bool haveSeqInProg = false;

    int diffLeft = DP;

    for (int d = 0; d < MAX_DIAG; ++d) {
        bool needSeq = (d == MAX_DIAG - 1) ? !haveSeqInProg : false;
        bool gotSeq = false;

        best_diag(&prog->diagonals[d], DD, inv, needSeq, &gotSeq);

        if (prog->diagonals[d].len == 0) break;

        for (int k = 0; k < prog->diagonals[d].len; ++k) {
            element_t* e = &inv->elements[prog->diagonals[d].elements[k]];
            if (e->info[type] == forward)  haveForward = true;
            if (e->info[type] == backward) haveBackward = true;
        }
        if (gotSeq) haveSeqInProg = true;
        float diagScore = prog->diagonals[d].value;
        if (d == MAX_DIAG - 1) {
            element_t* lastE = &inv->elements[prog->diagonals[d].elements[prog->diagonals[d].len - 1]];
            if (lastE->difficulty >= 8) {
                diagScore *= 1.5f;
            }
        }
        prog->tot += diagScore;
        prog->difficulty += prog->diagonals[d].difficulty;
        diffLeft -= prog->diagonals[d].difficulty;
        prog->len++;

        if (diffLeft <= 0) break;
    }
    if (prog->len != MAX_DIAG || !haveForward || !haveBackward || !haveSeqInProg) {
        prog->tot = 0.0f;
    }

    return prog;
}

int main(){
	int DD, DP;
    invElements_t* invElement = invElements_init();
    FILE *fin;
    fin = fopen(INPUT_PATH, "r");
    invElements_read(fin, invElement);

	printf("Insert maximum Diagonal Difficulty and maximum Program Difficulty: ");
	scanf("%d %d", &DD, &DP);

	program_p program = best_program(10, 20, invElement);
	program_print(stdout, program, invElement);
	program_clean(program);

	return 0;
}
