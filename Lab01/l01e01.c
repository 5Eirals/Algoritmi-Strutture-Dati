// Regex
//	. trova un singolo carattere (cioè qualunque carattere può corrispondere a un punto)
//	[] trova un singolo carattere contenuto nelle parentesi (cioè uno qualsiasi dei caratteri tra parentesi va bene). Si assumono distinti i caratteri fra parentesi.
//	[^ ] trova ogni singolo carattere non contenuto nelle parentesi (cioè tutti i caratteri tra parentesi non vanno bene). Si assumono distinti i caratteri fra parentesi.
//	\a trova un carattere minuscolo
//	\A trova un carattere maiuscolo

#include <stdio.h>
#include <string.h>

int cercaRegexp(char* src, char* regexp);
int windowSize(char* str);
int checkMeta(char c, char* regexp, int* regex_index);

int main(){
	char* src = "hello world";
    char* regexp = ".\\a[pqr]ld";

	printf("src: %s \n\tregex: %s\n", src, regexp);
    int result = cercaRegexp(src, regexp);

    if (result < 0){
    	printf("Regex not found\n");
    } else {
    	printf("Regex found form index: %d = %c\n", result, src[result]);
    }
	return 0;
}

int checkMeta(char c, char* regexp, int* regex_index){
	printf("\nInside checkMeta, index: %d\n", *regex_index);
	if(regexp[*regex_index] == '.') {
		*regex_index = *regex_index + 1;
		return 1;
	}
	if(regexp[*regex_index++] == '\\') {
		if (regexp[*regex_index++] == 'a' && 'a'-1 < c && c < 'z'+1)
			return 1;
		if (regexp[*regex_index++] == 'A' && 'A'-1 < c && c < 'Z'+1)
			return 1;
	}
	if(regexp[*regex_index++] == '[') {
		if(regexp[*regex_index++] == '^') {
			while (regexp[*regex_index] != ']') {
				if (regexp[*regex_index++] == c)
					return 0;
			}
		} else {
			while (regexp[*regex_index] != ']') {
				if (regexp[*regex_index++] == c)
					return 1;
			}
		}
	}

	if(regexp[*regex_index++] == c)
		return 1;
    return 0;
}

int cercaRegexp(char* src, char* regexp){
	int i;
	int flag = 1;
    for(i = 0; i < strlen(src) || flag == 0; i++){
        for(int j = 0; regexp[j] != '\0' || flag;){
			flag = 0;
        	printf("Inside for, checking: %c\n", regexp[j]);
        	//traduci come switch
        	if(regexp[j++] == '.'){
        		continue;
        	}
        	if(regexp[j++] == '\\') {
        		if (regexp[j++] == 'a' && !('a'-1 < src[i] && src[i] < 'z'+1)) {
					flag = 1;
        			break;
        		}
        		if (regexp[j++] == 'A' && !('A'-1 < src[i] && src[i] < 'Z'+1)) {
					flag = 1;
        			break;
        		}
        	}
        	if(regexp[j++] == '[') {
        		if(regexp[j++] == '^') {
        			while (regexp[j++] != ']') {
        				if (regexp[j++] == src[i]) {
        					flag = 1;
        				}
        			}
        			break;
        		} else {
        			while (regexp[j++] != ']') {
        				flag = 1;
        				if (regexp[j++] == src[i]) {
        					flag = 0;
        					break;
        				}
        			}
        			break;
        		}
        	}

        	if(regexp[j++] != src[i]) {
        		flag = 1;
        		break;
        	}
        }
    }
    if (flag) {
	    return -1;
    } else {
	    return i;
    }
}

