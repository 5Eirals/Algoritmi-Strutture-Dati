#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char color;
	int value;
} Tube;

typedef struct {
	Tube vertical;
    Tube horizontal;
} tile_s, *Tile;

Tile* readTiles(char* path, Tile* list, int* N);
int** readBoard(char* path, int** table, Tile* tiles, int* mark, int* R, int* C);
void freeBoard(int** table, int R);
void printTile(Tile tile);
void printBoard(int** board, Tile* tiles, int R, int C);
int searchMax(int** board, Tile* tiles, int* mark, int R, int C);

int main(){
	char* tiles_path = "Lab05/E2/tiles.txt";
	char* board_path = "Lab05/E2/board.txt";
	int N, R, C;
    Tile* tiles;
	int** board;

    tiles = readTiles(tiles_path, tiles, &N);
    int *mark = (int *) calloc(N, sizeof(int));
	board = readBoard(board_path, board, tiles, mark, &R, &C);
    printBoard(board, tiles, R, C);

	int max_score = searchMax(board, tiles, mark, R, C);

	free(tiles);
    freeBoard(board, R);
	return 0;
}

Tile* readTiles(char* path, Tile* list, int* N){
	FILE* file;
    if((file = fopen(path, "r"))==NULL){
    	printf("An error occurred while reading input file, terminating...\n");
        return NULL;
    }
    fscanf(file, "%d", N);
    list = malloc(*N * sizeof(Tile));

    for(int i = 0; i < *N; i++){
    	list[i] = (Tile)malloc(sizeof(tile_s));
    	fscanf(file, " %c %d %c %d ",
    		&(list[i]->horizontal.color),
    		&(list[i]->horizontal.value),
    		&(list[i]->vertical.color),
    		&(list[i]->vertical.value)
    		);
    }

    fclose(file);
    return list;
}

int** readBoard(char* path, int** table, Tile* tiles, int* mark, int* R, int* C){
	int a, b;
	FILE* file;
	if((file = fopen(path, "r"))==NULL){
		printf("An error occurred while reading input file, terminating...\n");
		return NULL;
	}
    fscanf(file, "%d %d", R, C);
    table = malloc(*R * sizeof(int*));
    for(int i = 0; i < *R; i++){
    	table[i] = (int*)malloc(*C * sizeof(int));
        for(int j = 0; j < *C; j++){
        	fscanf(file, "%d / %d", &a, &b);
            if(a == -1){
            	table[i][j] = a;
            	continue;
            }
            if(b){
            	char temp_c = tiles[a]->vertical.color;
                int temp_v = tiles[a]->vertical.value;
                tiles[a]->vertical.color = tiles[a]->horizontal.color;
            	tiles[a]->vertical.value = tiles[a]->horizontal.value;
            	tiles[a]->horizontal.color = temp_c;
                tiles[a]->horizontal.value = temp_v;
            }
        	table[i][j] = a;
            mark[a] = 1;
        }
    }
    return table;
}


void freeBoard(int** board, int R){
	for(int i = 0; i < R; i++){
          free(board[i]);
	}
    free(board);
}

void printTile(Tile tile){
	if (tile == NULL){
          printf("");
          return;
	}
    printf("___|%c|___\n"
           " %c | | %d \n"
           "```|%d|```\n", tile->vertical.color, tile->horizontal.color, tile->horizontal.value, tile->vertical.value);
}

void printBoard(int** board, Tile* tiles, int R, int C){
	for(int i = 0; i < R*3; i++){
        for(int j = 0; j < C; j++){
        	if(board[i/3][j] == -1){
           		printf("         ");
        	}else{
            	switch(i%3){
                	case 0:
                        printf("___|%c|___", tiles[board[i/3][j]]->vertical.color);
                        break;
                    case 1:
                    	printf(" %c | | %d ", tiles[board[i/3][j]]->horizontal.color, tiles[board[i/3][j]]->horizontal.value);
                        break;
                    case 2:
                    	printf("```|%d|```", tiles[board[i/3][j]]->vertical.value);
            	}
            }
        }
        printf("\n");
	}
}

int searchMax(int** board, Tile* tiles, int* mark, int R, int C) {
	int max = 0;
	boardPerm(0, board, tiles, mark, R, C, &max);
	return 0;
}

void boardPerm(int pos, int** board, Tile* tiles, int* mark, int R, int C, int *max) {
	int* perm = (int*)malloc(R*C * sizeof(int));
	for(int i = 0; i < R*C; i++) {
		if(mark[i] == 1) {
			perm[pos] = i;
		}
	}

}

void permutations() {

}
