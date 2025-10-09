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
	char src [100];
    char* regexp;

	printf("Type the source string: \n");
	gets(src);
	printf("Type the regex string:");
	scanf("%s", regexp);

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
		int i = index; //working src index for inner loop
		while (regexp[regx_i] != '\0' && valid) {
			switch (regexp[regx_i]) { //switch-case to check metacharacters
				case '.':
					break;
				case '[':
					regx_i++;
					int j = 0;
					if (regexp[regx_i] == '^') {
						regx_i++;
						while (regexp[regx_i+j] != ']') {
							if (regexp[regx_i+j] == src[i+regx_i] && valid) {
								valid = 0; // if a match is found within the exclusion list change the valid flag
								// keep looping to exit the parenthesis and correctly update regx_i
							}
							j++;
						}
						regx_i += j;
					} else {
						valid = 0; // set failing condition by default
						while (regexp[regx_i+j] != ']') {
							if (regexp[regx_i+j] == src[i]) {
								valid = 1; //if at least a match is found within the list change the valid flag
								// keep looping to exit the parenthesis and correctly update regx_i
							}
							j++;
						}

						regx_i += j;
					}
					break;
				case '\\':
					regx_i++;
					if (regexp[regx_i] == 'a' && ('a' > src[i] || src[i] > 'z')) //check lowercase
						valid = 0;
					if (regexp[regx_i] == 'A' && ('A' > src[i] || src[i] > 'Z')) //check uppercase
						valid = 0;
					break;
				default:
					if (regexp[regx_i] != src[i]) // check character by character
						valid = 0;
					break;
			}

			regx_i++;
			i++; // increment the working index without altering the starting index
		}

		regx_i = 0;
		if (valid) {
			return index; // if during the regex check a fail condition isn't triggered return the starting index
		}
	}

	return -1;
}
