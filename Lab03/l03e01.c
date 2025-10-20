#include <stdio.h>
#include <stdlib.h>

#define LEN 7

int majority(int* a, int N );

int main(){
	int vec[LEN] = {3, 3, 9, 4 ,3, 5, 3};

    int maj = majority(vec, LEN);

    if(maj > 0)
    	printf("Majority number is: %d\n", maj);
    else
    	printf("No majority number found\n");

	return 0;
}

int majority(int* a, int N ){ //how to implement backtracking?
	for(int i = 0; i < N; i++){
        if(a[0] == a[1]){
   			return 1 + majority(a+i, N-i);
        }
          return 0;

	}
	return majority(a+1, N-1);
}