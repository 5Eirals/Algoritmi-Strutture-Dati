#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_ERROR 3
#define MAX_LEN 255

typedef struct{
	int len;
    char** songs;
} Playlist;

typedef struct{
	int len;
    Playlist* playlist;
} Setlist;

Setlist* readSongs(char* path);
void freeSetlist(Setlist* setlist);
void printSetlist(Setlist setlist);
int printPlaylists(int pos, Playlist* playlist, char** sol, int n, int count);

int main() {
    char* path = "Lab04/E2/brani.txt";
    int count = 0;
    Setlist* setlist = readSongs(path);
    char** sol = (char**)malloc(setlist->len * sizeof(char*));
    count = printPlaylists(0, setlist->playlist, sol, setlist->len, count);
    printf("Combinazioni: %d\n", count);
}

void printSetlist(Setlist setlist){
	for (int i = 0; i < setlist.len; i++){
        for (int j = 0; j < setlist.playlist[i].len; j++){
          	printf("%s\n", setlist.playlist[i].songs[j]);
        }
        printf("\n");
	}
}

Setlist* readSongs(char* path){
	FILE* file;
	char buffer[MAX_LEN];
    Setlist* setlist = (Setlist*) malloc(sizeof(Setlist));
    if ((file = fopen(path, "r")) == NULL){
    	printf("An error occurred while opening the input file, terminating...\n");
        return NULL;
    }

    fscanf(file, "%d", &setlist->len);
	setlist->playlist = (Playlist*) malloc(sizeof(Playlist) * setlist->len);
    for (int i = 0; i < setlist->len; i++){
    	fscanf(file, " %d", &setlist->playlist[i].len);
    	setlist->playlist[i].songs = (char**)malloc(setlist->playlist[i].len * sizeof(char*));
        for (int j = 0; j < setlist->playlist[i].len; j++){
        	fscanf(file, " %s", buffer);
        	setlist->playlist[i].songs[j] = strdup(buffer);
        }
    }
	fclose(file);
    return setlist;
}

void freeSetlist(Setlist* setlist){
	for (int i = 0; i < setlist->len; i++) {
		for (int j = 0; j < setlist->playlist[i].len; j++) {
			free(setlist->playlist[i].songs[j]);
		}
	}
	free(setlist->playlist);
    free(setlist);
}

int printPlaylists(int pos, Playlist* playlist, char** sol, int n, int count){
	int i;
	if (pos >= n) {
		for (i = 0; i < n; i++)
			printf("%s ", sol[i]);
		printf("\n");
		return ++count;
	}
	for (i = 0; i < playlist[pos].len; i++) {
		sol[pos] = playlist[pos].songs[i];
		count = printPlaylists(pos+1, playlist, sol, n, count);
	}
	return count;
}
