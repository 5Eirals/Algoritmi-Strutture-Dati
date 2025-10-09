// Regex
//	. trova un singolo carattere (cioè qualunque carattere può corrispondere a un punto)
//	[] trova un singolo carattere contenuto nelle parentesi (cioè uno qualsiasi dei caratteri tra parentesi va bene). Si assumono distinti i caratteri fra parentesi.
//	[^ ] trova ogni singolo carattere non contenuto nelle parentesi (cioè tutti i caratteri tra parentesi non vanno bene). Si assumono distinti i caratteri fra parentesi.
//	\a trova un carattere minuscolo
//	\A trova un carattere maiuscolo

#include <stdio.h>
#include <string.h>

int cercaRegexp(char* src, char* regexp);
int regexSize(char* str);

int main(){
	char* src = "moto foto roto";
    char* regexp = "[^fmp]oto";

	printf("src: %s \n\tregex: %s\n", src, regexp);
    int result = cercaRegexp(src, regexp);

    if (result < 0){
    	printf("Regex not found\n");
    } else {
    	printf("Regex found form index: %d", result);
    }
	return 0;
}

int regexSize(char* str){
	int size = strlen(str);
	char* ptr, *start = str;
	start = str;
	while((ptr = strchr(start, '\\')) != NULL){
		size--; // either \a or \A since src is alphanumerical
		start = ptr + 1;
	}

	start = str;
	while((ptr = strchr(start, '[')) != NULL){
		char* ptrf;
		if((ptrf = strchr(start, ']')) != NULL){
			size =  size - (ptrf-ptr);
			// considering src as alphanumerical the only occurrence of [] is for a metacharacter
			start = ptrf + 1;
		}
	}
	return size-1;
}

int cercaRegexp(char* src, char* regexp) {
	int index = 0, regx_i = 0;
	int src_len = strlen(src);
	int regex_len = regexSize(regexp);

	for (index = 0; src_len - index + 1 != regex_len; index++) {
		int valid = 1;
		int i = index; //
		while (regexp[regx_i] != '\0' && valid) {
			switch (regexp[regx_i]) {
				case '.':
					break;
				case '[':
					regx_i++;
					int j = 0;
					if (regexp[regx_i] == '^') {
						regx_i++;
						while (regexp[regx_i+j] != ']') {
							if (regexp[regx_i+j] == src[i+regx_i] && valid) {
								valid = 0;
							}
							j++;
						}
						regx_i += j;
					} else {
						valid = 0;
						while (regexp[regx_i+j] != ']') {
							if (regexp[regx_i+j] == src[i]) {
								valid = 1;
							}
							j++;
						}

						regx_i += j;
					}
					break;
				case '\\':
					regx_i++;
					if (regexp[regx_i] == 'a' && ('a' > src[i] || src[i] > 'z'))
						valid = 0;
					if (regexp[regx_i] == 'A' && ('A' > src[i] || src[i] > 'Z'))
						valid = 0;
					break;
				default:
					if (regexp[regx_i] != src[i])
						valid = 0;
					break;
			}

			regx_i++;
			i++;
		}

		regx_i = 0;
		if (valid) {
			return index;
		}
	}

	return -1;
}
