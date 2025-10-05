// Regex
//	. trova un singolo carattere (cioè qualunque carattere può corrispondere a un punto)
//	[] trova un singolo carattere contenuto nelle parentesi (cioè uno qualsiasi dei caratteri tra parentesi va bene). Si assumono distinti i caratteri fra parentesi.
//	[^ ] trova ogni singolo carattere non contenuto nelle parentesi (cioè tutti i caratteri tra parentesi non vanno bene). Si assumono distinti i caratteri fra parentesi.
//	\a trova un carattere minuscolo
//	\A trova un carattere maiuscolo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* cercaRegexp(char* src, char* regexp);
int windowSize(char* str);

int main(){
	char* src = "hello world";
    char* regexp = ".\\a[pqr]ld";
    char* result = cercaRegexp(src, regexp);
	return 0;
}

int windowSize(char* str){
	int size = strlen(str);
	printf("size regex: %d size world: %d\n", size, strlen("world"));
	char* ptr, *start = str;

    // while((ptr = strchr(start, '.')) != NULL){
    // 	size--;
    //     start = ptr + 1;
    // 	printf("found . new size:%d \n", size);
    // }

    start = str;
    while((ptr = strchr(start, '\\')) != NULL){
        size--; // either \a or \A since src is alphanumerical
        start = ptr + 1;

    	printf("found \\a new size:%d \n", size);
    }

    start = str;
    while((ptr = strchr(start, '[')) != NULL){
    	char* ptrf;
    	if((ptrf = strchr(start, ']')) != NULL){
        	size =  size - (ptrf-ptr) + 1;
                // considering src as alphanumerical the only occurence of [] is for a metacharacter
        	start = ptrf + 1;
    	}

    	printf("found [] removing %d new size:%d \n", ptrf-ptr, size);
    }

    return size;
}

char* cercaRegexp(char* src, char* regexp){
	char* res = NULL;
    char window[windowSize(regexp)];


    return res;
}

