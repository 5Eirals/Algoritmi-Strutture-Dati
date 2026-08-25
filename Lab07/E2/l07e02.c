#include <stdlib.h>
#include <stdio.h>

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
    fprintf(fp, "%s \n", element->name);
    switch(element->info[type]){
        case transition: fprintf(fp, "transition - "); break;
        case backward: fprintf(fp, "acrobatic backward - "); break;
        case forward: fprintf(fp, "acrobatic forward - "); break;
    }
    fprintf(fp, "%s - ", element->info[ingresso] ? "forward" : "backward");
    fprintf(fp, "%s - ", element->info[uscita] ? "forward" : "backward");
    fprintf(fp, "%s - ", element->info[precedence] ? "next" : "first");
    fprintf(fp, "%s\n", element->info[finale] ? "stop" : "next");
    fprintf(fp, "val: %.02f - diff: %02d\n\n", element->value, element->difficulty);
}

void diag_print(FILE *fp, diagonal_p diagonal, invElements_p invElements) {
    for(int i = 0; i < diagonal->len; i++) {
        elem_printName(fp, &invElements->elements[diagonal->elements[i]]);
    }
    fprintf(fp, " [Diff: %d, Val: %.3f]\n", diagonal->difficulty, diagonal->value);
}

int diag_getLastElem(diagonal_p diagonal) {
    return diagonal->elements[diagonal->len - 1];
}

void program_print(FILE *fp, program_p program, invElements_p invElements) {
    fprintf(fp, "Score TOT: %.03f - Difficulty: %d\n", program->tot, program->difficulty);
    for(int i = 0; i < program->len; i++) {
        fprintf(fp, "DIAG #%d > ", i + 1);
        diag_print(fp, &program->diagonals[i], invElements);
    }
}

invElements_p invElements_init(){
    invElements_p invElement = (invElements_p) malloc(sizeof(invElements_t));
    invElement->elements = NULL;
    invElement->len = 0;
    return invElement;
}

void invElements_free(invElements_p invElement){
    if (invElement) {
        free(invElement->elements);
        free(invElement);
    }
}

void invElements_read(FILE* fp, invElements_p invElement){
    int size;
    if (fscanf(fp, "%d", &size) != 1) return;

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

element_t invElements_byIndex(invElements_p invElements, int index) {
    return invElements->elements[index];
}

float program_getScore(program_p prog, invElements_p inv) {
    float total_score = 0;
    for (int i = 0; i < prog->len; i++) {
        float diag_val = prog->diagonals[i].value;
        if (i == MAX_DIAG - 1) {
            int last_idx = prog->diagonals[i].elements[prog->diagonals[i].len - 1];
            if (inv->elements[last_idx].difficulty >= 8) {
                diag_val *= 1.5;
            }
        }
        total_score += diag_val;
    }
    return total_score;
}

bool prog_isValid(program_p prog, int DP, invElements_p inv) {
    if (prog->difficulty > DP) return false;
    if (prog->len < MAX_DIAG) return false;

    bool forward_elem = false;
    bool backward_elem = false;
    bool acrobatic_sequence = false;

    for (int i = 0; i < prog->len; i++) {
        diagonal_t *diag = &prog->diagonals[i];
        bool has_acrobatic = false;
        int sequence = 0;

        for (int j = 0; j < diag->len; j++) {
            element_t e = inv->elements[diag->elements[j]];

            if (e.info[type] == forward) {
                forward_elem = true;
                has_acrobatic = true;
                sequence++;
            } else if (e.info[type] == backward) {
                backward_elem = true;
                has_acrobatic = true;
                sequence++;
            } else {
                sequence = 0;
            }

            if (sequence >= 2) acrobatic_sequence = true;
        }

        if (!has_acrobatic) return false;
    }

    return forward_elem && backward_elem && acrobatic_sequence;
}

void solve_program(int diag_idx, invElements_p inv, int DD, int DP, program_t *current_p, program_t *best_p);

void generate_diagonal(int elem_idx, int diag_idx, invElements_p inv, int DD, int DP, program_t *current_p, program_t *best_p) {
    if (elem_idx > 0) {
        current_p->len = diag_idx + 1;
        solve_program(diag_idx + 1, inv, DD, DP, current_p, best_p);
    }

    if (elem_idx >= MAX_ELEM) return;

    for (int i = 0; i < inv->len; i++) {
        element_t e = inv->elements[i];
        diagonal_t *d = &current_p->diagonals[diag_idx];

        bool can_insert = true;
        if (d->difficulty + e.difficulty > DD) can_insert = false;
        if (current_p->difficulty + e.difficulty > DP) can_insert = false;

        if (elem_idx == 0) {
            if (e.info[ingresso] != front_i || e.info[precedence] != first) can_insert = false;
        } else {
            int prev_idx = d->elements[elem_idx - 1];
            if (inv->elements[prev_idx].info[uscita] != e.info[ingresso]) can_insert = false;
            if (inv->elements[prev_idx].info[finale] == stop) can_insert = false;
        }

        if (can_insert) {
            d->elements[elem_idx] = i;
            d->len++;
            d->value += e.value;
            d->difficulty += e.difficulty;
            current_p->difficulty += e.difficulty;

            generate_diagonal(elem_idx + 1, diag_idx, inv, DD, DP, current_p, best_p);

            current_p->difficulty -= e.difficulty;
            d->difficulty -= e.difficulty;
            d->value -= e.value;
            d->len--;
        }
    }
}

void solve_program(int diag_idx, invElements_p inv, int DD, int DP, program_t *current_p, program_t *best_p) {
    if (diag_idx == MAX_DIAG) {
        if (prog_isValid(current_p, DP, inv)) {
            float current_score = program_getScore(current_p, inv);
            if (current_score > best_p->tot) {
                best_p->tot = current_score;
                best_p->difficulty = current_p->difficulty;
                best_p->len = current_p->len;
                for (int i = 0; i < MAX_DIAG; i++) best_p->diagonals[i] = current_p->diagonals[i];
            }
        }
        return;
    }

    current_p->diagonals[diag_idx].len = 0;
    current_p->diagonals[diag_idx].value = 0;
    current_p->diagonals[diag_idx].difficulty = 0;
    generate_diagonal(0, diag_idx, inv, DD, DP, current_p, best_p);
}


int main() {
    int DD, DP;
    invElements_p invElement = invElements_init();
    FILE *fin = fopen(INPUT_PATH, "r");
    invElements_read(fin, invElement);

    printf("Insert maximum Diagonal Difficulty and maximum Program Difficulty: ");
    scanf("%d %d", &DD, &DP);

    program_t best_prog;
    best_prog.tot = -1.0;
    program_t current_prog;
    current_prog.difficulty = 0;
    current_prog.len = 0;

    solve_program(0, invElement, DD, DP, &current_prog, &best_prog);

    if (best_prog.tot > 0) {
        program_print(stdout, &best_prog, invElement);
    }

    invElements_free(invElement);
    fclose(fin);
    return 0;
}