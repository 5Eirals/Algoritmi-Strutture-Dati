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

int count = 0;

Tile* readTiles(char* path, Tile* list, int* N);
int** readBoard(char* path, int** table, Tile* tiles, int* mark, int *used, int* R, int* C);
void freeBoard(int** table, int R);
void printTile(Tile tile);
void printBoard(int** board, Tile* tiles, int R, int C);
int checkRotated(int pos, int** board, Tile* tiles, int* mark,int *used, int R, int C, int max);
int boardPerm(int pos, int **board, Tile *tiles, int *mark, int *used, int R, int C, int max);
int checkScore(int** board, Tile* tiles, int R, int C);
Tile rotateTile(Tile tile);


int main(){
	char* tiles_path = "Lab05/E2/tiles.txt";
	char* board_path = "Lab05/E2/board.txt";
	int N, R, C;
    Tile* tiles;
	int** board;

    tiles = readTiles(tiles_path, tiles, &N);
    int *used = (int *) calloc(N, sizeof(int));
	int *mark = (int *) calloc(N, sizeof(int));
	board = readBoard(board_path, board, tiles, mark, used, &R, &C);

	int max_score = boardPerm(0, board, tiles, mark, used, R, C, -1);
	printf("max_score = %d\n", max_score);

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

int** readBoard(char* path, int** table, Tile* tiles, int* mark, int *used, int* R, int* C){
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
        	used[a] = 1;
        }
    }
    return table;
}

Tile rotateTile(Tile tile) {
	char temp_c = tile->vertical.color;
	int temp_v = tile->vertical.value;
	tile->vertical.color = tile->horizontal.color;
	tile->vertical.value = tile->horizontal.value;
	tile->horizontal.color = temp_c;
	tile->horizontal.value = temp_v;
	return tile;
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

int boardPerm(int pos, int** board, Tile* tiles, int* mark, int *used, int R, int C, int max) {
	if (pos >= R*C) {
		return checkRotated(0, board, tiles, mark, used, R, C, max);
	}

	for (int i=0; i<R*C; i++)
		if (mark[i] == 0) {
			mark[i] = 1;
			while (board[pos/C][pos%C] != -1)
				pos++;
			board[pos/C][pos%C] = i;
			max = boardPerm(pos+1, board, tiles, mark, used, R, C, max);
			mark[i] = 0;
			board[pos/C][pos%C] = -1;
		}
	return max;
}

int checkRotated(int pos, int** board, Tile* tiles, int* mark, int *used, int R, int C, int max) {
	if (pos >= R*C) {
		int score = checkScore(board, tiles, R, C);
		if (score > max) {
			return score;
		}
		return max;
	}

	max = checkRotated(pos+1, board, tiles, mark, used, R, C, max);
	if (used[pos] == 0) {
		used[pos] = 1;
		char temp_c = tiles[pos]->vertical.color;
		int temp_v = tiles[pos]->vertical.value;
		tiles[pos]->vertical.color = tiles[pos]->horizontal.color;
		tiles[pos]->vertical.value = tiles[pos]->horizontal.value;
		tiles[pos]->horizontal.color = temp_c;
		tiles[pos]->horizontal.value = temp_v;

		max = boardPerm(pos+1, board, tiles, mark, used, R, C, max);
		used[pos] = 0;
	}
	return max;
}

int checkScore(int** board, Tile* tiles, int R, int C) {
	int rows = 0;
	int cols = 0;
	for(int i = 0; i < R; i++) {
		int r_diff = 0;
		int r_buff = 0;
		int c_diff = 0;
		int c_buff = 0;
		char r_last = tiles[board[i][0]]->horizontal.color;
		char c_last = tiles[board[0][i]]->vertical.color;
		for(int j = 0; j < C; j++) {
			if(tiles[board[i][j]]->horizontal.color != r_last) r_diff++;
			r_last = tiles[board[i][j]]->horizontal.color;
			r_buff += tiles[board[i][j]]->horizontal.value;
			if(tiles[board[j][i]]->vertical.color != c_last) c_diff++;
			c_last = tiles[board[j][i]]->vertical.color;
			c_buff += tiles[board[j][i]]->vertical.value;
		}
		if(r_diff == 0) rows += r_buff;
		if(c_diff == 0) cols += c_buff;
	}

	return rows + cols;
}